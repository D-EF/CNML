/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:48:46
 * @FilePath: \CNML\src\Algebra\NML_Matrix.cpp
 * @Description: 矩阵 Matrix
 */

#include "NML.hpp"
#include <iostream>
#include "./NML_Matrix.hpp"

namespace NML{
    namespace Matrix{
        
        void printf_Matrix(var*& matrix, Idx_VM width, Idx_VM height){
            Idx_VM i=0;
            for(;  i<height;  i++){
                printf_Vec(matrix+i*width, width);
            }
            printf("\n");
        }


        var*& setup_Matrix__Identity(var*& out, Idx_VM width, Idx_VM height){
            Idx_VM l=width*height;
            for(Idx_VM i=0;  i<l;  i++){
                out[i]=0;
            }
            l=width>height?height:width;
            for(Idx_VM i=0;  i<l;  i++){
                out[i*width+i]=1;
            }
            return out;
        }

        var*& setup_Matrix__Resize(var*& out, var*& mat, Idx_VM low_width, Idx_VM new_width, Idx_VM _low_height, Idx_VM _new_height, Idx_VM shift_left, Idx_VM shift_top){
            Idx_VM low_height   = _low_height?_low_height:low_width;
            Idx_VM new_height   = _new_height?_new_height:new_width;
            Idx_VM left, load_left, top, load_top;
            Idx_VM right    = std::min((Idx_VM)(shift_left+low_width), new_width);
            Idx_VM bottom   = std::min((Idx_VM)(shift_top+low_height), new_height);
            if(shift_left>=0){   left   = shift_left;   load_left   = 0;            }
            else{                left   = 0;            load_left   =-shift_left;   }
            if(shift_top>=0){    top    = shift_top;    load_top    = 0;            }
            else{                top    = 0;            load_top    =-shift_top;    }

            for (Idx_VM y = top; y < bottom; y++) {
                Idx_VM i_out= y * new_width;
                Idx_VM i_mat= (y + load_top) * low_width + (load_left);
                for (Idx_VM x = left; x < right; ++x, ++i_out, ++i_mat) {
                    out[i_out] = mat[i_mat];
                }
            }
            return out;
        }

        var*& setup_Matrix__HadamardProduct(var*& out, var*& mat_left, var*& mat_right, Idx_VM width, Idx_VM height){
            Idx_VM i=0;
            for(Idx_VM v=0;  v<height;  ++v){
                for(Idx_VM u=0;  u<width;  ++u, ++i){
                    out[i]=mat_left[i]*mat_right[i];
                }
            }
            return out;
        }

        var*& setup_Matrix__KroneckerProduct(var*& out, var*& mat_left, var*& mat_right, Idx_VM width_left, Idx_VM height_left, Idx_VM width_right, Idx_VM height_right){
            // hl, hr, wl, wr
            Idx_VM i=0, i_vr_head, il=0;

            for(Idx_VM vl=0;   vl<height_left;    ++vl)        {
            for(Idx_VM vr=0;   vr<height_right;   ++vr)        { i_vr_head=vr*width_right; il=vl*width_left;
            for(Idx_VM ul=0;   ul<width_left;     ++ul, ++il)   { 
            for(Idx_VM ur=0;   ur<width_right;    ++ur, ++i)    {
                out[i]=mat_left[il]*mat_right[i_vr_head+ur];
            }}}}
            
            return out;
        }

        var*& setup_Matrix__Concat(var*& out, var**& mats, Idx_VM width_m, Idx_VM height_m, Idx_VM width_g, Idx_VM height_g){
            // hl, hr, wl, wr
            Idx_VM i=0, i_vm_head, ig=0;

            for(Idx_VM vg=0;   vg<height_g;    ++vg)        {
            for(Idx_VM vm=0;   vm<height_m;   ++vm)        { i_vm_head=vm*width_m; ig=vg*width_g;
            for(Idx_VM ug=0;   ug<width_g;     ++ug, ++ig)   { 
            for(Idx_VM um=0;   um<width_m;    ++um, ++i)    {
                out[i]=mats[ig][i_vm_head+um];
            }}}}
            
            return out;
        }


        void transformation__ExchangeRow(var*& mat, Idx_VM width, Idx_VM v1, Idx_VM v2){
            Idx_VM i1 = v1*width,
                i2 = v2*width;
            for(Idx_VM i=0;  i<width;  ++i){
                std::swap(mat[i1+i], mat[i2+i]);
            }
        }
        void transformation__ExchangeRow(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM v1, Idx_VM v2){
            Idx_VM i1 = v1*width,
                i2 = v2*width;
            for(Idx_VM i=0;  i<width;  ++i){
                for(Idx_VM j=0;  j<length_g;  ++j){
                    std::swap(mats[j][i1+i], mats[j][i2+i]);
                }
            }
        }


        void transformation__ExchangeCol(var*& mat, Idx_VM width, Idx_VM height, Idx_VM u1, Idx_VM u2){
            var temp;
            Idx_VM i1 = u1,
                i2 = u2;
            for(Idx_VM i=0;  i<height;  ++i, i1+=width, i2+=width){
                std::swap(mat[i1], mat[i2]);
            }
        }
        void transformation__ExchangeCol(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM height, Idx_VM u1, Idx_VM u2){
            Idx_VM i1 = u1,
                i2 = u2;
            for(Idx_VM i=0;  i<height;  ++i, i1+=width, i2+=width){
                for(Idx_VM j=0;  j<length_g;  ++j){
                    std::swap(mats[j][i1], mats[j][i2]);
                }
            }
        }


        void transformation__ScaleRow(var*& mat, Idx_VM width, Idx_VM v, var k){
            Idx_VM index = v*width;
            for(Idx_VM i=0;  i<width;  ++i){
                mat[index+i]*=k;
            }
        }
        void transformation__ScaleRow(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM v, var k){
            Idx_VM index = v*width;
            for(Idx_VM i=0;  i<width;  ++i){
                for(Idx_VM j=0;  j<length_g;  ++j){
                    mats[j][index+i]*=k;
                }
            }
        }


        void transformation__ScaleCol(var*& mat, Idx_VM width, Idx_VM height, Idx_VM u, var k){
            Idx_VM index = u;
            for(Idx_VM i=0;  i<height;  ++i, index+=width){
                mat[index]*=k;
            }
        }
        void transformation__ScaleCol(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM height, Idx_VM u, var k){
            Idx_VM index = u;
            for(Idx_VM i=0;  i<height;  ++i, index+=width){
                for(Idx_VM j=0;  j<length_g;  ++j){
                    mats[j][index+i]*=k;
                }
            }
        }

        bool transformation__ExchangeRow_ToUnZero(var*& mat, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length){
            Idx_VM f=step_length>0?1:-1;
            Idx_VM v_target=v+f;
            for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
                if(check_Zero(mat[i])){
                    transformation__ExchangeRow(mat, width, v, v_target);
                    return true;
                }
            }
            return false;
        }
        bool transformation__ExchangeRow_ToUnZero(var**& mats, Idx_VM length_g, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length, Idx_VM _idx_m){
            Idx_VM f=step_length>0?1:-1;
            Idx_VM v_target=v+f;
            for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
                if(check_Zero(mats[_idx_m][i])){
                    transformation__ExchangeRow(mats, length_g, width, v, v_target);
                    return true;
                }
            }
            return false;
        }

        
        bool transformation__ExchangeRow_PivotToMax(var*& mat, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length){
            Idx_VM f=step_length>0?1:-1;
            Idx_VM v_target=v+f;
            
            Idx_VM max_row=v;
            Idx_VM max_row_pivot_index=index;
            for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
                if(mat[max_row_pivot_index]<mat[i]){
                    max_row_pivot_index=i;
                    max_row=v_target;
                }
            }
            if(check_Zero(mat[max_row_pivot_index])){
                return false;
            }
            if(v!=max_row) transformation__ExchangeRow(mat, width, v, max_row);
            return true;
        }
        
        bool transformation__ExchangeRow_PivotToMax(var**& mats, Idx_VM length_g, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length, Idx_VM _idx_m){
            Idx_VM f=step_length>0?1:-1;
            Idx_VM v_target=v+f;
            
            Idx_VM max_row=v;
            Idx_VM max_row_pivot_index=index;
            for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
                if(mats[_idx_m][max_row_pivot_index]<mats[_idx_m][i]){
                    max_row_pivot_index=i;
                    max_row=v_target;
                }
            }
            if(check_Zero(mats[_idx_m][max_row_pivot_index])){
                return false;
            }
            if(v!=max_row) transformation__ExchangeRow(mats, length_g, width, v, max_row);
            return true;
        }


        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, Idx_VM height_left, Idx_VM _width_left_height_right, Idx_VM _width_right){
            Idx_VM idx_out=0;
            Idx_VM width_left_height_right=_width_left_height_right?_width_left_height_right:height_left;
            Idx_VM width_right=_width_right?_width_right:height_left;

            for(Idx_VM i=0;  i<height_left;  ++i){
                for(Idx_VM j=0;  j<width_right;  ++j){
                    var temp=0;
                    for(Idx_VM l=height_left*i, k=j, c=0; c<width_left_height_right; ++c, ++l, k+=width_right){
                        temp+=mat_left[l]*mat_right[k];
                    }
                    out[idx_out]=temp;
                    ++idx_out;
                }
            }
            return out;
        }

        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, Idx_VM n){
            Idx_VM idx_out=0;
            Idx_VM length=n*n;

            for(Idx_VM i=0;  i<n;  ++i){
                for(Idx_VM j=0;  j<n;  ++j){
                    var temp=0;
                    for(Idx_VM l=n*i, k=j; k<length; ++l, k+=n){
                        temp+=mat_left[l]*mat_right[k];
                    }
                    out[idx_out]=temp;
                    ++idx_out;
                }
            }
            return out;
        }

        bool check_Orthogonal(var*& mat, Idx_VM n){
            Idx_VM u, v;
            for(v=0;  v<n-1;  ++v){
                for(u=v+1;  u<n;  ++u){
                    if(mat[clac_Index(n, u, v)]!=-mat[clac_Index(n, v, u)])return false;
                }
            }
            return true;
        }

        var*& transpose(var*& mat, Idx_VM n){
            var temp;
            for(Idx_VM v=1; v<n; ++v){
                Idx_VM point_line=v*n;
                for(Idx_VM u=0; u<v; ++u){
                    std::swap(mat[u*n+v], mat[point_line+u]);
                }
            }
            return mat;
        }
        
        var*& transpose(var*& out, var*& mat, Idx_VM width_mat, Idx_VM height_mat){
            Idx_VM idx_out=0;

            for(Idx_VM u=0;  u<width_mat;  ++u){
                for(Idx_VM v=0;  v<height_mat;  ++v){
                    out[idx_out]=mat[clac_Index(width_mat, u, v)];
                    ++idx_out;
                }
            }
            return out;
        }

        var calc_Det__Transformation(var*& mat, Idx_VM n){
            const Idx_VM length=n*n;
            var *temp_mat=create_Values__Clone(mat, length);
            var temp, det=1;
            Idx_VM _n=n-1;

            for(Idx_VM uv=0; uv<_n; ++uv){
                Idx_VM idx_v=uv*n;
                Idx_VM idx_mat__uv=idx_v+uv;
                
                if(check_Zero(temp_mat[idx_mat__uv])){    // 换行
                    if(!transformation__ExchangeRow_ToUnZero(temp_mat, length, n, idx_mat__uv, uv, n)){
                        delete temp_mat;
                        return 0;
                    }
                    else det=-det;
                }
                
                // 消元
                for(Idx_VM index=idx_mat__uv+n;  index<length;  index+=n){
                    temp=(temp_mat[index])/temp_mat[idx_mat__uv];
                    for(Idx_VM i=uv+1, j=index+1;  i<n;  ++i, ++j){
                        temp_mat[j]-=temp*temp_mat[idx_v+i];
                    }
                }
                det*=temp_mat[idx_mat__uv];
            }
            det*=temp_mat[length-1];

            delete temp_mat;

            return det;
        }
        

        bool setup_Matrix__Inverse__Transformation(var*& out, var*& mat, Idx_VM n){
            Idx_VM length=n*n;
            var *temp_mat=create_Values__Clone(mat, length);
            
            // 初始化 out 为增广矩阵
            setup_Matrix__Identity(out, n, n);
            var **mats=new var*[2]{temp_mat, out};
            
            for(Idx_VM uv=0; uv<n; ++uv){
                Idx_VM idx_v=uv*n;
                Idx_VM idx_mat__uv=idx_v+uv;

                // 换行设置最大主元
                if(!transformation__ExchangeRow_PivotToMax(mats, 2, length, n, idx_mat__uv, uv, n)) {
                    delete temp_mat;
                    delete mats;
                    return false;
                }
                transformation__ScaleRow(mats, 2, n, uv, 1/mats[0][idx_mat__uv]);

                for(Idx_VM i=0, index=0;  i<n;  ++i, index+=n){
                    if(i==uv) continue;
                    var k=temp_mat[index+uv];
                    for(Idx_VM j=0;  j<n;  ++j){
                        temp_mat[index+j] -= k * temp_mat[idx_v+j];
                        out[index+j]      -= k * out     [idx_v+j];
                    }
                }
            }

            delete temp_mat;
            delete mats;
            return true;
        }

        var calc_Det(var*& mat, Idx_VM n){
            switch (n)
            {
                case 1:
                    return calc_Det__1(mat);
                break;
                
                case 2:
                    return calc_Det__2(mat);
                break;
                
                case 3:
                    return calc_Det__3(mat);
                break;
                
                case 4:
                    return calc_Det__4(mat);
                break;
            
                default:
                    return calc_Det__Transformation(mat, n);
                break;
            }
        }

        bool setup_Matrix__Inverse__2(var*& out, var*& mat){
            var d=calc_Det__2(mat);
            if(check_Zero(d))return false;
            d=1/d;
            out[0]= mat[3]*d;   out[1]=-mat[1]*d;
            out[2]=-mat[2]*d;   out[3]= mat[0]*d;
            return true;
        }
        
        bool setup_Matrix__Inverse__3(var*& out, var*& mat){
            var d=calc_Det__3(mat);
            if(check_Zero(d))return false;
            d=1/d;
            out[0]= +mat[4]*mat[8] - mat[5]*mat[7]*d;   out[1]= -mat[3]*mat[8] - mat[5]*mat[6]*d;   out[2]= +mat[3]*mat[7] - mat[6]*mat[4]*d;
            out[3]= -mat[1]*mat[8] - mat[2]*mat[7]*d;   out[4]= +mat[0]*mat[8] - mat[2]*mat[6]*d;   out[5]= -mat[0]*mat[7] - mat[1]*mat[6]*d;
            out[6]= +mat[1]*mat[5] - mat[2]*mat[4]*d;   out[7]= -mat[0]*mat[5] - mat[2]*mat[3]*d;   out[8]= +mat[0]*mat[4] - mat[1]*mat[3]*d;
            return true;
        }
        
        bool setup_Matrix__Inverse__4(var*& out, var*& mat){
            var t00 = mat[0]  * mat[5]  - mat[1]  * mat[4],
                t01 = mat[0]  * mat[6]  - mat[2]  * mat[4],
                t02 = mat[0]  * mat[7]  - mat[3]  * mat[4],
                t03 = mat[1]  * mat[6]  - mat[2]  * mat[5],
                t04 = mat[1]  * mat[7]  - mat[3]  * mat[5],
                t05 = mat[2]  * mat[7]  - mat[3]  * mat[6],
                t06 = mat[8]  * mat[13] - mat[9]  * mat[12],
                t07 = mat[8]  * mat[14] - mat[10] * mat[12],
                t08 = mat[8]  * mat[15] - mat[11] * mat[12],
                t09 = mat[9]  * mat[14] - mat[10] * mat[13],
                t10 = mat[9]  * mat[15] - mat[11] * mat[13],
                t11 = mat[10] * mat[15] - mat[11] * mat[14];
            var d=t00*t11-t01*t10+t02*t09+t03*t08-t04*t07+t05*t06;
            if(check_Zero(d))return false;
            d=1/d;
            out[0]    =(mat[5]*t11-mat[6]*t10+mat[7]*t09)*d;   out[1]    =(mat[2]*t10-mat[1]*t11-mat[3]*t09)*d;   out[2]    =(mat[13]*t05-mat[14]*t04+mat[15]*t03)*d;   out[3]    =(mat[10]*t04-mat[9] *t05-mat[11]*t03)*d;
            out[4]    =(mat[6]*t08-mat[4]*t11-mat[7]*t07)*d;   out[5]    =(mat[0]*t11-mat[2]*t08+mat[3]*t07)*d;   out[6]    =(mat[14]*t02-mat[12]*t05-mat[15]*t01)*d;   out[7]    =(mat[8] *t05-mat[10]*t02+mat[11]*t01)*d;
            out[8]    =(mat[4]*t10-mat[5]*t08+mat[7]*t06)*d;   out[9]    =(mat[1]*t08-mat[0]*t10-mat[3]*t06)*d;   out[10]   =(mat[12]*t04-mat[13]*t02+mat[15]*t00)*d;   out[11]   =(mat[9] *t02-mat[8] *t04-mat[11]*t00)*d;
            out[12]   =(mat[5]*t07-mat[4]*t09-mat[6]*t06)*d;   out[13]   =(mat[0]*t09-mat[1]*t07+mat[2]*t06)*d;   out[14]   =(mat[13]*t01-mat[12]*t03-mat[14]*t00)*d;   out[15]   =(mat[8] *t03-mat[9] *t01+mat[10]*t00)*d;
            return true;
        }

        bool setup_Matrix__Inverse(var*& out, var*& mat, Idx_VM n){
            switch (n)
            {
                case 1:
                    return (out[0])&&(out[0]=1/mat[0]);
                break;
                
                case 2:
                    return setup_Matrix__Inverse__2(out, mat);
                break;
                
                case 3:
                    return setup_Matrix__Inverse__3(out, mat);
                break;
                
                case 4:
                    return setup_Matrix__Inverse__4(out, mat);
                break;
            
                default:
                    return setup_Matrix__Inverse__Transformation(out, mat, n);
                break;
            }
        }
        
    }
}

/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-05-05 02:52:22
 * @FilePath: \cnml\src\NML_Matrix.cpp
 * @Description: 矩阵 Matrix
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML.hpp"
#include <iostream>
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix{
        void printf_Matrix(var*& matrix, int width, int height){
            int i=0;
            for(;i<height;i++){
                printf_val(matrix+i*width, width);
            }
        }


        var*& setup_Identity(var*& out,int width, int height){
            int l=width*height;
            for(int i=0;i<l;i++){
                out[i]=0;
            }
            l=width>height?height:width;
            for(int i=0;i<l;i++){
                out[i*width+i]=1;
            }
            return out;
        }


        var*& setup_Resize(var*& out, var*& mat, int low_width, int new_width, int _low_height, int _new_height, int shift_left, int shift_top){
            int low_height   = _low_height?_low_height:low_width;
            int new_height   = _new_height?_new_height:new_width;
            int left, load_left, top, load_top;
            int right    = min(shift_left+low_width,new_width);
            int bottom   = min(shift_top+low_height,new_height);
            if(shift_left>=0){   left   = shift_left;   load_left   = 0;            }
            else{                left   = 0;            load_left   =-shift_left;   }
            if(shift_top>=0){    top    = shift_top;    load_top    = 0;            }
            else{                top    = 0;            load_top    =-shift_top;    }

            for (int y = top; y < bottom; y++) {
                int i_out= y * new_width;
                int i_mat= (y + load_top) * low_width + (load_left);
                for (int x = left; x < right; ++x,++i_out,++i_mat) {
                    out[i_out] = mat[i_mat];
                }
            }
            return out;
        }

        var*& setup_HadamardProduct(var*& out, var*& mat_left, var*& mat_right, int width, int height){
            int i=0;
            for(int v=0;v<height;++v){
                for(int u=0;u<width;++u,++i){
                    out[i]=mat_left[i]*mat_right[i];
                }
            }
            return out;
        }

        var*& setup_KroneckerProduct(var*& out, var*& mat_left, var*& mat_right, int width_left, int height_left, int width_right, int height_right){
            // hl, hr, wl, wr
            int i=0,i_vr_head,il=0;

            for(int vl=0;   vl<height_left;    ++vl)        {
            for(int vr=0;   vr<height_right;   ++vr)        { i_vr_head=vr*width_right; il=vl*width_left;
            for(int ul=0;   ul<width_left;     ++ul,++il)   { 
            for(int ur=0;   ur<width_right;    ++ur,++i)    {
                out[i]=mat_left[il]*mat_right[i_vr_head+ur];
            }}}}
            
            return out;
        }

        var*& setup_Concat(var*& out, var**& mats, int width_m, int height_m, int width_g, int height_g){
            // hl, hr, wl, wr
            int i=0,i_vm_head,ig=0;

            for(int vg=0;   vg<height_g;    ++vg)        {
            for(int vm=0;   vm<height_m;   ++vm)        { i_vm_head=vm*width_m; ig=vg*width_g;
            for(int ug=0;   ug<width_g;     ++ug,++ig)   { 
            for(int um=0;   um<width_m;    ++um,++i)    {
                out[i]=mats[ig][i_vm_head+um];
            }}}}
            
            return out;
        }


        void transformation__ExchangeRow(var*& mat, int width, int v1, int v2){
            int i1 = v1*width,
                i2 = v2*width;
            for(int i=0;i<width;++i){
                std::swap(mat[i1+i],mat[i2+i]);
            }
        }
        void transformation__ExchangeRow(var**& mats, int length_g, int width, int v1, int v2){
            int i1 = v1*width,
                i2 = v2*width;
            for(int i=0;i<width;++i){
                for(int j=0;j<length_g;++j){
                    std::swap(mats[j][i1+i],mats[j][i2+i]);
                }
            }
        }


        void transformation__ExchangeCol(var*& mat, int width,int height, int u1, int u2){
            var temp;
            int i1 = u1,
                i2 = u2;
            for(int i=0;i<height;++i,i1+=width,i2+=width){
                std::swap(mat[i1],mat[i2]);
            }
        }
        void transformation__ExchangeCol(var**& mats,int length_g, int width,int height, int u1, int u2){
            int i1 = u1,
                i2 = u2;
            for(int i=0;i<height;++i,i1+=width,i2+=width){
                for(int j=0;j<length_g;++j){
                    std::swap(mats[j][i1],mats[j][i2]);
                }
            }
        }


        void transformation__ScaleRow(var*& mat, int width, int v, var k){
            int index = v*width;
            for(int i=0;i<width;++i){
                mat[index+i]*=k;
            }
        }
        void transformation__ScaleRow(var**& mats,int length_g, int width, int v, var k){
            int index = v*width;
            for(int i=0;i<width;++i){
                for(int j=0;j<length_g;++j){
                    mats[j][index+i]*=k;
                }
            }
        }


        void transformation__ScaleCol(var*& mat, int width, int height, int u, var k){
            int index = u;
            for(int i=0;i<height;++i,index+=width){
                mat[index]*=k;
            }
        }
        void transformation__ScaleCol(var**& mats,int length_g, int width, int height, int u, var k){
            int index = u;
            for(int i=0;i<height;++i,index+=width){
                for(int j=0;j<length_g;++j){
                    mats[j][index+i]*=k;
                }
            }
        }

        bool transformation__ExchangeRow_ToUnZero(var*& mat, int length, int width, int index, int v, int step_length){
            int f=step_length>0?1:-1;
            int v_target=v+f;
            for(int i=index+step_length;i>=0&&i<length;i+=step_length,v_target+=f){
                if(check_Zero(mat[i])){
                    transformation__ExchangeRow(mat,width,v,v_target);
                    return true;
                }
            }
            return false;
        }
        bool transformation__ExchangeRow_ToUnZero(var**& mats, int length_g, int length, int width, int index, int v, int step_length, int _index_m){
            int f=step_length>0?1:-1;
            int v_target=v+f;
            for(int i=index+step_length;i>=0&&i<length;i+=step_length,v_target+=f){
                if(check_Zero(mats[_index_m][i])){
                    transformation__ExchangeRow(mats,length_g,width,v,v_target);
                    return true;
                }
            }
            return false;
        }

        
        bool transformation__ExchangeRow_PivotToMax(var*& mat, int length, int width, int index, int v, int step_length){
            int f=step_length>0?1:-1;
            int v_target=v+f;
            
            int max_row=v;
            int max_row_pivot_index=index;
            for(int i=index+step_length;i>=0&&i<length;i+=step_length,v_target+=f){
                if(mat[max_row_pivot_index]<mat[i]){
                    max_row_pivot_index=i;
                    max_row=v_target;
                }
            }
            if(check_Zero(mat[max_row_pivot_index])){
                return false;
            }
            if(v!=max_row) transformation__ExchangeRow(mat,width,v,max_row);
            return true;
        }
        
        bool transformation__ExchangeRow_PivotToMax(var**& mats, int length_g, int length, int width, int index, int v, int step_length, int _index_m){
            int f=step_length>0?1:-1;
            int v_target=v+f;
            
            int max_row=v;
            int max_row_pivot_index=index;
            for(int i=index+step_length;i>=0&&i<length;i+=step_length,v_target+=f){
                if(mats[_index_m][max_row_pivot_index]<mats[_index_m][i]){
                    max_row_pivot_index=i;
                    max_row=v_target;
                }
            }
            if(check_Zero(mats[_index_m][max_row_pivot_index])){
                return false;
            }
            if(v!=max_row) transformation__ExchangeRow(mats,length_g,width,v,max_row);
            return true;
        }


        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, int height_left, int _width_left_height_right, int _width_right){
            int index_out=0;
            int width_left_height_right=_width_left_height_right?_width_left_height_right:height_left;
            int width_right=_width_right?_width_right:height_left;

            for(int i=0;i<height_left;++i){
                for(int j=0;j<width_right;++j){
                    var temp=0;
                    for(int l=height_left*i,k=j,c=0; c<width_left_height_right; ++c,++l,k+=width_right){
                        temp+=mat_left[l]*mat_right[k];
                    }
                    out[index_out]=temp;
                    ++index_out;
                }
            }
            return out;
        }

        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, int n){
            int index_out=0;
            int length=n*n;

            for(int i=0;i<n;++i){
                for(int j=0;j<n;++j){
                    var temp=0;
                    for(int l=n*i,k=j; k<length; ++l,k+=n){
                        temp+=mat_left[l]*mat_right[k];
                    }
                    out[index_out]=temp;
                    ++index_out;
                }
            }
            return out;
        }

        bool check_Orthogonal(var*& mat,int n){
            int u,v;
            for(v=0;v<n-1;++v){
                for(u=v+1;u<n;++u){
                    if(mat[get_Index(n,u,v)]!=-mat[get_Index(n,v,u)])return false;
                }
            }
            return true;
        }

        var*& transpose(var*& mat, int n){
            var temp;
            for(int v=1; v<n; ++v){
                int point_line=v*n;
                for(int u=0; u<v; ++u){
                    std::swap(mat[u*n+v],mat[point_line+u]);
                }
            }
            return mat;
        }
        
        var*& transpose(var*& out, var*& mat, int width_mat, int height_mat){
            int index_out=0;

            for(int u=0;u<width_mat;++u){
                for(int v=0;v<height_mat;++v){
                    out[index_out]=mat[get_Index(width_mat,u,v)];
                    ++index_out;
                }
            }
            return out;
        }

        var calc_Det__Transformation(var*& mat,int n){
            const int length=n*n;
            var* temp_mat=create_Values__Clone(mat,length);
            var temp,det=1;
            int _n=n-1;

            for(int uv=0; uv<_n; ++uv){
                int index_v=uv*n;
                int index_mat__uv=index_v+uv;
                
                if(check_Zero(temp_mat[index_mat__uv])){    // 换行
                    if(!transformation__ExchangeRow_ToUnZero(temp_mat,length,n,index_mat__uv,uv,n)){
                        delete temp_mat;
                        return 0;
                    }
                    else det=-det;
                }
                
                // 消元
                for(int index=index_mat__uv+n;index<length;index+=n){
                    temp=(temp_mat[index])/temp_mat[index_mat__uv];
                    for(int i=uv+1,j=index+1;i<n;++i,++j){
                        temp_mat[j]-=temp*temp_mat[index_v+i];
                    }
                }
                det*=temp_mat[index_mat__uv];
            }
            det*=temp_mat[length-1];

            delete temp_mat;

            return det;
        }
        

        bool setup_Inverse__Transformation(var*& out, var*& mat, int n){
            int length=n*n;
            var* temp_mat=create_Values__Clone(mat,length);
            
            // printf_Matrix(temp_mat,n);

            // 初始化 out 为增广矩阵
            setup_Identity(out,n,n);
            var** mats=new var*[2]{temp_mat,out};
            
            for(int uv=0; uv<n; ++uv){
                int index_v=uv*n;
                int index_mat__uv=index_v+uv;

                // 换行设置最大主元
                if(!transformation__ExchangeRow_PivotToMax(mats,2,length,n,index_mat__uv,uv,n)) {
                    delete temp_mat;
                    delete mats;
                    return false;
                }

                transformation__ScaleRow(mats,2,n,uv,1/mats[0][index_mat__uv]);

                for(int i=0,index=0;i<n;++i,index+=n){
                    if(i==uv) continue;
                    var k=temp_mat[index+uv];
                    for(int j=0;j<n;++j){
                        temp_mat[index+j] -= k * temp_mat[index_v+j];
                        out[index+j]      -= k * out     [index_v+j];
                    }
                }
                
            }

            delete temp_mat;
            delete mats;
            return true;
        }

        var calc_Det(var*& mat,int n){
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
                    return calc_Det__Transformation(mat,n);
                break;
            }
        }

        bool setup_Inverse__2(var*& out, var*& mat){
            var d=calc_Det__2(mat);
            if(check_Equal(d,0))return false;
            d=1/d;
            out[0]= mat[3]*d;   out[1]=-mat[1]*d;
            out[2]=-mat[2]*d;   out[3]= mat[0]*d;
            return true;
        }
        
        bool setup_Inverse__3(var*& out, var*& mat){
            var d=calc_Det__3(mat);
            if(check_Equal(d,0))return false;
            d=1/d;
            out[0]= mat[3]*d;   out[1]=-mat[1]*d;
            out[2]=-mat[2]*d;   out[3]= mat[0]*d;
            return true;
        }
        
        bool setup_Inverse__4(var*& out, var*& mat){
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
            if(check_Equal(d,0))return false;
            d=1/d;
            out[0]    =(mat[5]*t11-mat[6]*t10+mat[7]*t09)*d;   out[1]    =(mat[2]*t10-mat[1]*t11-mat[3]*t09)*d;   out[2]    =(mat[13]*t05-mat[14]*t04+mat[15]*t03)*d;   out[3]    =(mat[10]*t04-mat[9] *t05-mat[11]*t03)*d;
            out[4]    =(mat[6]*t08-mat[4]*t11-mat[7]*t07)*d;   out[5]    =(mat[0]*t11-mat[2]*t08+mat[3]*t07)*d;   out[6]    =(mat[14]*t02-mat[12]*t05-mat[15]*t01)*d;   out[7]    =(mat[8] *t05-mat[10]*t02+mat[11]*t01)*d;
            out[8]    =(mat[4]*t10-mat[5]*t08+mat[7]*t06)*d;   out[9]    =(mat[1]*t08-mat[0]*t10-mat[3]*t06)*d;   out[10]   =(mat[12]*t04-mat[13]*t02+mat[15]*t00)*d;   out[11]   =(mat[9] *t02-mat[8] *t04-mat[11]*t00)*d;
            out[12]   =(mat[5]*t07-mat[4]*t09-mat[6]*t06)*d;   out[13]   =(mat[0]*t09-mat[1]*t07+mat[2]*t06)*d;   out[14]   =(mat[13]*t01-mat[12]*t03-mat[14]*t00)*d;   out[15]   =(mat[8] *t03-mat[9] *t01+mat[10]*t00)*d;
            return true;
        }

        bool setup_Inverse(var*& out, var*& mat, int n){
            switch (n)
            {
                case 1:
                    return (out[0])&&(out[0]=1/mat[0]);
                break;
                
                case 2:
                    return setup_Inverse__2(out,mat);
                break;
                
                case 3:
                    return setup_Inverse__3(out,mat);
                break;
                
                case 4:
                    return setup_Inverse__4(out,mat);
                break;
            
                default:
                    return setup_Inverse__Transformation(out,mat,n);
                break;
            }
        }

    }
}

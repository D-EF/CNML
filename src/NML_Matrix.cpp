/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-04-07 02:33:19
 * @FilePath: \NML\src\NML_Matrix.cpp
 * @Description: 矩阵 Matrix
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix{
        void setup_Identity(var*& out,int width, int height){
            int u=width,
                v=height,
                i=u*v;
            do{
                --i;
                out[i] = u==v ? 1.0f : 0.0f;
                --u;
                if(!u){
                    --v;
                    u=width;
                }
            }while(i);
        }

        void setup_Resize(var*& out, var*& mat, int low_width, int new_width, int _low_height, int _new_height, int _shift_left, int _shift_top){
            int 
                low_height    =~_low_height?_low_height:low_height,
                new_height    =~_new_height?_new_height:new_height,
                shift_top     =~_shift_top?_shift_top:_shift_left,
                &shift_left   =_shift_left,
                i             =new_width*new_height,
                u_out         =new_width-1,
                u_low         =u_out-shift_left,
                v_low         =new_height-1-shift_top;

            do{
                --i;
                if(!(u_low<0||v_low<0||u_low>=low_width||v_low>=low_height)){
                    out[i]=mat[get_Index(low_width,u_low,v_low)];
                }
                --u_out;
                --u_low;
                if(!u_out){
                    --v_low;
                    u_out=new_width-1;
                    u_low=u_out-shift_left;
                }
            }while(i);
        }

        void setup_TensorProduct(var*& out, var*& mat_left, var*& mat_right, int width_lef, int height_lef, int width_righ, int height_right){

        }

        void setup_Concat(var*& out, var**& mats, int width_mat, int height_mat, int width_g, int height_g){
            int 
                i_g   =width_g*height_g,
                i_m   =width_mat*height_mat,
                i     =i_m*i_g,
                u_g   =width_g-1,
                v_g   =height_g-1,
                u_m   =width_mat-1,
                v_m   =height_mat-1;

            --i_m,--i_g;
            do{
                --i;
                out[i]=mats[i_g][i_m];
                --u_m;
                --i_m;
                if(u_m<0){
                    u_m=width_mat-1;
                    --u_g;
                    if(u_g<0){
                        u_g=width_g-1;
                        --v_m;
                        if(v_m<0){
                            v_m=height_mat-1;
                            --v_g;
                        }
                        i_g=get_Index(width_g,u_g,v_g);
                    }
                    i_m=get_Index(width_mat,u_m,v_m);
                }
            }while(i);
        }

        void transformation__ExchangeRow(var*& mat, int width, int v1, int v2){
            var temp;
            int i=width,
                i1 = get_Index(width,width-1,v1),
                i2 = get_Index(width,width-1,v2);
            do{
                --i;
                temp=mat[i1];
                mat[i1]=mat[i2];
                mat[i2]=temp;
                --i1;
                --i2;
            }while(i);
        }

        void transformation__ExchangeCol(var*& mat, int width,int height, int u1, int u2){
            var temp;
            int i=height,
                i1 = get_Index(width,u1,height-1),
                i2 = get_Index(width,u2,height-1);
            do{
                --i;
                temp=mat[i1];
                mat[i1]=mat[i2];
                mat[i2]=temp;
                i1-=width;
                i2-=width;
            }while(i);
        }

        void transformation__ScaleRow(var*& mat, int width, int v, var k){
            int i=width,
                j=get_Index(width,width-1,v);
            do{
                --i;
                mat[j]*=k;
                --j;
            }while(i);
        }

        void transformation__ScaleCol(var*& mat, int width, int height, int u, var k){
            int i=width,
                j=get_Index(width,u,height-1);
            do{
                --i;
                mat[j]*=k;
                j-=width;
            }while(i);
        }

        void exchange_ToUnZero(var** mat, int length, int index, int v, int step_length){

        }

        void exchange_ToUnZero(var**& mat, int length, int index, int v, int step_length, int length_g, int _index_m){

        }

        void multiplication(var*& out, int width, int height, var*& mat_left, var*& mat_right){

        }

        bool check_Orthogonal(var*& mat,int _n){

        }

        void transpose(var*& mat, int width, int height){

        }

        var calc_Det__Transformation(var*& mat,int n){

        }

        void setup_Inverse__Transformation(var*& out, var*& mat, int n);
    }
}

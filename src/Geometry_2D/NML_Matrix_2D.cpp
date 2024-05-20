/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-05-07 09:40:52
 * @FilePath: \CNML\src\Geometry_2D\NML_Matrix_2D.cpp
 * @Description: 2D 矩阵计算
 */

#include "./NML_Matrix_2D.hpp"

namespace NML{
    namespace Matrix_2D{
        //默认使用 3*3 左乘向量 (vector * matrix)
        M2D_Type _using_m2d_type=M2D__3X3_L;
        // 数据类型的数据对应宽高
            Idx_VM m2d_w=3, m2d_h=3;
        // 数据类型的数据对应下标
            Idx_VM 
                mxx=0,   mxy=1,   mxz=2,
                myx=3,   myy=4,   myz=5,
                mzx=6,   mzy=7,   mzz=8;
            Idx_VM &mx_null=mxz, &my_null=myz, &tx=mzx, &ty=mzy, &mi_full=mzz;
        //
        

        void set_NMLConfig__using_m2d_type(M2D_Type type){
            if(_using_m2d_type==type)return;
            _using_m2d_type=type;
            switch (_using_m2d_type){
                case M2D__2X3:
                    m2d_w=2, m2d_h=3;
                    mxx=0,   mxy=1,    mx_null=0,
                    myx=2,   myy=3,    my_null=0,
                    tx =4,   ty =5,    mi_full=0;
                break;

                case M2D__3X2:
                    m2d_w=3, m2d_h=2;
                    mxx=0,        myx=1,        tx=2,
                    mxy=3,        myy=4,        ty=5,
                    mx_null =0,   my_null =0,   mi_full=0;
                break;

                case M2D__3X3_L:
                    m2d_w=3, m2d_h=3;
                    mxx=0,   mxy=1,   mx_null=2,
                    myx=3,   myy=4,   my_null=5,
                    tx =6,   ty =7,   mi_full=8;
                break;

                case M2D__3X3_R:
                    m2d_w=3,     m2d_h=3;
                    mxx=0,       myx=1,       tx=2,
                    mxy=3,       myy=4,       ty=5,
                    mx_null=6,   my_null=7,   mi_full=8;
                break;
            }
        }

        void printf_M2dCss(var*& mat){
            var v_mxz=0,
                v_myz=0,
                v_mzz=1;
                
            if(!mx_null){
                v_mxz=mat[mxz];
                v_myz=mat[myz];
                v_mzz=mat[mzz];
            }
            printf("matrix(%f, %f, %f, %f, %f, %f)\n",
                mat[mxx],   mat[mxy],
                mat[myx],   mat[myy],
                mat[tx],    mat[ty]
            );
        }

        var*& act_Matrix2D__Rotate__Vector (const _M2d_Act_Fnc& act, var*& out, var*& unit_vec__org, var*& unit_vec__to){
            var c=unit_vec__org[0]*unit_vec__to[0]+unit_vec__org[1]*unit_vec__to[1],
                s=unit_vec__org[1]*unit_vec__to[0]-unit_vec__org[0]*unit_vec__to[1];
            return act(out,
                c,   s,
               -s,   c,
                0,   0
            );
        }

        var*& act_Matrix2D__Reflect__Collinear(const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y){
            var m=normal_x*normal_x+normal_y*normal_y;
            if(!(check_Equal(1, m)||check_Zero(m))){
                m=1/sqrt(m);
                return act_Matrix2D__Reflect(act, out, normal_x*m, normal_y*m);
            }
            return act_Matrix2D__Reflect(act, out, normal_x, normal_y);
        }

        var*& act_Matrix2D__Shear__Collinear(const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k){
            var m=axis_x*axis_x+axis_y*axis_y;
            if(!(check_Equal(1, m)||check_Zero(m))){
                m=1/sqrt(m);
                return act_Matrix2D__Shear(act, out, axis_x*m, axis_y*m, k);
            }
            return act_Matrix2D__Shear(act, out, axis_x, axis_y, k);
        }


        var*& setup_Matrix2D(var*& out, var a, var b, var c, var d, var e, var f){
            out[mx_null]=0;   out[my_null]=0;   out[mi_full]=1;

            out[mxx]=a;       out[mxy]=b;
            out[myx]=c;       out[myy]=d;
            out[tx] =e;       out[ty] =f;
            return out;
        }

        var*& transform_Matrix2D(var*& mat, var app_mxx, var app_mxy, var app_myx, var app_myy, var app_tx, var app_ty){  
            return setup_Matrix2D(mat,
                mat[mxx]*app_mxx + mat[mxy]*app_myx,            mat[mxx]*app_mxy + mat[mxy]*app_myy,
                mat[myx]*app_mxx + mat[myy]*app_myx,            mat[myx]*app_mxy + mat[myy]*app_myy,
                mat[tx] *app_mxx + mat[ty] *app_myx + app_tx,   mat[tx] *app_mxy + mat[ty] *app_myy + app_ty
            );
        }

        var*& act_Matrix2D__Translate(const _M2d_Act_Fnc& act, var*& out, var translate_x, var translate_y){
            return act(out,
                1,             0,
                0,             1,
                translate_x,   translate_y
            );
        }

        var*& act_Matrix2D__Scale(const _M2d_Act_Fnc& act, var*& out, var scale_x, var scale_y){
            return act(out,
                scale_x,   0,
                0,         scale_y,
                0,         0
            );
        }

        var*& act_Matrix2D__Rotate(const _M2d_Act_Fnc& act, var*& out, var theta){
                var c=cos(theta), s=sin(theta);
                return act(out,
                     c,    s,
                    -s,    c,
                     0,    0
                );
        }

        var*& act_Matrix2D__Reflect(const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y){
            return act(out,
                1-2*normal_x*normal_x ,   -2*normal_x*normal_y,
                -2*normal_x*normal_y  ,   1-2*normal_y*normal_y,
                0,                        0
            );
        }

        var*& act_Matrix2D__Shear(const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k){
            return act(out,
                1,          k*axis_x,
                k*axis_y,   1,
                0,          0
            );
        }

    }
}
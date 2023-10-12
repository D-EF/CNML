/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-08 16:40:23
 * @FilePath: \cnml\src\NML_Matrix_3D.cpp
 * @Description: 3D 变换矩阵
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Matrix_3D.hpp"

namespace NML{
    namespace Matrix_3D{
        //默认使用 3*3 左乘向量 (vector * matrix)
        M3D_Type _using_m3d_type=M3D__4X4_L;
        // 数据类型的数据对应宽高
            Idx_VM m3d_w=4, m3d_h=4, m3d_length=16;
        // 数据类型的数据对应下标
            Idx_VM 
                mxx=0,    mxy=1,    mxz=2,    mxw=3,
                myx=4,    myy=5,    myz=6,    myw=7,
                mzx=8,    mzy=9,    mzz=10,   mzw=11,
                mwx=12,   mwy=13,   mwz=14,   mww=15;
            Idx_VM &tx=mwx, &ty=mwy, &tz=mwz;

        

        void set_NMLConfig__using_m3d_type(M3D_Type type){
            if(_using_m3d_type==type)return;
            _using_m3d_type=type;
            switch (_using_m3d_type){
                case M3D__3X4:
                    m3d_w=3, m3d_h=4, m3d_length=12;
                    mxx=0,   mxy=1,    mxz=2,    mxw=0,
                    myx=3,   myy=4,    myz=5,    myw=0,
                    mzx=6,   mzy=7,    mzz=8,    mzw=0,
                    tx =9,   ty =10,   tz =11,   mww=0;
                break;

                case M3D__4X3:
                    m3d_w=4, m3d_h=3, m3d_length=12;
                    mxx=0,     myx=1,    mzx=2,    tx=3,
                    mxy=4,     myy=5,    mzy=6,    ty=7,
                    mxz=8,     myz=9,    mzz=10,   tz=11,
                    mxw =0,    myw =0,   mzw =0,   mww=0;
                break;

                case M3D__4X4_L:
                    m3d_w=4, m3d_h=4, m3d_length=16;
                    mxx=0,    mxy=1,    mxz=2,    mxw=3,
                    myx=4,    myy=5,    myz=6,    myw=7,
                    mzx=8,    mzy=9,    mzz=10,   mzw=11,
                    tx =12,   ty =13,   tz =14,   mww=15;
                break;

                case M3D__4X4_R:
                    m3d_w=4, m3d_h=4, m3d_length=16;
                    mxx=0,     myx=1,     mzx=2,     tx=3,
                    mxy=4,     myy=5,     mzy=6,     ty=7,
                    mxz=8,     myz=9,     mzz=10,    tz=11,
                    mxw =12,   myw =13,   mzw =14,   mww=15;
                break;
            }
        }
        
        void printf_M3dCss(var*& mat){
            var v_mxw=0,
                v_myw=0,
                v_mzw=0,
                v_mww=1;
                
            if(!mxw){
                v_mxw=mat[mxw];
                v_myw=mat[myw];
                v_mzw=mat[mzw];
                v_mww=mat[mww];
            }
            printf("transform:matrix3d(%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);\n",
                mat[mxx],   mat[mxy],   mat[mxz],   v_mxw,
                mat[myx],   mat[myy],   mat[myz],   v_myw,
                mat[mzx],   mat[mzy],   mat[mzz],   v_mzw,
                mat[tx],    mat[ty],    mat[tz],    v_mww
            );
        }
    
        var*& transform_Matrix3D__Easy(var*& mat, 
            var app_mxx,   var app_mxy,   var app_mxz,
            var app_myx,   var app_myy,   var app_myz,
            var app_mzx,   var app_mzy,   var app_mzz,
            var app_mwx,   var app_mwy,   var app_mwz,
            var app_mxw,   var app_myw,   var app_mzw,   var app_mww
        ){
            var mat_mxw=0,
                mat_myw=0,  
                mat_mzw=0,
                mat_mww=1;
            if(mxw){
                mat_mxw=mat[mxw];
                mat_myw=mat[myw];
                mat_mzw=mat[mzw];
                mat_mww=mat[mww];
            }
            return setup_Matrix3D__Easy(mat,
                mat[mxx]*app_mxx + mat[mxy]*app_myx + mat[mxz]*app_mzx + mat_mxw*app_mwx,   mat[mxx]*app_mxy + mat[mxy]*app_myy + mat[mxz]*app_mzy + mat_mxw*app_mwy,   mat[mxx]*app_mxz + mat[mxy]*app_myz + mat[mxz]*app_mzz + mat_mxw*app_mwz,
                mat[myx]*app_mxx + mat[myy]*app_myx + mat[myz]*app_mzx + mat_myw*app_mwx,   mat[myx]*app_mxy + mat[myy]*app_myy + mat[myz]*app_mzy + mat_myw*app_mwy,   mat[myx]*app_mxz + mat[myy]*app_myz + mat[myz]*app_mzz + mat_myw*app_mwz,
                mat[mzx]*app_mxx + mat[mzy]*app_myx + mat[mzz]*app_mzx + mat_mzw*app_mwx,   mat[mzx]*app_mxy + mat[mzy]*app_myy + mat[mzz]*app_mzy + mat_mzw*app_mwy,   mat[mzx]*app_mxz + mat[mzy]*app_myz + mat[mzz]*app_mzz + mat_mzw*app_mwz,
                mat[mwx]*app_mxx + mat[mwy]*app_myx + mat[mwz]*app_mzx + mat_mww*app_mwx,   mat[mwx]*app_mxy + mat[mwy]*app_myy + mat[mwz]*app_mzy + mat_mww*app_mwy,   mat[mwx]*app_mxz + mat[mwy]*app_myz + mat[mwz]*app_mzz + mat_mww*app_mwz,

                mat[mxx]*app_mxw + mat[mxy]*app_myw + mat[mxz]*app_mzw + mat_mxw*app_mww,   mat[myx]*app_mxw + mat[myy]*app_myw + mat[myz]*app_mzw + mat_myw*app_mww,   mat[mzx]*app_mxw + mat[mzy]*app_myw + mat[mzz]*app_mzw + mat_mzw*app_mww,
                mat[mwx]*app_mxw + mat[mwy]*app_myw + mat[mwz]*app_mzw + mat_mww*app_mww

                // mat[mxx]*app_mxx + mat[myx]*app_mxy + mat[mzx]*app_mxz + mat[mwx]*app_mxw,   mat[mxy]*app_mxx + mat[myy]*app_mxy + mat[mzy]*app_mxz + mat[mwy]*app_mxw,   mat[mxz]*app_mxx + mat[myz]*app_mxy + mat[mzz]*app_mxz + mat[mwz]*app_mxw,   
                // mat[mxx]*app_myx + mat[myx]*app_myy + mat[mzx]*app_myz + mat[mwx]*app_myw,   mat[mxy]*app_myx + mat[myy]*app_myy + mat[mzy]*app_myz + mat[mwy]*app_myw,   mat[mxz]*app_myx + mat[myz]*app_myy + mat[mzz]*app_myz + mat[mwz]*app_myw,   
                // mat[mxx]*app_mzx + mat[myx]*app_mzy + mat[mzx]*app_mzz + mat[mwx]*app_mzw,   mat[mxy]*app_mzx + mat[myy]*app_mzy + mat[mzy]*app_mzz + mat[mwy]*app_mzw,   mat[mxz]*app_mzx + mat[myz]*app_mzy + mat[mzz]*app_mzz + mat[mwz]*app_mzw,   
                // mat[mxx]*app_mwx + mat[myx]*app_mwy + mat[mzx]*app_mwz + mat[mwx]*app_mww,   mat[mxy]*app_mwx + mat[myy]*app_mwy + mat[mzy]*app_mwz + mat[mwy]*app_mww,   mat[mxz]*app_mwx + mat[myz]*app_mwy + mat[mzz]*app_mwz + mat[mwz]*app_mww,   
                
                // mat_mxw*app_mxx + mat_myw*app_mxy + mat_mzw*app_mxz + mat_mww*app_mxw,
                // mat_mxw*app_myx + mat_myw*app_myy + mat_mzw*app_myz + mat_mww*app_myw,
                // mat_mxw*app_mzx + mat_myw*app_mzy + mat_mzw*app_mzz + mat_mww*app_mzw,
                // mat_mxw*app_mwx + mat_myw*app_mwy + mat_mzw*app_mwz + mat_mww*app_mww
            );
        }

        
        var*& act_Matrix3D__Reflect__Collinear (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            var m=normal_x*normal_x+normal_y*normal_y+normal_z*normal_z;
            if(!(check_Equal(1, m)||check_Zero(m))){
                m=1/sqrt(m);
                return act_Matrix3D__Reflect(act, out, normal_x*m, normal_y*m, normal_z*m);
            }
            return act_Matrix3D__Reflect(act, out, normal_x, normal_y, normal_z);
        }

        var*& act_Matrix3D__Shear (const _M3d_Act_Fnc__Easy& act, var*& out, Plane_3D plane, var k1, var k2){
            switch (plane){
                case X:
                    return act(out,
                        1, k1, k2,
                        0, 1, 0,
                        0, 0, 1,
                        0, 0, 0,
                        0, 0, 0, 1
                    );
                break;

                case Y:
                    return act(out,
                        1, 0, 0,
                        k2, 1, k1,
                        0, 0, 1,
                        0, 0, 0,
                        0, 0, 0, 1
                    );
                break;

                case Z:
                    return act(out,
                        1, 0, 0,
                        0, 1, 0,
                        k1, k2, 1,
                        0, 0, 0,
                        0, 0, 0, 1
                    );
                break;
            
                default:
                    return out;
                break;
            }
        }

        var*& act_Matrix3D__Rotate (const _M3d_Act_Fnc__Easy& act, var*& out, var theta, Axis axis){
            var c=cos(theta), s=sin(theta);
            switch (axis)
            {
                case X:
                    return act(out,
                        1,   0,    0,
                        0,   c,    s,
                        0,   -s,   c,
                        0,   0,    0,
                        0, 0, 0, 1
                    );
                break;
                
                case Y:
                    return act(out,
                        c,   0,   -s,
                        0,   1,   0,
                        s,   0,   c,
                        0,   0,   0,
                        0, 0, 0, 1
                    );
                break;
                
                case Z:
                    return act(out,
                        c,    s,   0,
                        -s,   c,   0,
                        0,    0,   1,
                        0,    0,   0,
                        0, 0, 0, 1
                    );
                break;
                default:
                    return out;
                break;
            }
        }
        
        var*& setup_Matrix3D__Easy(var*& out, 
            var value_mxx,   var value_mxy,   var value_mxz,
            var value_myx,   var value_myy,   var value_myz,
            var value_mzx,   var value_mzy,   var value_mzz,
            var value_tx,    var value_ty,    var value_tz,
            var value_mxw,   var value_myw,   var value_mzw,   var value_mww
        ){
            out[mxw]=value_mxw;        out[myw]=value_myw;        out[mzw]=value_mzw;       out[mww]=value_mww;
            
            out[mxx]= value_mxx;   out[mxy]= value_mxy;   out[mxz]=value_mxz;
            out[myx]= value_myx;   out[myy]= value_myy;   out[myz]=value_myz;
            out[mzx]= value_mzx;   out[mzy]= value_mzy;   out[mzz]=value_mzz;
            out[tx] = value_tx ;   out[ty] = value_ty ;   out[tz] =value_tz ;
            return out;
        }
        
        var*& act_Matrix3D__Translate(const _M3d_Act_Fnc__Easy& act, var*& out, var translate_x, var translate_y, var translate_z){
            return act(out,
                1,             0,             0,
                0,             1,             0,
                0,             0,             1,
                translate_x,   translate_y,   translate_z,
                0, 0, 0, 1
            );
        }

        var*& act_Matrix3D__Scale (const _M3d_Act_Fnc__Easy& act, var*& out, var scale_x, var scale_y, var scale_z){
            return act(out, 
                scale_x,   0,         0,
                0,         scale_y,   0,
                0,         0,         scale_z,
                0,         0,         0,
                0, 0, 0, 1
            );
        }

        var*& act_Matrix3D__Reflect (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            var i2xy=-2*normal_x*normal_y,
                i2xz=-2*normal_x*normal_z,
                i2yz=-2*normal_y*normal_z;
            return act(out,
                1-2*normal_x*normal_x,   i2xy,                    i2xz,
                i2xy,                    1-2*normal_y*normal_y,   i2yz,
                i2xz,                    i2yz,                    1-2*normal_z*normal_z,
                0,                       0,                       0,
                0, 0, 0, 1
            );
        }

        var*& act_Matrix3D__Rotate__Quaternion       (const _M3d_Act_Fnc__Easy& act, var*& out, var x, var y, var z, var w){
            var xx=x*x,
                yy=y*y,
                zz=z*z,
                xy=x*y,
                xz=x*z,
                yz=y*z,
                wx=w*x,
                wy=w*y,
                wz=w*z;
            return act(out,
                1-2*(yy+zz),   2*(xy+wz),     2*(xz-wy),
                2*(xy-wz),     1-2*(xx+zz),   2*(yz+wx),
                2*(xz+wy),     2*(yz-wx),     1-2*(xx+yy),
                0,             0,             0,
                0, 0, 0, 1
            );
        }

        var*& act_Matrix3D__Rotate__EulerAngles (const _M3d_Act_Fnc__Easy& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order){
            Axis axis= static_cast<Axis>(order &0b11);
            act_Matrix3D__Rotate(act, out, thetas_3, axis);

            axis= static_cast<Axis>(order>>2 &0b11);
            transform_Matrix3D__Rotate(out, thetas_2, axis);
            
            axis= static_cast<Axis>(order>>4 &0b11);
            return  transform_Matrix3D__Rotate(out, thetas_1, axis);
        }

        var*& act_Matrix3D__OrthographicProjection (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            return act(out,
                1-normal_x*normal_x,   -normal_x*normal_y,    -normal_x*normal_z,
                -normal_x*normal_y,    1-normal_y*normal_y,   -normal_y*normal_z,
                -normal_x*normal_z,    -normal_y*normal_z,    1-normal_z*normal_z,
                0,                     0,                     0,
                0, 0, 0, 1
            );
        }

    
    }
}
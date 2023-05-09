#ifndef __NML_MATRIX_3D__
#define __NML_MATRIX_3D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_3D{

        /** 可选的3D矩阵的存储格式 */
        enum M3D_Type{
            M3D__4X4_L,   // 矩阵左边乘向量 vec * met
            M3D__4X4_R,   // 矩阵右边乘向量 met * vec
            M3D__3X4,     // 矩阵左边乘向量 vec * met 省略右侧列
            M3D__4X3      // 矩阵右边乘向量 met * vec 省略下侧行
        };

        //默认使用 3*3 左乘向量 (vector * matrix)
        M3D_Type _using_m3d_type=M3D__4X4_L;

        // 数据类型的数据对应宽高
            int w=4,h=4;
        // 数据类型的数据对应下标
            int mxx=0,    mxy=1,    mxz=2,    mx_null=3,
                myx=4,    myy=5,    myz=6,    my_null=7,
                mzx=8,    mzy=9,    mzz=10,   mz_null=11,
                tx =12,   ty =13,   tz =14,   mi_full=15;
        //

        /**
         * @brief 切换要使用的数据格式
         * @param type 使用的矩阵格式
         */
        void set_NMLConfig__using_m3d_type(M3D_Type type);

        /**
         * @brief 设置 3d 矩阵数据
         * @param out       操作对象
         * @param value_mxx 3d线性变换矩阵 参数 mxx
         * @param value_mxy 3d线性变换矩阵 参数 mxy
         * @param value_mxz 3d线性变换矩阵 参数 mxz
         * @param value_myx 3d线性变换矩阵 参数 myx
         * @param value_myy 3d线性变换矩阵 参数 myy
         * @param value_myz 3d线性变换矩阵 参数 myz
         * @param value_mzx 3d线性变换矩阵 参数 mzx
         * @param value_mzy 3d线性变换矩阵 参数 mzy
         * @param value_mzz 3d线性变换矩阵 参数 mzz
         * @param value_tx  x 方向平移量
         * @param value_ty  y 方向平移量
         * @param value_tz  z 方向平移量
         * @return 写入 out 并返回
         */
        __NML__INLINE_M3D_ACTION_FUNCTION var*& setup_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        );

        /**
         * @brief 3d矩阵追加变换
         * @param out     操作对象
         * @param app_mxx 追加变换的 3d 线性变换矩阵 参数 mxx
         * @param app_mxy 追加变换的 3d 线性变换矩阵 参数 mxy
         * @param app_mxz 追加变换的 3d 线性变换矩阵 参数 mxz
         * @param app_myx 追加变换的 3d 线性变换矩阵 参数 myx
         * @param app_myy 追加变换的 3d 线性变换矩阵 参数 myy
         * @param app_myz 追加变换的 3d 线性变换矩阵 参数 myz
         * @param app_mzx 追加变换的 3d 线性变换矩阵 参数 mzx
         * @param app_mzy 追加变换的 3d 线性变换矩阵 参数 mzy
         * @param app_mzz 追加变换的 3d 线性变换矩阵 参数 mzz
         * @param app_tx  追加变换的 x 方向平移量
         * @param app_ty  追加变换的 y 方向平移量
         * @param app_tz  追加变换的 z 方向平移量
         * @return 修改 out 并返回
         */
        __NML__INLINE_M3D_ACTION_FUNCTION var*& transform_Matrix3D(var*& out, 
            var app_mxx, var app_mxy, var app_mxz,
            var app_myx, var app_myy, var app_myz,
            var app_mzx, var app_mzy, var app_mzz,
            var app_tx , var app_ty , var app_tz
        );

        /** 用于选择使用 setup 或 transform 的函数指针*/
        typedef var*& (*_M3d_Act_Fnc)(var*&,
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        );

        __NML__INLINE_M3D_ACTION_FUNCTION   var*& act_Translate             (const _M3d_Act_Fnc& act, var*& out, var translate_x, var translate_y=0, var translate_z=0);
        __NML__INLINE_M3D_ACTION_FUNCTION   var*& act_Scale                 (const _M3d_Act_Fnc& act, var*& out, var scale_x, var scale_y,var scale_z);
        __NML__INLINE_M3D_ACTION_FUNCTION   var*& act_Horizontal            (const _M3d_Act_Fnc& act, var*& out, var normal_x, var normal_y, var normal_z);
        __NML__INLINE_M3D_ACTION_FUNCTION   var*& act_Shear                 (const _M3d_Act_Fnc& act, var*& out, Axis axis, var k);
        /** never inline */                 var*& act_Rotate                (const _M3d_Act_Fnc& act, var*& out, var theta, Axis axis=X);
        __NML__INLINE_M3D_ACTION_FUNCTION   var*& act_Rotate__EulerAngles   (const _M3d_Act_Fnc& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order);

        inline var*& act_Rotate__EulerAngles   (const _M3d_Act_Fnc& act, var*& out, var*& thetas, Rotation_Order order=XYZ)   {return act_Rotate__EulerAngles(act,out,thetas[0],thetas[1],thetas[2],order);}


        // open * setup * open

            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_x   x方向平移量
             * @param translate_y   y方向平移量
             * @param translate_z   z方向平移量
             * @return 修改 out 并输出
             */
            inline var*& setup_Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Translate             (setup_Matrix3D,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& setup_Translate             (var*& out, var*& translate_vector)                                               {return act_Translate             (setup_Matrix3D,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Scale                 (setup_Matrix3D,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Scale                 (var*& out, var scale_value)                                                      {return act_Scale                 (setup_Matrix3D,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& setup_Horizontal            (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Horizontal            (setup_Matrix3D,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 设置 切变矩阵
             * @param out           输出对象
             * @param axis          切变方向轴
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& setup_Shear                 (var*& out, Axis axis, var k)                                                     {return act_Shear                 (setup_Matrix3D,out, axis, k);}
            /**
             * @brief 设置 旋转矩阵  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Rotate                (setup_Matrix3D,out, theta, axis);}
            /**
             * @brief 设置 旋转矩阵  (使用欧拉角)
             * @param out           输出对象      
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Rotate__EulerAngles   (setup_Matrix3D,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 设置 旋转矩阵 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Rotate__EulerAngles   (setup_Matrix3D,out, thetas[0],thetas[1],thetas[2], order);}
        
        // end  * setup * end  


        // open * transform * open

            /**
             * @brief 矩阵 进行 平移 变换
             * @param out           输出对象
             * @param translate_x   x方向平移量
             * @param translate_y   y方向平移量
             * @param translate_z   z方向平移量
             * @return 修改 out 并输出
             */
            inline var*& transform_Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Translate             (transform_Matrix3D,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& transform_Translate             (var*& out, var*& translate_vector)                                               {return act_Translate             (transform_Matrix3D,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Scale                 (transform_Matrix3D,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Scale                 (var*& out, var scale_value)                                                      {return act_Scale                 (transform_Matrix3D,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 矩阵 进行 镜像 变换
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& transform_Horizontal            (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Horizontal            (transform_Matrix3D,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 矩阵 进行 切变 变换
             * @param out           输出对象
             * @param axis          切变方向
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& transform_Shear                 (var*& out, Axis axis, var k)                                                     {return act_Shear                 (transform_Matrix3D,out, axis, k);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Rotate                (transform_Matrix3D,out, theta, axis);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用欧拉角)
             * @param out           输出对象
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Rotate__EulerAngles   (transform_Matrix3D,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 矩阵 进行 旋转 变换 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Rotate__EulerAngles   (transform_Matrix3D,out, thetas[0],thetas[1],thetas[2], order);}
        
        // end  * transform * end 

    }
}



namespace NML{
    namespace Matrix_3D{

        void set_NMLConfig__using_m3d_type(M3D_Type type){
            _using_m3d_type=type;
            switch (_using_m3d_type){
                case M3D__3X4:
                    w=3,h=4;
                    mxx=0,   mxy=1,    mxz=2,    mx_null=0,
                    myx=3,   myy=4,    myz=5,    my_null=0,
                    mzx=6,   mzy=7,    mzz=8,    mz_null=0,
                    tx =9,   ty =10,   tz =11,   mi_full=0;
                break;

                case M3D__4X3:
                    w=4,h=3;
                    mxx=0,        myx=1,        mzx=2,        tx=3,
                    mxy=4,        myy=5,        mzy=6,        ty=7,
                    mxz=8,        myz=9,        mzz=10,       tz=11,
                    mx_null =0,   my_null =0,   mz_null =0,   mi_full=0;
                break;

                case M3D__4X4_L:
                    w=4,h=3;
                    mxx=0,    mxy=1,    mxz=2,    mx_null=3,
                    myx=4,    myy=5,    myz=6,    my_null=7,
                    mzx=8,    mzy=9,    mzz=10,   mz_null=11,
                    tx =12,   ty =13,   tz =14,   mi_full=15;
                break;

                case M3D__4X4_R:
                    w=4,h=3;
                    mxx=0,         myx=1,         mzx=2,         tx=3,
                    mxy=4,         myy=5,         mzy=6,         ty=7,
                    mxz=8,         myz=9,         mzz=10,        tz=11,
                    mx_null =12,   my_null =13,   mz_null =14,   mi_full=15;
                break;
            }
        }


        __NML__INLINE_M3D_ACTION_FUNCTION var*& setup_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        ){
            out[mx_null]=0;        out[my_null]=0;        out[mz_null]=0;       out[mi_full]=1;
            
            out[mxx]= value_mxx;   out[mxy]= value_mxy;   out[mxz]=value_mxz;
            out[myx]= value_myx;   out[myy]= value_myy;   out[myz]=value_myz;
            out[mzx]= value_mzx;   out[mzy]= value_mzy;   out[mzz]=value_mzz;
            out[tx] = value_tx ;   out[ty] = value_ty ;   out[tz] =value_tz ;
            return out;
        }


        __NML__INLINE_M3D_ACTION_FUNCTION var*& transform_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        ){
            return setup_Matrix3D(out,
                out[mxx]*value_mxx + out[mxy]*value_myx + out[mxz]+value_mzx,       out[mxx]*value_mxy + out[mxy]*value_myy + out[mxz]*value_mzy,       out[mxx]*value_mxz + out[mxy]*value_myz + out[mxz]*value_mzz,
                out[myx]*value_mxx + out[myy]*value_myx + out[myz]+value_mzx,       out[myx]*value_mxy + out[myy]*value_myy + out[myz]*value_mzy,       out[myx]*value_mxz + out[myy]*value_myz + out[myz]*value_mzz,
                out[mzx]*value_mxx + out[mzy]*value_myx + out[mzz]+value_mzx,       out[mzx]*value_mxy + out[mzy]*value_myy + out[mzz]*value_mzy,       out[mzx]*value_mxz + out[mzy]*value_myz + out[mzz]*value_mzz,
                out[tx]*value_mxx+out[ty]*value_myx+out[tz]+value_mzx + value_tx,   out[tx]*value_mxy+out[ty]*value_myy+out[tz]+value_mzy + value_tx,   out[tx]*value_mxz+out[ty]*value_myz+out[tz]+value_mzz + value_tx
            );
        }
        
        

        __NML__INLINE_M3D_ACTION_FUNCTION var*& act_Translate(var*& out,_M3d_Act_Fnc act, var translate_x, var translate_y, var translate_z){
            return act(out,
                1,             0,             0,
                0,             1,             0,
                0,             0,             1,
                translate_x,   translate_y,   translate_z
            );
        }

        __NML__INLINE_M3D_ACTION_FUNCTION var*& act_Scale (const _M3d_Act_Fnc& act, var*& out, var scale_x, var scale_y,var scale_z){
            return act(out, 
                scale_x,   0,         0,
                0,         scale_y,   0,
                0,         0,         scale_z,
                0,         0,         0
            );
        }

        __NML__INLINE_M3D_ACTION_FUNCTION var*& act_Horizontal (const _M3d_Act_Fnc& act, var*& out, var normal_x, var normal_y, var normal_z){
            var i2xy=-2*normal_x*normal_y,
                i2xz=-2*normal_x*normal_z,
                i2yz=-2*normal_y*normal_z;
            return act(out,
                1-2*normal_x*normal_x,   i2xy,                    i2xz,
                i2xy,                    1-2*normal_y*normal_y,   i2yz,
                i2xz,                    i2yz,                    1-2*normal_z*normal_z,
                0,                       0,                       0
            );
        }

        __NML__INLINE_M3D_ACTION_FUNCTION var*& act_Shear (const _M3d_Act_Fnc& act, var*& out, Axis axis, var k){
            switch (axis){
                case X:
                    return act(out,
                        1,k,k,
                        0,1,0,
                        0,0,1,
                        0,0,0
                    );
                break;

                case Y:
                    return act(out,
                        1,0,0,
                        k,1,k,
                        0,0,1,
                        0,0,0
                    );
                break;

                case Z:
                    return act(out,
                        1,0,0,
                        0,1,0,
                        k,k,1,
                        0,0,0
                    );
                break;
            
                default:
                    return out;
                break;
            }
        }

        var*& act_Rotate (const _M3d_Act_Fnc& act, var*& out, var theta, Axis axis){
            var c=cos(theta), s=sin(theta);
            switch (axis)
            {
                case X:
                    return act(out,
                        1,   0,    0,
                        0,   c,    s,
                        0,   -s,   c,
                        0,   0,    0
                    );
                break;
                
                case Y:
                    return act(out,
                        c,   0,   -s,
                        0,   1,   0,
                        s,   0,   c,
                        0,   0,   0
                    );
                break;
                
                case Z:
                    return act(out,
                        c,    s,   0,
                        -s,   c,   0,
                        0,    0,   1,
                        0,    0,   0
                    );
                break;
                default:
                    return out;
                break;
            }
        }

        __NML__INLINE_M3D_ACTION_FUNCTION var*& act_Rotate__EulerAngles (const _M3d_Act_Fnc& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order){
            Axis axis= static_cast<Axis>(order>>4 &0b11);
            act_Rotate(act,out,thetas_1,axis);

            axis= static_cast<Axis>(order>>2 &0b11);
            transform_Rotate(out,thetas_2,axis);
            
            axis= static_cast<Axis>(order &0b11);
            return  transform_Rotate(out,thetas_3,axis);
        }

    }
}

#endif
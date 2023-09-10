/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-09 15:45:34
 * @FilePath: \cnml\src\NML_Matrix.hpp
 * @Description: 3D 变换矩阵
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

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
        extern M3D_Type _using_m3d_type;

        // 数据类型的数据对应宽高
            extern Idx_VM m3d_w,m3d_h,m3d_length;
        // 数据类型的数据对应下标
            extern Idx_VM 
                mxx,   mxy,   mxz,   mxw,
                myx,   myy,   myz,   myw,
                mzx,   mzy,   mzz,   mzw,
                mwx,   mwy,   mwz,   mww;
            extern Idx_VM &tx, &ty, &tz;
        //

        /**
         * @brief 切换要使用的数据格式
         * @param type 使用的矩阵格式
         */
        void set_NMLConfig__using_m3d_type(M3D_Type type);

        /**
         * @brief 打印输出3d矩阵变换的css样式
         * @param mat 矩阵数据
         */
        void printf_M3dCss(var*& mat);


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
         * @param value_mxw  3d线性变换矩阵 参数 mxw 
         * @param value_myw  3d线性变换矩阵 参数 myw 
         * @param value_mzw  3d线性变换矩阵 参数 mzw 
         * @param value_mww  3d线性变换矩阵 参数 mww 
         * @return 写入 out 并返回
         */
        var*& setup_Matrix3D__Easy(var*& out, 
            var value_mxx,     var value_mxy,     var value_mxz,
            var value_myx,     var value_myy,     var value_myz,
            var value_mzx,     var value_mzy,     var value_mzz,
            var value_tx=0,    var value_ty=0,    var value_tz=0,
            var value_mxw=0,   var value_myw=0,   var value_mzw=0,   var value_mww=1
        );

        /**
         * @brief 3d矩阵追加变换
         * @param mat     操作对象
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
         * @param app_mxw  3d线性变换矩阵 参数 mxw 
         * @param app_myw  3d线性变换矩阵 参数 myw 
         * @param app_mzw  3d线性变换矩阵 参数 mzw 
         * @param app_mww  3d线性变换矩阵 参数 mww 
         * @return 修改 mat 并返回
         */
        var*& transform_Matrix3D__Easy(var*& mat, 
            var app_mxx,     var app_mxy,     var app_mxz,
            var app_myx,     var app_myy,     var app_myz,
            var app_mzx,     var app_mzy,     var app_mzz,
            var app_tx=0,    var app_ty=0,    var app_tz=0,
            var app_mxw=0,   var app_myw=0,   var app_mzw=0,   var app_mww=1
        );


        /** 用于选择使用 setup 或 transform 的函数指针*/
        typedef var*& (*_M3d_Act_Fnc__Easy)(var*&,
            var value_mxx,   var value_mxy,   var value_mxz,
            var value_myx,   var value_myy,   var value_myz,
            var value_mzx,   var value_mzy,   var value_mzz,
            var value_tx,    var value_ty,    var value_tz,
            var value_mxw,   var value_myw,   var value_mzw,   var value_mww
        );
        
        /** 使用向量的函数*/
        typedef var*& (*_M3d_Act_Fnc__Use_Vec)(var*& out, var vec_x, var vec_y, var vec_z);

        var*& act_Matrix3D__Translate                (const _M3d_Act_Fnc__Easy& act, var*& out, var translate_x, var translate_y=0, var translate_z=0);
        var*& act_Matrix3D__Scale                    (const _M3d_Act_Fnc__Easy& act, var*& out, var scale_x, var scale_y, var scale_z);
        var*& act_Matrix3D__Reflect                  (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);
        var*& act_Matrix3D__Reflect__Collinear       (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);
        var*& act_Matrix3D__Shear                    (const _M3d_Act_Fnc__Easy& act, var*& out, Plane_3D plane, var k1, var k2);
        var*& act_Matrix3D__Rotate                   (const _M3d_Act_Fnc__Easy& act, var*& out, var theta, Axis axis=X);
        var*& act_Matrix3D__Rotate__Quaternion       (const _M3d_Act_Fnc__Easy& act, var*& out, var x, var y, var z, var w);
        var*& act_Matrix3D__Rotate__EulerAngles      (const _M3d_Act_Fnc__Easy& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order);
        var*& act_Matrix3D__OrthographicProjection   (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);

        inline var*& act_Matrix3D__Rotate__Quaternion    (const _M3d_Act_Fnc__Easy& act, var*& out, var*& quat){return act_Matrix3D__Rotate__Quaternion(act,out,quat[0],quat[1],quat[2],quat[3]);}
        inline var*& act_Matrix3D__Rotate__EulerAngles   (const _M3d_Act_Fnc__Easy& act, var*& out, var*& thetas, Rotation_Order order=XYZ) {return act_Matrix3D__Rotate__EulerAngles(act,out,thetas[0],thetas[1],thetas[2],order);}


        // open * setup * open

            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_x   x方向平移量
             * @param translate_y   y方向平移量
             * @param translate_z   z方向平移量
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Matrix3D__Translate             (setup_Matrix3D__Easy,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Translate             (var*& out, var*& translate_vector)                                               {return act_Matrix3D__Translate             (setup_Matrix3D__Easy,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Matrix3D__Scale                 (setup_Matrix3D__Easy,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Scale                 (var*& out, var scale_value)                                                      {return act_Matrix3D__Scale                 (setup_Matrix3D__Easy,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Reflect               (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Matrix3D__Reflect               (setup_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @param normal_z      镜像轴法线方向上的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Reflect__Collinear    (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Matrix3D__Reflect__Collinear    (setup_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 设置 切变矩阵
             * @param out           输出对象
             * @param axis          切变方向轴
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Shear                 (var*& out, Plane_3D plane, var k1, var k2)                                       {return act_Matrix3D__Shear                 (setup_Matrix3D__Easy,out, plane, k1, k2);}
            /**
             * @brief 设置 旋转矩阵  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Matrix3D__Rotate                (setup_Matrix3D__Easy,out, theta, axis);}
            /**
             * @brief 设置 旋转矩阵  (使用四元数)
             * @param out           输出对象
             * @param quat          四元数
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Rotate__Quaternion     (var*& out, var*& quat)                                                           {return act_Matrix3D__Rotate__Quaternion    (setup_Matrix3D__Easy,out,quat);}
            inline var*& setup_Matrix3D__Rotate__Quaternion     (var*& out, var x, var y, var z, var w)                                           {return act_Matrix3D__Rotate__Quaternion    (setup_Matrix3D__Easy,out,x,y,z,w);}
            /**
             * @brief 设置 旋转矩阵  (使用欧拉角)
             * @param out           输出对象      
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Matrix3D__Rotate__EulerAngles   (setup_Matrix3D__Easy,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 设置 旋转矩阵 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Matrix3D__Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Matrix3D__Rotate__EulerAngles   (setup_Matrix3D__Easy,out, thetas[0],thetas[1],thetas[2], order);}
        
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
            inline var*& transform_Matrix3D__Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Matrix3D__Translate             (transform_Matrix3D__Easy,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Translate             (var*& out, var*& translate_vector)                                               {return act_Matrix3D__Translate             (transform_Matrix3D__Easy,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Matrix3D__Scale                 (transform_Matrix3D__Easy,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Scale                 (var*& out, var scale_value)                                                      {return act_Matrix3D__Scale                 (transform_Matrix3D__Easy,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 矩阵 进行 镜像 变换
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Reflect               (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Matrix3D__Reflect               (transform_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 矩阵 进行 镜像 变换
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @param normal_z      镜像轴法线方向上的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Reflect__Collinear    (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Matrix3D__Reflect__Collinear    (transform_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 矩阵 进行 切变 变换
             * @param out           输出对象
             * @param axis          切变方向
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Shear                 (var*& out, Plane_3D plane, var k1, var k2)                                       {return act_Matrix3D__Shear                 (transform_Matrix3D__Easy,out, plane, k1, k2);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Matrix3D__Rotate                (transform_Matrix3D__Easy,out, theta, axis);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用四元数)
             * @param out           输出对象
             * @param quat          四元数
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Rotate_Quaternion     (var*& out, var*& quat)                                                           {return act_Matrix3D__Rotate__Quaternion    (transform_Matrix3D__Easy,out,quat);}
            inline var*& transform_Matrix3D__Rotate_Quaternion     (var*& out, var x, var y, var z, var w)                                           {return act_Matrix3D__Rotate__Quaternion    (transform_Matrix3D__Easy,out,x,y,z,w);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用欧拉角)
             * @param out           输出对象
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Matrix3D__Rotate__EulerAngles   (transform_Matrix3D__Easy,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 矩阵 进行 旋转 变换 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Matrix3D__Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Matrix3D__Rotate__EulerAngles   (transform_Matrix3D__Easy,out, thetas[0],thetas[1],thetas[2], order);}
        
        // end  * transform * end 

    }
}


#endif
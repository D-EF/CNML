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
            Idx_VM m3d_w=4,m3d_h=4,m3d_length=16;
        // 数据类型的数据对应下标
            Idx_VM mxx=0,    mxy=1,    mxz=2,    mxw=3,
                myx=4,    myy=5,    myz=6,    myw=7,
                mzx=8,    mzy=9,    mzz=10,   mzw=11,
                mwx=12,   mwy=13,   mwz=14,   mww=15;
            Idx_VM &tx=mwx, &ty=mwy, &tz=mwz;
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
        __NML__INLINE__M3D_ACTION_FUNCTION var*& setup_Matrix3D__Easy(var*& out, 
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
        __NML__INLINE__M3D_ACTION_FUNCTION var*& transform_Matrix3D__Easy(var*& mat, 
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

        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Translate                (const _M3d_Act_Fnc__Easy& act, var*& out, var translate_x, var translate_y=0, var translate_z=0);
        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Scale                    (const _M3d_Act_Fnc__Easy& act, var*& out, var scale_x, var scale_y, var scale_z);
        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Reflect                  (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);
        /** never inline */                  var*& act_Reflect__Collinear       (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);
        /** never inline */                  var*& act_Shear                    (const _M3d_Act_Fnc__Easy& act, var*& out, Plane_3D plane, var k1, var k2);
        /** never inline */                  var*& act_Rotate                   (const _M3d_Act_Fnc__Easy& act, var*& out, var theta, Axis axis=X);
        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Rotate__Quaternion       (const _M3d_Act_Fnc__Easy& act, var*& out, var x, var y, var z, var w);
        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Rotate__EulerAngles      (const _M3d_Act_Fnc__Easy& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order);
        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_OrthographicProjection   (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z);

        inline var*& act_Rotate__Quaternion    (const _M3d_Act_Fnc__Easy& act, var*& out, var*& quat){return act_Rotate__Quaternion(act,out,quat[0],quat[1],quat[2],quat[3]);}
        inline var*& act_Rotate__EulerAngles   (const _M3d_Act_Fnc__Easy& act, var*& out, var*& thetas, Rotation_Order order=XYZ) {return act_Rotate__EulerAngles(act,out,thetas[0],thetas[1],thetas[2],order);}


        // open * setup * open

            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_x   x方向平移量
             * @param translate_y   y方向平移量
             * @param translate_z   z方向平移量
             * @return 修改 out 并输出
             */
            inline var*& setup_Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Translate             (setup_Matrix3D__Easy,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& setup_Translate             (var*& out, var*& translate_vector)                                               {return act_Translate             (setup_Matrix3D__Easy,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Scale                 (setup_Matrix3D__Easy,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& setup_Scale                 (var*& out, var scale_value)                                                      {return act_Scale                 (setup_Matrix3D__Easy,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& setup_Reflect               (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Reflect               (setup_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @param normal_z      镜像轴法线方向上的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& setup_Reflect__Collinear    (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Reflect__Collinear    (setup_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 设置 切变矩阵
             * @param out           输出对象
             * @param axis          切变方向轴
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& setup_Shear                 (var*& out, Plane_3D plane, var k1, var k2)                                       {return act_Shear                 (setup_Matrix3D__Easy,out, plane, k1, k2);}
            /**
             * @brief 设置 旋转矩阵  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Rotate                (setup_Matrix3D__Easy,out, theta, axis);}
            /**
             * @brief 设置 旋转矩阵  (使用四元数)
             * @param out           输出对象
             * @param quat          四元数
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate__Quaternion     (var*& out, var*& quat)                                                           {return act_Rotate__Quaternion    (setup_Matrix3D__Easy,out,quat);}
            inline var*& setup_Rotate__Quaternion     (var*& out, var x, var y, var z, var w)                                           {return act_Rotate__Quaternion    (setup_Matrix3D__Easy,out,x,y,z,w);}
            /**
             * @brief 设置 旋转矩阵  (使用欧拉角)
             * @param out           输出对象      
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Rotate__EulerAngles   (setup_Matrix3D__Easy,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 设置 旋转矩阵 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& setup_Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Rotate__EulerAngles   (setup_Matrix3D__Easy,out, thetas[0],thetas[1],thetas[2], order);}
        
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
            inline var*& transform_Translate             (var*& out, var translate_x, var translate_y=0, var translate_z=0)                {return act_Translate             (transform_Matrix3D__Easy,out, translate_x, translate_y, translate_z);}
            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_vector   平移向量
             * @return 修改 out 并输出
             */
            inline var*& transform_Translate             (var*& out, var*& translate_vector)                                               {return act_Translate             (transform_Matrix3D__Easy,out, translate_vector[0], translate_vector[1], translate_vector[2]);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @param scale_z       z 方向缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Scale                 (var*& out, var scale_x, var scale_y,var scale_z)                                 {return act_Scale                 (transform_Matrix3D__Easy,out, scale_x, scale_y, scale_z);}
            /**
             * @brief 矩阵 进行 缩放 变换
             * @param out           输出对象
             * @param scale         缩放值
             * @return 修改 out 并输出
             */
            inline var*& transform_Scale                 (var*& out, var scale_value)                                                      {return act_Scale                 (transform_Matrix3D__Easy,out, scale_value, scale_value, scale_value);}
            /**
             * @brief 矩阵 进行 镜像 变换
             * @param out           输出对象
             * @param normal_x      镜像面的法向的 x 坐标
             * @param normal_y      镜像面的法向的 y 坐标
             * @param normal_z      镜像面的法向的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& transform_Reflect               (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Reflect               (transform_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 矩阵 进行 镜像 变换
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @param normal_z      镜像轴法线方向上的 z 坐标
             * @return 修改 out 并输出
             */
            inline var*& transform_Reflect__Collinear    (var*& out, var normal_x, var normal_y, var normal_z)                             {return act_Reflect__Collinear    (transform_Matrix3D__Easy,out, normal_x, normal_y, normal_z);}
            /**
             * @brief 矩阵 进行 切变 变换
             * @param out           输出对象
             * @param axis          切变方向
             * @param k             切变系数
             * @return 修改 out 并输出
             */
            inline var*& transform_Shear                 (var*& out, Plane_3D plane, var k1, var k2)                                       {return act_Shear                 (transform_Matrix3D__Easy,out, plane, k1, k2);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用旋转轴)
             * @param out           输出对象
             * @param theta         旋转量
             * @param axis          旋转轴
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate                (var*& out, var theta, Axis axis=X)                                               {return act_Rotate                (transform_Matrix3D__Easy,out, theta, axis);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用四元数)
             * @param out           输出对象
             * @param quat          四元数
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate_Quaternion     (var*& out, var*& quat)                                                           {return act_Rotate__Quaternion    (transform_Matrix3D__Easy,out,quat);}
            inline var*& transform_Rotate_Quaternion     (var*& out, var x, var y, var z, var w)                                           {return act_Rotate__Quaternion    (transform_Matrix3D__Easy,out,x,y,z,w);}
            /**
             * @brief 矩阵 进行 旋转 变换  (使用欧拉角)
             * @param out           输出对象
             * @param thetas_1      第1次旋转量
             * @param thetas_2      第2次旋转量
             * @param thetas_3      第3次旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate__EulerAngles   (var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order=XYZ)   {return act_Rotate__EulerAngles   (transform_Matrix3D__Easy,out, thetas_1, thetas_2, thetas_3, order);}
            /**
             * @brief 矩阵 进行 旋转 变换 (使用欧拉角)
             * @param out           输出对象
             * @param thetas        按顺序的旋转量
             * @param order         旋转轴顺序
             * @return 修改 out 并输出
             */
            inline var*& transform_Rotate__EulerAngles   (var*& out, var*& thetas, Rotation_Order order=XYZ)                               {return act_Rotate__EulerAngles   (transform_Matrix3D__Easy,out, thetas[0],thetas[1],thetas[2], order);}
        
        // end  * transform * end 

    }
}



namespace NML{
    namespace Matrix_3D{

        void set_NMLConfig__using_m3d_type(M3D_Type type){
            if(_using_m3d_type==type)return;
            _using_m3d_type=type;
            switch (_using_m3d_type){
                case M3D__3X4:
                    m3d_w=3,m3d_h=4,m3d_length=12;
                    mxx=0,   mxy=1,    mxz=2,    mxw=0,
                    myx=3,   myy=4,    myz=5,    myw=0,
                    mzx=6,   mzy=7,    mzz=8,    mzw=0,
                    tx =9,   ty =10,   tz =11,   mww=0;
                break;

                case M3D__4X3:
                    m3d_w=4,m3d_h=3,m3d_length=12;
                    mxx=0,     myx=1,    mzx=2,    tx=3,
                    mxy=4,     myy=5,    mzy=6,    ty=7,
                    mxz=8,     myz=9,    mzz=10,   tz=11,
                    mxw =0,    myw =0,   mzw =0,   mww=0;
                break;

                case M3D__4X4_L:
                    m3d_w=4,m3d_h=4,m3d_length=16;
                    mxx=0,    mxy=1,    mxz=2,    mxw=3,
                    myx=4,    myy=5,    myz=6,    myw=7,
                    mzx=8,    mzy=9,    mzz=10,   mzw=11,
                    tx =12,   ty =13,   tz =14,   mww=15;
                break;

                case M3D__4X4_R:
                    m3d_w=4,m3d_h=4,m3d_length=16;
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

        __NML__INLINE__M3D_ACTION_FUNCTION var*& setup_Matrix3D__Easy(var*& out, 
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

        __NML__INLINE__M3D_ACTION_FUNCTION var*& transform_Matrix3D__Easy(var*& mat, 
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
            if(!mxw){
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
            );
        }
        
        __NML__INLINE__M3D_ACTION_FUNCTION var*& act_Translate(const _M3d_Act_Fnc__Easy& act, var*& out, var translate_x, var translate_y, var translate_z){
            return act(out,
                1,             0,             0,
                0,             1,             0,
                0,             0,             1,
                translate_x,   translate_y,   translate_z,
                0,0,0,1
            );
        }

        __NML__INLINE__M3D_ACTION_FUNCTION var*& act_Scale (const _M3d_Act_Fnc__Easy& act, var*& out, var scale_x, var scale_y,var scale_z){
            return act(out, 
                scale_x,   0,         0,
                0,         scale_y,   0,
                0,         0,         scale_z,
                0,         0,         0,
                0,0,0,1
            );
        }

        var*& act_Reflect__Collinear (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            var m=normal_x*normal_x+normal_y*normal_y+normal_z*normal_z;
            if(!check_Equal(1,m)){
                m=1/sqrt(m);
                return act_Reflect(act,out,normal_x*m,normal_y*m,normal_z*m);
            }
            return act_Reflect(act,out,normal_x,normal_y,normal_z);
        }

        __NML__INLINE__M3D_ACTION_FUNCTION var*& act_Reflect (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            var i2xy=-2*normal_x*normal_y,
                i2xz=-2*normal_x*normal_z,
                i2yz=-2*normal_y*normal_z;
            return act(out,
                1-2*normal_x*normal_x,   i2xy,                    i2xz,
                i2xy,                    1-2*normal_y*normal_y,   i2yz,
                i2xz,                    i2yz,                    1-2*normal_z*normal_z,
                0,                       0,                       0,
                0,0,0,1
            );
        }

        var*& act_Shear (const _M3d_Act_Fnc__Easy& act, var*& out, Plane_3D plane, var k1, var k2){
            switch (plane){
                case X:
                    return act(out,
                        1,k1,k2,
                        0,1,0,
                        0,0,1,
                        0,0,0,
                        0,0,0,1
                    );
                break;

                case Y:
                    return act(out,
                        1,0,0,
                        k2,1,k1,
                        0,0,1,
                        0,0,0,
                        0,0,0,1
                    );
                break;

                case Z:
                    return act(out,
                        1,0,0,
                        0,1,0,
                        k1,k2,1,
                        0,0,0,
                        0,0,0,1
                    );
                break;
            
                default:
                    return out;
                break;
            }
        }

        var*& act_Rotate (const _M3d_Act_Fnc__Easy& act, var*& out, var theta, Axis axis){
            var c=cos(theta), s=sin(theta);
            switch (axis)
            {
                case X:
                    return act(out,
                        1,   0,    0,
                        0,   c,    s,
                        0,   -s,   c,
                        0,   0,    0,
                        0,0,0,1
                    );
                break;
                
                case Y:
                    return act(out,
                        c,   0,   -s,
                        0,   1,   0,
                        s,   0,   c,
                        0,   0,   0,
                        0,0,0,1
                    );
                break;
                
                case Z:
                    return act(out,
                        c,    s,   0,
                        -s,   c,   0,
                        0,    0,   1,
                        0,    0,   0,
                        0,0,0,1
                    );
                break;
                default:
                    return out;
                break;
            }
        }

        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_Rotate__Quaternion       (const _M3d_Act_Fnc__Easy& act, var*& out, var x, var y, var z, var w){
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
                0,0,0,1
            );
        }

        __NML__INLINE__M3D_ACTION_FUNCTION var*& act_Rotate__EulerAngles (const _M3d_Act_Fnc__Easy& act, var*& out, var thetas_1, var thetas_2, var thetas_3, Rotation_Order order){
            Axis axis= static_cast<Axis>(order>>4 &0b11);
            act_Rotate(act,out,thetas_1,axis);

            axis= static_cast<Axis>(order>>2 &0b11);
            transform_Rotate(out,thetas_2,axis);
            
            axis= static_cast<Axis>(order &0b11);
            return  transform_Rotate(out,thetas_3,axis);
        }

        __NML__INLINE__M3D_ACTION_FUNCTION   var*& act_OrthographicProjection (const _M3d_Act_Fnc__Easy& act, var*& out, var normal_x, var normal_y, var normal_z){
            return act(out,
                1-normal_x*normal_x,   -normal_x*normal_y,    -normal_x*normal_z,
                -normal_x*normal_y,    1-normal_y*normal_y,   -normal_y*normal_z,
                -normal_x*normal_z,    -normal_y*normal_z,    1-normal_z*normal_z,
                0,                     0,                     0,
                0,0,0,1
            );
        }

    }
}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-30 17:02:21
 * @FilePath: \CNML\src\Geometry_2D\NML_Matrix_2D.hpp
 * @Description: 2D 矩阵变换
 */

#ifndef __NML_MATRIX_2D__
#define __NML_MATRIX_2D__
#include "NML.hpp"
#include "Algebra/NML_Matrix.hpp"

namespace NML{
    namespace Matrix_2D{

        /** 可选的2D矩阵的存储格式 */
        enum M2D_Type{
            M2D__3X3_L,   // 矩阵左边乘向量 vec * met
            M2D__3X3_R,   // 矩阵右边乘向量 met * vec
            M2D__2X3,     // 矩阵左边乘向量 vec * met 省略右侧列
            M2D__3X2      // 矩阵右边乘向量 met * vec 省略下侧行
        };

        //默认使用 3*3 左乘向量 (vector * matrix)
        extern M2D_Type _using_m2d_type;

        // 数据类型的数据对应宽高
            extern Idx_VM m2d_w, m2d_h, m2d_l;
        // 数据类型的数据对应下标
            extern Idx_VM 
                mxx,   mxy,   mxz,
                myx,   myy,   myz,
                mzx,   mzy,   mzz;
            extern Idx_VM &mx_null, &my_null, &tx, &ty, &mi_full;
        //


        /**
         * @brief 切换要使用的数据格式
         * @param type 使用的矩阵格式
         */
        void set_NMLConfig__using_m2d_type(M2D_Type type);

        /**
         * @brief 打印输出2d矩阵变换的css样式
         * @param mat 矩阵数据
         */
        void printf_M2dCss(var*& mat);


        // 代码中类似 矩阵左乘向量

        /**
         * @brief 对向量进行变换
         * @param vec 需要变换的向量(2D), 将会被修改
         * @param mat 变换矩阵
         */
        inline void transform_Vector2D( var*& vec, var*& mat){
            var x = mat[mxx]*vec[0]  +  mat[myx]*vec[1]  +  mat[mzx];
            var y = mat[mxy]*vec[0]  +  mat[myy]*vec[1]  +  mat[mzy];
            vec[0] = x;   vec[1] = y;
        }


        /**
         * @brief 对向量进行变换
         * @param vec 需要变换的向量(2D), 将会被修改
         * @param mat 变换矩阵
         * @param _homogeneous_value 齐次坐标的参数值, 默认为 1; 用于将 2D 向量当作 3D [vec[0], vec[1], _homogeneous_value] 与3x3矩阵 进行矩阵乘法
         * @return 输出 变换后的 _homogeneous_value
         */
        inline var transform_Vector2D( var*& vec, var*& mat, var _homogeneous_value){
            var x = mat[mxx]*vec[0]  +  mat[myx]*vec[1]  +  mat[mzx]*_homogeneous_value;
            var y = mat[mxy]*vec[0]  +  mat[myy]*vec[1]  +  mat[mzy]*_homogeneous_value;
            var z = mat[mxz]*vec[0]  +  mat[myz]*vec[1]  +  mat[mzz]*_homogeneous_value;
            vec[0] = x;   vec[1] = y;
            return z;
        }
        
        /**
         * @brief 写入矩阵数据
         * @param out    操作对象           输出目标
         * @param value_mxx 2d线性变换矩阵 参数 mxx
         * @param value_myx 2d线性变换矩阵 参数 mxy
         * @param value_mxy 2d线性变换矩阵 参数 myx
         * @param value_myy 2d线性变换矩阵 参数 myy
         * @param value_tx  x 方向平移量
         * @param value_ty  y 方向平移量
         * @return 写入 out 并返回
         */
        var*& setup_Matrix2D(var*& out, var value_mxx, var value_myx, var value_mxy, var value_myy, var value_tx, var value_ty);
        
        /**
         * @brief 2d矩阵追加变换
         * @param mat     操作对象
         * @param app_mxx 2d线性变换矩阵 参数 mxx
         * @param app_myx 2d线性变换矩阵 参数 mxy
         * @param app_mxy 2d线性变换矩阵 参数 myx
         * @param app_myy 2d线性变换矩阵 参数 myy
         * @param app_tx  x 方向平移量
         * @param app_ty  y 方向平移量
         * @return 修改 mat 并返回
         */
        var*& transform_Matrix2D(var*& mat, var app_mxx, var app_mxy, var app_myx, var app_myy, var app_tx, var app_ty);

        
        typedef var*&(_M2d_Act_Fnc)(var*& mat, var app_mxx, var app_myx, var app_mxy, var app_myy, var app_tx, var app_ty);

        var*& act_Matrix2D__Translate            (const _M2d_Act_Fnc& act, var*& out, var translate_x, var translate_y=0);
        var*& act_Matrix2D__Scale                (const _M2d_Act_Fnc& act, var*& out, var scale_x, var scale_y);
        var*& act_Matrix2D__Rotate               (const _M2d_Act_Fnc& act, var*& out, var theta);
        var*& act_Matrix2D__Rotate__Vector       (const _M2d_Act_Fnc& act, var*& out, var*& unit_vec__from, var*& unit_vec__to);
        var*& act_Matrix2D__Reflect              (const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y);
        var*& act_Matrix2D__Shear                (const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k);
        var*& act_Matrix2D__Reflect__Collinear   (const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y);
        var*& act_Matrix2D__Shear__Collinear     (const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k);


        // open * setup * open

            /**
             * @brief 设置 平移矩阵
             * @param out           输出目标
             * @param translate_x   x 方向平移量
             * @param translate_y   y 方向平移量
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Translate(var*& out, var translate_x, var translate_y=0)
            {return act_Matrix2D__Translate(setup_Matrix2D, out, translate_x, translate_y);}
            /**
             * @brief 设置 缩放矩阵
             * @param out       输出目标
             * @param scale_x   x 方向缩放值
             * @param scale_y   y 方向缩放值
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Scale(var*& out, var scale_x, var scale_y)
            {return act_Matrix2D__Scale(setup_Matrix2D, out, scale_x, scale_y);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出目标
             * @param scale_value   缩放值
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Scale(var*& out, var scale_value)
            {return act_Matrix2D__Scale(setup_Matrix2D, out, scale_value, scale_value);}
            /**
             * @brief 设置 旋转矩阵
             * @param out     输出目标
             * @param theta   旋转弧度
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Rotate(var*& out, var theta)
            {return act_Matrix2D__Rotate(setup_Matrix2D, out, theta);}
            
            /**
             * @brief 使用向量设置旋转矩阵
             * @param out             输出目标
             * @param unit_vec__from   起点坐标 需要是单位坐标
             * @param unit_vec__to    终点坐标 需要是单位坐标
             * @return 修改并返回 out, 将 unit_vec__to 旋转到 unit_vec__from 的变换矩阵
             */
            inline var*& setup_Matrix2D__Rotate__Vector(var*& out, var*& unit_vec__from, var*& unit_vec__to)
            {return act_Matrix2D__Rotate__Vector(setup_Matrix2D, out, unit_vec__from, unit_vec__to);}
            /**
             * @brief 设置 镜像矩阵
             * @param out        输出目标
             * @param normal_x   镜像轴法线方向的标准向量的 x 坐标
             * @param normal_y   镜像轴法线方向的标准向量的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Reflect(var*& out, var normal_x, var normal_y)
            {return act_Matrix2D__Reflect(setup_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 设置 镜像矩阵 (允许法向量为任意向量)
             * @param out        输出目标
             * @param normal_x   镜像轴法线方向上的 x 坐标
             * @param normal_y   镜像轴法线方向上的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Reflect__Collinear(var*& out, var normal_x, var normal_y)
            {return act_Matrix2D__Reflect__Collinear(setup_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 设置 切变矩阵
             * @param out      输出目标
             * @param axis_x   切变轴标准向量的 x 坐标
             * @param axis_y   切变轴标准向量的 y 坐标
             * @param k        切变系数
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Shear(var*& out, var axis_x, var axis_y, var k)
            {return act_Matrix2D__Shear(setup_Matrix2D, out, axis_x, axis_y, k);}
            /**
             * @brief 设置 切变矩阵
             * @param out      输出目标
             * @param axis_x   切变轴方向上的 x 坐标
             * @param axis_y   切变轴方向上的 y 坐标
             * @param k        切变系数
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Shear__Collinear(var*& out, var axis_x, var axis_y, var k)
            {return act_Matrix2D__Shear__Collinear(setup_Matrix2D, out, axis_x, axis_y, k);}
        
        // end  * setup * end  


        // open * transform * open

            /**
             * @brief 矩阵进行平移变换
             * @param out           输出目标
             * @param translate_x   x 方向平移量
             * @param translate_y   y 方向平移量
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Translate(var*& out, var translate_x, var translate_y=0)
            {return act_Matrix2D__Translate(transform_Matrix2D, out, translate_x, translate_y);}
            /**
             * @brief 矩阵进行缩放变换
             * @param out       输出目标
             * @param scale_x   x 方向缩放值
             * @param scale_y   y 方向缩放值
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Scale(var*& out, var scale_x, var scale_y)
            {return act_Matrix2D__Scale(transform_Matrix2D, out, scale_x, scale_y);}
            /**
             * @brief 矩阵进行缩放变换
             * @param out           输出目标
             * @param scale_value   缩放值
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Scale(var*& out, var scale_value)
            {return act_Matrix2D__Scale(transform_Matrix2D, out, scale_value, scale_value);}
            /**
             * @brief 矩阵进行旋转变换
             * @param out     输出目标
             * @param theta   旋转轴
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Rotate(var*& out, var theta)
            {return act_Matrix2D__Rotate(transform_Matrix2D, out, theta);}
            
            /**
             * @brief 使用向量 矩阵进行旋转变换
             * @param out             输出目标
             * @param unit_vec__from   起点坐标 需要是单位坐标
             * @param unit_vec__to    终点坐标 需要是单位坐标
             * @return 修改并返回 out, 矩阵将 unit_vec__to 旋转到 unit_vec__from 
             */
            inline var*& transform_Matrix2D__Rotate__Vector(var*& out, var*& unit_vec__from, var*& unit_vec__to)
            {return act_Matrix2D__Rotate__Vector(transform_Matrix2D, out, unit_vec__from, unit_vec__to);}
            /**
             * @brief 矩阵进行镜像变换
             * @param out        输出目标
             * @param normal_x   镜像轴法线方向的标准向量的 x 坐标
             * @param normal_y   镜像轴法线方向的标准向量的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Reflect(var*& out, var normal_x, var normal_y)
            {return act_Matrix2D__Reflect(transform_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 矩阵进行镜像变换 (允许法向量为任意向量)
             * @param out        输出目标
             * @param normal_x   镜像轴法线方向上的 x 坐标
             * @param normal_y   镜像轴法线方向上的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Reflect__Collinear(var*& out, var normal_x, var normal_y)
            {return act_Matrix2D__Reflect__Collinear(transform_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 矩阵进行切变变换
             * @param out      输出目标
             * @param axis_x   切变轴标准向量的 x 坐标
             * @param axis_y   切变轴标准向量的 y 坐标
             * @param k        切变系数
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Shear(var*& out, var axis_x, var axis_y, var k)
            {return act_Matrix2D__Shear(transform_Matrix2D, out, axis_x, axis_y, k);}
            /**
             * @brief 矩阵进行切变变换
             * @param out      输出目标
             * @param axis_x   切变轴方向上的 x 坐标
             * @param axis_y   切变轴方向上的 y 坐标
             * @param k        切变系数
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Shear__Collinear(var*& out, var axis_x, var axis_y, var k)
            {return act_Matrix2D__Shear__Collinear(transform_Matrix2D, out, axis_x, axis_y, k);}

        // end  * transform * end 

    }
}

#endif
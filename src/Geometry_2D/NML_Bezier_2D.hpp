/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:56:17
 * @FilePath: \CNML\src\Geometry_2D\NML_Bezier_2D.hpp
 * @Description: 2D 贝塞尔曲线相关计算
 */

#ifndef __NML_BEZIER_2D__
#define __NML_BEZIER_2D__

#include "NML.hpp"

namespace NML{
    
    namespace Geometry_2D{

        /**
         * @brief 2d 贝塞尔曲线与线段求交
         * @param out            交点输出对象 应该有至少 coefficients.points_length-1 的长度以保证空间足够存储输出
         * @param coefficients   曲线 0 计算系数
         * @param line_p0        线段的端点 0
         * @param line_p1        线段的端点 1
         * @return 返回交点的个数
         */
        Idx_Algebra calc_Intersection__Bezier_Line(Points_Iterator& out, Points_Iterator& coefficients, var*& line_p0, var*& line_p1);

        /**
         * @brief 2d贝塞尔曲线求交
         * @param out                               交点输出对象 应该有至少 (coefficients_0.points_length-1) * (coefficients_1.points_length-1) 的长度以保证空间足够存储输出
         * @param coefficients_0                    曲线 0 计算系数
         * @param coefficients_1                    曲线 1 计算系数
         * @param derivatives_roots_lut_0           用于分隔曲线以生成单调曲线的 t 值  ( 使用 calc_T__DerivativesRootsLUT 生成 )
         * @param length__derivatives_roots_lut_0   derivatives_roots_lut_0 的长度
         * @param derivatives_roots_lut_1           用于分隔曲线以生成单调曲线的 t 值  ( 使用 calc_T__DerivativesRootsLUT 生成 )
         * @param length__derivatives_roots_lut_1   derivatives_roots_lut_1 的长度
         * @return 返回交点的个数
         */
        Idx calc_Intersection__Bezier_Bezier(
            Points_Iterator&   out, 
            Points_Iterator&   coefficients_0, 
            Points_Iterator&   coefficients_1, 
            var*&              derivatives_roots_lut_0, 
            Idx                length__derivatives_roots_lut_0, 
            var*&              derivatives_roots_lut_1, 
            Idx                length__derivatives_roots_lut_1
        );
    }
}

#endif
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

    }
}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-10-11 10:40:47
 * @FilePath: \cnml\src\NML_Geometry.hpp
 * @Description: 提供部分数据结构和算法, 不区分维度的通用内容
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NML_GEOMETRY__
#define __NML_GEOMETRY__

#include "NML.hpp"
#include "NML_Vector.hpp"

namespace NML{
    
    namespace Geometry{

        /**
         * @brief 计算直线段长度
         * @param point0 线段端点0
         * @param point1 线段端点1
         * @param dimensional 点的维度
         * @return 计算直线段长度并返回
         */
        var calc_LineDistance(var* point0, var* point1, Idx_Algebra dimensional);

        /**
         * @brief 计算直线段路径长度
         * @param line_path 路径点数据
         * @return 计算路径长度并返回
         */
        var calc_LinePathDistance(Points_Iterator& line_path);

        /**
         * 计算直线段路径并生成对应的 LUT 显示查找表
         * @param line_path      路径点数据
         * @param out_distance_lut   输出的对应长度的 LUT, 数据长度应该和点的个数相等
         * @return 计算路径长度并返回
         */
        var calc_LinePathDistance(Points_Iterator& line_path, var*& out_distance_lut);

    }

}

#endif
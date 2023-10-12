/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-10-11 10:40:47
 * @FilePath: \cnml\src\NML_Geometry.hpp
 * @Description: 提供部分数据结构和算法, 不区分维度的通用内容
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
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
         * @return 计算直线段长度并返回
         */
        var calc_LineLong(var* point0, var* point1, Idx_Algebra length);

        /**
         * @brief 计算直线段路径长度
         * @param line_path 直线段路径数据
         * @return 计算路径长度并返回
         */
        var calc_LinePathLong(Points_Iterator& line_path);

        

    }

}

#endif
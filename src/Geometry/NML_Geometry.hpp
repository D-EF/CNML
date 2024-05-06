/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-29 15:12:24
 * @FilePath: \CNML\src\Geometry\NML_Geometry.hpp
 * @Description: 通用图形计算, 提供部分数据结构和算法, 不区分维度的通用内容
 */

#ifndef __NML_GEOMETRY__
#define __NML_GEOMETRY__

#include "NML.hpp"
#include "Algebra/NML_Vector.hpp"

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
         * @brief 计算直线段路径并生成对应的 LUT 显示查找表
         * @param line_path      路径点数据
         * @param out_distance_lut   输出的对应长度的 LUT, 数据长度应该和点的个数相等
         * @return 计算路径长度并返回
         */
        var calc_LinePathDistance(Points_Iterator& line_path, var*& out_distance_lut);

        /**
         * @brief 加载 AABB 的角
         * @param out  输出对象, 长度应为 dimensional
         * @param min  AABB 的最小值, 长度应为 dimensional
         * @param max  AABB 的最大值, 长度应为 dimensional
         * @param dimensional 计算多少个维度, 取值范围为 [0, sizeof(int)]
         * @param corner_index AABB 角的序号, 取值范围为 [0, 2^dimensional]; 
         * @return 修改并返回 out
         */
        var*& load_AABBCorner(var*& out, var*& min, var*& max, Idx_Algebra dimensional, int corner_index);
        
        
        /**
         * @brief 对 AABB 置空
         * @param min  AABB 的最小值, 将置为 +INFINITY
         * @param max  AABB 的最大值, 将置为 -INFINITY
         */
        inline void empty_AABB(var*& min, var*& max){min[0]=INFINITY; max[0]=-INFINITY;}


        /**
         * @brief 检查 AABB 是否为空 (当 min 中某值大于对应维度的 max 值 时表示当前 AABB 为空盒子)
         * @param min  AABB 的最小值, 长度应为 dimensional
         * @param max  AABB 的最大值, 长度应为 dimensional
         * @param dimensional 计算多少个维度
         * @return 返回 是否为空
         */
        bool check_AABBEmpty(var*& min, var*& max, Idx_Algebra dimensional);
        
    }

}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-10 16:10:16
 * @FilePath: \CNML\src\Geometry_2D\NML_Geometry_2D_Primitive.hpp
 * @Description: 2D 图元 相关内容
 */

#ifndef __NML_GEOMETRY_2D_PRIMITIVE__
#define __NML_GEOMETRY_2D_PRIMITIVE__

#include "NML.hpp"
#include "Geometry/NML_Geometry.hpp"
#include "./NML_Geometry_2D.hpp"
#include "./NML_Matrix_2D.hpp"

namespace NML{
    namespace Geometry_2D{
        /**
         * @brief 2D 图元
         */
        namespace Primitive_2D{             

            class Primitive_2D{
                using AABB_Nodes = Geometry::AABB_Nodes;
                var _girth;
                var _max[2];
                var _min[2];
                AABB_Nodes _monotonic_aabb;
                Points_Iterator* _line_path;
                public:
                
                /** 
                 * @brief 获取周长
                 * @return 返回获取周长; 缓存可用则返回缓存值, 不可用则重新计算
                 */
                var get_Girth();
                
                /** 
                 * @brief 获取局部坐标的 AABB 包围盒数据
                 * @return 返回获取局部坐标的 AABB; 缓存可用则返回缓存值, 不可用则重新计算
                 */
                AABB_2D get_LocalAABB();

                /** 
                 * @brief 获取 拟合图元的线段路径
                 */
                Points_Iterator& get_LinePath();

                
                /** 
                 * @brief 获取 拟合图元的线段路径
                 */
                void read_LinePath(Points_Iterator& out, Idx write_index);
                

            };

        }
    }
}

#endif
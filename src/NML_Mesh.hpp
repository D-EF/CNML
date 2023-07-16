/*!
 * @Description: 2D 图元 相关内容
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-07-13 21:02:20
 */

#ifndef __NML_Mesh
#define __NML_Mesh

#include "NML.hpp"
#include "NML_Matrix_2D.hpp"

namespace NML{
    /**
     * @brief 多边形组
     */
    namespace Mesh{

        class Triangles_Mesh{
            /** @brief 点云数据 */
            Points_Iterator* point_cloud_data;
            /** 索引集合 */
            Idx* id;
        };
    }
}

#endif
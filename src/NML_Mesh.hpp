/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-08 16:42:52
 * @FilePath: \cnml\src\NML_Mesh.hpp
 * @Description: 多边形网格
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef __NML_Mesh__
#define __NML_Mesh__

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
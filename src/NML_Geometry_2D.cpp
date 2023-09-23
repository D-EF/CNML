/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-19 18:18:53
 * @FilePath: \cnml\src\NML_Geometry_2D.hpp
 * @Description: 矩阵 Matrix
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Geometry_2D.hpp"

namespace NML{
    
    namespace Geometry_2D{
        
        Rect_Data*& normalize_RectData(Rect_Data*& rect_data){
            if(rect_data->w<0){
                rect_data->x+=rect_data->w;
                rect_data->w=-rect_data->w;
            }
            if(rect_data->h<0){
                rect_data->y+=rect_data->h;
                rect_data->h=-rect_data->h;
            }
            return rect_data;
        }


        Arc_Data*& normalize_ArcData(Arc_Data*& arc_data){
            if(arc_data->theta_0>arc_data->theta_1){
                std::swap(arc_data->theta_0,arc_data->theta_1);
            }
            return arc_data;
        }
        
        char check_Inside__AABB(AABB_2D aabb,var x, var y){
            if(aabb.x0>x||aabb.x1<x)     return 0;
            if(aabb.y0>y||aabb.y1<y)     return 0;
            if(aabb.x0==x||aabb.x1==x)   return 2;
            if(aabb.y0==y||aabb.y1==y)   return 2;
            return 1;
        }
        
    }
}
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-08 16:40:23
 * @FilePath: \cnml\src\NML_Primitives_2D.cpp
 * @Description: 2D 图元 相关内容
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Primitives_2D.hpp"

namespace NML{
    namespace Primitives_2D{
        
        var Primitive_2D::get_Girth(){
            if(!_had__girth){
                _girth= calc_Girth();
                _had__girth = true;
            }
            return _girth;
        }

        AABB_2D Primitive_2D::get_LocalAABB(){
            if(!_had__girth){
                _loc_aabb = calc_LocalAABB();
                _had__loc_aabb = true;
            }
            return _loc_aabb;
        }

        Points_Iterator*& Primitive_2D::get_LinePath(){
            if(!_had__girth){
                _line_path = load_LinePath();
                _had__line_path = true;
            }
            return _line_path;
        }

        
    }
}

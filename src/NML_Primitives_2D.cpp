#include "NML_Primitives_2D.hpp"

namespace NML{
    namespace Primitives_2D{
        
        var Primitive_2D::get_Girth(){
            if(!had__girth){
                _girth= calc_Girth();
                had__girth = true;
            }
            return _girth;
        }

        AABB Primitive_2D::get_LocalAABB(){
            if(!had__girth){
                loc_aabb = calc_LocalAABB();
                had__loc_aabb = true;
            }
            return loc_aabb;
        }

    }
}

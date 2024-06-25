/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-05-28 14:15:24
 * @FilePath: \CNML\src\Geometry\NML_Geometry.cpp
 * @Description: 通用图形计算, 提供部分数据结构和算法, 不区分维度的通用内容
 */

#include "./NML_Geometry.hpp"

namespace NML{
    
    namespace Geometry{

        var calc_LineDistance(var* point0, var* point1, Idx_Algebra dimensional){
            var g=0;
            for(Idx_Algebra i;  i<dimensional;  ++i){
                g+=point0[i]*point0[i] + point1[i]*point1[i];
            }
            return sqrt(g);
        }

        var calc_LinePathDistance(Points_Iterator& line_path){
            var rtn=0;
            for(Idx i=1; i<line_path.points_length; ++i){
                rtn=calc_LineDistance(line_path[i],line_path[i-1],line_path.dimensional);
            }
            return rtn;
        }

        var calc_LinePathDistance(Points_Iterator& line_path, var*& out_distance_lut){
            Idx i=0,l=line_path.points_length-1;
            while(i<line_path.points_length){
                out_distance_lut[i]=calc_LineDistance(line_path[i],line_path[++i],line_path.dimensional);
            }
            return out_distance_lut[i];
        }

        
        var*& load_AABBCorner(var*& out, var*& min, var*& max, Idx_Algebra dimensional, int corner_index){
            int flag=0b1;
            for(Idx_Algebra i=0;  i<dimensional;  ++i, flag<<1){
                out[i] = corner_index & flag ? min[i] : max[i];
            }
            return out;
        }

        bool check_AABBEmpty(var*& min, var*& max, Idx_Algebra dimensional){
            for(Idx_Algebra i=0; i<dimensional; ++i){
                if(min[i]<max[i]){
                    return true;
                }
            }
            return false;
        }


        bool check_Intersection__AABB(AABB_Node& aabb_0, AABB_Node& aabb_1){
            int l=aabb_0.dimensional/2;
            for(int i=0; i<l; ++i){
                if(! check_Intersection__Range_Unordered(aabb_0.aabb[i],aabb_0.aabb[i+l],aabb_1.aabb[i],aabb_1.aabb[i+l]) ) return false;
            }
            return true;
        }

        bool check_Tolerance__AABB(AABB_Node& box, var _tolerance){
            var temp=0;
            int l=box.dimensional/2;
            for(Idx i=0; i<l; ++i){
                temp += abs(box.aabb[i]-box.aabb[i+l]);
            }
            return _tolerance > temp;
        }
        
    }

}

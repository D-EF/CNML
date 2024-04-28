/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:54:25
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

    }

}

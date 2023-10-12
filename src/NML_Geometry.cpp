/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-10-11 17:50:49
 * @FilePath: \cnml\src\NML_Geometry.hpp
 * @Description: 提供部分数据结构和算法, 不区分维度的通用内容
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Geometry.hpp"

namespace NML{
    
    namespace Geometry{

        var calc_LineLong(var* point0, var* point1, Idx_Algebra length){
            var g=0;
            for(Idx_Algebra i;  i<length;  ++i){
                g+=point0[i]*point0[i] + point1[i]*point1[i];
            }
            return sqrt(g);
        }

        var calc_LinePathLong(Points_Iterator& line_path){
            var rtn=0;
            for(Idx i=1; i<line_path.points_length; ++i){
                rtn=calc_LineLong(line_path[i],line_path[i-1],line_path.dimensional);
            }
            return rtn;
        }

    }

}
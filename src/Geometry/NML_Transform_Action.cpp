/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:55:05
 * @FilePath: \CNML\src\Geometry\NML_Transform_Action.cpp
 * @Description: 2D 3D 矩阵变换控制
 */

#include "./NML_Transform_Action.hpp"

namespace NML{
    namespace Matrix{
        
        var*& transform_Matrix(var*& action_target, Transform_Matrix_Flow*& act_flow_entrance){
            Transform_Matrix_Flow *doing_act = act_flow_entrance;
            do{
                doing_act->act->transform(action_target);
                doing_act=doing_act->next;
            }while(doing_act);
            return action_target;
        }
        
    }
}

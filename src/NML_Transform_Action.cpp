/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-19 18:23:52
 * @FilePath: \CNML\src\NML_Primitives_2D.hpp
 * @Description: 2D 3D 矩阵变换控制
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML_Transform_Action.hpp"

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

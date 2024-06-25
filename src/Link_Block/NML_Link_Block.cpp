/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-24 17:59:57
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块状链表存储结构
 */

#include "./NML_Link_Block.hpp"

namespace NML{
    namespace Link_Block{

        Option_Act_LinkBlock _DEFAULT_Link_Block_ACT_OPTION={
            2,  // find_free_max_after_node_count
            2,  // find_free_max_before_node_count
            255,  // ex_link_block_length
            0,  // flag_delete_data_item
        };
        Option_Act_LinkBlock* get_DefaultLinkBlockActOption(){return &_DEFAULT_Link_Block_ACT_OPTION;}


        Idx Points_Iterator__LinkBlock::calc_UsedPointsLength(){
            LBC* d = (LBC*)data;
            LBN* node = d->head_node;
            Idx rtn;
            while(node){
                rtn+=node->used_length/dimensional;
                node=node->next;
            }
            return rtn;
        }


        Idx Points_Iterator__LinkBlock::calc_PointsLength(){
            LBC* d = (LBC*)data;
            LBN* node = d->head_node;
            Idx rtn;
            while(node){
                rtn+=node->length/dimensional;
                node=node->next;
            }
            return rtn;
        }
        

        void Points_Iterator__LinkBlock::set_PointsLength(Idx new_points_length){
            settle_Values();
            LBC* d = (LBC*)data;
            Idx l = new_points_length - points_length;
            l*=dimensional;
            if(l<0){
                d->remove_EndItems(l);
            }else if(l>0){
                var* new_data = new var[l];
                d->push_Items(new_data,l);
                delete new_data;
            }
        }

        
        void Points_Iterator__LinkBlock::settle_Values(Idx critical_value=0){
            LBC* d = (LBC*)data;
            LBN* node = d->head_node;
            Idx l=0,i=0;

            if(critical_value<=0) critical_value = get_Option()->ex_link_block_length/2;

            while(node){
                node->used_length -= node->used_length%dimensional;
                l+=node->used_length;
                ++i;
                if(l>critical_value){
                    merge_LinkBlock(node,i,get_Option()->ex_link_block_length);
                    l = i = 0;
                }
                node=node->next;
            }
        }


    }
}
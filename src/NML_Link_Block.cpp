/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-08 18:05:00
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块链存储结构
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML_Link_Block.hpp"

namespace NML{
    namespace Link_Block{
        template <typename Value_Type> 
        Value_Type get_Item__LinkBlock(
            const Link_Block_Node<Value_Type>* const origin_node, Idx index_offset, 
            Link_Block_Node<Value_Type>** _out_node, Idx* _out_node_head_index
        ){
            Idx i;
            Link_Block_Node<Value_Type> *now_node=origin_node;

            if(index_offset>=0){
                for(i=0;  i+now_node->used_length<index_offset;  i+=now_node->used_length, now_node=now_node->next) 
                    if(now_node.next==0) throw index_offset;
            }else{
                for(i=0;  i>index_offset;  i-=now_node->used_length, now_node=now_node->previous) 
                    if(now_node.previous==0) throw index_offset;
            }
            if(_out_node_head_index)*_out_node_head_index=i;
            if(_out_node)*_out_node=now_node;
            return now_node->data[index_offset-i];
        }
        

        template <typename Value_Type> 
        void free_LinkBlock__After(Link_Block_Node<Value_Type>* header_node,bool _delete_data_item){
            Link_Block_Node<Value_Type> *now_node=header_node, *temp=header_node->previous;
            Idx i;

            while(!check_ELE__Link_Block(header_node,now_node,temp)){
                now_node->previous=0;
                temp=now_node->next;
                now_node->next=0;
                if(_delete_data_item){
                    for(i=0;  i<now_node->used_length;  ++i){
                        delete now_node->data[i];
                    }
                }
                delete now_node;
            }
        }

        template <typename Value_Type> 
        Idx spread_LinkBlock(
            Link_Block_Node<Value_Type>& header_node, Idx index__offset, Idx length,
            Link_Block_Node<Value_Type>* $origin_node,
            bool _reset_used_length
        ){
            // 初始化将 $origin_node 设置为基准节点
            Link_Block_Node<Value_Type>*& origin_node=$origin_node;
            if(!origin_node) origin_node=&header_node;
            if(index__offset>origin_node->used_length) get_Item__LinkBlock(origin_node, index__offset, &origin_node, &index__offset);

            if(origin_node->length-origin_node->used_length > length){
                // todo
            }
            
            Link_Block_Node<Value_Type> *l_node=origin_node, *r_node=origin_node;
            
            Idx idx__left_node_offset, idx__right_node_offset;
            while(
                check_ELE__Link_Block()
            );
        }
        
        template <typename Value_Type> 
        bool splice_LinkBlock(
            Link_Block_Node<Value_Type>& header_node, Idx index__offset, Idx length,
            Link_Block_Node<Value_Type>* $origin_node,
            Value_Type* _value, Idx _length_value, Behavior_Pattern__Add_LinkBlock _paternadd, Idx _add_node_length, Idx _max_link_block_length 
        ){
            Link_Block_Node<Value_Type>* target_node;
            Idx idx__target_node_head;
            get_Item__LinkBlock($origin_node, index__offset, &target_node, &idx__target_node_head);
            switch (_paternadd)
            {
                // todo
                case disabled:
                break;
                case disabled_move_forward:
                break;
                case disabled_move_backward:
                break;
                case able_move_forward:
                break;
                case able_move_backward:
                break;
                case tight:
                break;
                case active:
                break;
                case lazy: default:
                break;
            }
        }
        
        
        
        /**
         * 合并块链
         * @param origin_node   起始节点
         * @param node_length   需要合并多少个节点
         * @param _min_length   当合并后的节点容量小于 _min_length 时, 使用 _min_length 作为节点的容量
         */
        template <typename Value_Type> 
        Link_Block_Node<Value_Type>* merge_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx node_length, Idx _min_length){

        }
        

        template <typename Value_Type> 
        Idx calc_MaxLength(Link_Block_Node<Value_Type>& header_block){

        }
        


        // 点遍历器 链块存储
        
        void Points_Iterator__Link::free_Data(){
            Link_Block__Simple<var> *temp=((Link_Block__Simple<var>*)data), *next;
            while(temp!=data){
                delete temp->data;
                next=temp->next;
                delete temp;
                temp=next;
            }
        }

        var* Points_Iterator__Link::operator[](Idx v){
            Link_Block__Simple<var> *now_block;
            Idx now_block_head_v;
            if(v>=max_points_length) v = v % max_points_length;
            if(v>last_access_head_v){
                now_block=last_access_block;
                now_block_head_v=last_access_head_v;
            }else{
                now_block=((Link_Block__Simple<var>*)data)->next;
                now_block_head_v=0;
            }
            if((!now_block)||(!max_points_length)) return 0;

            Idx now_block_last_v=now_block_head_v+now_block->length/dimensional-1;
            while(now_block_last_v<v){
                now_block=now_block->next;
                now_block_head_v=now_block_last_v+1;
                now_block_last_v=now_block_head_v+now_block->length/dimensional-1;
            }
            last_access_block=now_block;
            last_access_head_v=now_block_head_v;
            return now_block->data + (v-now_block_head_v)*dimensional;
        }
        
        Idx Points_Iterator__Link::calc_MaxPointsLength(){
            Link_Block__Simple<var> *now_block=(Link_Block__Simple<var>*)data;
            if(!now_block) return 0;
            Idx rtn=0;
            do{
                rtn+=now_block->length/dimensional;
                now_block=now_block->next;
            }while(now_block!=data);
            max_points_length=rtn;
            return rtn;
        }

        void Points_Iterator__Link::append_Block(Idx length){
            if(length<__MIN_LINK_BLOCK_SIZE__)length=__MIN_LINK_BLOCK_SIZE__;
            if(length>__MAX_LINK_BLOCK_SIZE__)length=__MAX_LINK_BLOCK_SIZE__;
            Link_Block__Simple<var> *block=new Link_Block__Simple<var>{ 0, length, new var[length] };
            Link_Block__Simple<var> *last_block=(Link_Block__Simple<var>*)data;
            if(!last_block){
                block->next=block;
                data=block;
                max_points_length=length/dimensional;
            }else{
                block->next=last_block->next;
                last_block->next=block;
                max_points_length+=length/dimensional;
            }
        }


    }
}
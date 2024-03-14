/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-14 15:34:57
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块链存储结构
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML_Link_Block.hpp"

namespace NML{
    namespace Link_Block{
        template <typename Value_Type> 
        Value_Type& get_Item__LinkBlock(
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
        int splice_LinkBlock(
            Link_Block_Node<Value_Type>& header_node, Idx index__offset, Idx delete_length,
            Link_Block_Node<Value_Type>* $origin_node,
            Value_Type* _ex_value, Idx _ex_length, Option_Act_LinkBlock* _option
        ){
            // 初始化将 $origin_node 设置为基准节点
            if(delete_length<0){
                index__offset-=delete_length;
                delete_length=-delete_length;
            }
            Link_Block_Node<Value_Type>*& origin_node=$origin_node;
            if(!origin_node) origin_node=&header_node;
            if(index__offset>origin_node->used_length) get_Item__LinkBlock(origin_node, index__offset, &origin_node, &index__offset);

            if(_ex_length<0)_ex_length=0;

            Idx i;
            /** 插入位置的指针 */
            Value_Type* ptr_using_data;
            /** 插入位置后 有多少使用过的元素 */
            Idx length__used = origin_node->used_length - index__offset;
            /** 插入位置后 有多少元素的空间 */
            Idx length__full = origin_node->length - index__offset;
            

            if(_option->delete_data_item) for(i=index__offset; i< origin_node->used_length; ++i){
                delete origin_node->data[i];
            }

            // 仅需操作当前节点
            if( length__full > _ex_length-delete_length && length__used > delete_length ){
                ptr_using_data = origin_node.data+index__offset;
                if(_ex_length){
                    if(_ex_length<delete_length) std::copy(ptr_using_data + delete_length,  origin_node->data + origin_node->used_length,  ptr_using_data);
                    if(_ex_length>delete_length) std::copy_backward(ptr_using_data + delete_length,  origin_node->data + origin_node->used_length,  ptr_using_data);
                    std::copy(_ex_value, _ex_value+_ex_length, ptr_using_data);
                }
                origin_node->used_length = origin_node->used_length + _ex_length - delete_length;
                return 0;
            }

            Link_Block_Node<Value_Type>* now_node=origin_node.next;
            Link_Block_Node<Value_Type>* previous_node=origin_node;
            Idx count__free=previous_node->length-previous_node->used_length;
            Idx count__delete=previous_node->used_length-index__offset;
            Link_Block_Node<Value_Type>* delete_end_node=0;
            Idx delete_end_index;

            if( count__delete > delete_length){ // 基准节点已达成删除量
                delete_end_index= delete_length + index__offset;
                delete_end_node=previous_node;
                count__delete = delete_length;
            }

            for(i=0;  ((count__delete<delete_length)|| ((count__free<_ex_length) && (i!=_option->max_after_free_count))) && check_ELE__Link_Block(header_node,now_node,previous_node);  ++i){
                if(delete_length==count__delete){
                    count__free += now_node->length - now_node->used_length;
                }
                else {
                    count__delete += now_node->used_length;
                    if( count__delete > delete_length){ // 达成删除量
                        delete_end_index= delete_length - count__delete + now_node->used_length;
                        delete_end_node=now_node;
                        count__delete = delete_length;
                    }
                }
                previous_node = now_node;
            }
            if(count__free>_ex_length){
                
            }
            // todo
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
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-19 17:59:12
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块状链表存储结构
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
            Link_Block_Node<Value_Type> *now=origin_node;

            if(index_offset>=0){
                for(i=0;  i+now->used_length<index_offset;  i+=now->used_length, now=now->next) 
                    if(now.next==0) throw index_offset;
            }else{
                for(i=0;  i>index_offset;  i-=now->used_length, now=now->prev) 
                    if(now.prev==0) throw index_offset;
            }
            if(_out_node_head_index)*_out_node_head_index=i;
            if(_out_node)*_out_node=now;
            return now->data[index_offset-i];
        }
        

        template <typename Value_Type> 
        void free_LinkBlock__After(Link_Block_Node<Value_Type>* header_node,bool _flag_delete_data_item){
            Link_Block_Node<Value_Type> *now=header_node, *temp=header_node->prev;
            Idx i;

            while(!check_ELE__Link_Block(header_node,now,temp)){
                now->prev=0;
                temp=now->next;
                now->next=0;
                if(_flag_delete_data_item){
                    for(i=0;  i<now->used_length;  ++i){
                        delete now->data[i];
                    }
                }
                delete now;
            }
        }


        template <typename Value_Type> 
        Idx erase_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, 
            Idx _erase_length, bool _flag_delete_data_item, Link_Block_Node<Value_Type>* _end_node, Link_Block_Node<Value_Type>** _out_node 
        ){
            if(_erase_length<1) return 0;
            redirect_LinkBlock(origin_node, index);

            Link_Block_Node<Value_Type> *&now =  origin_node;
            Link_Block_Node<Value_Type> *prev_node =  origin_node.prev;
            Idx erase_count=0;
            Idx rtn=0;
            Idx erase_end;  
            Idx last;

            if(now->used_length-index >= _erase_length){
                erase_end=index+_erase_length;
                last=index;
            }else{
                erase_end=now->used_length;
                last=0;
            }

            while(check_ELE__Link_Block(_end_node,origin_node,prev_node)){
                now->used_length = index;
                if(_flag_delete_data_item){
                    erase_count += erase_end-index;
                    while(index<erase_end){
                        delete now->data[index];
                        ++index;
                    }
                }else{
                    erase_count += erase_end-index;
                }
                if(erase_count<_erase_length) break;
                index=0;
                prev_node=now;
                now=now->next;
                erase_end=std::min(now->used_length, _erase_length-erase_count);
                rtn+=std::min(now->length, _erase_length-erase_count);
            }
            std::copy(now->data+erase_end, now->data+erase_end+now->used_length, now->data+last);
            if(_out_node)*_out_node=now;
            return rtn;
        }


        template <typename Value_Type> 
        int shiftForward_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx length, 
            Link_Block_Node<Value_Type>** _out_node, Idx* _out_index, Link_Block_Node<Value_Type>* _end_node, Idx _max_node_length
        ){
            redirect_LinkBlock(origin_node, index);
            Link_Block_Node<Value_Type>* now=origin_node->prev;
            Link_Block_Node<Value_Type>* next=origin_node;
            Idx shift_length=0, offset, node_length=0;

            // 寻找可用空闲空间
            while(shift_length<length && now && now!=_end_node && now->next!=next && node_length<_max_node_length){
                ++node_length;
                if(shift_length+now->length-now->used_length>length){
                    offset=length-shift_length;
                }else{
                    offset=now->length-now->used_length;
                }
                shift_length+=offset;
                next=now;
                now=now->prev;
            }
            if(shift_length==0) return 0;

            now=next;
            next=next->next;
            Link_Block_Node<Value_Type>*& write=now;
            Link_Block_Node<Value_Type>*& read=next;
            
            Idx idx_write=write->used_length, idx_read=0, offset_read=next->used_length;
            Idx &offset_write=offset;
            offset_write+=write->used_length;

            do{
                if(idx_write>=offset_write){
                    idx_write=0;
                    write=write->next;
                    write->used_length=0;
                    offset_write=write->length;
                }
                if(idx_read>=offset_read){
                    idx_read=0;
                    read=read->next;
                    offset_read=read->used_length;
                }
                ++write->used_length;
                write->data[idx_write] = read->data[idx_read];
                ++idx_write;
                ++idx_read;
            }while(!((write==origin_node) && (idx_read==index)));

            if(_out_index) *_out_index=idx_write;
            if(_out_node) *_out_node=write;
            return shift_length;
        }


        template <typename Value_Type> 
        int backOff_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx length, 
            Link_Block_Node<Value_Type>** _out_node, Idx* _out_index, Link_Block_Node<Value_Type>* _end_node, Idx _max_node_length
        ){
            redirect_LinkBlock(origin_node, index);
            Link_Block_Node<Value_Type>* now=origin_node;
            Link_Block_Node<Value_Type>* next=origin_node.next;
            Idx back_length=0, offset, node_length=0;

            // 寻找可用空闲空间
            while(back_length<length && now && now!=_end_node && next.prev==now && node_length<=_max_node_length){
                ++node_length;
                if(back_length+now->length-now->used_length>length){
                    offset=length-back_length;
                }else{
                    offset=now->length-now->used_length;
                }
                back_length+=offset;
                now=next;
                next=next->next;
            }
            if(back_length==0) return 0;
            
            next=now;
            
            Link_Block_Node<Value_Type> *&write=now;
            Link_Block_Node<Value_Type> *&read=next;

            Idx idx_write=write->used_length+offset, idx_read=read->used_length;
            write->used_length=idx_write;
            do{
                if(idx_write==0){
                    write=write.prev;
                    idx_write=now->length;
                    now->used_length=idx_write;
                }
                if(idx_read==0){
                    read=read.prev;
                    idx_read=now->used_length;
                }
                --idx_write;
                --idx_read;
                write->data[idx_write] = read->data[idx_read];
            }while(read==origin_node && idx_read==index);
            
            if(_out_node)  _out_node  = write;
            if(_out_index) _out_index = idx_write;
            return back_length;
        }


        template <typename Value_Type> 
        Idx rape_LinkBlock(Link_Block_Node<Value_Type>* origin_node, Idx index, Value_Type* data, Idx length, bool _flag_used, bool _reset_last_used, Link_Block_Node<Value_Type>* _end_node ){
            redirect_LinkBlock(origin_node,index);
            Link_Block_Node<Value_Type> *&now=origin_node;

            Idx offset = _flag_used ? now->used_length : now->length;
            Idx left=0, right = offset -index;

            if(right>length){
                right=length;
            }
            str::copy(data+left, data+right, now->data+index);

            while(right<length && now && now!=_end_node){
                now    = now.next;
                left   = right;
                offset = _flag_used ? now->used_length : now->length;
                right  = right>length ?length : right+offset;
                str::copy(data+left, data+right, now->data+index);
                if(right==length && !_reset_last_used) break;
                now->used_length=offset;
            }
            return right;
        }

        template <typename Value_Type> 
        void splice_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx free_length,
            Value_Type* _ex_value, Idx _ex_length, Option_Act_LinkBlock* _option, Link_Block_Node<Value_Type>* _end_node
        ){
            if(free_length<0){
                index -= free_length;
                free_length =- free_length;
            }
            if(_ex_length<0)_ex_length=0;
            Link_Block_Node<Value_Type>* now;
            redirect_LinkBlock(origin_node, index);
            
            if(free_length){
                free_length=erase_LinkBlock(now, index, free_length, _option->flag_delete_data_item, _end_node);
            }
            if((!_ex_value)||(_ex_length<1)) return; // 无插入操作
            
            if(free_length>_ex_value){
                // rape_LinkBlock(origin_node,)
                
            }

            // todo
        }
        
        
        
        /**
         * 合并块状链表
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
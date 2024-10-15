/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-10 14:28:01
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块状链表存储结构
 */

#ifndef __NML_Link_Block__
#define __NML_Link_Block__

#include "NML.hpp"

namespace NML{
    /** 
     * @brief 块状链表结构 解决方案
     * @tparam Value_Type 块状链表节点使用的数据类型
     */
    namespace Link_Block{

        /** 块状链表节点
         * @tparam Value_Type data 中的数据类型
         */
        template <typename Value_Type> 
        struct Link_Block_Node {
            /** 上一个节点 */
            Link_Block_Node<Value_Type>* prev;
            /** 下一个节点 */
            Link_Block_Node<Value_Type>* next;
            /** 当前节点的长度容量 */
            Idx length;
            /** 当前节点已使用的长度 */
            Idx used_length;
            /** 当前节点内的数据 */
            Value_Type* data;
        };

        
        /** 操作块状链表时的设置 */
        typedef struct Option_Act_LinkBlock{
            /** 腾挪空间时 向后查找空闲空间的最大寻址节点个数 */
            int find_free_max_after_node_count;
            /** 腾挪空间时 向前查找空闲空间的最大寻址节点个数 */
            int find_free_max_before_node_count;
            /** 插入操作时追加节点的数据长度, 使用 0 表示禁止自动追加节点 */
            Idx ex_link_block_length;
            /** 当擦除/覆盖时 对每个内容的进行回调操作*/
            Callback erase_callback;
        } Option_Act_LinkBlock;

        /** @brief 默认的设置操作 { 2, 2, 255, false } */
        extern Option_Act_LinkBlock _DEFAULT_LINK_BLOCK_ACT_OPTION;
        /** @brief 获取默认的设置操作(指针) { 2, 2, 255, false } */
        Option_Act_LinkBlock* get_DefaultLinkBlockActOption();

        /**
         * @brief 封装的拷贝操作
         * @param read_first                 源数据读取的起始位置
         * @param read_last                  源数据读取的结束位置
         * @param write_first                写入时的起始位置
         * @param _flag__overload_operator   表示是否有重载赋值运算符, 如果没有将会使用 std::copy
         */
        template <typename Value_Type> 
        void copy__T(Value_Type* read_first, Value_Type* read_last, Value_Type* write_first, bool _flag__overload_operator=false){
            #ifndef __LINK_BLOCK__NEVER_OVERLOAD_OPERATOR__
                if(_flag__overload_operator){
                    while (read_first != read_last) {
                        *write_first = *read_first;
                        ++read_first;
                        ++write_first;
                    }
                    write_first;
                }else{
                    std::copy(read_first,read_last,write_first);
                }
            #else
                std::copy(read_first,read_last,write_first);
            #endif
        }
        
        /**
         * @brief 新创建块状链表节点
         * @param length 节点的最大长度
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* create_LinkBlockNode(Idx _length=__DEFAULT_LINK_BLOCK_LENGTH__){ 
            Link_Block_Node<Value_Type> *rtn= new Link_Block_Node<Value_Type>; 
            rtn->prev          = 0;
            rtn->next          = 0;
            rtn->length        = _length;
            rtn->used_length   = 0;
            rtn->data          = new Value_Type[_length];
            return rtn;
        }

        
        /**
         * @brief 使用原数据创建块状链表节点
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* create_LinkBlockNode(Idx used_length, Value_Type* values, Idx _length=__DEFAULT_LINK_BLOCK_LENGTH__, bool _flag__overload_operator=false){ 
            Link_Block_Node<Value_Type> *rtn= new Link_Block_Node<Value_Type>; 
            rtn->prev          = 0;
            rtn->next          = 0;
            rtn->length        = _length?_length:used_length;
            rtn->used_length   = used_length;
            rtn->data          = new Value_Type[_length];
            copy__T(values,values+used_length,rtn->data,_flag__overload_operator);
            return rtn;
        }
        
        
        /** 
         * @brief 获取块状链表的元素
         * @param origin_node             访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset             元素在访问节点的下标偏移量, 使用负数可以向前查找
         * @param  _out_node              输出 reutrn 元素所在的节点的指针, 默认为 0 (不输出)
         * @param  _out_node_head_index   输出 reutrn 元素所在的节点的 0 元素相对于 origin_node 的下标偏移量, 默认为 0 (不输出)
         * @return 返回对应下标的内容
         * @throw  抛出 std::out_of_range 异常时表示 index 超出可用范围
         */
        template <typename Value_Type> 
        Value_Type& get_Item__LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index_offset,
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_node_head_index=0
        ){
            Idx i;
            Link_Block_Node<Value_Type> *now=origin_node;

            if(index_offset>=0){
                for(i=0; now && i+now->used_length<=index_offset;  i+=now->used_length, now=now->next);
            }else{
                for(i=0; now && i>index_offset;  i-=now->used_length, now=now->prev);
            }
            if(!now) throw std::out_of_range("using index is out of link_block's used range");
            if(now!=origin_node){
                if(_out_node_head_index)   *_out_node_head_index += i;
                if(_out_node)              *_out_node = now;
            }
            return now->data[index_offset-i];
        }

        /**
         * @brief 将节点和超出可用范围的index, 重新定位到在范围内的index和对应节点
         * @param origin_node   访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset   元素在访问节点的下标偏移量, 使用负数可以向前查找
         */
        template <typename Value_Type> 
        inline void redirect_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx& index)
        {
            if(index>origin_node->used_length||index<0){
                Idx head_index=0;
                get_Item__LinkBlock(origin_node, index, &origin_node, &head_index);
                index=index-head_index;
            }
        }


        /**
         * @brief 擦除块状链表中的一段元素
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node       起始节点
         * @param index             从第 index 个元素开始擦除
         * @param _erase_length     擦除多少个元素, 默认为 1
         * @param _out_node         输出擦除完成后的活跃节点,  默认为 0 (不输出)
         * @param _erase_callback   擦除时对每个元素调用回调
         * @return 返回删除后从起始位置到结束位置有多少空闲空间
         */
        template <typename Value_Type> 
        Idx erase_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, 
            Idx _erase_length=1, Link_Block_Node<Value_Type>** _out_node=0, Callback _erase_callback=0
        ){
            if(_erase_length<1) return 0;
            redirect_LinkBlock(origin_node, index);

            Link_Block_Node<Value_Type> *now = origin_node;

            Idx &erase_end=_erase_length,  rtn=0, i;
            erase_end=_erase_length+index;

            while(now && erase_end>now->used_length){
                if(_erase_callback){
                    for(i=index;  i<erase_end && i<now->used_length;  ++i){
                        _erase_callback((void*)&now->data[i]);
                    }
                }
                erase_end-=now->used_length;
                rtn+=now->length-index;
                now->used_length=index;
                index=0;
                now=now->next;
            }
            
            if(now) {
                std::copy(now->data+erase_end, now->data+now->used_length, now->data+index);
                now->used_length-=erase_end-index;
            }
            
            if(_out_node)*_out_node=now;
            return rtn;
        }


        /**
         * @brief 强制覆盖拷贝数据到块状链表中
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node                起始节点
         * @param index                      从第 index 个元素开始覆盖
         * @param data                       需要写入的数据
         * @param length                     需要写入的数据长度
         * @param _flag_used                 是否仅对已使用的元素 (0 ~ node.used_length) 进行覆盖, 默认为 false (完全覆盖 0 ~ node.length )
         * @param _reset_last_used           是否修改操作中最后一个节点的已使用长度, 默认为 false (不修改)
         * @param _flag__overload_operator   替换元素时是否使用重载运算符, 默认false
         * @return 返回成功写入多少元素
         */
        template <typename Value_Type> 
        Idx rape_LinkBlock(Link_Block_Node<Value_Type>* origin_node, Idx index, Value_Type* data, Idx length, bool _flag_used=false, bool _reset_last_used=false, bool _flag__overload_operator=false){
            redirect_LinkBlock(origin_node,index);
            Link_Block_Node<Value_Type> *&now=origin_node;

            Idx offset = _flag_used ? now->used_length : now->length;
            Idx left, right = offset-index, temp_used_length;

            if(right>=length){
                copy__T(data, data+length, now->data+index, _flag__overload_operator);
                if(_reset_last_used) now->used_length=length+index;
                return length;
            }

            now->used_length=offset;
            copy__T(data, data+right, now->data+index,_flag__overload_operator);
            now = now->next;

            while(right<length && now){
                left  = right;
                right = right + (_flag_used ? now->used_length : now->length);
                if(right>length) right=length;
                copy__T(data+left, data+right, now->data,_flag__overload_operator);
                temp_used_length=right-left;
                if(right==length && !_reset_last_used && now->used_length>temp_used_length) break;
                now->used_length=temp_used_length;
                now = now->next;
            }
            return right;
        }


        /**
         * @brief 向前移动数据以腾出空间
         * @param origin_node        起始节点
         * @param index              从第 index 个元素开始
         * @param offset             向前移动的长度
         * @param _out_node          输出移动后的活跃节点, 默认为0 (不输出)
         * @param _out_index         输出移动后的活跃节点尾部, 默认为0 (不输出)
         * @param _max_node_length   最大访问节点数量, 默认为 INFINITY
         * @return 返回成功移动的长度
         */
        template <typename Value_Type> 
        int shiftForward_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx offset, 
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Idx _max_node_length=__NML_IDX_INFINITY__
        ){
            redirect_LinkBlock(origin_node, index);
            Link_Block_Node<Value_Type>* now=origin_node->prev;
            Link_Block_Node<Value_Type>* next=origin_node;
            Idx shift_length=0, offset_write, node_length=0;

            // 寻找可用空闲空间
            while(shift_length<offset && now && now->next==next && node_length<_max_node_length){
                ++node_length;
                if(shift_length+now->length-now->used_length>offset){
                    offset_write=offset-shift_length;
                }else{
                    offset_write=now->length-now->used_length;
                }
                shift_length+=offset_write;
                next=now;
                now=now->prev;
            }
            if(shift_length==0) return 0;

            now=next;
            next=next->next;
            Link_Block_Node<Value_Type>*& write=now;
            Link_Block_Node<Value_Type>*& read=next;
            
            Idx idx_write=write->used_length, idx_read=0, offset_read=next->used_length;
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
            }while(!((read==origin_node) && (idx_read==index)));

            if(idx_write>=offset_write){
                idx_write=0;
                write=write->next;
            }
            if(_out_index) *_out_index=idx_write;
            if(_out_node)  *_out_node =write;
            return shift_length;
        }


        /**
         * @brief 向后移动数据以腾出空间
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node        起始节点
         * @param index              从第 index 个元素开始
         * @param offset             向后移动的长度
         * @param _out_node          输出移动后的活跃节点, 默认为0 (不输出)
         * @param _out_index         输出移动后的活跃节点第一个实际可用元素, 默认为0 (不输出)
         * @param _max_node_length   最大访问节点数量, 默认为 INFINITY
         * @return 返回 成功移动的长度
         */
        template <typename Value_Type> 
        int backOff_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx offset, 
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Idx _max_node_length=__NML_IDX_INFINITY__
        ){
            redirect_LinkBlock(origin_node, index);
            Link_Block_Node<Value_Type>* now=origin_node;
            Link_Block_Node<Value_Type>* last_node;
            Idx back_length=0, loc_offset, node_length=0;

            // 寻找可用空闲空间
            do{
                ++node_length;
                if(back_length+now->length-now->used_length>offset){
                    loc_offset=offset-back_length;
                }else{
                    loc_offset=now->length-now->used_length;
                }
                back_length+=loc_offset;
                last_node=now;
                now=now->next;
            }while(back_length<offset && now && node_length<=_max_node_length);
            if(back_length==0) return 0;
            
            now=last_node;
            Link_Block_Node<Value_Type> *&write = now;
            Link_Block_Node<Value_Type> *&read  = last_node;

            Idx idx_write=write->used_length+loc_offset, idx_read=read->used_length;
            write->used_length=idx_write;
            do{
                while(idx_write==0){
                    write=write->prev;
                    idx_write=write->length;
                    write->used_length=idx_write;
                }
                while(idx_read==0){
                    read=read->prev;
                    idx_read=read->used_length;
                }
                --idx_write;
                --idx_read;
                write->data[idx_write] = read->data[idx_read];
            }while(!(read==origin_node && idx_read<=index));
            
            if(_out_node)  *_out_node  = origin_node;
            if(_out_index) *_out_index = index;
            return back_length;
        }
        
        
        /** 插入新节点到块状链表中
         * @param node     在这个节点的后面插入新节点
         * @param length   新节点的数据长度
         * @return 返回新节点的指针
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* add_LinkBlockNode(Link_Block_Node<Value_Type>*& node, Idx length=__DEFAULT_LINK_BLOCK_LENGTH__){
            Link_Block_Node<Value_Type>* new_node = new Link_Block_Node<Value_Type>;
            new_node->data = new Value_Type[length];
            new_node->length = length;
            new_node->used_length = 0;
            new_node->next = node->next;
            new_node->prev = node;
            if(node->next) node->next->prev = new_node;
            node->next = new_node;
            return new_node;
        }


        /** 插入新节点到块状链表中
         * @param node      在这个节点的后面插入新节点
         * @param new_node  需要插入的节点
         * @return 返回新节点的指针
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* add_LinkBlockNode(Link_Block_Node<Value_Type>*& node, Link_Block_Node<Value_Type>* new_node){
            new_node->next = node->next;
            new_node->prev = node;
            if(node->next) node->next->prev = new_node;
            node->next = new_node;
            return new_node;
        }


        /**
         * @brief 移除一个节点和里面的内容
         * @param node              需要移除的节点
         * @param _erase_callback   如果存在则对每个元素执行该函数
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* remove_LinkBlockNode(Link_Block_Node<Value_Type>& node, Callback _erase_callback=0){
            if(node.prev)node.prev->next=node.next;
            if(node.next)node.next->prev=node.prev;
            if(_erase_callback){
                Idx i;
                for(i=0;  i<node->used_length;  ++i){
                    _erase_callback((void*)&node->data[i]);
                }
            }
            delete[] node.data;
            delete &node;
        }

        /**
         * 插入/替换中间部分内容
         * @param origin_node     基准位置节点, 作为 0 下标的基准
         * @param index           从哪个下标位置开始操作
         * @param erase_length    清理数据的长度
         * @param _inset_value    用于插入的数据
         * @param _inset_length   插入数据的长度
         * @param _option         用于控制插入时的行为模式的参数
         * @param _head_node      头部节点, 用于控制寻址的边界
         * @param _tail_node      尾部节点, 用于控制寻址的边界
         * @throw  抛出 std::bad_alloc 异常时表示无法分配空间
         * @throw  抛出 std::out_of_range 异常时表示 index 超出可用范围
         * @return 返回 index_0: 向后移动的长度, index_1 腾出的总长度
         */
        template <typename Value_Type> 
        Sliding_Index splice_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx erase_length,
            Value_Type* _inset_value=0, Idx _inset_length=0, Option_Act_LinkBlock* _option=0
        ){
            redirect_LinkBlock(origin_node,index);
            
            Link_Block_Node<Value_Type>* now = origin_node;

            Idx free_length__after  = erase_LinkBlock(origin_node, index, erase_length, &now);
            Idx free_length = 0;
            Idx node_length = -1;

            if(!_option) _option=get_DefaultLinkBlockActOption();

            // 向后检查空闲空间
            while(free_length__after < _inset_length  &&  now  &&  node_length < _option->find_free_max_after_node_count){
                free_length__after += now->length - now->used_length;
                now = now->next;
                ++node_length;
            }

            // 向前检查空闲空间
            node_length=0;
            now=origin_node->prev;
            free_length=free_length__after;
            while(free_length < _inset_length  &&  now  &&  node_length < _option->find_free_max_before_node_count){
                free_length += now->length - now->used_length;
                now = now->prev;
                ++node_length;
            }

            if(free_length < _inset_length){ // 可用空间不足
                if(_option->ex_link_block_length < 0) throw std::bad_alloc();
                do{
                    add_LinkBlockNode(origin_node, _option->ex_link_block_length);
                    free_length += _option->ex_link_block_length;
                    free_length__after += _option->ex_link_block_length;
                }while(free_length < _inset_length);
            }

            now = origin_node;
            free_length = _inset_length - backOff_LinkBlock(now,index,free_length__after<_inset_length?free_length__after:_inset_length);
            if(free_length>0)shiftForward_LinkBlock(now, index, free_length, &now, &index);
            
            rape_LinkBlock(now,index,_inset_value,_inset_length,false);

            return {
                free_length__after,
                free_length
            };
        }

        /**
         * @brief 合并块状链表
         * @param origin_node   起始节点的指针, 合并后会修改这个指针的值以指向新的节点
         * @param node_length   需要合并多少个节点
         * @param _min_length   当合并后的节点容量小于 _min_length 时, 使用 _min_length 作为节点的容量
         */
        template <typename Value_Type> 
        Link_Block_Node<Value_Type>* merge_LinkBlock(Link_Block_Node<Value_Type>** origin_node, Idx node_length, Idx _min_length=__DEFAULT_LINK_BLOCK_LENGTH__){
            if(node_length<=1)return *origin_node;
            Link_Block_Node<Value_Type>* prev = (*origin_node)->prev;
            Link_Block_Node<Value_Type>* now  = (*origin_node);
            Idx new_length = 0, node_index = 0;
            while(now && node_index<node_length){
                new_length += now->used_length;
                now = now->next;
                ++node_index;
            }

            Link_Block_Node<Value_Type>* new_node = new Link_Block_Node<Value_Type>;
            new_node->length = new_length<_min_length?_min_length:new_length;
            new_node->used_length = new_length;
            new_node->data = new Value_Type[new_length];
            node_index = new_length = 0;
            now = (*origin_node);
            while(now && node_index<node_length){
                std::copy(now->data, now->data+now->used_length, new_node->data+new_length);
                ++node_index;
                new_length+=now->used_length;
                now=now->next;
                if(now && now->prev){
                    delete[] now->prev->data;
                    delete now->prev;
                }
            }
            new_node->next=now;
            if(now) now->prev=new_node;
            if(prev){
                prev->next=new_node;
                new_node->prev=prev;
            }else{
                *origin_node=new_node;
                new_node->prev=0;
            }
            
            return new_node;
        }
        

        /** 
         * @brief 释放/销毁 后段块状链表
         * @param header_node 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         * @param _erase_callback  如果存在则对每个数据元素执行 _erase_callback
         */
        template <typename Value_Type> 
        void free_LinkBlock(Link_Block_Node<Value_Type>* header_node, Callback _erase_callback=0){
            Link_Block_Node<Value_Type> *now=header_node, *temp;
            Idx i;

            while(now){
                if(_erase_callback){
                    for(i=0;  i<now->used_length;  ++i){
                        _erase_callback((void*)&now->data[i]);
                    }
                }
                temp=now;
                now=now->next;
                delete temp;
            }
        }


        /** 
         * @brief 计算整段块状链表的最大容量
         * @param header_block 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         */
        template <typename Value_Type> 
        Idx calc_UsedLength(Link_Block_Node<Value_Type>*& head_node, Link_Block_Node<Value_Type>** _out_end_node){
            Idx rtn=0;
            Link_Block_Node<Value_Type> *now_node=head_node;
            do{
                rtn+=now_node->used_length;
            }while(now_node->next && (now_node->next!=head_node) && ((now_node=now_node->next),1));
            if(_out_end_node)*_out_end_node=now_node;
            
            return rtn;
        }


        /** 
         * @brief 计算整段块状链表的最大容量
         * @param header_block 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         */
        template <typename Value_Type> 
        Idx calc_MaxLength(Link_Block_Node<Value_Type>*& head_node, Link_Block_Node<Value_Type>** _out_end_node){
            Idx rtn=0;
            Link_Block_Node<Value_Type> *now_node=head_node;
            do{
                rtn+=now_node->length;
            }while((now_node->next && (now_node->next!=head_node)) && ((now_node=now_node->next),1));
            if(_out_end_node)*_out_end_node=now_node;
            
            return rtn;
        }


        /** 
         * @brief 链表节点的数量
         * @param header_block 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         */
        template <typename Value_Type> 
        Idx calc_NodeLength(Link_Block_Node<Value_Type>*& head_node, Link_Block_Node<Value_Type>** _out_end_node){
            Idx rtn=0;
            Link_Block_Node<Value_Type> *now_node=head_node;
            do{
                ++rtn;
            }while((now_node->next && (now_node->next!=head_node)) && ((now_node=now_node->next),1));
            if(_out_end_node)*_out_end_node=now_node;
            
            return rtn;
        }


        /**
         * 输出块状链表内容 (打印用)
         * @param head_code 头部节点
         * @param os 输出通道 默认为 std::cout
         */
        template <typename T>
        void out_LinkBlock(Link_Block_Node<T>* head_node, std::ostream* os=&std::cout){
            Idx i;
            Link_Block_Node<T>* now_node=head_node;
            (*os) << "[";
            do{
                i=0;
                while(i<now_node->used_length){
                    (*os) << now_node->data[i] << ",";
                    ++i;
                }
                now_node=now_node->next;
            }while(now_node && now_node!=head_node);
            (*os) << "\b]";
        }


        /**
         * @brief 遍历链表使用的回调函数类型
         * @param value        当前值
         * @param index        当期下标
         * @param node         当前节点
         * @param index_node   相对于当前节点的下标
         */
        template<typename Value_Type>
        using Callback__through_LinkBlock = void (*)(Value_Type, Idx, Link_Block_Node<Value_Type>*, Idx);


        /**
         * @brief 取出块状链表的内容
         * @param  out                       输出位置
         * @param  origin_node               入口节点
         * @param  _read_start_index         初始下标
         * @param  _max_length               最大读取长度
         * @param _flag__overload_operator   替换元素时是否使用重载运算符, 默认false
         * @return 返回输出长度
         */
        template<typename Value_Type>
        Idx load_LinkBlockData(
            Value_Type* out,Link_Block_Node<Value_Type>* origin_node,
            Idx _read_start_index=0, Idx _max_length=INFINITY, bool _flag__overload_operator=false
        ){
            Link_Block_Node<Value_Type>*& now=origin_node;
            redirect_LinkBlock(now,_read_start_index);
            Idx i=now->used_length-_read_start_index;
            if(i>_max_length) i=_max_length;

            copy__T(now->data+_read_start_index, now->data+_read_start_index+i,out,_flag__overload_operator);

            for(now=now->next; now; now=now->next){
                copy__T(now->data, now->data+now->used_length, out+i, _flag__overload_operator);
                i+=now->used_length;
                now=now->next;
                if(i+now->used_length>_max_length){
                    copy__T(now->data, now->data+_max_length-i, out+i, _flag__overload_operator);
                    i=_max_length;
                    break;
                }
            }
            return i;
        }

        
        /**
         * @brief 读块状链表的内容到另一个块状链表
         * @param  out                  输出位置
         * @param  origin_node          入口节点
         * @param  _read_start_index    初始下标
         * @param  _max_length          最大读取长度
         * @param  _write_start_index   初始写入下标 (相对于out)
         * @param  _new_node_length     当 out 不足以存放内容时, 新增节点的数据长度
         * @return 返回输出长度
         */
        template<typename Value_Type>
        Idx copy_LinkBlockData(
            Link_Block_Node<Value_Type>* out,Link_Block_Node<Value_Type>* origin_node, 
            Idx _read_start_index=0, Idx _max_length=INFINITY, Idx _write_start_index=0, Idx _new_node_length=__DEFAULT_LINK_BLOCK_LENGTH__
        ){
            redirect_LinkBlock(origin_node,_read_start_index);

            Idx rtn=0;
            Link_Block_Node<Value_Type>*& read=origin_node;
            Idx &i_r = _read_start_index;
            Idx &i_w = _write_start_index;
            while(read && rtn<_max_length){
                out->data[i_w] = read->data[i_r];

                ++i_r;   ++i_w;   ++rtn;
                
                if(i_r > read->used_length){
                    read=read->next;
                    i_r=0;
                }
                if(i_w > out->length){
                    if(!out->next) add_LinkBlockNode(out,_new_node_length);
                    out = out->next;
                    i_w=0;
                }
            }
            return rtn;
        }


        /**
         * @brief 在链表中追加元素
         * @param target             目标链表
         * @param items              追加的元素值
         * @param _write_length      追加的个数 默认为1
         * @param _new_node_length   当目标无可用空间时, 新增的节点长度 <=0 表示禁止增加节点
         * @throw 无可用空间且禁止增加节点 抛出 std::bad_alloc 
         * @return 返回新增了多少个节点
         */
        template <typename Value_Type> 
        Idx push_LinkBlockItems(Link_Block_Node<Value_Type>* target, Value_Type* items, Idx _write_length=1, Idx _new_node_length=__DEFAULT_LINK_BLOCK_LENGTH__){
            Idx i=0, count_add=0;

            while(target->next) target=target->next;
            while(target->used_length==0 && target->prev && (target->prev->used_length < target->prev->length)) target = target->prev;

            while(i<_write_length){
                while(target->used_length >= target->length){
                    if(target->next){
                        target=target->next;
                    }else{
                        if(_new_node_length<=0) throw std::bad_alloc();
                        target = add_LinkBlockNode(target,_new_node_length);
                        ++count_add;
                    }
                }
                target->data[target->used_length] = items[i];
                ++target->used_length;
                ++i;
            }

            return count_add;
        }

        
        /**
         * @brief 在链表中追加元素
         * @param target             目标链表
         * @param item               追加的元素值
         * @param _new_node_length   当目标无可用空间时, 新增的节点长度 <=0 表示禁止增加节点
         * @throw 无可用空间且禁止增加节点 抛出 std::bad_alloc 
         * @return 返回新增了多少个节点
         */
        template <typename Value_Type> 
        Idx push_LinkBlockItem(Link_Block_Node<Value_Type>* target, Value_Type item, Idx _new_node_length=__DEFAULT_LINK_BLOCK_LENGTH__){
            while(target->next) target=target->next;
            while(target->used_length==0 && target->prev && (target->prev->used_length < target->prev->length)) target = target->prev;

            if(target->used_length >= target->length){
                if(_new_node_length<=0) throw std::bad_alloc();
                target = add_LinkBlockNode(target,_new_node_length);
                target->data[target->used_length] = item;
                ++target->used_length;
                return 1;
            }
            target->data[target->used_length] = item;
            ++target->used_length;
            return 0;
        }

        /**
         * @brief 从尾部开始移除元素
         * @param target            访问链表的入口节点
         * @param length            要移除的长度
         * @param _erase_callback   擦除时对每个元素调用回调
         * @return 返回实际成功擦除了多少个元素
         */
        template <typename Value_Type> 
        Idx remove_LinkBlockEndItems(Link_Block_Node<Value_Type>* target, Idx length, Callback _erase_callback=0){
            while(target->next) target=target->next;

            Idx i=0;

            if(_erase_callback){
                while(i<length){
                    while(target->used_length<=0){
                        target=target->prev;
                    }
                    if(!target) break;
                    --target->used_length;
                    ++i;
                    _erase_callback(&target->data[target->used_length]);
                }
            }else{
                while(length>0 && target){
                    if(target->used_length>length){
                        target->used_length-=length;
                        length=0;
                        i+=length;
                    }else{
                        length-=target->used_length;
                        i+=target->used_length;
                        target->used_length=0;
                        target=target->prev;
                    }
                }
            }
            return i;
        }

        /**
         * @brief 从尾部开始移除元素
         * @param target            访问链表的入口节点
         * @param _erase_callback   擦除时对每个元素调用回调
         * @return 返回实际成功擦除了多少个元素
         */
        template <typename Value_Type> 
        Idx remove_LinkBlockEndItem(Link_Block_Node<Value_Type>* target, Callback _erase_callback=0){
            while(target->next) target=target->next;
            while(target->used_length<=0 && target->prev && target->prev->used_length>0 ) target = target->prev;
            if(target->used_length<=0) return 0;
            if(_erase_callback) _erase_callback(target->data[target->used_length]);
            --target->used_length;
            return 1;
        }


        /**
         * @brief 遍历链表运行某个函数
         * @param origin_node     访问的入口节点
         * @param callback        回调函数, 参数见 Callback__through_LinkBlock
         * @param _start_index    遍历时 相对于 origin_node 位置的 初始下标, 默认 0
         * @param _max_length     遍历时 最大访问次数, 默认 INFINITY
         */
        template <typename Value_Type, typename Callback> 
        void through_LinkBlock(Link_Block_Node<Value_Type>* origin_node, Callback callback, Idx _start_index=0, Idx _max_length=INFINITY){
            Link_Block_Node<Value_Type>*& now=origin_node;
            Idx i=0, &index=_start_index, index_now=_start_index;
            rape_LinkBlock(now,index);
            while(now&&i<_max_length){
                callback(now->data[index],index,now,index_now);
                ++index;
                ++index_now;
                if(now->used_length>=index_now){
                    now=now->next;
                    index_now=0;
                }
            }
        }


        template <typename Value_Type> 
        class Link_Block_Ctrl{

            using Node =  Link_Block_Node<Value_Type>;

            private:
            /** 设置的操作参数 */
            Option_Act_LinkBlock *_option;

            public:
            /** 头部节点指针 */
            Node *head_node;
            /** 尾部节点指针 */
            Node *end_node;
            /** 浮动指针 指向链表中上次访问的节点, 用于加速访问 */
            Node *origin_node;
            /** 浮动指针节点的 0 位置,  */
            Idx origin_index__item;
            /** 最大长度 */
            Idx max_length;
            /** 已经被使用的长度 */
            Idx used_length;
            /** 节点长度 */
            Idx node_length;

            /** @brief 对一个已有的链表节点创建控制器 */
            Link_Block_Ctrl(Node* head_node, Option_Act_LinkBlock* _option=0):
            _option(_option),
            head_node(head_node),
            origin_node(head_node),
            origin_index__item(0)
            {
                reload_Length();
            }

            /**
             * @brief 使用一个长度初始化头节点
             * @param _init_length 初始化时提供的初始空间长度
             */
            Link_Block_Ctrl(Idx _init_length=__DEFAULT_LINK_BLOCK_LENGTH__):
                _option(0),
                origin_node(0),
                origin_index__item(0),
                max_length(_init_length),
                used_length(0),
                node_length(1)
            {
                head_node = end_node = create_LinkBlockNode<Value_Type>(_init_length);
            }

            /**
             * @brief 使用一个配置对象进行初始化
             * @throw 抛出 std::bad_alloc 表示使用了不能正常创建节点的配置
             */
            Link_Block_Ctrl(Option_Act_LinkBlock* option):
                _option(option),
                origin_node(0),
                origin_index__item(0),
                max_length(option->ex_link_block_length),
                used_length(0),
                node_length(1)
            {
                Option_Act_LinkBlock* p_option = get_Option();
                if(p_option->ex_link_block_length<=0) throw std::bad_alloc();
                head_node = end_node = create_LinkBlockNode<Value_Type>(p_option->ex_link_block_length);
            }


            /** @brief 拷贝链表, 新链表的每块长度为 option 设置的最大长度 或 总数据长度*/
            Link_Block_Ctrl(Link_Block_Ctrl<Value_Type>*& link_block, Option_Act_LinkBlock* _option=0):
                _option(_option), 
                origin_index__item(0), 
                used_length(link_block->used_length),
                head_node(0),
                end_node(0),
                origin_node(0)
            {
                Option_Act_LinkBlock* option=get_Option();
                copy_LinkBlockData(head_node, link_block, 0, INFINITY, 0, option->ex_link_block_length);
            };

            ~Link_Block_Ctrl(){
                free_LinkBlock(head_node,get_Option()->erase_callback);
            }

            void add_Node(Node*& node){
                node_length++;
                max_length  += node->length;
                used_length += node->used_length;
                end_node->next = node;
                node->prev = end_node;
                end_node   = node;
            }

            
            void add_Node(Idx length){
                Node* node = create_LinkBlockNode<Value_Type>(length);
                add_Node(node);
            }

            /**
             * 在尾部增加元素
             * @param items     需要添加的元素集合
             * @param _length   需要添加的长度
             */
            void push_Items(Value_Type* items, Idx _length=1){
                Option_Act_LinkBlock* option = get_Option();
                Idx add_node_length=push_LinkBlockItems(end_node,items,_length,option->ex_link_block_length);
                used_length += _length;
                max_length  += add_node_length * option->ex_link_block_length;
                while(end_node->next) end_node = end_node->next;
                node_length += add_node_length;
            }
             

             /**
              * 在尾部增加元素
              * @param item 需要添加的元素
              */
            void push_Item(Value_Type item){
                Option_Act_LinkBlock* option = get_Option();
                Idx add_node_length=push_LinkBlockItem(end_node,item,option->ex_link_block_length);
                ++used_length;
                if(add_node_length){
                    max_length += option->ex_link_block_length;
                    end_node=end_node->next;
                    ++node_length;
                }
            }


            /**
             * 从尾部移除元素
             * @param length 要移除的长度
             * @return 返回实际成功擦除了多少个元素
             */
            Idx remove_EndItems(Idx length){
                Option_Act_LinkBlock* option= get_Option();
                return remove_LinkBlockEndItems(end_node, length, option->erase_callback);
            }
            

            /**
             * 从尾部移除一个元素
             * @return 返回实际成功擦除了多少个元素
             */
            Idx remove_EndItem(){
                Option_Act_LinkBlock* option= get_Option();
                return remove_LinkBlockEndItem(end_node, option->erase_callback);
            }


            /** @brief 取用设置对象 */
            Option_Act_LinkBlock* get_Option(){
                if(_option) return _option;
                return get_DefaultLinkBlockActOption();
            }

            /** 
             * @brief 存入设置对象
             * @param new_option      存入的新设置对象
             * @param _delete_flag     是否对旧 new_option 执行 delete 
             */
            void set_Option(Option_Act_LinkBlock* new_option, bool _delete_flag=false){
                if(_delete_flag) delete _option;
                _option=new_option;
            }


            Node* get_Node(int node_index, Node** out__prev_to_tgt=0, Node** out__next_to_tgt=0){
                if(!node_index){
                    if(out__next_to_tgt) out__next_to_tgt = &(head_node->next->prev);
                    return head_node;
                }
                int i=0;
                Node* node=head_node;
                do{
                    node=node->next;
                    ++i;
                }while(i<node_index);

                if(out__prev_to_tgt) out__prev_to_tgt = &(node->prev->next);
                if(out__next_to_tgt) out__next_to_tgt = &(node->next->prev);

                return node;
            }


            /** 
             * @brief 使用下标获取元素
             * @param index 下标
             * @param _use_cache_index 是否使用并更新缓存索引, 默认为 true
             * @return 返回对应下标的元素的引用
             */
            Value_Type& get_Item(int index, bool _use_cache_index=true){
                if(!_use_cache_index){
                    if(index<0)   return get_Item__LinkBlock(end_node, index - end_node->used_length);
                    else          return get_Item__LinkBlock(head_node,index);
                }
                if(index<0) index+=used_length;
                Idx _index=index-origin_index__item;
                if((!origin_node) || (index<origin_index__item && index<(-_index)) ){
                    _index=index;
                    origin_node=head_node;
                    origin_index__item=0;
                }
                return get_Item__LinkBlock(origin_node, _index, &origin_node, &origin_index__item);
            }

            /**
             * 重置 缓存访问指针 origin_node 到头部
             */
            void reset_origin(){
                origin_node=head_node;
                origin_index__item=0;
            }
            
            /** 
             * @brief 使用下标获取元素
             * @param index 下标
             * @return 返回对应下标的元素的引用
             */
            Value_Type& operator[](int index){return get_Item(index);}

            /**
             * @brief 替换内容
             * @param op_index        下标
             * @param erase_length    擦除原数据的长度
             * @param inset_data      需要插入的数据
             * @param length          插入数据的长度
             */
            void splice(Idx op_index, Idx erase_length, Value_Type* _inset_data=0, Idx _inset_length=0){
                if(op_index<0) op_index = used_length + op_index;
                get_Item(op_index);
                Sliding_Index afert_length=splice_LinkBlock(origin_node,op_index-origin_index__item,erase_length, _inset_data, _inset_length, _option);
                if(afert_length.index_1-afert_length.index_0>0){
                    reset_origin();
                }
                if(afert_length.index_1>_inset_length){
                    reload_Length();
                }else{
                    this->used_length+=_inset_length-erase_length;
                }
            }

            /**
             * @brief 替换内容
             * @param op_index        下标
             * @param erase_length    擦除原数据的长度
             * @param inset_data      需要插入的数据
             * @param length          插入数据的长度
             */
            inline void splice(Idx op_index, Idx erase_length, Node& inset_data){
                splice(op_index,erase_length, inset_data.data, inset_data.used_length);
            }

            /**
             * @brief 重新加载链表的 节点长度/ 最大可用长度 / 已使用长度
             */
            void reload_Length(){
                node_length = 0;
                used_length = 0;
                max_length  = 0;
                end_node=head_node;
                do{
                    ++node_length;
                    max_length  = end_node->length;
                    used_length = end_node->used_length;
                }while((end_node->next && (end_node->next!=head_node)) && ((end_node=end_node->next),1));
            }
            
            /**
             * 用于输出内容
             */
            friend std::ostream& operator<<(std::ostream& os, const Link_Block_Ctrl& link_block) {
                out_LinkBlock(link_block.head_node, &os);
                return os;
            }

            /**
             * 直接设置使用长度
             */
            void set_UsedLength(Idx new_length){
                Idx l=new_length-used_length;
                if(used_length<new_length){
                    Value_Type init_data=new Value_Type[l];
                    push_Items(init_data,l);
                    delete[] init_data;
                }else{
                    remove_EndItems(-l);
                }
            }
            
        };


        /**
         * @brief 物理块状链表存储的点访问器
         */
        class Points_Iterator__LinkBlock :virtual public Points_Iterator{
            /** 点访问器中使用的 块状链表控制器 数据类型 */
            using LBC = Link_Block_Ctrl<var>;
            /** 点访问器中使用的 块状链表节点 数据类型 */
            using LBN = Link_Block_Node<var>;

            public:

            /** 
             * @brief 接管一个链表数据建立点访问器
             * @param data 已有的链表数据
             * @param dimensional 维度
             */
            Points_Iterator__LinkBlock(LBC* data, Idx_Algebra dimensional):Points_Iterator(data, dimensional, 0){
                points_length=calc_UsedPointsLength();
            }

            /** 
             * @brief 拷贝构造函数
             * @param copy_obj 原数据对象
             */
            Points_Iterator__LinkBlock(Points_Iterator& copy_obj):Points_Iterator(copy_obj){}

            /**
             * @brief 初始化长度的数据
             * @param dimensional   维度
             * @param points_length 点的个数
             */
            Points_Iterator__LinkBlock(Idx_Algebra dimensional, Idx points_length):Points_Iterator(dimensional, points_length){
                data=0;
                install_Data(dimensional, points_length);
            }

            ~Points_Iterator__LinkBlock(){free_Data();}

            /**
             * @brief 装配 new data (初始化分配数据)
             * @param dimensional   维度
             * @param points_length 点的个数
             */
            void install_Data(Idx_Algebra dimensional, Idx points_length) override{ 
                if(data) free_Data();
                Idx l = dimensional*points_length;
                data = new LBC(l); 
                ((LBC*)data)->used_length  =  ((LBC*)data)->head_node->used_length  =  l;
                this->dimensional   = dimensional;
                this->points_length = points_length;
            }
            
            void free_Data(){delete (LBC*)data; data=0;}

            var* operator[](Idx v) override{
                LBC* d = (LBC*)data;
                return &d->get_Item(v*dimensional);
            }

            /**
             * @brief 设置链表配置
             * @param option 新的配置
             */
            void set_Option(Option_Act_LinkBlock* option){
                LBC* d = (LBC*)data;
                d->set_Option(option);
            }
            
            /**
             * @brief 获取链表配置
             * @return 返回当前 data 中使用的配置
             */
            Option_Act_LinkBlock* get_Option(){
                LBC* d = (LBC*)data;
                return d->get_Option();
            }

            /**
             * @brief 计算当前 data 链表中已使用的数据有多少个点
             * @return 遍历节点以计算结果
             */
            Idx calc_UsedPointsLength();
            
            /**
             * @brief 计算当前 data 链表中最大可用多少个点
             * @return 遍历节点以计算结果
             */
            Idx calc_PointsLength();
            
            /** 设置 维度 */
            void set_Dimensional(Idx_Algebra new_dimensional, bool reset_data=true) override{
                dimensional = new_dimensional;
                if(reset_data)settle_Values();
                points_length = calc_UsedPointsLength();
            }

            /** 设置 点的个数 */
            void set_PointsLength(Idx new_points_length, bool reset_data=true) override;

            /** 
             * @brief 整理内容并尝试合并链表数据节点
             * @param critical_value 当节点长度小于临界点时, 向后合并节点, 默认为 get_Option()->ex_link_block_length/2
             */
            void settle_Values(Idx critical_value=0);
        };

    }
}

#endif
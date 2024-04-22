/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-19 17:34:21
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块状链表存储结构
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NML_Link_Block__
#define __NML_Link_Block__

#include "NML.hpp"

#ifndef __DEFAULT_LINK_BLOCK_SIZE__
    /** @brief 创建块状链表存储的默认单块长度 size */
    #define __DEFAULT_LINK_BLOCK_SIZE__ 256
#endif

#ifndef __MAX_LINK_BLOCK_SIZE__
    /** @brief 创建块状链表存储的单块最大 size */
    #define __MAX_LINK_BLOCK_SIZE__ 65536
#endif


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
            /** 当擦除/覆盖时 是否对每个内容 delete*/
            bool flag_delete_data_item;
        } Option_Act_LinkBlock;

        /** @brief 默认的设置操作 { 2, 2, 255, false } */
        extern Option_Act_LinkBlock _DEFAULT_LINK_BLOCK_ACT_OPTION;
        /** @brief 默认的设置操作(指针) { 2, 2, 255, false } */
        extern Option_Act_LinkBlock *DEFAULT_LINK_BLOCK_ACT_OPTION;
        /** @brief 获取默认的设置操作(指针) { 2, 2, 255, false } */
        inline Option_Act_LinkBlock* get_DefaultLinkBlockActOption(){return DEFAULT_LINK_BLOCK_ACT_OPTION;}

        
        /**
         * @brief 新创建块状链表节点
         * @param length 节点的最大长度
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* create_LinkBlockNode(Idx _length=__DEFAULT_LINK_BLOCK_SIZE__){ 
            Link_Block_Node<Value_Type> *rtn= new Link_Block_Node<Value_Type>; 
            rtn->prev          = 0;
            rtn->next          = 0;
            rtn->length        = _length;
            rtn->used_length   = 0;
            rtn->data          = new Value_Type(_length);
            return rtn;
        }

        
        /**
         * @brief 使用原数据创建块状链表节点
         * 
         */
        template <typename Value_Type> 
        inline Link_Block_Node<Value_Type>* create_LinkBlockNode(Idx used_length, Value_Type* value, Idx _length=0){ 
            return new Link_Block_Node<Value_Type>; 
            Link_Block_Node<Value_Type> *rtn= new Link_Block_Node<Value_Type>; 
            rtn->prev          = 0;
            rtn->next          = 0;
            rtn->length        = _length||used_length;
            rtn->used_length   = used_length;
            rtn->data          = value;
            return rtn;
        }
        
        /** 
         * @brief 获取块状链表的元素
         * @param origin_node             访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset             元素在访问节点的下标偏移量, 使用负数可以向前查找
         * @param  _out_node              输出 reutrn 元素所在的节点的指针, 默认为 0 (不输出)
         * @param  _out_node_head_index   输出 reutrn 元素所在的节点的 0 元素相对于 origin_node 的下标偏移量, 默认为 0 (不输出)
         * @return 返回对应下标的内容
         * @throw 当下标无法找到对应位置时, throw index;
         */
        template <typename Value_Type> 
        Value_Type& get_Item__LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index_offset,
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_node_head_index=0
        ){
            Idx i;
            Link_Block_Node<Value_Type> *now=origin_node;

            if(index_offset>=0){
                for(i=0;  i+now->used_length<index_offset;  i+=now->used_length, now=now->next) 
                    if(!now) throw index_offset;
            }else{
                for(i=0;  i>index_offset;  i-=now->used_length, now=now->prev) 
                    if(!now) throw index_offset;
            }
            if(_out_node_head_index) *_out_node_head_index=index_offset-i;
            if(_out_node) *_out_node=now;
            return now->data[index_offset-i];
        }
        

        /**
         * @brief 将节点和超出可用范围的index, 重新定位到在范围内的index和对应节点
         * @param origin_node   访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset   元素在访问节点的下标偏移量, 使用负数可以向前查找
         */
        template <typename Value_Type> 
        inline void redirect_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx& index){ if(index>origin_node->used_length||index<0) get_Item__LinkBlock(origin_node, index, &origin_node, &index); }


        /**
         * @brief 擦除块状链表中的一段元素
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node              起始节点
         * @param index                    从第 index 个元素开始擦除
         * @param _erase_length            擦除多少个元素, 默认为 1
         * @param _flag_delete_data_item   是否对每个元素执行 delete, 默认为 false接结束擦除行为, 默认为 0 (循环链表时应为头节点)
         * @param _out_node                输出擦除完成后的活跃节点,  默认为 0 (不输出)
         * @return 返回删除后从起始位置到结束位置有多少空闲空间
         */
        template <typename Value_Type> 
        Idx erase_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, 
            Idx _erase_length=1, Link_Block_Node<Value_Type>** _out_node=0
        ){
            if(_erase_length<1) return 0;
            redirect_LinkBlock(origin_node, index);

            Link_Block_Node<Value_Type> *now = origin_node;

            Idx &erase_end=_erase_length,  rtn=0;
            erase_end=_erase_length+index;

            while(now && erase_end>now->used_length){
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
         * @param origin_node        起始节点
         * @param index              从第 index 个元素开始覆盖
         * @param data               需要写入的数据
         * @param length             需要写入的数据长度
         * @param _flag_used         是否仅对已使用的元素 (0 ~ node.used_length) 进行覆盖, 默认为 false (完全覆盖 0 ~ node.length )
         * @param _reset_last_used   是否修改操作中最后一个节点的已使用长度, 默认为 false (不修改)
         * @return 返回成功写入多少元素
         */
        template <typename Value_Type> 
        Idx rape_LinkBlock(Link_Block_Node<Value_Type>* origin_node, Idx index, Value_Type* data, Idx length, bool _flag_used=false, bool _reset_last_used=false){
            redirect_LinkBlock(origin_node,index);
            Link_Block_Node<Value_Type> *&now=origin_node;

            Idx offset = _flag_used ? now->used_length : now->length;
            Idx left=0, right = offset -index;

            if(right>length){
                right=length;
            }
            std::copy(data+left, data+right, now->data+index);
            if( right<length || _reset_last_used) now->used_length=offset;

            now = now->next;

            while(right<length && now){
                left  = right;
                right = right + (_flag_used ? now->used_length : now->length);
                if(right>length) right=length;
                std::copy(data+left, data+right, now->data);
                if(right==length && !_reset_last_used) break;
                now->used_length=right-left;
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
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Idx _max_node_length=INFINITY
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

            if(_out_index) *_out_index=idx_write;
            if(_out_node) *_out_node=write;
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
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Idx _max_node_length=INFINITY
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
            Link_Block_Node<Value_Type> *&write=now;
            Link_Block_Node<Value_Type> *&read=last_node;

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
            }while(!(read==origin_node && idx_read==index));
            
            if(_out_node)  *_out_node  = origin_node;
            if(_out_index) *_out_index = index;
            return back_length;
        }
        

        /**
         * 插入/替换中间部分内容
         * @param origin_node   基准位置节点, 作为 0 下标的基准
         * @param index         从哪个下标位置开始操作
         * @param free_length   清理数据的长度
         * @param _ex_value     用于插入的数据
         * @param _ex_length    插入数据的长度
         * @param _option       用于控制插入时的行为模式的参数
         * @param _head_node    头部节点, 用于控制寻址的边界
         * @param _tail_node    尾部节点, 用于控制寻址的边界
         */
        template <typename Value_Type> 
        void splice_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx free_length,
            Value_Type* _ex_value=0, Idx _ex_length=0, Option_Act_LinkBlock* _option=DEFAULT_LINK_BLOCK_ACT_OPTION, Link_Block_Node<Value_Type>* _head_node=0, Link_Block_Node<Value_Type>* _tail_node=0
        ){
            if(free_length<0){
                index -= free_length;
                free_length =- free_length;
            }
            if(_ex_length<0)_ex_length=0;
            Link_Block_Node<Value_Type> *now=origin_node;
            Link_Block_Node<Value_Type> *erase_node;
            Link_Block_Node<Value_Type> *left_node, *right_node;
            redirect_LinkBlock(origin_node, index);
            
            if(free_length){
                free_length=erase_LinkBlock(now, index, free_length, _option->flag_delete_data_item);
            }
            if((!_ex_value)||(_ex_length<1)){  // 无插入操作
                return;
            }
            
            Idx left_index, right_index, back_off_length;
            
            free_length = backOff_LinkBlock(now, index, _ex_length, &right_node, &right_index, _option->find_free_max_after_node_count);

            if(free_length>_ex_value){
                rape_LinkBlock(now,index,_ex_value, _ex_length, false, true);
            }

            free_length += shiftForward_LinkBlock(now,index,_ex_length-free_length,0,0);

            if(free_length>_ex_value){
                rape_LinkBlock(now,index,_ex_value, _ex_length, false, true);
            }

        }


        /**
         * @brief 合并块状链表
         * @param origin_node   起始节点
         * @param node_length   需要合并多少个节点
         * @param _min_length   当合并后的节点容量小于 _min_length 时, 使用 _min_length 作为节点的容量
         */
        template <typename Value_Type> 
        Link_Block_Node<Value_Type>* merge_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx node_length, Idx _min_length=__DEFAULT_LINK_BLOCK_SIZE__);
        

        /** 
         * @brief 释放/销毁 后段块状链表
         * @param header_node 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         * @param _flag_delete_data_item 是否对每个数据元素执行 delete 关键字, 默认 false
         * @param _erase_callback  是否对每个数据元素执行 _erase_callback
         */
        template <typename Value_Type> 
        void free_LinkBlock(Link_Block_Node<Value_Type>* header_node,bool _flag_delete_data_item=false, Callback _erase_callback=0){
            Link_Block_Node<Value_Type> *now=header_node, *temp;
            Idx i;

            while(now){
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
         * 输出块状链表内容
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
                    (*os) << now_node->data[i];
                    ++i;
                    (*os) << ",";
                }
                now_node=now_node->next;
            }while(now_node && now_node!=head_node);
            (*os) << "\b]";
        }


        template <typename Value_Type> 
        class Link_Block_Ctrl{

            private:
            /** 设置的操作参数 */
            Option_Act_LinkBlock *_option;

            public:
            /** 头部节点指针 */
            Link_Block_Node<Value_Type> *head_node;
            /** 尾部节点指针 */
            Link_Block_Node<Value_Type> *end_node;
            /** 浮动指针 指向链表中上次访问的节点, 用于加速访问 */
            Link_Block_Node<Value_Type> *origin_node;
            /** 浮动指针节点的 0 位置,  */
            Idx origin_index__item;
            /** 浮动指针指向第几个节点 */
            Idx origin_index__node;
            /** 最大长度 */
            Idx max_length;
            /** 已经被使用的长度 */
            Idx used_length;
            /** 节点长度 */
            Idx node_length;

            /** @brief 对一个已有的链表节点创建控制器 */
            Link_Block_Ctrl(Link_Block_Node<Value_Type>* head_node, Option_Act_LinkBlock* _option=0):
            _option(_option),
            head_node(head_node),
            origin_node(head_node),
            origin_index__item(0),
            origin_index__node(0)
            {
                reload_Length(); 
            }

            /** @brief 创建一个新链表 */
            Link_Block_Ctrl(Idx _length=__DEFAULT_LINK_BLOCK_SIZE__, Option_Act_LinkBlock* _option=0){
                end_node =origin_node=head_node=new Link_Block_Node<Value_Type>{ 0, 0, _length, 0, new Value_Type(_length) };

                origin_index__item = origin_index__node = used_length=0;
                max_length=_length;
            };

            void add_Node(Link_Block_Node<Value_Type>* node){
                node_length++;
                max_length  += node->length;
                used_length += node->used_length;
                end_node->next = node;
                node->prev = end_node;
                end_node   = node;
            }

            
            void add_Node(Idx length){
                Link_Block_Node<Value_Type>* node = create_LinkBlockNode<Value_Type>(length);
                node_length++;
                max_length  += node->length;
                used_length += node->used_length;
                end_node->next = node;
                node->prev = end_node;
                end_node   = node;
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


            /** 
             * @brief 使用下标获取元素
             * @param index 下标
             * @return 返回对应下标的元素的引用
             */
            Value_Type& get_Item(int index){
                if(index<0) index+=used_length;
                Idx i=index-origin_index__item;
                if(index<origin_index__item && index<(-i)){
                    i=index;
                    origin_node=head_node;
                }
                return get_Item__LinkBlock(origin_node, i, &origin_node, &origin_index__item);
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
             * @param delete_length   插入的数据
             * @param inset_data      插入的数据
             * @param length          插入的数据
             * @param _out_address    将 op_index ~ op_index+delete_length 内容复制到输出位置
             */
            void splice(Idx op_index, Idx delete_length, Value_Type* inset_data, Idx length, Value_Type* _out_address=0);

            /**
             * @brief 替换内容
             * @param op_index        下标
             * @param delete_length   插入的数据
             * @param inset_data      插入的数据
             * @param length          插入的数据
             * @param _out_address    将 op_index ~ op_index+delete_length 内容复制到输出位置
             */
            void splice(Idx op_index, Idx delete_length, Link_Block_Node<Value_Type> inset_data, Value_Type* _out_address=0);

            /**
             * @brief 重新计算链表的长度
             */
            void reload_Length(){
                used_length = calc_UsedLength (head_node, &end_node);
                max_length  = calc_MaxLength  (head_node, &end_node);
            }
            
            /**
             * 用于输出内容
             */
            friend std::ostream& operator<<(std::ostream& os, const Link_Block_Ctrl& link_block) {
                out_LinkBlock(link_block.head_node, &os);
                return os;
            }
            
        };



    }
}

#endif
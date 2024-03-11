/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-07 15:20:13
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块链存储结构
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NML_Link_Block__
#define __NML_Link_Block__

#ifndef __MIN_LINK_BLOCK_SIZE__
    /** @brief 创建块链存储的单块最小 size */
    #define __MIN_LINK_BLOCK_SIZE__ 256
#endif

#ifndef __MAX_LINK_BLOCK_SIZE__
    /** @brief 创建块链存储的单块最大 size */
    #define __MAX_LINK_BLOCK_SIZE__ 65536
#endif

#include "NML.hpp"

namespace NML{
    namespace Link_Block{
        /** 块链节点
         * @tparam Value_Type data 中的数据类型
         */
        template <typename Value_Type> 
        struct Link_Block_Node {
            /** 上一个节点 */
            Link_Block_Node<Value_Type>* previous;
            /** 下一个节点 */
            Link_Block_Node<Value_Type>* next;
            /** 当前节点的长度容量 */
            Idx length;
            /** 当前节点已使用的长度 */
            Idx used_length;
            /** 当前节点内的数据 */
            Value_Type* data;
        };
        

        /** 插入内容时追加块链节点时的行为模式 */
        enum Behavior_Pattern__Add_LinkBlock{
            /** 禁止添加, 将尽可能在已有的节点中分配空间存储内容; 无法完成时将会报错 */
            disabled,
            /** 禁止添加, 当前节点无法容纳插入内容时尝试在前面的节点中已有的空间中重新分配以腾出空间保存内容, 无法完成时将会报错*/
            disabled_move_forward,
            /** 禁止添加, 当前节点无法容纳插入内容时尝试在后面的节点中已有的空间中重新分配以腾出空间保存内容, 无法完成时将会报错*/
            disabled_move_backward,
            
            /** 添加, 当前节点无法容纳插入内容时尝试在前面的节点中已有的空间中重新分配以腾出空间保存内容, 无法保存内容时才会增加节点*/
            able_move_forward,
            /** 添加, 当前节点无法容纳插入内容时尝试在后面的节点中已有的空间中重新分配以腾出空间保存内容, 无法保存内容时才会增加节点*/
            able_move_backward,
            /** 紧凑的, 当所有节点的剩余空间都不足以保存内容时才会增加节点 */
            tight,
            /** 懒惰的, 仅判断节点和前后一个节点是否有剩余空间保存内容, 无法保存时增加节点 */
            lazy,
            /** 积极添加, 当前节点无法容纳插入内容时直接分为3块 >> [0,index):before, [index,length):insert_values, [index+length,...]: after*/
            active
        };


        /** 使用下标获取块链的内容
         * @tparam Value_Type 块链节点使用的数据类型
         * @param origin_node             访问节点, 节点数据的起始位置将作为 0 下标
         * @param index__offset           元素在访问节点的下标偏移量, 使用负数可以向前查找
         * @param  _out_node              在访问后将被修改为 reutrn 元素所在的节点
         * @param  _out_node_head_index   在访问后将被修改为 reutrn 元素所在的节点的 0 元素相对于 origin_node 的下标偏移量
         * @return 返回对应下标的内容
         * @throw 当下标无法找到对应位置时, throw index;
         */
        template <typename Value_Type> 
        Value_Type get_Item__LinkBlock(
            const Link_Block_Node<Value_Type>* const origin_node, Idx index_offset,
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_node_head_index=0
        );


        /**
         * 用于delete时遍历块链时的结束判断 (now_node==0) || (now_node==head_node) || (previous_node!=now_node->previous);  
         */
        template <typename Value_Type> 
        inline bool check_ELE__Link_Block(Link_Block_Node<Value_Type>*& head_node, Link_Block_Node<Value_Type>*& now_node, Link_Block_Node<Value_Type>*& previous_node)
        {
            return (now_node==0)  ||   // end
                (now_node==head_node) ||   // loop in head to end 
                (previous_node!=now_node->previous);    // error
        }


        /** 
         * @brief 释放/销毁 后段块链
         * @tparam Value_Type 块链节点使用的数据类型
         * @param header_node 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         * @param _delete_data_item 是否对每个数据元素执行 delete 关键字, 默认 false
         * @param _delete_callback  是否对每个数据元素执行 _delete_callback
         */
        template <typename Value_Type> 
        void free_LinkBlock__After(Link_Block_Node<Value_Type>* header_node,bool _delete_data_item=false, Callback _delete_callback=0);


        /** 
         * @brief 向块链插入内容
         * @tparam Value_Type 块链节点使用的数据类型
         * @param header_node              头部节点
         * @param index__offset            元素在访问节点后的下标偏移量
         * @param length                   删除的内容的长度
         * @param value                    追加的内容
         * @param $origin_node             访问节点, 应该可以用header节点访问到, 用于重置 0 下标的位置, 默认使用 header_node
         * @param _length_value            添加内容的长度, 默认为1
         * @param _delete_data_item        是否对删除内容的每个元素执行delete, 默认false
         * @param _paternadd               当前节点无法装载内容时追加块链的行为模式 默认为 lazy (仅检查相邻的块容量)
         * @param _add_node_length         追加节点时新块的长度, 默认为 __MIN_LINK_BLOCK_SIZE__
         * @param _max_link_block_length   块链的最大容量
         * @return 返回是否增加了节点
         * @throw int l  : 当 _paternadd 为禁止新增节点时, 且块链中不足以存入内容, 会抛出整数数值表示还需要额外多少个元素的空间 
         */
        template <typename Value_Type> 
        bool splice_LinkBlock(
            Link_Block_Node<Value_Type>& header_node, Idx index__offset, Idx length,
            Link_Block_Node<Value_Type>* $origin_node=0,
            Value_Type* _value=0, Idx _length_value=1, Behavior_Pattern__Add_LinkBlock _paternadd=lazy, Idx _add_node_length=__MIN_LINK_BLOCK_SIZE__, Idx _max_link_block_length 
        );


        /**
         * @brief 合并块链
         * @param origin_node   起始节点
         * @param node_length   需要合并多少个节点
         * @param _min_length   当合并后的节点容量小于 _min_length 时, 使用 _min_length 作为节点的容量
         */
        template <typename Value_Type> 
        Link_Block_Node<Value_Type>* merge_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx node_length, Idx _min_length);
        

        /** 
         * @brief 计算整段块链的最大容量
         * @tparam Value_Type 块链节点使用的数据类型
         * @param header_block 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         */
        template <typename Value_Type> 
        Idx calc_MaxLength(Link_Block_Node<Value_Type>& header_block);


        // todo 块链访问器类

        
        class Points_Iterator__Link :virtual public Points_Iterator{
            public:
            /** @brief 最大存储长度 (缓存 calc_MaxPointsLength()的计算结果) */
            Idx max_points_length;
            Idx last_access_head_v;
            Link_Block__Simple<var>* last_access_block;
            Points_Iterator__Link(Link_Block__Simple<var>* data, Idx_Algebra dimensional, Idx points_length): Points_Iterator(data, dimensional, points_length), last_access_head_v(-1), last_access_block(0) {}
            Points_Iterator__Link(Idx_Algebra dimensional, Idx points_length):Points_Iterator(dimensional, points_length){}
            Points_Iterator__Link(Points_Iterator& copy_obj):Points_Iterator(copy_obj){install_Data(dimensional, points_length);copy_Data(copy_obj);}
            ~Points_Iterator__Link(){free_Data();}
            void install_Data(Idx_Algebra dimensional, Idx points_length){ append_Block(dimensional*points_length); }
            void free_Data();
            var* operator[](Idx v) override;
            
            /** @brief 计算当前已有空间的最多能存放多少个点数 */
            Idx calc_MaxPointsLength();

            /** 
             * @brief 追加一块存储空间
             * @param length 块的大小 ( 实际空间大小= length * sizeof(var) )
             */
            void append_Block(Idx length=-1);
        };
        
    }
}

#endif
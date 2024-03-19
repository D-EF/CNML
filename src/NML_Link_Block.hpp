/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-19 17:59:40
 * @FilePath: \CNML\src\NML_Link_Block.hpp
 * @Description: 块状链表存储结构
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NML_Link_Block__
#define __NML_Link_Block__

#ifndef __MIN_LINK_BLOCK_SIZE__
    /** @brief 创建块状链表存储的单块最小 size */
    #define __MIN_LINK_BLOCK_SIZE__ 256
#endif

#ifndef __MAX_LINK_BLOCK_SIZE__
    /** @brief 创建块状链表存储的单块最大 size */
    #define __MAX_LINK_BLOCK_SIZE__ 65536
#endif

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
        

        /** 
         * @brief 使用下标获取块状链表的内容
         * @param origin_node             访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset             元素在访问节点的下标偏移量, 使用负数可以向前查找
         * @param  _out_node              在访问后将被修改为 reutrn 元素所在的节点
         * @param  _out_node_head_index   在访问后将被修改为 reutrn 元素所在的节点的 0 元素相对于 origin_node 的下标偏移量
         * @return 返回对应下标的内容
         * @throw 当下标无法找到对应位置时, throw index;
         */
        template <typename Value_Type> 
        Value_Type& get_Item__LinkBlock(
            const Link_Block_Node<Value_Type>* const origin_node, Idx idx_offset,
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_node_head_index=0
        );


        /**
         * @brief 将节点和超出可用范围的index, 重新定位到在范围内的index和对应节点
         * @param origin_node   访问节点, 节点数据的起始位置将作为 0 下标
         * @param idx__offset   元素在访问节点的下标偏移量, 使用负数可以向前查找
         */
        template <typename Value_Type> 
        inline void redirect_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx& index){ if(index>origin_node->used_length||index<0) get_Item__LinkBlock(origin_node, index, &origin_node, &index); }


        /**
         * 用于delete时遍历块状链表时的结束判断 (now_node==0) || (now_node==end_node) || (prev_node!=now_node->prev);  
         */
        template <typename Value_Type> 
        inline bool check_ELE__Link_Block(Link_Block_Node<Value_Type>*& end_node, Link_Block_Node<Value_Type>*& now_node, Link_Block_Node<Value_Type>*& prev_node)
        {
            return (now_node==0)  ||   // end
                (now_node==end_node) ||   // loop in head to end 
                (prev_node!=now_node->prev);    // error
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
         * @param _end_node          当轮询到 _end_node 时直接结束覆盖行为, 默认为 0 (循环链表时应为尾节点)
         * @return 返回成功写入多少元素
         */
        template <typename Value_Type> 
        Idx rape_LinkBlock(Link_Block_Node<Value_Type>* origin_node, Idx index, Value_Type* data, Idx length, bool _flag_used=false, bool _reset_last_used=false, Link_Block_Node<Value_Type>* _end_node=0 );


        /**
         * @brief 擦除块状链表中的一段元素
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node              起始节点
         * @param index                    从第 index 个元素开始擦除
         * @param _erase_length            擦除多少个元素, 默认为 1
         * @param _flag_delete_data_item   是否对每个元素执行 delete, 默认为 false
         * @param _end_node                当轮询到 _end_node 时直接结束擦除行为, 默认为 0 (循环链表时应为尾节点)
         * @param _out_node                输出擦除完成后的活跃节点,  默认为 0 (不输出)
         * @return 返回删除后从起始位置到结束位置有多少空闲空间
         */
        template <typename Value_Type> 
        Idx erase_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, 
            Idx _erase_length=1, bool _flag_delete_data_item=false, Link_Block_Node<Value_Type>* _end_node=0, Link_Block_Node<Value_Type>** _out_node=0
        );


        /**
         * @brief 向前移动数据以腾出空间
         * @param origin_node        起始节点
         * @param index              从第 index 个元素开始
         * @param length             向前移动的长度
         * @param _out_node          输出移动后的活跃节点, 默认为0 (不输出)
         * @param _out_index         输出移动后的活跃节点尾部, 默认为0 (不输出)
         * @param _end_node          当节点轮询到 _end_node 时直接退出循环, 默认为 0 (循环链表时应为尾节点)
         * @param _max_node_length   最大访问节点数量, 默认为 INFINITY
         * @return 返回成功移动的长度
         */
        template <typename Value_Type> 
        int shiftForward_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx length, 
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Link_Block_Node<Value_Type>* _end_node=0, Idx _max_node_length=INFINITY
        );


        /**
         * @brief 向后移动数据以腾出空间
         * @tparam Value_Type 块状链表的数据类型
         * @param origin_node        起始节点
         * @param index              从第 index 个元素开始
         * @param length             向后移动的长度
         * @param _out_node          输出移动后的活跃节点, 默认为0 (不输出)
         * @param _out_index         输出移动后的活跃节点第一个实际可用元素, 默认为0 (不输出)
         * @param _end_node          当节点轮询到 _end_node 时直接退出循环, 默认为 0 (循环链表时应为尾节点)
         * @param _max_node_length   最大访问节点数量, 默认为 INFINITY
         * @return 返回 移动操作完成后原数据在活跃节点的下标
         */
        template <typename Value_Type> 
        int backOff_LinkBlock(
            Link_Block_Node<Value_Type>* origin_node, Idx index, Idx length, 
            Link_Block_Node<Value_Type>** _out_node=0, Idx* _out_index=0, Link_Block_Node<Value_Type>* _end_node=0, Idx _max_node_length=INFINITY
        );
        

        /** 操作块状链表时的设置 */
        typedef struct Option_Act_LinkBlock{
            /** 插入操作; 当加入元素长度大于擦除元素长度时, 以origin为起点向后查找空闲空间时最大寻址节点个数, 优先使用 after 节点中的空闲空间 */
            int max_after_free_count;
            /** 插入操作; 向前查找空闲空间时最大寻址节点个数 */
            int max_before_free_count;
            /** 插入操作; 无法在现有节点中存放插入数据时是否要添加新节点 */
            bool use_create_node;
            /** 追加节点时新块的长度 */
            Idx ex_link_block_length;
            /** 当擦除/覆盖时 是否对每个内容 delete*/
            bool flag_delete_data_item;
        } Option_Act_LinkBlock;


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
            Value_Type* _ex_value, Idx _ex_length, Option_Act_LinkBlock* _option, Link_Block_Node<Value_Type>* _head_node, Link_Block_Node<Value_Type>* _tail_node
        );


        /** 在尾部追加内容 */
        template <typename Value_Type> 
        int append_LinkBlock();


        /**
         * @brief 合并块状链表
         * @param origin_node   起始节点
         * @param node_length   需要合并多少个节点
         * @param _min_length   当合并后的节点容量小于 _min_length 时, 使用 _min_length 作为节点的容量
         */
        template <typename Value_Type> 
        Link_Block_Node<Value_Type>* merge_LinkBlock(Link_Block_Node<Value_Type>*& origin_node, Idx node_length, Idx _min_length);
        

        /** 
         * @brief 释放/销毁 后段块状链表
         * @param header_node 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         * @param _flag_delete_data_item 是否对每个数据元素执行 delete 关键字, 默认 false
         * @param _erase_callback  是否对每个数据元素执行 _erase_callback
         */
        template <typename Value_Type> 
        void free_LinkBlock__After(Link_Block_Node<Value_Type>* header_node,bool _flag_delete_data_item=false, Callback _erase_callback=0);


        /** 
         * @brief 计算整段块状链表的最大容量
         * @param header_block 起始节点, 当访问 next 为 0 或 header_node 时, 会认为是到达了尾部节点
         */
        template <typename Value_Type> 
        Idx calc_MaxLength(Link_Block_Node<Value_Type>& header_block);


        // todo 块状链表访问器类

        
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
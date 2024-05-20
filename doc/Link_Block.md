# 块状链表数据结构

* 块状链表是结合了链表和线性表的存储结构, 综合性能可观, 可用于部分算法中的空间存储;

* 部分常量的宏定义:
    ``` cpp
    #ifndef __DEFAULT_LINK_BLOCK_SIZE__
        /** @brief 创建块状链表存储的默认单块长度 size */
        #define __DEFAULT_LINK_BLOCK_SIZE__ 256
    #endif
    ```

* 基本数据结构:
    ``` cpp
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
    ```

* 简单示例   
    $$
    0                                                 \\
    \uparrow                                          \\
    [a_0,a_1,a_2,...,a_{used\_ length-1},...(void)]   \\
    \uparrow  \downarrow                              \\
    [b_0,b_1,b_2,...,b_{used\_ length-1},...(void)]   \\
    \uparrow  \downarrow                              \\
    [c_0,c_1,c_2,...,c_{used\_ length-1},...(void)]   \\
    \downarrow                                        \\
    0                                                 \\
    $$
    
    * 其中 void 指该节点中下标范围为 \[used_length,length\) 的位置, 它们作为节点的空闲空间存在;
    * 双向链表, 头部的 prev 和尾部的 next 应为空指针 (0);
    * 应该禁止出现 prev 和 next 的节点不对应 (a.next==b && b.prev!=a) 的情况;

## 基本操作

* 操作配置
    ``` cpp
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
    ```

* 使用下标获取元素 / 节点 (get_Item__LinkBlock)   
    * 以传入的参数节点为 0 下标的位置, 相当于以节点的 used_length 建立显式查找表进行查找; 返回目标元素, 并可以使用 指针参数接收其他输出; 详细说明查阅代码 NML_Link_Block.hpp
    * 简单示例:
        $$
        N=\{a,b,...\} \\
        F_{get\_Item\_\_LinkBlock}(N,i)=\{a_0,a_1,a_2,...,a_{used\_ length}, b_0,b_1,b_2,...,b_{used\_ length},...\}[i]
        $$

* 擦除内容 (erase_LinkBlock)
    * 擦除 get_Item__LinkBlock(node, index) 至 get_Item__LinkBlock(node, index+erase_length) 间的内容; 修改对应的节点中的 data 和 used_length

* 向前/向后移动数据以腾出空闲空间
    * 简单示例 (此处为向后移动数据,且移动时影响到多个节点时过程) : 
    ```
    index=2, offset=11;
    move before :
                                index+offset=13 ([1][1])
        index ([0][2])                  ↓
            ↓                           ↓
        [1,2,3,4,5,6,7,8,9, , , ] <-> [a,b,c,d, , , , , ] <-> [e,f,g, , , , , , ] ...
            -------------------------   ---------------------   -------------
            length=+12;                 +9;                     +9              =sum(length)   =30
            used=+9;                    +4;                     +3              =sum(used)     =16
            free=+3                     +5                      +6              =length-used   =14 
            // 当 free>offset时不再继续寻找节点
            
    moved after :
      // 当可用节点中空闲空间不足以腾出offset参数的空间时, 尽量腾出空间并返回成功腾出的空间的长度
      return[ , , , , , , , , ,       , , ].length => min(offset,free)
        [1,2, , , , , , , , , , ] <-> [ , ,3,4,5,6,7,8,9] <-> [a,b,c,d,e,f,g, , ]
             ↑                                                             ↑
          _out_index=2;                              对齐到尾部的下标 used+offset=27 ([2][6])
        ↑
      _out_node
            new_used=2;                  new_used=9;              new_used=7;
    ```
    * 向前挪动也是类似的;
* 插入/替换内容
    * 擦除;
    * 腾挪出空间;
    * 是否成功腾挪出空间? 继续 : 新增节点 or 弹出错误;
    * 写入;

* 销毁/释放
    * 从头到尾 delete 即可;

* 合并节点
    将 每个节点的 \[0,used_length\) 数据拷贝到一个新的足够大的节点中; 然后重新设置前后节点的指针; 最后销毁旧节点;

* 计算适合的长度 (手动计算)   
    * 设 d = _\_DEFAULT\_LINK\_BLOCK\_SIZE\_\_   
    * 适合的长度 $ L_{node} = d⌈ \frac{L{data}}{d} ⌉  $
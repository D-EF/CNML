/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-03-06 11:34:26
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-23 16:50:11
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
    }
}
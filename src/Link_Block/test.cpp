
#include "./NML_Link_Block.hpp"
#include <iostream>

namespace NML_Test{
    namespace Test_Act{

        void test_LinkBlock(){
            using namespace NML::Link_Block;
            using namespace NML;
            
            var _test_data[]={0,1,2,3,4,5,6,7,8,9};
            var *test_data=_test_data;

            Link_Block_Ctrl<var> d=Link_Block_Ctrl<var>(6);
            d.head_node->next=new Link_Block_Node<var>;
            d.head_node->next->length=6,
            d.head_node->next->data=new var(6),
            d.head_node->next->prev=d.head_node,
            d.head_node->next->next=0;
            d.head_node->used_length=5;
            d.head_node->next->used_length=6;
            d.reload_Length();
            rape_LinkBlock(d.head_node, 0, test_data, 10, false, true);
            if(FLAG__TEST_PRINT){
                std::cout << "\t" << d;
                printf("\n\tLink_Block_Ctrl max_length : %d\n",d.max_length);
            }
            
        }

    }
}
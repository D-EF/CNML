/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-25 10:42:38
 * @FilePath: \CNML\src\Link_Block\test.cpp
 * @Description: 块链 单元测试
 */
#include "unit_test_basics.hpp"
#include "./NML_Link_Block.hpp"
#include <iostream>

namespace NML_Test{
    namespace Test_Act{
        
        using namespace NML;
        using namespace NML::Link_Block;

        template <typename T>
        void printf_TestLinkBlock(Link_Block_Node<T>* head_node, std::ostream* os=&std::cout){
            using namespace NML;
            using namespace NML::Link_Block;

            Idx i;
            Link_Block_Node<T> *now_node = head_node;
            do{
                (*os) << "[";
                i=0;
                while(i<now_node->used_length){
                    (*os) << (T)now_node->data[i] <<  ",";
                    ++i;
                }
                if(now_node->used_length < now_node->length){
                    (*os) << "...x" << now_node->length - now_node->used_length << "x]";
                }else{
                    (*os) << "\b]\n";
                }
                now_node=now_node->next;
            }while(now_node && now_node!=head_node);
            (*os) << "\n\n";
        }

        template <typename T>
        void _printf_Test(Link_Block_Ctrl<T>& lbc){
            std::cout << "\t";
            printf_TestLinkBlock(lbc.head_node);
            printf("\n\tLink_Block_Ctrl max_length  : %d ; used_length : %d ;\n\n", lbc.max_length, lbc.used_length);
        }


        void test_LinkBlock(){
            printf("\n");

            var *test_data     =new var[256];
            var *test_data_i   =new var[256];
            var *test_data_s   =new var[256];

            int i;
            
            for(i=0;i< 256;++i) test_data  [i] = i;
            for(i=1;i<=256;++i) test_data_i[i-1] = -i;
            for(i=1;i<=256;++i) test_data_s[i-1] = i*0.1;

            Link_Block_Ctrl<var> d=Link_Block_Ctrl<var>(6);
            d.add_Node(6);
            d.add_Node(6);
            d.add_Node(6);
            d.add_Node(6);
            d.add_Node(6);
            d.add_Node(6);

            Link_Block_Node<var> *_node;
            Idx index;

            rape_LinkBlock(d.head_node, 0, test_data, 30, false, true);
            d.reload_Length();
            _printf_Test(d);

            backOff_LinkBlock(d.head_node, 3, 7 );
            rape_LinkBlock(d.head_node, 3, test_data_s, 7, false, false);
            d.reload_Length();
            _printf_Test(d);
            // [0,1,2,0.1,0.2,0.3][3,0.4,0.5,0.6,3,4][5,6,7,8,9,10  ......

            d.head_node->used_length=3;
            d.head_node->next->used_length=3;
            Idx shift_length = shiftForward_LinkBlock(d.head_node, 13, 6, &_node, &index);  // max shift_length = 3+3 = 6
            rape_LinkBlock(_node, index, test_data_s, shift_length, false, false);
            d.reload_Length();
            _printf_Test(d);
            // shift_length>=6  >>  [0,1,2,0.4,0.5,0.6][5,6,7,8,9,10][11,0.1,0.2,0.3,0.4,0.5][0.6,12,13,14,15,16  ......


            // erase
            // [0,1,2,0.4,0.5,0.6][5,6,7,8,9,10][11,0.1,0.2,0.3,0.4,0.5][0.6,12,13,14,15,16  ......
            //  0                  6     9                   15            
            // [0,1,2,0.4,0.5,0.6][5,6,7,...x3x][0.3,0.4,0.5,.......x3x][0.6,12,13,14,15,16  ......     // erase 9,6
            //                                                               13       16
            // [0,1,2,0.4,0.5,0.6][5,6,7,...x3x][0.3,0.4,0.5,.......x3x][0.6,15,16  ......     // erase 13,3
            erase_LinkBlock(d.head_node, 9,  6);
            erase_LinkBlock(d.head_node, 13, 3);
            d.reload_Length();
            _printf_Test(d);

            Option_Act_LinkBlock* d_option=new Option_Act_LinkBlock;
            d_option->ex_link_block_length=6;
            d_option->find_free_max_after_node_count  = 1;
            d_option->find_free_max_before_node_count = 1;
            d_option->erase_callback=0;
            d.set_Option(d_option);

            // [0,1,2,0.4,0.5,0.6][5,6,7,...x3x][0.3,0.4,0.5,.......x3x][0.6,15,16  ......     
            //                                       10   11
            // [0,1,2,0.4,0.5,0.6][5,6,7,...x3x][0.3,.......x5x][ (x2x) ,0.5,0.6,15,16]  ...... // backOff 
            // [0,1,2,0.4,0.5,0.6][5,6,7,0.3,...x2x][.......x6x][ (x2x) ,0.5,0.6,15,16]  ...... // shift   
            //                           shift out:  ^node^ , 0
            splice_LinkBlock(d.head_node, 10, 1, test_data_i, 20, d.get_Option()); // 将会删除 10 位置内容(0.4)并填充负数
            // [0,1,2,0.4,0.5,0.6][5,6,7,0.3,...x2x][-1,-2,-3,-4,-5,-6][-7,-8,-9,-10,-11,-12][-13,-14,-15,-16,-17,-18][-19,-20,0.5,0.6,15,16][17,18,19,20,21,22][23,24,25,26,27,28][29,...x5x]
            d.reload_Length();
            _printf_Test(d);

            merge_LinkBlock(d.head_node,3,10);
            d.reload_Length();
            _printf_Test(d);

            return;
        }


        void test_LinkBlock_256(){
            
            var *test_data     =new var[256];
            var *test_data_i   =new var[256];
            var *test_data_s   =new var[256];

            int i;
            
            for(i=0;i< 256;++i) test_data  [i] = i;
            for(i=1;i<=256;++i) test_data_i[i-1] = -i;
            for(i=1;i<=256;++i) test_data_s[i-1] = i*0.1;

            Option_Act_LinkBlock* option__256 = new Option_Act_LinkBlock;
            option__256->ex_link_block_length=256;
            option__256->find_free_max_after_node_count  = 1;
            option__256->find_free_max_before_node_count = 1;
            option__256->erase_callback=0;


            Link_Block_Node<var> *hn=create_LinkBlockNode(256,test_data,256);
            Link_Block_Ctrl<var> d = Link_Block_Ctrl<var>(hn);
            d.set_Option(option__256);
            d.reload_Length();

            printf_TestLinkBlock(d.head_node);

            // d.splice(0,0,test_data_i,1);
            d.push_Items(test_data_i,5);
            d.splice(255,0,test_data_i,1);

            printf_TestLinkBlock(d.head_node);
        }


        void test_Points_Iterator__LinkBlock(){
            
            Points_Iterator__LinkBlock p=Points_Iterator__LinkBlock(3,128);
            
            printf_Points(p);

        }

    }
};
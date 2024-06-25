/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-03 11:53:56
 * @FilePath: \CNML\src\unit_test_basics.cpp
 * @Description: 单元测试
 */

#include <iostream>
#include <chrono>
#include "unit_test_basics.hpp"

namespace NML_Test{
    
    int _test_count=0;
    int _test_error_count=0;

    namespace unprint__check_Test{
        const bool FLAG__TEST_PRINT=false;
        void check_Test(bool flag, const char* msg){
            ++_test_count;
            if(!flag){
                ++_test_error_count;
            }
        }
    }

    namespace print__check_Test{
        const bool FLAG__TEST_PRINT=true;
        void check_Test(bool flag, const char* msg){
            ++_test_count;
            if(flag){
                printf("    \033[32m done -> %s \033[0m \n", msg);
                return;
            }
            else {
                ++_test_error_count;
                printf("    \033[31m error -> %s \033[0m \n", msg);
            }
        }
    }


    namespace Test_Act{

        Test_Act_Node* test_act=0;

        void add_TestAct(Act_Fnc cb, char* name){
            Test_Act_Node* new_node = new Test_Act_Node{cb,0,name};
            if(!test_act){
                new_node->next=new_node;
            }
            else {
                new_node->next = test_act->next;
                test_act->next = new_node;
            }
            test_act=new_node;
        }


        void run_Test(){
            if(!test_act) throw "Have not any test Act! ";

            printf("start run test **********************\n");

            using namespace std;
            using namespace NML;
            using namespace chrono;

            chrono::_V2::system_clock::time_point start_time, end_time, loc_start_time, loc_end_time;
            int64_t duration;
            Test_Act_Node* temp=test_act->next;

            loc_start_time=start_time = high_resolution_clock::now();

            int temp_count=0;
            int temp_err_count=0;
            int act_count=0;
                
            do{
                ++act_count;
                printf("\n  <Act [%d]> start test %s : ------------- \n", act_count, temp->name);

                loc_start_time = high_resolution_clock::now();

                temp->callback();

                loc_end_time = high_resolution_clock::now();
                duration = duration_cast<microseconds>(loc_end_time - loc_start_time).count();
                loc_start_time=loc_end_time;

                printf("\n     <Act [%d]> Test %s done!  use time: %lld microseconds.", act_count, temp->name, duration);
                printf("\n     This Test check / error count: %d / %d\n\n" , 
                    _test_count-temp_count, 
                    _test_error_count-temp_err_count
                );

                temp_count=_test_count;
                temp_err_count=_test_error_count;
                temp=temp->next;
            }while(temp!=test_act->next);

            end_time = high_resolution_clock::now();
            duration = duration_cast<microseconds>(end_time - start_time).count();

            printf("\n ALL done!  use time: %lld microseconds.\n", duration);
            printf("\n act_count count: %d\n" , act_count);
            printf("\n check / error count: %d / %d\n" , _test_count, _test_error_count);
        }
        
    }

}
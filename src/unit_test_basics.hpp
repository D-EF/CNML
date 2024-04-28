/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 17:19:26
 * @FilePath: \CNML\src\unit_test_basics.hpp
 * @Description: 单元测试
 */

#ifndef __NML_TEST__
#define __NML_TEST__

#include "NML.hpp"

namespace NML_Test{
    extern int _test_count;
    extern int _test_error_count;
    
    namespace print__check_Test{void check_Test(bool flag, char* msg=0);    extern const bool FLAG__TEST_PRINT; }

    namespace unprint__check_Test{void check_Test(bool flag, char* msg=0);  extern const bool FLAG__TEST_PRINT; }

    #ifndef __NML_TEST_TYPE__
        #define __NML_TEST_TYPE__ print__check_Test;
    #endif

    namespace Test_Act{
        using namespace __NML_TEST_TYPE__;

        typedef void (*Act_Fnc)();

        typedef struct Test_Act_Node{
            Act_Fnc callback;
            Test_Act_Node *next;
            char* name;
        }Test_Act_Node;

        extern Test_Act_Node* test_act;

        void add_TestAct(Act_Fnc,char* name=0);

        void run_Test();

    }
}
#endif
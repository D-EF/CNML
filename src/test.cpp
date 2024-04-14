/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-20 00:58:11
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-07 11:19:50
 * @FilePath: \CNML\src\test.cpp
 * @Description: 单元测试
 * @
 * @Copyright (c) 2023 by ${git_name} ${git_email}, All Rights Reserved. 
 */

#include "unit_test_basics.hpp"
#include "Algebra/test.cpp"
#include "Link_Block/test.cpp"

int main(int argc, char **argv){
    using namespace NML_Test::Test_Act;
    // add_TestAct(test_Vector,"test_Vector");
    // add_TestAct(test_Matrix,"test_Matrix");
    // add_TestAct(test_Algebra,"test_Algebra");
    add_TestAct(test_LinkBlock,"test_LinkBlock");
    run_Test();
    return 0;
}
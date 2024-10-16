/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-20 00:58:11
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-10-16 04:43:44
 * @FilePath: \CNML\src\test.cpp
 * @Description: 单元测试 入口文件
 */

#include "unit_test_basics.hpp"
#include "Algebra/test.cpp"
#include "Geometry/test.cpp"
#include "Link_Block/test.cpp"
#include "Geometry_2D/test.cpp"

int asd(int[2]){
    return 1;
}

int main(int argc, char **argv){
    using namespace NML_Test::Test_Act;
    add_TestAct(test_Vector,"test_Vector");
    add_TestAct(test_Matrix,"test_Matrix");
    add_TestAct(test_Algebra,"test_Algebra");
    add_TestAct(test_LinkBlock,"test_LinkBlock");
    add_TestAct(test_LinkBlock_256,"test_LinkBlock_256");
    add_TestAct(test_Points_Iterator__LinkBlock,"test_Points_Iterator__LinkBlock");
    add_TestAct(test_Bezier,"test_Bezier");
    add_TestAct(test_G2D,"test_G2D");
    add_TestAct(test_g2d_a,"test_g2d_a");
    add_TestAct(test_g2d_b,"test_g2d_b");
    add_TestAct(test_g2d_c,"test_g2d_c");
    add_TestAct(test_Path,"test_Path");
    // add_TestAct(test_2D_Bezier,"test_2D_Bezier");
    run_Test();
    return 0;
}

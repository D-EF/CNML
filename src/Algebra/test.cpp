/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-10-16 06:42:03
 * @FilePath: \CNML\src\Algebra\test.cpp
 * @Description: test 基本代数计算、向量、矩阵
 */

#include <iostream>
#include "./NML_Algebra.hpp"
#include "./NML_Matrix.hpp"
#include "./NML_Vector.hpp"
#include "unit_test_basics.hpp"

namespace NML_Test{
    namespace Test_Act{
        
        void test_Vector(){
            using namespace NML;
            using namespace Vector;

            var *vec1=new var[3]{123.0, 456.0, 789.0};
            var *vec2=new var[3]{3.0, 2.0, 1.0};
            var *unit__vec1=new var[3]{0.13375998748853218, 0.49589068532333885,  0.8580213831581455};
            var *unit__vec2=new var[3]{0.8017837257372732,  0.5345224838248488,   0.2672612419124244};

            var mag__vec_1=919.5575022803088;
            var mag__vec_2=3.7416573867739413;

            var *vec_zero=new var[3]{0, 0, 0};
            var *vec_zero__f=create_Values__Clone(unit__vec1, 3);

            var *temp   =new var[3];
            var *temp1  =new var[3];

            np(vec_zero__f, 3, NML_TOLERANCE*0.1);

            // test is_Unit
                check_Test(false==is_Unit(3, vec1),                                      "test is_Unit(vec1)");
                check_Test(false==is_Unit(3, vec2),                                      "test is_Unit(vec2)");
                check_Test(true==is_Unit(3, unit__vec1),                                 "test is_Unit(unit__vec1)");
                check_Test(true==is_Unit(3, unit__vec2),                                 "test is_Unit(unit__vec2)");
            // get_Quadrant__v2
                check_Test(1==get_Quadrant__v2(vec1),                                    "test get_Quadrant__v2(vec1)");
            // mag
                check_Test(mag(3, vec1)==mag__vec_1,                                     "test mag(3, vec1)");
                check_Test(mag(3, vec2)==mag__vec_2,                                     "test mag(3, vec2)");
                check_Test(mag(unit__vec2, 3)==1,                                        "test mag(unit__vec2, 3)");
                check_Test(mag(3, unit__vec1)==1,                                        "test mag(3, unit__vec1)");
            // is_Zero__Strict
                check_Test(is_Zero__Strict(3, vec1)==false,                              "test is_Zero__Strict(3, vec1)");
                check_Test(is_Zero__Strict(vec_zero__f, 3)==false,                       "test is_Zero__Strict(vec2, 3)");
                check_Test(is_Zero__Strict(vec2, 3)==false,                              "test is_Zero__Strict(vec2, 3)");
            // is_Zero
                check_Test(is_Zero(3, vec1)==false,                                      "test is_Zero(3, vec1)");
                check_Test(is_Zero(vec2, 3)==false,                                      "test is_Zero(vec2, 3)");
                check_Test(is_Zero(vec_zero__f, 3)==true,                                "test is_Zero(vec_zero__f, 3)");
            // normalize
                std::copy(vec2, vec2+3, temp);
                check_Test(check_Equal(3, normalize(temp, 3), unit__vec2),               "test normalize(vec2, 3)");
            // instead
                std::copy(vec2, vec2+3, temp);
                temp1[0]=-vec2[0];
                temp1[1]=-vec2[1];
                temp1[2]=-vec2[2];
                check_Test(check_Equal(3, instead(temp, 3), temp1),                      "test instead(vec2, 3)");
            // cross
                // cross_V3 == cross
                cross_V3(temp, vec1, vec2);
                temp1[0]=-1122;
                temp1[1]= 2244;
                temp1[2]=-1122;
                check_Test(check_Equal(3, temp, temp1),                                  "test cross_V3(vec1, vec2)");
            // cross_V2
                check_Test(check_Equal(cross_V2(temp, vec1), -1122*456-2244*123),        "test cross_V2(vec1, vec2)");
            // dot
                check_Test(check_Equal(dot(3, vec2, vec1), 2070),                        "test dot(vec1, vec2)");
                check_Test(check_Equal(dot(unit__vec1, vec1, 3), 919.5575022803088),     "test dot(vec1, unit__vec1)");
            // dot_v2
                check_Test(check_Equal(dot_v2(vec2, vec1), 123+123+123+456+456),         "test dot_v2(vec1, vec2)");
            // dot_v3
                check_Test(check_Equal(dot_v3(vec2, vec1), 2070),                        "test dot_v3(vec1, vec2)");
                check_Test(check_Equal(dot_v3(unit__vec1, vec1), 919.5575022803088),     "test dot_v3(vec1, unit__vec1)");
            // mag
                check_Test(check_Equal(mag(3, vec1), mag__vec_1),                        "test mag(vec1)");
                check_Test(check_Equal(mag(3, vec2), mag__vec_2),                        "test mag(vec2)");
                check_Test(check_Equal(mag(3, unit__vec1), 1),                           "test mag(unit__vec1)");
            // mag_v2
            // mag_v3
                check_Test(check_Equal(mag_v3(unit__vec2), 1),                           "test mag(unit__vec2)");
                check_Test(check_Equal(mag(3, vec1), mag__vec_1),                        "test mag_3(vec1)");
                check_Test(check_Equal(mag(3, vec2), mag__vec_2),                        "test mag_3(vec2)");
            // np
                std::copy(unit__vec1, unit__vec1+3, temp);
                std::copy(unit__vec2, unit__vec2+3, temp1);
                
                check_Test(check_Equal(np(temp, 3, mag__vec_1), vec1, 3),                "test np(v1)");
                check_Test(check_Equal(np(temp1, 3, mag__vec_2), vec2, 3),               "test np(v2)");
            // cos_2Vec
                check_Test(check_Equal(cos_2Vec(vec1, vec2), 0.7522492046784672),        "test cos_2Vec(v1, v2)");
                check_Test(check_Equal(cos_3Vec(vec1, vec2), 0.6016271623980259),        "test cos_3Vec(v1, v2)");

            delete temp;
            delete temp1;
            delete vec_zero;
            delete vec_zero__f;
            delete vec1;
            delete vec2;
            delete unit__vec1;
            delete unit__vec2;
        }

        
        void test_Matrix(){
            using namespace NML;
            using namespace Matrix;
            
            var *m3=new var[9]{9, 8, 7, 6, 5, 4, 3, 2, 1};

            var *m2=new var[4]{1, 2, 3, 4};

            var *temp_m3=new var[9];
            var *temp_m3_1=new var[9];
            var *temp_m3_i=new var[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};
            var *m3__m3xm3=new var[9]{
                150,   126,   102,
                96,    81,    66,
                42,    36,    30
            };
            var *m3__orthogonal=new var[9]{
                1,    4,   -5,
                -4,    2,    6,
                5,   -6,    3
            };
            var *m3__orthogonal_i=new var[9]{
                1,   -4,    5,
                4,    2,   -6,
                -5,    6,    3
            };
            
            var *m3__router_x22deg=new var[9]{
                1,    0,           0,
                0,    0.927184,   -0.374607,
                0,    0.374607,    0.927184
            };
            
            var *m3__router_x22deg_i=new var[9]{
                1,    0,           0,
                0,    0.927184,    0.374607,
                0,   -0.374607,    0.927184
            };
            var *temp_m3__setup_m2_t11=new var[9]{1, 0, 0, 0, 1, 2, 0, 3, 4};
            var *temp_m2=new var[4];
            var *temp_m2_i=new var[4]{1, 0, 0, 1};

            var **m2x4=new var*[4]{m2, m2, m2, m2};
            var *temp_m4=new var[16];
            var *m4__m2_tx_m2=new var[16]{
                1,   2,    2,    4,
                3,   4,    6,    8,
                3,   6,    4,    8,
                9,   12,   12,   16
            };
            var *m4__m2x4=new var[16]{
                1,   2,   1,   2,
                3,   4,   3,   4,
                1,   2,   1,   2,
                3,   4,   3,   4
            };
            // clac_Index
                check_Test(clac_Index(3, 0, 1)==3,                                                                        "clac_Index(3, 0, 1)");
                check_Test(clac_Index(3, 2, 2)==8,                                                                        "clac_Index(3, 2, 2)");
            // setup_Matrix__Identity
                check_Test(check_Equal(3, setup_Matrix__Identity(temp_m3, 3, 3), temp_m3_i),                             "setup_Matrix__Identity(temp_m3, 3, 3)");
                check_Test(check_Equal(2, setup_Matrix__Identity(temp_m2, 2, 2), temp_m2_i),                             "setup_Matrix__Identity(temp_m2, 2, 2)");
            // setup_Matrix__Resize
                check_Test(check_Equal(3, setup_Matrix__Resize(temp_m3, m2, 2, 3, 2, 3, 1, 1), temp_m3__setup_m2_t11),   "setup_Matrix__Resize(temp_m3, m2, 2, 3, 2, 3, 1, 1)");
            // setup_Matrix__KroneckerProduct
                check_Test(check_Equal(16, setup_Matrix__KroneckerProduct(temp_m4, m2, m2, 2, 2, 2, 2), m4__m2_tx_m2),   "setup_TensorProduct(temp_m4, m2, m2, 2, 2, 2, 2)");
            // printf_Matrix(temp_m4, 4, 4);
            // setup_Matrix__Concat
                check_Test(check_Equal(16, setup_Matrix__Concat(temp_m4, m2x4, 2, 2, 2, 2), m4__m2x4),                   "setup_Matrix__Concat(temp_m4, m2x4, 2, 2, 2, 2)");
            // printf_Matrix(temp_m4, 4, 4);
            
            //初等变换操作在求逆矩阵中有使用，不多测试了
                // transformation__ExchangeRow
                // transformation__ExchangeCol
                // transformation__ScaleRow
                // transformation__ScaleCol
                // transformation__ExchangeRow_ToUnZero
                // transformation__ExchangeRow_ToUnZero
                // transformation__ExchangeRow_PivotToMax
                // transformation__ExchangeRow_PivotToMax
            // multiplication
                check_Test(check_Equal(16, multiplication(temp_m3, m3, m3, 3), m3__m3xm3),                               "multiplication(temp_m3, m3, m3, 3)");
                check_Test(check_Equal(16, multiplication(temp_m3, m3, m3, 3, 3, 3), m3__m3xm3),                         "multiplication(temp_m3, m3, m3, 3, 3, 3)");
            // check_Orthogonal
                check_Test( check_Orthogonal(m3__orthogonal, 3),                                                         "check_Orthogonal(m3__orthogonal, 3)");
                check_Test(!check_Orthogonal(m3, 3),                                                                     "check_Orthogonal(m3, 3)");
            // transpose
                std::copy(m3__orthogonal,m3__orthogonal+9, temp_m3);
                check_Test(check_Equal(9, transpose(temp_m3, 3), m3__orthogonal_i),                                      "transpose(temp_m3, 3)");
            // transpose_2
            // transpose_3
                std::copy(m3__orthogonal,m3__orthogonal+9, temp_m3);
                check_Test(check_Equal(9, transpose_3(temp_m3), m3__orthogonal_i),                                       "transpose_3(temp_m3)");
            // calc_Det
                // calc_Det__2
                // calc_Det__3
                // calc_Det__4
                // calc_Det__Transformation
            // setup_Matrix__Inverse__Transformation
                setup_Matrix__Inverse__Transformation(temp_m3, m3__router_x22deg, 3);
                check_Test(check_Equal(3, temp_m3, m3__router_x22deg_i),                                                 "setup_Matrix__Inverse(temp_m3, m3__orthogonal, 3)");
            // printf_Matrix(temp_m3, 3, 3);
            // setup_Matrix__Inverse
                setup_Matrix__Inverse(temp_m3, m3__router_x22deg, 3);
                check_Test(check_Equal(3, temp_m3, m3__router_x22deg_i),                                                 "setup_Matrix__Inverse(temp_m3, m3__orthogonal, 3)");
            // printf_Matrix(temp_m3, 3);
            // setup_Matrix__Inverse__2
            // setup_Matrix__Inverse__4

            delete m3;
            delete m2;
            delete temp_m3;
            delete temp_m3_1;
            delete temp_m3_i;
            delete m3__m3xm3;
            delete m3__orthogonal;
            delete m3__orthogonal_i;
            delete m3__router_x22deg;
            delete m3__router_x22deg_i;
            delete temp_m3__setup_m2_t11;
            delete temp_m2;
            delete temp_m2_i;
            delete m2x4;
            delete temp_m4;
            delete m4__m2_tx_m2;
            delete m4__m2x4;
        }


        void test_Algebra(){
            using namespace NML;
            using namespace Algebra;

            var temp_data_0[10];
            var temp_data_1[10];
            var *temp_0=temp_data_0;
            var *temp_1=temp_data_1;
            int i;

            // PascalsTriangle // get_PascalsTriangleLine(Idx_Algebra n);
                int ptl_9_const_data[]={1,9,36, 84, 126, 126, 84, 36,9,1};
                int *ptl_9_const=ptl_9_const_data;
                Pascals_Triangle_Line *ptl_9=get_PascalsTriangleLine(9);
                int *ptl_9_calc=ptl_9->data;
                check_Test(check_Equal(10, ptl_9_const, ptl_9_calc), "test get_PascalsTriangleLine(9)");
                // 0   :   -   -   -   -   -    -    -    -    -     1
                // 1   :   -   -   -   -   -    -    -    -    1     -    1
                // 2   :   -   -   -   -   -    -    -    1    -     2    -     1
                // 3   :   -   -   -   -   -    -    1    -    3     -    3     -    1
                // 4   :   -   -   -   -   -    1    -    4    -     6    -     4    -    1
                // 5   :   -   -   -   -   1    -    5    -    10    -    10    -    5    -    1
                // 6   :   -   -   -   1   -    6    -    15   -     20   -     15   -    6    -    1
                // 7   :   -   -   1   -   7    -    21   -    35    -    35    -    21   -    7    -   1
                // 8   :   -   1   -   8   -    28   -    56   -     70   -     56   -    28   -    8   -   1
                // 9   :   1   -   9   -   36   -    84   -    126   -    126   -    84   -    36   -   9   -   1


            // clac_EquationSolution__Linear(var*& out, var z1, var o1, var z2, var o2, var z3, var o3, var z4, var o4);
                temp_1[0]=-1;
                temp_1[1]=-1;

                // 9+8x=7+6y
                // 5+4x=3+2y
                clac_EquationSolution__Linear(temp_0,9,8,7,6,5,4,3,2);

                check_Test( check_Equal(2, temp_0, temp_1), "test clac_EquationSolution__Linear(temp_0,9,8,7,6,5,4,3,2)");


            // calc_UnivariatePolynomials(var* coefficients, Idx_Algebra length, var param_value);
                temp_1[0]=1;   temp_1[1]=3;   temp_1[2]=5;   temp_1[3]=7;   temp_1[4]=9;

                var temp_v=calc_UnivariatePolynomials(temp_1, 5, 0.123);

                check_Test( check_Equal(1.4597310487689998, temp_v), "test calc_UnivariatePolynomials({1,3,5,7,9},0.123)");


            // setup_Derivatives__UnivariatePolynomials(var*& out, var* coefficients, Idx_Algebra length_coefficients);
                temp_1[0]=1;   temp_1[1]=3;   temp_1[2]=5;   temp_1[3]=7;   temp_1[4]=9;

                setup_Derivatives__UnivariatePolynomials(temp_0,temp_1,5);

                temp_1[0]=3;   temp_1[1]=10;   temp_1[2]=21;   temp_1[3]=36;

                check_Test( check_Equal(temp_0,temp_1,4), "setup_Derivatives__UnivariatePolynomials(temp_0, {1,3,5,7,9})" );


            // setup_Derivatives__UnivariatePolynomials(Points_Iterator& out, Points_Iterator& coefficients);
            
                temp_1[2*0]=1;     temp_1[2*1]=3;     temp_1[2*2]=5;     temp_1[2*3]=7;     temp_1[2*4]=9;
                temp_1[1+2*0]=1;   temp_1[1+2*1]=3;   temp_1[1+2*2]=5;   temp_1[1+2*3]=7;   temp_1[1+2*4]=9;

                Points_Iterator *points_0=new Points_Iterator__1DList(2,5);
                Points_Iterator *points_1=new Points_Iterator__1DList(temp_1,2,5);

                temp_1[2*0]  =3;   temp_1[2*1]  =10;   temp_1[2*2]  =21;   temp_1[2*3]  =36;    
                temp_1[1+2*0]=3;   temp_1[1+2*1]=10;   temp_1[1+2*2]=21;   temp_1[1+2*3]=36; 

                setup_Derivatives__UnivariatePolynomials(*points_0, *points_1);

            // calc_Roots__Square(var*& out, var*& coefficients);

                temp_1[0]=-1;   temp_1[1]=3;   temp_1[2]=5;
                // (-b ± \sqrt{b^2 - 4ac}) / (2a)
                // (-3 ± 5.385164807134504)/ -2

                i=calc_Roots__Square(temp_0, temp_1);

                check_Test(
                    (i==2) &&
                    ( check_Equal(-0.8385164807134505 ,temp_0[0])  ||  check_Equal(0.23851648071345037,temp_0[0]) )&&
                    ( check_Equal(-0.8385164807134505 ,temp_0[1])  ||  check_Equal(0.23851648071345037,temp_0[1]) ), 
                    "test calc_Roots__Square(temp_0, {-1,3,5})"
                );

            // calc_Roots__Cubic(var*& out, var*& coefficients);

                temp_1[0]=-1;   temp_1[1]=3;   temp_1[2]=5;   temp_1[3]=7;

                i=calc_Roots__Cubic(temp_0, temp_1);

                check_Test( i==1 && check_Equal(temp_0[0], 0.22375267927400244) , "test calc_Roots__Cubic(temp_0, {-1,3,5,7})" );

            // calc_Roots__UnivariatePolynomials(var*& out, var*& coefficients,Idx_Algebra length);

                temp_1[0]=4;   temp_1[1]=7;   temp_1[2]=9;   temp_1[3]=6;   temp_1[4]=-3;

                i=calc_Roots__UnivariatePolynomials(temp_0, temp_1, 5);

                check_Test(
                    (i==2) &&
                    ( check_Equal(3.2041110508468353 ,temp_0[0])  ||  check_Equal(-0.7859614615400179,temp_0[0]) )&&
                    ( check_Equal(3.2041110508468353 ,temp_0[1])  ||  check_Equal(-0.7859614615400179,temp_0[1]) ), 
                    "test calc_Roots__UnivariatePolynomials(temp_0, {4,7,9,6,-3})"
                );

            // normalize_Radians(var theta);
            
                check_Test(
                    check_Equal(normalize_Radians((123+360)*DEG),123*DEG)&&
                    check_Equal(normalize_Radians((-66-360)*DEG),-66*DEG), 
                    "test normalize_Radians"
                );
        }

    }
}

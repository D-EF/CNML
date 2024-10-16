/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-28 16:42:11
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-10-16 04:42:51
 * @FilePath: \CNML\src\Geometry\test.cpp
 * @Description: test 贝塞尔曲线 、 通用图形算法 、 线性变换
 */


#include <iostream>
#include "../Algebra/NML_Algebra.hpp"
#include "./NML_Bezier.hpp"
#include "./NML_Geometry.hpp"
#include "./NML_Transform_Action.hpp"
#include "unit_test_basics.hpp"


namespace NML_Test{
    namespace Test_Act{

        void printf_IntLine(int length, int* val){
            using namespace NML;
            Idx i=0;
            printf("[%d", val[i]);
            for(i++;  i<length;  i++){
                printf(",%d", val[i]);
            }
            printf("]\n");
        }

        void test_Bezier__sp(){
            using namespace NML;
            using namespace NML::Algebra;
            using namespace NML::Bezier;
                
            printf("\n printf_IntLinelength=%d,%d,%d,%d,%d\n", get_PascalsTriangleLine(1)->length, get_PascalsTriangleLine(2)->length, get_PascalsTriangleLine(3)->length, get_PascalsTriangleLine(4)->length, get_PascalsTriangleLine(5)->length);
            printf_IntLine(1, get_PascalsTriangleLine(1)->data);
            printf_IntLine(2, get_PascalsTriangleLine(2)->data);
            printf_IntLine(3, get_PascalsTriangleLine(3)->data);
            printf_IntLine(4, get_PascalsTriangleLine(4)->data);
            printf_IntLine(5, get_PascalsTriangleLine(5)->data);

            var *org = new var[5]{0, 1.1, 1.2};
            var *d   = new var[4];
            printf("\n setup_Derivatives__UnivariatePolynomials=");
            setup_Derivatives__UnivariatePolynomials(d, org, 3);
            printf_Vec(d, 2);

            printf("\n get_BezierCalcMatrix:\n");
                printf_IntLine(6, get_BezierCalcMatrix(2));
                printf_IntLine(10, get_BezierCalcMatrix(3));
                printf_IntLine(15, get_BezierCalcMatrix(4));
            printf("\n");

            var d1[4]={0, 1, 2, 3};
            printf_Vec(d1, 4);
            printf_IntLine(4,(int*)d1);
            std::fill_n(d1, 4, 0);
            printf_Vec(d1, 4);
            printf_IntLine(4,(int*)d1);

            var *dd = new var[8]{
                2, 5,
                3, 3,
                6, 7,
                4, 1,
            };
            Points_Iterator__1DList _bezier_coefficients (2, 4);
            Points_Iterator__1DList bezier_ctrl_points   (dd, 2, 4);
            printf_Points(bezier_ctrl_points);
            // [2,  3,  6,  -7] T
            // [5, -6, 18, -16]

            setup_BezierCoefficients(_bezier_coefficients, bezier_ctrl_points);

            // printf_Vec((var*)_bezier_coefficients.data, 8);
            printf("\n  BezierCoefficients  _bezier_coefficients:    \n");
            printf_Points(_bezier_coefficients);
            printf("\n");

            var test_vec_d[2]={0};
            var *test_vec=test_vec_d;
            sample_Bezier__Coefficients(test_vec, _bezier_coefficients, 0.456); // {x: 3.9518842880000005, y: 4.489746944}
            
            printf_Vec(test_vec, 2);
            check_Test( check_Equal(test_vec[0], 3.951884288)&&check_Equal(test_vec[1], 4.489746944), "sample_Bezier__Coefficients {2, 5},{3, 3},{6, 7},{4, 1} 0.456");

            var *cut_bezier_matrix_q = new var[10];
            calc_CutBezierMatrixQ(cut_bezier_matrix_q, 3, 0.456);
            printf_Vec(cut_bezier_matrix_q, 10);

            Points_Iterator__1DList cut_o1(2, 4);
            Points_Iterator__1DList cut_o2(2, 4);

            cut_Bezier__ByMatrix(cut_o1, cut_o2, bezier_ctrl_points, cut_bezier_matrix_q);
            
            printf_Points(cut_o1);
            printf_Points(cut_o2);

            calc_BezierCtrlPoints__Coefficients(cut_o1, _bezier_coefficients);
            printf_Points(cut_o1);
        }

        void test_Bezier(){
            
        }
    }
}
        
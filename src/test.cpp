/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-20 00:58:11
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-10-08 19:58:40
 * @FilePath: \CNML\src\test.cpp
 * @Description: 单元测试
 * @
 * @Copyright (c) 2023 by ${git_name} ${git_email}, All Rights Reserved. 
 */

#include <iostream>
#include <chrono>
#include "NML.hpp"
#include "NML_Algebra.hpp"
#include "NML_Bezier.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_2D.hpp"
#include "NML_Matrix_3D.hpp"
#include "NML_Euler_Angle.hpp"
#include "NML_Quaternion.hpp"

using namespace std;
using namespace NML;
using namespace chrono;

int _test_error_counter=0;
namespace print__check_Test{void check_Test(bool flag, char* msg="");}
namespace unprint__check_Test{void check_Test(bool flag, char* msg="");}

namespace Test_Algebra_Bezier{
    void test_AllFnc();
}
namespace Test_Vector{
    void test_AllFnc();
}
namespace Test_Matrix{
    void test_AllFnc();
    void test_transformation();
}
namespace Test_Euler_Angle{
    void test_AllFnc();
}
namespace Test_Quaternion{
    void test_AllFnc();
}

// using namespace unprint__check_Test;
using namespace print__check_Test;

int main(int argc, char **argv){
    std::chrono::_V2::system_clock::time_point start_time, end_time;
    int64_t duration;

    cout<< "start test :"<<endl;
    start_time = high_resolution_clock::now();
        Test_Algebra_Bezier::test_AllFnc();
        // Test_Vector::test_AllFnc();
        // Test_Matrix::test_AllFnc();
        // Test_Euler_Angle::test_AllFnc();
        // Test_Quaternion::test_AllFnc();
    end_time = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end_time - start_time).count();
    cout << "\nALL done!  use time: " << duration << " microseconds" << endl;
    cout << "\nerror counter: " << _test_error_counter << endl;

    // Test_Matrix::test_AllFnc();

    return 0;
}

namespace unprint__check_Test{
    void check_Test(bool flag, char* msg){
        if(!flag)_test_error_counter++;
    }
}
namespace print__check_Test{
    void check_Test(bool flag, char* msg){
        if(flag){
            printf("\033[32m done -> %s \033[0m \n", msg);
            return;
        }
        else {
            _test_error_counter++;
            printf("\033[31m error -> %s \033[0m \n", msg);
        }
    }
}



namespace Test_Algebra_Bezier{
    using namespace Algebra;
    using namespace Bezier;
    void printf_IntLine(int length, int* val){
        Idx i=0;
        printf("[%d", val[i]);
        for(i++;  i<length;  i++){
            printf(",%d", val[i]);
        }
        printf("]\n");
    }
    void test_AllFnc(){
        printf("\n printf_IntLinelength=%d,%d,%d,%d,%d\n", get_PascalsTriangleLine(1)->size, get_PascalsTriangleLine(2)->size, get_PascalsTriangleLine(3)->size, get_PascalsTriangleLine(4)->size, get_PascalsTriangleLine(5)->size);
        printf_IntLine(1, get_PascalsTriangleLine(1)->data);
        printf_IntLine(2, get_PascalsTriangleLine(2)->data);
        printf_IntLine(3, get_PascalsTriangleLine(3)->data);
        printf_IntLine(4, get_PascalsTriangleLine(4)->data);
        printf_IntLine(5, get_PascalsTriangleLine(5)->data);

        var *org=new var[5]{0, 1.1, 1.2};
        var *d=new var[4];
        printf("\n calc_Derivative__OneUnitaryRealParameterFunction=");
        calc_Derivative__OneUnitaryRealParameterFunction(d, org, 3);
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

        var **dd = new var*[4]{
            new var[2]{2, 5},
            new var[2]{3, 3},
            new var[2]{6, 7},
            new var[2]{4, 1},
        };
        Points_Iterator__1DList _bezier_coefficients=Points_Iterator__1DList((new var[8]), 2, 4);
        Points_Iterator__2DList bezier_ctrl_points=Points_Iterator__2DList((dd), 2, 4);
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

        Points_Iterator__1DList cut_o1=Points_Iterator__1DList((new var[8]), 2, 4);
        Points_Iterator__1DList cut_o2=Points_Iterator__1DList((new var[8]), 2, 4);

        cut_Bezier__ByMatrix(cut_o1, cut_o2, bezier_ctrl_points, cut_bezier_matrix_q);
        
        printf_Points(cut_o1);
        printf_Points(cut_o2);

        calc_BezierCtrlPoints__Coefficients(cut_o1, _bezier_coefficients);
        printf_Points(cut_o1);
        

    }
}


namespace Test_Vector{
    using namespace Vector;
    using namespace NML;
    
    var* vec1=new var[3]{123.0, 456.0, 789.0};
    var* vec2=new var[3]{3.0, 2.0, 1.0};
    var* unit__vec1=new var[3]{0.13375998748853218, 0.49589068532333885,  0.8580213831581455};
    var* unit__vec2=new var[3]{0.8017837257372732,  0.5345224838248488,   0.2672612419124244};

    var mag__vec_1=919.5575022803088;
    var mag__vec_2=3.7416573867739413;

    void test_AllFnc(){
        var* vec_zero=new var[3]{0, 0, 0};
        var* vec_zero__f=create_Values__Clone(unit__vec1, 3);

        var* temp   =new var[3];
        var* temp1  =new var[3];

        np(vec_zero__f, 3, NML_TOLERANCE*0.1);

        // test is_Unit
            check_Test(false==is_Unit(3, vec1),                                        "test is_Unit(vec1)");
            check_Test(false==is_Unit(3, vec2),                                        "test is_Unit(vec2)");
            check_Test(true==is_Unit(3, unit__vec1),                                   "test is_Unit(unit__vec1)");
            check_Test(true==is_Unit(3, unit__vec2),                                   "test is_Unit(unit__vec2)");
        // get_Quadrant__v2
            check_Test(1==get_Quadrant__v2(vec1),                                     "test get_Quadrant__v2(vec1)");
        // mag
            check_Test(mag(3, vec1)==mag__vec_1,                                       "test mag(3, vec1)");
            check_Test(mag(3, vec2)==mag__vec_2,                                       "test mag(3, vec2)");
            check_Test(mag(unit__vec2, 3)==1,                                          "test mag(unit__vec2, 3)");
            check_Test(mag(3, unit__vec1)==1,                                          "test mag(3, unit__vec1)");
        // is_Zero__Strict
            check_Test(is_Zero__Strict(3, vec1)==false,                                "test is_Zero__Strict(3, vec1)");
            check_Test(is_Zero__Strict(vec_zero__f, 3)==false,                         "test is_Zero__Strict(vec2, 3)");
            check_Test(is_Zero__Strict(vec2, 3)==false,                                "test is_Zero__Strict(vec2, 3)");
        // is_Zero
            check_Test(is_Zero(3, vec1)==false,                                        "test is_Zero(3, vec1)");
            check_Test(is_Zero(vec2, 3)==false,                                        "test is_Zero(vec2, 3)");
            check_Test(is_Zero(vec_zero__f, 3)==true,                                  "test is_Zero(vec_zero__f, 3)");
        // normalize
            clone_To(temp, vec2, 3);
            check_Test(check_Equal(3, normalize(temp, 3), unit__vec2),                   "test normalize(vec2, 3)");
        // instead
            clone_To(temp, vec2, 3);
            temp1[0]=-vec2[0];
            temp1[1]=-vec2[1];
            temp1[2]=-vec2[2];
            check_Test(check_Equal(3, instead(temp, 3), temp1),                          "test instead(vec2, 3)");
        // cross
            // cross_V3 == cross
            cross_V3(temp, vec1, vec2);
            temp1[0]=-1122;
            temp1[1]= 2244;
            temp1[2]=-1122;
            check_Test(check_Equal(3, temp, temp1),                                     "test cross_V3(vec1, vec2)");
        // cross_V2
            check_Test(check_Equal(cross_V2(temp, vec1), -1122*456-2244*123),           "test cross_V2(vec1, vec2)");
        // dot
            check_Test(check_Equal(dot(3, vec2, vec1), 2070),                            "test dot(vec1, vec2)");
            check_Test(check_Equal(dot(unit__vec1, vec1, 3), 919.5575022803088),         "test dot(vec1, unit__vec1)");
        // dot_v2
            check_Test(check_Equal(dot_v2(vec2, vec1), 123+123+123+456+456),            "test dot_v2(vec1, vec2)");
        // dot_v3
            check_Test(check_Equal(dot_v3(vec2, vec1), 2070),                           "test dot_v3(vec1, vec2)");
            check_Test(check_Equal(dot_v3(unit__vec1, vec1), 919.5575022803088),        "test dot_v3(vec1, unit__vec1)");
        // mag
            check_Test(check_Equal(mag(3, vec1), mag__vec_1),                           "test mag(vec1)");
            check_Test(check_Equal(mag(3, vec2), mag__vec_2),                           "test mag(vec2)");
            check_Test(check_Equal(mag(3, unit__vec1), 1),                              "test mag(unit__vec1)");
        // mag_v2
        // mag_v3
            check_Test(check_Equal(mag_v3(unit__vec2), 1),                             "test mag(unit__vec2)");
            check_Test(check_Equal(mag(3, vec1), mag__vec_1),                           "test mag_3(vec1)");
            check_Test(check_Equal(mag(3, vec2), mag__vec_2),                           "test mag_3(vec2)");
        // np
            clone_To(temp, unit__vec1, 3);
            clone_To(temp1, unit__vec2, 3);
            
            check_Test(check_Equal(np(temp, 3, mag__vec_1), vec1, 3),                   "test np(v1)");
            check_Test(check_Equal(np(temp1, 3, mag__vec_2), vec2, 3),                   "test np(v2)");
        // cos_2Vec
            check_Test(check_Equal(cos_2Vec(vec1, vec2), 0.7522492046784672),           "test cos_2Vec(v1, v2)");
            check_Test(check_Equal(cos_3Vec(vec1, vec2), 0.6016271623980259),           "test cos_3Vec(v1, v2)");

        delete temp;
        delete temp1;
        delete vec_zero;
        delete vec_zero__f;
    }
}


namespace Test_Matrix{
    using namespace Matrix;
    
    var* m4=new var[16]{
        15,   1,    2,   3,   
        4,    10,   5,   6,   
        7,    6,    5,   4,   
        3,    2,    1,   -1
    };

    var* m4_i=new var[16]{
        0.07547169811320754,    0.012006861063464836,   -0.05660377358490566,   0.07204116638078903,
        0.018867924528301886,   0.20754716981132076,    -0.2641509433962264,    0.24528301886792453,
        -0.18867924528301888,   -0.3481989708404803,    0.6415094339622641,     -0.08919382504288165,
        0.07547169811320754,    0.10291595197255575,    -0.05660377358490566,   -0.38250428816466553
    };

    var* m3=new var[9]{9, 8, 7, 6, 5, 4, 3, 2, 1};

    var* m2=new var[4]{1, 2, 3, 4};


    void test_AllFnc__Matrix();
    void test_AllFnc__M2d__AllType();
    void test_AllFnc__M3d__AllType();
    void test_AllFnc(){
        test_AllFnc__Matrix();
        test_AllFnc__M2d__AllType();
        test_AllFnc__M3d__AllType();
    }
    void test_AllFnc__Matrix(){
        printf("\n\n start testing NML_Matrix's function.\n");
        var* temp_m3=new var[9];
        var* temp_m3_1=new var[9];
        var* temp_m3_i=new var[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};
        var* m3__m3xm3=new var[9]{
            150,   126,   102,
            96,    81,    66,
            42,    36,    30
        };
        var* m3__orthogonal=new var[9]{
             1,    4,   -5,
            -4,    2,    6,
             5,   -6,    3
        };
        var* m3__orthogonal_i=new var[9]{
             1,   -4,    5,
             4,    2,   -6,
            -5,    6,    3
        };
        
        var* m3__router_x22deg=new var[9]{
             1,    0,           0,
             0,    0.927184,   -0.374607,
             0,    0.374607,    0.927184
        };
        
        var* m3__router_x22deg_i=new var[9]{
             1,    0,           0,
             0,    0.927184,    0.374607,
             0,   -0.374607,    0.927184
        };
        var* temp_m3__setup_m2_t11=new var[9]{1, 0, 0, 0, 1, 2, 0, 3, 4};
        var* temp_m2=new var[4];
        var* temp_m2_i=new var[4]{1, 0, 0, 1};

        var** m2x4=new var*[4]{m2, m2, m2, m2};
        var* temp_m4=new var[16];
        var* m4__m2_tx_m2=new var[16]{
            1,   2,    2,    4,
            3,   4,    6,    8,
            3,   6,    4,    8,
            9,   12,   12,   16
        };
        var* m4__m2x4=new var[16]{
            1,   2,   1,   2,
            3,   4,   3,   4,
            1,   2,   1,   2,
            3,   4,   3,   4
        };
        // get_Index
            check_Test(get_Index(3, 0, 1)==3,                                                                     "get_Index(3, 0, 1)");
                check_Test(get_Index(3, 2, 2)==8,                                                                 "get_Index(3, 2, 2)");
        // setup_Matrix__Identity
            check_Test(check_Equal(3, setup_Matrix__Identity(temp_m3, 3, 3), temp_m3_i),                                    "setup_Matrix__Identity(temp_m3, 3, 3)");
            check_Test(check_Equal(2, setup_Matrix__Identity(temp_m2, 2, 2), temp_m2_i),                                    "setup_Matrix__Identity(temp_m2, 2, 2)");
        // setup_Matrix__Resize
            check_Test(check_Equal(3, setup_Matrix__Resize(temp_m3, m2, 2, 3, 2, 3, 1, 1), temp_m3__setup_m2_t11),               "setup_Matrix__Resize(temp_m3, m2, 2, 3, 2, 3, 1, 1)");
        // setup_Matrix__KroneckerProduct
            check_Test(check_Equal(16, setup_Matrix__KroneckerProduct(temp_m4, m2, m2, 2, 2, 2, 2), m4__m2_tx_m2),              "setup_TensorProduct(temp_m4, m2, m2, 2, 2, 2, 2)");
            // printf_Matrix(temp_m4, 4, 4);
        // setup_Matrix__Concat
            check_Test(check_Equal(16, setup_Matrix__Concat(temp_m4, m2x4, 2, 2, 2, 2), m4__m2x4),                             "setup_Matrix__Concat(temp_m4, m2x4, 2, 2, 2, 2)");
            // printf_Matrix(temp_m4, 4, 4);
        // transformation__ExchangeRow
        // transformation__ExchangeCol
        // transformation__ScaleRow
        // transformation__ScaleCol
        // transformation__ExchangeRow_ToUnZero
        // transformation__ExchangeRow_ToUnZero
        // transformation__ExchangeRow_PivotToMax
        // transformation__ExchangeRow_PivotToMax
            //初等变换操作在求逆矩阵中有使用，不多测试了
        // multiplication
            check_Test(check_Equal(16, multiplication(temp_m3, m3, m3, 3), m3__m3xm3),                               "multiplication(temp_m3, m3, m3, 3)");
            check_Test(check_Equal(16, multiplication(temp_m3, m3, m3, 3, 3, 3), m3__m3xm3),                           "multiplication(temp_m3, m3, m3, 3, 3, 3)");
        // check_Orthogonal
            check_Test( check_Orthogonal(m3__orthogonal, 3),                                                     "check_Orthogonal(m3__orthogonal, 3)");
            check_Test(!check_Orthogonal(m3, 3),                                                                 "check_Orthogonal(m3, 3)");
        // transpose
            clone_To(temp_m3, m3__orthogonal, 9);
            check_Test(check_Equal(9, transpose(temp_m3, 3), m3__orthogonal_i),                                    "transpose(temp_m3, 3)");
        // transpose_2
        // transpose_3
            clone_To(temp_m3, m3__orthogonal, 9);
            check_Test(check_Equal(9, transpose_3(temp_m3), m3__orthogonal_i),                                    "transpose_3(temp_m3)");
        // calc_Det__Transformation
        // calc_Det
        // calc_Det__2
        // calc_Det__3
        // calc_Det__4
        // setup_Matrix__Inverse__Transformation
            setup_Matrix__Inverse__Transformation(temp_m3, m3__router_x22deg, 3);
            check_Test(check_Equal(3, temp_m3, m3__router_x22deg_i),                                              "setup_Matrix__Inverse(temp_m3, m3__orthogonal, 3)");
            // printf_Matrix(temp_m3, 3, 3);
        // setup_Matrix__Inverse
            setup_Matrix__Inverse(temp_m3, m3__router_x22deg, 3);
            check_Test(check_Equal(3, temp_m3, m3__router_x22deg_i),                                              "setup_Matrix__Inverse(temp_m3, m3__orthogonal, 3)");
            // printf_Matrix(temp_m3, 3);
        // setup_Matrix__Inverse__2
        // setup_Matrix__Inverse__4
    }
    
    void test_transformation(){
        var* t_m4=create_Values__Clone(m4, 16);
        var* t_m4_1=create_Values__Clone(m4, 16);
        var* t_m4_2=create_Values__Clone(m4, 16);
        var** m4s=new var*[2]{t_m4_1, t_m4_2};

        auto start_time = high_resolution_clock::now();

            // transformation__ExchangeRow(t_m4, 4, 0, 0);
            // transformation__ExchangeRow_PivotToMax(m4s, 2, 16, 4, 0, 0, 4);
            // transformation__ExchangeRow_PivotToMax(t_m4, 16, 4, 0, 0, 4);
            // transformation__ScaleRow(m4s, 2, 4, 0, 1/m4s[0][0]);
            setup_Matrix__Inverse__Transformation(t_m4, m4, 4);


        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();

        cout << "test_transformation use time: " << duration << " microseconds" << endl;

        cout<<endl;
        printf_Matrix(t_m4, 4);
        cout<<endl;
        printf_Matrix(t_m4_1, 4);
        cout<<endl;
        printf_Matrix(t_m4_2, 4);
        cout<<endl;
        delete t_m4;
        delete t_m4_1;
        delete t_m4_2;
        delete m4s;
    }
    
    var* test_m2d__setup[4]={
        new var[9]{1, 2, 0, 3, 4, 0, 5, 6, 1},
        new var[9]{1, 3, 5, 2, 4, 6, 0, 0, 1},
        new var[6]{1, 2, 3, 4, 5, 6},
        new var[6]{1, 3, 5, 2, 4, 6}
    };

    
    var* test_m2d__transform_987654[4]={
        new var[9]{23, 20, 0, 55, 48, 0, 92, 80, 1},
        new var[9]{23, 55, 92, 20, 48, 80, 0, 0, 1},
        new var[6]{23, 20, 55, 48, 92, 80},
        new var[6]{23, 55, 92, 20, 48, 80}
    };

    void test_AllFnc__M2d(Matrix_2D::M2D_Type type = Matrix_2D::M2D__3X3_L);
    void test_AllFnc__M2d__AllType(){
        test_AllFnc__M2d(Matrix_2D::M2D__3X3_L);
        test_AllFnc__M2d(Matrix_2D::M2D__3X3_R);
        test_AllFnc__M2d(Matrix_2D::M2D__2X3);
        test_AllFnc__M2d(Matrix_2D::M2D__3X2);
    }

    void test_AllFnc__M2d(Matrix_2D::M2D_Type type){
        printf("\n\n start testing NML_Matrix_2D's function.(%d)\n", type);
        using namespace Matrix_2D;
        set_NMLConfig__using_m2d_type(type);
        int l=m2d_w*m2d_h;

        var* t_m2d= new var[l];
        char *ss, *st;
        switch (type)
        {
            case 0:
                ss="test setup_Matrix2D type M2D__3X3_L";
                st="test transform_Matrix2D type M2D__3X3_L";
            break;
            case 1:
                ss="test setup_Matrix2D type M2D__3X3_R";
                st="test transform_Matrix2D type M2D__3X3_R";
            break;
            case 2:
                ss="test setup_Matrix2D type M2D__2X3";
                st="test transform_Matrix2D type M2D__2X3";
            break;
            case 3:
                ss="test setup_Matrix2D type M2D__3X2";
                st="test transform_Matrix2D type M2D__3X2";
            break;
        }
        
        setup_Matrix2D(t_m2d, 1, 2, 3, 4, 5, 6);
        check_Test(check_Equal(l, test_m2d__setup[type], t_m2d), ss);
        // printf_Matrix(t_m2d, m2d_w, m2d_h);

        transform_Matrix2D(t_m2d, 9, 8, 7, 6, 5, 4);
        check_Test(check_Equal(l, test_m2d__transform_987654[type], t_m2d), st);
        // printf_Matrix(t_m2d, m2d_w, m2d_h);
        
        var* s_test_m2d__Translate_123_321    =new var[l];
        var* s_test_m2d__Scale_1d234_5d678    =new var[l];
        var* s_test_m2d__Rotate_9d876         =new var[l];
        var* s_test_m2d__Reflect_4_7       =new var[l];
        var* s_test_m2d__Shear_2_1_2          =new var[l];

        var* s_test_m2d__ts      =new var[l];
        var* s_test_m2d__tsr     =new var[l];
        var* s_test_m2d__tsrh    =new var[l];
        var* s_test_m2d__tsrhs   =new var[l];

        // init test transform matrix
            setup_Matrix2D(s_test_m2d__Translate_123_321,
                1,     0,
                0,     1,
                123,   321
            );
            setup_Matrix2D(s_test_m2d__Scale_1d234_5d678,
                1.234,   0,
                0,       5.678,
                0,       0
            );
            setup_Matrix2D(s_test_m2d__Rotate_9d876,
                -0.8999148851836156,   -0.4360655907371733,
                0.4360655907371733,    -0.8999148851836156,
                0,                     0
            );
            setup_Matrix2D(s_test_m2d__Reflect_4_7,
                0.5076923076923077,    -0.8615384615384617,
                -0.8615384615384617,   -0.5076923076923081,
                0,                     0
            );
            setup_Matrix2D(s_test_m2d__Shear_2_1_2,
                1,                     0.4472135954999579,
                0.22360679774997896,   1,
                0,                     0
            );

            setup_Matrix2D(s_test_m2d__ts,
                1.234,     0,
                0,         5.678,
                151.782,   1822.638
            );
            setup_Matrix2D(s_test_m2d__tsr,
                -1.1104949683165816504,   -0.5381049389696718522,
                2.4759804242056699974,    -5.1097167180725693768,
                658.19883506708052617,    -1706.4059739945644077
            );
            setup_Matrix2D(s_test_m2d__tsrh,
                -0.10019165187916261854,   1.2299258647958118541,
                5.6592536955515542906,   0.461011506782728714,
                1804.2968630909120175,   299.26557504714085398
            );
            setup_Matrix2D(s_test_m2d__tsrh,
                -0.10019165187916261854,   1.2299258647958118541,
                5.6592536955515542906,   0.461011506782728714,
                1804.2968630909120175,   299.26557504714085398
            );
            setup_Matrix2D(s_test_m2d__tsrhs,
                0.17482813221770243656,   1.1851187959198513712,
                5.7623390023091336766,    2.9919066998167637425,
                1871.214680004009163,     1106.1716625393228379
            );
        //

        check_Test(check_Equal(l, s_test_m2d__Translate_123_321, setup_Matrix2D__Translate(t_m2d, 123, 321)),                                "test setup_Matrix2D__Translate(t_m2d, 123, 321)");
        check_Test(check_Equal(l, s_test_m2d__Scale_1d234_5d678, setup_Matrix2D__Scale(t_m2d, 1.234, 5.678)),                                "test setup_Matrix2D__Scale(t_m2d, 1.234, 5.678)");
        check_Test(check_Equal(l, s_test_m2d__Rotate_9d876, setup_Matrix2D__Rotate(t_m2d, 9.876)),                                          "test setup_Matrix2D__Rotate(t_m2d, 9.876)");
        check_Test(check_Equal(l, s_test_m2d__Reflect_4_7, setup_Matrix2D__Reflect(t_m2d, 0.49613893835683387, 0.8682431421244593)),   "test setup_Matrix2D__Reflect(t_m2d, 0.49613893835683387, 0.8682431421244593)");
        check_Test(check_Equal(l, s_test_m2d__Reflect_4_7, setup_Matrix2D__Reflect__Collinear(t_m2d, 4, 7)),                           "test setup_Matrix2D__Reflect__Collinear(t_m2d, 4, 7)");
        check_Test(check_Equal(l, s_test_m2d__Shear_2_1_2, setup_Matrix2D__Shear(t_m2d, 0.8944271909999159, 0.4472135954999579, 0.5)),        "test setup_Matrix2D__Shear(t_m2d, 0.8944271909999159, 0.4472135954999579, 0.5)");
        check_Test(check_Equal(l, s_test_m2d__Shear_2_1_2, setup_Matrix2D__Shear__Collinear(t_m2d, 2, 1, 0.5)),                               "test setup_Matrix2D__Shear__Collinear(t_m2d, 2, 1, 0.5)");

        setup_Matrix__Identity(t_m2d, m2d_w, m2d_h);
        //平移值设置太大了，所以容差改大点
        check_Test(check_Equal(l, s_test_m2d__Translate_123_321   , transform_Matrix2D__Translate(t_m2d, 123, 321),           1e-3),   "test transform_Matrix2D__Translate(t_m2d, 123, 321)");
        check_Test(check_Equal(l, s_test_m2d__ts                  , transform_Matrix2D__Scale(t_m2d, 1.234, 5.678),           1e-3),   "test transform_Matrix2D__Scale(t_m2d, 1.234, 5.678)");
        check_Test(check_Equal(l, s_test_m2d__tsr                 , transform_Matrix2D__Rotate(t_m2d, 9.876),                1e-3),   "test transform_Matrix2D__Rotate(t_m2d, 9.876)");
        check_Test(check_Equal(l, s_test_m2d__tsrh                , transform_Matrix2D__Reflect__Collinear(t_m2d, 4, 7),   2e-3),   "test transform_Matrix2D__Reflect__Collinear(t_m2d, 4, 7)");
        check_Test(check_Equal(l, s_test_m2d__tsrhs               , transform_Matrix2D__Shear__Collinear(t_m2d, 2, 1, 0.5),    1e-3),   "test transform_Matrix2D__Shear__Collinear(t_m2d, 2, 1, 0.5)");
        
        // printf_M2dCss(s_test_m2d__Translate_123_321);
        // printf_M2dCss(s_test_m2d__Scale_1d234_5d678);
        // printf_M2dCss(s_test_m2d__Rotate_9d876);
        // printf_M2dCss(s_test_m2d__Reflect_4_7);
        // printf_M2dCss(s_test_m2d__Reflect_4_7);
        // printf_M2dCss(s_test_m2d__Shear_2_1_2);
        // printf_M2dCss(s_test_m2d__Shear_2_1_2);
        // printf_M2dCss(s_test_m2d__ts);
        // printf_M2dCss(s_test_m2d__tsr);
        // printf_M2dCss(s_test_m2d__tsrh);
        // printf_M2dCss(s_test_m2d__tsrhs);

        delete s_test_m2d__Translate_123_321;
        delete s_test_m2d__Scale_1d234_5d678;
        delete s_test_m2d__Rotate_9d876;
        delete s_test_m2d__Reflect_4_7;
        delete s_test_m2d__Shear_2_1_2;

        delete s_test_m2d__ts;
        delete s_test_m2d__tsr;
        delete s_test_m2d__tsrh;
        delete s_test_m2d__tsrhs;
    }


    var* test_m3d__setup[4]={
        new var[16]{
            1,    2,    3,    0,
            4,    5,    6,    0,
            7,    8,    9,    0,
            10,   11,   12,   1
        },
        new var[16]{
            1,   4,   7,   10,
            2,   5,   8,   11,
            3,   6,   9,   12,
            0,   0,   0,   1
        },
        new var[12]{
            1,    2,    3,
            4,    5,    6,
            7,    8,    9,
            10,   11,   12
        },
        new var[12]{
            1,   4,   7,   10,
            2,   5,   8,   11,
            3,   6,   9,   12,
        },
    };

    var* test_m3d__transform_9down[4]={
        new var[16]{
            30,    24,    18,    0,
            84,    69,    54,    0,
            138,   114,   90,    0,
            192,   158,   124,   1
        },
        new var[16]{
            30,   84,   138,   192,
            24,   69,   114,   158,
            18,   54,   90,    124,
            0,    0,    0,     1
        },
        new var[12]{
            30,    24,    18,
            84,    69,    54,
            138,   114,   90,
            192,   158,   124
        },
        new var[12]{
            30,   84,   138,   192,
            24,   69,   114,   158,
            18,   54,   90,    124
        },
    };
    
    void test_AllFnc__M3d(Matrix_3D::M3D_Type type = Matrix_3D::M3D__4X4_L);
    void test_AllFnc__M3d__AllType(){

        using namespace Matrix_3D;
        var *x = new var[16];
        var *y = new var[16];
        var *z = new var[16];
        var *t_m3d = new var[16];
        var *t_m3d1 = new var[16];
        setup_Matrix3D__Rotate(x, 1.23, X);
        setup_Matrix3D__Rotate(y, 3.45, Y);
        setup_Matrix3D__Rotate(z, 5.67, Z);
        multiplication(t_m3d, x, y, 4);
        multiplication(t_m3d1, t_m3d, z, 4);

        // printf_Matrix(x, 4);
        // printf_Matrix(y, 4);
        // printf_Matrix(z, 4);
        // printf_Matrix(t_m3d, 4);
        // printf_Matrix(t_m3d1, 4);

        // printf_M3dCss(x);
        // printf_M3dCss(y);
        // printf_M3dCss(z);
        // printf_M3dCss(t_m3d);
        // printf_M3dCss(t_m3d1);

        test_AllFnc__M3d(Matrix_3D::M3D__4X4_L);
        test_AllFnc__M3d(Matrix_3D::M3D__4X4_R);
        test_AllFnc__M3d(Matrix_3D::M3D__3X4);
        test_AllFnc__M3d(Matrix_3D::M3D__4X3);
    }

    void test_AllFnc__M3d(Matrix_3D::M3D_Type type){
        printf("\n\n start testing NML_Matrix_3D's function (%d).\n", type);
        using namespace Matrix_3D;
        set_NMLConfig__using_m3d_type(type);
        int l=m3d_w*m3d_h;
        var* t_m3d= new var[l];
        char *ss, *st;
        switch (type)
        {
            case 0:
                ss="test setup_Matrix3D type M3D__4X4_L";
                st="test transform_Matrix3D type M3D__4X4_L";
            break;
            case 1:
                ss="test setup_Matrix3D type M3D__4X4_R";
                st="test transform_Matrix3D type M3D__4X4_R";
            break;
            case 2:
                ss="test setup_Matrix3D type M3D__3X4";
                st="test transform_Matrix3D type M3D__3X4";
            break;
            case 3:
                ss="test setup_Matrix3D type M3D__4X3";
                st="test transform_Matrix3D type M3D__4X3";
            break;
        }

        setup_Matrix3D__Easy(t_m3d, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        check_Test(check_Equal(l, test_m3d__setup[type], t_m3d), ss);
        // printf_Matrix(t_m3d, w, h);

        transform_Matrix3D__Easy(t_m3d, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2);
        check_Test(check_Equal(l, test_m3d__transform_9down[type], t_m3d), st);
        // printf_Matrix(test_m3d__transform_9down[type], m3d_w, m3d_h);
        // printf_Matrix(t_m3d, m3d_w, m3d_h);

        var* s_test_m3d__Translate_1d23_4d56_7d89         =new var[l];
        var* s_test_m3d__Scale_1d234_5d678_9d876          =new var[l];
        var* s_test_m3d__Rotate_EulerXYZ_1d23_3d45_5d67   =new var[l];
        var* s_test_m3d__Reflect_1_2_3                    =new var[l];
        var* s_test_m3d__Shear_X_2                        =new var[l];

        setup_Matrix3D__Easy(s_test_m3d__Translate_1d23_4d56_7d89,
            1,      0,      0,     
            0,      1,      0,     
            0,      0,      1,     
            1.23,   4.56,   7.89
        );
        setup_Matrix3D__Easy(s_test_m3d__Scale_1d234_5d678_9d876,
            1.234,   0,       0,       
            0,       5.678,   0,       
            0,       0,       9.876
        );
        setup_Matrix3D__Easy(s_test_m3d__Rotate_EulerXYZ_1d23_3d45_5d67,
            -0.779232938488844,    -0.4263109334403601,   -0.4594072437426846,
            -0.5483234243005856,   0.10871142553638674,   0.8291702167354582, 
            -0.30354151270842933,   0.8980204975316853,    -0.318467794408827
        );
        setup_Matrix3D__Easy(s_test_m3d__Reflect_1_2_3,
            0.857143,    -0.285714,   -0.428571,   
            -0.285714,   0.428571,    -0.857143,   
            -0.428571,   -0.857143,   -0.285714
        );
        setup_Matrix3D__Easy(s_test_m3d__Shear_X_2,
            1,   2,   1.25,
            0,   1,   0,
            0,   0,   1
        );

        check_Test(check_Equal(l, s_test_m3d__Translate_1d23_4d56_7d89, setup_Matrix3D__Translate(t_m3d, 1.23, 4.56, 7.89)),                       "test setup_Matrix3D__Translate(t_m3d, 1.23, 4.56, 7.89))");
        check_Test(check_Equal(l, s_test_m3d__Scale_1d234_5d678_9d876, setup_Matrix3D__Scale(t_m3d, 1.234, 5.678, 9.876)),                           "test setup_Matrix3D__Scale(t_m3d, 1.234, 5.678, 9.876))");
        check_Test(check_Equal(l, s_test_m3d__Rotate_EulerXYZ_1d23_3d45_5d67, setup_Matrix3D__Rotate__EulerAngles(t_m3d, 1.23, 3.45, 5.67, XYZ)),   "test setup_Matrix3D__Rotate__EulerAngles(t_m3d, 1.23, 3.45, 5.67, XYZ))");
        // Matrix::printf_Matrix(t_m3d, m3d_w, m3d_h);
        // printf_M3dCss(t_m3d);
        check_Test(check_Equal(l, s_test_m3d__Reflect_1_2_3, setup_Matrix3D__Reflect__Collinear(t_m3d, 1, 2, 3)),                                    "test setup_Matrix3D__Reflect__Collinear(t_m3d, 1, 2, 3))");
        check_Test(check_Equal(l, s_test_m3d__Shear_X_2, setup_Matrix3D__Shear(t_m3d, YZ, 2, 1.25)),                                                 "test setup_Matrix3D__Shear(t_m3d, X, 2))");
    }
}


namespace Test_Euler_Angle{
    using namespace Euler_Angle;
    using namespace Matrix_3D;
    using namespace Quaternion;

    void test_MatToEulerAngle();
    void test_Item__MatToEulerAngle(var*& euler_angle__out, var*& euler_angle__org, var*& mat__out, var*& mat__org, Rotation_Order order, char* tip);

    void test_QuatToEulerAngle(){
        // todo
    }

    void test_AllFnc(){
        printf("\ntesting left-handed Eluer-Angle.\n");
        set_NMLConfig__using_m3d_type(M3D__4X4_L);
        test_MatToEulerAngle();
        
        printf("\ntesting right-handed Eluer-Angle.\n");
        set_NMLConfig__using_m3d_type(M3D__4X4_R);
        test_MatToEulerAngle();
        
        printf("\ntesting M3D__3X4 mat Eluer-Angle.\n");
        set_NMLConfig__using_m3d_type(M3D__3X4);
        test_MatToEulerAngle();
        
        printf("\ntesting M3D__4X3 mat Eluer-Angle.\n");
        set_NMLConfig__using_m3d_type(M3D__4X3);
        test_MatToEulerAngle();
    }

    void test_MatToEulerAngle(){
        var* m3d_rotate__m=new var[16];
        var* m3d_rotate__e=new var[16];
        var* rotate_value=new var[3];
        var* rotate_value__out=new var[3];
        
        rotate_value[0]=30*DEG;   rotate_value[1]=90*DEG;       rotate_value[2]=68*DEG;
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XYZ,"泰勒布莱顿欧拉角. XYZ 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XZY,"泰勒布莱顿欧拉角. XZY 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YXZ,"泰勒布莱顿欧拉角. YXZ 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YZX,"泰勒布莱顿欧拉角. YZX 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZXY,"泰勒布莱顿欧拉角. ZXY 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZYX,"泰勒布莱顿欧拉角. ZYX 欧拉角万向锁");

        rotate_value[0]=34*DEG;   rotate_value[1]=26*DEG;       rotate_value[2]=78*DEG;
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XYZ,"泰勒布莱顿欧拉角. XYZ 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XZY,"泰勒布莱顿欧拉角. XZY 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YXZ,"泰勒布莱顿欧拉角. YXZ 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YZX,"泰勒布莱顿欧拉角. YZX 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZXY,"泰勒布莱顿欧拉角. ZXY 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZYX,"泰勒布莱顿欧拉角. ZYX 正常情况");

        
        rotate_value[0]=30*DEG;   rotate_value[1]=180*DEG;      rotate_value[2]=68*DEG;
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XYX,"典型欧拉角. XYX 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XZX,"典型欧拉角. XZX 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YXY,"典型欧拉角. YXY 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YZY,"典型欧拉角. YZY 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZXZ,"典型欧拉角. ZXZ 欧拉角万向锁");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZYZ,"典型欧拉角. ZYZ 欧拉角万向锁");

        rotate_value[0]=34*DEG;   rotate_value[1]=26*DEG;       rotate_value[2]=78*DEG;
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XYX,"典型欧拉角. XYX 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, XZX,"典型欧拉角. XZX 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YXY,"典型欧拉角. YXY 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, YZY,"典型欧拉角. YZY 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZXZ,"典型欧拉角. ZXZ 正常情况");
        test_Item__MatToEulerAngle(rotate_value__out, rotate_value, m3d_rotate__m, m3d_rotate__e, ZYZ,"典型欧拉角. ZYZ 正常情况");

        delete m3d_rotate__m;
        delete m3d_rotate__e;
        delete rotate_value;
        delete rotate_value__out;
    }

    void test_Item__MatToEulerAngle(var*& euler_angle__out, var*& euler_angle__org, var*& mat__out, var*& mat__org, Rotation_Order order, char* tip){
        // printf("\n\n\n%s\n", tip);
        setup_Matrix3D__Rotate__EulerAngles(mat__org, euler_angle__org, order);
        setup_EulerAngle__ByMatrix(euler_angle__out, mat__org, order);
        setup_Matrix3D__Rotate__EulerAngles(mat__out, euler_angle__out, order);
        // printf("\n原欧拉角数据:");    printf_Vec(euler_angle__org, 3);   printf("\n");
        // Matrix::printf_Matrix(mat__org, m3d_w, m3d_h);
        // printf("生成欧拉角数据:");    printf_Vec(euler_angle__out, 3);   printf("\n");
        // Matrix::printf_Matrix(mat__out, m3d_w, m3d_h);
        check_Test(check_Equal(mat__out, mat__org, m3d_w*m3d_h), tip);
    }
}


namespace Test_Quaternion{
    using namespace Vector;
    using namespace Quaternion;
    using namespace Matrix_3D;
    using namespace Euler_Angle;
        
    void test_AllFnc(){
        var 
            *test_quat1         =new var[4],
            *test_quat2         =new var[4],
            *test_quat3         =new var[4],
            *test_quat4         =new var[4],
            *test_quat5         =new var[4],
            *test_quat6         =new var[4],
            *test_quat7         =new var[4],
            *test_quat8         =new var[4],
            *test_quat9         =new var[4],
            *vec_routate_axis   =new var[3]{0.8017837257372732,  0.5345224838248488,   0.2672612419124244},
            *demo_euler         =new var[3],
            *test_euler         =new var[3],
            *demo_m3d_euler     =new var[m3d_w*m3d_h],
            *demo_quat1         =new var[4]{0.462, 0.535, -0.267, 0.817},
            *demo_quat2         =new var[4]{0.357, -0.012, 0.638, 0.683},
            *unit__quat         =new var[4]{0, 0, 0, 1}
            ;

        set_NMLConfig__using_m3d_type(M3D__4X4_R);

        printf("  Now M3d's type is %d \n", _using_m3d_type);
        
        setup_Quaternion(test_quat1, 1, 2, 3, 4);
        normalize(4, test_quat1);
        
        setup_Quaternion__ByAxis(test_quat2, vec_routate_axis, 1.23);
        check_Test(check_Equal(4, test_quat3, test_quat4, 0.001),"axis >> quat == Quat");
        
        demo_euler[0]=34*DEG;   demo_euler[1]=45*DEG;       demo_euler[2]=56*DEG; // XYZ

        setup_Quaternion__ByEulerAngle(test_quat3, demo_euler, XYZ);
        
        setup_Matrix3D__Rotate__EulerAngles(demo_m3d_euler, demo_euler, XYZ);
        setup_Quaternion__ByMatrix(test_quat4, demo_m3d_euler);

        check_Test(check_Equal(4, test_quat3, test_quat4),"EulerAngle >> Quat == Matrix >> Quat");

        setup_Quaternion__Conjugate(test_quat5, test_quat4);

        cross_Quat(test_quat6, test_quat4, test_quat5);
        check_Test(check_Equal(4, unit__quat, test_quat6),"setup_Quaternion__Conjugate");

        setup_Quaternion__Logarithms(test_quat6, test_quat4);
        
        setup_Quaternion__Pow(test_quat6, 2, test_quat4);
        cross_Quat(test_quat7, test_quat4, test_quat4);
        check_Test(check_Equal(4, test_quat6, test_quat7),"quat ^2 == quat*quat");


        setup_Quaternion__Slerp(test_quat8, test_quat4, test_quat6, 0.456);
        printf_Vec(test_quat8, 4);

        var 
            angle,
            *axis                   =new var[3],
            *demo_m3d_euler_q_s1    =new var[m3d_w*m3d_h],
            *demo_m3d_euler_q_org   =new var[m3d_w*m3d_h],
            *demo_m3d_euler_q_tgt   =new var[m3d_w*m3d_h];

        setup_Matrix3D__Rotate__Quaternion(demo_m3d_euler_q_s1, test_quat8);
        setup_Matrix3D__Rotate__Quaternion(demo_m3d_euler_q_org, test_quat4);
        setup_Matrix3D__Rotate__Quaternion(demo_m3d_euler_q_tgt, test_quat6);

        angle=calc_Angle__GetQuaternion(test_quat6);
        calc_Axis__GetQuaternion(axis, test_quat6);

        printf("\n");
        printf("Quat slerp -> matrix:\n");
        printf("org:\n");
        printf_M3dCss(demo_m3d_euler_q_s1);
        printf("s1:\n");
        printf_M3dCss(demo_m3d_euler_q_org);
        printf("tgt:\n");
        printf_M3dCss(demo_m3d_euler_q_tgt);
        printf("transform: rotate3d(%f, %f, %f, %frad);", axis[0], axis[1], axis[2], angle);

        delete test_quat1;
        delete test_quat2;
        delete test_quat3;
        delete test_quat4;
        delete test_quat5;
        delete test_quat6;
        delete test_quat7;
        delete test_quat8;
        delete test_quat9;
        delete vec_routate_axis;
        delete demo_euler;
        delete test_euler;
        delete demo_m3d_euler;
        delete demo_quat1;
        delete demo_quat2;
        delete unit__quat;
    }
}
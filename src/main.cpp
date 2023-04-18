#include <iostream>
#include <chrono>
#include "NML.hpp"
#include "NML_Matrix.hpp"

using namespace std;
using namespace NML;

namespace Test_Vector{
    void test_AllFnc();
}
namespace Test_Matrix{
    void test_transformation();
}

int main(int argc, char **argv){
    cout<< "hello world!"<<endl;
    Test_Vector::test_AllFnc();

    // Test_Matrix::test_transformation();

    return 0;
}

void check_Test(bool flag,char* msg=""){
    if(flag){
        printf("done  -> %s\n", msg);
    }
    else if(msg[0]){
        printf("error -> %s\n", msg);
        // throw msg;
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
        var* vec_zero=new var[3]{0,0,0};
        var* vec_zero__f=create_Values__Clone(unit__vec1,3);

        var* temp   =new var[3];
        var* temp1  =new var[3];

        np(vec_zero__f,3,__TOLERANCE__);

        // test is_Unit
            check_Test(false==is_Unit(3,vec1),                                        "test is_Unit(vec1)");
            check_Test(false==is_Unit(3,vec2),                                        "test is_Unit(vec2)");
            check_Test(true==is_Unit(3,unit__vec1),                                   "test is_Unit(unit__vec1)");
            check_Test(true==is_Unit(3,unit__vec2),                                   "test is_Unit(unit__vec2)");
        // get_Quadrant__v2
            check_Test(1==get_Quadrant__v2(vec1),                                     "test get_Quadrant__v2(vec1)");
        // mag
            check_Test(mag(3,vec1)==mag__vec_1,                                       "test mag(3,vec1)");
            check_Test(mag(3,vec2)==mag__vec_2,                                       "test mag(3,vec2)");
            check_Test(mag(unit__vec2,3)==1,                                          "test mag(unit__vec2,3)");
            check_Test(mag(3,unit__vec1)==1,                                          "test mag(3,unit__vec1)");
        // is_Zero__Strict
            check_Test(is_Zero__Strict(3,vec1)==false,                                "test is_Zero__Strict(3,vec1)");
            check_Test(is_Zero__Strict(vec2,3)==false,                                "test is_Zero__Strict(vec2,3)");
        // is_Zero
            check_Test(is_Zero(3,vec1)==false,                                        "test is_Zero(3,vec1)");
            check_Test(is_Zero(vec2,3)==false,                                        "test is_Zero(vec2,3)");
        // normalize
            clone_To(temp,vec2,3);
            check_Test(check_Equal(3,normalize(temp,3),unit__vec2),                   "test normalize(vec2,3)");
        // instead
            clone_To(temp,vec2,3);
            temp1[0]=-vec2[0];
            temp1[1]=-vec2[1];
            temp1[2]=-vec2[2];
            check_Test(check_Equal(3,instead(temp,3),temp1),                          "test instead(vec2,3)");
        // cross
            // cross_v3 == cross
            cross(temp,vec1,vec2);
            temp1[0]=-1122;
            temp1[1]= 2244;
            temp1[2]=-1122;
            check_Test(check_Equal(3,temp,temp1),                                     "test cross(vec1,vec2)");
        // cross_v2
            check_Test(check_Equal(cross_v2(temp,vec1),-1122*456-2244*123),           "test cross_v2(vec1,vec2)");
        // dot
            check_Test(check_Equal(dot(3,vec2,vec1),2070),                            "test dot(vec1,vec2)");
            check_Test(check_Equal(dot(unit__vec1,vec1,3),919.5575022803088),         "test dot(vec1,unit__vec1)");
        // dot_v2
            check_Test(check_Equal(dot_v2(vec2,vec1),123+123+123+456+456),            "test dot_v2(vec1,vec2)");
        // dot_v3
            check_Test(check_Equal(dot_v3(vec2,vec1),2070),                           "test dot_v3(vec1,vec2)");
            check_Test(check_Equal(dot_v3(unit__vec1,vec1),919.5575022803088),        "test dot_v3(vec1,unit__vec1)");
        // mag
            check_Test(check_Equal(mag(3,vec1),mag__vec_1),                           "test mag(vec1)");
            check_Test(check_Equal(mag(3,vec2),mag__vec_2),                           "test mag(vec2)");
            check_Test(check_Equal(mag(3,unit__vec1),1),                              "test mag(unit__vec1)");
        // mag_v2
        // mag_v3
            check_Test(check_Equal(mag_v3(unit__vec2),1),                             "test mag(unit__vec2)");
            check_Test(check_Equal(mag(3,vec1),mag__vec_1),                           "test mag_3(vec1)");
            check_Test(check_Equal(mag(3,vec2),mag__vec_2),                           "test mag_3(vec2)");
        // np
            clone_To(temp,unit__vec1,3);
            clone_To(temp1,unit__vec2,3);
            
            check_Test(check_Equal(np(temp,3,mag__vec_1), vec1, 3),                   "test np(v1)");
            check_Test(check_Equal(np(temp1,3,mag__vec_2),vec2, 3),                   "test np(v2)");
        // cos_2Vec
            check_Test(check_Equal(cos_2Vec(vec1,vec2),0.6016271623980259),           "test cos_2Vec(v1,v2)");

        delete temp;
        delete temp1;
        delete vec_zero;
        delete vec_zero__f;

    }
}

namespace Test_Matrix{
    using namespace Matrix;
    using namespace chrono;
    
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

    var* m3=new var[9]{9,8,7,6,5,4,3,2,1};

    var* m2=new var[4]{1,2,3,4};
    

    void test_transformation(){
        var* t_m4=create_Values__Clone(m4,16);
        var* t_m4_1=create_Values__Clone(m4,16);
        var* t_m4_2=create_Values__Clone(m4,16);
        var** m4s=new var*[2]{t_m4_1,t_m4_2};

        auto start_time = high_resolution_clock::now();

            // transformation__ExchangeRow(t_m4,4,0,0);
            // transformation__ExchangeRow_PivotToMax(m4s,2,16,4,0,0,4);
            // transformation__ExchangeRow_PivotToMax(t_m4,16,4,0,0,4);
            // transformation__ScaleRow(m4s,2,4,0,1/m4s[0][0]);
            setup_Inverse__Transformation(t_m4,m4,4);


        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();

        cout <<                                                                                     "test_transformation use time: " << duration << " microseconds" << endl;

        cout<<endl;
        printf_Matrix(t_m4,4);
        cout<<endl;
        printf_Matrix(t_m4_1,4);
        cout<<endl;
        printf_Matrix(t_m4_2,4);
        cout<<endl;
        delete t_m4;
        delete t_m4_1;
        delete t_m4_2;
        delete m4s;
    }
}
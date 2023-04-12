#include <iostream>
#include <chrono>
#include "NML.hpp"
#include "NML_Matrix.hpp"

using namespace std;
using namespace NML;

namespace Test_Matrix{
    void test_transformation();
}

int main(int argc, char **argv){
    cout<< "hello world!"<<endl;

    Test_Matrix::test_transformation();

    return 0;
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

        cout << "test_transformation use time: " << duration << " microseconds" << endl;

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
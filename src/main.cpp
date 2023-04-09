#include <iostream>
#include <chrono>
#include "NML.hpp"
#include "NML_Matrix.hpp"

using namespace std;
using namespace NML;

int main(int argc, char **argv){
    cout<< "hello world!"<<endl;

    var* m3=new var[9]{9,8,7,6,5,4,3,2,1};
    // Matrix::setup_Identity(m3,3,3);
    var* m2=new var[4]{1,2,3,4};

    auto start_time = std::chrono::high_resolution_clock::now();

        // Matrix::setup_Resize(m3,m2,2,3,2,3,0,0);
        cout<<Matrix::calc_Det__3(m3)<<endl;
        cout<<Matrix::calc_Det__Transformation(m3,3)<<endl;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    Matrix::printf_Matrix(3,3,m3);

    std::cout << "my Execution time: " << duration << " microseconds" << std::endl;

    return 0;
}


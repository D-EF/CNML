#include <iostream>
#include "NML.hpp"

using namespace std;
using namespace NML;

void printf_val(int length, const var* val){
    int i=0;
    cout<<'['<<val[i];
    for(++i;i<length;++i){
        cout<<val[i];
    }
    cout<<']';
}
inline void printf_val(const Values val){printf_val(val.length, val.data);}


void printf_Matrix(int width, int height, var*& matrix){
    int i=0;
    for(;i<height;++i){
        printf_val(width, matrix+i*width);
    }
}

int main(int argc, char **argv){
    cout<< "hello world!";
    
    return 0;
}
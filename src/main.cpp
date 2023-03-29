#include <iostream>
#include <array>
#include "NML.h"

using namespace std;
using namespace NML;

inline void printf_Val(NML_Value val){printf_Val(val.length,val.data);}
void printf_Val(int length,var* val){
    int i=0;
    do{
        cout<< val[i];
        ++i;
    }while(i<length);
    cout<< endl;
}


int main(int argc,char **argv){
    NML_Value d=NML_Value(2);
    Vector::is_Unit(d);
    Vector::is_Unit(d.length,d.data);
    return 0;
}
#include "NML.h"
#include "Math.h"


using namespace NML;

char Vector::get_Quadrant__v2(var* vec){
        if(vec[0]>=0){
            if(vec[1]>=0)   return '\1';
            else            return '\4';
        }else{
            if(vec[1]>=0)   return '\2'; 
            else            return '\3'; 
        }
}

var Vector::mag(int i,var* vec){
    var Squares=0;
    for(--i;i>=0;--i){
        Squares+=vec[i]*vec[i];
    }
    return sqrt(Squares);
}
#include "NML.h"
#include "Math.h"

using namespace NML;
using namespace Vector;

char get_Quadrant__v2(var* vec2){
        if(vec2[0]>=0){
            if(vec2[1]>=0)  return '\1';
            else    return '\4';
        }else{
            if(vec2[1]>=0)  return '\2'; 
            else    return '\3'; 
        }
}

var mag(int length,var* vec){
    var Squares=0;
    for(int i = length-1;i>=0;--i){
        Squares+=vec[i]*vec[i];
    }
    return sqrt(Squares);
}


bool is_Zero__Strict(const int length,var* vec){

}

bool is_Zero(const int length,var* vec){

}

void reset_Normalization(const int length,var* vec){

}

void reset_Instead(const int length,var* vec){

}

void cross(var* val_left, var* val_right, var* out){

}

var cross_v2(var* val_left, var* val_right){

}

var cos_2Vec(var* vec_left, var*vec_right){

}
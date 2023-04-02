#include "NML.h"

using namespace NML;

void Values::setup(const int length,const var* data){
    int i=length;
    if(this->length<i) delete[] this->data;
    this->data=new var[length];
    this->length=length;
    for(--i;i>=0;--i){
        this->data[i]=data[i];
    }
}

void sum(const int length,var* val_left, var* val_right, var* out){
    for(int i=length-1;i>=0;--i){
        out[i]=val_left[i]+val_left[i];
    }
}

void dif(const int length,var* val_left, var* val_right, var* out){
    for(int i=length-1;i>=0;--i){
        out[i]=val_left[i]-val_left[i];
    }
}

var dot(const int length,var* val_left,var* val_right){
    var rtn=0;
    for(int i=length-1;i>=0;--i){
        rtn+=val_left[i]*val_left[i];
    }
    return rtn;
}

void np(const int length,var* val,var k, var* out){
    for(int i=length-1;i>=0;--i){
        out[i]=val[i]*k;
    }
}
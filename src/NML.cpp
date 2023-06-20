#include "NML.hpp"
#include <iostream>

namespace NML{

    const var NML_TOLERANCE=1e-6;
    
    const var 
        PI      = 3.14159265358979323846,
        DEG     = 0.01745329251994329576,
        DEG_90  = 1.57079632679489661923,
        CYCLES  = 6.28318530717958647692;
    const var &DEG_180 = PI;

    const var ONE_OVER_THREE= 1.0/3;
    const var FOUR_OVER_THREE= 4.0/3;

    void Values::setup(const Idx length, const var* data){
        if(this->length<length) delete[] this->data;
        this->data=new var[length];
        this->length=length;
        for(Idx i=0;i<length;++i){
            this->data[i]=data[i];
        }
    }

    void clone_To(var* to,const var* val, Idx length){
        for(Idx i=0;i<length;++i){
            to[i]=val[i];
        }
    }

    var* create_Values__Clone(const var* val, Idx length){
        var* rtn=new var[length];
        for(Idx i=0;i<length;++i){
            rtn[i]=val[i];
        }
        return rtn;
    }
    
    void printf_Vec(const var* val, Idx length){
        Idx i=0;
        printf("[%f",val[i]);
        for(i++;i<length;i++){
            printf(",%f", val[i]);
        }
        printf("]\n");
    }

    bool check_Equal(Idx length, var*& val_left, var*& val_right, var _tolerance){
        for(Idx i=0;i<length;++i){
            if(!check_Equal(val_left[i], val_right[i], _tolerance))return false;
        }
        return true;
    }

    bool check_Zero(Idx length, var*& value, var _tolerance){
        for(Idx i=0;i<length;++i){
            if(!check_Zero(value[i], _tolerance))return false;
        }
        return true;
    }


    void sum(var*& out, Idx length, var*& val_left, var*& val_right){
        for(Idx i=0;i<length;++i){
            out[i]=val_left[i]+val_left[i];
        }
    }

    void dif(var*& out, Idx length, var*& val_left, var*& val_right){
        for(Idx i=0;i<length;++i){
            out[i]=val_left[i]-val_left[i];
        }
    }

    var dot(Idx length, var*& val_left, var*& val_right){
        var rtn=0;
        for(Idx i=0;i<length;++i){
            rtn+=val_left[i]*val_right[i];
        }
        return rtn;
    }

    var*& np(var*& out, Idx length, var k){
        for(Idx i=0;i<length;++i){
            out[i]*=k;
        }
        return out;
    }
}
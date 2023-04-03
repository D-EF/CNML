#include "NML.hpp"

namespace NML{

    void Values::setup(const int length,const var* data){
        int i=length;
        if(this->length<i) delete[] this->data;
        this->data=new var[length];
        this->length=length;
        for(--i;i>=0;--i){
            this->data[i]=data[i];
        }
    }


    bool check_Equal(int i,var*& val_left, var*& val_right, var _tolerance=__TOLERANCE__){
        for(--i;i>=0;--i){
            if(!check_Equal(val_left[i],val_right[i],_tolerance))return false;
        }
        return true;
    }

    void sum(int i,var*& val_left, var*& val_right, var*& out){
        for(--i;i>=0;--i){
            out[i]=val_left[i]+val_left[i];
        }
    }

    void dif(int i,var*& val_left, var*& val_right, var*& out){
        for(--i;i>=0;--i){
            out[i]=val_left[i]-val_left[i];
        }
    }

    var dot(int i,var*& val_left,var*& val_right){
        var rtn=0;
        for(--i;i>=0;--i){
            rtn+=val_left[i]*val_left[i];
        }
        return rtn;
    }

    void np(int i,var*& val,var k, var*& out){
        for(--i;i>=0;--i){
            out[i]=val[i]*k;
        }
    }
}
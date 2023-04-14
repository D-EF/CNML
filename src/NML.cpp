#include "NML.hpp"
#include <iostream>

namespace NML{

    void Values::setup(const int length, const var* data){
        if(this->length<length) delete[] this->data;
        this->data=new var[length];
        this->length=length;
        for(int i=0;i<length;++i){
            this->data[i]=data[i];
        }
    }

    var* create_Values__Clone(const var* val, int length){
        var* rtn=new var[length];
        for(int i=0;i<length;++i){
            rtn[i]=val[i];
        }
        return rtn;
    }
    
    void printf_val(const var* val, int length){
        int i=0;
        std::cout<<'['<<val[i];
        for(i++;i<length;i++){
            std::cout<<','<<val[i];
        }
        std::cout<<"]\n";
    }

    bool check_Equal(int length, var*& val_left, var*& val_right, var _tolerance){
        for(int i=0;i<length;++i){
            if(!check_Equal(val_left[i], val_right[i], _tolerance))return false;
        }
        return true;
    }

    bool check_Zero(int length, var*& value, var _tolerance){
        for(int i=0;i<length;++i){
            if(!check_Zero(value[i], _tolerance))return false;
        }
        return true;
    }


    void sum(int length, var*& val_left, var*& val_right, var*& out){
        for(int i=0;i<length;++i){
            out[i]=val_left[i]+val_left[i];
        }
    }

    void dif(int length, var*& val_left, var*& val_right, var*& out){
        for(int i=0;i<length;++i){
            out[i]=val_left[i]-val_left[i];
        }
    }

    var dot(int length, var*& val_left, var*& val_right){
        var rtn=0;
        for(int i=0;i<length;++i){
            rtn+=val_left[i]*val_left[i];
        }
        return rtn;
    }

    void np(var*& val, int length, var k){
        for(int i=0;i<length;++i){
            val[i]*=k;
        }
    }
}
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

    void clone_To(var* to,const var* val, int length){
        for(int i=0;i<length;++i){
            to[i]=val[i];
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
        // std::cout<<'['<<val[i];
        printf("[%f",val[i]);
        for(i++;i<length;i++){
            // std::cout<<','<<val[i];
            printf(",%f", val[i]);
        }
        // std::cout<<"]\n";
        printf("]\n");
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


    void sum(var*& out, int length, var*& val_left, var*& val_right){
        for(int i=0;i<length;++i){
            out[i]=val_left[i]+val_left[i];
        }
    }

    void dif(var*& out, int length, var*& val_left, var*& val_right){
        for(int i=0;i<length;++i){
            out[i]=val_left[i]-val_left[i];
        }
    }

    var dot(int length, var*& val_left, var*& val_right){
        var rtn=0;
        for(int i=0;i<length;++i){
            rtn+=val_left[i]*val_right[i];
        }
        return rtn;
    }

    var*& np(var*& out, int length, var k){
        for(int i=0;i<length;++i){
            out[i]*=k;
        }
        return out;
    }
}
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

    namespace Matrix_2D{
        void set_M2dConfig__using_matrix_type(int type){
            _using_matrix_type=type;
            switch (_using_matrix_type){
                case M2D__2X3:
                    w  =2,   h  =3,
                    mxx=0,   mxy=1,    mx_null=0,
                    myx=2,   myy=3,    my_null=0,
                    tx =4,   ty =5,    mi_full=0;
                break;

                case M2D__3X2:
                    w  =3,        h  =2,
                    mxx=0,        myx=1,        ty=2,
                    mxy=3,        myy=4,        ty=5,
                    mx_null =0,   my_null =0,   mi_full=0;
                break;

                case M2D__3X3_L:
                    w  =3,   h  =3,
                    mxx=0,   mxy=1,   mx_null=2,
                    myx=3,   myy=4,   my_null=5,
                    tx =6,   ty =7,   mi_full=8;
                break;

                case M2D__3X3_R:
                    w  =3,        h  =3,
                    mxx=0,        myx=1,        tx=2,
                    mxy=3,        myy=4,        ty=5,
                    mx_null =6,   my_null =7,   mi_full=8;
                break;
            }
        }
    }
}
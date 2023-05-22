#include "NML_Vector.hpp"

namespace NML{
    namespace Vector{

        char get_Quadrant__v2(var*& vec2){
                if(vec2[0]>=0){
                    if(vec2[1]>=0)    return '\1';
                    else              return '\4';
                }else{
                    if(vec2[1]>=0)    return '\2';
                    else              return '\3';
                }
        }

        var mag(Idx_VM length, var*& vec){
            var Squares=0;
            for(Idx_VM i=0; i<length; ++i){
                Squares+=vec[i]*vec[i];
            }
            return sqrt(Squares);
        }

        bool is_Zero__Strict(Idx_VM length, var*& vec){
            for(Idx_VM i=0; i<length; ++i){
                if(vec[i]!=0) return false;
            }
            return true;
        }

        bool is_Zero(Idx_VM length, var*& vec){
            for(Idx_VM i=0; i<length; ++i){
                if(vec[i]!=0) return false;
            }
            return true;
        }

        var*& normalize(Idx_VM length, var*& vec){
            if(is_Zero__Strict(length, vec)){
                vec[0]=1;
                for(Idx_VM i=1; i<length; ++i){
                    vec[i]=0;
                }
            }else{
                var magSq = mag(length, vec),
                oneOverMag = 1.0/magSq;
                for(Idx_VM i=0; i<length; ++i){
                    vec[i] *= oneOverMag;
                }
            }
            return vec;
        }

        var*& instead(Idx_VM length, var*& vec){
            for(Idx_VM i=0; i<length; ++i){
                vec[i] = -vec[i];
            }
            return vec;
        }
    }
}
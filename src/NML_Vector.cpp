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

        var mag(int length, var*& vec){
            var Squares=0;
            for(int i=0; i<length; ++i){
                Squares+=vec[i]*vec[i];
            }
            return sqrt(Squares);
        }

        bool is_Zero__Strict(int length, var*& vec){
            for(int i=0; i<length; ++i){
                if(vec[i]!=0) return false;
            }
            return true;
        }

        bool is_Zero(int length, var*& vec){
            for(int i=0; i<length; ++i){
                if(vec[i]!=0) return false;
            }
            return true;
        }

        void normalize(int length, var*& vec){
            if(!is_Zero__Strict(length, vec)){
                vec[0]=1;
                for(int i=0; i<length; ++i){
                    vec[i]=0;
                }
            }else{
                var magSq = mag(length, vec),
                oneOverMag=0;
                oneOverMag = 1.0/magSq;
                for(int i=0; i<length; ++i){
                    vec[i] *= oneOverMag;
                }
            }
        }

        void instead(int length, var*& vec){
            for(int i=0; i<length; ++i){
                vec[i] = -vec[i];
            }
        }
    }
}
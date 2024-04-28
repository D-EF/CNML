/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:50:02
 * @FilePath: \CNML\src\Algebra\NML_Vector.cpp
 * @Description: 基本向量操作
 */

#include "./NML_Vector.hpp"

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
            var rtn_squares=0;
            for(Idx_VM i=0; i<length; ++i) rtn_squares+=vec[i]*vec[i];
            return sqrt(rtn_squares);
        }

        bool is_Zero__Strict(Idx_VM length, var*& vec){
            for(Idx_VM i=0; i<length; ++i){
                if(vec[i]!=0) return false;
            }
            return true;
        }

        bool is_Zero(Idx_VM length, var*& vec, var _tolerance){
            for(Idx_VM i=0; i<length; ++i){
                if(abs(vec[i])>_tolerance) return false;
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
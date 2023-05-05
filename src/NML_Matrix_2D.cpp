#ifndef __NML_MATRIX_2D__
#define __NML_MATRIX_2D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_2D{
        var*& setup_Matrix2D(var*& out, var a, var b, var c, var d, var e, var f){
            if(mi_full){
                out[mx_null]=0;
                out[my_null]=0;
                out[mi_full]=1;
            }
            out[mxx]=a;   out[mxy]=b;
            out[myx]=c;   out[myy]=d;
            out[tx] =e;   out[ty] =f;
            return out;
        }
    }
}

#endif
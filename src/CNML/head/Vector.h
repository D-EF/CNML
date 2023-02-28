#ifndef __CNML_VECTOR__
#define __CNML_VECTOR__
#include <stdio.h>
#include <stdlib.h>

namespace CNML{

    template<typename VALUE_TYPE >

    class Vector{
        public:
            int length;
            float* data;
            Vector(int length):length(length){
                this->data=(malloc(sizeof(float)*length));
            }
            Vector(int length,float* data);
            Vector(Vector &vec);
            ~(){
                free(this->data);
            }
    };
    class Vector3{
        public:
            float x,y,z;
    };
    class Vector2{
        public:
            float x,y;
    };
    
};

#endif
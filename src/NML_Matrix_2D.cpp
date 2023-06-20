#include "NML_Matrix_2D.hpp"

namespace NML{
    namespace Matrix_2D{
        //默认使用 3*3 左乘向量 (vector * matrix)
        M2D_Type _using_m2d_type=M2D__3X3_L;
        // 数据类型的数据对应宽高
            Idx_VM m2d_w=3,m2d_h=3;
        // 数据类型的数据对应下标
            Idx_VM 
                mxx=0,   mxy=1,   mxz=2,
                myx=3,   myy=4,   myz=5,
                mzx=6,   mzy=7,   mzz=8;
        //
        
    }
}
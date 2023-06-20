#include "NML_Matrix_3D.hpp"

namespace NML{
    namespace Matrix_3D{
        //默认使用 3*3 左乘向量 (vector * matrix)
        M3D_Type _using_m3d_type=M3D__4X4_L;
        // 数据类型的数据对应宽高
            Idx_VM m3d_w=4,m3d_h=4,m3d_length=16;
        // 数据类型的数据对应下标
            Idx_VM 
                mxx=0,    mxy=1,    mxz=2,    mxw=3,
                myx=4,    myy=5,    myz=6,    myw=7,
                mzx=8,    mzy=9,    mzz=10,   mzw=11,
                mwx=12,   mwy=13,   mwz=14,   mww=15;
    }
}
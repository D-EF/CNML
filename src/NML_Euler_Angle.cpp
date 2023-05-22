#include  "NML_Euler_Angle.hpp"

namespace NML{
    namespace Euler_Angle{
        var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order){
            switch (order)
            {
                case XYZ: return setup_EulerAngle__ByMatrix__XYZ(out,mat); break;
                case XZY: return setup_EulerAngle__ByMatrix__XZY(out,mat); break;
                case YXZ: return setup_EulerAngle__ByMatrix__YXZ(out,mat); break;
                case YZX: return setup_EulerAngle__ByMatrix__YZX(out,mat); break;
                case ZXY: return setup_EulerAngle__ByMatrix__ZXY(out,mat); break;
                case ZYX: return setup_EulerAngle__ByMatrix__ZYX(out,mat); break;
                case XYX: return setup_EulerAngle__ByMatrix__XYX(out,mat); break;
                case XZX: return setup_EulerAngle__ByMatrix__XZX(out,mat); break;
                case YXY: return setup_EulerAngle__ByMatrix__YXY(out,mat); break;
                case YZY: return setup_EulerAngle__ByMatrix__YZY(out,mat); break;
                case ZXZ: return setup_EulerAngle__ByMatrix__ZXZ(out,mat); break;
                case ZYZ: return setup_EulerAngle__ByMatrix__ZYZ(out,mat); break;
            }
            return out;
        }

        var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order){
            // todo
            return out;
        }

        using namespace Matrix_3D;
        
        var*& setup_EulerAngle__ByMatrix__XYZ(var*& out, var*&mat){   if(0.99999<fabs(mat[mxz])){out[1]=-DEG_90*mat[mxz];   out[0]=0;   out[2]=mat[mxz]*atan2(-mat[mzy],+mat[myy]); }   else{out[1]=-asin(mat[mxz]);   out[2]=atan2(+mat[mxy],+mat[mxx]);   out[0]=atan2(+mat[myz],+mat[mzz]);   }     return out;}
        var*& setup_EulerAngle__ByMatrix__XZY(var*& out, var*&mat){   if(0.99999<fabs(mat[mxy])){out[1]=+DEG_90*mat[mxy];   out[0]=0;   out[2]=mat[mxy]*atan2(+mat[myz],+mat[mzz]); }   else{out[1]=+asin(mat[mxy]);   out[2]=atan2(-mat[mxz],+mat[mxx]);   out[0]=atan2(-mat[mzy],+mat[myy]);   }     return out;}
        var*& setup_EulerAngle__ByMatrix__YXZ(var*& out, var*&mat){   if(0.99999<fabs(mat[myz])){out[1]=+DEG_90*mat[myz];   out[0]=0;   out[2]=mat[myz]*atan2(+mat[mzx],+mat[mxx]); }   else{out[1]=+asin(mat[myz]);   out[2]=atan2(-mat[myx],+mat[myy]);   out[0]=atan2(-mat[mxz],+mat[mzz]);   }     return out;}
        var*& setup_EulerAngle__ByMatrix__YZX(var*& out, var*&mat){   if(0.99999<fabs(mat[myx])){out[1]=-DEG_90*mat[myx];   out[0]=0;   out[2]=mat[myx]*atan2(-mat[mxz],+mat[mzz]); }   else{out[1]=-asin(mat[myx]);   out[2]=atan2(+mat[myz],+mat[myy]);   out[0]=atan2(+mat[mzx],+mat[mxx]);   }     return out;}
        var*& setup_EulerAngle__ByMatrix__ZXY(var*& out, var*&mat){   if(0.99999<fabs(mat[mzy])){out[1]=-DEG_90*mat[mzy];   out[0]=0;   out[2]=mat[mzy]*atan2(-mat[myx],+mat[mxx]); }   else{out[1]=-asin(mat[mzy]);   out[2]=atan2(+mat[mzx],+mat[mzz]);   out[0]=atan2(+mat[mxy],+mat[myy]);   }     return out;}
        var*& setup_EulerAngle__ByMatrix__ZYX(var*& out, var*&mat){   if(0.99999<fabs(mat[mzx])){out[1]=+DEG_90*mat[mzx];   out[0]=0;   out[2]=mat[mzx]*atan2(+mat[mxy],+mat[myy]); }   else{out[1]=+asin(mat[mzx]);   out[2]=atan2(-mat[mzy],+mat[mzz]);   out[0]=atan2(-mat[myx],+mat[mxx]);   }     return out;}

        var*& setup_EulerAngle__ByMatrix__XYX(var*& out, var*&mat){   if(0.99999<fabs(mat[mxx])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[mxx]*atan2(-mat[mzy],+mat[myy]); }   else{out[1]=acos(mat[mxx]);    out[2]=atan2(+mat[mxy],-mat[mxz]);   out[0]=atan2(+mat[myx],+mat[mzx]);   }      return out;}
        var*& setup_EulerAngle__ByMatrix__XZX(var*& out, var*&mat){   if(0.99999<fabs(mat[mxx])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[mxx]*atan2(+mat[myz],+mat[mzz]); }   else{out[1]=acos(mat[mxx]);    out[2]=atan2(+mat[mxz],+mat[mxy]);   out[0]=atan2(+mat[mzx],-mat[myx]);   }      return out;}
        var*& setup_EulerAngle__ByMatrix__YXY(var*& out, var*&mat){   if(0.99999<fabs(mat[myy])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[myy]*atan2(+mat[mzx],+mat[mxx]); }   else{out[1]=acos(mat[myy]);    out[2]=atan2(+mat[myx],+mat[myz]);   out[0]=atan2(+mat[mxy],-mat[mzy]);   }      return out;}
        var*& setup_EulerAngle__ByMatrix__YZY(var*& out, var*&mat){   if(0.99999<fabs(mat[myy])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[myy]*atan2(-mat[mxz],+mat[mzz]); }   else{out[1]=acos(mat[myy]);    out[2]=atan2(+mat[myz],-mat[myx]);   out[0]=atan2(+mat[mzy],+mat[mxy]);   }      return out;}
        var*& setup_EulerAngle__ByMatrix__ZXZ(var*& out, var*&mat){   if(0.99999<fabs(mat[mzz])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[mzz]*atan2(-mat[myx],+mat[mxx]); }   else{out[1]=acos(mat[mzz]);    out[2]=atan2(+mat[mzx],-mat[mzy]);   out[0]=atan2(+mat[mxz],+mat[myz]);   }      return out;}
        var*& setup_EulerAngle__ByMatrix__ZYZ(var*& out, var*&mat){   if(0.99999<fabs(mat[mzz])){out[1]=DEG_180;            out[0]=0;   out[2]=mat[mzz]*atan2(+mat[mxy],+mat[myy]); }   else{out[1]=acos(mat[mzz]);    out[2]=atan2(+mat[mzy],+mat[mzx]);   out[0]=atan2(+mat[myz],-mat[mxz]);   }      return out;}
    }
}
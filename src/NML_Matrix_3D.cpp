#include "NML.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{
    namespace Matrix_3D{
        
        var*& setup_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        ){
            if(mi_full){
                out[mx_null]=0;
                out[my_null]=0;
                out[mz_null]=0;
                out[mi_full]=1;
            }
            out[mxx]= value_mxx;   out[mxy]= value_mxy;   out[mxz]=value_mxz;
            out[myx]= value_myx;   out[myy]= value_myy;   out[myz]=value_myz;
            out[mzx]= value_mzx;   out[mzy]= value_mzy;   out[mzz]=value_mzz;
            out[tx] = value_tx ;   out[ty] = value_ty ;   out[tz] =value_tz ;
            return out;
        }

        var*& transform_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        ){
            setup_Matrix3D(out,
                out[mxx]*value_mxx + out[mxy]*value_myx + out[mxz]+value_mzx,       out[mxx]*value_mxy + out[mxy]*value_myy + out[mxz]*value_mzy,       out[mxx]*value_mxz + out[mxy]*value_myz + out[mxz]*value_mzz,
                out[myx]*value_mxx + out[myy]*value_myx + out[myz]+value_mzx,       out[myx]*value_mxy + out[myy]*value_myy + out[myz]*value_mzy,       out[myx]*value_mxz + out[myy]*value_myz + out[myz]*value_mzz,
                out[mzx]*value_mxx + out[mzy]*value_myx + out[mzz]+value_mzx,       out[mzx]*value_mxy + out[mzy]*value_myy + out[mzz]*value_mzy,       out[mzx]*value_mxz + out[mzy]*value_myz + out[mzz]*value_mzz,
                out[tx]*value_mxx+out[ty]*value_myx+out[tz]+value_mzx + value_tx,   out[tx]*value_mxy+out[ty]*value_myy+out[tz]+value_mzy + value_tx,   out[tx]*value_mxz+out[ty]*value_myz+out[tz]+value_mzz + value_tx
            );
        }

        var*& setup_Rotate(var*& out, var theta, Axis axis=X){
            var c=cos(theta), s=sin(theta);
            switch (axis)
            {
                case X:
                    return setup_Matrix3D(out,
                        1,   0,    0,
                        0,   c,    s,
                        0,   -s,   c,
                        0,   0,    0
                    );
                break;
                
                case Y:
                    return setup_Matrix3D(out,
                        c,   0,   -s,
                        0,   1,   0,
                        s,   0,   c,
                        0,   0,   0
                    );
                break;
                
                case Z:
                    return setup_Matrix3D(out,
                        c,    s,   0,
                        -s,   c,   0,
                        0,    0,   1,
                        0,    0,   0
                    );
                break;
                default:
                    return out;
                break;

            }
        }
        var*& transform_Rotate(var*& out, var theta, Axis axis=X){
            var c=cos(theta), s=sin(theta);
            switch (axis)
            {
                case X:
                    return transform_Matrix3D(out,
                        1,   0,    0,
                        0,   c,    s,
                        0,   -s,   c,
                        0,   0,    0
                    );
                break;
                
                case Y:
                    return transform_Matrix3D(out,
                        c,   0,   -s,
                        0,   1,   0,
                        s,   0,   c,
                        0,   0,   0
                    );
                break;
                
                case Z:
                    return transform_Matrix3D(out,
                        c,    s,   0,
                        -s,   c,   0,
                        0,    0,   1,
                        0,    0,   0
                    );
                break;
                default:
                    return out;
                break;

            }
        }

        var*& setup_Rotate__EulerAngles(var*& out, var*& thetas, Rotation_Order order=XYZ){
            Axis axis= static_cast<Axis>(order>>4 &0b11);
            setup_Rotate(out,thetas[0],axis);

            axis= static_cast<Axis>(order>>2 &0b11);
            transform_Rotate(out,thetas[0],axis);
            
            axis= static_cast<Axis>(order &0b11);
            return  transform_Rotate(out,thetas[0],axis);
        }
    }
}
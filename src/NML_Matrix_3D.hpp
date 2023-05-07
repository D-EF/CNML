#ifndef __NML_MATRIX_3D__
#define __NML_MATRIX_3D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_3D{
        /**
         * @brief 写入矩阵数据
         */
        var*& setup_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        );

        var*& transform_Matrix3D(var*& out, 
            var value_mxx, var value_mxy, var value_mxz,
            var value_myx, var value_myy, var value_myz,
            var value_mzx, var value_mzy, var value_mzz,
            var value_tx , var value_ty , var value_tz
        );
        
        // open * setup * open

            /***/
            inline var*& setup_Translate(var*& out, var translate_x, var translate_y=0, var translate_z=0){
                return setup_Matrix3D(out, 
                    1,             0,             0,
                    0,             1,             0,
                    0,             0,             1,
                    translate_x,   translate_y,   translate_z
                );
            }

            /***/
            var*& setup_Scale(var*& out,var scale_x, var scale_y,var scale_z){
                return setup_Matrix3D(out, 
                    scale_x,   0,         0,
                    0,         scale_y,   0,
                    0,         0,         scale_z,
                    0,         0,         0
                );
            }

            /***/
            var*& setup_Rotate(var*& out, var theta, Axis axis=X);
            
            /***/
            var*& setup_Rotate__EulerAngles(var*& out, var*& thetas, Rotation_Order order=XYZ);

            /***/
            inline var*& setup_Horizontal(var*& out, var normal_x, var normal_y, var normal_z){
                var i2xy=-2*normal_x*normal_y,
                    i2xz=-2*normal_x*normal_z,
                    i2yz=-2*normal_y*normal_z;
                return setup_Matrix3D(out,
                    1-2*normal_x*normal_x,   i2xy,                    i2xz,
                    i2xy,                    1-2*normal_y*normal_y,   i2yz,
                    i2xz,                    i2yz,                    1-2*normal_z*normal_z,
                    0,                       0,                       0
                );
            }

            /***/
            inline var*& setup_Shear(var*& out,var axis_x, var axis_y, var k){

            }

        // end  * setup * end 

        // open * transform * open

            /***/
            var*& transform_Translate(var*& out, var translate_x, var translate_y=0, var translate_z=0);

            /***/
            var*& transform_Scale(var*& out,var scale_x, var scale_y,var scale_z);

            /***/
            var*& transform_Rotate(var*& out, var theta, Axis axis=X);

            /***/
            var*& transform_Rotate__EulerAngles(var*& out, var*& thetas, Rotation_Order order=XYZ);

            /***/
            var*& transform_Horizontal(var*& out, var normal_x, var normal_y);

            /***/
            var*& transform_Shear(var*& out,var axis_x, var axis_y, var k);

        // end  * transform * end 

        const var*  M3D__ROTATE_LEFT_X_CCW_90DEG  = new var[16]{ 1, 0, 0, 0, 0, 0, 1, 0, 0,-1, 0, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_LEFT_X_CW_90DEG   = new var[16]{ 1, 0, 0, 0, 0, 0,-1, 0, 0, 1, 0, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_X_180DEG          = new var[16]{ 1, 0, 0, 0, 0,-1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_LEFT_Y_CCW_90DEG  = new var[16]{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_LEFT_Y_CW_90DEG   = new var[16]{ 0, 0,-1, 0, 0, 1, 0, 0,-1, 0, 0, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_Y_180DEG          = new var[16]{-1, 0, 0, 0, 0, 1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_LEFT_Z_CCW_90DEG  = new var[16]{ 0, 1, 0, 0,-1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_LEFT_Z_CW_90DEG   = new var[16]{ 0,-1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        const var*  M3D__ROTATE_Z_180DEG          = new var[16]{-1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        const var*& M3D__ROTATE_RIGHT_X_CW_90DEG  = ROTATE_LEFT_X_CCW_90DEG;
        const var*& M3D__ROTATE_RIGHT_X_CCW_90DEG = ROTATE_LEFT_X_CW_90DEG;
        const var*& M3D__ROTATE_RIGHT_Y_CW_90DEG  = ROTATE_LEFT_Y_CCW_90DEG;
        const var*& M3D__ROTATE_RIGHT_Y_CCW_90DEG = ROTATE_RIGHT_Y_CCW_90DEG;
        const var*& M3D__ROTATE_RIGHT_Z_CW_90DEG  = ROTATE_LEFT_Z_CCW_90DEG;
        const var*& M3D__ROTATE_RIGHT_Z_CCW_90DEG = ROTATE_RIGHT_Z_CCW_90DEG;
    }
}

#endif
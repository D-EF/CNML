#ifndef __NML_Euler_Angle__
#define __NML_Euler_Angle__
#include "NML.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{
    const var 
        PI      = 3.14159265358979323846,
        DEG     = 0.01745329251994329576,
        DEG_90  = 1.57079632679489661923,
        CYCLES  = 6.28318530717958647692;
    const var &DEG_180 = PI;

    namespace Euler_Angle{
        
        /**
         * @brief 写入数据
         * @param out      操作对象
         * @param r1       第 1 次旋转量
         * @param r2       第 2 次旋转量
         * @param r3       第 3 次旋转量
         * @return 修改 out 并输出
         */
        inline var*& setup_EulerAngle(var*& out, var r1, var r2, var r3){
            out[0]=r1;
            out[1]=r2;
            out[2]=r3;
            return out;
        }
        
        /**
         * @brief 使用旋转矩阵生成欧拉角
         * @param out       输出对象
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order=XYZ);

        var*& setup_EulerAngle__ByMatrix__XYZ(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__XZY(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__YXZ(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__YZX(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__ZXY(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__ZYX(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__XYX(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__XZX(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__YXY(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__YZY(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__ZXZ(var*& out,var*& mat);
        var*& setup_EulerAngle__ByMatrix__ZYZ(var*& out,var*& mat);
        
        /**
         * @brief 使用四元数生成欧拉角
         * @param out       输出对象
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order=XYZ);
        
    }
}

#endif
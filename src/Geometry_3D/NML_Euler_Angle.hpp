/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 17:06:13
 * @FilePath: \CNML\src\Geometry_3D\NML_Euler_Angle.hpp
 * @Description: 欧拉角
 */

#ifndef __NML_Euler_Angle__
#define __NML_Euler_Angle__
#include "NML.hpp"
#include "Algebra/NML_Matrix.hpp"
#include "./NML_Matrix_3D.hpp"

namespace NML{
    namespace Euler_Angle{
        using namespace Matrix_3D;
        
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
         * @param out       输出目标
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        inline var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order=XYZ);

        inline var*& setup_EulerAngle__ByMatrix__XYZ(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__XZY(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__YXZ(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__YZX(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__ZXY(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__ZYX(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__XYX(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__XZX(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__YXY(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__YZY(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__ZXZ(var*& out, var*& mat);
        inline var*& setup_EulerAngle__ByMatrix__ZYZ(var*& out, var*& mat);
        
        /**
         * @brief 使用四元数生成欧拉角
         * @param out       输出目标
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        inline var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order=XYZ);
        
        inline var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order){
            switch (order)
            {
                case XYZ: return setup_EulerAngle__ByMatrix__XYZ(out, mat); break;
                case XZY: return setup_EulerAngle__ByMatrix__XZY(out, mat); break;
                case YXZ: return setup_EulerAngle__ByMatrix__YXZ(out, mat); break;
                case YZX: return setup_EulerAngle__ByMatrix__YZX(out, mat); break;
                case ZXY: return setup_EulerAngle__ByMatrix__ZXY(out, mat); break;
                case ZYX: return setup_EulerAngle__ByMatrix__ZYX(out, mat); break;
                case XYX: return setup_EulerAngle__ByMatrix__XYX(out, mat); break;
                case XZX: return setup_EulerAngle__ByMatrix__XZX(out, mat); break;
                case YXY: return setup_EulerAngle__ByMatrix__YXY(out, mat); break;
                case YZY: return setup_EulerAngle__ByMatrix__YZY(out, mat); break;
                case ZXZ: return setup_EulerAngle__ByMatrix__ZXZ(out, mat); break;
                case ZYZ: return setup_EulerAngle__ByMatrix__ZYZ(out, mat); break;
            }
            return out;
        }

        inline var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order){
            var temp_mat_data[m3d_length];
            var *temp_mat=temp_mat_data;
            Matrix_3D::setup_Matrix3D__Rotate__Quaternion(temp_mat, quat);
            return setup_EulerAngle__ByMatrix(out, temp_mat, order);
        }

        
        inline var*& setup_EulerAngle__ByMatrix__ZYX(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mxz])){out[1]=-DEG_90*mat[mxz];   out[2]=0;   out[0]=mat[mxz]*atan2(-mat[mzy], +mat[myy]); }   else{out[1]=-asin(mat[mxz]);   out[0]=atan2(+mat[mxy], +mat[mxx]);   out[2]=atan2(+mat[myz], +mat[mzz]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__YZX(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mxy])){out[1]=+DEG_90*mat[mxy];   out[2]=0;   out[0]=mat[mxy]*atan2(+mat[myz], +mat[mzz]); }   else{out[1]=+asin(mat[mxy]);   out[0]=atan2(-mat[mxz], +mat[mxx]);   out[2]=atan2(-mat[mzy], +mat[myy]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__ZXY(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[myz])){out[1]=+DEG_90*mat[myz];   out[2]=0;   out[0]=mat[myz]*atan2(+mat[mzx], +mat[mxx]); }   else{out[1]=+asin(mat[myz]);   out[0]=atan2(-mat[myx], +mat[myy]);   out[2]=atan2(-mat[mxz], +mat[mzz]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__XZY(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[myx])){out[1]=-DEG_90*mat[myx];   out[2]=0;   out[0]=mat[myx]*atan2(-mat[mxz], +mat[mzz]); }   else{out[1]=-asin(mat[myx]);   out[0]=atan2(+mat[myz], +mat[myy]);   out[2]=atan2(+mat[mzx], +mat[mxx]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__YXZ(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mzy])){out[1]=-DEG_90*mat[mzy];   out[2]=0;   out[0]=mat[mzy]*atan2(-mat[myx], +mat[mxx]); }   else{out[1]=-asin(mat[mzy]);   out[0]=atan2(+mat[mzx], +mat[mzz]);   out[2]=atan2(+mat[mxy], +mat[myy]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__XYZ(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mzx])){out[1]=+DEG_90*mat[mzx];   out[2]=0;   out[0]=mat[mzx]*atan2(+mat[mxy], +mat[myy]); }   else{out[1]=+asin(mat[mzx]);   out[0]=atan2(-mat[mzy], +mat[mzz]);   out[2]=atan2(-mat[myx], +mat[mxx]);   }   return out;}
        //
        inline var*& setup_EulerAngle__ByMatrix__XYX(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mxx])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[mxx]*atan2(-mat[mzy], +mat[myy]); }   else{out[1]=acos(mat[mxx]);    out[0]=atan2(+mat[mxy], -mat[mxz]);   out[2]=atan2(+mat[myx], +mat[mzx]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__XZX(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mxx])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[mxx]*atan2(+mat[myz], +mat[mzz]); }   else{out[1]=acos(mat[mxx]);    out[0]=atan2(+mat[mxz], +mat[mxy]);   out[2]=atan2(+mat[mzx], -mat[myx]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__YXY(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[myy])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[myy]*atan2(+mat[mzx], +mat[mxx]); }   else{out[1]=acos(mat[myy]);    out[0]=atan2(+mat[myx], +mat[myz]);   out[2]=atan2(+mat[mxy], -mat[mzy]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__YZY(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[myy])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[myy]*atan2(-mat[mxz], +mat[mzz]); }   else{out[1]=acos(mat[myy]);    out[0]=atan2(+mat[myz], -mat[myx]);   out[2]=atan2(+mat[mzy], +mat[mxy]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__ZXZ(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mzz])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[mzz]*atan2(-mat[myx], +mat[mxx]); }   else{out[1]=acos(mat[mzz]);    out[0]=atan2(+mat[mzx], -mat[mzy]);   out[2]=atan2(+mat[mxz], +mat[myz]);   }   return out;}
        inline var*& setup_EulerAngle__ByMatrix__ZYZ(var*& out, var*& mat){   if(NML_TOLERANCE_D1<abs(mat[mzz])){out[1]=DEG_180;            out[2]=0;   out[0]=mat[mzz]*atan2(+mat[mxy], +mat[myy]); }   else{out[1]=acos(mat[mzz]);    out[0]=atan2(+mat[mzy], +mat[mzx]);   out[2]=atan2(+mat[myz], -mat[mxz]);   }   return out;}
    }
}

#endif
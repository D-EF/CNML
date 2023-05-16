#ifndef __NML_Euler_Angle__
#define __NML_Euler_Angle__
#include "NML.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{
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
        
        /**
         * @brief 使用四元数生成欧拉角
         * @param out       输出对象
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order=XYZ);

        
        
        var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order){
            int v=get_Rotation_Order(order,0),
                u=get_Rotation_Order(order,2),
                index=Matrix::get_Index(Matrix_3D::w,u,v);
            int inverse=Matrix_3D::_using_m3d_type&1? 
                ((Matrix_3D::myx==index||Matrix_3D::mzy==index||Matrix_3D::mxz==index)?-1 : 1):
                ((Matrix_3D::mxy==index||Matrix_3D::mzx==index||Matrix_3D::myz==index)?-1 : 1);
            
            var mat_mapping_out1=inverse*mat[index];

            out[1]=u==v? acos(mat_mapping_out1):asin(mat_mapping_out1);

            if(check_Zero(mat_mapping_out1)){   // 发生 万向锁 Gimbal lock
                
            }else{  //一般情况
                
            }
        }

        var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order){
            // todo
        }

    }
}

#endif
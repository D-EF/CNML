#ifndef __NML_QUATERNION__
#define __NML_QUATERNION__

#include "NML.hpp"
#include "NML_Vector.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{

    namespace Quaternion{

        /**
         * @brief 写入数据
         * @param out      操作对象
         * @param x        四元数x值
         * @param y        四元数y值
         * @param z        四元数z值
         * @param w        四元数w值
         * @return 修改 out 并输出
         */
        inline var*& setup_Quaternion(var*& out, var x, var y, var z, var w){
            out[0]=x;
            out[1]=y;
            out[2]=z;
            out[3]=w;
            return out;
        }

        /**
         * @brief 四维向量模
         * @param vec   向量
         * @return 返回计算的模长
         */
        inline var mag_v4(var*& vec){
            return sqrt(
                vec[0]*vec[0]+
                vec[1]*vec[1]+
                vec[2]*vec[2]+
                vec[3]*vec[3]
            );
        }


        /** 
         * @brief 使用旋转轴和旋转弧度生成四元数
         * @param out       输出对象
         * @param axis      旋转轴[X,Y,Z]
         * @param theta     旋转弧度
         * @return 修改 out 并返回
         */
        __NML__INLINE__ROTATE_FUNCTION var*& create_Quaternion__ByAxis(var*& out, Axis axis, var theta);

        /** 
         * @brief 使用旋转轴和旋转弧度生成四元数
         * @param out       输出对象
         * @param axis_vec  旋转轴向量 (3d单位向量)
         * @param theta     旋转弧度
         * @return 修改 out 并返回
         */
        __NML__INLINE__ROTATE_FUNCTION var*& create_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta);

        /**
         * @brief 使用旋转矩阵计算四元数
         * @param out       输出对象
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat);
        
        /**
         * @brief 使用欧拉角生成四元数
         * @param out       输出对象
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& EulerAngle, Rotation_Order order=XYZ);

        /**
         * @brief 四元数叉乘
         * @param out           输出对象
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return  修改 out 并输出
         */
        var*& corss(var*& out, var*& quat_left, var*& quat_right);
        

        /**
         * @brief 四元数除法 quat_left/quat_right
         * @param out           输出对象
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return 修改 out 并返回
         */
        var*& setup_Quaternion_division(var*& out, var*& quat);

        /**
         * @brief 四元数的逆
         * @param out   输出对象
         * @param quat  原四元数
         * @return 修改 out 并返回
         */
        __NML__INLINE__ROTATE_FUNCTION var*& setup_Quaternion__Inverse(var*& out, var*& quat);

        /**
         * @brief 四元数的共轭
         * @param out   输出对象
         * @param quat  原四元数
         * @return 修改 out 并返回
         */
        inline var*& setup_Quaternion__Conjugate(var*& out, var*& quat){return setup_Quaternion(out,-quat[0],-quat[1],-quat[2],+quat[3]);}

        /**
         * @brief 提取四元数的旋转量
         * @param quat 四元数数据
         * @return 返回四元数旋转量(弧度)
         */
        inline var calc_Angle(var*& quat){return acos(quat[3])*2;}

        /**
         * @brief 提取四元数旋转轴
         * @param out   输出对象(3d向量)
         * @param quat  四元数数据
         * @return 修改 out 并返回
         */
        inline var*& calc_Axis (var*& out,var*& quat){
            var k=1/sqrt(1.0-quat[3]*quat[3]);
            out[0]=quat[0]*k;
            out[1]=quat[1]*k;
            out[2]=quat[2]*k;
            return out;
        }

        __NML__INLINE__ROTATE_FUNCTION var*& create_Quaternion__ByAxis(var*& out, Axis axis, var theta){
            var vec[]={0,0,0};
            vec[axis]=1;
            var theta_over2=theta*0.5;
            var sin_t=sin(theta_over2),
                cos_t=cos(theta_over2);
            return setup_Quaternion(out,
                sin_t*vec[0],
                sin_t*vec[1],
                sin_t*vec[2],
                cos_t
            );
        }

        __NML__INLINE__ROTATE_FUNCTION var*& create_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta){
            var theta_over2=theta*0.5;
            var sin_t=sin(theta_over2),
                cos_t=cos(theta_over2);
            return setup_Quaternion(out,
                sin_t*axis_vec[0],
                sin_t*axis_vec[1],
                sin_t*axis_vec[2],
                cos_t
            );
        }
        
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat){
            // todo
        }
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& EulerAngle, Rotation_Order order){
            // todo
        }
        

        
        __NML__INLINE__ROTATE_FUNCTION var*& setup_Quaternion__Inverse(var*& out, var*& quat){
            var m=mag_v4(out);
            setup_Quaternion__Conjugate(out, quat);
            np_v4(out,1/m);
            return out;
        }

    }
}

#endif
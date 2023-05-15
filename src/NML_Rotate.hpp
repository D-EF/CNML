#ifndef __NML_ROTATE__
#define __NML_ROTATE__

#include "NML.hpp"
#include "NML_Vector.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{
    
    /**
     * @brief 提取 Rotation_Order 的旋转轴
     * @param order 欧拉角旋转顺序
     * @param index 旋转轴下标[0,2], 表示第几次旋转
     * @return 返回当前旋转轴向
     */
    inline Axis get_Rotation_Order(Rotation_Order order,char index){
        return static_cast<Axis>(order>>(2*index) &0b11);
    }

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
         * @brief 使用旋转矩阵计算欧拉角
         * @param out       输出对象
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_EulerAngle__ByMatrix(var*& out, var*& mat, Rotation_Order order=_DEFAULT_EULER_ANGLE_ORDER);
        
        /**
         * @brief 使用旋转矩阵计算欧拉角
         * @param out       输出对象
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_EulerAngle__ByQuaternion(var*& out, var*& quat, Rotation_Order order=_DEFAULT_EULER_ANGLE_ORDER);

    }


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
         * @brief 使用旋转矩阵计算四元数
         * @param out       输出对象
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat);
        
        /**
         * @brief 使用旋转矩阵计算欧拉角
         * @param out       输出对象
         * @param quat      四元数数据
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& EulerAngle, Rotation_Order order=_DEFAULT_EULER_ANGLE_ORDER);

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
        var*& setup_Quaternion__Inverse(var*& out, var*& quat){
            var m=mag_v4(out);
            setup_Quaternion__Conjugate(out, quat);
            np_v4(out,1/m);
            return out;
        }

        /**
         * @brief 四元数的共轭
         * @param out   输出对象
         * @param quat  原四元数
         * @return 修改 out 并返回
         */
        var*& setup_Quaternion__Conjugate(var*& out, var*& quat){
            return setup_Quaternion(out,
                -quat[0],
                -quat[1],
                -quat[2],
                +quat[3]
            );
        }

        
    }
}

#endif
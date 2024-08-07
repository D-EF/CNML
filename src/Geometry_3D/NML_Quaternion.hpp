/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 17:16:46
 * @FilePath: \CNML\src\Geometry_3D\NML_Quaternion.hpp
 * @Description: 四元数
 */

#ifndef __NML_QUATERNION__
#define __NML_QUATERNION__

#include "NML.hpp"
#include "Algebra/NML_Vector.hpp"
#include "Algebra/NML_Matrix.hpp"
#include "./NML_Matrix_3D.hpp"

namespace NML{
    namespace Quaternion{
        enum Idx__Quaternion{
            QX=0,
            QY=1,
            QZ=2,
            QW=3,
        };

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
            out[QX]=x;
            out[QY]=y;
            out[QZ]=z;
            out[QW]=w;
            return out;
        }

        /** 
         * @brief 使用旋转轴和旋转弧度生成四元数
         * @param out       输出目标
         * @param axis_vec  旋转轴向量 (3d单位向量)
         * @param theta     旋转弧度
         * @return 修改并返回 out
         */
        var*& setup_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta);

        /**
         * @brief 使用旋转矩阵生成四元数
         * @param out       输出目标
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat);
        
        /**
         * @brief 使用欧拉角生成四元数
         * @param out           输出目标
         * @param euler_angle   欧拉角数据
         * @param order         旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& euler_angle, Rotation_Order order=XYZ);
        
        /**
         * @brief 四元数的共轭(逆)
         * @param out   输出目标
         * @param quat  原四元数
         * @return 修改并返回 out
         */
        inline var*& setup_Quaternion__Conjugate(var*& out, var*& quat){
            out[QX]=-quat[QX];
            out[QY]=-quat[QY];
            out[QZ]=-quat[QZ];
            out[QW]=+quat[QW];
            return out;
        }
        
        /**
         * @brief 四元数叉乘
         * @param out           输出目标
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return  修改 out 并输出
         */
        inline var*& cross_Quat(var*& out, var*& quat_left, var*& quat_right){
            out[QX]=quat_left[QW]*quat_right[QX] + quat_left[QX]*quat_right[QW] + quat_left[QZ]*quat_right[QY] - quat_left[QY]*quat_right[QZ];
            out[QY]=quat_left[QW]*quat_right[QY] + quat_left[QY]*quat_right[QW] + quat_left[QX]*quat_right[QZ] - quat_left[QZ]*quat_right[QX];
            out[QZ]=quat_left[QW]*quat_right[QZ] + quat_left[QZ]*quat_right[QW] + quat_left[QY]*quat_right[QX] - quat_left[QX]*quat_right[QY];
            out[QW]=quat_left[QW]*quat_right[QW] - quat_left[QX]*quat_right[QX] - quat_left[QY]*quat_right[QY] - quat_left[QZ]*quat_right[QZ];
            return out;
        }

        /**
         * @brief 四元数的对数
         * @param out 输出目标
         * @param quat 原四元数
         * @return 修改并返回 out
         */
        var*& setup_Quaternion__Logarithms(var*& out, var*& quat){
            var ac=acos(out[QW]);
            out[QX]=quat[QX]*ac;
            out[QY]=quat[QY]*ac;
            out[QZ]=quat[QZ]*ac;
            out[QW]=0;
            return out;
        }

        /**
         * @brief 四元数求幂
         * @param out   输出目标
         * @param n     n次幂
         * @param quat  原四元数
         * @return 修改并返回 out
         */
        var*& setup_Quaternion__Pow(var*& out, var n, var*& quat);
        

        /**
         * @brief 四元数除法 (旋转的差) quat_left to quat_right
         * @param out           输出目标
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return 修改并返回 out
         */
        inline var*& setup_Quaternion__Division(var*& out, var*& quat_left, var*& quat_right){
            var temp_data[4];
            var *temp=temp_data;
            setup_Quaternion__Conjugate(temp, quat_left);
            return cross_Quat(out, temp, quat_right);
        }

        /**
         * @brief 提取四元数的旋转量
         * @param quat 标准化的四元数数据
         * @return 返回四元数旋转量(弧度)
         */
        inline var calc_Angle__GetQuaternion(var*& quat){return acos(quat[QW])*2;}

        /**
         * @brief 提取四元数旋转轴
         * @param out   输出目标(3d向量)
         * @param quat  标准化的四元数数据
         * @return 修改并返回 out
         */
        inline var*& calc_Axis__GetQuaternion (var*& out, var*& quat){
            var k=check_Equal(1, quat[QW])? 1 : 1/sqrt(1.0-quat[QW]*quat[QW]);
            out[QX]=quat[QX]*k;
            out[QY]=quat[QY]*k;
            out[QZ]=quat[QZ]*k;
            return out;
        }

        /**
         * @brief 四元数球面线性插值采样
         * @param out         输出目标
         * @param quat_form   初态四元数
         * @param quat_to     终态四元数
         * @param t           时间参数t
         * @return 修改并返回 out
         */
        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, var*& quat_to, var t);

        /**
         * @brief  计算四元数球面线性插值的缓存数据
         */
        typedef struct SlerpCache{
            var x, y, z, w,
            omega, one_over__sin_omega;
        } SlerpCache;
        
        /**
         * @brief 加载四元数球面线性插值的计算缓存
         * @param out           输出目标
         * @param quat_form     初态四元数
         * @param quat_to       终态四元数
         * @return 修改并返回 out
         */
        SlerpCache& load_SlerpCache(SlerpCache &out, var*& quat_form, var*& quat_to);

        /**
         * @brief 使用缓存计算四元数球面线性插值
         * @param out           输出目标
         * @param quat_form     初态四元数
         * @param SlerpCache    load_SlerpCache计算的缓存
         * @param t             时间参数t
         * @return 修改并返回 out
         */
        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, SlerpCache slerp_cache, var t);



    }
}

#endif
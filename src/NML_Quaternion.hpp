/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-05-23 13:48:47
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-06-05 17:10:15
 * @FilePath: \cnml\src\NML_Quaternion.hpp
 * @Description: 四元数相关计算.  注: 如无特殊标明,这些函数的参数中的四元数都默认需要单位向量
 */
#ifndef __NML_QUATERNION__
#define __NML_QUATERNION__

#include "NML.hpp"
#include "NML_Vector.hpp"
#include "NML_Matrix.hpp"
#include "NML_Matrix_3D.hpp"

namespace NML{

    namespace Quaternion{
        enum Idx__Quaternion{
            qx=0,
            qy=1,
            qz=2,
            qw=3,
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
            out[qx]=x;
            out[qy]=y;
            out[qz]=z;
            out[qw]=w;
            return out;
        }

        /** 
         * @brief 使用旋转轴和旋转弧度生成四元数
         * @param out       输出对象
         * @param axis_vec  旋转轴向量 (3d单位向量)
         * @param theta     旋转弧度
         * @return 修改 out 并返回
         */
        __NML__INLINE__QUATERNION_FUNCTION var*& setup_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta);

        /**
         * @brief 使用旋转矩阵生成四元数
         * @param out       输出对象
         * @param mat       数据来源矩阵 需要仅做旋转变换的矩阵
         * @param order     旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat);
        
        /**
         * @brief 使用欧拉角生成四元数
         * @param out           输出对象
         * @param euler_angle   欧拉角数据
         * @param order         旋转顺序
         * @return 修改 out 并输出
         */
        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& euler_angle, Rotation_Order order=XYZ);
        
        /**
         * @brief 四元数的共轭(逆)
         * @param out   输出对象
         * @param quat  原四元数
         * @return 修改 out 并返回
         */
        inline var*& setup_Quaternion__Conjugate(var*& out, var*& quat){
            out[qx]=-quat[qx];
            out[qy]=-quat[qy];
            out[qz]=-quat[qz];
            out[qw]=+quat[qw];
            return out;
        }
        
        /**
         * @brief 四元数叉乘
         * @param out           输出对象
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return  修改 out 并输出
         */
        inline var*& cross_Quat(var*& out, var*& quat_left, var*& quat_right){
            out[qx]=quat_left[qw]*quat_right[qx] + quat_left[qx]*quat_right[qw] + quat_left[qz]*quat_right[qy] - quat_left[qy]*quat_right[qz];
            out[qy]=quat_left[qw]*quat_right[qy] + quat_left[qy]*quat_right[qw] + quat_left[qx]*quat_right[qz] - quat_left[qz]*quat_right[qx];
            out[qz]=quat_left[qw]*quat_right[qz] + quat_left[qz]*quat_right[qw] + quat_left[qy]*quat_right[qx] - quat_left[qx]*quat_right[qy];
            out[qw]=quat_left[qw]*quat_right[qw] - quat_left[qx]*quat_right[qx] - quat_left[qy]*quat_right[qy] - quat_left[qz]*quat_right[qz];
            return out;
        }

        /**
         * @brief 四元数的对数
         * @param out 输出对象
         * @param quat 原四元数
         * @return 修改out并返回
         */
        var*& logarithms(var*& out,var*& quat){
            var ac=acos(out[qw]);
            out[qx]=quat[qx]*ac;
            out[qy]=quat[qy]*ac;
            out[qz]=quat[qz]*ac;
            out[qw]=0;
            return out;
        }

        /**
         * @brief 四元数求幂
         * @param out   输出对象
         * @param n     n次幂
         * @param quat  原四元数
         * @return 修改 out 并返回
         */
        var*& pow(var*& out,var n,var*& quat);
        

        /**
         * @brief 四元数除法 (旋转的差) quat_left to quat_right
         * @param out           输出对象
         * @param quat_left     左侧四元数
         * @param quat_right    右侧四元数
         * @return 修改 out 并返回
         */
        inline var*& setup_Quaternion_division(var*& out, var*& quat_left, var*& quat_right){
            var temp_data[4];
            var *temp=temp_data;
            setup_Quaternion__Conjugate(temp,quat_left);
            return cross_Quat(out,temp,quat_right);
        }

        /**
         * @brief 提取四元数的旋转量
         * @param quat 标准化的四元数数据
         * @return 返回四元数旋转量(弧度)
         */
        inline var calc_Angle(var*& quat){return acos(quat[qw])*2;}

        /**
         * @brief 提取四元数旋转轴
         * @param out   输出对象(3d向量)
         * @param quat  标准化的四元数数据
         * @return 修改 out 并返回
         */
        inline var*& calc_Axis (var*& out,var*& quat){
            var k=1/sqrt(1.0-quat[qw]*quat[qw]);
            out[qx]=quat[qx]*k;
            out[qy]=quat[qy]*k;
            out[qz]=quat[qz]*k;
            return out;
        }

        /**
         * @brief 四元数线性插值采样
         * @param out         输出对象
         * @param quat_form   初态四元数
         * @param quat_to     终态四元数
         * @param t           时间参数t
         * @return 修改 out 并返回
         */
        var*& slerp(var*& out, var*& quat_form, var*& quat_to, var t);

        /**
         * @brief  计算四元数球面线性插值的缓存数据
         */
        typedef struct SlerpCache{
            var x,y,z,w,
            omega, one_over__sin_omega;
        } SlerpCache;
        
        /**
         * @brief 加载四元数球面线性插值的计算缓存
         * @param out           输出对象
         * @param quat_form     初态四元数
         * @param quat_to       终态四元数
         * @return 修改 out 并返回
         */
        SlerpCache& load_SlerpCache(SlerpCache &out, var*& quat_form, var*& quat_to);

        /**
         * @brief 使用缓存计算四元数球面线性插值
         * @param out           输出对象
         * @param quat_form     初态四元数
         * @param SlerpCache    load_SlerpCache计算的缓存
         * @param t             时间参数t
         * @return 修改 out 并返回
         */
        var*& slerp(var*& out, var*& quat_form, SlerpCache slerp_cache, var t);



        using namespace Matrix_3D;

        __NML__INLINE__QUATERNION_FUNCTION var*& setup_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta){
            var theta_over2=theta*0.5;
            var sin_t=sin(theta_over2),
                cos_t=cos(theta_over2);
            out[qx]=sin_t*axis_vec[qx];
            out[qy]=sin_t*axis_vec[qy];
            out[qz]=sin_t*axis_vec[qz];
            out[qw]=cos_t;
            return out;
        }

        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat){
            // 此处算法参考于 ( GRAPHICS GEMS II/ QUATERNIONS AND 4X4 MATRICES ), 作者 KenShoemake
            // 取开平方根前最大的值作为基础进行另外三个参数计算, 减少误差
            out[qx]=+mat[mxx]-mat[myy]-mat[mzz];
            out[qy]=-mat[mxx]+mat[myy]-mat[mzz];
            out[qz]=-mat[mxx]-mat[myy]+mat[mzz];
            out[qw]=+mat[mxx]+mat[myy]+mat[mzz];

            var temp=out[qx], mult;
            Idx__Quaternion idx__biggest=qx;
            if(out[qx]<out[qy]){temp=out[qy]; idx__biggest=qy;}
            if(out[qy]<out[qz]){temp=out[qz]; idx__biggest=qz;}
            if(out[qz]<out[qw]){temp=out[qw]; idx__biggest=qw;}

            temp=sqrt(temp+1)*0.5;
            mult=0.25/temp;
            switch (idx__biggest)
            {
                case qw:   out[qw]=temp;   out[qx]=(mat[myz] - mat[mzy])*mult;   out[qy]=(mat[mzx] - mat[mxz])*mult;   out[qz]=(mat[mxy] - mat[myx])*mult;   break;
                case qx:   out[qx]=temp;   out[qy]=(mat[mxy] + mat[myx])*mult;   out[qz]=(mat[mzx] + mat[mxz])*mult;   out[qw]=(mat[myz] - mat[mzy])*mult;   break;
                case qy:   out[qy]=temp;   out[qx]=(mat[mxy] + mat[myx])*mult;   out[qw]=(mat[mzx] - mat[mxz])*mult;   out[qx]=(mat[myz] + mat[mzy])*mult;   break;
                case qz:   out[qz]=temp;   out[qw]=(mat[mxy] - mat[myx])*mult;   out[qx]=(mat[mzx] + mat[mxz])*mult;   out[qy]=(mat[myz] + mat[mzy])*mult;   break;
            }
            return out;
        }

        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& euler_angle, Rotation_Order order){
            var a0=euler_angle[0]*0.5, a1=euler_angle[1]*0.5, a2=euler_angle[2]*0.5, c0=cos(a0), c1=cos(a1), c2=cos(a2), s0=sin(a0), s1=sin(a1), s2=sin(a2);
            switch (order)
            {
                case XYZ:   out[qx]=s0*c1*c2 + c0*s1*s2;   out[qy]=c0*s1*c2 - s0*c1*s2;   out[qz]=c0*c1*s2 + s0*s1*c2;   out[qw]=c0*c1*c2 - s0*s1*s2;   break;
                case XZY:   out[qx]=s0*c1*c2 - c0*s1*s2;   out[qy]=c0*s1*c2 - s0*c1*s2;   out[qz]=c0*c1*s2 + s0*s1*c2;   out[qw]=c0*c1*c2 + s0*s1*s2;   break;
                case YXZ:   out[qx]=s0*c1*c2 + c0*s1*s2;   out[qy]=c0*s1*c2 - s0*c1*s2;   out[qz]=c0*c1*s2 - s0*s1*c2;   out[qw]=c0*c1*c2 + s0*s1*s2;   break;
                case YZX:   out[qx]=s0*c1*c2 + c0*s1*s2;   out[qy]=c0*s1*c2 + s0*c1*s2;   out[qz]=c0*c1*s2 - s0*s1*c2;   out[qw]=c0*c1*c2 - s0*s1*s2;   break;
                case ZXY:   out[qx]=s0*c1*c2 - c0*s1*s2;   out[qy]=c0*s1*c2 + s0*c1*s2;   out[qz]=c0*c1*s2 + s0*s1*c2;   out[qw]=c0*c1*c2 - s0*s1*s2;   break;
                case ZYX:   out[qx]=s0*c1*c2 - c0*s1*s2;   out[qy]=c0*s1*c2 + s0*c1*s2;   out[qz]=c0*c1*s2 - s0*s1*c2;   out[qw]=c0*c1*c2 + s0*s1*s2;   break;
                case XYX:   out[qx]=c0*c1*s2 + s0*c1*c2;   out[qy]=c0*s1*c2 - s0*s1*s2;   out[qz]=s0*s1*c2 + c0*s1*s2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
                case XZX:   out[qx]=c0*c1*s2 + s0*c1*c2;   out[qy]=s0*s1*c2 - c0*s1*s2;   out[qz]=c0*s1*c2 + s0*s1*s2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
                case YXY:   out[qx]=c0*s1*c2 + s0*s1*s2;   out[qy]=c0*c1*s2 + s0*c1*c2;   out[qz]=s0*s1*c2 - c0*s1*s2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
                case YZY:   out[qx]=s0*s1*c2 + c0*s1*s2;   out[qy]=c0*c1*s2 + s0*c1*c2;   out[qz]=c0*s1*c2 - s0*s1*s2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
                case ZXZ:   out[qx]=c0*s1*c2 - s0*s1*s2;   out[qy]=s0*s1*c2 + c0*s1*s2;   out[qz]=c0*c1*s2 + s0*c1*c2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
                case ZYZ:   out[qx]=s0*s1*c2 - c0*s1*s2;   out[qy]=c0*s1*c2 + s0*s1*s2;   out[qz]=c0*c1*s2 + s0*c1*c2;   out[qw]=c0*c1*c2 - s0*c1*s2;   break;
            }
            return out;
        }

        var*& pow(var*& out,var n,var*& quat){
            if(check_Equal(quat[qw],1)){
                out[qx]=quat[qx];
                out[qy]=quat[qy];
                out[qz]=quat[qz];
                out[qw]=quat[qw];
                return out;
            }
            var alpha=acos(quat[qw]),
                n_alpha=n*alpha,
                mult=sin(n_alpha)/sin(alpha);
            out[qx]=quat[qx]*mult;
            out[qy]=quat[qy]*mult;
            out[qz]=quat[qz]*mult;
            out[qw]=cos(n_alpha);
            return out;
        }

        var*& slerp(var*& out, var*& quat_form, var*& quat_to, var t){
            if(t<=0)return setup_Quaternion(out, quat_form[qx], quat_form[qy], quat_form[qz], quat_form[qw]);
            if(t>=1)return setup_Quaternion(out, quat_to[qx], quat_to[qy], quat_to[qz], quat_to[qw]);

            var cos_omega=
                quat_form[qx]*quat_to[qx]+
                quat_form[qy]*quat_to[qy]+
                quat_form[qz]*quat_to[qz]+
                quat_form[qw]*quat_to[qw];

            var to_x, to_y, to_z, to_w;
            if(cos_omega<0){
                to_x = -quat_to[qx];
                to_y = -quat_to[qy];
                to_z = -quat_to[qz];
                to_w = -quat_to[qw];
                cos_omega=-cos_omega;
            }else{
                to_x = +quat_to[qx];
                to_y = +quat_to[qy];
                to_z = +quat_to[qz];
                to_w = +quat_to[qw];
            }

            var  k0,k1;
            if(cos_omega>0.999){
                k0=1-t;
                k1=t;
            }else{
                var sin_omega = sqrt(1-cos_omega*cos_omega);
                var omega = atan2(sin_omega,cos_omega);
                var one_over__sin_omega = 1/sin_omega;
                k0=sin((1-t)*omega) * one_over__sin_omega;
                k1=sin(t*omega)     * one_over__sin_omega;
            }

            out[qx]= k0*quat_form[qx] + k1*to_x;
            out[qy]= k0*quat_form[qy] + k1*to_y;
            out[qz]= k0*quat_form[qz] + k1*to_z;
            out[qw]= k0*quat_form[qw] + k1*to_w;
            return out;
        }


        SlerpCache& load_SlerpCache(SlerpCache &out, var*& quat_form, var*& quat_to){
            var cos_omega=
                quat_form[qx]*quat_to[qx]+
                quat_form[qy]*quat_to[qy]+
                quat_form[qz]*quat_to[qz]+
                quat_form[qw]*quat_to[qw];

            if(cos_omega<0){
                out.x = -quat_to[qx];
                out.y = -quat_to[qy];
                out.z = -quat_to[qz];
                out.w = -quat_to[qw];
                cos_omega=-cos_omega;
            }else{
                out.x = +quat_to[qx];
                out.y = +quat_to[qy];
                out.z = +quat_to[qz];
                out.w = +quat_to[qw];
            }
            
            if(cos_omega>0.999){
                out.omega=1;
                out.one_over__sin_omega=1;
            }else{
                var sin_omega = sqrt(1-cos_omega*cos_omega);
                out.omega = atan2(sin_omega,cos_omega);
                out.one_over__sin_omega = 1/sin_omega;
            }

            return out;
        }
        
        var*& slerp(var*& out, var*& quat_form, SlerpCache slerp_cache, var t){
            var k0=sin( (1-t) *slerp_cache.omega ) * slerp_cache.one_over__sin_omega,
                k1=sin(   t   *slerp_cache.omega ) * slerp_cache.one_over__sin_omega;
            out[qx]= k0*quat_form[qx] + k1*slerp_cache.x;
            out[qy]= k0*quat_form[qy] + k1*slerp_cache.y;
            out[qz]= k0*quat_form[qz] + k1*slerp_cache.z;
            out[qw]= k0*quat_form[qw] + k1*slerp_cache.w;
            return out;
        }
    }
}

#endif
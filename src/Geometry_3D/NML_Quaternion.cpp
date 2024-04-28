/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 17:06:13
 * @FilePath: \CNML\src\Geometry_3D\NML_Quaternion.cpp
 * @Description: 四元数
 */

#include "./NML_Quaternion.hpp"

namespace NML{
    namespace Quaternion{
        
        using namespace Matrix_3D;

        var*& setup_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta){
            var theta_over2=theta*0.5;
            var sin_t=sin(theta_over2),
                cos_t=cos(theta_over2);
            out[QX]=sin_t*axis_vec[QX];
            out[QY]=sin_t*axis_vec[QY];
            out[QZ]=sin_t*axis_vec[QZ];
            out[QW]=cos_t;
            return out;
        }

        var*& setup_Quaternion__ByMatrix(var*& out, var*& mat){
            // 此处算法参考于 ( GRAPHICS GEMS II/ QUATERNIONS AND 4X4 MATRICES ), 作者 KenShoemake
            // 取开平方根前最大的值作为基础进行另外三个参数计算, 减少误差
            out[QX]=+mat[mxx]-mat[myy]-mat[mzz];
            out[QY]=-mat[mxx]+mat[myy]-mat[mzz];
            out[QZ]=-mat[mxx]-mat[myy]+mat[mzz];
            out[QW]=+mat[mxx]+mat[myy]+mat[mzz];

            var temp=out[QX], mult;
            Idx__Quaternion Idx__biggest=QX;
            if(out[QX]<out[QY]){temp=out[QY]; Idx__biggest=QY;}
            if(out[QY]<out[QZ]){temp=out[QZ]; Idx__biggest=QZ;}
            if(out[QZ]<out[QW]){temp=out[QW]; Idx__biggest=QW;}

            temp=sqrt(temp+1)*0.5;
            mult=0.25/temp;
            switch (Idx__biggest)
            {
                case QW:   out[QW]=temp;   out[QX]=(mat[myz] - mat[mzy])*mult;   out[QY]=(mat[mzx] - mat[mxz])*mult;   out[QZ]=(mat[mxy] - mat[myx])*mult;   break;
                case QX:   out[QX]=temp;   out[QY]=(mat[mxy] + mat[myx])*mult;   out[QZ]=(mat[mzx] + mat[mxz])*mult;   out[QW]=(mat[myz] - mat[mzy])*mult;   break;
                case QY:   out[QY]=temp;   out[QX]=(mat[mxy] + mat[myx])*mult;   out[QW]=(mat[mzx] - mat[mxz])*mult;   out[QX]=(mat[myz] + mat[mzy])*mult;   break;
                case QZ:   out[QZ]=temp;   out[QW]=(mat[mxy] - mat[myx])*mult;   out[QX]=(mat[mzx] + mat[mxz])*mult;   out[QY]=(mat[myz] + mat[mzy])*mult;   break;
            }
            return out;
        }

        var*& setup_Quaternion__ByEulerAngle(var*& out, var*& euler_angle, Rotation_Order order){
            var a0=euler_angle[0]*0.5, a1=euler_angle[1]*0.5, a2=euler_angle[2]*0.5, c0=cos(a0), c1=cos(a1), c2=cos(a2), s0=sin(a0), s1=sin(a1), s2=sin(a2);
            switch (order)
            {
                case XYZ:   out[QX]=s0*c1*c2 + c0*s1*s2;   out[QY]=c0*s1*c2 - s0*c1*s2;   out[QZ]=c0*c1*s2 + s0*s1*c2;   out[QW]=c0*c1*c2 - s0*s1*s2;   break;
                case XZY:   out[QX]=s0*c1*c2 - c0*s1*s2;   out[QY]=c0*s1*c2 - s0*c1*s2;   out[QZ]=c0*c1*s2 + s0*s1*c2;   out[QW]=c0*c1*c2 + s0*s1*s2;   break;
                case YXZ:   out[QX]=s0*c1*c2 + c0*s1*s2;   out[QY]=c0*s1*c2 - s0*c1*s2;   out[QZ]=c0*c1*s2 - s0*s1*c2;   out[QW]=c0*c1*c2 + s0*s1*s2;   break;
                case YZX:   out[QX]=s0*c1*c2 + c0*s1*s2;   out[QY]=c0*s1*c2 + s0*c1*s2;   out[QZ]=c0*c1*s2 - s0*s1*c2;   out[QW]=c0*c1*c2 - s0*s1*s2;   break;
                case ZXY:   out[QX]=s0*c1*c2 - c0*s1*s2;   out[QY]=c0*s1*c2 + s0*c1*s2;   out[QZ]=c0*c1*s2 + s0*s1*c2;   out[QW]=c0*c1*c2 - s0*s1*s2;   break;
                case ZYX:   out[QX]=s0*c1*c2 - c0*s1*s2;   out[QY]=c0*s1*c2 + s0*c1*s2;   out[QZ]=c0*c1*s2 - s0*s1*c2;   out[QW]=c0*c1*c2 + s0*s1*s2;   break;
                case XYX:   out[QX]=c0*c1*s2 + s0*c1*c2;   out[QY]=c0*s1*c2 - s0*s1*s2;   out[QZ]=s0*s1*c2 + c0*s1*s2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
                case XZX:   out[QX]=c0*c1*s2 + s0*c1*c2;   out[QY]=s0*s1*c2 - c0*s1*s2;   out[QZ]=c0*s1*c2 + s0*s1*s2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
                case YXY:   out[QX]=c0*s1*c2 + s0*s1*s2;   out[QY]=c0*c1*s2 + s0*c1*c2;   out[QZ]=s0*s1*c2 - c0*s1*s2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
                case YZY:   out[QX]=s0*s1*c2 + c0*s1*s2;   out[QY]=c0*c1*s2 + s0*c1*c2;   out[QZ]=c0*s1*c2 - s0*s1*s2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
                case ZXZ:   out[QX]=c0*s1*c2 - s0*s1*s2;   out[QY]=s0*s1*c2 + c0*s1*s2;   out[QZ]=c0*c1*s2 + s0*c1*c2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
                case ZYZ:   out[QX]=s0*s1*c2 - c0*s1*s2;   out[QY]=c0*s1*c2 + s0*s1*s2;   out[QZ]=c0*c1*s2 + s0*c1*c2;   out[QW]=c0*c1*c2 - s0*c1*s2;   break;
            }
            return out;
        }

        var*& setup_Quaternion__Pow(var*& out, var n, var*& quat){
            if(check_Equal(quat[QW], 1)){
                out[QX]=quat[QX];
                out[QY]=quat[QY];
                out[QZ]=quat[QZ];
                out[QW]=quat[QW];
                return out;
            }
            var alpha=acos(quat[QW]),
                n_alpha=n*alpha,
                mult=sin(n_alpha)/sin(alpha);
            out[QX]=quat[QX]*mult;
            out[QY]=quat[QY]*mult;
            out[QZ]=quat[QZ]*mult;
            out[QW]=cos(n_alpha);
            return out;
        }

        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, var*& quat_to, var t){
            if(t<=0)return setup_Quaternion(out, quat_form[QX], quat_form[QY], quat_form[QZ], quat_form[QW]);
            if(t>=1)return setup_Quaternion(out, quat_to[QX], quat_to[QY], quat_to[QZ], quat_to[QW]);

            var cos_omega=
                quat_form[QX]*quat_to[QX]+
                quat_form[QY]*quat_to[QY]+
                quat_form[QZ]*quat_to[QZ]+
                quat_form[QW]*quat_to[QW];

            var to_x, to_y, to_z, to_w;
            if(cos_omega<0){
                to_x = -quat_to[QX];
                to_y = -quat_to[QY];
                to_z = -quat_to[QZ];
                to_w = -quat_to[QW];
                cos_omega=-cos_omega;
            }else{
                to_x = +quat_to[QX];
                to_y = +quat_to[QY];
                to_z = +quat_to[QZ];
                to_w = +quat_to[QW];
            }

            var  k0, k1;
            if(cos_omega>0.999){
                k0=1-t;
                k1=t;
            }else{
                var sin_omega = sqrt(1-cos_omega*cos_omega);
                var omega = atan2(sin_omega, cos_omega);
                var one_over__sin_omega = 1/sin_omega;
                k0=sin((1-t)*omega) * one_over__sin_omega;
                k1=sin(t*omega)     * one_over__sin_omega;
            }

            out[QX]= k0*quat_form[QX] + k1*to_x;
            out[QY]= k0*quat_form[QY] + k1*to_y;
            out[QZ]= k0*quat_form[QZ] + k1*to_z;
            out[QW]= k0*quat_form[QW] + k1*to_w;
            return out;
        }


        SlerpCache& load_SlerpCache(SlerpCache &out, var*& quat_form, var*& quat_to){
            var cos_omega=
                quat_form[QX]*quat_to[QX]+
                quat_form[QY]*quat_to[QY]+
                quat_form[QZ]*quat_to[QZ]+
                quat_form[QW]*quat_to[QW];

            if(cos_omega<0){
                out.x = -quat_to[QX];
                out.y = -quat_to[QY];
                out.z = -quat_to[QZ];
                out.w = -quat_to[QW];
                cos_omega=-cos_omega;
            }else{
                out.x = +quat_to[QX];
                out.y = +quat_to[QY];
                out.z = +quat_to[QZ];
                out.w = +quat_to[QW];
            }
            
            if(cos_omega>0.999){
                out.omega=1;
                out.one_over__sin_omega=1;
            }else{
                var sin_omega = sqrt(1-cos_omega*cos_omega);
                out.omega = atan2(sin_omega, cos_omega);
                out.one_over__sin_omega = 1/sin_omega;
            }

            return out;
        }
        
        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, SlerpCache slerp_cache, var t){
            var k0=sin( (1-t) *slerp_cache.omega ) * slerp_cache.one_over__sin_omega,
                k1=sin(   t   *slerp_cache.omega ) * slerp_cache.one_over__sin_omega;
            out[QX]= k0*quat_form[QX] + k1*slerp_cache.x;
            out[QY]= k0*quat_form[QY] + k1*slerp_cache.y;
            out[QZ]= k0*quat_form[QZ] + k1*slerp_cache.z;
            out[QW]= k0*quat_form[QW] + k1*slerp_cache.w;
            return out;
        }
    }
}
#include "NML_Quaternion.hpp"

namespace NML{
    namespace Quaternion{
        
        using namespace Matrix_3D;

        var*& setup_Quaternion__ByAxis(var*& out, var*& axis_vec, var theta){
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
            Idx__Quaternion Idx__biggest=qx;
            if(out[qx]<out[qy]){temp=out[qy]; Idx__biggest=qy;}
            if(out[qy]<out[qz]){temp=out[qz]; Idx__biggest=qz;}
            if(out[qz]<out[qw]){temp=out[qw]; Idx__biggest=qw;}

            temp=sqrt(temp+1)*0.5;
            mult=0.25/temp;
            switch (Idx__biggest)
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

        var*& setup_Quaternion__Pow(var*& out,var n,var*& quat){
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

        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, var*& quat_to, var t){
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
        
        var*& setup_Quaternion__Slerp(var*& out, var*& quat_form, SlerpCache slerp_cache, var t){
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
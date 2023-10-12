/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-08 16:40:23
 * @FilePath: \cnml\src\NML_Algebra.cpp
 * @Description: 数与代数 运算相关
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "NML_Algebra.hpp"

namespace NML{
    namespace Algebra{
        
        /**
         * @brief 帕斯卡三角数据
        */
        Pascals_Triangle_Line _G_PASCALS_TRIANGLE={&_G_PASCALS_TRIANGLE, 0, new int[3]{0, 1, 0}+1};
        Pascals_Triangle_Line *_ROOT__G_PASCALS_TRIANGLE=&_G_PASCALS_TRIANGLE;

        /**
         * @brief 最后一次演算的一层帕斯卡三角数组; next 指向第零层(_G_PASCALS_TRIANGLE)
         */
        Pascals_Triangle_Line *_last_calc_pascals_triangle=&_G_PASCALS_TRIANGLE;
        
        Pascals_Triangle_Line *_calc_PascalsTriangle(Idx_Algebra n){
            Pascals_Triangle_Line *&rtn=_last_calc_pascals_triangle;
            while(rtn->size<n){
                Idx_Algebra length__next=rtn->size+1;
                rtn->next=new Pascals_Triangle_Line{&_G_PASCALS_TRIANGLE, length__next, new int[length__next+3]+1};

                rtn->next->data[-1]=0;
                for(Idx_Algebra i=0; i<=length__next; ++i){
                    rtn->next->data[i]=(rtn->data[i])+(rtn->data[i-1]);
                }
                rtn->next->data[length__next+1]=0;

                rtn=rtn->next;
            }
            return rtn;
        }

        
        Pascals_Triangle_Line *get_PascalsTriangleLine(Idx_Algebra n){
            if(n<0)return 0;
            Pascals_Triangle_Line *rtn=_last_calc_pascals_triangle;
            if(rtn->size<n) rtn=_calc_PascalsTriangle(n);
            while(rtn->size!=n){
                rtn=rtn->next;
            }
            return rtn;
        }


        var*& calc_Derivative__OneUnitaryRealParameterFunction(var *&out, var *coefficients, Idx_Algebra length_coefficients){
            Idx_Algebra l=length_coefficients-1, i;
            for(i=1;  i<=l;  ++i){
                out[i-1]=coefficients[i]*i;
            }
            return out;
        }

        var _calc_CubeRoot(var value){
            return value < 0?-pow(-value, ONE_OVER_THREE) : pow(value, ONE_OVER_THREE);
        }

        Idx_Algebra calc_RootsOfSquare(var *&out, var z1, var o1, var z2, var o2, var z3, var o3, var z4, var o4){
            var pd=(o1*o4 - o2*o3);
            if(check_Zero(pd)){
                if((z1-z2)*o2==(z3-z4)*o4){
                    return '\2';
                }else{
                    return '\1';
                }
            }
            out[0]= (z2*o4 + o2*z3 - z4*o2 - z1*o4) / pd;
            out[1]= (z2*o3 + z3*o1 - z4*o1 - z1*o3) / pd;
            // out[1]=(z3 + o3*out[0] - z4) / o4;   // o4 可能为0所以不能用
            return '\0';
        }
        
        Idx_Algebra calc_RootsOfCubic(var*& out, var*& coefficients){
            var a=coefficients[2]||0,
                b=coefficients[1]||0,
                c=coefficients[0]||0,
                d=coefficients[3]||0;

            //一元一至三次函数求根公式编程表示 来自 https://pomax.github.io/bezierinfo/zh-CN/index.html#extremities
            
            // Quartic curves: Cardano's algorithm.

            // do a check to see whether we even need cubic solving:
            if (check_Zero(d)) {
                // this is not a cubic curve.
                if (check_Zero(a)) {
                    // in fact, this is not a quadratic curve either.
                    if (check_Zero(b)) {
                        // in fact in fact, there are no solutions.
                        return 0;
                    }
                    // linear solution
                    out[0]=-c / b;
                    return 1;
                }
                // quadratic solution
                var k=b * b - 4 * a * c;
                if(k<0)return 0;
                var q = sqrt(k), a2 = 2 * a;
                out[0] = ( q - b) / a2;
                out[1] = (-b - q) / a2;
                return 2;
            }
            
            a /= d;
            b /= d;
            c /= d;

            var p = (3 * b - a * a) * ONE_OVER_THREE,
                p3 = p * ONE_OVER_THREE,
                q = (2 * a * a * a - 9 * a * b + 27 * c) / 27,
                q2 = q * 0.5,
                discriminant = q2 * q2 + p3 * p3 * p3;

            // and some variables we're going to use later on:
            var u1, v1;

            // three possible real roots:
            if (discriminant < 0) {
                var mp3 = -p * ONE_OVER_THREE,
                    mp33 = mp3 * mp3 * mp3,
                    r = sqrt(mp33),
                    t = -q / (2 * r),
                    cosphi = t < -1 ? -1 : t > 1 ? 1 : t,
                    phi = acos(cosphi),
                    crtr = _calc_CubeRoot(r),
                    t1 = 2 * crtr;
                out[0] = t1 * cos(phi * ONE_OVER_THREE) - a * ONE_OVER_THREE;
                out[1] = t1 * cos((phi + 2 * PI) * ONE_OVER_THREE) - a * ONE_OVER_THREE;
                out[2] = t1 * cos((phi + 4 * PI) * ONE_OVER_THREE) - a * ONE_OVER_THREE;
                return 3;
            }

            // three real roots, but two of them are equal:
            if (discriminant == 0) {
                u1 = q2 < 0 ? _calc_CubeRoot(-q2) : -_calc_CubeRoot(q2);
                out[0] = 2 * u1 - a * ONE_OVER_THREE;
                out[1] = -u1 - a * ONE_OVER_THREE;
                return 2;
            }

            // one real root, two complex roots
            var sd = sqrt(discriminant);
            u1 = _calc_CubeRoot(sd - q2);
            v1 = _calc_CubeRoot(sd + q2);
            out[0] = u1 - v1 - a * ONE_OVER_THREE;
            return 1;
        }



    }
}

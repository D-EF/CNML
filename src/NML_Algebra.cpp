/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-01-30 17:57:45
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

        var calc_UnivariatePolynomials(var* coefficients, Idx_Algebra length, var param_value){
            var rtn=0;
            var k=1;
            for(Idx_Algebra i=0;  i<length;  ++i){
                rtn+=coefficients[i]*k;
                k*=param_value;
            }
            return rtn;
        }

        var*& setup_Derivatives__UnivariatePolynomials(var*& out, var* coefficients, Idx_Algebra length_coefficients){
            Idx_Algebra i;
            for(i=1;  i<length_coefficients;  ++i){
                out[i-1]=coefficients[i]*i;
            }
            return out;
        }

        Points_Iterator& setup_Derivatives__UnivariatePolynomials(Points_Iterator& out, Points_Iterator& coefficients){
            Idx_Algebra i, j, &d=out.dimensional;
            for(i=1;  i<out.points_length;  ++i){
                var* temp_out=out[i-1];
                var* temp_coefficients=coefficients[i];
                for(j=0; j<d;++j){
                    temp_out[j]=temp_coefficients[j]*i;
                }
            }
            return out;
        }
        

        Idx_Algebra clac_EquationSolution__Linear(var*& out, var z1, var o1, var z2, var o2, var z3, var o3, var z4, var o4){
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


        Idx_Algebra calc_Roots__Square(var*& out, var*& coefficients){
            var a=coefficients[2]||0,
                b=coefficients[1]||0,
                c=coefficients[0]||0;
            if(a==0) {
                out[0] = calc_Root__Line(c,b);
                return 1;
            }
            var k=b * b - 4 * a * c;
            if(k<0)return 0;
            var q = sqrt(k), a2 = 2 * a;
            out[0] = ( q - b) / a2;
            if(q==0) return 1;
            out[1] = (-b - q) / a2;
            return 2;
        }
        
        var _calc_CubeRoot(var value){
            return value < 0?-pow(-value, ONE_OVER_THREE) : pow(value, ONE_OVER_THREE);
        }
        
        Idx_Algebra calc_Roots__Cubic(var*& out, var*& coefficients){
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

        Idx_Algebra find_Roots__UnivariatePolynomials__IterationMethod (var*& out, var*& coefficients, Idx_Algebra length, var _tolerance){
            // 筛去高次的0系数
            while(coefficients[length-1]==0) --length;
            if(length<=4) return calc_Roots__UnivariatePolynomials (out, coefficients, length);

            Idx i, l=(length-3)*(length+4)/2;
            var *derivatives=new var[l];
            copy_To(derivatives, coefficients, length);
            
            // 加载导数集合直到可以被公式求根的多项式 (一元三次函数)
            // q = 第 n 次计算导数起始位置, p = 第 n+1 次计算导数起始位置
             var *q = derivatives,
                *p = q + length;
            for(i=length-1;  i>3;  --i){
                setup_Derivatives__UnivariatePolynomials(p,q,i+1);
                q  = p;
                p += i;
            }

            // 初始化一元三次函数的根, 并且保证从小到大排序
            Idx_Algebra roots_length = calc_Roots__Cubic(out,q);
            if(roots_length>1){
                if(out[0]>out[1]) std::swap(out[0],out[1]);
                if(roots_length>2){
                    if(out[1]>out[2]) std::swap(out[1], out[2]);
                    if(out[0]>out[1]) std::swap(out[0], out[1]);
                }
            }

            // 寻根
            for(i=5;  i<=length;  ++i){
                p  = q;
                q -= i;
                roots_length = find_Roots__UnivariatePolynomials__IterationMethod(out, q, p, i, out, roots_length, _tolerance);
            }

            return roots_length;
        }

        Idx_Algebra find_Roots__UnivariatePolynomials__IterationMethod (var*& out, var*& coefficients, var*& derivatives, Idx_Algebra length__coefficients, var*& derivatives_roots, Idx_Algebra length__derivatives_roots, var _tolerance){
            Idx_Algebra roots_length = 0;
            Idx_Algebra i;
            var temp_root,  temp_root_0,  temp_root_1;
            var temp_value, temp_value_0, temp_value_1, temp_value_next;

            // 判断 -INFINITY ~ 当前位置的单调性, n_flag >> true:+,  false:-;
            bool n_flag=coefficients[length__coefficients-1]>0;
            if(length__coefficients%2)n_flag=!n_flag;

            // 寻找最小位置根
            if(length__derivatives_roots==0)   temp_root = 0;
            else                               temp_root = derivatives_roots[0];
            temp_value = calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root);
            
            if(n_flag == temp_value>0){  
                out[roots_length] = find_Roots__UnivariatePolynomials__IterationMethod__NewtonThenBisection(
                    temp_root-1, coefficients, derivatives, length__coefficients, _tolerance
                );
                ++roots_length;
            }

            // 寻找折点间的根
            if(length__derivatives_roots>1){
                temp_value_0=calc_UnivariatePolynomials(coefficients, length__coefficients, derivatives_roots[0]);

                for(i=0;  i+1<length__derivatives_roots;  ++i, temp_value_0=temp_value_next){
                    temp_root_0 = derivatives_roots[i];
                    temp_root_1 = derivatives_roots[i+1];

                    temp_value_1 = temp_value_next = calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root_1);

                    // 导数根的位置在当前函数值为同号, 两位置间无根
                    if(temp_value_0>0==temp_value_next>0) continue;

                    out[roots_length]=find_Roots__UnivariatePolynomials__IterationMethod__Bisection(
                        temp_root_0, temp_root_1, coefficients, length__coefficients, 
                        _tolerance, temp_value_0,temp_value_1
                    );
                    ++roots_length;
                }
            }

            // length__coefficients系数个数为奇数, 当前位置 ~ +INFINITY 单调性改变
            if((length__coefficients%2))n_flag=!n_flag;

            // 寻找最大位置根 过程与寻最小时类似
            if(length__derivatives_roots==0)   temp_root = 0;
            else                               temp_root = derivatives_roots[length__derivatives_roots-1];
            temp_value = calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root);

            if(n_flag == temp_value<0){  
                out[roots_length] = find_Roots__UnivariatePolynomials__IterationMethod__NewtonThenBisection(
                    temp_root+1, coefficients, derivatives, length__coefficients, _tolerance
                );
                ++roots_length;
            }
            
            return roots_length;
        }

        var find_Roots__UnivariatePolynomials__IterationMethod__NewtonThenBisection(var init_param, var*& coefficients, var*& derivatives, Idx_Algebra length__coefficients, var _tolerance, var _init_value){
            var &root=init_param, &temp_value=_init_value;
            var derivative;
            var low_value,low_root;

            if(temp_value==INFINITY) temp_value = calc_UnivariatePolynomials(coefficients, length__coefficients,  root);

            while(!check_Zero(temp_value,_tolerance)){
                low_value=temp_value;
                low_root=root;
                derivative = calc_UnivariatePolynomials(derivatives, length__coefficients-1, root);
                root -= temp_value/derivative*2;  // 提供过量值, 用于转到二分法方案
                temp_value = calc_UnivariatePolynomials(coefficients, length__coefficients,  root);

                if(low_value>0 != temp_value>0){ // 发现异号函数值切换使用二分法方案
                    return find_Roots__UnivariatePolynomials__IterationMethod__Bisection(low_root, root, coefficients, length__coefficients, _tolerance, low_value, temp_value);
                }
            }
            return root;
        };

        var find_Roots__UnivariatePolynomials__IterationMethod__Bisection(var init_open, var init_end, var*& coefficients, Idx_Algebra length__coefficients, var _tolerance, var _init_value_0, var _init_value_1){
            var temp_root, temp_value;
            var &temp_value_0=_init_value_0, &temp_value_1=_init_value_1;
            var &temp_root_0=init_open, &temp_root_1=init_end;

            if(temp_value_0==INFINITY) temp_value_0 = calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root_0);
            if(temp_value_1==INFINITY) temp_value_1 = calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root_1);

            do{
                temp_root=(temp_root_0+temp_root_1)*0.5;
                temp_value=calc_UnivariatePolynomials(coefficients, length__coefficients, temp_root);
                if(temp_value>0 == temp_value_0>0){
                    temp_value_0 = temp_value;
                    temp_root_0  = temp_root;
                }else{
                    temp_root_1  = temp_root;
                }
            }while(!check_Zero(temp_value,_tolerance));

            return (temp_root_0+temp_root_1)*0.5;
        };


        Idx_Algebra calc_Roots__UnivariatePolynomials(var*& out, var*& coefficients,Idx_Algebra length){
            if(length<=0) return -1;
            switch (length){
                case 1:  return calc_Roots__Line(out,coefficients);  break;
                case 2:  return calc_Roots__Square(out,coefficients); break;
                case 3:  return calc_Roots__Cubic(out,coefficients); break;
                default: return find_Roots__UnivariatePolynomials__IterationMethod(out,coefficients,length); break;
            }
        }


        var normalize_Radians(var theta){
            while(theta>PI)    { theta+=DEG_360_I; }
            while(theta<PI_I)  { theta+=DEG_360;   }
            return theta;
        }
        

    }
}

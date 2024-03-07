/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-02-01 14:02:26
 * @FilePath: \cnml\src\NML_Algebra.hpp
 * @Description: 数与代数 运算相关
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __NML_ALGEBRA__
#define __NML_ALGEBRA__

#include "NML.hpp"

namespace NML{
    namespace Algebra{

        typedef Link_Block__Simple<int> Pascals_Triangle_Line;
        
        /**
         * @brief 帕斯卡三角数据
        */
        extern Pascals_Triangle_Line _G_PASCALS_TRIANGLE;
        extern Pascals_Triangle_Line *_ROOT__G_PASCALS_TRIANGLE;

        /**
         * @brief 最后一次演算的一层帕斯卡三角数组; next 指向第零层(_G_PASCALS_TRIANGLE)
         */
        extern Pascals_Triangle_Line *_last_calc_pascals_triangle;

        /**
         * @brief 演算帕斯卡三角
         * @param n 目标演算到第几层
         * @return 最后一次演算结果将保存到 _last_calc_pascals_triangle 上;
         */
        Pascals_Triangle_Line *_calc_PascalsTriangle(Idx_Algebra n);

        /**
         * @brief 获取帕斯卡三角的一行数据
         * @param n 第n行帕斯卡三角的一行数据 (数据长度为n+1的一行帕斯卡三角)
         * @return 返回数据长度为n的帕斯卡三角的一行数据
         */
        Pascals_Triangle_Line* get_PascalsTriangleLine(Idx_Algebra n);

        /**
         * @brief 解二元一次方程   
         *  z1 + o1*x = z2 + o2*y;   
         *  z3 + o3*x = z4 + o4*y;   
         * @param  out 输出目标{ x , y }
         * @return 返回计算状态:{ 0: 正常相交, 1:无解(平行), 2无限解(重合) } 
         */
        Idx_Algebra clac_EquationSolution__Linear(var*& out, var z1, var o1, var z2, var o2, var z3, var o3, var z4, var o4);
        
        // open * 一元多项式 * open 
            // 一元多项式:
            //         coefficients.length
            //  F(t) = ∑ t^i*c[i]
            //         i=0
            
            /**
             * @brief 计算一元多项式
             * 
             * @param coefficients  多项式的系数
             * @param length        系数的长度
             * @param param_value   自变量参数值
             * @return 计算多项式并返回计算结果
             */
            var calc_UnivariatePolynomials(var* coefficients, Idx_Algebra length, var param_value);

            /** 
             * @brief 求导一元多项式 f(t) >>> f'(t)=d(f);
             * @param coefficients 各次幂的系数 [t^0, t^1, t^2, t^3, ...]
             * @param length_coefficients coefficients 的长度
             * @return 返回导数的各次幂的系数 [t^0, dt^1, dt^2, dt^3, ...] 长度 = length_coefficients-1
             */
            var*& setup_Derivatives__UnivariatePolynomials(var*& out, var* coefficients, Idx_Algebra length_coefficients);
                
                
            /**
             * @brief 求一元n次函数集的导数
             * @param out            输出对象, 应满足 out.point_length == coefficients.point_length-1 && out.dimensional == coefficients.dimensional
             * @param coefficients   系数集合, 其中 coefficients[i] 表示 各个函数中 i 次幂的系数
             * @return 修改并返回 out, 一组新的系数表示原函数系数的导函数
             */
            Points_Iterator& setup_Derivatives__UnivariatePolynomials(Points_Iterator& out, Points_Iterator& coefficients);
            
            
            // open * 一元多项式求根 * open

                /**
                 * @brief 求线性函数 y=a+bx 的根
                 * @param  a 常量
                 * @param  b x 的系数
                 * @return 返回计算的 x 值; 当无限解时, 返回 +INFINITY; 当无解时, 返回 -INFINITY
                 */
                inline var calc_Root__Line(var a, var b){ return b==0 ? ( a ? +INFINITY : -INFINITY ) : -a/b; }
                inline var calc_Root__Line(var*& coefficients){ return coefficients[1]==0 ? ( coefficients[0] ? +INFINITY : -INFINITY ) : -coefficients[0]/coefficients[1]; }
                
                /**
                 * @brief  求线性函数 y=a+bx 的根
                 * @param out 计算结果输出目标, 需要1个元素以上的长度
                 * @param coefficients 函数的系数集合, 从低次幂到高次幂 [ a, b, c ] 下标 = x 的指数
                 * @return 返回计算后得到了几个根
                 */
                inline Idx_Algebra calc_Roots__Line(var*& out, var*& coefficients){ return coefficients[1]==0 ? ( 0 ) : ( out[0] = -coefficients[0]/coefficients[1] ) , 1; }

                /**
                 * @brief 求一元二次函数的根, 0 = ax^0 + bx^1 + cx^2
                 * @param out 计算结果输出目标, 需要2个元素以上的长度
                 * @param coefficients 函数的系数集合, 从低次幂到高次幂 [ a, b, c ] 下标 = x 的指数
                 * @return 返回计算后得到了几个根
                 */
                Idx_Algebra calc_Roots__Square(var*& out, var*& coefficients);

                /** 
                 * @brief 求一元三次函数的根, 0 = ax^0 + bx^1 + cx^2 + dx^3
                 * @param out            计算结果输出目标, 需要3个元素以上的长度
                 * @param coefficients   函数的系数集合, 从低次幂到高次幂 [ a, b, c, d ] 下标 = x 的指数
                 * @return 返回计算后得到了几个根
                 */
                Idx_Algebra calc_Roots__Cubic(var*& out, var*& coefficients);

                /**
                 * @brief 使用迭代法寻找一元多项式的根 0 = c_0·x^0 + c_1·x^1 + c_2·x^2 + ... + c_n·x^n
                 * 
                 * @param out            计算结果输出目标, 长度应该等于 length
                 * @param coefficients   函数的系数集合, 从低次幂到高次幂 [ a, b, c, d ] 下标 = x 的指数
                 * @param length         函数的系数个数
                 * @param _tolerance     数值根的容差
                 * @return 返回计算后得到了几个根
                 */
                Idx_Algebra find_Roots__UnivariatePolynomials__IterationMethod (var*& out, var*& coefficients,Idx_Algebra length, var _tolerance=NML_TOLERANCE);
                
                /** 
                 * @brief 使用迭代进行寻根
                 * 
                 * @param out                         结果输出对象
                 * @param coefficients                多项式的系数
                 * @param derivatives                 多项式的导数系数
                 * @param length                      多项式的系数的长度
                 * @param derivatives_roots           多项式的导数的根, 用于初始化寻根过程, 需要从小到大排序
                 * @param length__derivatives_roots   多项式的导数的根的长度
                 * @param _tolerance     数值根的容差
                 * @return 返回计算后得到了几个根
                 */
                Idx_Algebra find_Roots__UnivariatePolynomials__IterationMethod (var*& out, var*& coefficients, var*& derivatives, Idx_Algebra length__coefficients, var*& derivatives_roots, Idx_Algebra length__derivatives_roots, var _tolerance=NML_TOLERANCE);

                /** 
                 * @brief 牛顿法配合二分法求根
                 * @param init_param             初始位置
                 * @param coefficients           函数计算系数
                 * @param derivatives            函数的导数
                 * @param length__coefficients   计算系数长度
                 * @param _tolerance             容差
                 * @param _init_value            初始化的值, 用于省略初始化函数计算值 
                 * @return 迭代演算并返回结果
                 */
                var find_Roots__UnivariatePolynomials__IterationMethod__NewtonThenBisection(var init_param, var*& coefficients, var*& derivatives, Idx_Algebra length__coefficients, var _tolerance=NML_TOLERANCE, var _init_value=INFINITY);

                /** 
                 * @brief 二分法求根
                 * @param init_open              初始区间起始位置
                 * @param init_end               初始区间结束位置
                 * @param coefficients           函数计算系数
                 * @param length__coefficients   计算系数长度
                 * @param _tolerance             容差
                 * @param _init_value_0          起始位置初始化的值, 用于省略初始化函数计算值 
                 * @param _init_value_1          结束位置初始化的值, 用于省略初始化函数计算值 
                 * @return 迭代演算并返回结果
                 */
                var find_Roots__UnivariatePolynomials__IterationMethod__Bisection(var init_open, var init_end, var*& coefficients, Idx_Algebra length__coefficients, var _tolerance=NML_TOLERANCE, var _init_value_0=INFINITY, var _init_value_1=INFINITY);

                /**
                 * @brief 求一元多项式的根 0 = c_0·x^0 + c_1·x^1 + c_2·x^2 + ... + c_n·x^n
                 * @param out            计算结果输出目标, 长度应该等于 length
                 * @param coefficients   函数的系数集合, 从低次幂到高次幂 [ a, b, c, d ] 下标 = x 的指数
                 * @param length         函数的系数个数
                 * @return 返回计算后得到了几个根
                 */
                Idx_Algebra calc_Roots__UnivariatePolynomials(var*& out, var*& coefficients,Idx_Algebra length);

            // end  * 一元多项式求根 * end 
        // end  * 一元多项式 * end  

        /** 
         * @brief 求拥有参数弧度相同射线并且取值范围在 ±π 内的弧度
         * @param theta 参数弧度
         * @return 返回范围在 ±π 的弧度
         */
        var normalize_Radians(var theta);

    }
}

#endif
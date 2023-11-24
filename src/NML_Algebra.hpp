/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-08 16:40:23
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

        typedef Link_Block__Int Pascals_Triangle_Line;
        
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
         * @brief 求导一元多次函数 d(f);
         * @param coefficients 各次幂的系数 [1, t^1, t^2, t^3, ...]
         * @param length_coefficients coefficients 的长度
         * @return 返回导数的各次幂的系数 [1, dt^1, dt^2, dt^3, ...] 长度会比形参少 1
         */
        var*& calc_Derivative__OneUnitaryRealParameterFunction(var*& out, var* coefficients, Idx_Algebra length_coefficients);
            // 一元多次函数:
            //         coefficients.length
            //  F(t) = ∑ t^i*c[i]
            //         i=0

        /**
         * @brief 解二元一次方程   
         *  z1 + o1*x = z2 + o2*y;   
         *  z3 + o3*x = z4 + o4*y;   
         * @param  out 输出对象{ x , y }
         * @return 返回计算状态:{ 0: 正常相交, 1:无解(平行), 2无限解(重合) } 
         */
        Idx_Algebra calc_RootsOfSquare(var*& out, var z1, var o1, var z2, var o2, var z3, var o3, var z4, var o4);

        /** 
         * @brief 解一元三次方程, ax^3+bx^2+cx+d=0
         * @param out 计算结果输出对象, 需要3个元素以上的长度
         * @param coefficients 系数集合 从低次幂到高次幂 [ x^0, x^1, x^2, x^3 ]
         * @return 返回计算后得到了几个根
         */
        Idx_Algebra calc_RootsOfCubic(var*& out, var*& coefficients);

    }
}

#endif
/*!
 * @Description: 数与代数 运算相关
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-06-25 16:54:26
 */

#ifndef __NML_BEZIER__
#define __NML_BEZIER__

#include "NML.hpp"

namespace NML{
    namespace Bezier{

        /**
         * @brief 采样贝塞尔曲线    使用DeCasteljau算法 (不建议使用)
         * @param out               输出对象, 采样点 长度为 points.dimensional
         * @param points            贝塞尔曲线控制点集合 长度为 dimensional*points_length
         * @param t                 时间参数 t
         * @return 修改并返回 out
         */
        var *&sample_Bezier__DeCasteljau(var *&out, Points_Iterator& points, var t);
        

        typedef Link_List__Int_List Bezier_Calc_Matrix;
        
        /**
         * @brief 获取 贝塞尔曲线计算矩阵
         * @param n 表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @return 返回一个行优先展开的整形下三角矩阵 长度为 (n+1)*(n+2)/2
         */
        int* get_BezierCalcMatrix(Idx_Algebra n);

        
        /**
         * @brief 求贝塞尔曲线 各次幂的系数
         * @param out      输出对象, 规模与 points 相同
         * @param points   贝塞尔曲线控制点集合
         * @return 修改并返回 out , 输出几个维度的各次幂的系数
         */
        Points_Iterator& calc_BezierCoefficients(Points_Iterator& out, Points_Iterator& points);

        /** 
         * @brief 采样贝塞尔曲线 使用各次幂的系数
         * @param out            输出对象, 采样点, 长度为 dimensional
         * @param coefficients   贝塞尔曲线各次幂系数 ( 使用 calc_BezierCoefficients 计算 )
         * @param t              时间参数t
         * @return 修改并返回 out (采样点)
         */
        var*& sample_Bezier__Coefficients(var *&out, Points_Iterator& coefficients, var t);


        /**
         * @brief 计算贝塞尔曲线分割矩阵 Q
         * @param out 输出对象; 行优先展开的 下三角矩阵 长度为 (1+2+3+...+(n+1)) = ((n+1)*(n+2)/2))
         * @param n   表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @param t   时间参数t, 表示在原曲线的 p(t) 点分割
         * @return 修改out并返回
         */
        var*& calc_CutBezierMatrixQ(var*& out, Idx_Algebra n, var t);
            // 贝塞尔计算矩阵 记作M, M = get_BezierCalcMatrix(n);
            // 对角线矩阵 T = [t^0, t^1, t^2,....,t^n]
            // Q = (M^-1) * T * M
            // start -> p(t) 原曲线起点到分割点 == 矩阵Q右乘控制点 
            // p(t)  -> end  分割点到原曲线终点计算矩阵Q' 为 Q上下颠倒并把元素右移动得到上三角矩阵

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 
         * @param out0      输出对象0, 曲线 p(0~t) 的控制点集合
         * @param out1      输出对象1, 曲线 p(t~1) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 函数修改了两个 out 对象但无返回, 需要手动取需要的对应 out 对象
         */
        void cut_Bezier__ByMatrix(Points_Iterator& out0, Points_Iterator& out1, Points_Iterator& points, var*& cut_matrix_q);

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 
         * @param out       输出对象, 曲线 p(0~t) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 修改并返回 out
         */
        Points_Iterator& cut_Bezier__ByMatrix__p0pt(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q);

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 获取原曲线上的曲线 p(t~1) 的控制点
         * @param out       输出对象, 曲线 p(t~1) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 修改并返回 out
         */
        Points_Iterator& cut_Bezier__ByMatrix__ptp1(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q);

        /** 
         * @brief 通过系数计算贝塞尔曲线控制点
         * @param out               输出对象, 控制点数据 规模与 coefficients 相同;
         * @param coefficients      贝塞尔曲线各次幂系数 ( 使用 calc_BezierCoefficients 计算 )
         * @return 修改 out 一维数组的内容 并返回 
         */
        Points_Iterator& calc_BezierCtrlPoints__Coefficients(Points_Iterator& out, Points_Iterator& coefficients);

        /** 计算 贝塞尔曲线拟合圆弧 的 k 值
         * @param   angle 终点与 (1,0) 夹角弧度
         * @return  返回用于计算拟合圆弧的 k 值
         */
        inline var calc_K__BezierToCyles(var angle){return FOUR_OVER_THREE*tan(angle*0.25);}
        
        /** @brief 贝塞尔曲线拟合四分之一圆 的 k 值 */
        extern const var BEZIER_TO_CYCLES_K__1D4;
        // 三阶二维贝塞尔曲线拟合圆弧公式
        // 单位圆且起点角度为0   示例
        // p1=起点    //(1,0)
        // p2=p1 + (k*圆弧上的点 p1 的导向量)    // (1,k)     
        // p3=p4 + (-k*圆弧上的点 p4 的导向量)   // 需要计算
        // p4=终点
        
    }
}

#endif
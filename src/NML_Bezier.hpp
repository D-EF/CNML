/*!
 * @Description: 数与代数 运算相关
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-06-21 02:56:35
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
        

        typedef Link_List__Int_List Bezier_Clac_Matrix;
        
        /**
         * @brief 获取 贝塞尔曲线计算矩阵
         * @param n 表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @return 返回一个行优先展开的整形下三角矩阵
         */
        int* get_BezierClacMatrix(Idx_Algebra n);

        
        /**
         * @brief 求贝塞尔曲线 各次幂的系数
         * @param out      输出对象, 规模与 points 相同
         * @param points   贝塞尔曲线控制点集合
         * @return 修改并返回 out , 输出几个维度的各次幂的系数
         */
        Points_Iterator& clac_BezierCoefficients(Points_Iterator& out, Points_Iterator& points);

        /** 
         * 采样贝塞尔曲线 使用各次幂的系数
         * @param out               输出对象, 采样点, 长度为 dimensional
         * @param coefficients      贝塞尔曲线各次幂系数 ( 使用 clac_BezierCoefficients 计算 )
         * @return 修改并返回 out (采样点)
         */
        var*& sample_Bezier__Coefficients(var *&out, Points_Iterator& coefficients);


        /**
         * 计算贝塞尔曲线分割矩阵q
         * @param out 输出对象; 行优先展开的 下三角矩阵 长度为 (1+2+3+...+(n+1))
         * @param n   表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @param t   时间参数t
         * @return 修改out并返回
         */
        var*& setup_Matrix__CutBezierMatrixQ(var*& out, Idx_Algebra n, var t);

        
        /** 通过系数创建贝塞尔曲线控制点
         * @param out               输出采样点; 一维数组, 长度为dimensional*points_length
         * @param coefficients      贝塞尔曲线各次幂系数 ( 使用 clac_BezierCoefficients 计算 )
         * @return 修改 out 一维数组的内容 并返回 
         */
        Points_Iterator& calc_BezierCtrlPoints__Coefficients(Points_Iterator& out, Points_Iterator& coefficients);
        

        /** 计算 贝塞尔曲线拟合圆弧 的 k 值
         * @param   angle 终点与 (1,0) 夹角弧度
         * @return  返回用于计算拟合圆弧的 k 值
         */
        inline var calc_K__BezierToCyles(var angle){return FOUR_OVER_THREE*tan(angle*0.25);}
        /** @brief 贝塞尔曲线拟合四分之一圆 的 k 值 */
        const var BEZIER_TO_CYCLES_K__1D4=0.551784777779014;
        // 三阶二维贝塞尔曲线拟合圆弧公式
        // 单位圆且起点角度为0   示例
        // p1=起点    //(1,0)
        // p2=p1 + (k*圆弧上的点 p1 的导向量)    // (1,k)     
        // p3=p4 + (-k*圆弧上的点 p4 的导向量)   // 需要计算
        // p4=终点
        
    }
}

#endif
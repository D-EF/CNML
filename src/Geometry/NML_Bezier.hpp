/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-06 15:27:25
 * @FilePath: \CNML\src\Geometry\NML_Bezier.hpp
 * @Description: 贝塞尔曲线
 */

#ifndef __NML_BEZIER__
#define __NML_BEZIER__

#include "NML.hpp"
#include "./NML_Geometry.hpp"

namespace NML{
    namespace Bezier{

        extern var BEZIER_PROXY_POLYGON_SAMPLE_STEP_SIZE;

        /**
         * @brief 采样贝塞尔曲线 使用DeCasteljau算法 (不建议使用)
         * @param out      输出目标, 采样点 长度为 points.dimensional
         * @param points   贝塞尔曲线控制点集合 长度为 dimensional*points_length
         * @param t        时间参数 t
         * @return 修改并返回 out
         */
        var*& sample_Bezier__DeCasteljau(var*& out, Points_Iterator& points, var t);
        

        typedef Link_Block__Simple<int> Bezier_Calc_Matrix;
        
        /**
         * @brief 获取 贝塞尔曲线计算矩阵
         * @param n 表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @return 返回一个行优先展开的整形下三角矩阵 长度为 (n+1)*(n+2)/2
         */
        int* get_BezierCalcMatrix(Idx_Algebra n);

        
        /**
         * @brief 求贝塞尔曲线 的 系数
         * @param out      输出目标, 规模为 points 的转置
         * @param points   贝塞尔曲线控制点集合
         * @return 修改并返回 out , 输出几个维度的系数
         */
        Points_Iterator& setup_BezierCoefficients(Points_Iterator& out, Points_Iterator& points);

        /** 
         * @brief 采样贝塞尔曲线 使用系数
         * @param out            输出目标, 采样点, 长度为 coefficients.points_length
         * @param coefficients   贝塞尔曲线计算系数 ( 使用 setup_BezierCoefficients 生成 )
         * @param t              时间参数t
         * @return 修改并返回 out (采样点)
         */
        var*& sample_Bezier__Coefficients(var*& out, Points_Iterator& coefficients, var t);

        /** 
         * @brief 采样贝塞尔曲线 使用系数
         * @param out              输出目标, 采样点集合, points_length 应不小于 length__t_list, dimensional 应等于 coefficients.dimensional 
         * @param coefficients     贝塞尔曲线计算系数 ( 使用 setup_BezierCoefficients 生成 )
         * @param t_list           时间参数 t 的集合
         * @param length__t_list   t_list 的长度
         * @return 修改并返回 out (采样点)
         */
        Points_Iterator& sample_Bezier__Coefficients(Points_Iterator& out, Points_Iterator& coefficients, var*& t_list, Idx length__t_list);


        /**
         * @brief 计算贝塞尔曲线分割矩阵 Q
         * @param out 输出目标; 行优先展开的 下三角矩阵 长度为 (1+2+3+...+(n+1)) = ((n+1)*(n+2)/2))
         * @param n   表示n阶贝塞尔曲线 (n=控制点个数-1)
         * @param t   时间参数t, 表示在原曲线的 p(t) 点分割
         * @return 修改out并返回
         */
        var*& calc_CutBezierMatrixQ(var*& out, Idx_Algebra n, var t);
            // 贝塞尔计算矩阵 记作M, M = get_BezierCalcMatrix(n);
            // 对角线矩阵 T = [t^0, t^1, t^2,...., t^n]
            // Q = (M^-1) * T * M
            // start -> p(t) 原曲线起点到分割点 == 矩阵Q右乘控制点 
            // p(t)  -> end  分割点到原曲线终点计算矩阵Q' 为 Q上下颠倒并把元素右移动得到上三角矩阵

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 
         * @param out0      输出目标0, 曲线 p(0~t) 的控制点集合
         * @param out1      输出目标1, 曲线 p(t~1) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 函数修改了两个 out 对象但无返回, 需要手动取需要的对应 out 对象
         */
        void cut_Bezier__ByMatrix(Points_Iterator& out0, Points_Iterator& out1, Points_Iterator& points, var*& cut_matrix_q);

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 
         * @param out       输出目标, 曲线 p(0~t) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 修改并返回 out
         */
        Points_Iterator& cut_Bezier__ByMatrix__p0pt(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q);

        /**
         * @brief 切分贝塞尔曲线 使用分割矩阵Q 获取原曲线上的曲线 p(t~1) 的控制点
         * @param out       输出目标, 曲线 p(t~1) 的控制点集合
         * @param points    原曲线控制点集合
         * @param cut_matrix_q    曲线分割矩阵 使用 calc_CutBezierMatrixQ 函数计算
         * @return 修改并返回 out
         */
        Points_Iterator& cut_Bezier__ByMatrix__ptp1(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q);

        /** 
         * @brief 通过系数计算贝塞尔曲线控制点
         * @param out               输出目标, 控制点数据 规模与 coefficients 相同;
         * @param coefficients      贝塞尔曲线计算系数 ( 使用 setup_BezierCoefficients 生成 )
         * @return 修改 out 并返回 
         */
        Points_Iterator& calc_BezierCtrlPoints__Coefficients(Points_Iterator& out, Points_Iterator& coefficients);

        /** 计算 三阶贝塞尔曲线拟合圆弧 的 k 值
         * @param   angle 终点与 (1, 0) 夹角弧度
         * @return  返回用于计算拟合圆弧的 k 值
         */
        inline var calc_K__BezierToCyles(var angle){return FOUR_OVER_THREE*tan(angle*0.25);}
        
        /** @brief 三阶贝塞尔曲线拟合四分之一圆 的 k 值 */
        extern const var BEZIER_TO_CYCLES_K__1D4;

        // 三阶二维贝塞尔曲线拟合圆弧公式
        // 单位圆且起点角度为0   示例
        // p1=起点    //(1, 0)
        // p2=p1 + (k*圆弧上的点 p1 的导向量)    // (1, k)     
        // p3=p4 + (-k*圆弧上的点 p4 的导向量)   // 需要计算
        // p4=终点
        
        /**
         * 求贝塞尔曲线的导函数 (一维)
         * @param out                   输出对象
         * @param ctrl_points           控制点坐标集合
         * @param length__ctrl_points   控制点的个数长度
         * @return 修改并返回 out, 一组新的贝塞尔曲线控制点
         */
        var*& setup_Derivatives__BezierPoints(var*& out, var*& ctrl_points,Idx_Algebra length__ctrl_points);

        /**
         * 求贝塞尔曲线的导函数
         * @param out           输出对象 应满足 out.point_length == coefficients.point_length-1 && out.dimensional == coefficients.dimensional
         * @param ctrl_points   控制点坐标集合
         * @return 修改并返回 out, 一组新的贝塞尔曲线控制点
         */
        Points_Iterator& setup_Derivatives__BezierPoints(Points_Iterator& out, Points_Iterator& ctrl_points);


        /**
         * @brief 生成拟合贝塞尔曲线的线段路径
         * @param out               输出目标, 如果有 sample_step_size 参数,则 out 长度应为 ceil(1/sample_step_size)
         * @param coefficients      曲线计算系数  ( 使用 setup_BezierCoefficients 生成 )
         * @param _sample_step_size  采样点 t 值的步长, 默认为 1/out.points_length
         */
        Points_Iterator& setup_LinePath__FitBezier(Points_Iterator& out, Points_Iterator& coefficients, var _sample_step_size=0);

        // 线性距离插值

        /**
         * @brief 求线性距离插值的 t
         * @param t_distance    线性距离的 t 值, 取值范围为 [0,1]
         * @param polygon   多边形代理
         * @return 返回对应的 t 值
         */
        var calc_T__LinearDistance__TDistance(var t_distance, Points_Iterator& polygon);
        
        /**
         * @brief 求线性距离插值的 t
         * @param distance      当前在曲线上离起点的距离
         * @param polygon   多边形代理
         * @return 返回对应的 t 值
         */
        var calc_T__LinearDistance__Distance();

        /**
         * @brief 生成贝塞尔曲线的 AABB 包围盒
         * @param out_min       输出的 AABB 盒靠近坐标轴负方向的坐标 
         * @param out_max       输出的 AABB 盒靠近坐标轴正方向的坐标 
         * @param coefficients  计算系数  ( 使用 setup_BezierCoefficients 生成 )
         * @param _derivatives  计算系数的导数; 可选的参数, 用于避免再次生成导数  ( 使用 setup_Derivatives__UnivariatePolynomials 生成 )
         */
        void setup_AABB__Bezier(var*& out_min, var*& out_max, Points_Iterator& coefficients, Points_Iterator* _derivatives=0);

        /**
         * @brief 使用采样坐标计算t值
         * @param out                    计算结果输出对象
         * @param coefficients           某一维度的计算系数
         * @param length                 计算系数的个数
         * @param sample                 当前维度的采样坐标
         * @return 返回对应 t 值的个数
         */
        Idx_Algebra calc_T__BySample_FromBezier(var*& out, var*& coefficients, Idx_Algebra length, var sample);

        /**
         * @brief 找到曲线上靠近参数点的位置
         * @param out            输出目标
         * @param point          参数点
         * @param coefficients   曲线计算系数
         * @param _polygon       拟合曲线的直线段组, 用于辅助计算
         * @param _tolerance     迭代法求近点时的容差
         * @return 返回对应的 t 值
         */
        var find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, Points_Iterator* _polygon=0, var _tolerance=NML_TOLERANCE);

        /**
         * @brief 找到曲线上靠近参数点的位置
         * @param out                                输出目标
         * @param point                              参数点
         * @param coefficients                       曲线计算系数
         * @param _propxy_polygon_sample_step_size   创建拟合曲线的直线段组时的采样步长
         * @param _tolerance                         迭代法求近点时的容差
         * @return 返回对应的 t 值
         */
        var find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, var _propxy_polygon_sample_step_size, var _tolerance=NML_TOLERANCE);
        //  todo test find_NearPoint


        /**
         * @brief 计算各维度的多项式中的根, 并且 ∈ [0,1], 升序排序
         * @param out           t 集合的输出对象 应该有至少 derivatives.points_length*derivatives.dimensional 的长度以保证空间足够存储输出
         * @param derivatives   曲线计算系数的导数
         * @return 返回 t 的个数 (显式查找表的可用数据长度)
         */
        Idx calc_T__DerivativesRootsLUT(var*& out, Points_Iterator& derivatives);



        /** todo:
         * 点在曲线上的投影(近点)(点到曲线的最短距离); test
         * 求交; 
         * 求曲率;
         * 曲线的拐点
         * 包装类
         */

        class Bezier_Object{
            private:
            
            /** 创建线段组代理时的采样精度 */
            var _sample_seed__line;

            public:

            /** 计算系数 */
            Points_Iterator* coefficients;

            /** 缓存的系数长度, 用于判断其他缓存值的空间是否可用 */
            Idx length__coefficients;
            /** 缓存的系数维度, 用于判断其他缓存值的空间是否可用 */
            Idx_Algebra dimensional__coefficients;

            /** 导函数的系数, 使用 had_derivatives 表示是否有效 */
            Points_Iterator* derivatives;

            /** 当前导数是否有效 */
            bool had_derivatives;

            /** 导函数的在各个维度的根, 从小到大 , length__derivatives_root<0 时表示失效 */
            var* derivatives_root;
            
            /** 导函数的根的个数 */
            Idx_Algebra length__derivatives_root;

            /** 根据单调性的拆分出的 aabb, 用于初始化求交函数 monotonic_aabbs.length<0 时表示失效 */
            Geometry::AABB_Nodes monotonic_aabbs;

            /** 线段组代理, 拟合曲线的线段组, 用于计算长度或其他辅助计算, distance<0 时表示失效 */
            Points_Iterator* line_path;

            /** 长度与t的显式查找表, distance<0 时表示失效, t步长 = 采样精度 */
            var* lut__distance;

            /** 缓存曲线长度, 负数表示未计算 */
            var distance;

            /**
             * @brief 直接使用已有的系数进行初始化
             * @param coefficients_ 参数的系数
             */
            Bezier_Object(Points_Iterator& coefficients_){
                coefficients=new Points_Iterator__1DList(coefficients_);
                _sample_seed__line=0.1;
                giveUp_Cache();
            }
            
            /**
             * @brief 直接使用已有的系数进行初始化
             * @param coefficients 参数的系数
             */
            Bezier_Object(){
                this->coefficients=0;
                _sample_seed__line=0.1;
                giveUp_Cache();
            }

            /** 采样点函数 */
            var*& sample(var*& out,var t){ 
                if(!coefficients) throw 0;
                return sample_Bezier__Coefficients(out, *coefficients, t);
            }

            /**
             * @brief 淘汰缓存内容, 使缓存内容标记失效并刷新 length__coefficients , dimensional
             */
            void giveUp_Cache();
            
            /**
             * @brief 为当前曲线计算一个合适的采样精度, 计算过程为 : 计算导数根 >> 采样并链接成线段 >> 使用线段长度计算采样精度
             * @param sample_seed  采样精度的计算种子, 值越小采样精度越高
             * @return 返回采样步长 t_step = sample_seed/(distance(derivatives__roots));
             */
            var calc_SampleStep(var sample_seed=__DEFINE_SAMPLE_SIZE_SEED__);

            /** 
             * @brief 设置线段组代理采样精度
             * @param sample_step 新采样精度
             */
            var set_LineSampleStep(var sample_step){
                _sample_seed__line=sample_step;
                if(lut__distance) {   delete lut__distance;   lut__distance=0;   }
                if(line_path) {       delete line_path;       line_path=0;       }
                return _sample_seed__line;
            }


            /**
             * @brief 加载导数
             */
            void load_Derivatives();

            /**
             * @brief 加载导数根 计算结果将存储到 derivatives_root
             * @param _tolerance 计算导数根时使用的容差
             */
            void load_DerivativesRoot(var _tolerance=__NML_TOLERANCE__);

            /**
             * @brief 加载 单调区间的 AABB
             * @param _tolerance 计算导数根时使用的容差
             */
            void load_MonotonicAABB(var _tolerance=__NML_TOLERANCE__);

            /**
             * @brief 使用控制点初始化曲线对象
             * @param ctrl_points       需要导入的控制点
             */
            void import_CtrlPoints(Points_Iterator& ctrl_points);


            /**
             * @brief 将贝塞尔曲线的计算系数导出为控制点
             * @param out 导出控制点的输出对象
             */
            void export_CtrlPoints(Points_Iterator& out){ calc_BezierCtrlPoints__Coefficients(out,*coefficients); }

        };

    }
}

#endif
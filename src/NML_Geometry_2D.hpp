/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-28 17:47:04
 * @FilePath: \cnml\src\NML_Geometry_2D.hpp
 * @Description: 提供2d基本图元数据结构和部分算法
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef __NML_GEOMETRY_2D__
#define __NML_GEOMETRY_2D__

#include "NML.hpp"
#include "NML_Vector.hpp"

namespace NML{
    
    namespace Geometry_2D{
        
        // open * 2D 基本数据结构体 * open

            /** @brief 一条线段图元数据 */
            typedef struct Point_2D {
                /** @brief 坐标 */
                var x, y; 
            } Point_2D;

            /** @brief 一条线段图元数据 */
            typedef struct Line_Data_2D {
                /** @brief 起点(min)坐标 */
                var x0, y0; 
                /** @brief 终点(max)坐标 */
                var x1, y1;
            } Line_Data_2D;
            
            
            /** @brief 矩形图元数据 */
            typedef struct Rect_Data {
                /** @brief 锚点的 x 坐标 */
                var x;
                /** @brief 锚点的 y 坐标 */
                var y; 
                /** @brief 宽度 ( x 方向偏移量 ) */
                var w; 
                /** @brief 高度 ( y 方向偏移量 ) */
                var h;
            } Rect_Data;

            /**
             * @brief 标准化矩形数据
             * @param rect_data 原矩形数据
             * @return 将 w 和 h 变为非负数 后返回 rect_data
             */
            Rect_Data*& normalize_RectData(Rect_Data*& rect_data);


            /** @brief 圆弧 图元数据 */
            typedef struct Arc_Data {
                /** @brief 圆心 x 坐标 */
                var cx;
                /** @brief 圆心 y 坐标 */
                var cy;
                /** @brief 半径 */
                var r;
                /** @brief 弧线的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
                var theta_0;
                /** @brief 弧线的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
                var theta_1;
            } Arc_Data;

            /**
             * @brief 标准化弧形数据
             * @param arc_data 原矩形数据
             * @return 将 (theta_1-theta_0) 变为非负数
             */
            Arc_Data*& normalize_ArcData(Arc_Data*& arc_data);

            /** @brief 椭圆弧线 图元数据 */
            typedef struct Ellipse_Arc_Data {
                /** @brief 圆心 x 坐标 */
                var cx;
                /** @brief 圆心 y 坐标 */
                var cy;
                /** @brief 局部水平方向半径 */
                var rx;
                /** @brief 局部垂直方向半径 */
                var ry;
                /** @brief 弧线的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
                var theta_0;
                /** @brief 弧线的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
                var theta_1;
                /** @brief 旋转偏移量 */
                var rotate;
            } Ellipse_Arc_Data;


            /** @brief AABB 轴对齐包围盒 min={x0, y0}; max={x1, y1}; */
            typedef Line_Data_2D AABB_2D;

            /**
             * @brief 检查点是否在AABB内部
             * @param aabb AABB 轴对齐包围盒数据
             * @param x 点的 x 坐标
             * @param y 点的 y 坐标
             * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
             */
            char check_Inside__AABB(AABB_2D aabb, var x, var y);

        // end  * 2D 基本数据结构体 * end 


        /**
         * @brief 生成旋转值单位向量
         * @param out   输出地址
         * @param angle 旋转量
         * @return 修改并返回 out
         */
        inline var*& setup_Vector2__Rotate(var*&out, var angle){   out[0]=cos(angle);   out[1]=sin(angle);   return out;   }

        /**
         * @brief 生成旋转值单位向量
         * @param out   输出地址
         * @param angle 旋转量
         * @return 修改并返回 out
         */
        inline Point_2D create_Point2D__Rotate(var angle){   return { cos(angle), sin(angle) };   }


        /**
         * @brief 计算线段长度
         * @param x0 线段端点0 的x坐标
         * @param y0 线段端点0 的y坐标
         * @param x1 线段端点1 的x坐标
         * @param y1 线段端点1 的y坐标
         * @return 返回计算的长度值
         */
        inline var calc_LineLength(var x0, var y0, var x1, var y1){   var x=x0-x1;   var y=y0-y1;   return sqrt(x*x+y*y);  }

        /** 
         * @brief x正方向->向量(x, y) 的弧度
         * @param x 向量 x 坐标
         * @param y 向量 y 坐标
         * @return 返回计算的弧度值
         */
        inline var get_Angle(var x, var y){return atan2(y, x);}

        
        /** 
         * @brief 获取点在线段上的投影信息
         * @param p_x           需要投射的点 的 x 坐标
         * @param p_y           需要投射的点 的 y 坐标
         * @param line_p0_x     线段的端点 0 的 x 坐标
         * @param line_p0_y     线段的端点 0 的 y 坐标
         * @param line_p1_x     线段的端点 1 的 x 坐标
         * @param line_p1_y     线段的端点 1 的 y 坐标
         * @return 返回投影系数 t ( t ∈ [0, 1] ) 表示投射落点在 p0->p1 的位置
         */
        inline var get_PointInLine(var p_x, var p_y, var line_p0_x, var line_p0_y, var line_p1_x, var line_p1_y){
            var temp_x0= p_x - line_p0_x,    temp_x1= line_p1_x - line_p0_x,
                temp_y0= p_y - line_p0_y,    temp_y1= line_p1_y - line_p0_y;
            return temp_x0*temp_x1+temp_y0*temp_y1 / (sqrt(temp_x1*temp_x1+temp_y1*temp_y1));
        }

        /**
         * @brief 从线段上取采样点
         * @param out    输出对象
         * @param t      时间参数t [0~1]
         * @param p0_x   线段起点 x 坐标
         * @param p0_y   线段起点 y 坐标
         * @param p1_x   线段终点 x 坐标
         * @param p1_y   线段终点 y 坐标
         * @return 修改并返回 out
         */
        inline var*& sample_Line(var*& out, var t, var p0_x, var p0_y, var p1_x, var p1_y){
            var td=1-t;
            out[0]=p0_x*td+p1_x*t;
            out[1]=p0_y*td+p1_y*t;
            return out;
        }

        
        /** 
         * @param p_x           需要投射的点 的 x 坐标
         * @param p_y           需要投射的点 的 y 坐标
         * @param line_p0_x     线段的端点 0 的 x 坐标
         * @param line_p0_y     线段的端点 0 的 y 坐标
         * @param line_p1_x     线段的端点 1 的 x 坐标
         * @param line_p1_y     线段的端点 1 的 y 坐标
         * @return 返回投影系数 t ( t ∈ [0, 1] ) 表示投射落点在 p0->p1 的位置
         */
        inline var get_DistanceOfPointToLine(var p_x, var p_y, var line_p0_x, var line_p0_y, var line_p1_x, var line_p1_y){
            var t=get_PointInLine(p_x, p_y, line_p0_x, line_p0_y, line_p1_x, line_p1_y);
            var td=1-t;
            return calc_LineLength(
                line_p0_x*td+line_p1_x*t,   line_p0_y*td+line_p1_y*t,
                p_x,                         p_y
            );
        }

        
        // open * 求交函数 * open

            /**
             * @brief 检查一组 AABB 盒是否重叠
             * @param box0_p0_x  AABB 0的描述点 0 的 x 坐标
             * @param box0_p0_y  AABB 0的描述点 0 的 y 坐标
             * @param box0_p1_x  AABB 0的描述点 1 的 x 坐标
             * @param box0_p1_y  AABB 0的描述点 1 的 y 坐标
             * @param box1_p0_x  AABB 1的描述点 0 的 x 坐标
             * @param box1_p0_y  AABB 1的描述点 0 的 y 坐标
             * @param box1_p1_x  AABB 1的描述点 1 的 x 坐标
             * @param box1_p1_y  AABB 1的描述点 1 的 y 坐标
             * @return 返回 AABB 盒是否重叠
             */
            inline bool check_Overlap__AABB(var box0_p0_x, var box0_p0_y, var box0_p1_x, var box0_p1_y, var box1_p0_x, var box1_p0_y, var box1_p1_x, var box1_p1_y){
                return  (((box0_p0_x>box1_p0_x)!=(box0_p0_x>box1_p1_x))||((box0_p1_x>box1_p0_x)!=(box0_p1_x>box1_p1_x))||((box1_p0_x>box0_p0_x)!=(box1_p0_x>box0_p1_x))||((box1_p1_x>box0_p0_x)!=(box1_p1_x>box0_p1_x)))&&
                        (((box0_p0_y>box1_p0_y)!=(box0_p0_y>box1_p1_y))||((box0_p1_y>box1_p0_y)!=(box0_p1_y>box1_p1_y))||((box1_p0_y>box0_p0_y)!=(box1_p0_y>box0_p1_y))||((box1_p1_y>box0_p0_y)!=(box1_p1_y>box0_p1_y)));
            }

            /**
             * @brief 检查两条线段相交情况
             * @param line0_p0_x    线段 0 的 起点 的 x 坐标
             * @param line0_p0_y    线段 0 的 起点 的 y 坐标
             * @param line0_p1_x    线段 0 的 终点 的 x 坐标
             * @param line0_p1_y    线段 0 的 终点 的 y 坐标
             * @param line1_p0_x    线段 1 的 起点 的 x 坐标
             * @param line1_p0_y    线段 1 的 起点 的 y 坐标
             * @param line1_p1_x    线段 1 的 终点 的 x 坐标
             * @param line1_p1_y    线段 1 的 终点 的 y 坐标
             * @return 返回 1 表示正常相交; 0 表示没有相交; -1 表示 l1 终点在 l2 上, 或者 l2 起点在 l1 上; 2 表示 l2 终点在 l1 上, 或者 l1 起点在 l2 上; 
             */
            char check_Intersection__Line_Line(var line0_p0_x, var line0_p0_y, var line0_p1_x, var line0_p1_y, var line1_p0_x, var line1_p0_y, var line1_p1_x, var line1_p1_y);

            /**
             * @brief 求两线段交点
             * @param out           输出对象
             * @param line0_p0_x    线段 0 的 起点 的 x 坐标
             * @param line0_p0_y    线段 0 的 起点 的 y 坐标
             * @param line0_p1_x    线段 0 的 终点 的 x 坐标
             * @param line0_p1_y    线段 0 的 终点 的 y 坐标
             * @param line1_p0_x    线段 1 的 起点 的 x 坐标
             * @param line1_p0_y    线段 1 的 起点 的 y 坐标
             * @param line1_p1_x    线段 1 的 终点 的 x 坐标
             * @param line1_p1_y    线段 1 的 终点 的 y 坐标
             * @return 修改并返回 out ; 如果out内容为 Infinity 或 -Infinity 则为未相交
             */
            var*& calc_Intersection__Line_Line(var*& out , var line0_p0_x, var line0_p0_y, var line0_p1_x, var line0_p1_y, var line1_p0_x, var line1_p0_y, var line1_p1_x, var line1_p1_y);

            /**
             * @brief 检查两圆是否相交
             * @param cx0   圆0 的圆心 x 坐标
             * @param cy0   圆0 的圆心 y 坐标
             * @param r0    圆0 的半径
             * @param cx1   圆1 的圆心 x 坐标
             * @param cy1   圆1 的圆心 y 坐标
             * @param r1    圆1 的半径
             * @return 返回是否相交
             */
            bool check_Intersection__Circle_Circle(var cx0, var cy0, var r0, var cx1, var cy1, var r1);

            /**
             * @brief 两圆求交点
             * @param out   输出对象, 点长度应大于等于2
             * @param cx0   圆0 的圆心 x 坐标
             * @param cy0   圆0 的圆心 y 坐标
             * @param r0    圆0 的半径
             * @param cx1   圆1 的圆心 x 坐标
             * @param cy1   圆1 的圆心 y 坐标
             * @param r1    圆1 的半径
             * @return 输出交点数量, 如果两个圆重合，将输出-1
             */
            char calc_Intersection__Circle_Circle(Points_Iterator*& out, var cx0, var cy0, var r0, var cx1, var cy1, var r1);

            /**
             * @brief 检查两弧形是否相交
             * @param cx0         弧形0 的圆心 x 坐标
             * @param cy0         弧形0 的圆心 y 坐标
             * @param r0          弧形0 的半径
             * @param theta_0_0   弧形0 的端点弧度
             * @param theta_0_1   弧形0 的端点弧度
             * @param cx1         弧形1 的圆心 x 坐标
             * @param cy1         弧形1 的圆心 y 坐标
             * @param r1          弧形1 的半径
             * @param theta_1_0   弧形1 的端点弧度
             * @param theta_1_1   弧形1 的端点弧度
             * @return 返回是否相交
             */
            bool check_Intersection__Arc_Arc(var cx0, var cy0, var r0, var theta_0_0, var theta_0_1, var cx1, var cy1, var r1, var theta_1_0, var theta_1_1);

            /**
             * @brief 求圆与线段的交点
             * @param out   输出对象, 点长度应大于等于2
             * @param cx0   圆0 的圆心 x 坐标
             * @param cy0   圆0 的圆心 y 坐标
             * @param r0    圆0 的半径
             * @param line_p0_x    线段 的 起点 的 x 坐标
             * @param line_p0_y    线段 的 起点 的 y 坐标
             * @param line_p1_x    线段 的 终点 的 x 坐标
             * @param line_p1_y    线段 的 终点 的 y 坐标
             * @return 输出有多少交点
             */
            char calc_Intersection__Circle_Line(Points_Iterator*& out, var cx0, var cy0, var r0, var line_p0_x, var line_p0_y, var line_p1_x, var line_p1_y);

            /**
             * @brief 求弧形与线段的相交情况
             * @param out   输出对象, 点长度应大于等于2
             * @param cx0   圆0 的圆心 x 坐标
             * @param cy0   圆0 的圆心 y 坐标
             * @param r0    圆0 的半径
             * @param line_p0_x    线段 的 起点 的 x 坐标
             * @param line_p0_y    线段 的 起点 的 y 坐标
             * @param line_p1_x    线段 的 终点 的 x 坐标
             * @param line_p1_y    线段 的 终点 的 y 坐标
             * @return 输出有多少交点
             */
            char check_Intersection__Arc_Line(var cx0, var cy0, var r0, var line_p0_x, var line_p0_y, var line_p1_x, var line_p1_y);

            /**
             * @brief 求圆与线段的交点
             * @param out   输出对象, 点长度应大于等于2
             * @param cx0   圆0 的圆心 x 坐标
             * @param cy0   圆0 的圆心 y 坐标
             * @param r0    圆0 的半径
             * @param line_p0_x    线段 的 起点 的 x 坐标
             * @param line_p0_y    线段 的 起点 的 y 坐标
             * @param line_p1_x    线段 的 终点 的 x 坐标
             * @param line_p1_y    线段 的 终点 的 y 坐标
             * @return 输出有多少交点
             */
            char calc_Intersection__Arc_Line(Points_Iterator*& out, var cx0, var cy0, var r0, var line_p0_x, var line_p0_y, var line_p1_x, var line_p1_y);

        // end  * 求交函数 * end 


        // open * 不同参数调用原函数的重载函数 * open

            /**
             * @brief 计算线段长度
             * @param point_0 线段端点0 的x坐标
             * @param point_1 线段端点1 的x坐标
             * @return 返回计算的长度值
             */
            inline var calc_LineLength(var *point_0, var *point_1){ return calc_LineLength(point_0[0], point_0[1], point_1[0], point_1[1]);}

            /**
             * @brief 计算线段长度
             * @param line 线段数据
             * @return 返回计算的长度值
             */
            inline var calc_LineLength(Line_Data_2D line){ return calc_LineLength(line.x0, line.y0, line.x1, line.y1);}

            /** 
             * @brief 取向量和x正方向的弧度
             * @param v 坐标
             * @return 返回计算的弧度值
             */
            inline var get_Angle(var* v){return atan2(v[1], v[0]);}
            
        // end  * 不同参数调用原函数的重载函数 * end 
    }

}

#endif
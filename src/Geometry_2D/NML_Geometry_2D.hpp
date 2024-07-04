/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-01 14:32:40
 * @FilePath: \CNML\src\Geometry_2D\NML_Geometry_2D.hpp
 * @Description: 2D图形相关内容
 */

#ifndef __NML_GEOMETRY_2D__
#define __NML_GEOMETRY_2D__

#include "NML.hpp"
#include "Algebra/NML_Vector.hpp"
#include "./NML_Matrix_2D.hpp"
#include "Link_Block/NML_Link_Block.hpp"

namespace NML{
    
    namespace Geometry_2D{
        
        // open * 2D 基本数据结构体 * open

            /** @brief 2D点 */
            typedef struct Point_2D {
                /** @brief 坐标 */
                var x, y; 
            } Point_2D;
            
            /** @brief 一条2D线段图元数据 */
            typedef struct Line_2D
            {
                Point_2D p0;
                Point_2D p1;
            } Line_2D;
            
            typedef Line_2D AABB_2D;

            /**
             * @brief 使用两个点设置 AABB
             * @param out AABB 的输出对象
             * @param p_0 参数点 0
             * @param p_1 参数点 1
             */
            void setup_AABB_ByPoint(var* out, var*& p_0, var*& p_1);
            
            /**
             * @brief 使用两个点设置 AABB
             * @param out AABB 的输出对象
             * @param p_0 参数点 0
             * @param p_1 参数点 1
             */
            void setup_AABB_ByPoint(var* out, Point_2D& p_0, Point_2D& p_1);


            /**
             * @brief 检查点是否在AABB内部
             * @param aabb_p0 AABB 的端点 0
             * @param aabb_p1 AABB 的端点 1
             * @param p 点的坐标
             * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
             */
            inline Idx_Algebra check_Inside__AABB(Point_2D& aabb_p0, Point_2D& aabb_p1, Point_2D& p){
                return check_Inside__Range(aabb_p0.x,aabb_p1.x,p.x) && 
                       check_Inside__Range(aabb_p0.y,aabb_p1.y,p.y) ;
            }

            
            /**
             * @brief 将一个 AABB 进行线性变换后得到新的 AABB
             * @param min 原 AABB 的 min 向量, 函数执行后将被修改 
             * @param max 原 AABB 的 max 向量, 函数执行后将被修改 
             * @param transform_matrix 变换矩阵
             */
            void transform_AABB(var*& min, var*& max, var*& transform_matrix);

            
            // open * 矩形 * open
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
                Rect_Data& normalize_RectData(Rect_Data& rect_data);

            // end  * 矩形 * end 

            // open * 弧形 & 椭圆弧线 * open

                /** @brief 圆弧 图元数据 */
                typedef struct Arc_Data {
                    /** @brief 圆心坐标 */
                    Point_2D centre;
                    /** @brief 半径 */
                    var radius;
                    /** @brief 弧形起点与x正方向的旋转偏移量 */
                    var theta_op;
                    /** @brief 弧形的终点与起点的旋转偏移量 */
                    var theta_ed;
                } Arc_Data;

                /**
                 * @brief 标准化弧形绘制弧度
                 * @param theta_op     弧形的绘制起点相对圆心的向量 与 x 正方向 的夹角弧度
                 * @param theta_ed   弧形的绘制终点与绘制起点 theta_op 的偏移量
                 * @return 
                 *         当 theta_ed-theta_op > 2π, 直接将 theta_op, theta_ed 赋值为 -π, π
                 *         将 theta_op 限制在 [-π,π] 内, 且 theta_ed-theta_op 的值保持不变
                 */
                void normalize_DrawArcTheta(var& theta_op, var& theta_ed);

                /**
                 * @brief 标准化弧形绘制数据
                 * @param arc_data 原矩形数据
                 * @return 使用 normalize_DrawArcTheta 另弧度值规范化
                 */
                inline Arc_Data& normalize_DrawArcData(Arc_Data& arc_data){
                    normalize_DrawArcTheta(arc_data.theta_op,arc_data.theta_ed);
                    return arc_data;
                }
                

                /** @brief 椭圆弧形 图元数据 */
                typedef struct Ellipse_Arc_Data {
                    /** @brief 圆心坐标 */
                    Point_2D centre;
                    /** @brief 局部水平方向半径 */
                    var radius_x;
                    /** @brief 局部垂直方向半径 */
                    var radius_y;
                    /** @brief 弧形的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
                    var theta0;
                    /** @brief 弧形的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
                    var theta1;
                    /** @brief 旋转偏移量 */
                    var rotate;
                } Ellipse_Arc_Data;

                /** 
                 * @brief 计算椭圆的焦距
                 * @param rx x方向上的半径
                 * @param ry y方向上的半径
                 * @return 返回椭圆的焦距
                 */
                inline var calc_EllipseFocalLength(var rx, var ry){return sqrt(abs(rx*rx-ry*ry));}

                /** 
                 * @brief 计算椭圆的缩放比 x/y
                 * @param rx x方向上的半径
                 * @param ry y方向上的半径
                 * @return 返回椭圆的缩放比
                 */
                inline var calc_EllipseScaleValue(var rx, var ry){return rx/ry;}
                
                /** 
                 * @brief 计算椭圆相对圆心的焦点
                 * @param rx     x方向上的半径
                 * @param ry     y方向上的半径
                 * @param rotate 椭圆的旋转偏移量
                 * @return 返回椭圆的焦点相对于圆心的位置(正方向)
                 */
                Point_2D calc_EllipseFocus(var rx, var ry,var rotate);
                
                /** 
                 * @brief 计算椭圆的焦距
                 * @param ellipse_arc_data 椭圆的数据
                 * @return 返回椭圆的焦距
                 */
                inline var calc_EllipseFocalLength(Ellipse_Arc_Data ellipse_arc_data){
                    return calc_EllipseFocalLength(ellipse_arc_data.radius_x,ellipse_arc_data.radius_y);
                }

                /** 
                 * @brief 计算椭圆的缩放比
                 * @param ellipse_arc_data 椭圆的数据
                 * @return 返回椭圆的缩放比
                 */
                inline var calc_EllipseScaleValue(Ellipse_Arc_Data ellipse_arc_data){
                    return calc_EllipseScaleValue(ellipse_arc_data.radius_x,ellipse_arc_data.radius_y);
                }

                /** 
                 * @brief 计算椭圆的焦点
                 * @param ellipse_arc_data 椭圆的数据
                 * @return 返回椭圆的焦点
                 */
                inline Point_2D calc_EllipseFocus(Ellipse_Arc_Data ellipse_arc_data){
                    return calc_EllipseFocus(ellipse_arc_data.radius_x,ellipse_arc_data.radius_y,ellipse_arc_data.rotate);
                }

            // end  * 弧形 & 椭圆弧线 * end 


        // end  * 2D 基本数据结构体 * end 

        /**
         * @brief 生成旋转值单位向量
         * @param out   输出地址
         * @param theta 旋转量
         * @return 修改并返回 out
         */
        inline var*& setup_Vector2__Rotate(var*&out, var theta){   out[0]=cos(theta);   out[1]=sin(theta);   return out;   }

        /**
         * @brief 生成旋转值单位向量
         * @param out   输出地址
         * @param theta 旋转量
         * @return 修改并返回 out
         */
        inline Point_2D calc_Point2D__Rotate(var theta){   return { cos(theta), sin(theta) };   }

        /**
         * @brief 判断点是否在夹角的内部
         * @param ray_op   夹角起边的点
         * @param ray_ed   夹角终边的点
         * @param point    点的坐标
         * @param is_ray_more_than_pi   夹角是否大于半圆(PI)
         * @return 返回点是否在夹角内部
         */
        inline bool check_Inside__Angle(Point_2D& ray_op,Point_2D& ray_ed, Point_2D& point, bool is_angle_more_than_pi){
            return (Vector::cross_V2(ray_op.x,ray_op.y,point.x,point.y)>=0) && 
                   ((Vector::cross_V2(ray_ed.x,ray_ed.y,point.x,point.y)<=0)||(is_angle_more_than_pi));
        }

        /**
         * @brief 判断点是否在夹角的内部
         * @param theta_op   夹角起点的弧度
         * @param theta_ed   夹角终点的弧度
         * @param point      点的坐标
         * @return 返回点是否在夹角内部
         */
        inline bool check_Inside__Angle(var theta_op, var theta_ed, Point_2D& point){
            Point_2D op=calc_Point2D__Rotate(theta_op);
            Point_2D ed=calc_Point2D__Rotate(theta_ed);
            return check_Inside__Angle(op,ed, point,(theta_ed-theta_op>PI));
        }

        /**
         * @brief 计算线段长度
         * @param point_0 线段端点 0
         * @param point_1 线段端点 1
         * @return 返回计算的长度值
         */
        inline var calc_LineLength(Point_2D& point_0, Point_2D& point_1){   
            var x=point_0.x-point_1.x;   
            var y=point_0.y-point_1.y;   
            return sqrt(x*x+y*y);  
        }
        
        /** 
         * @brief x正方向与向量(x, y) 的夹角弧度
         * @param x 向量 x 坐标
         * @param y 向量 y 坐标
         * @return 返回计算的弧度值
         */
        inline var calc_VectorAngle(var x, var y){return atan2(y, x);}
        
        /** 
         * @brief x正方向与向量(x, y) 的夹角弧度
         * @param x 向量 x 坐标
         * @param y 向量 y 坐标
         * @return 返回计算的弧度值
         */
        inline var calc_VectorAngle(Point_2D& point){return atan2(point.y, point.x);}


        /** 
         * @brief 求直线(p0->p1)与x正方向的夹角弧度
         * @param p0 点 p0 的坐标
         * @param p1 点 p1 的坐标
         * @return 返回计算的弧度值
         */
        inline var calc_LineAngle(Point_2D& p0, Point_2D& p1){return atan2(p1.y-p0.y, p1.x-p0.x);}
        
        /** 
         * @brief 求直线与x正方向的夹角弧度
         * @param p0 点 p0 的坐标
         * @param p1 点 p1 的坐标
         * @return 返回计算的弧度值
         */
        inline var calc_LineAngle(var* p0, var* p1){return atan2(p1[1]-p0[1], p1[0]-p0[0]);}

        /** 
         * @brief 获取点在线段上的投影信息
         * @param line_p0   线段的端点 0 
         * @param line_p1   线段的端点 1 
         * @param point     需要投射的点
         * @return 返回投影系数 t, 表示投射落点在 p0->p1 的位置
         */
        inline var calc_PointInLine(Point_2D& line_p0, Point_2D& line_p1, Point_2D& point){
            Point_2D temp0 = { point.x-line_p0.x,     point.y-line_p0.y     };
            Point_2D temp1 = { line_p1.x-line_p0.x,   line_p1.y-line_p0.y   };

            return temp0.x*temp1.x+temp0.y*temp1.y / (sqrt(temp1.x*temp1.x+temp1.y*temp1.y));
        }

        /**
         * @brief 从线段上取采样点
         * @param out        输出目标
         * @param t          时间参数t [0~1]
         * @param point_op   线段起点 x 坐标
         * @param point_ed   线段终点 y 坐标
         * @return 修改并返回 out
         */
        inline var*& sample_Line(var*& out, var t, Point_2D& point_op, Point_2D& point_ed){
            var td=1-t;
            out[0]=point_op.x*td+point_ed.x*t;
            out[1]=point_op.y*td+point_ed.y*t;
            return out;
        }

        
        /** 
         * @brief 计算点到线段的距离
         * @param line_p0   线段的端点 0 的坐标
         * @param line_p1   线段的端点 1 的坐标
         * @param point     需要投射的点 的坐标
         * @return 
         */
        inline var calc_DistanceOfPointToLine(Point_2D& line_p0, Point_2D& line_p1, Point_2D& point){
            var t=calc_PointInLine(line_p0, line_p1, point);
            var td=1-t;
            Point_2D point_t = {line_p0.x*td+line_p1.x*t,   line_p0.y*td+line_p1.y*t};
            return calc_LineLength(point_t,point);
        }

        
        // open * 求交函数 * open
            // todo 求交函数实现

            /**
             * @brief 检查两个 AABB 盒是否有重叠部分
             * @param min0  AABB 0 的最小坐标
             * @param max0  AABB 0 的最大坐标
             * @param min1  AABB 1 的最小坐标
             * @param max1  AABB 1 的最大坐标
             * @return 返回 AABB 盒是否重叠
             */
            inline bool check_Overlap__AABB_AABB(Point_2D& min0, Point_2D& max0, Point_2D& min1, Point_2D& max1){
                return  min0.x<=max1.x && min1.x<=max0.x &&
                        min0.y<=max1.y && min1.y<=max0.y ;
            }

            /**
             * @brief 检查两个 AABB 盒是否有重叠部分
             * @param aabb_0  AABB 0 : {min_x, min_y, max_x, max_y}
             * @param aabb_1  AABB 1 : {min_x, min_y, max_x, max_y}
             * @return 返回 AABB 盒是否重叠
             */
            inline bool check_Overlap__AABB_AABB(var* aabb_0, var* aabb_1){
                return  aabb_0[0]<=aabb_1[2] && aabb_1[0]<=aabb_0[2] &&
                        aabb_0[1]<=aabb_1[3] && aabb_1[1]<=aabb_0[3] ;
            }


            
            /**
             * @brief 求两组夹角的绘制交集 (同圆心同半径的扇形的交集)
             * @param out          交集输出目标, 输出交集的弧度范围 [[min,max],[min,max]]
             * @param theta0_min   扇形0 起点弧度
             * @param theta0_max   扇形0 终点弧度
             * @param theta1_min   扇形1 起点弧度
             * @param theta1_max   扇形1 终点弧度
             * @return 返回两个弧形绘制弧度有多少组交集
             */
            Idx_Algebra calc_Intersection__Theta_Theta(Points_Iterator& out, var theta0_min_x, var theta0_min_y, var theta0_max_x, var theta0_max_y, var theta1_min_x, var theta1_min_y, var theta1_max_x, var theta1_max_y);
            
            /**
             * @brief 求两组夹角的绘制交集 (同圆心同半径的扇形的交集)
             * @param out          交集输出目标, 输出交集的弧度范围 [[min,max],[min,max]]
             * @param theta0_min   扇形0 起点弧度
             * @param theta0_max   扇形0 终点弧度
             * @param theta1_min   扇形1 起点弧度
             * @param theta1_max   扇形1 终点弧度
             * @return 返回两个弧形绘制弧度有多少组交集
             */
            Idx_Algebra calc_Intersection__Theta_Theta(Points_Iterator& out, var theta0_min, var theta0_max, var theta1_min, var theta1_max);



            /**
             * 计算相对于点 line0_p0 的 line0_p1 与line1两点的叉积的乘积
             * 用于跨立检查, 检查线段 line1 两点是否跨过直线 line0 两边, 当两次叉积异号时(跨立) 值应小于 0 或 容差
             */
            var calc_cross__Line_Line(Point_2D& line0_p0, Point_2D& line0_p1, Point_2D& line1_p0, Point_2D& line1_p1);

            /**
             * @brief 检查两条线段相交情况
             * @param line0_p0    线段 0 的起点坐标
             * @param line0_p1    线段 0 的终点坐标
             * @param line1_p0    线段 1 的起点坐标
             * @param line1_p1    线段 1 的终点坐标
             * @return 返回两个线段是否相交
             */
            inline bool check_Intersection__Line_Line(Point_2D& line0_p0, Point_2D& line0_p1, Point_2D& line1_p0, Point_2D& line1_p1){
                // 两次跨立检查即可判断是否相交
                return  (calc_cross__Line_Line(line0_p0,line0_p0,line0_p1,line0_p1) < NML_TOLERANCE) &&
                        (calc_cross__Line_Line(line1_p0,line1_p0,line1_p1,line1_p1) < NML_TOLERANCE) ;
            }
            
            /**
             * @brief 求两线段交点
             * @param line0_p0    线段 0 的起点坐标
             * @param line0_p1    线段 0 的终点坐标
             * @param line1_p0    线段 1 的起点坐标
             * @param line1_p1    线段 1 的终点坐标
             * @return 计算出线段交点 ; 如果内容为 INFINITY 则表示找不到交点
             */
            Point_2D calc_Intersection__Line_Line(Point_2D& line0_p0, Point_2D& line0_p1, Point_2D& line1_p0, Point_2D& line1_p1);

            /**
             * @brief 检查两圆是否相交 ( 仅检查圆的边是否有相交, 无视一个圆完全被另一个圆覆盖的情况 )
             * @param c0   圆0 的圆心 x 坐标
             * @param r0   圆0 的半径
             * @param c1   圆1 的圆心 x 坐标
             * @param r1   圆1 的半径
             * @return 返回是否相交
             */
            inline bool check_Intersection__Circle_Circle(var c0_x, var c0_y, var r0, var c1_x, var c1_y, var r1){
                var l=Vector::mag_v2( c1_x-c0_x , c1_y-c0_y );
                return !( l>r1+r0 || l<abs(r1-r0) );
            }

            /** 
             * @brief 检查两个圆形是否有重叠部分
             * @param c0_x   圆0 的圆心 x 坐标
             * @param c0_y   圆0 的圆心 y 坐标
             * @param r0     圆0 的半径
             * @param c1_x   圆1 的圆心 x 坐标
             * @param c1_y   圆1 的圆心 y 坐标
             * @param r1     圆1 的半径
             * @return 返回是否有重叠部分
             */
            inline bool check_Overlap__Circle_Circle(var c0_x, var c0_y, var r0, var c1_x, var c1_y, var r1){
                var l=Vector::mag_v2( c1_x-c0_x , c1_y-c0_y );
                return !(l>r1+r0);
            }

            /**
             * @brief 两圆求交点
             * @param out    输出目标, 点数量应大于等于2
             * @param c0_x   圆0 的圆心 x 坐标
             * @param c0_y   圆0 的圆心 y 坐标
             * @param r0     圆0 的半径
             * @param c1_x   圆1 的圆心 x 坐标
             * @param c1_y   圆1 的圆心 y 坐标
             * @param r1     圆1 的半径
             * @return 输出交点数量, 如果两个圆重合，将输出-1
             */
            Idx_Algebra calc_Intersection__Circle_Circle(Points_Iterator& out, var c0_x, var c0_y, var r0, var c1_x, var c1_y, var r1);


            /**
             * @brief 求两弧形交点
             * @param out              输出目标, 点数量应大于等于2, 存储弧形相同半径的同心圆的交点
             * @param c0_x             弧形0 的圆心 x 坐标
             * @param c0_y             弧形0 的圆心 y 坐标
             * @param r0               弧形0 的半径
             * @param theta0_op        弧形0 起点弧度
             * @param theta0_ed        弧形0 终点弧度
             * @param c1_x             弧形1 的圆心 x 坐标
             * @param c1_y             弧形1 的圆心 y 坐标
             * @param r1               弧形1 的半径
             * @param theta1_op        弧形1 起点弧度
             * @param theta1_ed        弧形1 终点弧度
             * @param _use_normalize   是否执行规范化弧度值的操作, 默认为false, 应仅在不确认传入数据是否合法时使用 true
             * @return 返回 0:无相交; 1: [out[0]]; 2:[out[1]]; 3:[out[0],out[1]]; -1:弧形有重合部分, 重合的弧度存储到out[0]中;
             */
            Idx_Algebra calc_Intersection__Arc_Arc(Points_Iterator& out, var c0_x, var c0_y, var r0, var theta0_op, var theta0_ed, var c1_x, var c1_y, var r1, var theta1_op, var theta1_ed, bool _use_normalize=false);


            // ↓↓↓ todo test ↓↓↓

            /**
             * @brief 求圆与线段的交点
             * @param out       输出目标, 点数量应大于等于2
             * @param c_x       圆0 的圆心 x 坐标
             * @param c_y       圆0 的圆心 y 坐标
             * @param r         圆0 的半径
             * @param line_p0   线段端点0 的坐标
             * @param line_p1   线段端点1 的坐标
             * @return 输出有多少交点
             */
            Idx_Algebra calc_Intersection__Circle_Line(Points_Iterator& out, var c_x, var c_y, var r, Point_2D& line_p0, Point_2D& line_p1);

            /**
             * @brief 求圆与线段的交点
             * @param out        输出目标, 点数量应大于等于2
             * @param c_x        弧形的圆心 x 坐标
             * @param c_y        弧形的圆心 y 坐标
             * @param r          弧形的半径
             * @param theta_op   弧形起点弧度
             * @param theta_ed   弧形终点弧度
             * @param line_p0    线段端点0 的坐标
             * @param line_p1    线段端点1 的坐标
             * @return 输出有多少交点
             */
            Idx_Algebra calc_Intersection__Arc_Line(Points_Iterator& out, var c_x, var c_y, var r, var theta_op, var theta_ed, Point_2D& line_p0, Point_2D& line_p1);

        // end  * 求交函数 * end 


        // open * 不同参数调用原函数的重载函数 * open

            /**
             * @brief 计算线段长度
             * @param point_0 线段端点0 的坐标
             * @param point_1 线段端点1 的坐标
             * @return 返回计算的长度值
             */
            inline var calc_LineLength(var* point_0, var* point_1){ return calc_LineLength(*(Point_2D*)point_0, *(Point_2D*)point_1); }

            /** 
             * @brief 取向量和x正方向的夹角弧度
             * @param v 坐标
             * @return 返回计算的弧度值
             */
            inline var calc_VectorAngle(var* v){return atan2(v[1], v[0]);}
            
        // end  * 不同参数调用原函数的重载函数 * end 
                
    }

}

#endif
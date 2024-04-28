/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-04-28 16:56:17
 * @FilePath: \CNML\src\Geometry_2D\NML_Bezier_2D.cpp
 * @Description: 2D 贝塞尔曲线相关计算
 */

#include "NML_Bezier_2D.hpp"
#include "Geometry/NML_Bezier.hpp"
#include "./NML_Geometry_2D.hpp"


namespace NML{
    
    namespace Geometry_2D{

        Idx_Algebra calc_Intersection__Bezier_Line(Points_Iterator& out, Points_Iterator& coefficients, var*& line_p0, var*& line_p1){
            Idx_Algebra rtn=0;
            var *t_intersection = new var[coefficients.points_length];
            var *temp_coefficients = new var[coefficients.points_length];
            var *temp_point;
            Idx i;

            // 计算相对坐标
            var x=line_p1[0]-line_p0[0],
                y=line_p0[1]-line_p1[1];
            var mag=sqrt(x*x+y*y);
            if(check_Zero(mag)) return 0;
            mag=1/mag;
            x *= mag;
            y *= mag;

            // 进行平移+旋转变换 使线段处于x正方向上
            temp_point=coefficients[0];
            temp_coefficients[0] = x*(temp_point[0]-line_p0[0]) + y*(temp_point[1]-line_p0[1]);
            for(i=1;  i<coefficients.points_length;  ++i){
                temp_point=coefficients[i];
                temp_coefficients[i] = x*temp_point[0] + y*temp_point[1];
                // 由于计算t值时仅需使用一个维度, 所以仅计算一个维度的值
            }

            Idx_Algebra t_length = Bezier::calc_T__BySample_FromBezier(t_intersection, temp_coefficients, coefficients.points_length, 0);

            // 采样点并保存在线段上的点
            for(i=0;  i<t_length;  ++i){
                temp_point=out[rtn];
                Bezier::sample_Bezier__Coefficients(temp_point, coefficients, t_intersection[i]);
                var projection_value = calc_PointInLine(*(Point_2D*)line_p0, *(Point_2D*)line_p1, *(Point_2D*)temp_point);
                if(projection_value>=0 && projection_value<=1) ++rtn;
            }

            delete t_intersection;
            delete temp_coefficients;
            return rtn;
        }


        typedef class Node__Bezier_AABB{
            public:
            Node__Bezier_AABB* half_0 = 0;
            Node__Bezier_AABB* half_1 = 0;
            var aabb[4];
            var t_0, t_1;
            Node__Bezier_AABB():half_0(0),half_1(0){}
        } Node__Bezier_AABB;

        /**
         * 创建 贝塞尔曲线单调区间 的 AABB 组
         * @param points 曲线单调性变换位置的采样点(任一方向上的驻点)集合
         * @param t_list 曲线各个维度的导数根集合, 是 points 对应的 t 值
         * @param length t_list 和 points 的可用长度
         * @return 返回一组 Node__Bezier_AABB 数组, 包含曲线中的 AABB 集合
         */
        Node__Bezier_AABB* create_BezierMonotonicAABBGroud(Points_Iterator& points, var*& t_list, Idx length){
            if(length<2) return 0;
            
            Idx i;
            Node__Bezier_AABB* now_node=new Node__Bezier_AABB[length-1]();
            var *p_0, *p_1;

            p_1=points[0];
            for(i=0;  i<length-1;  ++i){
                p_0=p_1;
                p_1=points[i+1];
                now_node[i].t_0 = t_list[i];
                now_node[i].t_1 = t_list[i+1];
                setup_AABB_ByPoint(now_node[i].aabb, p_0, p_1);
            }
            
            return now_node;
        }

        /**
         * @brief 释放 create_BezierMonotonicAABBGroud 与迭代生成的内容
         */
        void free_BezierAABBGroud(Node__Bezier_AABB* target, Idx length){
            Node__Bezier_AABB *now_node;
            Link_Block__Simple<Node__Bezier_AABB*> *path;
            Idx i;

            for(i=0;  i<length;  ++i){
                now_node=target+i;
                // path=
                // todo
            }
        }

        Idx calc_Intersection__Bezier_Bezier(
            Points_Iterator&   out, 
            Points_Iterator&   coefficients_0, 
            Points_Iterator&   coefficients_1, 
            var*&              derivatives_roots_lut_0, 
            Idx                length__derivatives_roots_lut_0, 
            var*&              derivatives_roots_lut_1, 
            Idx                length__derivatives_roots_lut_1  
        ){
            Points_Iterator *aabb_point_list_0 = new Points_Iterator__1DList(coefficients_0.dimensional, length__derivatives_roots_lut_0);
            Points_Iterator *aabb_point_list_1 = new Points_Iterator__1DList(coefficients_1.dimensional, length__derivatives_roots_lut_1);

            Bezier::sample_Bezier__Coefficients(*aabb_point_list_0, coefficients_0, derivatives_roots_lut_0, length__derivatives_roots_lut_0);
            Bezier::sample_Bezier__Coefficients(*aabb_point_list_1, coefficients_1, derivatives_roots_lut_1, length__derivatives_roots_lut_1);

            Node__Bezier_AABB * aabb_gound_0 = create_BezierMonotonicAABBGroud(*aabb_point_list_0, derivatives_roots_lut_0, length__derivatives_roots_lut_0);
            Node__Bezier_AABB * aabb_gound_1 = create_BezierMonotonicAABBGroud(*aabb_point_list_1, derivatives_roots_lut_1, length__derivatives_roots_lut_1);

            Idx i,j,rtn;

            delete aabb_point_list_0;
            delete aabb_point_list_1;

            // todo check pair_gound
            
            return rtn;
        }
    }
}
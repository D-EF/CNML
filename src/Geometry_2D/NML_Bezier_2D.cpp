/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-05-27 09:21:05
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

    }
}
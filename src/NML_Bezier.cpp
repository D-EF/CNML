/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-06 09:59:23
 * @FilePath: \CNML\src\NML_Bezier.cpp
 * @Description: 贝塞尔曲线
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#include "NML_Bezier.hpp"
#include "NML_Algebra.hpp"
#include "NML_Geometry.hpp"
#include "NML_Geometry_2D.hpp"
#include "NML_Matrix_2D.hpp"

namespace NML{
    namespace Bezier{
        var *&sample_Bezier__DeCasteljau(var*& out, Points_Iterator& points, var t){
            if(points.points_length>1){
                Points_Iterator__1DList new_points(points.dimensional, points.points_length-1);
                var td=1-t;
                for(int i=0;  i>=0;  --i){
                    var *temp_point__new=new_points[i];
                    var *temp_point__low=points[i];
                    var *temp_point__low1=points[i+1];
                    for(int j=0;  j<points.dimensional;  ++j){
                        temp_point__new[j]=td*temp_point__low[j]+t*temp_point__low1[j];
                    }
                }
                sample_Bezier__DeCasteljau(out, new_points, t);
                new_points.free_Data();
                return out;
            }else{
                for(int i=0; i<points.dimensional;  ++i){
                    out[i]=points[0][i];
                }
                return out;
            }
        }

        // 缓存的贝塞尔曲线计算矩阵
        Bezier_Calc_Matrix _BEZIER_CALC_MATRIX={&_BEZIER_CALC_MATRIX, 0, new int[1]{1}};
        // 最后一次 get 的 贝塞尔曲线计算矩阵 用于加速查找
        Bezier_Calc_Matrix* _last_load_bezier_calc_matrix=&_BEZIER_CALC_MATRIX;

        int* get_BezierCalcMatrix(Idx_Algebra n){
            Bezier_Calc_Matrix *ptr__move, *ptr__static;
            ptr__move=ptr__static = _last_load_bezier_calc_matrix;
            // 查找缓存
            while (!(n==ptr__move->length||ptr__move->next==ptr__static)){
                ptr__move=ptr__move->next;
            }
            if(ptr__move->length==n){
                _last_load_bezier_calc_matrix=ptr__move;
                return ptr__move->data;
            }
            
            Link_Block__Simple<int> *temp_pascals_triangle_line= Algebra::get_PascalsTriangleLine(n);   // 第n行的帕斯卡三角
            Link_Block__Simple<int> *move_pascals_triangle_line= &Algebra::_G_PASCALS_TRIANGLE;         // 从第0行帕斯卡三角开始
            Idx matrix_n=n+1;
            Idx new_length=(matrix_n)*(matrix_n+1)/2;
            int *new_matrix_data=new int[new_length];

            Idx_Algebra idx_new_matrix=0, f=1;
            for(int i=0;  i<=matrix_n;  ++i, move_pascals_triangle_line=move_pascals_triangle_line->next){
                f=1&i?-1:+1;
                for(int j=0;  j<=i;  ++j, ++idx_new_matrix){
                    new_matrix_data[idx_new_matrix] = move_pascals_triangle_line->data[j] * temp_pascals_triangle_line->data[i] * f;
                    f*=-1;
                }
            }
            Bezier_Calc_Matrix *new_bezier_calc_matrix=new Bezier_Calc_Matrix{ptr__static, n, new_matrix_data};
            ptr__move->next=new_bezier_calc_matrix;
            _last_load_bezier_calc_matrix=new_bezier_calc_matrix;
            return new_matrix_data;
        }


        Points_Iterator& setup_BezierCoefficients(Points_Iterator& out, Points_Iterator& points){
            const Idx n=out.points_length-1;
            Idx_Algebra &dimensional=out.dimensional;
            int *_bezier_calc_matrix=get_BezierCalcMatrix(n);
            var *editing_target;
            var *temp=new var[dimensional];
            Idx i, j, idx_m=0;
            for(i=0;  i<=n;  ++i){
                var *cnm=points[i];
                editing_target=out[i];
                std::fill_n(temp, dimensional, 0);
                for(j=0;  j<=i;  ++j, ++idx_m){
                    var *point=points[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        temp[d]+=_bezier_calc_matrix[idx_m]*point[d];
                    }
                }
                std::copy(temp, temp+dimensional, editing_target);
            }
            delete temp;
            return out;
        }
        

        var*& sample_Bezier__Coefficients(var*& out, Points_Iterator& coefficients, var t){
            Idx_Algebra &dimensional=coefficients.dimensional;
            std::fill_n(out, dimensional, 0);
            var power_t=1;
            for(Idx i=0;  i<coefficients.points_length;  ++i){
                var *line=coefficients[i];
                for(Idx_Algebra d=0;  d<dimensional;  ++d){
                    out[d]+=power_t*line[d];
                }
                power_t*=t;
            }
            return out;
        }

        Points_Iterator& sample_Bezier__Coefficients(Points_Iterator& out, Points_Iterator& coefficients, var*& t_list, Idx length__t_list){
            var *temp_point;
            for(Idx i=0;  i<length__t_list;  ++i){
                temp_point=coefficients[i];
                Bezier::sample_Bezier__Coefficients(temp_point,coefficients,t_list[i]);
            }
            return out;
        }

        var*& calc_CutBezierMatrixQ(var*& out, Idx_Algebra n, var t){
            if(Algebra::_last_calc_pascals_triangle->length<n){
                Algebra::_calc_PascalsTriangle(n);
            }

            Idx_Algebra u, v;
            Idx index=0;
            // Init matrix of pascals triangle
            Link_Block__Simple<int> *pascals_line = Algebra::get_PascalsTriangleLine(0);
            for(v=0;  v<=n;  ++v){
                for(u=0;  u<=pascals_line->length;  ++u, ++index){
                    out[index]=pascals_line->data[u];
                }
                pascals_line=pascals_line->next;
            }

            var d = 1.0-t;
            var temp = t;

            // 1
            // 1   t   
            // 1   t   tt
            // 1   t   tt   ttt
            Idx idx_uv=0;
            for(u=1;  u<=n;  ++u, temp*=t){
                idx_uv+=u+1;
                index=idx_uv;
                for(v=u;  v<=n;  ++v, index+=v){
                    out[index]*=temp;
                }
            }
            
            // 1
            // d    1
            // dd   d    1
            // ddd  dd   d    1
            temp=d;
            idx_uv=0;
            for(v=1;  v<=n;  ++v, temp*=d){
                idx_uv+=v;
                index=idx_uv;
                for(u=v;  u<=n;  ++u, index+=u+1){
                    out[index]*=temp;
                }
            }

            return out;
        }


        void cut_Bezier__ByMatrix(Points_Iterator& out0, Points_Iterator& out1, Points_Iterator& points, var*& cut_matrix_q){
            cut_Bezier__ByMatrix__p0pt(out0, points, cut_matrix_q);
            cut_Bezier__ByMatrix__ptp1(out1, points, cut_matrix_q);
        }

        
        Points_Iterator& cut_Bezier__ByMatrix__p0pt(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q){
            Idx_Algebra &dimensional=points.dimensional;
            Idx idx_m=1;
            var *calcing_target=out[0], *point;
            std::copy(points[0], points[0]+dimensional, calcing_target);
            
            for(Idx i=1;  i<points.points_length;  ++i){
                calcing_target=out[i];
                std::fill_n(calcing_target, dimensional, 0);
                for(Idx j=0;  j<=i;  ++j, ++idx_m){
                    point=points[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        calcing_target[d]+=point[d]*cut_matrix_q[idx_m];
                    }
                }
            }
            return out;
        }


        Points_Iterator& cut_Bezier__ByMatrix__ptp1(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q){
            Idx_Algebra &dimensional=points.dimensional;
            Idx &length=points.points_length;
            Idx idx_m, idx_line=length*(length+1)/2;
            Idx n=length-1;
            var *calcing_target=out[n], *point;
            std::copy(points[n], points[n]+dimensional, calcing_target);
            
            for(Idx i=0, ii=length;  i<n;  ++i, --ii){
                calcing_target=out[i];
                std::fill_n(calcing_target, dimensional, 0);
                idx_line-=ii;
                idx_m=idx_line;
                for(Idx j=i;  j<length;  ++j, ++idx_m){
                    point=points[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        calcing_target[d]+=point[d]*cut_matrix_q[idx_m];
                    }
                }
            }
            return out;
        }


        Points_Iterator& calc_BezierCtrlPoints__Coefficients(Points_Iterator& out, Points_Iterator& coefficients){
            Idx &length=coefficients.points_length;
            Idx_Algebra &dimensional=coefficients.dimensional;
            int *m=get_BezierCalcMatrix(length-1);
            var *temp=new var[dimensional], *calcing_tgt;
            Idx idx_m=0;
            for(Idx i=0;  i<length;  ++i, ++idx_m){
                std::copy(coefficients[i], coefficients[i]+dimensional, temp);
                for(var j=0;  j<i;  ++j, ++idx_m){
                    calcing_tgt=out[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        temp[d]-=calcing_tgt[d]*m[idx_m];
                    }
                }
                var *calcing_tgt=out[i];
                for(Idx_Algebra d=0;  d<dimensional;  ++d){
                    calcing_tgt[d]=temp[d]/m[idx_m];
                }
            }
            return out;
        }

        const var BEZIER_TO_CYCLES_K__1D4=0.551784777779014;

        
        var*& setup_Derivatives__BezierPoints(var*& out, var*& ctrl_points,Idx_Algebra length__ctrl_points){
            // n 指 n阶贝塞尔曲线, 导数的控制点长度为原曲线的控制点个数-1, 导数的 n 为原曲线的控制点个数-2
            Idx_Algebra n=length__ctrl_points-2, i;
            for(i=0;  i<=n;  ++i){
                out[i] = n*(ctrl_points[i+1]-ctrl_points[i]);
            }
            return out;
        }

        Points_Iterator& setup_Derivatives__BezierPoints(Points_Iterator& out, Points_Iterator& ctrl_points){
            // n 指 n阶贝塞尔曲线, 导数的控制点长度为原曲线的控制点个数-1, 导数的 n 为原曲线的控制点个数-2
            Idx_Algebra n=out.points_length-1, i, j, d=out.dimensional;
            for(i=0;i<=n;++i){
                var* temp_out = out[i];
                var* temp_0   = ctrl_points[i];
                var* temp_1   = ctrl_points[i+1];
                for(j=0;  j<d;  ++j){
                    temp_out[j] = n*(temp_1[j]-temp_0[j]);
                }
            }
            return out;
        }



        Points_Iterator& setup_LinePath__FitBezier(Points_Iterator& out, Points_Iterator& coefficients, var _sample_step_size){
            if(!_sample_step_size) _sample_step_size=1/out.points_length;
            var t=0;
            Idx i=0;
            var *editor_target;
            do{
                editor_target=out[i];
                sample_Bezier__Coefficients(editor_target,coefficients,t);
                ++i;
                t+=_sample_step_size;
            }while(t<NML::NML_TOLERANCE_D1);
            editor_target=out[i];
            sample_Bezier__Coefficients(editor_target,coefficients,1);
            return out;
        }


        void setup_AABB__Bezier(var*& out_min, var*& out_max, Points_Iterator& coefficients, Points_Iterator* _derivatives){
            bool flag__create_derivatives=false;
            if(!_derivatives){
                _derivatives=new Points_Iterator__1DList(coefficients);
                Algebra::setup_Derivatives__UnivariatePolynomials(*_derivatives,coefficients);
                flag__create_derivatives=true;
            }

            Idx idx_derivatives, idx_point, idx_t, l=_derivatives->points_length, d=_derivatives->dimensional;

            var* derivatives__dimensional     = new var[l];
            var* coefficients__dimensional   = new var[l+1];
            var* roots__dimensional          = new var[l+2];
            Idx_Algebra length__roots;
            var temp_sample;

            for(idx_derivatives=0;  idx_derivatives<d;  ++idx_derivatives){
                out_min[idx_derivatives]=+INFINITY;
                out_max[idx_derivatives]=-INFINITY;
                for(idx_point=0;  idx_point<l;  ++idx_point){
                    derivatives__dimensional[idx_point]   = (*_derivatives)[idx_point][idx_derivatives];
                    coefficients__dimensional[idx_point] = coefficients[idx_point][idx_derivatives];
                }
                
                length__roots = Algebra::calc_Roots__UnivariatePolynomials(roots__dimensional, derivatives__dimensional, l) + 2;
                roots__dimensional[length__roots-2] = 0;
                roots__dimensional[length__roots-1] = 1;

                for(idx_t=0;  idx_t<length__roots;  ++idx_t){
                    if(roots__dimensional[idx_t]<0 || roots__dimensional[idx_t]>1) continue;
                    temp_sample=0;
                    for(idx_point=0;  idx_point<l;  ++idx_point){
                        roots__dimensional[idx_point] *= roots__dimensional[idx_point];
                        temp_sample += roots__dimensional[idx_point]*coefficients__dimensional[idx_point];
                    }
                    if(temp_sample < out_min[idx_derivatives])out_min[idx_derivatives]=temp_sample;
                    if(temp_sample > out_max[idx_derivatives])out_max[idx_derivatives]=temp_sample;
                }
            }

            delete derivatives__dimensional;
            delete roots__dimensional;
            if(flag__create_derivatives) delete _derivatives;
        }


        Idx_Algebra calc_T__BySample_FromBezier(var*& out, var*& coefficients, Idx_Algebra length, var sample){
            var *_coefficients=new var[length];
            _coefficients[0]+=sample;
            std::copy(coefficients,coefficients+length,_coefficients);
            Algebra::calc_Roots__UnivariatePolynomials(out,_coefficients,length);
            Idx_Algebra i, idx_root=0;
            for(i=0;i<length;++i){
                if(out[i]>=0&&out[i]<=1){
                    out[idx_root]=out[i];
                    ++idx_root;
                }
            }
            return idx_root;
        }


        var find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, Points_Iterator& polygon, var _tolerance){
            var temp_value=INFINITY;
            var temp_value_0, temp_value_1;
            var temp, temp_0, temp_1=0;
            Idx idx_min;
            Idx i;
            
            // 找到多边形代理中的近点
            for(i=0;  i<polygon.points_length;  ++i){
                if(temp_value > (temp_0=Geometry::calc_LineDistance(point, polygon[i], coefficients.dimensional))){
                    temp_value=temp_0;
                    idx_min=i;
                }
            }
            // open * 可能接近起点 or 终点 * open 
                if(idx_min==0)                         temp_1 = 0-_tolerance*10;   // 可能接近起点
                if(idx_min==polygon.points_length-1)   temp_1 = 1+_tolerance*10;   // 可能接近终点
                if(temp_1!=0.0){
                    sample_Bezier__Coefficients(out, coefficients,temp_1);
                    if(Geometry::calc_LineDistance(point, out, coefficients.dimensional)<temp_value){
                        if(temp_1>1){
                            std::copy(polygon[polygon.points_length-1], polygon[polygon.points_length-1]+polygon.dimensional, out);
                            return 1;
                        }
                        else {
                            std::copy(polygon[0], polygon[0]+polygon.dimensional, out);
                            return 0;
                        }
                    }
                }
            // end  * 可能接近起点 or 终点 * end  

            // 二分法逼近 近点
            var one_over_polygon_points_length = 1/polygon.points_length;
            if(idx_min==0){
                temp_0 = idx_min * one_over_polygon_points_length;
                temp_1 = (idx_min+1) * one_over_polygon_points_length;
                temp_value_0 = temp_value;
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_1 = Geometry::calc_LineDistance(point, out, coefficients.dimensional);
            }else if(idx_min==polygon.points_length-1){
                temp_0 = (idx_min-1) * one_over_polygon_points_length;
                temp_1 = idx_min * one_over_polygon_points_length;
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_0 = Geometry::calc_LineDistance(point, out, coefficients.dimensional);
                temp_value_1 = temp_value;
            }else{
                temp_0 = (idx_min-1) * one_over_polygon_points_length;
                temp_1 = (idx_min+1) * one_over_polygon_points_length;
                sample_Bezier__Coefficients(out,coefficients,temp_0);
                temp_value_0 = Geometry::calc_LineDistance(point, out, coefficients.dimensional);
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_1 = Geometry::calc_LineDistance(point, out, coefficients.dimensional);
            }

            do{
                temp = (temp_0+temp_1)*0.5;
                sample_Bezier__Coefficients(out,coefficients,temp);
                temp_value = Geometry::calc_LineDistance(point, out, coefficients.dimensional);
                if(temp_value_0<temp_value_1){
                    temp_value_1 = temp_value;
                    temp_1 = temp;
                }else{
                    temp_value_0 = temp_value;
                    temp_0 = temp;
                }
            }while(!check_Equal(temp_0,temp_1,_tolerance));

            return temp;
        }


        var find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, var _propxy_polygon_sample_step_size, var _tolerance){
            Points_Iterator* polygon;
            polygon=new Points_Iterator__1DList(coefficients.dimensional,std::ceil(_propxy_polygon_sample_step_size));
            setup_LinePath__FitBezier(*polygon,coefficients,_propxy_polygon_sample_step_size);
            Idx_Algebra rtn=find_NearPoint(out, point, coefficients, polygon, _tolerance);
            delete polygon;
            return rtn;
        }


        Idx calc_T_DerivativesRootsLUT(var*& out, Points_Iterator& derivatives){
            var *temp_dimensional = new var[derivatives.points_length];
            var *temp_out;
            Idx rtn,l=1;
            Idx i,j;

            out[0]=0;

            // 计算各个维度的导数根
            for(i=0;  i<derivatives.dimensional;  ++i){
                for(j=0;  j<derivatives.points_length;  ++j){
                    temp_dimensional[j]=derivatives[j][i];
                }
                temp_out=out+l;
                l+=Algebra::calc_Roots__UnivariatePolynomials(temp_out,temp_dimensional,derivatives.points_length);
            }
            out[l]=1;
            ++l;

            // 排序
            rtn=l;
            for(i=1;  i<l;  ++i){
                if((out[i]<0) || (out[i]>1)){
                    out[i]=INFINITY;
                    --rtn;
                } 
            }
            for(i=1;  i<l;  ++i){
                for(j=0;  j<l-i;  ++j){
                    if(out[j] < out[j+1]){
                        std::swap(out[j],out[j+1]);
                    }
                }
            }

            delete temp_dimensional;
            return rtn;
        }

    }

    
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
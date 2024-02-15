/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-02-16 03:21:46
 * @FilePath: \CNML\src\NML_Bezier.cpp
 * @Description: 贝塞尔曲线
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML_Bezier.hpp"
#include "NML_Algebra.hpp"
#include "NML_Geometry.hpp"

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
            while (!(n==ptr__move->size||ptr__move->next==ptr__static)){
                ptr__move=ptr__move->next;
            }
            if(ptr__move->size==n){
                _last_load_bezier_calc_matrix=ptr__move;
                return ptr__move->data;
            }
            
            Link_Block<int> *temp_pascals_triangle_line= Algebra::get_PascalsTriangleLine(n);   // 第n行的帕斯卡三角
            Link_Block<int> *move_pascals_triangle_line= &Algebra::_G_PASCALS_TRIANGLE;         // 从第0行帕斯卡三角开始
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


        var*& calc_CutBezierMatrixQ(var*& out, Idx_Algebra n, var t){
            if(Algebra::_last_calc_pascals_triangle->size<n){
                Algebra::_calc_PascalsTriangle(n);
            }

            Idx_Algebra u, v;
            Idx index=0;
            // Init matrix of pascals triangle
            Link_Block<int> *pascals_line = Algebra::get_PascalsTriangleLine(0);
            for(v=0;  v<=n;  ++v){
                for(u=0;  u<=pascals_line->size;  ++u, ++index){
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
            Idx index_uv=0;
            for(u=1;  u<=n;  ++u, temp*=t){
                index_uv+=u+1;
                index=index_uv;
                for(v=u;  v<=n;  ++v, index+=v){
                    out[index]*=temp;
                }
            }
            
            // 1
            // d    1
            // dd   d    1
            // ddd  dd   d    1
            temp=d;
            index_uv=0;
            for(v=1;  v<=n;  ++v, temp*=d){
                index_uv+=v;
                index=index_uv;
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
            Idx index_m=1;
            var *calcing_target=out[0], *point;
            std::copy(points[0], points[0]+dimensional, calcing_target);
            
            for(Idx i=1;  i<points.points_length;  ++i){
                calcing_target=out[i];
                std::fill_n(calcing_target, dimensional, 0);
                for(Idx j=0;  j<=i;  ++j, ++index_m){
                    point=points[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        calcing_target[d]+=point[d]*cut_matrix_q[index_m];
                    }
                }
            }
            return out;
        }


        Points_Iterator& cut_Bezier__ByMatrix__ptp1(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q){
            Idx_Algebra &dimensional=points.dimensional;
            Idx &length=points.points_length;
            Idx index_m, index_line=length*(length+1)/2;
            Idx n=length-1;
            var *calcing_target=out[n], *point;
            std::copy(points[n], points[n]+dimensional, calcing_target);
            
            for(Idx i=0, ii=length;  i<n;  ++i, --ii){
                calcing_target=out[i];
                std::fill_n(calcing_target, dimensional, 0);
                index_line-=ii;
                index_m=index_line;
                for(Idx j=i;  j<length;  ++j, ++index_m){
                    point=points[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        calcing_target[d]+=point[d]*cut_matrix_q[index_m];
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
            Idx index_m=0;
            for(Idx i=0;  i<length;  ++i, ++index_m){
                std::copy(coefficients[i], coefficients[i]+dimensional, temp);
                for(var j=0;  j<i;  ++j, ++index_m){
                    calcing_tgt=out[j];
                    for(Idx_Algebra d=0;  d<dimensional;  ++d){
                        temp[d]-=calcing_tgt[d]*m[index_m];
                    }
                }
                var *calcing_tgt=out[i];
                for(Idx_Algebra d=0;  d<dimensional;  ++d){
                    calcing_tgt[d]=temp[d]/m[index_m];
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


        void setup_AABB__Bezier(var*& out_min, var*& out_max, Points_Iterator& coefficients, Points_Iterator* derivatives){
            bool flag__create_derivatives=false;
            if(!derivatives){
                derivatives=new Points_Iterator__1DList(coefficients);
                Algebra::setup_Derivatives__UnivariatePolynomials(*derivatives,coefficients);
                flag__create_derivatives=true;
            }

            Idx idx_derivatives, idx_point, idx_t, l=derivatives->points_length, d=derivatives->dimensional;

            var* derivatives__dimensional     = new var[l];
            var* coefficients__dimensional   = new var[l+1];
            var* roots__dimensional          = new var[l+2];
            Idx_Algebra length__roots;
            var temp_sample;

            for(idx_derivatives=0;  idx_derivatives<d;  ++idx_derivatives){
                out_min[idx_derivatives]=+INFINITY;
                out_max[idx_derivatives]=-INFINITY;
                for(idx_point=0;  idx_point<l;  ++idx_point){
                    derivatives__dimensional[idx_point]   = (*derivatives)[idx_point][idx_derivatives];
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
            if(flag__create_derivatives) delete derivatives;
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
        

        Idx_Algebra find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, var _propxy_polygon_sample_step_size, var _tolerance){
            Points_Iterator* polygon;
            polygon=new Points_Iterator__1DList(coefficients.dimensional,std::ceil(_propxy_polygon_sample_step_size));
            setup_LinePath__FitBezier(*polygon,coefficients,_propxy_polygon_sample_step_size);
            Idx_Algebra rtn=find_NearPoint(out, point, coefficients, polygon, _tolerance);
            delete polygon;
            return rtn;
        }

        Idx_Algebra find_NearPoint(var*& out, var*& point, Points_Iterator& coefficients, Points_Iterator& polygon, var _tolerance){
            var temp_value=INFINITY;
            var temp_value_0, temp_value_1;
            var temp, temp_0, temp_1=0;
            Idx idx_min;
            Idx i;
            
            // 找到多边形代理中的近点

            for(i=1;  i<polygon.points_length;  ++i){
                if(temp_value > (temp_0=Geometry::calc_LineLong(point, polygon[i], coefficients.dimensional))){
                    temp_value=temp_0;
                    idx_min=i;
                }
            }
            // open * 可能接近起点 or 终点 * open 
                if(idx_min==0)                         temp_1 = 0-_tolerance;   // 可能接近起点
                if(idx_min==polygon.points_length-1)   temp_1 = 1+_tolerance;   // 可能接近终点
                if(temp_1!=0.0){
                    sample_Bezier__Coefficients(out, coefficients,temp_1);
                    if(Geometry::calc_LineLong(point, out, coefficients.dimensional)<temp_value){
                        if(temp_1>1){
                            std::copy(polygon[polygon.points_length-1], polygon[polygon.points_length-1]+polygon.dimensional, out);
                            return 2;
                        }
                        else {
                            std::copy(polygon[0], polygon[0]+polygon.dimensional, out);
                            return 1;
                        }
                    }
                }
            // end  * 可能接近起点 or 终点 * end  

            // 二分法逼近 近点
            var one_of_polygon_points_length=1/polygon.points_length;
            if(idx_min<0){
                temp_0=idx_min*one_of_polygon_points_length;
                temp_1=(idx_min+1)*one_of_polygon_points_length;
                temp_value_0=temp_value;
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_1=Geometry::calc_LineLong(point, out, coefficients.dimensional);
            }else if(idx_min>polygon.points_length){
                temp_0=(idx_min-1)*one_of_polygon_points_length;
                temp_1=idx_min*one_of_polygon_points_length;
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_0=Geometry::calc_LineLong(point, out, coefficients.dimensional);
                temp_value_1=temp_value;
            }else{
                temp_0=(idx_min-1)*one_of_polygon_points_length;
                temp_1=(idx_min+1)*one_of_polygon_points_length;
                sample_Bezier__Coefficients(out,coefficients,temp_0);
                temp_value_0=Geometry::calc_LineLong(point, out, coefficients.dimensional);
                sample_Bezier__Coefficients(out,coefficients,temp_1);
                temp_value_1=Geometry::calc_LineLong(point, out, coefficients.dimensional);
            }

            do{
                temp=(temp_0+temp_1)*0.5;
                sample_Bezier__Coefficients(out,coefficients,temp);
                temp_value=Geometry::calc_LineLong(point, out, coefficients.dimensional);
                if(temp_value_0<temp_value_1){
                    temp_value_1=temp_value;
                    temp_1=temp;
                }else{
                    temp_value_0=temp_value;
                    temp_0=temp;
                }
            }while(!check_Equal(temp_0,temp_1,_tolerance));

            return 0;
        }

    }
}
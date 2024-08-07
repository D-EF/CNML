/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-24 09:45:39
 * @FilePath: \CNML\src\Geometry\NML_Bezier.cpp
 * @Description: 贝塞尔曲线
 */

#include "Algebra/NML_Algebra.hpp"
#include "./NML_Bezier.hpp"
#include "./NML_Geometry.hpp"

namespace NML{
    namespace Bezier{
        var BEZIER_PROXY_POLYGON_SAMPLE_STEP_SIZE=0.1;
        
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
                sample_Bezier__Coefficients(temp_point,coefficients,t_list[i]);
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

            var* derivatives__dimensional    = new var[l];
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
            Idx_Algebra rtn=find_NearPoint(out, point, coefficients, *polygon, _tolerance);
            delete polygon;
            return rtn;
        }


        Idx calc_T__DerivativesRootsLUT(var*& out, Points_Iterator& derivatives){
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


        Idx setup_BezierMonotonicLut(var*& out, Points_Iterator& coefficients){
            Points_Iterator__1DList temp_derivatives(coefficients.dimensional,coefficients.points_length-1);
            if(out==0) out = new var[temp_derivatives.points_length*temp_derivatives.dimensional];
            Algebra::setup_Derivatives__UnivariatePolynomials(temp_derivatives, coefficients);
            Idx rtn = calc_T__DerivativesRootsLUT(out, temp_derivatives);
            return rtn;
        }


        void Bezier_Object::giveUp_Cache(){
            if(!coefficients){
                derivatives                = 0;
                derivatives_root           = 0;
                monotonic_aabbs.nodes      = 0;
                line_path                  = 0;
                had_derivatives            = false;
                length__derivatives_root   = -1;
                distance                   = -1;
                monotonic_aabbs.length     = -1;
                return;
            }
            if((length__coefficients!=coefficients->points_length) || (dimensional__coefficients!=coefficients->dimensional) ){   // 曲线计算系数的空间修改, 则其他缓存的空间也要修改
                if(derivatives)        {   delete derivatives;        derivatives=0;        }
                if(derivatives_root)   {   delete derivatives_root;   derivatives_root=0;   }
                if(monotonic_aabbs.nodes)     {   delete monotonic_aabbs.nodes;     monotonic_aabbs.nodes=0;     }
            }
            if(dimensional__coefficients){   // line_path 点的维度与曲线的维度需要相同
                if(line_path)   {   delete line_path;   line_path=0;   }
            }
            length__coefficients=coefficients->points_length;
            dimensional__coefficients=coefficients->dimensional;

            had_derivatives   = false;

            // lut__distance 的数据长度由采样精度决定, 所以此处仅将 distance 置负, 在更新 _sample_seed__line 时删除内存 (set_SampleStep(var))

            length__derivatives_root   = -1;
            distance                   = -1;
            monotonic_aabbs.length     = -1;
        }


        var Bezier_Object::calc_SampleStep(var sample_seed){ 
            using namespace Geometry;
            var derivatives__root;
            load_MonotonicAABB();
            NML::Geometry::AABB_Node* node = monotonic_aabbs.nodes;
            Idx_Algebra &d=node->dimensional;
            Idx i;
            for(i=0;  i < node->dimensional;  ++i, node=monotonic_aabbs.nodes+i){
                derivatives__root+=calc_LineDistance(node->aabb, node->aabb+d, d);
            }
            return sample_seed / derivatives__root;
        }


        void Bezier_Object::load_Derivatives(){
            if(!derivatives){
                derivatives=new Points_Iterator__1DList(coefficients->dimensional, coefficients->points_length-1);
                had_derivatives=false;
            }
            if(!had_derivatives){
                Algebra::setup_Derivatives__UnivariatePolynomials(*derivatives, *coefficients);
            }
        }

        void Bezier_Object:: load_DerivativesRoot(var _tolerance){
            if(!derivatives_root){
                derivatives_root=new var[derivatives->points_length*derivatives->dimensional];
                length__derivatives_root=-1;
            }
            if(length__derivatives_root>=0){
                load_Derivatives();
                length__derivatives_root = calc_T__DerivativesRootsLUT(derivatives_root,*derivatives);
            }
        }

        void Bezier_Object::load_MonotonicAABB(var _tolerance){
            load_DerivativesRoot(_tolerance);
            if(monotonic_aabbs.nodes && monotonic_aabbs.length>0) return;
            Idx i, j=1;
            Idx_Algebra &dimensional = dimensional__coefficients;

            if(!monotonic_aabbs.nodes){  // 初始化最大 AABB 数量为 导数的系数长度 * 维度 +2
                Idx max_length=derivatives->dimensional*derivatives->points_length+2;
                monotonic_aabbs.nodes=new Geometry::AABB_Node[max_length];
                for(i=0; i<max_length; ++i) monotonic_aabbs.nodes[i].init(dimensional);
            }

            // 采样生成 AABB
            var* temp_point=new var[dimensional];
            while(derivatives_root[i]<0 && i<length__derivatives_root) ++i;
            sample(monotonic_aabbs.nodes[0].aabb,0);
            while(derivatives_root[i]<1 && i<length__derivatives_root){
                sample(monotonic_aabbs.nodes[j].aabb,derivatives_root[i]);
                std::copy(monotonic_aabbs.nodes[j].aabb, monotonic_aabbs.nodes[j].aabb+dimensional, monotonic_aabbs.nodes[j-1].aabb+dimensional);
                ++i; ++j;
            }
            var *p=monotonic_aabbs.nodes[j-1].aabb+dimensional;
            sample(p,1);
            monotonic_aabbs.length=j;
        }


        void Bezier_Object::import_CtrlPoints(Points_Iterator& ctrl_points){
            if(coefficients && ctrl_points.points_length!=coefficients->points_length){
                delete coefficients;
                coefficients=0;
            }
            if(!coefficients){
                coefficients=new Points_Iterator__1DList(ctrl_points.dimensional,ctrl_points.points_length);
            }
            setup_BezierCoefficients(*coefficients,ctrl_points);
            giveUp_Cache();
        }

    }

    
}
/*!
 * @Description: 数与代数 运算相关
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-06-28 10:31:13
 */

#include "NML_Bezier.hpp"
#include "NML_Algebra.hpp"

namespace NML{
    namespace Bezier{
        var *&sample_Bezier__DeCasteljau(var *&out, Points_Iterator& points, var t){
            if(points.points_length>1){
                Points_Iterator__1DList new_points=Points_Iterator__1DList(points.dimensional,points.points_length-1);
                var td=1-t;
                for(int i=0;i>=0;--i){
                    var* temp_point__new=new_points[i];
                    var* temp_point__low=points[i];
                    var* temp_point__low1=points[i+1];
                    for(int j=0;j<points.dimensional;++j){
                        temp_point__new[j]=td*temp_point__low[j]+t*temp_point__low1[j];
                    }
                }
                sample_Bezier__DeCasteljau(out,new_points,t);
                new_points.free_Data();
                return out;
            }else{
                for(int i=0; i<points.dimensional;++i){
                    out[i]=points[0][i];
                }
                return out;
            }
        }

        
        Bezier_Calc_Matrix _BEZIER_CALC_MATRIX={&_BEZIER_CALC_MATRIX,0,new int[1]{1}};
        Bezier_Calc_Matrix* _last_load_bezier_calc_matrix=&_BEZIER_CALC_MATRIX;

        int* get_BezierCalcMatrix(Idx_Algebra n){
            Bezier_Calc_Matrix* ptr__move, *ptr__static;
            ptr__move=ptr__static = _last_load_bezier_calc_matrix;
            while (!(n==ptr__move->n||ptr__move->next==ptr__static)){
                ptr__move=ptr__move->next;
            }
            if(ptr__move->n==n){
                _last_load_bezier_calc_matrix=ptr__move;
                return ptr__move->data;
            }
            Link_List__Int_List *temp_pascals_triangle_line= Algebra::get_PascalsTriangleLine(n);
            Link_List__Int_List *move_pascals_triangle_line= &Algebra::_G_PASCALS_TRIANGLE;
            Idx matrix_n=n+1;
            Idx new_length=(matrix_n)*(matrix_n+1)/2;
            int *new_matrix_data=new int[new_length];

            Idx_Algebra idx_new_matrix=0,f=1;
            for(int i=0;i<=matrix_n;++i,move_pascals_triangle_line=move_pascals_triangle_line->next){
                f=1&i?-1:+1;
                for(int j=0;j<=i;++j,++idx_new_matrix){
                    new_matrix_data[idx_new_matrix] = move_pascals_triangle_line->data[j] * temp_pascals_triangle_line->data[i] * f;
                    f*=-1;
                }
            }
            Bezier_Calc_Matrix *new_bezier_calc_matrix=new Bezier_Calc_Matrix{ptr__static,n,new_matrix_data};
            ptr__move->next=new_bezier_calc_matrix;
            return new_matrix_data;
        }


        Points_Iterator& calc_BezierCoefficients(Points_Iterator& out, Points_Iterator& points){
            const Idx n=out.points_length-1;
            Idx_Algebra &dimensional=out.dimensional;
            int* _bezier_calc_matrix=get_BezierCalcMatrix(n);
            var* editing_target;
            var *temp=new var[dimensional];
            Idx i,j,idx_m=0;
            for(i=0;i<=n;++i){
                var* cnm=points[i];
                editing_target=out[i];
                std::fill_n(temp,dimensional,0);
                for(j=0;j<=i;++j,++idx_m){
                    var *point=points[j];
                    for(Idx_Algebra d=0;d<dimensional;++d){
                        temp[d]+=_bezier_calc_matrix[idx_m]*point[d];
                    }
                }
                std::copy(temp,temp+dimensional,editing_target);
            }
            delete temp;
            return out;
        }
        

        var*& sample_Bezier__Coefficients(var *&out, Points_Iterator& coefficients, var t){
            Idx_Algebra &dimensional=coefficients.dimensional;
            std::fill_n(out,dimensional,0);
            var temp;
            for(Idx i=0;i<coefficients.points_length;++i){
                var* line=coefficients[i];
                temp=pow(t,i);
                for(Idx_Algebra d=0;d<dimensional;++d){
                    out[d]+=temp*line[d];
                }
            }
            return out;
        }


        var*& calc_CutBezierMatrixQ(var*& out, Idx_Algebra n, var t){
            if(Algebra::_last_calc_pascals_triangle->n<n){
                Algebra::_calc_PascalsTriangle(n);
            }

            Idx_Algebra u,v;
            Idx index=0;
            // Init matrix of pascals triangle
            Link_List__Int_List *pascals_line = Algebra::get_PascalsTriangleLine(0);
            for(v=0;v<=n;++v){
                for(u=0;u<=pascals_line->n;++u,++index){
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
            for(u=1;u<=n;++u,temp*=t){
                index_uv+=u+1;
                index=index_uv;
                for(v=u;v<=n;++v,index+=v){
                    out[index]*=temp;
                }
            }
            
            // 1
            // d    1
            // dd   d    1
            // ddd  dd   d    1
            temp=d;
            index_uv=0;
            for(v=1;v<=n;++v,temp*=d){
                index_uv+=v;
                index=index_uv;
                for(u=v;u<=n;++u,index+=u+1){
                    out[index]*=temp;
                }
            }

            return out;
        }


        void cut_Bezier__ByMatrix(Points_Iterator& out0, Points_Iterator& out1, Points_Iterator& points, var*& cut_matrix_q){
            cut_Bezier__ByMatrix__p0pt(out0,points,cut_matrix_q);
            cut_Bezier__ByMatrix__ptp1(out1,points,cut_matrix_q);
        }

        
        Points_Iterator& cut_Bezier__ByMatrix__p0pt(Points_Iterator& out, Points_Iterator& points, var*& cut_matrix_q){
            Idx_Algebra &dimensional=points.dimensional;
            Idx index_m=1;
            var *calcing_target=out[0],*point;
            std::copy(points[0],points[0]+dimensional,calcing_target);
            
            for(Idx i=1;i<points.points_length;++i){
                calcing_target=out[i];
                std::fill_n(calcing_target,dimensional,0);
                for(Idx j=0;j<=i;++j,++index_m){
                    point=points[j];
                    for(Idx_Algebra d=0;d<dimensional;++d){
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
            var *calcing_target=out[n],*point;
            std::copy(points[n],points[n]+dimensional,calcing_target);
            
            for(Idx i=0,ii=length;i<n;++i,--ii){
                calcing_target=out[i];
                std::fill_n(calcing_target,dimensional,0);
                index_line-=ii;
                index_m=index_line;
                for(Idx j=i;j<length;++j,++index_m){
                    point=points[j];
                    for(Idx_Algebra d=0;d<dimensional;++d){
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
            for(Idx i=0;i<length;++i,++index_m){
                std::copy(coefficients[i],coefficients[i]+dimensional,temp);
                for(var j=0;j<i;++j,++index_m){
                    calcing_tgt=out[j];
                    for(Idx_Algebra d=0;d<dimensional;++d){
                        temp[d]-=calcing_tgt[d]*m[index_m];
                    }
                }
                var *calcing_tgt=out[i];
                for(Idx_Algebra d=0;d<dimensional;++d){
                    calcing_tgt[d]=temp[d]/m[index_m];
                }
            }
            return out;
        }

        const var BEZIER_TO_CYCLES_K__1D4=0.551784777779014;
    }
}
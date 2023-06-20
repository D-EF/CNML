/*!
 * @Description: 数与代数 运算相关
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-06-19 20:29:41
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

        
        Bezier_Clac_Matrix _BEZIER_CLAC_MATRIX={&_BEZIER_CLAC_MATRIX,0,new int[1]{1}};
        Bezier_Clac_Matrix* _last_load_bezier_clac_matrix=&_BEZIER_CLAC_MATRIX;

        int* get_BezierClacMatrix(Idx_Algebra n){
            Bezier_Clac_Matrix* ptr__move, *ptr__static;
            ptr__move=ptr__static = _last_load_bezier_clac_matrix;
            while (!(n==ptr__move->n||ptr__move->next==ptr__static)){
                ptr__move=ptr__move->next;
            }
            if(ptr__move->n==n){
                _last_load_bezier_clac_matrix=ptr__move;
                return ptr__move->data;
            }
            Link_List__Int_List *temp_pascals_triangle_line= Algebra::get_PascalsTriangleLine(n);
            Link_List__Int_List *move_pascals_triangle_line= &Algebra::_G_PASCALS_TRIANGLE;
            Idx matrix_n=n+1;
            Idx new_length=(matrix_n)*(matrix_n+1)/2;
            int *new_matrix_data=new int[new_length];

            Idx_Algebra idx_new_matrix=0,f=1;
            for(int i=0;i<=matrix_n;++i,move_pascals_triangle_line=move_pascals_triangle_line->next){
                for(int j=0;j<=i;++j,++idx_new_matrix){
                    new_matrix_data[idx_new_matrix] = move_pascals_triangle_line->data[j] * temp_pascals_triangle_line->data[i] * f;
                    f*=-1;
                }
            }
            Bezier_Clac_Matrix *new_bezier_clac_matrix=new Bezier_Clac_Matrix{ptr__static,n,new_matrix_data};
            ptr__move->next=new_bezier_clac_matrix;
            return new_matrix_data;
        }


        Points_Iterator& clac_BezierCoefficients(Points_Iterator& out, Points_Iterator& points);
        var*& sample_Bezier__Coefficients(var *&out, Points_Iterator& coefficients);
        var*& setup_Matrix__CutBezierMatrixQ(var*& out, Idx_Algebra n, var t);
        Points_Iterator& calc_BezierCtrlPoints__Coefficients(Points_Iterator& out, Points_Iterator& coefficients);

        
    }
}
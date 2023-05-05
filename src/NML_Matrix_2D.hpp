#ifndef __NML_MATRIX_2D__
#define __NML_MATRIX_2D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_2D{
        
        // open * setup * open
            /**
             * @brief 写入矩阵数据
             * @param out    操作对象
             * @param a      2d线性变换矩阵 参数 mxx
             * @param b      2d线性变换矩阵 参数 mxy
             * @param c      2d线性变换矩阵 参数 myx
             * @param d      2d线性变换矩阵 参数 myy
             * @param e      x 方向平移量
             * @param f      y 方向平移量
             */
            var*& setup_Matrix2D(var*& out, var a, var b, var c, var d, var e, var f);

            /**
             * @brief Set the up Translate matrix 平移矩阵
             * @param out    输出对象
             * @param tx     x方向平移量
             * @param ty     y方向平移量
             * @return 修改并返回 out
             */
            inline var*& setup_Translate(var*& out, var translate_x, var translate_y=0){
                return setup_Matrix2D(out,
                    1,             0,
                    0,             1,
                    translate_x,   translate_y
                );
            }

            /**
             * @brief Set the up Scale matrix 缩放矩阵
             * @param out        输出对象
             * @param scale_x    x方向缩放比
             * @param scale_y    y方向缩放比
             * @return 修改并返回 out
             */
            var*& setup_Scale(var*& out,var scale_x, var scale_y){
                return setup_Matrix2D(out,
                    scale_x,   0,
                    0,         scale_y,
                    0,         0
                );
            }
            inline var*& setup_Scale(var*& out,var scale_value){return setup_Scale(out,scale_value,scale_value);}

            /**
             * @brief Set the up Rotate matrix 旋转矩阵
             * @param out      输出对象
             * @param theta    旋转弧度(顺时针)
             * @return 修改并返回 out
             */
            inline var*& setup_Rotate(var*& out, var theta){
                var c=cos(theta),s=sin(theta);
                return setup_Matrix2D(out,
                     c,    s,
                    -s,    c,
                     0,    0
                );
            }

            /**
             * @brief Set the up Horizontal matrix 镜像矩阵
             * @param out           输出对象
             * @param normal_x      对称轴的法线 x 坐标
             * @param normal_y      对称轴的法线 y 坐标
             * @return 修改并返回 out
             */
            inline var*& setup_Horizontal(var*& out, var normal_x, var normal_y){
                return setup_Matrix2D(out,
                    1-2*normal_x*normal_x ,   -2*normal_x*normal_y,
                    -2*normal_x*normal_y  ,   1-2*normal_y*normal_y,
                    0,                        0
                );
            }

            /**
             * @brief Set the up Shear matrix 切变矩阵
             * @param out       输出对象
             * @param axis_x    切变轴的方向
             * @param axis_y    切变轴的方向
             * @param k         切变系数k
             * @return 修改并返回 out
             */
            inline var*& setup_Shear(var*& out,var axis_x, var axis_y, var k){
                return setup_Matrix2D(out,
                    1,          k*axis_x,
                    k*axis_y,   1,
                    0,          0
                );
            }
            
        // end  * setup * end 
        

        // open * transform * open
            inline var*& transform_2DMatrix(var*& mat, var app_mxx, var app_myx, var app_mxy, var app_myy, var app_tx, var app_ty){  
                return setup_Matrix2D(mat,
                    mat[mxx]*app_mxx + mat[mxy]*app_myx,          mat[mxx]*app_mxy + mat[mxy]*app_myy,
                    mat[myx]*app_mxx + mat[myy]*app_myx,          mat[myx]*app_mxy + mat[myy]*app_myy,
                    mat[tx]*app_mxx + mat[ty]*app_myx + app_tx,   mat[ty]*app_mxy + mat[ty]*app_myy + app_ty
                );
            }
            inline var*& transform_2DMatrix (var*& mat, var*& mat_app){
                return transform_2DMatrix(mat,
                    mat_app[mxx],   mat_app[myx],
                    mat_app[mxy],   mat_app[myy],
                    mat_app[tx],    mat_app[ty]
                );
            }
            
            /**
             * @brief transform matrix Translate 矩阵平移变换
             * @param out    输出对象
             * @param tx     x方向平移量
             * @param ty     y方向平移量
             * @return 修改并返回 out
             */
            inline var*& transform_Translate(var*& out, var translate_x, var translate_y=0){
                out[tx]+=translate_x;
                out[ty]+=translate_y;
                return out;
            }

            /**
             * @brief transform matrix Scale 矩阵缩放变换
             * @param out        输出对象
             * @param scale_x    x方向缩放比
             * @param scale_y    y方向缩放比
             * @return 修改并返回 out
             */
            inline var*& transform_Scale(var*& out,var scale_x, var scale_y){
                out[mxx]*=scale_x;   out[mxy]*=scale_y;
                out[myx]*=scale_x;   out[myy]*=scale_y;
                out[tx] *=scale_x;   out[ty] *=scale_y;
                return out;
            }
            inline var*& transform_Scale(var*& out,var scale_value){return transform_Scale(out,scale_value,scale_value);}

            /**
             * @brief transform matrix Rotate 矩阵旋转变换
             * @param out      输出对象
             * @param theta    旋转弧度(顺时针)
             * @return 修改并返回 out
             */
            var*& transform_Rotate(var*& out, var theta){
                // todo
                return out;
            }

            /**
             * @brief transform matrix Horizontal 镜像矩阵 矩阵变换
             * @param out           输出对象
             * @param normal_x      对称轴的法线
             * @param normal_y      对称轴的法线
             * @return 修改并返回 out
             */
            var*& transform_Horizontal(var*& out, var normal_x, var normal_y);

            /**
             * @brief transform matrix Shear 切变矩阵 矩阵变换
             * @param out       输出对象
             * @param axis_x    切变轴的方向
             * @param axis_y    切变轴的方向
             * @param k         切变系数k
             * @return 修改并返回 out
             */
            var*& transform_Shear(var*& out,var axis_x, var axis_y, var k);

        // end  * transform * end 
    }
}

#endif
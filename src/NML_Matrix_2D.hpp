#ifndef __NML_MATRIX_2D__
#define __NML_MATRIX_2D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_2D{
        
        // mij 表示 i行, j列 (mvu);   tx,ty 表示 x,y 齐次坐标;
        // open * 2*3 or 3*3 矩阵算法下标定义 * open
            
            /** 3*3矩阵 的对应下标常量 */
            #ifdef __NML_MATRIX_2D__USING_2X3__
            // 2*3
                const int
                    w  =2,   h  =3,
                    mxx=0,   mxy=1,
                    myx=2,   myy=3,
                    tx =4,   ty =5;

                inline var*& setup_Matrix2D__Init(var*& out){
                    out[0]=1;   out[1]=0;
                    out[2]=0;   out[3]=1;
                    out[4]=0;   out[5]=0;
                    return out;
                }
            #else
            // 3*3
                const int
                    w  =3,   h  =3,
                    mxx=0,   mxy=1,   mx_null=2,
                    myx=3,   myy=4,   my_null=5,
                    tx =6,   ty =7,   mi_full=8;
                    
                inline var*& setup_Matrix2D__Init(var*& out){
                    out[0]=1;   out[1]=0;   out[2]=0;
                    out[3]=0;   out[4]=1;   out[5]=0;
                    out[6]=0;   out[7]=0;   out[8]=1;
                    return out;
                }
            #endif

        // end  * 2*3 or 3*3 矩阵算法下标定义 * end 
        
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
            inline var*& setup_Matrix2D(var*& out, var a, var b, var c, var d, var e, var f){
                #ifndef __NML_MATRIX_2D__USING_2X3__
                    out[mx_null]=0;
                    out[my_null]=0;
                    out[mi_full]=1;
                #endif
                out[mxx]=a;   out[mxy]=b;
                out[myx]=c;   out[myy]=d;
                out[tx] =e;   out[ty] =f;
                return out;
            }

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
        
        // todo
            var*& transform_2DMatrix (var*& mat, var*& mat_right){
                return setup_Matrix2D(mat,
                    mat[mxx]*mat_right[mxx]+mat[mxy]*mat_right[myx],   mat[mxx]*mat_right[mxy]+mat[mxy]*mat_right[myy],
                    mat[myx]*mat_right[mxx]+mat[myy]*mat_right[myx],   mat[myx]*mat_right[mxy]+mat[myy]*mat_right[myy],
                    mat[myx]*mat_right[mxx]+mat[myy]*mat_right[myx],   mat[myx]*mat_right[mxy]+mat[myy]*mat_right[myy]
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
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-19 15:47:55
 * @FilePath: \CNML\src\NML_Primitives_2D.hpp
 * @Description: 2D 3D 矩阵变换控制
 * @
 * @Copyright (c) 2023 by darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NML_TRANSFORM_ACTION__
#define __NML_TRANSFORM_ACTION__

#include "NML.hpp"
#include "NML_Matrix_2D.hpp"

namespace NML{
    namespace Matrix{
        
        // 矩阵变换控制器
        
        /** @brief 矩阵变换过程的一次动作 */
        class Transform_Matrix_Action{
            public:
            /** 
             * @brief 对矩阵 进行变换 
             * @param out 修改的对象
             * @return 修改并输出 out
             */
            virtual var*& transform(var*& out) = 0;
        };

        /** @brief 矩阵变换的过程 */
        typedef struct Transform_Matrix_Flow{
            /** @brief 当前要进行的矩阵变换操作 */
            Transform_Matrix_Action *act;
            /** @brief 下一次进行的矩阵变换 */
            Transform_Matrix_Flow *next;
        } Transform_Matrix_Flow;

        /** 
         * @brief 实行矩阵变换
         * 
         * @param out  修改的对象
         * @param act_flow_entrance  矩阵变换过程的入口
         * @return 修改并返回 out
         */
        var*& transform_Matrix(var*& out, Transform_Matrix_Flow*& act_flow_entrance);


        /** @brief 2D 变换操作 */
        namespace Transform_Action__2D{
            class Init_Matrix2D : public Matrix::Transform_Matrix_Action{ public: var*& transform(var*& out){ return Matrix_2D::setup_Matrix2D(out, 1, 0, 0, 1, 0, 0); } };

            /** @brief 平移操作 */
            class Translate_Action : public Matrix::Transform_Matrix_Action{ 
                public: 
                    var translate_x; var translate_y;
                    Translate_Action(var translate_x=0, var translate_y=0):translate_x(translate_x), translate_y(translate_y){}
                    var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Translate (out, translate_x, translate_y); }
            };

            /** @brief 缩放操作 */
            class Scale_Action : public Matrix::Transform_Matrix_Action{ 
                public: 
                    var scale_x; var scale_y;
                    Scale_Action(var scale_x=1, var scale_y=1):scale_x(scale_x), scale_y(scale_y){}
                    var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Scale (out, scale_x, scale_y); }
            };

            /** @brief 旋转操作 */
            class Rotate_Action : public Matrix::Transform_Matrix_Action{ 
                public: 
                    var theta;
                    Rotate_Action(var theta=0):theta(theta){}
                    var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Rotate (out, theta); }
            };

            /** @brief 镜像操作 */
            class Reflect_Action : public Matrix::Transform_Matrix_Action{ 
                public: 
                    var normal_x; var normal_y;
                    Reflect_Action(var normal_x=1, var normal_y=0):normal_x(normal_x), normal_y(normal_y){}
                    var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Reflect (out, normal_x, normal_y); }
            };

            /** @brief 切变操作 */
            class Shear_Action : public Matrix::Transform_Matrix_Action{ 
                public: 
                    var axis_x; var axis_y; var k;
                    Shear_Action(var axis_x, var axis_y, var k):axis_x(axis_x), axis_y(axis_y), k(k){}
                    var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Shear (out, axis_x, axis_y, k); }
            };
        }
    }
}

#endif
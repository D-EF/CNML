/*!
 * @Description: 2D 图元 相关内容
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-07-05 03:44:16
 */

#ifndef __NML_PRIMITIVES_2D__
#define __NML_PRIMITIVES_2D__

#include "NML.hpp"
#include "NML_Matrix_2D.hpp"

namespace NML{
    /**
     * @brief 2D 图元相关
     */
    namespace Primitives_2D{
        
        class Init_Matrix2D : public Matrix::Transform_Matrix_Action{ public: var*& transform(var*& out){ return Matrix_2D::setup_Matrix2D(out,1,0,0,1,0,0); } };

        class Translate_Matrix2D : public Matrix::Transform_Matrix_Action{ 
            public: 
                var translate_x; var translate_y;
                Translate_Matrix2D(var translate_x,var translate_y=0):translate_x(translate_x),translate_y(translate_y){}
                var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Translate (out, translate_x, translate_y); }
        };

        class Scale_Matrix2D : public Matrix::Transform_Matrix_Action{ 
            public: 
                var scale_x; var scale_y;
                var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Scale (out, scale_x, scale_y); }
        };

        class Rotate_Matrix2D : public Matrix::Transform_Matrix_Action{ 
            public: 
                var theta;
                var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Rotate (out, theta); }
        };

        class Reflect_Matrix2D : public Matrix::Transform_Matrix_Action{ 
            public: 
                var normal_x; var normal_y;
                var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Reflect (out, normal_x, normal_y); }
        };

        class Shear_Matrix2D : public Matrix::Transform_Matrix_Action{ 
            public: 
                var axis_x; var axis_y; var k;
                var*& transform(var*& out){ return Matrix_2D::transform_Matrix2D__Shear (out, axis_x, axis_y, k); }
        };

        /** @brief 一条线段图元数据 */
        typedef struct Line_Data {
            /** @brief 起点坐标 */
            var x0, y0; 
            /** @brief 终点坐标 */
            var x1, y1;
        } Line_Data;

        /** @brief 矩形图元数据 */
        typedef struct Rect_Data {
            /** @brief 锚点的 x 坐标 */
            var x;
            /** @brief 锚点的 y 坐标 */
            var y; 
            /** @brief 宽度 ( x 方向偏移量 ) */
            var w; 
            /** @brief 高度 ( y 方向偏移量 ) */
            var h;
        } Rect_Data;

        /** @brief 圆弧 图元数据 */
        typedef struct Arc_Data {
            /** @brief 圆心 x 坐标 */
            var cx;
            /** @brief 圆心 y 坐标 */
            var cy;
            /** @brief 半径 */
            var r;
            /** @brief 弧线的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_0;
            /** @brief 弧线的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_1;
        } Arc_Data;

        /** @brief 椭圆弧线 图元数据 */
        typedef struct Ellipse_Arc_Data {
            /** @brief 圆心 x 坐标 */
            var cx;
            /** @brief 圆心 y 坐标 */
            var cy;
            /** @brief 主要半径计算参数 */
            var r;
            /** @brief 附加的半径计算参数 */
            var r_ex;

            var &rx=r;
            var &ry=r_ex;
            
            var &ry=r_ex;
            var &ry=r_ex;
            
            /** @brief 弧线的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_0;
            /** @brief 弧线的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_1;
            /** @brief 旋转偏移量 */
            var rotate;
        } Ellipse_Arc_Data;


        // todo
        class Primitives_2D{

            /** 
             * @brief 局部坐标 to 世界坐标 的 变换矩阵
             */
            var *transform_matrix;

            /** 
             * @brief 缓存的周长
             */
            var _girth;

            /** 
             * @brief 缓存的 aabb 数据; min={x0, y0}; max={x1, y1};
             */
            Line_Data aabb;


            /**
             * @brief 表示缓存的 aabb 是否可用
             */
            bool had_aabb;

            /**
             * @brief 表示缓存的 周长 是否可用
             */
            bool had_girth;



            /**
             * @brief 淘汰缓存值, 使缓存数据标志置否
             */
            void giveUp_Cache(){
                had_aabb    = false;
                had_girth   = false;
            }


            /** 
             * @brief 获取周长
             * @return 缓存可用则返回缓存值, 不可用则重新计算
             */
            var get_Girth(){
                if(!had_girth){
                    _girth= calc_Girth();
                    had_girth = true;
                }
                return _girth;
            }

            
            /** 
             * @brief 获取局部坐标的 aabb 包围盒数据
             * @return 缓存可用则返回缓存值, 不可用则重新计算
             */
            Line_Data get_LocalAABB(){
                if(!had_girth){
                    aabb = calc_LocalAABB();
                    had_aabb = true;
                }
                return aabb;
            }


            /** 
             * @brief 计算周长
             * @return 返回计算周长
             */
            virtual var calc_Girth() = 0;

            /** 
             * @brief 计算 aabb 包围盒
             * @return 返回计算的aabb盒子
             */
            virtual Line_Data calc_LocalAABB() = 0;
            
            /** 
             * @brief 加载多边形
             * @param out   数据输出对象: 多边形的顶点的访问器, 采样次数 = Points_Iterator->points_length
             * @return 修改 out 并返回
             */
            virtual Points_Iterator*& load_Polyon(Points_Iterator *&out) = 0;


        };

    }
}

#endif
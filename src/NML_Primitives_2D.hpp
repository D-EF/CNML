/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-09 14:52:01
 * @FilePath: \cnml\src\NML_Primitives_2D.hpp
 * @Description: 2D 图元 相关内容
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
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
        typedef struct Line_Data_2D {
            /** @brief 起点坐标 */
            var x0, y0; 
            /** @brief 终点坐标 */
            var x1, y1;
        } Line_Data_2D;
        
        
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
            /** @brief 局部水平方向半径 */
            var rx;
            /** @brief 局部垂直方向半径 */
            var ry;
            /** @brief 弧线的端点 0 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_0;
            /** @brief 弧线的端点 1 相对圆心的向量 与 x 正方向 的夹角弧度 */
            var theta_1;
            /** @brief 旋转偏移量 */
            var rotate;
        } Ellipse_Arc_Data;


        /** @brief AABB 轴对齐包围盒 min={x0, y0}; max={x1, y1}; */
        typedef Line_Data_2D AABB_2D;



        /**
         * @brief 2D 图元 基类
         */
        class Primitive_2D{
            protected:
                /** 自动闭合路径; 0:不自动闭合, 1:直线段回到起点, 2:圆心连接起点和终点(仅适用于弧和椭圆弧线) 或 贝塞尔曲线使用控制点演化曲线闭合  */
                char _auto_close=0;

                /** @brief 缓存的图元生成的 拟合图元的线段路径, _line_path.points_length 将作为采样次数 */
                Points_Iterator *_line_path=0;

                /** @brief 缓存的周长 */
                var _girth=-1;

                /** @brief 缓存的 aabb 数据; */
                AABB_2D _loc_aabb={0,0,0,0};

                /** @brief 表示缓存的 aabb 是否可用 */
                bool _had__loc_aabb=false;

                /** @brief 表示缓存的 周长 是否可用 */
                bool _had__girth=false;

                /** @brief 表示缓存的 拟合图元的线段路径 是否可用 */
                bool _had__line_path=false;

                /** @brief 表示缓存的 三角面 是否可用 */
                bool _had__triangles_mesh=false;
                // todo 三角面


            public:

                Primitive_2D(){}

                /** @brief 局部坐标 to 世界坐标 的 变换矩阵 */
                var *transform_matrix;


                /** @brief 淘汰所有缓存值, 使缓存数据标志置否 */
                void giveUp_AllCache(){
                    _had__loc_aabb          =false;
                    _had__girth             =false;
                    _had__line_path         =false;
                    _had__triangles_mesh    =false;
                }


                /** 
                 * @brief 获取周长
                 * @return 返回获取周长; 缓存可用则返回缓存值, 不可用则重新计算
                 */
                var get_Girth();
                
                /** 
                 * @brief 获取局部坐标的 AABB 包围盒数据
                 * @return 返回获取局部坐标的 AABB; 缓存可用则返回缓存值, 不可用则重新计算
                 */
                AABB_2D get_LocalAABB();

                /** 
                 * @brief 获取 拟合图元的线段路径
                 */
                Points_Iterator*& get_LinePath();


                /** 
                 * @brief 计算周长
                 * @return 返回计算周长
                 */
                virtual var calc_Girth() = 0;

                /** 
                 * @brief 计算局部坐标系的 aabb 包围盒
                 * @return 返回计算的aabb盒
                 */
                virtual AABB_2D calc_LocalAABB() = 0;
                
                /** 
                 * @brief 计算 拟合图元的线段路径, 修改成员变量 _line_path 的内容
                 * @return 返回成员变量 _line_path 的引用
                 */
                virtual Points_Iterator*& load_LinePath() = 0;

                /** 
                 * @brief 设置生成 拟合图元的线段路径时的采样次数, 值越高表示精度越高
                 * @param size 精度参数
                 */
                virtual Idx set_SampleSize(Idx size)=0;
            
                /** 
                 * @brief 检查是否闭合路径
                 * @return 返回 true:闭合路径; false:非闭合路径
                 */
                virtual bool check_Close() = 0;

        };



        
        class Primitive_2D__Rect: public Primitive_2D{
            Rect_Data *data;

            /** 计算矩形周长 =2*(长+宽) */
            var calc_Girth(){return data->w+data->w+data->h+data->h;}
            
            /** 矩形路径始终为闭合路径 */
            bool check_Close(){return true;}
            

            /** 
             * 无用的函数, 矩形采样始终为四次采样
             */
            Idx set_SampleSize(){
                // not thing
                return 4;
            }
        };
        
        
        class Primitive_2D__Arc: public Primitive_2D{
            Arc_Data *data;
            
            /**
             * @brief 设置生成 拟合弧形图元的线段路径时的采样次数, 值越高表示精度越高
             * @param size size+1 将作为采样次数 (多出的点用于自动闭合路径)
             */
            Idx set_SampleSize(Idx size){
                _had__line_path=false;
                _line_path->free_Data();
                _line_path->install_Data(2,size+1);
                return _line_path->points_length;
            }
        };
        
        
        class Primitive_2D__Ellipse_Arc: public Primitive_2D{
            Ellipse_Arc_Data *data;
            
            /**
             * @brief 设置生成 拟合椭圆弧线图元的线段路径时的采样次数, 值越高表示精度越高
             * @param size size+1 将作为采样次数 (多出的点用于自动闭合路径)
             */
            Idx set_SampleSize(Idx size){
                _had__line_path=false;
                _line_path->free_Data();
                _line_path->install_Data(2,size+1);
                return _line_path->points_length;
            }
        };
        
        
        class Primitive_2D__Line_Path: public Primitive_2D{
            Points_Iterator *data;
            
            /** 
             * 无用的函数, 线段路径图元直接使用自身的数据作为输出的拟合线段路径
             */
            Idx set_SampleSize(){
                // not thing
                return data->points_length;
            }
        };
        
        
        class Primitive_2D__Bezier_Path: public Primitive_2D{
            /** 贝塞尔曲线数据; 曲线级别 = data.dimensional/2,  曲线数量 = data.points_length-1; 锚点=(data[i][0],data[i][1]) 控制点=锚点+(data[i][2*j],data[i][2*j+1]) */
            Points_Iterator *data;
            
            /**
             * @brief 设置生成 拟合贝塞尔曲线组图元的线段路径时的采样次数, 值越高表示精度越高
             * @param size size*data.points_length 将作为采样次数 (多出的点用于自动闭合路径)
             */
            Idx set_SampleSize(Idx size){
                _had__line_path=false;
                _line_path->free_Data();
                _line_path->install_Data(2,size*data->points_length);
                return _line_path->points_length;
            }
        };

    }
}

#endif
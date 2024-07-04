/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-07-01 14:24:36
 * @FilePath: \CNML\src\Geometry_2D\NML_Geometry_2D_Primitive.hpp
 * @Description: 2D 图元 相关内容
 */

#ifndef __NML_GEOMETRY_2D_PRIMITIVE__
#define __NML_GEOMETRY_2D_PRIMITIVE__

#include "NML.hpp"
#include "./NML_Geometry_2D.hpp"
#include "./NML_Matrix_2D.hpp"

namespace NML{
    namespace Geometry_2D{
        /**
         * @brief 2D 图元
         */
        namespace Primitive_2D{             

            /** @brief 2D 图元基类 */
            class Primitive_2D{
                public:
                /** @brief 局部坐标 to 世界坐标 的 变换矩阵 */
                var *transform_matrix;

                /** @brief 缓存的周长 */
                var _girth;

                /** @brief 缓存的 aabb 数据; */
                AABB_2D loc_aabb;

                /** @brief 缓存的图元生成的多边形, points_length 将作为采样次数 */
                Points_Iterator *polygon;

                /** 自动闭合图元路径, 在不同类型图元内可能有不同处理方式
                 * @p 矩形: 常闭合的
                 * @p 弧形: [ 0:不自动闭合, 1:使用弦闭合, 2:作为整圆 ]
                 */
                char auto_close;

                /** @brief 表示缓存的 aabb 是否可用 */
                bool had__loc_aabb;

                /** @brief 表示缓存的 周长 是否可用 */
                bool had__girth;

                /** @brief 表示缓存的 多边形 是否可用 */
                bool had__polygon;

                /** @brief 表示缓存的 三角面 是否可用 */
                bool had__triangles_mesh;

                /** @brief 采样精度种子, 不同派生类将以此生成不同的实际精度参数 */
                Idx _sample_size_seed;

                /**
                 * @brief 默认构造函数
                 * @param sample_size_seed 采样精度
                 */
                Primitive_2D( Idx sample_size_seed = __DEFINE_SAMPLE_SIZE_SEED__ ):
                    _sample_size_seed(sample_size_seed),
                    transform_matrix(Matrix::create_Matrix__Identity(Matrix_2D::m2d_w, Matrix_2D::m2d_h)),
                    auto_close(0),
                    polygon(0){
                    giveUp_AllCache();
                }

                /** @brief 淘汰所有缓存值, 使缓存数据标志置否 */
                void giveUp_AllCache(){
                    had__loc_aabb         = false;
                    had__girth            = false;
                    had__polygon          = false;
                    had__triangles_mesh   = false;
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
                 * @brief 判断点是否在图元内部
                 * @param point 局部坐标系中点的坐标
                 * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
                 */
                inline char check_Inside__Loc(Point_2D& point){ return this->check_Inside__Local__P(point);}
                
                /**
                 * @brief 判断点是否在图元内部
                 * @param point 局部坐标系中点的 x, y 坐标
                 * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
                 */
                inline char check_Inside__Loc(var*& point){Point_2D* _p=(Point_2D*)point; return this->check_Inside__Local__P(*_p);}
                
                /**
                 * @brief 判断点是否在图元内部
                 * @param point 局部坐标系中点的坐标
                 * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
                 */
                inline char check_Inside__Loc(var x, var y){Point_2D _p={x,y}; return this->check_Inside__Local__P(_p);}
                
                /** 
                 * @brief 获取 拟合图元的线段路径
                 */
                Points_Iterator& get_Polygon();


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
                 * @brief 计算 拟合图元的线段路径, 修改成员变量 polygon 的内容
                 * @return 返回成员变量 polygon 的引用
                 */
                virtual Points_Iterator& load_Polygon() = 0;

                /** 
                 * @brief 设置生成 拟合图元的线段路径时的采样次数, 值越高表示精度越高
                 * @param size 精度参数
                 * @return 正常则返回实际采样次数, 如果出错将返回0
                 */
                virtual Idx set_SampleSizeSeed(Idx size = __DEFINE_SAMPLE_SIZE_SEED__)=0;

                
                /** 
                 * @brief 设置生成 拟合图元的线段路径时的采样次数, 值越高表示精度越高
                 * @param size 精度参数
                 * @return 正常则返回实际采样次数, 如果出错将返回0
                 */
                virtual Idx get_SampleSize()=0;
            
            
                /** 
                 * @brief 检查是否闭合路径
                 * @return 返回 true:闭合路径; false:非闭合路径
                 */
                virtual bool check_Close() = 0;

                /** 
                 * @brief 判断点是否在图元内部 ( 继承用 )
                 * @param point 局部坐标系中点的坐标
                 * @return 返回 {0, 1, 2} 表示 [ 不在内部, 在内部, 在边上 ]; 如果图元为非闭合图元, 将始终返回0.
                 */
                virtual char check_Inside__Local__P(Point_2D point)=0;

            };



            /** 矩形 图元对象 */
            class Primitive_2D__Rect: public Primitive_2D{
                public:

                /** 图元数据内容 */
                Rect_Data *data;

                Primitive_2D__Rect(Rect_Data *data=0):data(data){}

                /** @brief 计算矩形周长 =2*(长+宽) */
                inline var calc_Girth(){return data->w+data->w+data->h+data->h;}
                
                /** 矩形路径始终为闭合路径 */
                inline bool check_Close(){return true;}
                
                /** 
                 * @brief 矩形采样始终为四次采样
                 * @return 始终返回 4
                 */
                inline Idx get_SampleSize(){return 4;}

                /** 
                 * @brief 矩形采样始终为四次采样
                 * @return 始终返回 4
                 */
                inline Idx set_SampleSizeSeed(Idx size=4){return _sample_size_seed=4;}

                inline AABB_2D calc_LocalAABB(){
                    normalize_RectData(*data);
                    return {
                        p0 : {data->x, data->y},
                        p1 : {data->x+data->w, data->y+data->h}
                    };
                }

                char check_Inside__Local__P(Point_2D& point);

                /**
                 * @brief 生成矩形的多边形代理
                 * @return 生成 [{min_x, min_y},{max_x, min_y},{max_x, max_y},{min_x, max_y},{min_x, min_y}] 数据，存放到缓存中
                 */
                Points_Iterator& load_Polygon();
            };
            
            
            // todo
            /** 弧形 图元对象, 旋转量大于整圆将认作为整圆 */
            class Primitive_2D__Arc: public Primitive_2D{
                /** @brief 椭圆的数据 */
                Arc_Data *data;
                /** @brief 椭圆的弧长, <0 表示未计算 */
                var arc_length;
                /** @brief 椭圆的弦长, <0 表示未计算 */
                var chord_length;

                Primitive_2D__Arc(Arc_Data *data=0):data(data),arc_length(-1),chord_length(-1){}

                /** 获取 弧形弧长 */
                var get_ArcLength();
                
                /** 获取 弧形弦长 */
                var get_ChordLength();
                
                /** 弧形是否闭合: 检查是弧形旋转量是否大于整圆 */
                inline bool check_Close(){return abs(data->theta_op-data->theta_ed)>CYCLES;}
                
                /** 获取局部坐标的弧形的弦信息(端点相对于圆心的位置)*/
                Line_2D get_local_chord();

                /** 计算局部坐标的弧形的弦信息(端点相对于圆心的位置)*/
                Line_2D calc_LocalChord();

                /** 局部坐标的弧形的弦信息(端点相对于圆心的位置)*/
                Line_2D loc_chord;

                /** loc_chord 是否可用*/
                bool had__loc_chord;

                Primitive_2D__Arc():had__loc_chord(false){}

                inline void giveUp_AllCache(){
                    had__loc_chord=false;
                    Primitive_2D::giveUp_AllCache();
                }

                /** @brief 计算弧形周长  */
                var calc_Girth();
                
                /** @brief 计算弧形弧长  */
                var calc_ArcLength();
                
                /** @brief 计算弧形弦长  */
                var calc_ChordLength();

                /**
                 * @brief 获取采样次数(多边形代理的可用长度)
                 * @return 采样精度种子 = 采样次数 
                 */
                inline Idx get_SampleSize(){return _sample_size_seed;}

                /**
                 * @brief 设置生成 拟合弧形图元的线段路径时的采样次数, 值越高表示精度越高
                 * @param size size 将作为采样次数
                 */
                inline Idx set_SampleSizeSeed(Idx size=4){
                    had__polygon=false;
                    polygon->free_Data();
                    polygon->install_Data(2, size);
                    return _sample_size_seed=size;
                }

                AABB_2D calc_LocalAABB();
            };

            // todo
            /** 椭圆弧线 图元对象, 旋转量大于整圆将认作为整圆 */
            class Primitive_2D__Ellipse_Arc: public Primitive_2D{
                /** @brief 椭圆的数据 */
                Ellipse_Arc_Data *data;
                /** @brief 椭圆的焦点 */
                Line_2D focus;
                /** @brief 椭圆的焦距 */
                var focal_length;
                /** @brief 椭圆的缩放比 */
                var scale_value;

                AABB_2D calc_LocalAABB();

                /**
                 * @brief 设置生成 拟合椭圆弧线图元的线段路径时的采样次数, 值越高表示精度越高
                 * @param size size+1 将作为最大采样次数 (多出的点用于自动闭合路径)
                 */
                Idx set_SampleSize(Idx size){
                    had__polygon=false;
                    polygon->free_Data();
                    polygon->install_Data(2, size+1);
                    return polygon->points_length;
                }
            };
            
            
            /** 多边形(线段组) 图元对象 */
            class Primitive_2D__Polygon: public Primitive_2D{
                Points_Iterator *data;
                
                /**
                 * @brief 设置生成多边形时的采样次数, 值越高表示精度越高
                 */
                Idx set_SampleSize(Idx size){
                    had__polygon=false;
                    polygon->free_Data();
                    polygon->install_Data(2, size);
                    return size;
                }
                
                /** 
                 * @brief 获取局部坐标的 AABB 包围盒数据
                 * @return 返回获取局部坐标的 AABB; 缓存可用则返回缓存值, 不可用则重新计算
                 */
                AABB_2D get_LocalAABB();

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
                 * @brief 计算多边形, 修改成员变量 polygon 的内容
                 * @return 返回成员变量 polygon 的引用
                 */
                virtual Points_Iterator& load_Polyon() = 0;

            };
            

        }
    }
}

#endif
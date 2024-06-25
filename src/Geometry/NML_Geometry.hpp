/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-04-15 08:37:42
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-04 17:17:49
 * @FilePath: \CNML\src\Geometry\NML_Geometry.hpp
 * @Description: 通用图形计算, 提供部分数据结构和算法, 不区分维度的通用内容
 */

#ifndef __NML_GEOMETRY__
#define __NML_GEOMETRY__

#include "NML.hpp"
#include "Link_Block/NML_Link_Block.hpp"
#include "Algebra/NML_Vector.hpp"

namespace NML{
    
    namespace Geometry{

        /**
         * @brief 计算点到降一维度的对象的距离
         * @param obj          低一维度的对象, 使用法向量+投影系数d
         * @param point        点
         * @param dimesional   世界的维度
         */
        inline var calc_Distance__Point_To_DimensionalityReduction(var* obj, var* point, Idx_Algebra dimesional){ return dot(point,obj,dimesional) - obj[dimesional]; }


        /**
         * aabb 节点 (用于曲线求交)
         */
        class AABB_Node{
            public:
            /** 采样用的 t 参数 */
            var op_t, ed_t;
            /** aabb 值 内容应为 {axis_i_A,..., axis_i_B,...}, 长度为 2*dimensional */
            var* aabb;
            /** 有多少个坐标轴 */
            Idx_Algebra dimensional;
            /** 派生的子 AABB */
            AABB_Node *child_0, *child_1;

            AABB_Node(){}

            void init(Idx_Algebra dimensional){
                if(aabb) delete aabb;
                aabb=new var[dimensional*2];
            }
            
            AABB_Node(Idx_Algebra dimensional):dimensional(dimensional),child_0(0),child_1(0){
                aabb = new var[dimensional*2];
            }

            ~AABB_Node(){
                delete child_0;
                delete child_1;
                delete aabb;
            }
        };

        /**
         * aabb 节点集合 (用于曲线求交)
         */
        typedef struct AABB_Nodes{
            AABB_Node* nodes;
            Idx length;
        } AABB_Nodes;

        /**
         * aabb配对
         */
        typedef struct AABB_Pair{
            /** 配对的两个 aabb */
            Geometry::AABB_Node *box_0, *box_1;
        } AABB_Pair;


        /**
         * @brief 计算直线段长度
         * @param point0 线段端点0
         * @param point1 线段端点1
         * @param dimensional 点的维度
         * @return 计算直线段长度并返回
         */
        var calc_LineDistance(var* point0, var* point1, Idx_Algebra dimensional);

        /**
         * @brief 计算直线段路径长度
         * @param line_path 路径点数据
         * @return 计算路径长度并返回
         */
        var calc_LinePathDistance(Points_Iterator& line_path);

        /**
         * @brief 计算直线段路径并生成对应的 LUT 显式查找表
         * @param line_path      路径点数据
         * @param out_distance_lut   输出的对应长度的 LUT, 数据长度应该和点的个数相等
         * @return 计算路径长度并返回
         */
        var calc_LinePathDistance(Points_Iterator& line_path, var*& out_distance_lut);

        /**
         * @brief 加载 AABB 的角
         * @param out  输出对象, 长度应为 dimensional
         * @param min  AABB 的最小值, 长度应为 dimensional
         * @param max  AABB 的最大值, 长度应为 dimensional
         * @param dimensional 计算多少个维度, 取值范围为 [0, sizeof(int)]
         * @param corner_index AABB 角的序号, 取值范围为 [0, 2^dimensional]; 
         * @return 修改并返回 out
         */
        var*& load_AABBCorner(var*& out, var*& min, var*& max, Idx_Algebra dimensional, int corner_index);
        
        
        /**
         * @brief 对 AABB 置空
         * @param min  AABB 的最小值, 将置为 +INFINITY
         * @param max  AABB 的最大值, 将置为 -INFINITY
         */
        inline void empty_AABB(var*& min, var*& max){min[0]=INFINITY; max[0]=-INFINITY;}


        /**
         * @brief 检查 AABB 是否为空 (当 min 中某值大于对应维度的 max 值 时表示当前 AABB 为空盒子)
         * @param min  AABB 的最小值, 长度应为 dimensional
         * @param max  AABB 的最大值, 长度应为 dimensional
         * @param dimensional 计算多少个维度
         * @return 返回 是否为空
         */
        bool check_AABBEmpty(var*& min, var*& max, Idx_Algebra dimensional);

        
        /**
         * @brief 检查 AABB 相交性
         * @param aabb_0           aabb 0
         * @param aabb_1           aabb 1
         * @return 返回 是否相交
         */
        bool check_Intersection__AABB(AABB_Node& aabb_0, AABB_Node& aabb_1);


        
        /**
         * @brief 检查 aabb 是否达到精度要求
         * @param box                 需要检查的 AABB
         * @param _tolerance          容差, 默认为 NML_TOLERANCE*10 , 当 sum(max) - sum(min) < _tolerance 表示精度达成
         * @return 返回交点的个数, 最多为初始化时 AABB 组长度的积; [ 0, (g_0.l-1)(g_1.l-1) ]
         */
        bool check_Tolerance__AABB(AABB_Node& box, var _tolerance=NML_TOLERANCE*10);


        /**
         * @brief 尝试派生 aabb 
         * @return 返回 正常派生/精度达成
         */
        template <typename CurvType_e>
        bool _refine_AABB(AABB_Node& box, var& temp, Idx& dimensional, Idx& i, Idx& l, var*& temp_point, CurvType_e& curve, var _tolerance=NML_TOLERANCE*10){
            if(box.child_1) return true;
            for(temp=0, i=0; i<l; ++i) temp += abs(box.aabb[i]-box.aabb[i+l]);
            if(_tolerance > temp){
                return false;
            }else{
                curve.sample(temp_point, (box.op_t+box.ed_t)*0.5);
                box.child_0=new AABB_Node(box);
                std::copy(temp_point, temp_point+dimensional, box.child_0->aabb);
                box.child_1=new AABB_Node(box);
                std::copy(temp_point, temp_point+dimensional, box.child_1->aabb+dimensional);
                return true;
            }
        }

        /**
         * @brief 曲线求交
         * @param out            输出目标, 输出交点在 curve_0 上的 t 参数; 长度应该为两个曲线的最大次数的积
         * @param curve_0        曲线控制对象, 应有成员函数 sample(var*& out, var t); 其中 out 为采样点坐标输出, t 为采样参数
         * @param curve_1        曲线控制对象, 应有成员函数 sample(var*& out, var t); 其中 out 为采样点坐标输出, t 为采样参数
         * @param aabb_group_0   曲线 0 的单调 AABB 组
         * @param aabb_group_1   曲线 1 的单调 AABB 组 
         * @param _tolerance     容差, 默认为 NML_TOLERANCE*10 , 当 sum(max) - sum(min) < _tolerance 表示精度达成
         * @return 返回交点的个数, 最多为初始化时 AABB 组长度的积; [ 0, (g_0.l-1)(g_1.l-1) ]
         */
        template <typename Curve_Type_0, typename Curve_Type_1>
        Idx calc_Intersection__curve_curve(
            var*&                   out, 
            Curve_Type_0&           curve_0, 
            Curve_Type_1&           curve_1, 
            Geometry::AABB_Nodes&   aabb_group_0, 
            Geometry::AABB_Nodes&   aabb_group_1,
            var                     _tolerance = NML_TOLERANCE*10
        ){
            using Pair = Link_Block::Link_Block_Ctrl<AABB_Pair>;
            
            Pair pair;
            AABB_Pair ex_pair[4];
            AABB_Node *box_0, *box_1;
            Idx i, j, rtn, dimensional=aabb_group_0.nodes[0].dimensional, l=dimensional/2;
            var temp=0;
            var *temp_point=new var[dimensional];
            bool flag__refine_0,flag__refine_1;

            // 初始化配对
            for(i=0; i<aabb_group_0.length; ++i){
                for(j=0; j<aabb_group_1.length; ++j){
                    pair.push_Item({ aabb_group_0.nodes+i, aabb_group_1.nodes+j });
                }
            }

            while(pair.used_length>0){
                box_0 = pair[pair.used_length].box_0;
                box_1 = pair[pair.used_length].box_1;
                pair.remove_EndItem();
                
                // 检查相交
                for(i=0; i<l; ++i) if(!check_Intersection__Range_Unordered(box_0->aabb[i], box_0->aabb[i+l], box_1->aabb[i], box_1->aabb[i+l]) ) break;
                
                if(i<l){
                    //相交, 派生 aabb
                    flag__refine_0 = _refine_AABB(box_0, temp, dimensional, i, l, temp_point, curve_0, _tolerance);
                    flag__refine_1 = _refine_AABB(box_1, temp, dimensional, i, l, temp_point, curve_1, _tolerance);
                    // 增加派生配对
                    if(flag__refine_0){
                        pair.push_Item({ box_0->child_0, box_1->child_0 });
                        pair.push_Item({ box_0->child_1, box_1->child_0 });
                        if(flag__refine_1){
                            pair.push_Item({ box_0->child_0, box_1->child_1 });
                            pair.push_Item({ box_0->child_1, box_1->child_1 });
                        }
                    }else if(flag__refine_1){
                        pair.push_Item({ box_0->child_0, box_1->child_0 });
                        pair.push_Item({ box_0->child_0, box_1->child_1 });
                    }else{
                        out[rtn] = box_0->op_t + box_0->ed_t;
                        ++rtn;
                    }
                }
                // 不相交, do nothing
            }
            return rtn;
        }
        // todo test

    }

}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-11-22 15:11:17
 * @FilePath: \cnml\src\NML_Vector.hpp
 * @Description: 基本向量操作
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef __NML_VECTOR__
#define __NML_VECTOR__

#include "NML.hpp"

namespace NML{
    /**
     * @brief 存放向量相关函数
     * 
     */
    namespace Vector{

        /**
         * @brief 判断某个向量是否为单位向量
         * 
         * @param length        向量数组长度
         * @param vec           数组表示的向量数据
         * @param _tolerance    容差 默认 1e-6
         * @return 返回是否为单位向量 
         */
        inline bool is_Unit(Idx_VM length, var*& vec, var _tolerance=NML_TOLERANCE){return check_Equal(1, dot(length, vec, vec), _tolerance);}
        inline bool is_Unit(var*& vec, Idx_VM length, var _tolerance=NML_TOLERANCE){return check_Equal(1, dot(length, vec, vec), _tolerance);}
        
        /**
         * @brief 判断2d向量象限 (+x=right, +y=up)
         * [2, 1]
         * [3, 4] 
         * @param vec2    数组表示的向量
         * @return 返回判断向量所在象限
         */
        char get_Quadrant__v2(var*& vec2);
        
        /**
         * @brief 向量求模
         * 
         * @param length 向量长度
         * @param vec    数组表示的向量
         * @return 返回向量模长
         */
        var mag(Idx_VM length, var*& vec);
        inline var mag(var*& vec, Idx_VM length){return mag(length, vec);}

        /**
         * @brief 判断向量是不是零向量     (严格的, $1考虑浮点数误差)
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero__Strict(Idx_VM length, var*& vec);
        inline bool is_Zero__Strict(var*& vec, Idx_VM length){return is_Zero__Strict(length, vec);}

        /**
         * @brief 判断向量是不是零向量     
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero(Idx_VM length, var*& vec, var _tolerance=NML_TOLERANCE);
        inline bool is_Zero(var*& vec, Idx_VM length, var _tolerance=NML_TOLERANCE){return is_Zero(length, vec, _tolerance);};

        /**
         * @brief 标准化向量
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        var*& normalize(Idx_VM length, var*& vec);
        inline var*& normalize(var*& vec, Idx_VM length){return normalize(length, vec);}
        
        /**
         * @brief 向量取反
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        var*& instead(Idx_VM length, var*& vec);
        inline var*& instead(var*& vec, Idx_VM length){return instead(length, vec);}
        
        /**
         * @brief 3d叉乘 数据长度固定为3
         * 
         * @param out           输出目标
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         */
        inline void cross_V3(var*& out, var*& vec_left, var*& vec_right){
            out[0]= vec_left[1]*vec_right[2] - vec_left[2]*vec_right[1];    // x : y1z2-z1y2
            out[1]= vec_left[2]*vec_right[0] - vec_left[0]*vec_right[2];    // y : z1x2-x1z2
            out[2]= vec_left[0]*vec_right[1] - vec_left[1]*vec_right[0];    // z : x1y2-y1x2
        }

        /**
         * @brief 2d叉乘 数据长度固定为2
         * 
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         * @return 输出2d向量叉积值
         */
        inline var cross_V2(var*& vec_left, var*& vec_right){return vec_left[0]*vec_right[1] - vec_left[1]*vec_right[0];}

        /**
         * @brief 2d向量求点乘
         * 
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         * @return 输出2d向量点积值
         */
        inline var dot_v2(var*& vec_left, var*& vec_right){return vec_left[0]*vec_right[0]+vec_left[1]*vec_right[1];}
        
        /**
         * @brief 3d向量求点乘
         * 
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         * @return 输出3d向量点积值
         */
        inline var dot_v3(var*& vec_left, var*& vec_right){return vec_left[0]*vec_right[0]+vec_left[1]*vec_right[1]+vec_left[2]*vec_right[2];}
        
        /**
         * @brief 2d向量求模
         * 
         * @param vec 向量数据
         * @return 返回2d向量模长
         */
        inline var mag_v2(var*& vec){
            return sqrt(
                vec[0]*vec[0]+
                vec[1]*vec[1]
            );
        }
        
        /**
         * @brief 2d向量求模
         * @param x 向量 x 坐标
         * @param y 向量 y 坐标
         * @return 返回2d向量模长
         */
        inline var mag_v2(var x, var y){return sqrt(x*x+y*y);}
        
        /**
         * @brief 3d向量求模
         * 
         * @param vec  向量数据
         * @return 返回3d向量模长
         */
        inline var mag_v3(var*& vec){
            return sqrt(
                vec[0]*vec[0]+
                vec[1]*vec[1]+
                vec[2]*vec[2]
            );
        }

        /**
         * @brief 获取2d向量夹角cos值 (∠LOR)
         * 
         * @param vec_left      左侧向量数据
         * @param vec_right     右侧向量数据
         * @return 返回夹角的cos值
         */
        inline var cos_2Vec(var*& vec_left, var*vec_right){return dot_v2(vec_left, vec_right)/(mag_v2(vec_left)*mag_v2(vec_right));}
        
        /**
         * @brief 获取 3d向量夹角值 (∠LOR)
         * 
         * @param vec_left      左侧向量数据
         * @param vec_right     右侧向量数据
         * @return 返回夹角的cos值
         */
        inline var cos_3Vec(var*& vec_left, var*vec_right){return dot_v3(vec_left, vec_right)/(mag_v3(vec_left)*mag_v3(vec_right));}
        
    }
}

#endif
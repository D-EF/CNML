/*!
 * @Description: 向量 Vector 
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-04-15 03:52:08
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
        inline bool is_Unit(const int length, var*& vec, const var _tolerance=__TOLERANCE__){
            return abs(1-dot(length, vec, vec))<(_tolerance);
        }
        
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
        var mag(int length, var*& vec);
        inline var mag(var*& vec,int length){return mag(length,vec);}

        /**
         * @brief 判断向量是不是零向量     (严格的,不考虑浮点数误差)
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero__Strict(int length, var*& vec);
        inline bool is_Zero__Strict(var*& vec,int length){return is_Zero__Strict(length,vec);};

        /**
         * @brief 判断向量是不是零向量     
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero(int length, var*& vec);
        inline bool is_Zero(var*& vec,int length){return is_Zero(length,vec);};

        /**
         * @brief 标准化向量
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        void normalize(int length, var*& vec);
        inline void normalize(var*& vec,int length){return normalize(length,vec);}
        
        /**
         * @brief 向量取反
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        void instead(int length, var*& vec);
        inline void instead(var*& vec, int length){return instead(length,vec);}
        
        /**
         * @brief 3d叉乘 数据长度固定为3
         * 
         * @param out           输出对象
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         */
        inline void cross(var*& out, var*& vec_left, var*& vec_right){
            out[0]= vec_left[1]*vec_right[2] - vec_left[2]*vec_right[1];    // x : y1z2-z1y2
            out[1]= vec_left[2]*vec_right[0] - vec_left[0]*vec_right[2];    // y : z1x2-x1z2
            out[2]= vec_left[0]*vec_right[1] - vec_left[1]*vec_right[0];    // z : x1y2-y1x2
        }
        
        /**
         * @brief 3d叉乘 数据长度固定为3
         * 
         * @param out           输出对象
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         */
        inline void cross_v3(var*& out, var*& vec_left, var*& vec_right){cross(vec_left, vec_right, out);}

        /**
         * @brief 2d叉乘 数据长度固定为2
         * 
         * @param vec_left      左侧数据
         * @param vec_right     右侧数据
         * @return 输出2d向量叉积值
         */
        inline var cross_v2(var*& vec_left, var*& vec_right){return vec_left[0]*vec_right[1] - vec_left[1]*vec_right[0];}

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
         * @brief 获取  2d向量夹角值
         * 
         * @param vec_left      左侧向量数据
         * @param vec_right     右侧向量数据
         * @return 返回夹角的cos值
         */
        inline var cos_2Vec(var*& vec_left, var*vec_right){return dot_v2(vec_left, vec_right)/(mag_v2(vec_left)*mag_v2(vec_right));}
        
    }
}

#endif
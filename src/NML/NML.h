/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-03-30 03:13:55
 * @FilePath: \NML\src\NML\NML.h
 * @Description: 
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__
#include <stdlib.h>
#include <cstring>

namespace NML{
    typedef float var;

    class NML_Value{
        public:
            int length;
            var* data;
            NML_Value(int length)              :length(length)       , data(new var[length]){}
            NML_Value(int length, var* data)   :length(length)       , data(new var[length]){memcpy(this->data,data,length*sizeof(var));}
            NML_Value(NML_Value &vec)          :length(vec.length)   , data(new var[length]){memcpy(this->data,vec.data,vec.length*sizeof(var));}
            ~NML_Value(){free(this->data);}

            inline var& operator[](int index){return data[index];};
    };
    // typedef NML_Value Vector;
    // typedef NML_Value Matrix;
    // typedef NML_Value Quaternion;
    // typedef NML_Value Euler_Angles;

    namespace Vector{

        typedef NML_Value Vec;
  
        // 判断二维向量的象限
        // [2,1]   
        // [3,4] 
        inline char get_Quadrant__v2(Vec& vec);
        char get_Quadrant__v2(var* vec2);

        // 向量求模
        inline var mag(Vec& vec){return mag(vec.length,vec.data);}
        var mag(int length,var* vec);
        
        /** 判断某个向量是否为单位向量
         * @param vec         向量
         * @param _tolerance   容差 默认为 1e-6
         * @return 返回是否为单位向量
         */
        inline bool is_Unit(Vec& vec,var _tolerance=1e-6f){return is_Unit(vec.length,vec.data,_tolerance);}
        bool is_Unit(int length,var* vec,var _tolerance=1e-6f);

        
        /** 判断向量是不是零向量 (严格的,不考虑浮点数误差)
         * @param   vec 向量
         * @return  返回0或非0
         */
        bool is_Zero__Strict(Vec& vec);

        /** 标准化向量 
         * @param vec 数据来源和输出
         * @return 修改 vec 并输出
         */   
        Vec setup_Vector__Normalization(Vec vec);

        /** 向量取反
         * @param vec 数据来源和输出
         * @return 修改 vec 并输出
         */     
        Vec setup_Vector__Instead(Vec vec);

        
        /** 求向量和
         * @param  vec_left     向量1
         * @param  vec_right    向量2
         * @param  out          输出结果
         * @return 修改 out 并输出
         */
        Vec setup_Vector__Sum(Vec vec_left, Vec vec_right, Vec out);
        
        /** 平移
         * @template {Vec} _Out_Vec
         * @param {_Out_Vec} vec_left  原向量
         * @param {Vec} vec_right  偏移量向量
         * @return {_Out_Vec} 修改并返回 vec_left
         */
        Vec translate(Vec out, Vec translate_value);
        
        /** 求向量差 1-2
         * @param {Vec} vec_left 向量1
         * @param {Vec} vec_right 向量2
         * @return {Vector} 返回一个新向量
         */
        Vec& dif(Vec& vec_left,Vec& vec_right);
        
        /** 数字乘向量 
         * @param {Vec} vec    向量
         * @param {number} k 标量
         * @return {Vec} 返回新的向量
         */
        Vec& np(Vec& vec,var k);

        /** 向量内积
         * @param {Vec} vec_left 向量1
         * @param {Vec} vec_right 向量2
         * @return {number} 返回 vec_left * vec_right
         */
        var dot(Vec& vec_left,Vec& vec_right);

        /** 向量外积(叉乘) 此处仅可用长度为3的数组或类数组 vec.length === 3
         * @param {Vec} vec_left    向量1 length=3
         * @param {Vec} vec_right   向量2 length=3
         * @param {Vec} [_out]      输出对象
         * @throws {TypeError} 参数 vec_left 或 vec_right 长度不等于3时, 将会报错
         * @return {Vec} 返回 vec_left x vec_right
         */
        Vec& cross(Vec& vec_left,Vec& vec_right,Vec& _out);

        /** 计算向量夹角 ∠AOB 的 cos
         * @param {Vec} vec_left 表示角的一边的射线上 的 向量A
         * @param {Vec} vec_right 表示角的一边的射线上 的 向量B
         * @return {number} 返回夹角的cos值
         */
        var& cos_2Vec(Vec& vec_left,Vec& vec_right);

    }
    
    namespace Matrix{
        
    }

    namespace Euler_Angles{

    }

    namespace Quaternion{
        
    }
    
};

#endif
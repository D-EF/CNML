/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-04-03 06:48:14
 * @FilePath: \NML\src\NML.h
 * @Description: 
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__



namespace NML{
    typedef float var;
    const var __TOLERANCE__=1e-6;

    class Values{
        public:
            int length;
            var* data;
            Values(const int length)    :length(length)       , data(new var[length]){}
            Values(const Values &vec)   :length(vec.length)   , data(new var[length]){int i; for(i=length-1;i>=0;--i){this->data[i]=vec.data[i];}}

            void setup (const int length,const var* data);

            ~Values(){delete[] this->data;}

            inline var& operator[](int index){return data[index];};

            inline Values& operator=(var* d){setup(this->length,d);};
    };

    // open * 公用的函数 * open

        /**
         * @brief 数据数值 和
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param out           输出对象
         */
        void sum(const int length,var* val_left, var* val_right, var* out);
        
        /**
         * @brief 数据数值 差
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param out           输出对象
         */
        void dif(const int length,var* val_left, var* val_right, var* out);

        /**
         * @brief 点乘
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @return 输出点乘数量积
         */
        var dot(const int length,var* val_left,var* val_right);

        /**
         * @brief 标量乘
         * 
         * @param length        数据长度
         * @param val           数组数据
         * @param k             标量
         * @param out           输出对象
         */
        void np(const int length,var* val,var k, var* out);

    // end  * 公用的函数 * end 


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
        inline bool is_Unit(const int length,var* vec,const var _tolerance=__TOLERANCE__){
            return abs(1-dot(length,vec,vec))<(_tolerance);
        }
        
        /**
         * @brief 向量求模 
         * [2,1]
         * [3,4] 
         * @param length 向量长度
         * @param vec    数组表示的向量
         * @return 返回向量模长
         */
        char get_Quadrant__v2(var* vec2);
        
        /**
         * @brief 向量求模
         * 
         * @param length 向量长度
         * @param vec    数组表示的向量
         * @return 返回向量模长
         */
        var mag(int length,var* vec);

        /**
         * @brief 判断向量是不是零向量     (严格的,不考虑浮点数误差)
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero__Strict(const int length,var* vec);

        /**
         * @brief 判断向量是不是零向量     
         * 
         * @param length                   向量数组长度
         * @param vec                      数组表示的向量数据
         * @return 返回向量是不是零向量 
         */
        bool is_Zero(const int length,var* vec);

        /**
         * @brief 标准化向量
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        void reset_Normalization(const int length,var* vec);
        
        /**
         * @brief 向量取反
         * 
         * @param length    向量数组长度
         * @param vec       数组表示的向量数据 将会被函数修改
         */
        void reset_Instead(const int length,var* vec);
        
        /**
         * @brief 3d叉乘 数据长度固定为3
         * 
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param out           输出对象
         */
        void cross(var* val_left, var* val_right, var* out);

        /**
         * @brief 2d叉乘 数据长度固定为2
         * 
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @return 输出2d向量叉积值
         */
        var cross_v2(var* val_left, var* val_right);

        /**
         * @brief 获取  2d向量夹角值
         * 
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @return 输出2d向量叉积值
         */
        var cos_2Vec(var* vec_left, var*vec_right);

    }

}



#endif


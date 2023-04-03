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

#include "Math.h"

namespace NML{
    typedef float var;
    const var __TOLERANCE__=1e-6;

    class Values{
        public:
            int length;
            var* data;
            Values(const int length)    :length(length)       , data(new var[length]){}
            Values(const Values &vec)   :length(vec.length)   , data(new var[length]){setup(vec.data);}

            /**
             * @brief 写入数据
             * 
             * @param length   数据长度
             * @param data     数据数组
             */
            void setup (const int length,const var* data);
            inline void setup (const var* data){setup(this->length,data);}

            ~Values(){delete[] this->data;}

            inline var& operator[](int index){return data[index];}

            inline Values& operator=(var*& d){setup(d);}
    };

    // open * 公用的函数 * open
        
        /**
         * @brief 判断值是否相等(容差)
         * 
         * @param v1            左侧数据
         * @param v2            右侧数据
         * @param _tolerance    容差
         * @return  返回是否相等
         */
        inline bool check_Equal(var v1,var v2,var _tolerance=__TOLERANCE__){return abs(v1-v2)<_tolerance;}

        /**
         * @brief 判断数据是否相等(容差)
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param _tolerance    容差
         * @return  返回是否相等
         */
        bool check_Equal(int length,var*& val_left, var*& val_right, var _tolerance=__TOLERANCE__);
        
        /**
         * @brief 数据数值 和
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param out           输出对象
         */
        void sum(int length,var*& val_left, var*& val_right, var*& out);
        
        /**
         * @brief 数据数值 差
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @param out           输出对象
         */
        void dif(int length,var*& val_left, var*& val_right, var*& out);

        /**
         * @brief 点乘
         * 
         * @param length        数据长度
         * @param val_left      左侧数据
         * @param val_right     右侧数据
         * @return 输出点乘数量积
         */
        var dot(int length,var*& val_left,var*& val_right);

        /**
         * @brief 标量乘
         * 
         * @param length        数据长度
         * @param val           数组数据
         * @param k             标量
         * @param out           输出对象
         */
        void np(int length,var*& val,var k, var*& out);

    // end  * 公用的函数 * end 

}



#endif


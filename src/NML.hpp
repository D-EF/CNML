/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-05-06 02:41:46
 * @Description: Nittle Math Library 简单数学库
 * 
 * @Copyright (c) 2023 by Darth_Eternalfaith darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__

#define __NML_VALUE_TYPE__ float
// #define __NML_MATRIX_2D__USING_2X3__  // or use 3x3 matrix


#include <Math.h>

namespace NML{

    typedef __NML_VALUE_TYPE__ var;

    const var __TOLERANCE__=1e-6;

    template <typename value_Type> inline value_Type min(value_Type a,value_Type b){return a>b?b:a;}
    
    template <typename value_Type> inline value_Type max(value_Type a,value_Type b){return a>b?a:b;}

    class Values{
        public:
            int length;
            var* data;
            Values(const int length)    :length(length)       , data(new var[length]()){}
            Values(const Values &vec)   :length(vec.length)   , data(new var[length]){setup(vec.data);}

            /**
             * @brief 写入数据
             * 
             * @param length   数据长度
             * @param data     数据数组
             */
            void setup (const int length, const var* data);
            inline void setup (const var* data){setup(this->length, data);}

            ~Values(){delete[] this->data;}

            inline var& operator[](int index){return data[index];}

            inline Values& operator=(var*& d){setup(d);return *this;}
    };

    void clone_To(var* to, const var* val, int length);
    inline void copy_To(var* to, const var* val, int length){clone_To(to, val, length);}

    /**
     * @brief 拷贝数据
     * 
     * @param val       数据
     * @param length    长度
     * @return 拷贝数据到 new var[length] 并返回地址
     */
    var* create_Values__Clone(const var* val, int length);

    /** 打印行数据 */

    /**
     * @brief 
     * 
     * @param val 
     * @param length 
     */
    void printf_val(const var* val, int length);
    inline void printf_val(const Values val){printf_val(val.data,val.length);}

    /**
     * @brief 判断值是否相等(容差)
     * 
     * @param v1            左侧数据
     * @param v2            右侧数据
     * @param _tolerance    容差
     * @return  返回是否近似相等
     */
    inline bool check_Equal(var v1, var v2, var _tolerance=__TOLERANCE__){return fabs(v1-v2)<_tolerance;}

    /**
     * @brief 判断是否趋近零
     * 
     * @param value         数值
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    inline bool check_Zero(var value, var _tolerance=__TOLERANCE__){return fabs(value)<_tolerance;}

    /**
     * @brief 判断数据是否相等(容差)
     * 
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     * @param _tolerance    容差
     * @return  返回是否相等
     */
    bool check_Equal(int length, var*& val_left, var*& val_right, var _tolerance=__TOLERANCE__);
    inline bool check_Equal(var*& val_left, var*& val_right,int length, var _tolerance=__TOLERANCE__){return check_Equal(length, val_left, val_right, _tolerance);}
    
    
    /**
     * @brief 判断是否趋近零
     * 
     * @param length        数据长度
     * @param value         数据
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    bool check_Zero(int length, var*& value, var _tolerance=__TOLERANCE__);

    /**
     * @brief 数据数值 和
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void sum(var*& out, int length, var*& val_left, var*& val_right);
    
    /**
     * @brief 数据数值 差
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void dif(var*& out, int length, var*& val_left, var*& val_right);

    /**
     * @brief 点乘
     * 
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     * @return 输出点乘数量积
     */
    var dot(int length, var*& val_left, var*& val_right);
    inline var dot(var*& val_left, var*& val_right,int length){return dot(length,val_left,val_right);}

    /**
     * @brief 标量乘
     * 
     * @param out           输出对象
     * @param val           数组数据
     * @param k             标量
     */
    var*& np(var*& out, int length, var k);
    inline var*& np_v2(var*& out, var k){out[0]*=k;out[1]*=k;       return out;}
    inline var*& np_v3(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;     return out;}
    inline var*& np_v4(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;out[3]*=k;       return out;}


    namespace Matrix_2D{
        const int M2D__2X3     =0;
        const int M2D__3X2     =1;
        const int M2D__3X3_L   =2;
        const int M2D__3X3_R   =3;

        //默认使用 3*3 左乘向量 (vector * matrix)
        int _using_matrix_type=M2D__3X3_L;

        // 定义操作时的下标: mij 表示 i行,j列; tx,ty 表示 x,y 齐次坐标;
        int w  =3,   h  =3,
            mxx=0,   mxy=1,   mx_null=2,
            myx=3,   myy=4,   my_null=5,
            tx =6,   ty =7,   mi_full=8;
        /**
         * @brief 
         * @param type 使用的矩阵格式
         */
        void set_M2dConfig__using_matrix_type(int type);
    }
}



#endif


/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-05-18 11:35:08
 * @Description: Nittle Math Library 简单数学库
 * 
 * @Copyright (c) 2023 by Darth_Eternalfaith darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__

#ifndef __NML_VALUE_TYPE__
    /**
     * @brief NML使用的基本数据类型
     */
    #define __NML_VALUE_TYPE__ float
#endif

#ifndef __NML_VECTOR_INDEX_TYPE__
    /**
     * @brief NML使用的向量和矩阵下标类型
     */
    #define __NML_VECTOR_MATRIX_INDEX_TYPE__ char
#endif

#ifndef __NML_INDEX_TYPE__
    #define __NML_INDEX_TYPE__ int
#endif

#define __NML__INLINE__M2D_ACTION_FUNCTION inline
#define __NML__INLINE__M3D_ACTION_FUNCTION inline
#define __NML__INLINE__QUATERNION_FUNCTION inline


#include <Math.h>
#include <iostream>

namespace NML{
    typedef __NML_VALUE_TYPE__ var;
    typedef __NML_VECTOR_MATRIX_INDEX_TYPE__ Idx_VM;
    typedef __NML_INDEX_TYPE__ idx;

    const var NML_TOLERANCE=1e-6;
    
    /** 三个坐标轴 */
    enum Axis{ X=0, Y=1, Z=2 };
    
    enum Plane_3D{
        YZ=0,
        ZX=1,
        XY=2
    };
    
    /** 欧拉角旋转顺序 */
    enum Rotation_Order{
        XYZ=0b000110,    XYX=0b000100,    XZY=0b001001,    XZX=0b001000,
        YXZ=0b010010,    YXY=0b010001,    YZX=0b011000,    YZY=0b011001,
        ZXY=0b100001,    ZXZ=0b100010,    ZYX=0b100100,    ZYZ=0b100110
    };
    
    /**
     * @brief 提取 Rotation_Order 的旋转轴
     * @param order 欧拉角旋转顺序
     * @param index 旋转轴下标[0,2], 表示第几次旋转
     * @return 返回当前旋转轴向
     */
    inline Axis get_Rotation_Order(Rotation_Order order,char index){
        return (Axis)(order>>(2*index) &0b11);
    }

    template <typename value_Type> inline value_Type min(value_Type a,value_Type b){return a>b?b:a;}
    
    template <typename value_Type> inline value_Type max(value_Type a,value_Type b){return a>b?a:b;}

    class Values{
        public:
            idx length;
            var* data;
            Values(const idx length)    :length(length)       , data(new var[length]()){}
            Values(const Values &vec)   :length(vec.length)   , data(new var[length]){setup(vec.data);}

            /**
             * @brief 写入数据
             * 
             * @param length   数据长度
             * @param data     数据数组
             */
            void setup (const idx length, const var* data);
            inline void setup (const var* data){setup(this->length, data);}

            ~Values(){delete[] this->data;}

            inline var& operator[](idx index){return data[index];}

            inline Values& operator=(var*& d){setup(d);return *this;}
    };

    void clone_To(var* to, const var* val, idx length);
    inline void copy_To(var* to, const var* val, idx length){clone_To(to, val, length);}

    /**
     * @brief 拷贝数据
     * 
     * @param val       数据
     * @param length    长度
     * @return 拷贝数据到 new var[length] 并返回地址
     */
    var* create_Values__Clone(const var* val, idx length);


    /**
     * @brief 打印向量
     * 
     * @param val    数据
     * @param length 长度
     */
    void printf_Vec(const var* val, idx length);
    inline void printf_Vec(const Values val){printf_Vec(val.data,val.length);}

    /**
     * @brief 判断值是否相等(容差)
     * 
     * @param v1            左侧数据
     * @param v2            右侧数据
     * @param _tolerance    容差
     * @return  返回是否近似相等
     */
    inline bool check_Equal(var v1, var v2, var _tolerance=NML_TOLERANCE){return fabs(v1-v2)<_tolerance;}

    /**
     * @brief 判断是否趋近零
     * 
     * @param value         数值
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    inline bool check_Zero(var value, var _tolerance=NML_TOLERANCE){return fabs(value)<_tolerance;}

    /**
     * @brief 判断数据是否相等(容差)
     * 
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     * @param _tolerance    容差
     * @return  返回是否相等
     */
    bool check_Equal(idx length, var*& val_left, var*& val_right, var _tolerance=NML_TOLERANCE);
    inline bool check_Equal(var*& val_left, var*& val_right,idx length, var _tolerance=NML_TOLERANCE){return check_Equal(length, val_left, val_right, _tolerance);}
    
    
    /**
     * @brief 判断是否趋近零
     * 
     * @param length        数据长度
     * @param value         数据
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    bool check_Zero(idx length, var*& value, var _tolerance=NML_TOLERANCE);

    /**
     * @brief 数据数值 和
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void sum(var*& out, idx length, var*& val_left, var*& val_right);
    
    /**
     * @brief 数据数值 差
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void dif(var*& out, idx length, var*& val_left, var*& val_right);

    /**
     * @brief 点乘
     * 
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     * @return 输出点乘数量积
     */
    var dot(idx length, var*& val_left, var*& val_right);
    inline var dot(var*& val_left, var*& val_right,idx length){return dot(length,val_left,val_right);}

    /**
     * @brief 标量乘
     * 
     * @param out           输出对象
     * @param val           数组数据
     * @param k             标量
     */
    var*& np(var*& out, idx length, var k);
    inline var*& np_v2(var*& out, var k){out[0]*=k;out[1]*=k;                       return out;}
    inline var*& np_v3(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;             return out;}
    inline var*& np_v4(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;out[3]*=k;   return out;}

}

#endif


/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-09-09 16:36:34
 * @FilePath: \cnml\src\NML.hpp
 * @Description: Nittle Math Library 简单数学库
 * 
 * @Copyright (c) 2023 by Darth_Eternalfaith darth_ef@hotmail.com, All Rights Reserved. 
 */

#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__

#ifndef __NML_VALUE_TYPE__
    /** @brief NML使用的基本数据类型 */
    #define __NML_VALUE_TYPE__ float
#endif

#ifndef __NML_VECTOR_INDEX_TYPE__
    /** @brief NML使用的向量和矩阵下标类型 */
    #define __NML_VECTOR_MATRIX_INDEX_TYPE__ char
#endif

#ifndef __NML_INDEX_TYPE__
    /** @brief 通用下标类型 */
    #define __NML_INDEX_TYPE__ int
#endif

#ifndef __NML_ALGEBRA_INDEX_TYPE__
    /** @brief 算数下标类型 */
    #define __NML_ALGEBRA_INDEX_TYPE__ char
#endif

#ifndef __DEFINE_SAMPLE_SIZE_SEED__
    /** @brief 全局默认采样精度种子 */
    #define __DEFINE_SAMPLE_SIZE_SEED__ 10
#endif


#include <Math.h>
#include <iostream>

namespace NML{

    /** @brief 基本数据类型 */
    typedef __NML_VALUE_TYPE__ var;
    /** @brief 通用下标类型 */
    typedef __NML_INDEX_TYPE__ Idx;
    /** @brief 向量和矩阵的下标类型 */
    typedef __NML_VECTOR_MATRIX_INDEX_TYPE__ Idx_VM;
    /** @brief 算数下标类型 */
    typedef __NML_ALGEBRA_INDEX_TYPE__ Idx_Algebra;
    /** @brief 默认容差 */
    extern const var NML_TOLERANCE;
    
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
    
    extern const var PI, DEG, DEG_90, CYCLES;
    extern const var &DEG_180;
    extern const var ONE_OVER_THREE;
    extern const var FOUR_OVER_THREE;

    /**
     * @brief 整形数组链表
     */
    typedef struct Link_List__Int_List
    {
        Link_List__Int_List *next;
        Idx_Algebra n;
        int *data;
    } Link_List__Int_List;


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
            Idx length;
            var* data;
            Values(const Idx length)    :length(length)       , data(new var[length]()){}
            Values(const Values &vec)   :length(vec.length)   , data(new var[length]){setup(vec.data);}

            /**
             * @brief 写入数据
             * 
             * @param length   数据长度
             * @param data     数据数组
             */
            void setup (const Idx length, const var* data);
            inline void setup (const var* data){setup(this->length, data);}

            ~Values(){delete[] this->data;}

            inline var& operator[](Idx index){return data[index];}

            inline Values& operator=(var*& d){setup(d);return *this;}
    };

    /**
     * @brief 点云数据访问器
     */
    class Points_Iterator{
        public:
        void *data;
        Idx points_length;
        Idx_Algebra dimensional;
        Points_Iterator(){}
        Points_Iterator(Idx_Algebra dimensional, Idx points_length):points_length(points_length), dimensional(dimensional){}
        Points_Iterator(void *data, Idx_Algebra dimensional, Idx points_length):data(data), points_length(points_length), dimensional(dimensional){}
        /** @brief 用下标 取点 */
        virtual var* operator[](int v) = 0; 
        /** @brief 装配 new data */
        virtual void install_Data(Idx_Algebra dimensional, Idx points_length) = 0; 
        /** @brief 释放data数据 */
        virtual void free_Data () = 0;
    };
    
    class Points_Iterator__2DList :virtual public Points_Iterator{
        public:
        Points_Iterator__2DList(var** data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__2DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(dimensional, points_length){install_Data(dimensional,points_length);}
        void install_Data(Idx_Algebra dimensional, Idx points_length){
            var** d=new var*[points_length];
            for(int i=0;i<points_length;++i){
                d[i]=new var[dimensional];
            }
            data=d;
        }
        void free_Data(){
            for(int i=0;i<points_length;++i){
                delete ((var**)data)[i];
            }
            delete (var**)data;
            data=0;
        }
        var* operator[](int v) override{return ((var**)data)[v];}
    };

    class Points_Iterator__1DList :virtual public Points_Iterator{
        public:
        Points_Iterator__1DList(var* data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__1DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(new var[dimensional*points_length], dimensional, points_length){}
        void install_Data(Idx_Algebra dimensional, Idx points_length){ data=new var[dimensional*points_length]; }
        void free_Data(){delete (var*)data; data=0;}
        var* operator[](int v) override{return ((var*)data)+(v*dimensional);}
    };

    void clone_To(var* to, const var* val, Idx length);
    inline void copy_To(var* to, const var* val, Idx length){clone_To(to, val, length);}

    /**
     * @brief 拷贝数据
     * 
     * @param val       数据
     * @param length    长度
     * @return 拷贝数据到 new var[length] 并返回地址
     */
    var* create_Values__Clone(const var* val, Idx length);


    /**
     * @brief 打印向量
     * 
     * @param val    数据
     * @param length 长度
     */
    void printf_Vec(const var* val, Idx length);
    inline void printf_Vec(const Values val){printf_Vec(val.data,val.length);}

    /**
     * @brief 打印点云数据
     * @param points    点云数据访问器
     */
    void printf_Points(Points_Iterator &points);


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
    bool check_Equal(Idx length, var*& val_left, var*& val_right, var _tolerance=NML_TOLERANCE);
    inline bool check_Equal(var*& val_left, var*& val_right,Idx length, var _tolerance=NML_TOLERANCE){return check_Equal(length, val_left, val_right, _tolerance);}
    
    
    /**
     * @brief 判断是否趋近零
     * 
     * @param length        数据长度
     * @param value         数据
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    bool check_Zero(Idx length, var*& value, var _tolerance=NML_TOLERANCE);

    /**
     * @brief 数据数值 和
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void sum(var*& out, Idx length, var*& val_left, var*& val_right);

    var sum(var* start,Idx length);
    
    /**
     * @brief 数据数值 差
     * 
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void dif(var*& out, Idx length, var*& val_left, var*& val_right);

    /**
     * @brief 点乘
     * 
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     * @return 输出点乘数量积
     */
    var dot(Idx length, var*& val_left, var*& val_right);
    inline var dot(var*& val_left, var*& val_right,Idx length){return dot(length,val_left,val_right);}

    /**
     * @brief 标量乘
     * 
     * @param out           输出对象
     * @param val           数组数据
     * @param k             标量
     */
    var*& np(var*& out, Idx length, var k);
    inline var*& np_v2(var*& out, var k){out[0]*=k;out[1]*=k;                       return out;}
    inline var*& np_v3(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;             return out;}
    inline var*& np_v4(var*& out, var k){out[0]*=k;out[1]*=k;out[2]*=k;out[3]*=k;   return out;}

}

#endif


/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-03-06 11:32:46
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

#ifndef __NML_TOLERANCE__
    /** @brief 默认容差 */
    #define __NML_TOLERANCE__ 1e-6
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
    /** 1 - 默认容差 */
    extern const var NML_TOLERANCE_D1;
    /** @brief 默认采样精度种子 */
    extern const Idx SAMPLE_SIZE_SEED;
    /** @brief 默认采样精度步长 */
    extern const var SAMPLE_SIZE_SIZE;
    
    /** 三个坐标轴 */
    enum Axis{ X=0, Y=1, Z=2 };
    
    /** 三个坐标轴 */
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
    
    extern const var PI,
                     DEG, 
                     DEG_90, 
                     CYCLES, 
                     PI_I, 
                     DEG_90_I, 
                     CYCLES_I;

    extern const var &DEG_180_I,
                     &DEG_180,
                     &DEG_360_I,
                     &DEG_360;
                     
    extern const var ONE_OVER_THREE;
    extern const var FOUR_OVER_THREE;


    /**
     * @brief 提取 Rotation_Order 的旋转轴
     * @param order 欧拉角旋转顺序
     * @param index 旋转轴下标[0, 2], 表示第几次旋转
     * @return 返回当前旋转轴向
     */
    inline Axis get_Rotation_Order(Rotation_Order order, char index){ return (Axis)(order>>(2*index) &0b11); }

    /** 
     * @brief 取 [a, b] 中的最小值
     */
    template <typename Value_Type> inline Value_Type min(const Value_Type& const a, const Value_Type& const b){return a>b?b:a;}
    
    /** 
     * @brief 取 [a, b] 中的最大值
     */
    template <typename Value_Type> inline Value_Type max(const Value_Type& const a, const Value_Type& const b){return a>b?a:b;}
    
    
    /** 用于各种回调的函数类型 */
    typedef void (*Callback)(void*, int);


    template <typename Value_Type>
    /** 用于存储静态数据或自定访问规则的的简单块链节点 */
    struct Link_Block__Simple {
        Link_Block__Static<Value_Type>* next;
        Idx length;
        Value_Type* data;
    };


    /**
     * @brief 点云数据访问器
     */
    class Points_Iterator{
        public:
        void *data;
        /** @brief 点的数量 */
        Idx points_length;
        /** @brief 点的维度 */
        Idx_Algebra dimensional;
        Points_Iterator(){}
        Points_Iterator(Idx_Algebra dimensional, Idx points_length):points_length(points_length), dimensional(dimensional){}
        Points_Iterator(void *data, Idx_Algebra dimensional, Idx points_length):data(data), points_length(points_length), dimensional(dimensional){}
        Points_Iterator(Points_Iterator& copy_obj):points_length(copy_obj.points_length), dimensional(copy_obj.dimensional){}
        /** @brief 用下标 取点 */
        virtual var* operator[](Idx v) = 0; 
        /** @brief 装配 new data */
        virtual void install_Data(Idx_Algebra dimensional, Idx points_length) = 0; 
        /** @brief 抄录数据到当前实例的 data */
        void copy_Data(Points_Iterator& copy_obj);
        /** @brief 释放data数据 */
        virtual void free_Data () = 0;
    };
    

    /**
     * @brief 物理一维存储的点访问器
     */
    class Points_Iterator__1DList :virtual public Points_Iterator{
        public:
        Points_Iterator__1DList(var* data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__1DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(new var[dimensional*points_length], dimensional, points_length){}
        Points_Iterator__1DList(Points_Iterator& copy_obj):Points_Iterator(copy_obj){install_Data(dimensional, points_length);copy_Data(copy_obj);}
        ~Points_Iterator__1DList(){free_Data();}
        void install_Data(Idx_Algebra dimensional, Idx points_length){ data=new var[dimensional*points_length]; }
        void free_Data(){delete (var*)data; data=0;}
        var* operator[](Idx v) override{return ((var*)data)+(v*dimensional);}
    };
    

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

    /**
     * @brief 打印点云数据
     * @param points    点云数据访问器
     */
    void printf_Points(Points_Iterator& points);


    /**
     * @brief 判断值是否相等(容差)
     * 
     * @param v1            左侧数据
     * @param v2            右侧数据
     * @param _tolerance    容差
     * @return  返回是否近似相等
     */
    inline bool check_Equal(var v1, var v2, var _tolerance=NML_TOLERANCE){return abs(v1-v2)<_tolerance;}

    /**
     * @brief 判断是否趋近零
     * 
     * @param value         数值
     * @param _tolerance    容差
     * @return 返回数值是否趋近0
     */
    inline bool check_Zero(var value, var _tolerance=NML_TOLERANCE){return abs(value)<_tolerance;}

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
    inline bool check_Equal(var*& val_left, var*& val_right, Idx length, var _tolerance=NML_TOLERANCE){return check_Equal(length, val_left, val_right, _tolerance);}
    
    
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
     * @param out           输出目标
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void sum(var*& out, Idx length, var*& val_left, var*& val_right);

    var sum(var* start, Idx length);
    
    /**
     * @brief 数据数值 差
     * 
     * @param out           输出目标
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
    inline var dot(var*& val_left, var*& val_right, Idx length){return dot(length, val_left, val_right);}

    /**
     * @brief 标量乘
     * 
     * @param out           输出目标
     * @param val           数组数据
     * @param k             标量
     */
    var*& np(var*& out, Idx length, var k);
    inline var*& np_v2(var*& out, var k){out[0]*=k;  out[1]*=k;                           return out;}
    inline var*& np_v3(var*& out, var k){out[0]*=k;  out[1]*=k;  out[2]*=k;               return out;}
    inline var*& np_v4(var*& out, var k){out[0]*=k;  out[1]*=k;  out[2]*=k;  out[3]*=k;   return out;}

    /**
     * @brief 二分法查找显式查找表中离 target 最近的项目
     * @param target    要查找的目标
     * @param lut       显式查找表 应为正序排序的 Number 类型数组 (如路径到当前下标指令的长度)
     * @param length    lut 的长度
     * @return 返回最离 target 最近的项的下标
     */
    Idx select_Lut__Binary(var target, var* lut, Idx length);

    /**
     * 判断值是否在取值范围内
     */
    inline bool check_Inside__Range(var range0, var range1, var value){ return ( (range0>value) != (range1>value) ); }

    /**
     * 判断两个取值范围是否有交集 
     * @param r0_min 取值范围 r0 的最小值
     * @param r0_max 取值范围 r0 的最大值
     * @param r1_min 取值范围 r1 的最小值
     * @param r1_max 取值范围 r1 的最大值
     * @return 返回是否有交集
     */
    inline bool check_Intersection__Range(var r0_min, var r0_max, var r1_min, var r1_max){
        return r0_min<=r1_max && r1_min<=r0_max;
    }
    
    /**
     * 求两个取值范围的交集 
     * @param out_min   新取值范围的最小值的输出目标
     * @param out_max   新取值范围的最大值的输出目标
     * @param r0_min    取值范围 r0 的最小值
     * @param r0_max    取值范围 r0 的最大值
     * @param r1_min    取值范围 r1 的最小值
     * @param r1_max    取值范围 r1 的最大值
     * @return 返回是否有交集
     */
    bool calc_Intersection__Range(var& out_min,var& out_max, var r0_min, var r0_max, var r1_min, var r1_max);

    /**
     * 判断两个取值范围是否有交集 (无序的)
     * @param a0 取值范围 a 的端点 0
     * @param a1 取值范围 a 的端点 1
     * @param b0 取值范围 b 的端点 0
     * @param b1 取值范围 b 的端点 1
     * @return 返回是否有交集
     */
    inline bool check_Intersection__Range_Unordered(var a0, var a1, var b0, var b1){
        return (
            ( (a0>=b0) != (a0>=b1) )||
            ( (a1>=b0) != (a1>=b1) )||
            ( (b0>=a0) != (b0>=a1) )||
            ( (b1>=a0) != (b1>=a1) )  
        );
    }

}

#endif


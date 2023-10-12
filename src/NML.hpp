/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-10-11 19:46:13
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

#ifndef __MIN_LINK_BLOCK_SIZE__
    /** @brief 创建链块存储的单块最小 size */
    #define __MIN_LINK_BLOCK_SIZE__ 256
#endif

#ifndef __MAX_LINK_BLOCK_SIZE__
    /** @brief 创建链块存储的单块最大 size */
    #define __MAX_LINK_BLOCK_SIZE__ 65536
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
    /** @brief 默认采样精度种子 */
    extern const Idx SAMPLE_SIZE_SEED;
    /** @brief 默认采样精度步长 */
    extern const var SAMPLE_SIZE_SIZE;
    
    /** @brief 数值块链节点 */
    typedef struct Link_Block__Var{
        var *data;
        Idx size;
        Idx max_size;
        Link_Block__Var* next;
    }Link_Block__Var;
    
    /** @brief 整形块链节点 */
    typedef struct Link_Block__Int
    {
        Link_Block__Int *next;
        Idx size;
        int *data;
    } Link_Block__Int;


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
     * @brief 提取 Rotation_Order 的旋转轴
     * @param order 欧拉角旋转顺序
     * @param index 旋转轴下标[0, 2], 表示第几次旋转
     * @return 返回当前旋转轴向
     */
    inline Axis get_Rotation_Order(Rotation_Order order, char index){
        return (Axis)(order>>(2*index) &0b11);
    }

    template <typename value_Type> inline value_Type min(value_Type a, value_Type b){return a>b?b:a;}
    
    template <typename value_Type> inline value_Type max(value_Type a, value_Type b){return a>b?a:b;}


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
        /** @brief 用下标 取点 */
        virtual var* operator[](Idx v) = 0; 
        /** @brief 装配 new data */
        virtual void install_Data(Idx_Algebra dimensional, Idx points_length) = 0; 
        /** @brief 释放data数据 */
        virtual void free_Data () = 0;
    };
    
    class Points_Iterator__2DList :virtual public Points_Iterator{
        public:
        Points_Iterator__2DList(var** data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__2DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(dimensional, points_length){install_Data(dimensional, points_length);}
        ~Points_Iterator__2DList(){free_Data();}
        void install_Data(Idx_Algebra dimensional, Idx points_length);
        void free_Data();
        var* operator[](Idx v) override{return ((var**)data)[v];}
    };

    class Points_Iterator__1DList :virtual public Points_Iterator{
        public:
        Points_Iterator__1DList(var* data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__1DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(new var[dimensional*points_length], dimensional, points_length){}
        ~Points_Iterator__1DList(){free_Data();}
        void install_Data(Idx_Algebra dimensional, Idx points_length){ data=new var[dimensional*points_length]; }
        void free_Data(){delete (var*)data; data=0;}
        var* operator[](Idx v) override{return ((var*)data)+(v*dimensional);}
    };

    
    class Points_Iterator__Link :virtual public Points_Iterator{
        public:
        /** @brief 最大存储长度 (缓存 calc_MaxPointsLength()的计算结果) */
        Idx max_points_length;
        Idx last_access_head_v;
        Link_Block__Var* last_access_block;
        Points_Iterator__Link(Link_Block__Var* data, Idx_Algebra dimensional, Idx points_length): Points_Iterator(data, dimensional, points_length), last_access_head_v(-1), last_access_block(0) {}
        Points_Iterator__Link(Idx_Algebra dimensional, Idx points_length):Points_Iterator(dimensional, points_length){}
        ~Points_Iterator__Link(){free_Data();}
        void install_Data(Idx_Algebra dimensional, Idx points_length){ append_Block(dimensional*points_length); }
        void free_Data();
        var* operator[](Idx v) override;
        
        /** @brief 计算当前已有空间的最多能存放多少个点数 */
        Idx calc_MaxPointsLength();

        /** 
         * @brief 追加一块存储空间
         * @param 块的大小 ( 实际空间大小= size * sizeof(var) )
         */
        void append_Block(Idx size=-1);
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
     * @param out           输出对象
     * @param length        数据长度
     * @param val_left      左侧数据
     * @param val_right     右侧数据
     */
    void sum(var*& out, Idx length, var*& val_left, var*& val_right);

    var sum(var* start, Idx length);
    
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
    inline var dot(var*& val_left, var*& val_right, Idx length){return dot(length, val_left, val_right);}

    /**
     * @brief 标量乘
     * 
     * @param out           输出对象
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
}

#endif


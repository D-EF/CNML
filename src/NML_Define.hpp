/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2024-05-06 15:14:27
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-21 17:00:30
 * @FilePath: \CNML\src\NML_Define.hpp
 * @Description: 包含各种公用的 宏, 类型, 结构体, 常量值, 枚举 声明 的头文件, 常量定义在 NML.cpp
 */

#ifndef __NITTLE_MATH_LIBRARY_DEFINE__
#define __NITTLE_MATH_LIBRARY_DEFINE__

    #ifdef _MSC_VER // Visual C++ 编译器
        /** 显式 dll 导出 */
        #define EXPORT_SYMBOL __declspec(dllexport)
    #else // 其他编译器
        /** 显式 dll 导出 */
        #define EXPORT_SYMBOL
    #endif


    #include <iostream>


    // open * NML * open
    
        #ifndef __NML_IDX_INFINITY__
            /** @brief Idx 的最大值 */
            #define __NML_IDX_INFINITY__ 2147483647
        #endif

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
            #define __DEFINE_SAMPLE_SIZE_SEED__ 16
        #endif

        #ifndef __NML_TOLERANCE__
            /** @brief 默认容差 */
            #define __NML_TOLERANCE__ 1e-6
        #endif
    // end  * NML * end 
    
    
    // open * Link Block * open
        #ifndef __DEFAULT_LINK_BLOCK_LENGTH__
            /** @brief 创建块状链表存储的默认单块长度 size */
            #define __DEFAULT_LINK_BLOCK_LENGTH__ 256
        #endif

        #define __LINK_BLOCK__NEVER_OVERLOAD_OPERATOR__
    // end  * Link Block * end 


    // open * NML * open
    // end  * NML * end 


    // open * NML * open
    // end  * NML * end 



EXPORT_SYMBOL namespace NML{
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
    
    template <typename Value_Type>
    /** 用于存储静态数据或自定访问规则的的简单块状链表节点 */
    struct Link_Block__Simple {
        Link_Block__Simple<Value_Type>* next;
        Idx length;
        Value_Type* data;
    };
    
    /* @brief 存放左右两个下标的结构体 */
    typedef struct Sliding_Index{
        Idx index_0;
        Idx index_1;
    } Sliding_Index;


    /** 圆周率 */
    extern const var PI;
    /** 1度的弧度值 */
    extern const var DEG;
    /** 90度的弧度值 */
    extern const var DEG_90;
    /** 整圆的弧度值 */
    extern const var CYCLES;
    /** 负的圆周率 */
    extern const var PI_I;
    /** -90度的弧度值 */
    extern const var DEG_90_I;
    /** 反向整圆的弧度值 */
    extern const var CYCLES_I;

    /** -180度的弧度值 */
    extern const var &DEG_180_I;
    /** -360度的弧度值 */
    extern const var &DEG_360_I;
    /** 180度的弧度值 */
    extern const var &DEG_180;
    /** 360度的弧度值 */
    extern const var &DEG_360;
                     
    /** 1/3 的值 */
    extern const var ONE_OVER_THREE;
    /** 4/3 的值 */
    extern const var FOUR_OVER_THREE;


    /** 用于各种回调的函数类型 */
    typedef void (*Callback)(void*);


    /**
     * @brief 点云数据访问器基类
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
        Points_Iterator(Points_Iterator& copy_obj):points_length(copy_obj.points_length), dimensional(copy_obj.dimensional){
            install_Data(dimensional, points_length);
            copy_Data(copy_obj);
        }
        /** @brief 用下标 取点 */
        virtual var* operator[](Idx v) = 0; 

        /** @brief 装配 new data */
        virtual void install_Data(Idx_Algebra dimensional, Idx points_length) = 0; 

        /** @brief 抄录数据到当前实例的 data */
        void copy_Data(Points_Iterator& copy_obj);

        /** @brief 释放data数据 */
        virtual void free_Data () = 0;

        /** 设置 维度 */
        void set_Dimensional(Idx_Algebra new_dimensional){
            dimensional=new_dimensional;
        }

        /** 设置 点的个数 */
        void set_PointsLength(Idx new_points_length){
            points_length = new_points_length;
        }

    };
    

}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-02-28 20:18:33
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2024-06-26 10:07:47
 * @FilePath: \cnml\src\NML.hpp
 * @Description: Nittle Math Library 简单数学库
 */


#ifndef __NITTLE_MATH_LIBRARY__
#define __NITTLE_MATH_LIBRARY__

#include "NML_Define.hpp"
#include <Math.h>
#include <iostream>

EXPORT_SYMBOL namespace NML{
    

    /**
     * @brief 提取 Rotation_Order 的旋转轴
     * @param order 欧拉角旋转顺序
     * @param index 旋转轴下标[0, 2], 表示第几次旋转
     * @return 返回当前旋转轴向
     */
    inline Axis get_Rotation_Order(Rotation_Order order, char index){ return (Axis)(order>>(2*index) &0b11); }


    /**
     * @brief 物理一维存储的点访问器
     */
    class Points_Iterator__1DList :virtual public Points_Iterator{
        public:
        Points_Iterator__1DList(var* data, Idx_Algebra dimensional, Idx points_length):Points_Iterator(data, dimensional, points_length){}
        Points_Iterator__1DList(Idx_Algebra dimensional, Idx points_length):Points_Iterator(new var[dimensional*points_length], dimensional, points_length){}
        Points_Iterator__1DList(Points_Iterator& copy_obj):Points_Iterator(copy_obj){}
        ~Points_Iterator__1DList(){free_Data();}
        void install_Data(Idx_Algebra new_dimensional=0, Idx new_points_length=0){ 
            if(new_dimensional>0)   dimensional     = new_dimensional;
            if(points_length>0)     points_length   = new_points_length;

            data=new var[dimensional*points_length]; 
        }
        void free_Data(){delete (var*)data; data=0;}
        var* operator[](Idx v) override{return ((var*)data)+(v*dimensional);}
        void set_Dimensional(Idx_Algebra new_dimensional, bool reset_data=true) override{
            dimensional=new_dimensional;
            if(reset_data)install_Data();
        }
        void set_PointsLength(Idx new_points_length, bool reset_data=true) override{
            points_length=new_points_length;
            if(reset_data)install_Data();
        }
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
    void printf_Vec(const var* val, Idx length, const char* line_head=0);

    /**
     * @brief 打印点云数据
     * @param points    点云数据访问器
     */
    void printf_Points(Points_Iterator& points, const char* line_head=0);


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
    bool check_Equal(Idx length, var* val_left, var* val_right, var _tolerance=NML_TOLERANCE);
    inline bool check_Equal(var* val_left, var* val_right, Idx length, var _tolerance=NML_TOLERANCE){return check_Equal(length, val_left, val_right, _tolerance);}
    
    bool check_Equal(Idx length, int* val_left, int* val_right);
    inline bool check_Equal(int* val_left, int* val_right, Idx length){return check_Equal(length, val_left, val_right);}
    
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
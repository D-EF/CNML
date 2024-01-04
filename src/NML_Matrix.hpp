/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-12-29 17:57:29
 * @FilePath: \cnml\src\NML_Matrix.hpp
 * @Description: 矩阵 Matrix
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef __NML_MATRIX__
#define __NML_MATRIX__

#include "NML.hpp"
#include "NML_Vector.hpp"

namespace NML{
    /**
     * @brief 存放矩阵相关函数
     * 
     */
    namespace Matrix{
        
        /** 打印矩阵*/
        void printf_Matrix(var*& matrix, Idx_VM width, Idx_VM height);
        inline void printf_Matrix(var*& matrix, Idx_VM n){
            printf_Matrix(matrix, n, n);
        }

        /**
         * @brief 使用uv坐标 获取实际下标index
         * 
         * @param width     矩阵宽度
         * @param u         横坐标 u
         * @param v         纵坐标 v
         * @return 返回下标index
         */
        inline Idx_VM get_Index(Idx_VM width, Idx_VM u, Idx_VM v){return u+width*v;}

        /**
         * @brief 创建单位矩阵
         * @param out       输出目标
         * @param width     矩阵宽度
         * @param height    矩阵高度
         * @return 修改并返回 out
         */
        var*& setup_Matrix__Identity(var*& out, Idx_VM width, Idx_VM height);
        
        /**
         * @brief 创建单位矩阵
         * @param width     矩阵宽度
         * @param height    矩阵高度
         * @return 返回一个 new var[width*height]对象
         */
        inline var* create_Matrix__Identity(Idx_VM width, Idx_VM height){
            var *out=new var[width*height];
            setup_Matrix__Identity(out, width, height);
            return out;
        }

        /** 
         * @brief 矩阵数据转写   空省位置会保留out原有的内容
         * 
         * @param out            输出目标 (不能与 mat 使用同一地址)
         * @param mat            数据来源 (不能与 out 使用同一地址)
         * @param low_width      原矩阵宽度
         * @param new_width      新矩阵宽度
         * @param _low_height    原矩阵高度  无输入时将使用 low_width
         * @param _new_height    新矩阵高度  无输入时将使用 new_width
         * @param _shift_left    旧矩阵拷贝到新矩阵时的左侧偏移 默认为 0
         * @param _shift_top     旧矩阵拷贝到新矩阵时的上方偏移 默认为 0
         * @return 修改并返回 out
         */
        var*& setup_Matrix__Resize(var*& out, var*& mat, Idx_VM low_width, Idx_VM new_width, Idx_VM _low_height=0, Idx_VM _new_height=0, Idx_VM _shift_left=0, Idx_VM _shift_top=0);

        /**
         * @brief 计算哈达姆积 HadamardProduct
         * @param  out            输出目标
         * @param  mat_left       左矩阵
         * @param  mat_right      右矩阵
         * @param  width          矩阵宽度
         * @param  height         矩阵高度
         * @return 修改并返回 out
         */
        var*& setup_Matrix__HadamardProduct(var*& out, var*& mat_left, var*& mat_right, Idx_VM width, Idx_VM height);

        /** 
         * @brief 计算 Kronecker 张量积
         * @param  out            输出目标
         * @param  mat_left       左矩阵
         * @param  mat_right      右矩阵
         * @param  width_left     左矩阵的宽度
         * @param  height_left    左矩阵的高度
         * @param  width_right    右矩阵的宽度
         * @param  height_right   右矩阵的高度
         * @return 修改并返回 out
         */
        var*& setup_Matrix__KroneckerProduct(var*& out, var*& mat_left, var*& mat_right, Idx_VM width_left, Idx_VM height_left, Idx_VM width_right, Idx_VM height_right);

        /** 
         * @brief 合并矩阵
         * @param  out          输出目标 长度应为 width_g * height_g * width_mat * height_mat
         * @param  mats         矩阵集合 长度应为 width_g * height_g
         * @param  width_mat    每个矩阵的宽度
         * @param  height_mat   每个矩阵的高度
         * @param  width_g      输出中一行放多少个矩阵
         * @param  height_g     输出中一列放多少个矩阵
         */
        var*& setup_Matrix__Concat(var*& out, var**& mats, Idx_VM width_mat, Idx_VM height_mat, Idx_VM width_g, Idx_VM height_g);

        /**
         * @brief 初等变换 换行
         * 
         * @param mat       要处理的矩阵
         * @param width     矩阵宽度
         * @param v1        v坐标1
         * @param v2        v坐标2
         */
        void transformation__ExchangeRow(var*& mat, Idx_VM width, Idx_VM v1, Idx_VM v2);
        void transformation__ExchangeRow(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM v1, Idx_VM v2);

        /**
         * @brief 初等变换 换列
         * 
         * @param mat      要处理的矩阵
         * @param widht    矩阵宽度
         * @param height   矩阵高度
         * @param u1       u坐标1
         * @param u2       u坐标2
         */
        void transformation__ExchangeCol(var*& mat, Idx_VM widht, Idx_VM height, Idx_VM u1, Idx_VM u2);
        void transformation__ExchangeCol(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM height, Idx_VM u1, Idx_VM u2);

        /**
         * @brief 初等变换 行乘标量
         * 
         * @param mat       要处理的矩阵
         * @param width     矩阵宽度
         * @param v         v坐标
         * @param k         标量乘值
         */
        void transformation__ScaleRow(var*& mat, Idx_VM width, Idx_VM v, var k);
        void transformation__ScaleRow(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM v, var k);

        /**
         * @brief 初等变换 列乘标量
         * 
         * @param mat       要处理的矩阵
         * @param height    矩阵高度
         * @param u         u坐标
         * @param k         标量乘值
         */
        void transformation__ScaleCol(var*& mat, Idx_VM width, Idx_VM height, Idx_VM u, var k);
        void transformation__ScaleCol(var**& mats, Idx_VM length_g, Idx_VM width, Idx_VM height, Idx_VM u, var k);

        /** 
         * @brief 将矩阵某个为0的项 通过初等变换的换行操作, 变成非0
         * 
         * @param  mat          矩阵数据
         * @param  length       矩阵数据长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长, $1为  ±width
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_ToUnZero(var*& mat, Idx_VM length, Idx_VM width,  Idx_VM index, Idx_VM v, Idx_VM step_length);
        
        /** 
         * @brief 将矩阵某个为0的项 通过初等变换的换行操作, 变成非0; 换行将副作用到其他矩阵上
         * 
         * @param  mats         矩阵数据集合
         * @param  length_g     有多少个矩阵
         * @param  length       每个矩阵长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长, $1为  ±width
         * @param  _index_m     传入多个矩阵时使用哪个矩阵的值 默认0
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_ToUnZero(var**& mats, Idx_VM length_g,  Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length, Idx_VM _index_m=0);


        /** 
         * @brief 寻找最大主元并换行
         * 
         * @param  mat          矩阵数据
         * @param  length       矩阵数据长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长, $1为  ±width
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_PivotToMax(var*& mat, Idx_VM length, Idx_VM width,  Idx_VM index, Idx_VM v, Idx_VM step_length);
        
        /** 
         * @brief 寻找最大主元并换行; 换行将副作用到其他矩阵上
         * 
         * @param  mats         矩阵数据集合
         * @param  length_g     有多少个矩阵
         * @param  length       每个矩阵长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长, $1为  ±width
         * @param  _index_m     传入多个矩阵时使用哪个矩阵的值 默认0
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_PivotToMax(var**& mats, Idx_VM length_g, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length, Idx_VM _index_m=0);

        /**
         * @brief 矩阵乘法
         * 
         * @param out                       输出目标
         * @param mat_left                  左矩阵
         * @param mat_right                 右矩阵
         * @param height_left               左矩阵高度
         * @param _width_left_height_right   右矩阵高度 和 左矩阵宽度
         * @param _width_right               右矩阵宽度 ; 默认使用 height_left
         */
        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, Idx_VM height_left, Idx_VM _width_left_height_right, Idx_VM _width_right=0);

        
        /**
         * @brief 矩阵乘法 (方阵)
         * 
         * @param out                       输出目标
         * @param mat_left                  左矩阵
         * @param mat_right                 右矩阵
         * @param n                         表示这个矩阵是n*n方阵
         */
        var*& multiplication(var*& out, var*& mat_left, var*& mat_right, Idx_VM n);
        
        /** 
         * @brief 检查矩阵正交
         * 
         * @param mat           矩阵数据
         * @param n             表示这个矩阵是n*n方阵
         * @return 返回矩阵是否正交
         */
        bool check_Orthogonal(var*& mat, Idx_VM n);

        /**
         * @brief 方阵转置
         * 
         * @param mat           方阵数据 将会被函数修改
         * @param n             表示是n*n方阵
         */
        var*& transpose(var*& mat, Idx_VM n);

        /**
         * @brief 矩阵转置 (注意输出目标不能和输入矩阵使用同一内存)
         * 
         * @param out           输出目标 注意这个输出目标不能和输入矩阵使用同一内存
         * @param mat           矩阵数据
         * @param width_mat     原矩阵宽度
         * @param height_mat    原矩阵高度
         */
        var*& transpose(var*& out, var*& mat, Idx_VM width_mat, Idx_VM height_mat);

        /**
         * @brief 2*2矩阵转置
         * @param mat   矩阵数据
         * @param temp  传一个temp变量引用以节约开销
         */
        inline var*& transpose_2(var*& mat){
            std::swap(mat[1], mat[2]);
            return mat;
        }
        
        /**
         * @brief 3*3矩阵转置
         * @param mat   矩阵数据
         * @param temp  传一个temp变量引用以节约开销
         */
        inline var*& transpose_3(var*& mat){
            std::swap(mat[1], mat[3]);
            std::swap(mat[2], mat[6]);
            std::swap(mat[5], mat[7]);
            return mat;
        }
        /**
         * @brief 4*4矩阵转置
         * @param mat   矩阵数据
         * @param temp  传一个temp变量引用以节约开销
         */
        inline var*& transpose_4(var*& mat){
            std::swap(mat[1], mat[4]);
            std::swap(mat[2], mat[8]);
            std::swap(mat[3], mat[12]);
            std::swap(mat[6], mat[9]);
            std::swap(mat[7], mat[13]);
            std::swap(mat[11], mat[14]);
            return mat;
        }

        /**
         * @brief 使用初等变换计算行列式;
         * 应在n>4时才使用, n<4时推荐使用 calc_Det__${n}
         * 
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方矩阵
         * @return 返回计算的行列式值 
         */
        var calc_Det__Transformation(var*& mat, Idx_VM n);

        // open * 1-4阶矩阵行列式内联函数 * open
            /**
             * @brief 1x1矩阵行列式
             * 
             * @param mat 矩阵数据
             * @return 返回计算行列式值
             */
            inline var calc_Det__1(var*& mat){return mat[0];}

            /**
             * @brief 2x2矩阵行列式
             * 
             * @param mat 矩阵数据
             * @return 返回计算行列式值
             */
            inline var calc_Det__2(var*& mat){return  mat[0]*mat[3]-mat[1]*mat[2];}

            /**
             * @brief 3x3矩阵行列式
             * 
             * @param mat 矩阵数据
             * @return 返回计算行列式值
             */
            inline var calc_Det__3(var*& mat){
                return  mat[0]*(mat[4]*mat[8] - mat[5]*mat[7]) -
                        mat[1]*(mat[3]*mat[8] - mat[5]*mat[6]) +
                        mat[2]*(mat[3]*mat[7] - mat[4]*mat[6]);
            }

            /**
             * @brief 4x4矩阵行列式
             * 
             * @param mat 矩阵数据
             * @return 返回计算行列式值
             */
            inline var calc_Det__4(var*& mat){
                var t0  = mat[0]  * mat[5]  - mat[1]  * mat[4],
                    t1  = mat[0]  * mat[6]  - mat[2]  * mat[4],
                    t2  = mat[0]  * mat[7]  - mat[3]  * mat[4],
                    t3  = mat[1]  * mat[6]  - mat[2]  * mat[5],
                    t4  = mat[1]  * mat[7]  - mat[3]  * mat[5],
                    t5  = mat[2]  * mat[7]  - mat[3]  * mat[6],
                    t6  = mat[8]  * mat[13] - mat[9]  * mat[12],
                    t7  = mat[8]  * mat[14] - mat[10] * mat[12],
                    t8  = mat[8]  * mat[15] - mat[11] * mat[12],
                    t9  = mat[9]  * mat[14] - mat[10] * mat[13],
                    t10 = mat[9]  * mat[15] - mat[11] * mat[13],
                    t11 = mat[10] * mat[15] - mat[11] * mat[14];
                
                return t0 * t11 - t1 * t10 + t2 * t9 + t3 * t8 - t4 * t7 + t5 * t6;
            }
        // end  * 1-4阶矩阵行列式内联函数 * end 

        /**
         * @brief 计算矩阵行列式
         * 
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方阵
         * @return 返回计算的行列式值
         */
        var calc_Det(var*& mat, Idx_VM n);

        /**
         * @brief 矩阵求逆 使用初等变换法(高斯乔丹消元法)
         * 
         * @param out       输出目标
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方阵
         * @return 返回是否成功计算逆矩阵
         */
        bool setup_Matrix__Inverse__Transformation(var*& out, var*& mat, Idx_VM n);

        // open * 公式法矩阵求逆函数 * open
            // 公式法 m^-1=adj(m)/|m|
            
            /**
             * @brief 2x2 矩阵求逆
             * 
             * @param out       输出目标
             * @param mat       矩阵数据 (必须是方阵)
             * @return 返回是否成功计算逆矩阵
             */
            bool setup_Matrix__Inverse__2(var*& out, var*& mat);
            
            /**
             * @brief 3x3 矩阵求逆
             * 
             * @param out       输出目标
             * @param mat       矩阵数据 (必须是方阵)
             * @return 返回是否成功计算逆矩阵
             */
            bool setup_Matrix__Inverse__3(var*& out, var*& mat);
            
            /**
             * @brief 4x4 矩阵求逆
             * 
             * @param out       输出目标
             * @param mat       矩阵数据 (必须是方阵)
             * @return 返回是否成功计算逆矩阵
             */
            bool setup_Matrix__Inverse__4(var*& out, var*& mat);

        // end  * 公式法矩阵求逆函数 * end 

        /**
         * @brief 矩阵求逆
         * 
         * @param out       输出目标
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方矩阵
         * @return 返回是否成功计算逆矩阵
         */
        bool setup_Matrix__Inverse(var*& out, var*& mat, Idx_VM n);
        
    }
}

#endif
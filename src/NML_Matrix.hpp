/*!
 * @Description: 矩阵 Matrix
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-04-09 22:35:51
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
        void printf_Matrix(int width, int height, var*& matrix);

        /**
         * @brief 使用uv坐标 获取实际下标index
         * 
         * @param width     矩阵宽度
         * @param u         横坐标 u
         * @param v         纵坐标 v
         * @return 返回下标index
         */
        inline int get_Index(int width, int u, int v){
            return u+width*v;
        }

        /**
         * @brief 创建单位矩阵
         * 
         * @param out       输出对象
         * @param width     矩阵宽度
         * @param height    矩阵高度
         */
        void setup_Identity(var*& out, int width, int height);

        /** 
         * @brief 矩阵数据转写   空省位置会保留out原有的内容
         * 
         * @param out            输出对象 (不能与 mat 使用同一地址)
         * @param mat            数据来源 (不能与 out 使用同一地址)
         * @param low_width      原矩阵宽度
         * @param new_width      新矩阵宽度
         * @param _low_height    原矩阵高度  无输入时将使用 low_width
         * @param _new_height    新矩阵高度  无输入时将使用 new_width
         * @param _shift_left    旧矩阵拷贝到新矩阵时的左侧偏移 默认为 0
         * @param _shift_top     旧矩阵拷贝到新矩阵时的上方偏移 默认为 0
         */
        void setup_Resize(var*& out, var*& mat, int low_width, int new_width, int _low_height=0, int _new_height=0, int _shift_left=0, int _shift_top=0);

        /** 
         * @brief 计算张量积
         * @param  out            输出对象
         * @param  mat_left       左矩阵
         * @param  mat_right      右矩阵
         * @param  width_left     左矩阵的宽度
         * @param  height_left    左矩阵的高度
         * @param  width_right    右矩阵的宽度
         * @param  height_right   右矩阵的高度
         */
        void setup_TensorProduct(var*& out, var*& mat_left, var*& mat_right, int width_left, int height_left, int width_right, int height_right);

        /** 
         * @brief 合并矩阵
         * @param  out          输出对象 长度应为 width_g * height_g * width_mat * height_mat
         * @param  mats         矩阵集合 长度应为 width_g * height_g
         * @param  width_mat    每个矩阵的宽度
         * @param  height_mat   每个矩阵的高度
         * @param  width_g      输出中一行放多少个矩阵
         * @param  height_g     输出中一列放多少个矩阵
         */
        void setup_Concat(var*& out, var**& mats, int width_mat, int height_mat, int width_g, int height_g);

        /**
         * @brief 初等变换 换行
         * 
         * @param mat       要处理的矩阵
         * @param width     矩阵宽度
         * @param v1        v坐标1
         * @param v2        v坐标2
         */
        void transformation__ExchangeRow(var*& mat, int width, int v1, int v2);

        /**
         * @brief 初等变换 换列
         * 
         * @param mat       要处理的矩阵
         * @param widht    矩阵宽度
         * @param height    矩阵高度
         * @param u1        u坐标1
         * @param u2        u坐标2
         */
        void transformation__ExchangeCol(var*& mat, int widht, int height, int u1, int u2);
        
        /**
         * @brief 初等变换 行乘标量
         * 
         * @param mat       要处理的矩阵
         * @param width     矩阵宽度
         * @param v         v坐标
         * @param k         标量乘值
         */
        void transformation__ScaleRow(var*& mat, int width, int v, var k);

        /**
         * @brief 初等变换 列乘标量
         * 
         * @param mat       要处理的矩阵
         * @param height    矩阵高度
         * @param u         u坐标
         * @param k         标量乘值
         */
        void transformation__ScaleCol(var*& mat, int width, int height, int u, var k);

        /** 
         * @brief 将矩阵某个为0的项 通过初等变换的换行操作, 变成非0
         * 
         * @param  mat          矩阵数据
         * @param  length       矩阵数据长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长,应为  ±width
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_ToUnZero(var*& mat, int length, int width,  int index, int v, int step_length);
        
        /** 
         * @brief 将矩阵某个为0的项 通过初等变换的换行操作, 变成非0; 换行将副作用到其他矩阵上
         * 
         * @param  mats         矩阵数据集合
         * @param  length       每个矩阵长度
         * @param  width        矩阵宽度
         * @param  index        当前下标
         * @param  v            当前v坐标(行下标)
         * @param  step_length  寻址步长,应为  ±width
         * @param  length_g     有多少个矩阵
         * @param  _index_m     传入多个矩阵时使用哪个矩阵的值 默认0
         * @return 返回是否成功换行
         */
        bool transformation__ExchangeRow_ToUnZero(var**& mat, int length, int index, int width, int v, int step_length, int length_g, int _index_m=0);

        /**
         * @brief 矩阵乘法
         * 
         * @param out                       输出对象
         * @param mat_left                  左矩阵
         * @param mat_right                 右矩阵
         * @param height_left               左矩阵高度
         * @param width_left_height_right   右矩阵高度 和 左矩阵宽度
         * @param width_right               右矩阵宽度
         */
        void multiplication(var*& out, var*& mat_left, var*& mat_right, int height_left, int _width_left_height_right, int _width_right);

        
        /**
         * @brief 矩阵乘法 (方阵)
         * 
         * @param out                       输出对象
         * @param mat_left                  左矩阵
         * @param mat_right                 右矩阵
         * @param n                         表示这个矩阵是n*n方阵
         */
        void multiplication(var*& out, var*& mat_left, var*& mat_right, int n);
        
        /** 
         * @brief 检查矩阵正交
         * 
         * @param mat           矩阵数据
         * @param n             表示这个矩阵是n*n方阵
         * @return 返回矩阵是否正交
         */
        bool check_Orthogonal(var*& mat,int _n);

        /**
         * @brief 方阵转置
         * 
         * @param mat           方阵数据 将会被函数修改
         * @param n             表示是n*n方阵
         */
        void transpose(var*& mat, int n);

        /**
         * @brief 矩阵转置
         * 
         * @param out           输出对象
         * @param mat           矩阵数据
         * @param width_mat     原矩阵宽度
         * @param height_mat    原矩阵高度
         */
        void transpose(var*& out, var*& mat, int width_mat, int height_mat);

        /**
         * @brief 2*2矩阵转置
         * @param mat   矩阵数据
         * @param temp  传一个temp变量引用以节约开销
         */
        inline void transpose_2(var*& mat,var& temp){
            temp=mat[1];
            mat[1]=mat[2];
            mat[2]=temp;
        }
        
        /**
         * @brief 3*3矩阵转置
         * @param mat   矩阵数据
         * @param temp  传一个temp变量引用以节约开销
         */
        inline void transpose_3(var*& mat,var& temp){
            temp=mat[1];
            mat[1]=mat[3];
            mat[3]=temp;
            temp=mat[2];
            mat[2]=mat[6];
            mat[6]=temp;
            temp=mat[5];
            mat[5]=mat[7];
            mat[7]=temp;
        }

        /**
         * @brief 使用初等变换计算行列式;
         * 应在n>4时才使用, n<4时推荐使用 calc_Det__${n}
         * 
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方矩阵
         * @return 返回计算的行列式值 
         */
        var calc_Det__Transformation(var*& mat,int n);

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
                return  mat[0] * (mat[4]*mat[8] - mat[5]*mat[7])+
                        mat[1] * (mat[5]*mat[6] - mat[3]*mat[8])+
                        mat[2] * (mat[3]*mat[7] - mat[5]*mat[6]);
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
        var calc_Det(var*& mat,int n);

        /**
         * @brief 矩阵求逆 使用初等变换法(高斯乔丹消元法)
         * 
         * @param out       输出对象
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方阵
         */
        void setup_Inverse__Transformation(var*& out, var*& mat, int n);

        // open * 公式法矩阵求逆函数 * open
            // 公式法 m^-1=adj(m)/|m|

            /**
             * @brief 1x1 矩阵求逆
             * 
             * @param out       输出对象
             * @param mat       矩阵数据 (必须是方阵)
             */
            inline void setup_Inverse__1(var*& out, var*& mat){
                out[0]=1/mat[0];
            }
            
            /**
             * @brief 2x2 矩阵求逆
             * 
             * @param out       输出对象
             * @param mat       矩阵数据 (必须是方阵)
             */
            void setup_Inverse__2(var*& out, var*& mat);
            
            /**
             * @brief 3x3 矩阵求逆
             * 
             * @param out       输出对象
             * @param mat       矩阵数据 (必须是方阵)
             */
            void setup_Inverse__3(var*& out, var*& mat);
            
            /**
             * @brief 4x4 矩阵求逆
             * 
             * @param out       输出对象
             * @param mat       矩阵数据 (必须是方阵)
             */
            void setup_Inverse__4(var*& out, var*& mat);

        // end  * 公式法矩阵求逆函数 * end 

        /**
         * @brief 矩阵求逆
         * 
         * @param out       输出对象
         * @param mat       矩阵数据 (必须是方阵)
         * @param n         表示这个矩阵是n*n方矩阵
         */
        void setup_Inverse(var*& out, var*& mat, int n);

    }
}

#endif
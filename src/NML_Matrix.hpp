#ifndef __NML_MATRIX__
#define __NML_MATRIX__

#include "NML.hpp"

namespace NML{
    /**
     * @brief 存放矩阵相关函数
     * 
     */
    namespace Matrix{

        /** 
         * @brief 矩阵数据转写   空省位置会保留out原有的内容
         * 
         * @param mat            数据来源 (注意！不能与 out 使用同一地址)
         * @param out            输出对象 (注意！不能与 mat 使用同一地址)
         * @param low_width      原矩阵宽度
         * @param new_width      新矩阵宽度
         * @param _low_height    原矩阵高度  无输入时将使用 low_width
         * @param _new_height    新矩阵高度  无输入时将使用 new_width
         * @param _shift_left    旧矩阵拷贝到新矩阵时的左侧偏移 默认为 0
         * @param _shift_top     旧矩阵拷贝到新矩阵时的上方偏移 无输入时将使用 _shift_left
         */
        void setup_Resize(var*& out, var*& mat, int low_width, int new_width, int _low_height=-1, int _new_height=-1, int _shift_left=0, int _shift_top=-1);

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
        void setup_TensorProduct(var*& out, var*& mat_left, var*& mat_right, int width_lef, int height_lef, int width_righ, int height_right);

        /** 
         * @brief 合并矩阵
         * @param  out          输出对象
         * @param  mats         矩阵集合
         * @param  width_mat    每个矩阵的宽度
         * @param  height_mat   每个矩阵的高度
         * @param  width_g      输出中一行放多少个矩阵
         * @param  height_g     输出中一列放多少个矩阵
         */
        void setup_Concat(var*& out, var**& mats, int width_mat, int height_mat, int width_g, int height_g);
    }
}

#endif
/*!
 * @Author: Darth_Eternalfaith darth_ef@hotmail.com
 * @Date: 2023-04-04 01:26:00
 * @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
 * @LastEditTime: 2023-04-06 02:38:21
 * @FilePath: \NML\src\NML_Matrix.cpp
 * @Description: 矩阵 Matrix
 * @
 * @Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix{
        void setup_Identity(var*& out,int width, int height){
            
        }

        void setup_Resize(var*& out, var*& mat, int low_width, int new_width, int _low_height, int _new_height, int _shift_left, int _shift_top){

        }

        void setup_TensorProduct(var*& out, var*& mat_left, var*& mat_right, int width_lef, int height_lef, int width_righ, int height_right){

        }

        void setup_Concat(var*& out, var**& mats, int width_mat, int height_mat, int width_g, int height_g){

        }

        void transformation__ExchangeRow(var*& mat, int width, int v1, int v2){

        }

        void transformation__ExchangeCol(var*& mat, int height, int u1, int u2){

        }

        void transformation__ScaleRow(var*& mat, int width, int v, var k){

        }

        void transformation__ScaleCol(var*& mat, int height, int u, var k){

        }

        void exchange_ToUnZero(var** mat, int length, int index, int v, int step_length){

        }

        void exchange_ToUnZero(var**& mat, int length, int index, int v, int step_length, int length_g, int _index_m){

        }

        void multiplication(var*& out, int width, int height, var*& mat_left, var*& mat_right){

        }

        bool check_Orthogonal(var*& mat,int _n){

        }

        void transpose(var*& mat, int width, int height){

        }

        var calc_Det__Transformation(var*& mat,int n){

        }

        void setup_Inverse__Transformation(var*& out, var*& mat, int n);
    }
}

#ifndef __NML_MATRIX_2D__
#define __NML_MATRIX_2D__
#include "NML.hpp"
#include "NML_Matrix.hpp"

namespace NML{
    namespace Matrix_2D{

        /** 可选的2D矩阵的存储格式 */
        enum M2D_Type{
            M2D__3X3_L,   // 矩阵左边乘向量 vec * met
            M2D__3X3_R,   // 矩阵右边乘向量 met * vec
            M2D__2X3,     // 矩阵左边乘向量 vec * met 省略右侧列
            M2D__3X2      // 矩阵右边乘向量 met * vec 省略下侧行
        };

        //默认使用 3*3 左乘向量 (vector * matrix)
        extern M2D_Type _using_m2d_type;

        // 数据类型的数据对应宽高
            extern Idx_VM m2d_w,m2d_h;
        // 数据类型的数据对应下标
            extern Idx_VM 
                mxx,   mxy,   mxz,
                myx,   myy,   myz,
                mzx,   mzy,   mzz;
            Idx_VM &mx_null=mxz, &my_null=myz, &tx=mzx, &ty=mzy, &mi_full=mzz;
        //


        /**
         * @brief 切换要使用的数据格式
         * @param type 使用的矩阵格式
         */
        void set_NMLConfig__using_m2d_type(M2D_Type type);

        /**
         * @brief 打印输出2d矩阵变换的css样式
         * @param mat 矩阵数据
         */
        void printf_M2dCss(var*& mat);

        
        /**
         * @brief 写入矩阵数据
         * @param out    操作对象           输出对象
         * @param value_mxx 2d线性变换矩阵 参数 mxx
         * @param value_myx 2d线性变换矩阵 参数 mxy
         * @param value_mxy 2d线性变换矩阵 参数 myx
         * @param value_myy 2d线性变换矩阵 参数 myy
         * @param value_tx  x 方向平移量
         * @param value_ty  y 方向平移量
         * @return 写入 out 并返回
         */
        __NML__INLINE__M2D_ACTION_FUNCTION var*& setup_Matrix2D(var*& out, var value_mxx, var value_myx, var value_mxy, var value_myy, var value_tx, var value_ty);
        
        /**
         * @brief 2d矩阵追加变换
         * @param mat     操作对象
         * @param app_mxx 2d线性变换矩阵 参数 mxx
         * @param app_myx 2d线性变换矩阵 参数 mxy
         * @param app_mxy 2d线性变换矩阵 参数 myx
         * @param app_myy 2d线性变换矩阵 参数 myy
         * @param app_tx  x 方向平移量
         * @param app_ty  y 方向平移量
         * @return 修改 mat 并返回
         */
        __NML__INLINE__M2D_ACTION_FUNCTION  var*& transform_Matrix2D(var*& mat, var app_mxx, var app_mxy, var app_myx, var app_myy, var app_tx, var app_ty);

        
        typedef var*&(_M2d_Act_Fnc)(var*& mat, var app_mxx, var app_myx, var app_mxy, var app_myy, var app_tx, var app_ty);

        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Translate            (const _M2d_Act_Fnc& act, var*& out, var translate_x, var translate_y=0);
        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Scale                (const _M2d_Act_Fnc& act, var*& out, var scale_x, var scale_y);
        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Rotate               (const _M2d_Act_Fnc& act, var*& out, var theta);
        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Rotate__Vector       (const _M2d_Act_Fnc& act, var*& out, var*& unit_vec__org, var*& unit_vec__to);
        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Reflect              (const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y);
        __NML__INLINE__M2D_ACTION_FUNCTION   var*& act_Matrix2D__Shear                (const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k);
        /** never inline */                  var*& act_Matrix2D__Reflect__Collinear   (const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y);
        /** never inline */                  var*& act_Matrix2D__Shear__Collinear     (const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k);


        // open * setup * open

            /**
             * @brief 设置 平移矩阵
             * @param out           输出对象
             * @param translate_x   x 方向平移量
             * @param translate_y   y 方向平移量
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Translate             (var*& out, var translate_x, var translate_y=0)        {return act_Matrix2D__Translate            (setup_Matrix2D, out, translate_x, translate_y);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Scale                 (var*& out, var scale_x, var scale_y)                  {return act_Matrix2D__Scale                (setup_Matrix2D, out, scale_x, scale_y);}
            /**
             * @brief 设置 缩放矩阵
             * @param out           输出对象
             * @param scale_value   缩放值
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Scale                 (var*& out, var scale_value)                           {return act_Matrix2D__Scale                (setup_Matrix2D, out, scale_value, scale_value);}
            /**
             * @brief 设置 旋转矩阵
             * @param out           输出对象
             * @param theta         旋转弧度
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Rotate                (var*& out, var theta)                                 {return act_Matrix2D__Rotate               (setup_Matrix2D, out, theta);}
            inline var*& setup_Matrix2D__Rotate__Vector        (var*& out, var*& unit_vec__org, var*& unit_vec__to)   {return act_Matrix2D__Rotate__Vector       (setup_Matrix2D, out, unit_vec__org, unit_vec__to);}
            /**
             * @brief 设置 镜像矩阵
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向的标准向量的 x 坐标
             * @param normal_y      镜像轴法线方向的标准向量的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Reflect               (var*& out, var normal_x, var normal_y)                {return act_Matrix2D__Reflect              (setup_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 设置 镜像矩阵 (允许法向量为任意向量)
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Reflect__Collinear    (var*& out, var normal_x, var normal_y)                {return act_Matrix2D__Reflect__Collinear   (setup_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief 设置 切变矩阵
             * @param out           输出对象
             * @param axis_x        切变轴标准向量的 x 坐标
             * @param axis_y        切变轴标准向量的 y 坐标
             * @param k             切变系数
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Shear                 (var*& out, var axis_x, var axis_y, var k)             {return act_Matrix2D__Shear                (setup_Matrix2D, out, axis_x, axis_y, k);}
            /**
             * @brief 设置 切变矩阵
             * @param out           输出对象
             * @param axis_x        切变轴方向上的 x 坐标
             * @param axis_y        切变轴方向上的 y 坐标
             * @param k             切变系数
             * @return 修改并返回 out
             */
            inline var*& setup_Matrix2D__Shear__Collinear      (var*& out, var axis_x, var axis_y, var k)             {return act_Matrix2D__Shear__Collinear     (setup_Matrix2D, out, axis_x, axis_y, k);}
        
        // end  * setup * end  


        // open * transform * open

            /**
             * @brief               矩阵进行平移变换
             * @param out           输出对象
             * @param translate_x   x 方向平移量
             * @param translate_y   y 方向平移量
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Translate            (var*& out, var translate_x, var translate_y=0)         {return act_Matrix2D__Translate            (transform_Matrix2D, out, translate_x, translate_y);}
            /**
             * @brief               矩阵进行缩放变换
             * @param out           输出对象
             * @param scale_x       x 方向缩放值
             * @param scale_y       y 方向缩放值
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Scale                (var*& out, var scale_x, var scale_y)                   {return act_Matrix2D__Scale                (transform_Matrix2D, out, scale_x, scale_y);}
            /**
             * @brief               矩阵进行缩放变换
             * @param out           输出对象
             * @param scale_value   缩放值
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Scale                (var*& out, var scale_value)                            {return act_Matrix2D__Scale                (transform_Matrix2D, out, scale_value, scale_value);}
            /**
             * @brief               矩阵进行旋转变换
             * @param out           输出对象
             * @param theta         旋转轴
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Rotate               (var*& out, var theta)                                  {return act_Matrix2D__Rotate               (transform_Matrix2D, out, theta);}
            inline var*& transform_Matrix2D__Rotate__Vector       (var*& out, var*& unit_vec__org, var*& unit_vec__to)    {return act_Matrix2D__Rotate__Vector       (transform_Matrix2D, out, unit_vec__org, unit_vec__to);}
            /**
             * @brief               矩阵进行镜像变换
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向的标准向量的 x 坐标
             * @param normal_y      镜像轴法线方向的标准向量的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Reflect              (var*& out, var normal_x, var normal_y)                 {return act_Matrix2D__Reflect              (transform_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief               矩阵进行镜像变换 (允许法向量为任意向量)
             * @param out           输出对象
             * @param normal_x      镜像轴法线方向上的 x 坐标
             * @param normal_y      镜像轴法线方向上的 y 坐标
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Reflect__Collinear   (var*& out, var normal_x, var normal_y)                 {return act_Matrix2D__Reflect__Collinear   (transform_Matrix2D, out, normal_x, normal_y);}
            /**
             * @brief               矩阵进行切变变换
             * @param out           输出对象
             * @param axis_x        切变轴标准向量的 x 坐标
             * @param axis_y        切变轴标准向量的 y 坐标
             * @param k             切变系数
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Shear                (var*& out, var axis_x, var axis_y, var k)              {return act_Matrix2D__Shear                (transform_Matrix2D, out, axis_x, axis_y, k);}
            /**
             * @brief               矩阵进行切变变换
             * @param out           输出对象
             * @param axis_x        切变轴方向上的 x 坐标
             * @param axis_y        切变轴方向上的 y 坐标
             * @param k             切变系数
             * @return 修改并返回 out
             */
            inline var*& transform_Matrix2D__Shear__Collinear     (var*& out, var axis_x, var axis_y, var k)              {return act_Matrix2D__Shear__Collinear     (transform_Matrix2D, out, axis_x, axis_y, k);}

        // end  * transform * end 


        void set_NMLConfig__using_m2d_type(M2D_Type type){
            if(_using_m2d_type==type)return;
            _using_m2d_type=type;
            switch (_using_m2d_type){
                case M2D__2X3:
                    m2d_w=2,m2d_h=3;
                    mxx=0,   mxy=1,    mx_null=0,
                    myx=2,   myy=3,    my_null=0,
                    tx =4,   ty =5,    mi_full=0;
                break;

                case M2D__3X2:
                    m2d_w=3,m2d_h=2;
                    mxx=0,        myx=1,        tx=2,
                    mxy=3,        myy=4,        ty=5,
                    mx_null =0,   my_null =0,   mi_full=0;
                break;

                case M2D__3X3_L:
                    m2d_w=3,m2d_h=3;
                    mxx=0,   mxy=1,   mx_null=2,
                    myx=3,   myy=4,   my_null=5,
                    tx =6,   ty =7,   mi_full=8;
                break;

                case M2D__3X3_R:
                    m2d_w=3,m2d_h=3;
                    mxx=0,        myx=1,        tx=2,
                    mxy=3,        myy=4,        ty=5,
                    mx_null =6,   my_null =7,   mi_full=8;
                break;
            }
        }

        void printf_M2dCss(var*& mat){
            var v_mxz=0,
                v_myz=0,
                v_mzz=1;
                
            if(!mx_null){
                v_mxz=mat[mxz];
                v_myz=mat[myz];
                v_mzz=mat[mzz];
            }
            printf("transform:matrix(%f, %f, %f, %f, %f, %f);\n",
                mat[mxx],   mat[mxy],
                mat[myx],   mat[myy],
                mat[tx],    mat[ty]
            );
        }

        var*& act_Matrix2D__Rotate__Vector (const _M2d_Act_Fnc& act, var*& out, var*& unit_vec__org, var*& unit_vec__to){
            var c=unit_vec__org[0]*unit_vec__to[0]+unit_vec__org[1]*unit_vec__to[1],
                s=unit_vec__org[1]*unit_vec__to[0]-unit_vec__org[0]*unit_vec__to[1];
            return act(out,
                c,   s,
               -s,   c,
                0,   0
            );
        }

        var*& act_Matrix2D__Reflect__Collinear(const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y){
            var m=normal_x*normal_x+normal_y*normal_y;
            if(!(check_Equal(1,m)||check_Zero(m))){
                m=1/sqrt(m);
                return act_Matrix2D__Reflect(act,out,normal_x*m,normal_y*m);
            }
            return act_Matrix2D__Reflect(act,out,normal_x,normal_y);
        }

        var*& act_Matrix2D__Shear__Collinear(const _M2d_Act_Fnc& act, var*& out, var axis_x, var axis_y, var k){
            var m=axis_x*axis_x+axis_y*axis_y;
            if(!(check_Equal(1,m)||check_Zero(m))){
                m=1/sqrt(m);
                return act_Matrix2D__Shear(act,out,axis_x*m,axis_y*m,k);
            }
            return act_Matrix2D__Shear(act,out,axis_x,axis_y,k);
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& setup_Matrix2D(var*& out, var a, var b, var c, var d, var e, var f){
            out[mx_null]=0;   out[my_null]=0;   out[mi_full]=1;

            out[mxx]=a;       out[mxy]=b;
            out[myx]=c;       out[myy]=d;
            out[tx] =e;       out[ty] =f;
            return out;
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& transform_Matrix2D(var*& mat, var app_mxx, var app_mxy, var app_myx, var app_myy, var app_tx, var app_ty){  
            return setup_Matrix2D(mat,
                mat[mxx]*app_mxx + mat[mxy]*app_myx,            mat[mxx]*app_mxy + mat[mxy]*app_myy,
                mat[myx]*app_mxx + mat[myy]*app_myx,            mat[myx]*app_mxy + mat[myy]*app_myy,
                mat[tx] *app_mxx + mat[ty] *app_myx + app_tx,   mat[tx] *app_mxy + mat[ty] *app_myy + app_ty
            );
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& act_Matrix2D__Translate(const _M2d_Act_Fnc& act, var*& out, var translate_x, var translate_y){
            return act(out,
                1,             0,
                0,             1,
                translate_x,   translate_y
            );
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& act_Matrix2D__Scale(const _M2d_Act_Fnc& act, var*& out,var scale_x, var scale_y){
            return act(out,
                scale_x,   0,
                0,         scale_y,
                0,         0
            );
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& act_Matrix2D__Rotate(const _M2d_Act_Fnc& act, var*& out, var theta){
                var c=cos(theta),s=sin(theta);
                return act(out,
                     c,    s,
                    -s,    c,
                     0,    0
                );
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& act_Matrix2D__Reflect(const _M2d_Act_Fnc& act, var*& out, var normal_x, var normal_y){
            return act(out,
                1-2*normal_x*normal_x ,   -2*normal_x*normal_y,
                -2*normal_x*normal_y  ,   1-2*normal_y*normal_y,
                0,                        0
            );
        }

        __NML__INLINE__M2D_ACTION_FUNCTION var*& act_Matrix2D__Shear(const _M2d_Act_Fnc& act, var*& out,var axis_x, var axis_y, var k){
            return act(out,
                1,          k*axis_x,
                k*axis_y,   1,
                0,          0
            );
        }

    }
}

#endif
# CNML 
* **Nittle Math Library 的 c++ 实现**   
开发中   
文档最后编辑于 2023-12-12
---
其它文档 todo   
  * [向量,矩阵,简单的线性代数](./doc/Linear_Algebra.md)
  * [简单的bezier曲线](./doc/Bezier.md)
  * [点,矩形,弧形,多边形,简单的2D内容](./doc/Geometry_2D.md)
  <!-- * [简单的3D内容](./doc/3D.md) -->

---

## 部分类型说明
可以修改宏定义的类型以替换默认的类型; 如将 通用数值类型 var 设置为 doble
``` cpp
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
namespace NML{
    /** @brief 基本数据类型 */
    typedef __NML_VALUE_TYPE__ var;
    /** @brief 通用下标类型 */
    typedef __NML_INDEX_TYPE__ Idx;
    /** @brief 向量和矩阵的下标类型 */
    typedef __NML_VECTOR_MATRIX_INDEX_TYPE__ Idx_VM;
    /** @brief 算数下标类型 */
    typedef __NML_ALGEBRA_INDEX_TYPE__ Idx_Algebra;
}
```

## 编码规范
  * 命名和编码时避免用1表示起始, 应该使用0;
  * 左花括号不换行, 右花括号要换行;
  * 指针(引用)符号(*&) 在函数、形参的类型中往类型名靠; 在变量声明时往变量名靠;
    ``` cpp
      int* fnc(int* list, int length){
        int *rtn=list;
        for(int i=0; i<length; ++i){
          if(i%2){
            rtn+=list[i];
          }else{
            rtn-=list[i];
          }
        }
        return rtn;
      }
    ```
  * 矩阵参数编辑时应该对齐
    ``` cpp
      // 此处使用了 Visual Studio Code 的插件 align-text-like-table 进行对齐
      float mat_3x3__scale[9]={
          scale_x,   0,         0,
          0,         scale_y,   0,
          0,         0,         scale_z,
      };
    ```
  * 运算符的空格(较宽松的规则)
    * 作为整体时应该避免空格 作为两个部分间的操作应该增加空格
      ```
        123*DEG + 456*DEG;
        (a0>value) != (a1>value);
      ```


## 命名规范
  * 一般命名为基本命名+双下划线+追加说明
  ```
  ${name}__${note}
  ```
  ### 常量
  * 全大写+下划线命名
      ```
      NML_TOLERANCE
      ```
  ### 类、命名空间
  * 大写首字母+下划线命名
      ```
      Matrix_3D
      ```
  ### 变量、形参
  * 小写字母下划线命名
      ```
      index_mat__uv //矩阵对应uv坐标的物理下标
      ```
  * 私有成员, 可选参数; 以下划线开始
      ```
      bool check_Equal(var v1, var v2, var _tolerance=NML_TOLERANCE);
      ```
  * 推荐提供的可选参数; 以 $ 开始
      ```
      void function(void* param_0, void* $param_1=0);
      ```
  ### 函数
  * 小驼峰的动词单词动词短语 + 下划线 + 大驼峰
      ```
      calc_Det__Transformation  //使用初等变换消元法计算行列式
      ```

---

## 注释规范
  
  * 文件头部应该写这个文件的最后编辑者和这个文件的信息, 此处推荐使用编辑器插件实现,我使用的是vscode编辑器, 正好有可用的插件[koroFileHeader](https://marketplace.visualstudio.com/items?itemName=OBKoro1.korofileheader), 头部注释使用 "/\*\!"起始;
    ``` cpp
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
    ```

  * 所有对某个 宏,类/结构体,函数,常量/变量 的声明添加注释时 应该使用块注释并以 "/\*\*"起始, 使用 JavaDoc 的格式编写;

  * 对类型的说明和命名无法一目了然的枚举常量、全局变量，应该有说明, 如果命名就能很明确的清楚这个变量的意义可以省略注释;
    ``` cpp
    // 例 不需要增加注释 :

        extern const var PI;     // 总所周知 PI 是圆周率, 不需要加注释
        
        /** 欧拉角旋转顺序 */
        enum Rotation_Order{
            XYZ=0b000110,    XYX=0b000100,    XZY=0b001001,    XZX=0b001000,
            YXZ=0b010010,    YXY=0b010001,    YZX=0b011000,    YZY=0b011001,
            ZXY=0b100001,    ZXZ=0b100010,    ZYX=0b100100,    ZYZ=0b100110
            // 旋转顺序就是命名中的字母顺序, 不需要额外加注释
        };
        

    // 例 需要增加注释 :
    
        /** @brief 贝塞尔曲线拟合四分之一圆 的 k 值 */
        extern const var BEZIER_TO_CYCLES_K__1D4;
        
        /** 插入内容时追加块链节点时的行为模式 */
        enum Behavior_Pattern__Add_LinkBlock{
            // 禁止添加
                /** 禁止添加, 将尽可能在已有的节点中分配空间存储内容; 无法完成时将会报错 */
                disabled,
                /** 禁止添加, 当前节点无法容纳插入内容时尝试在前面的节点中已有的空间中重新分配以腾出空间保存内容, 无法完成时将会报错*/
                disabled_move_forward,
                /** 禁止添加, 当前节点无法容纳插入内容时尝试在后面的节点中已有的空间中重新分配以腾出空间保存内容, 无法完成时将会报错*/
                disabled_move_backward,
            // 添加
                /** 添加, 当前节点无法容纳插入内容时尝试在前面的节点中已有的空间中重新分配以腾出空间保存内容, 无法保存内容时才会增加节点*/
                able_move_forward,
                /** 添加, 当前节点无法容纳插入内容时尝试在后面的节点中已有的空间中重新分配以腾出空间保存内容, 无法保存内容时才会增加节点*/
                able_move_backward,
                /** 紧凑的, 当所有节点的剩余空间都不足以保存内容时才会增加节点 */
                tight,
                /** 懒惰的, 仅判断节点和前后一个节点是否有剩余空间保存内容, 无法保存时增加节点 */
                lazy,
                /** 积极添加, 当前节点无法容纳插入内容时直接分为3块 >> [0,index):before, [index,length):insert_values, [index+length,...]: after*/
                active
        };
    ```


  * 函数声明的时候都应该写注释, 其中起码要包括函数的说明、参数的说明和可能存在的限制、返回值说明、可能产生的抛出异常和说明;     
    ``` cpp
  
        /** 
         * @brief 向块链插入内容
         * @tparam Value_Type 块链节点使用的数据类型
         * @param header_node              头部节点
         * @param index__offset            元素在访问节点后的下标偏移量
         * @param length                   删除的内容的长度
         * @param value                    追加的内容
         * @param $origin_node             访问节点, 应该可以用header节点访问到, 用于重置 0 下标的位置, 默认使用 header_node
         * @param _length_value            添加内容的长度, 默认为1
         * @param _delete_data_item        是否对删除内容的每个元素执行delete, 默认false
         * @param _paternadd               当前节点无法装载内容时追加块链的行为模式 默认为 lazy (仅检查相邻的块容量)
         * @param _add_node_length         追加节点时新块的长度, 默认为 __MIN_LINK_BLOCK_SIZE__
         * @param _max_link_block_length   块链的最大容量
         * @return 返回是否增加了节点
         * @throw int l  : 当 _paternadd 为禁止新增节点时, 且块链中不足以存入内容, 会抛出整数数值表示还需要额外多少个元素的空间 
         */
        template <typename Value_Type> 
        bool splice_LinkBlock(
            Link_Block_Node<Value_Type>& header_node, Idx index__offset, Idx length,
            Link_Block_Node<Value_Type>* $origin_node=0,
            Value_Type* _value=0, Idx _length_value=1, Behavior_Pattern__Add_LinkBlock _paternadd=lazy, Idx _add_node_length=__MIN_LINK_BLOCK_SIZE__, Idx _max_link_block_length 
        );
    ```

  * 在比较复杂函数代码实现里加一点注释说明当前操作处于算法的哪个步骤
    ``` cpp
        Idx_Algebra calc_Intersection__Bezier_Line(Points_Iterator& out, Points_Iterator& coefficients, var*& line_p0, var*& line_p1){
            Idx_Algebra rtn=0;
            var *t_intersection = new var[coefficients.points_length];
            var *temp_coefficients = new var[coefficients.points_length];
            var *temp_point;
            Idx i;

            // 计算相对坐标
            var x=line_p1[0]-line_p0[0],
                y=line_p0[1]-line_p1[1];
            var mag=sqrt(x*x+y*y);
            if(check_Zero(mag)) return 0;
            mag=1/mag;
            x *= mag;
            y *= mag;

            // 进行平移+旋转变换 使线段处于x正方向上
            temp_point=coefficients[0];
            temp_coefficients[0] = x*(temp_point[0]-line_p0[0]) + y*(temp_point[1]-line_p0[1]);
            for(i=1;  i<coefficients.points_length;  ++i){
                temp_point=coefficients[i];
                temp_coefficients[i] = x*temp_point[0] + y*temp_point[1];
                // 由于计算t值时仅需使用一个维度, 所以仅计算一个维度的值
            }

            Idx_Algebra t_length = Bezier::calc_T__BySample_FromBezier(t_intersection, temp_coefficients, coefficients.points_length, 0);

            // 采样点并保存在线段上的点
            for(i=0;  i<t_length;  ++i){
                temp_point=out[rtn];
                Bezier::sample_Bezier__Coefficients(temp_point, coefficients, t_intersection[i]);
                var projection_value = calc_PointInLine(*(Point_2D*)line_p0, *(Point_2D*)line_p1, *(Point_2D*)temp_point);
                if(projection_value>=0 && projection_value<=1) ++rtn;
            }

            delete t_intersection;
            delete temp_coefficients;
            return rtn;
        }
    ```

---

## 部分命名解释和缩写

  ### 名词
  ```
  * NML            : 库的名字( Nittle Math Library )
  * i(j/k)         : 迭代器(iterator)
  * l              : 长度(length)
  * d              : 差(differ)
  * op/ed          : 起始/结束(open/end)
  * idx            : 索引/下标 ( index )
  * vec            : 向量 ( vector )
  * mat            : 矩阵 ( matrix )
  * m2d            : 2D矩阵 ( matrix two dimensional )
  * m3d            : 3D矩阵 ( matrix three dimensional )
  * det            : 行列式 ( determinant )
  * u              : u 坐标 (水平坐标)
  * v              : v 坐标 (垂直坐标)
  * x              : x 坐标
  * y              : y 坐标
  * z              : z 坐标
  * q,p            : 左指针(q) 和 右指针(p)
  * ex             : 额外的, 追加的, 附加的 (extra)
  * quat           : 四元数 ( quaternion )
  * square         : 平方, 平方曲线(抛物线), 2阶贝塞尔曲线
  * cubic          : 立方, 立方曲线, 3阶贝塞尔曲线
  * girth          : 周长
  * polygon        : 2D多边形
  * mesh           : 3D网格组 (3d多边形)
  * line path      : 首尾相连的多个线段
  * step size      : 步长
  * sample size    : 采样点个数 (采样次数)
  * line           : 线段
  * race           : 矩形
  * arc            : 圆弧
  * ellipse arc    : 椭圆弧
  * bezier         : 贝塞尔曲线
  * AABB           : 轴对齐包围盒 ( Axis-aligned bounding box )
  * intersection   : 交点
  * distance       : 表示几何中的距离/长度
  * inside         : 表示状态  - 在内部
  * had            : 表示状态  - 有可用的缓存值
  ```
  
  ### 动词和动词短语
  ```
  * get                : 获取属性
  * dot                : 在向量运算中表示向量点乘
  * cross              : 2d/3d向量叉乘, 四元数乘法
  * mapping            : 映射为
  * calc               : 计算/求值
  * setup              : 执行装载操作 (初始化为)
  * create             : 创建 (需要手动 delete/free )
  * transformation     : 矩阵基本变换 
  * transform          : 矩阵线性变换 
  * sample             : 采样点 
  * check              : 检查 
  * load               : 加载 (计算值保存到成员变量上)
  * give up            : 淘汰 (淘汰缓存)
  ```
  
  ### 函数形参中的特殊名词
  * out     : 输出对象, 作为复杂数据的输出
  * t       : 插值/采样点 时 使用的抽象单位时间参数 取值范围为 \[0~1\]
  
---

## 部分数据结构说明
* 绝大部分数据结构都使用线性结构的数组/指针表示

### 数值类型
* 宏 **\_\_NML_VALUE_TYPE\_\_** 定义了全局中使用的基本类型,默认为单浮点(float);   

* 命名空间 NML 中所有数值的类型都使用 **var** 表示
* 命名空间 NML 中的 通用下标类型为 **Idx**
* 命名空间 NML::Matrix_3D 和 NML::Matrix_2D 中下标类型为 **Idx_VM**
* 命名空间 NML 中的 表示曲线为n阶, 帕斯卡三角第n层, n维度 使用 **Idx_Algebra**
    ```c++

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

    namespace NML{
        /** @brief 基本数据类型 */
        typedef __NML_VALUE_TYPE__ var;
        /** @brief 通用下标类型 */
        typedef __NML_INDEX_TYPE__ Idx;
        /** @brief 向量和矩阵的下标类型 */
        typedef __NML_VECTOR_MATRIX_INDEX_TYPE__ Idx_VM;
        /** @brief 算数下标类型 */
        typedef __NML_ALGEBRA_INDEX_TYPE__ Idx_Algebra;
    }
    ```


### 点云
* points 点云的坐标集合; 可选使用一维数组和二维数组存储;
* 点云访问器基类
    ``` cpp
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
            Points_Iterator(void *data, Idx_Algebra dimensional, Idx points_length):data(data), points_length(points_length), dimensional(dimensional){
                install_Data(dimensional, points_length); 
            }
            /** @brief 用下标 取点 */
            virtual var* operator[](int v) = 0; 
            /** @brief 装配 new data */
            virtual void install_Data(Idx_Algebra dimensional, Idx points_length) = 0; 
            /** @brief 释放data数据 */
            virtual void free_Data () = 0;
        };
    ```
* 使用两种迭代器类 Points_Iterator__1DList, Points_Iterator__2DList 对一维数组或二维数组的点云数据进行操作
* 块链存储结构 Points_Iterator__Link ,可以运行中添加空间, 用于mesh或其它需要频繁修改长度的操作
    * 使用 成员函数 **void append_Block(Idx size)** 进行追加空间的操作, size 为追加块的 **var \*data** 的长度
    * Points_Iterator__Link 使用循环块链表存储, 其中 data 为尾块的指针
    * 单块空间大小有最大值和最小值, 使用宏定义 
    ```c++
        #define __MIN_LINK_BLOCK_SIZE__ 256
        #define __MAX_LINK_BLOCK_SIZE__ 65536
    ```
    * 点坐标数据存储在每块的data指针处, 多余的空间会被空省
    ```
        // 当前块的空间大小为14, 点维度为3
        [x0, y0, z0]
        [x1, y1, z1]
        [x2, y2, z2]
        [x4, y4, z4]
        [*,*] // 无用的两个值
    ```
    * 成员函数 **Idx calc_MaxPointsLength();** 可以计算当前已有的块空间最多能存放多少个点, 计算值将存储到成员属性 **Idx max_points_length;** 中缓存
    * 使用 points_iterator\[index\] 获取点时，如果 index >= max_points_length, 将会取到 points_iterator\[index%max_points_length\] 

### 矩阵
* *矩阵使用行优先展开的数值数组*

### 2D/3D 矩阵
* 2D变换矩阵可选使用2\*3, 3\*2, 3\*3矩阵左乘向量, 3\*3矩阵右乘向量   
``` c++
namespace NML{
    namespace Matrix_2D{
    /** 可选的2D矩阵的存储格式 */
    enum M2D_Type{
        M2D__3X3_L,   // 矩阵左边乘向量 vec * met
        M2D__3X3_R,   // 矩阵右边乘向量 met * vec
        M2D__2X3,     // 矩阵左边乘向量 vec * met 省略右侧列
        M2D__3X2      // 矩阵右边乘向量 met * vec 省略下侧行
    };
    /**
     * @brief 
        * @param type 使用的矩阵格式
        */
    void set_M2dConfig__using_matrix_type(M2D_Type type);
    }
}
```
* 3D的也和2d类似
具体矩阵左乘向量还是右乘向量   
**注意, 3d矩阵不建议使用省略行列的存储, 因为如透视投影矩阵等是需要右(下)侧行(列)的!**
``` c++
namespace NML{
    namespace Matrix_3D{
    /** 可选的3D矩阵的存储格式 */
    enum M3D_Type{
        M3D__4X4_L,   // 矩阵左边乘向量 vec * met
        M3D__4X4_R,   // 矩阵右边乘向量 met * vec
        M3D__3X4,     // 矩阵左边乘向量 vec * met 省略右侧列
        M3D__4X3      // 矩阵右边乘向量 met * vec 省略下侧行
    };
    /**
     * @brief 
        * @param type 使用的矩阵格式
        */
    void set_M2dConfig__using_matrix_type(M3D_Type type);
    }
}
```
* 左乘( \_L )和右乘( \_R )的区别
```ts
//以2d举例

    //线性变换使用 矩阵左乘向量(后缀_L), 即变换时 vec * mat
    //向量是横向量(行向量), 拓展为 
    [x, y, 1]
    //变换矩阵的齐次坐标在矩阵下侧
    [
    mat_value_a,   mat_value_b,   0,
    mat_value_c,   mat_value_d,   0,
    translate_x,   translate_y,   1
    ]
    // 省略右侧列 (0, 0, 1) 即为 2*3 矩阵
    

    //线性变换使用 矩阵右乘向量(后缀_R)时, 即变换时 mat * vec
    //向量是纵向量(列向量), 拓展为 
    [
    x,
    y,
    1
    ]
    //变换矩阵的齐次坐标在右侧, 矩阵是对应左乘时的转置
    [
    mat_value_a,   mat_value_c,   translate_x,
    mat_value_b,   mat_value_d,   translate_y,
    0,             0,             1
    ]
    // 省略下侧行 (0, 0, 1) 即为 3*2 矩阵

```

### 四元数
* *四元数结构为 \[x, y, z, w\]*

### 欧拉角
* 欧拉角数值是[r1, r2, r3]三个旋转弧度值, 进行欧拉角相关计算时需要另外追加旋转顺序的参数, 默认顺序为 xyz;   
定义的十二种顺序   
    ```c++
    /** 欧拉角旋转顺序 */
    enum Rotation_Order{
        XYZ=0b000110,    XYX=0b000100,    XZY=0b001001,    XZX=0b001000,
        YXZ=0b010010,    YXY=0b010001,    YZX=0b011000,    YZY=0b011001,
        ZXY=0b100001,    ZXZ=0b100010,    ZYX=0b100100,    ZYZ=0b100110
    };
    ```



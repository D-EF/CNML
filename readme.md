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
## 所有旋转量默认为逆时针

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
  * 声明变量时指针或引用符号(*&) 在只有一个变量名时往类型名靠; 在一次声明多个变量时往变量名靠;
    ``` cpp
      int* fnc(int* list, int length){
        int *rtn=list, i;
        for(i=0; i<length; ++i){
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
      idx_mat__uv //矩阵对应uv坐标的物理下标
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

  * 对类型的说明和命名无法一目了然的枚举常量、全局变量，应该有说明, 如果命名很短且明确的清楚这个变量的意义可以省略注释;
  * 命名比较长的时候(超过两个单词), 通常需要阅读命名并尝试理解, 更建议使用注释以令编辑器的题词器和说明得以工作
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
        
    ```


  * 函数声明的时候都应该写注释, 其中起码要包括函数的说明、参数的说明和可能存在的限制、返回值说明、可能产生的抛出异常和说明;     
    ``` cpp
        /**
         * @brief 函数的大体说明
         * @param param 参数的说明
         * @throw 函数可能产生的抛出异常的类型和说明
         * @return 函数返回值的说明
         */
        int fnc(int param){
            // (code...)
        }
    ```

  * 在比较复杂函数代码实现里加一点注释说明当前操作处于算法的哪个步骤
    ``` cpp
        void fnc(/*params...*/){
            // (步骤1)
            // (code...)

            // (步骤2)
            // (code...)

            // (步骤3)
            // (code...)

            //...
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
  * r              : 读(read)
  * w              : 写(write)
  * op/ed          : 起始/结束(open/end)
  * idx            : 索引/下标 ( index )
  * vec            : 向量 ( vector )
  * mat            : 矩阵 ( matrix )
  * m2d            : 2D矩阵 ( matrix two dimensional )
  * m3d            : 3D矩阵 ( matrix three dimensional )
  * det            : 行列式 ( determinant )
  * dimensional    : 维度
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
  * prev           : 前一个 (previous)
  * tgt            : 目标 (target)
  * now            : 当前 (指针/节点)
  * origin         : 源/起点/初始值
  * src            : 来源/源代码/溯源
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
  * stand back         : 靠后排列
  * rape copy          : 强制覆盖
  * empty              : 置空
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
* points 点云的坐标集合; 可选使用一维数组和块状链表;
* 点云访问器基类 Points_Iterator
    * 一维线性表存储结构 Points_Iterator__1DList , 用于不常修改长度的情景, 开销更小.
    * 块状链表存储结构 Points_Iterator__LinkBlock ,可以运行中更灵活地修改空间, 用于mesh或其它需要频繁修改长度的操作; 详细说明见 doc/Link_Block.md

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



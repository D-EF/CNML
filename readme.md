# CNML 
* **Nittle Math Library 的 c++ 实现**   
开发中   
文档最后编辑于 2023-05-06
---

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
    Values
    Matrix_3D
    ```
### 变量、形参
  * 小写字母下划线命名
    ```
    index_mat__uv //矩阵对应uv坐标的物理下标
    ```
### 函数
  * 小驼峰的动词单词动词短语 + 下划线 + 大驼峰
    ```
    calc_Det__Transformation  //使用初等变换消元法计算行列式
    ```

---

## 部分命名解释和缩写
### 名词
  * NML     : 库的名字( Nittle Math Library )
  * vec     : 向量 ( vector )
  * mat     : 矩阵 ( matrix )
  * m2d     : 2D矩阵 ( matrix two dimensional )
  * m3d     : 3D矩阵 ( matrix three dimensional )
  * det     : 行列式 ( determinant )
  * u       : u 坐标 (水平坐标)
  * v       : v 坐标 (垂直坐标)
  * quat    : 四元数 ( quaternion )

### 动词和动词短语
  * get              : 获取属性
  * dot              : 在向量运算中表示向量点乘
  * cross            : 在向量运算中表示叉乘
  * mapping          : 映射为
  * clac             : 计算求值
  * setup            : 执行装载操作 (初始化为)
  * transformation   : 矩阵基本变换
  * transform        : 矩阵线性变换

---

## 部分数据结构说明
* 绝大部分数据结构都使用线性结构的数组表示
  ### 数值类型
  * 宏 **\_\_NML_VALUE_TYPE\_\_** 定义了全局中使用的基本类型,默认为单浮点(float);   
  命名空间 NML 中所有数值的类型都使用 **var** 表示
    ```c++
    #ifndef __NML_VALUE_TYPE__
        #define __NML_VALUE_TYPE__ float
    #endif
    
    namespace NML{
      typedef __NML_VALUE_TYPE__ var;
    }
    ```

  ### 矩阵
  * *矩阵使用行优先展开的数值数组*

  ### 2D/3D 矩阵
  * 2D变换矩阵可选使用2\*3,3\*2,3\*3矩阵左乘向量,3\*3矩阵右乘向量   
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
      [x,y,1]
      //变换矩阵的齐次坐标在矩阵下侧
      [
        mat_value_a,   mat_value_b,   0,
        mat_value_c,   mat_value_d,   0,
        translate_x,   translate_y,   1
      ]
      // 省略右侧列 (0,0,1) 即为 2*3 矩阵
      

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
      // 省略下侧行 (0,0,1) 即为 3*2 矩阵

    ```

  ### 四元数
  * *四元数结构为 \[x,y,z,w\]*

  ### 欧拉角
  * 欧拉角数值是[r1,r2,r3]三个旋转弧度值, 进行欧拉角相关计算时需要另外追加旋转顺序的参数, 默认顺序为 xyz;   
  定义的十二种顺序   
      ```c++
      const 
          XYZ, XYX, XZY, XZX,   
          YXZ, YXY, YZX, YZY,   
          ZXY, ZXZ, ZYX, ZYZ;
      ```


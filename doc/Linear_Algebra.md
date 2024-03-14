# 简单的线性代数与几何
最后编辑于 2024-01-04   

本文中所有作为下标的代数均为正整数   

## 向量 Vector

### 存储
向量是表示方向的量, 在不同维度的下向量的数据长度有所不同；   
记录时以轴的顺序记录在不同轴上的坐标 : { x(第0轴的坐标) , y(第1轴的坐标), z(第2轴的坐标)....}   
代码中使用数值的指针并携带长度属性代替大部分的向量参数, 例 : 
``` cpp
    // 向量模长
    var mag(Idx_VM length, var*& vec);
```

### 向量的基本运算
#### 模 mag
* 向量的模(mag)是指向量的坐标到原点的距离, 用勾股定理即可求;
* 2D向量(x,y) 的模(mag) : $ mag=\sqrt{x^2+y^2} $
* n维度向量 $ v=(v_0,v_1,v_2,...,v_{n-1}) $ 的模(mag) : 
  $$
  mag=|v|=\sqrt{\sum_{i=0}^{n-1}{{v_i}^2}}
  $$
*   ```
    var mag(Idx_VM length, var*& vec){
        var rtn_squares=0;
        for(Idx_VM i=0; i<length; ++i) rtn_squares+=vec[i]*vec[i];
        return sqrt(rtn_squares);
    }
    ```
* mag = 1 的向量称为单位向量, 将一个向量 (v) 变成单位向量时的过程成为向量标准化, 记作 $ ||v|| $
    $$
    ||v|| = (\frac{v_0}{mag}, \frac{v_1}{mag}, \dots, \frac{v_{n-1}}{mag})
    $$

#### 向量加减 sum / dif
* 向量加减在几何上表示原向量正向或反向平移偏移量后得到新向量, 在运算时只需要将所有对应维度的值相加或相减
* 原向量:( $ v_0=(v_{0_0}  , v_{0_1}  , v_{0_2}  , ... , v_{0_{n-1}}) $ )   
  偏移量:( $ v_1=(v_{1_0}  , v_{1_1}  , v_{1_2}  , ... , v_{1_{n-1}}) $ )   
  新向量:
  $$
  F_{sum}(v_0,v_1)=v_0+v_1=(v_{0_0}+v_{1_0}, v_{0_1}+v_{1_1}, v_{0_2}+v_{1_2}, ... , v_{0_{n-1}}+v_{1_{n-1}})
  $$
  $$
  F_{dif}(v_0,v_1)=v_0-v_1=(v_{0_0}-v_{1_0}, v_{0_1}-v_{1_1}, v_{0_2}-v_{1_2}, ... , v_{0_{n-1}}-v_{1_{n-1}})
  $$
*   ```
    void sum(var*& out, Idx_VM length, var*& vec_0, var*& vec_1){
        for(Idx_VM i=0; i<length; ++i) out[i]=vec_0[i]+vec_1[i];
    }
    void dif(var*& out, Idx_VM length, var*& vec_0, var*& vec_1){
        for(Idx_VM i=0; i<length; ++i) out[i]=vec_0[i]-vec_1[i];
    }
#### 向量乘标量 np
* 向量乘标量在几何上表示多个相同的向量相加, 在运算时只需要将所有维度的值乘以标量
* 原向量: ( $ v=(v_{0_0}  , v_{0_1}  , v_{0_2}  , ... , v_{0_n-1}) $ ) 乘以标量 ( $ k $ )   
  新向量: 
  $$
    F_{np}(k,v)=kv=(kv_{0_0}  , kv_{0_1}  , kv_{0_2}  , ... , kv_{0_n-1})
  $$
* ```
    void np(var*& vec, Idx_VM length, var k){
        for(Idx_VM i=0; i<length; ++i) vec[i]*=k;
    }
  ```

#### 向量点积 dot
* 向量点积计算时需要将两个向量所有对应维度相乘后再相加
* 向量0:( $ v_0=(v_{0_0}  , v_{0_1}  , v_{0_2}  , ... , v_{0_n-1}) $ )   
  向量1:( $ v_1=(v_{1_0}  , v_{1_1}  , v_{1_2}  , ... , v_{1_n-1}) $ )   
  向量点积 : 
  $$
  F_{dot}(v_0,v_1)=v_0·v_1=\sum_{i=0}^{n-1}{v_{0_i}v_{1_i}}
  $$
* 向量点积的几何应用 :   
  * 点积可以表示点在另一个点上的投影系数(t)与模的乘积 : $ dot=t_1|v_1| $ ;   
  * 由此可以用于计算点( $ v_0 $ )在另一个点( $ v_1 $ )上的投影的坐标( $ v $ ) : 
    $$
    F_{projection'point}(v_0,v_1)=\frac{(v_0·v_1)}{|v_1|}
    $$
  * 使用点积计算两个向量夹角的cos值
    $$
      F_{cosΘ}(v_0,v_1)=\frac{(v_0·v_1)}{|v_0||v_1|}
    $$

#### 向量叉积 cross
* 向量叉积仅适用于2D或3D中
* 几何意义和公式
  * 叉积表示一个向量以某方向旋转到另一个向量时的旋转轴
  * 当叉积为0时, 表示两个向量处于同一直线上
  * 2D 叉积, 旋转轴总是在一个虚构的z轴上, 所以直接可以使用一个标量表示, 以叉积的正负表示旋转方向; 
    起始向量(叉积左向量) ( $ v_0 $ ), 终点向量(叉积右向量) { $ v_1 $ } 
    $$
    F_{cross}(v_0,v_1)=v_0×v_1=v_{0_x}v_{1_y}-v_{0_y}v_{1_x}
    $$
    
    ```
    +y
    ^ 
    |*v_0 {1,2}
    |
    |     *v_1 {2,1}
    +------------> +x

    此处有两点处于坐标系中, 其中x在水平方向的右方向, y在垂直方向的上方向, 虚拟的z在注视内容时的前方向; 
    v_0={1,2}, v_1={2,1}; cross=1*1-2*2=-3;
    此时叉积值为负数, v_0->v_1为顺时针
    ```
  * 3D 叉积, 叉积为一个新的向量, 表示旋转时的旋转轴   
    起始向量(叉积左向量) ( $ v_0 $ ), 终点向量(叉积右向量) { $ v_1 $ } 
    $  
    F_{cross}(v_0,v_1)=v_0×v_1=\begin{pmatrix}
       v_{0_y}v_{1_z} - v_{0_z}v_{1_y} \\
       v_{0_z}v_{1_x} - v_{0_x}v_{1_z} \\
       v_{0_x}v_{1_y} - v_{0_y}v_{1_x} \\
    \end{pmatrix}
    $$

## 矩阵 Matrix

### 存储
代码中使用数值的指针并携带宽高属性代替大部分的矩阵参数, 例 : 
``` cpp
    // 设置单位矩阵
    var*& setup_Matrix__Identity(var*& out, Idx_VM width, Idx_VM height);
```
* 下标位置   
    * 本文中, 矩阵下标通常以水平坐标 (u) 和垂直坐标 (v) 表示 ( $ M_{u,v} $ ) , 本文中所有下标均以0为起点;    
    如此矩阵M中0列2行的值 $ M_{0,2} $ = 6
    $$
    M=
    \begin{pmatrix}
        M_{0,0},   M_{1,0},   M_{2,0}\\
        M_{0,1},   M_{1,1},   M_{2,1}\\
        M_{0,2},   M_{1,2},   M_{2,2}\\
    \end{pmatrix}
    =
    \begin{pmatrix}
        0,1,2\\
        3,4,5\\
        6,7,8\\
    \end{pmatrix}
    $$
    * 物理数据下标计算, 需要宽度参数(w), 水平坐标(u), 垂直坐标(v) : $ F_i(w,u,v)=v*w+u $

    * 对角线位置, 水平坐标与垂直坐标相同的位置 $ M_{i,i} $

### 部分特殊的矩阵
* 方阵
    * 宽度和高度相同的矩阵
* 零矩阵
    * 特征为 矩阵中所有数值均为0
* 单位矩阵
    * 特征为 矩阵中除了对角线上的数值为1 ( $ M_{i,i} = 1 $ ), 其他数值均为0
* 正交矩阵
    * 特征为 对角线位置的值为 1, 且除了对角线位置以外的值都满足 $ M_{u,v} = -M_{v,u} $
* 上/下 三角矩阵
    * 特征为对角线上方或下方所有值为0   
       $ (v\in[0,u))\&(M_{u,v}=0) $   
       $ (v\in(u,w])\&(M_{u,v}=0) $   

### 矩阵部分计算
#### 矩阵乘法   
* 矩阵乘法需要左矩阵的宽度与右矩阵的高度相同, 新矩阵的宽为右矩阵的宽, 高为左矩阵的高
* 进行矩阵乘法时有顺序要求, 而且不满足乘法交换律;
* 执行乘法时为左行乘右列, 新矩阵的每个值都是左矩阵的对应行与右矩阵的对应列的点积
* A=左矩阵, B=右矩阵; l=左矩阵宽度=右矩阵高度; h=左矩阵高度, w=右矩阵宽度; $ F_{getRow}(M,v) $ 和 $ F_{getCol}(M,u) $ 分别为取矩阵行与取矩阵列
$$
    F_{Multiplication}(A,B)=
    \begin{pmatrix}
        A_{0,0},A_{1,0},       \dots   ,A_{l-1,0}     \\
        A_{0,1},A_{1,1},       \dots   ,A_{l-1,1}     \\
        \vdots\\
        A_{0,h-1},A_{1,h-1},   \dots   ,A_{l-1,h-1}   \\
    \end{pmatrix}
    \begin{pmatrix}
        B_{0,0},B_{1,0},       \dots   ,B_{w-1,0}     \\
        B_{0,1},B_{1,1},       \dots   ,B_{w-1,1}     \\
        \vdots\\
        B_{0,l-1},B_{1,l-1},   \dots   ,B_{w-1,l-1}   \\
    \end{pmatrix}\\
    \quad\\
    =
    \begin{pmatrix}
        F_{getrow}(A,0)·F_{getCol}(B,0),   F_{getrow}(A,0)·F_{getCol}(B,1),   \dots   ,F_{getrow}(A,0)·F_{getCol}(B,w-1)\\
        F_{getrow}(A,1)·F_{getCol}(B,0),   F_{getrow}(A,1)·F_{getCol}(B,1),   \dots   ,F_{getrow}(A,1)·F_{getCol}(B,w-1)\\
        \vdots\\
        F_{getrow}(A,h-1)·F_{getCol}(B,0),   F_{getrow}(A,h-1)·F_{getCol}(B,1),   \dots   ,F_{getrow}(A,h-1)·F_{getCol}(B,w-1)\\
    \end{pmatrix}
$$

#### 矩阵转置   
* 矩阵转置就是把矩阵的水平方向和垂直方向交换, 新矩阵的高度为原矩阵的宽度, 新矩阵的宽度为原矩阵的高度
$$
    F_{transposition}(M)=M^t=
    \begin{pmatrix}
        M_{0,0},M_{1,0},       \dots   ,M_{w-1,0}     \\
        M_{0,1},M_{1,1},       \dots   ,M_{w-1,1}     \\
        \vdots\\
        M_{0,h-1},M_{1,h-1},   \dots   ,M_{w-1,h-1}   \\
    \end{pmatrix}^t=
    \begin{pmatrix}
        M_{0,0},M_{0,1},       \dots   ,M_{0,h-1}     \\
        M_{1,0},M_{1,1},       \dots   ,M_{1,h-1}     \\
        \vdots\\
        M_{w-1,0},M_{w-1,1},   \dots   ,M_{w-1,h-1}   \\
    \end{pmatrix}
$$

#### 基本变换   
* 基本变换分为 换行/ 换列 / 行乘标量 / 列乘标量
* 具体代码实现请翻阅代码 NML_Matrix.hpp , NML_Matrix.cpp

#### 矩阵行列式   
* 矩阵行列式计算时要求矩阵应该是方阵
* 矩阵行列式几何意义上用于表示线性变换对原对象的规模(体积/面积)影响, 如原对象的体积为 v , 使用变换矩阵的行列式为 d, 则变换后的对象体积为 v·d
* 本文中, 计算矩阵行列式时使用两种方法, 分别为对 4 阶以及更小规模的方阵使用化简后的快速计算公式, 以及更高阶矩阵使用高斯消元法进行计算
* 快速计算公式:
    * 2阶方阵行列式快速计算公式
    $$
        M=\begin{pmatrix}
        m_0,m_1 \\
        m_2,m_3 \\
        \end{pmatrix}
        \\
        \quad
        \\
        F_{det2}(M) = |M| = m_0m_3-m_1m_2;
    $$
    * 3阶方阵行列式快速计算公式
    $$
        M=\begin{pmatrix}
        m_0,m_1,m_2 \\
        m_3,m_4,m_5 \\
        m_6,m_7,m_8 \\
        \end{pmatrix}
        \\
        \quad
        \\
        F_{det3}(M) = |M| = \\
        m_0(m_4m_8 - m_5m_7) - \\
        m_1(m_3m_8 - m_5m_6) + \\
        m_2(m_3m_7 - m_4m_6) ;\quad
    $$
    * 4阶方阵行列式快速计算公式
    $$
        M=\begin{pmatrix}
        m_{0},m_{1},m_{2},m_{3} \\
        m_{4},m_{5},m_{6},m_{7} \\
        m_{8},m_{9},m_{10},m_{11} \\
        m_{12},m_{13},m_{14},m_{15} \\
        \end{pmatrix}
        \\
        \quad
        \\
        temp=\begin{pmatrix}
            t_{0}  = m_{0}  * m_{5}  - m_{1}  * m_{4}    \\
            t_{1}  = m_{0}  * m_{6}  - m_{2}  * m_{4}    \\
            t_{2}  = m_{0}  * m_{7}  - m_{3}  * m_{4}    \\
            t_{3}  = m_{1}  * m_{6}  - m_{2}  * m_{5}    \\
            t_{4}  = m_{1}  * m_{7}  - m_{3}  * m_{5}    \\
            t_{5}  = m_{2}  * m_{7}  - m_{3}  * m_{6}    \\
            t_{6}  = m_{8}  * m_{13} - m_{9}  * m_{12}   \\
            t_{7}  = m_{8}  * m_{14} - m_{10} * m_{12}   \\
            t_{8}  = m_{8}  * m_{15} - m_{11} * m_{12}   \\
            t_{9}  = m_{9}  * m_{14} - m_{10} * m_{13}   \\
            t_{10} = m_{9}  * m_{15} - m_{11} * m_{13}   \\
            t_{11} = m_{10} * m_{15} - m_{11} * m_{14}   \\
        \end{pmatrix}
        \\
        \quad
        \\
        F_{det4}(M) = |M| = t_{0}t_{11} - t_{1}t_{10} + t_{2}t_{9} + t_{3}t_{8} - t_{4}t_{7} + t_{5}t_{6} ;
    $$
* n阶方阵(M) 消元法求行列式步骤
    $$
        M= \begin{pmatrix}
            A_{0,0},A_{1,0},       \dots   ,A_{n-1,0}     \\
            A_{0,1},A_{1,1},       \dots   ,A_{n-1,1}     \\
            \vdots\\
            A_{0,n-1},A_{1,n-1},   \dots   ,A_{n-1,n-1}   \\
        \end{pmatrix}
    $$
    * 使用基本变换和消元, 从左上开始, 右下结束 ( $ i=0; i\in[0,n); i+=1 $ )
        * 当 $ M_{i,i}=0 $ 时, 向下查找并尝试使用矩阵基本变换的换行操作使 $ M_{i,i}\not=0 $ ; 如果无法完成, 则矩阵行列式为 0
        * 缓存矩阵M的第i行上所有值与 $ \frac{1}{M_{i,i}} $ 的积
        $$
            t=(\frac{A_{0,0}}{M_{i,i}},\frac{A_{1,0}}{M_{i,i}},...,\frac{A_{w-1,0}}{M_{i,i}})\\
        $$
        * $ j\in(i,n) $ , 将矩阵的所有j行与t的倍数相加, 使 $ M_{i,j} = 0 $$ 
        * 回到第一步, 再次计算直到完成结束条件
    * 最后会得到一个上三角矩阵 ( $ M' $ ), 矩阵的行列式为该上三角矩阵的对角线上的值的乘积
    $$
    det=\prod_{i=0}^n M'_{i,i}
    $$
*  n阶方阵(M) 消元法求行列式代码实现
    ``` cpp
    
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
    bool transformation__ExchangeRow_ToUnZero(var*& mat, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length){
        Idx_VM f=step_length>0?1:-1;
        Idx_VM v_target=v+f;
        for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
            if(check_Zero(mat[i])){
                // transformation__ExchangeRow 是初等变换的换行操作, 具体实现请翻阅代码 NML_Matrix.hpp , NML_Matrix.cpp 
                transformation__ExchangeRow(mat, width, v, v_target);
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief 使用初等变换计算行列式;
        * 应在n>4时才使用, n<4时推荐使用 calc_Det__${n}
        * 
        * @param mat       矩阵数据 (必须是方阵)
        * @param n         表示这个矩阵是n*n方矩阵
        * @return 返回计算的行列式值 
        */
    var calc_Det__Transformation(var*& mat, Idx_VM n){
        const Idx_VM length=n*n;
        var *temp_mat=create_Values__Clone(mat, length);
        var temp, det=1;
        Idx_VM _n=n-1;

        for(Idx_VM uv=0; uv<_n; ++uv){
            Idx_VM idx_v=uv*n;
            Idx_VM idx_mat__uv=idx_v+uv;
            
            if(check_Zero(temp_mat[idx_mat__uv])){    // 换行
                if(!transformation__ExchangeRow_ToUnZero(temp_mat, length, n, idx_mat__uv, uv, n)){
                    delete temp_mat;
                    return 0;
                }
                else det=-det;
            }
            
            // 消元
            for(Idx_VM index=idx_mat__uv+n;  index<length;  index+=n){
                temp=(temp_mat[index])/temp_mat[idx_mat__uv];
                for(Idx_VM i=uv+1, j=index+1;  i<n;  ++i, ++j){
                    temp_mat[j]-=temp*temp_mat[idx_v+i];
                }
            }
            det*=temp_mat[idx_mat__uv];
        }
        det*=temp_mat[length-1];

        delete temp_mat;

        return det;
    }
        
    ```
        
#### 余子式 / 代数余子式 / 标准伴随矩阵   
* 原矩阵中剔除某个元素的行和列后余剩的其他元素称为余子式矩阵, 余子式矩阵的宽高为原矩阵的宽高减一, 这个矩阵的行列式就是余子式
* 代数余子式 = 余子式 * $ -1^{u+v} $
* 例 :
$$
原矩阵M=
\begin{pmatrix}
    M_{0,0},   M_{1,0},   M_{2,0}\\
    M_{0,1},   M_{1,1},   M_{2,1}\\
    M_{0,2},   M_{1,2},   M_{2,2}\\
\end{pmatrix}
\\
\quad
\\
矩阵M的元素M_{0,0}的余子式矩阵 Q=
\begin{pmatrix}
    M_{1,1},   M_{2,1}\\
    M_{1,2},   M_{2,2}\\
\end{pmatrix}
\\
\quad
\\
矩阵M的元素M_{0,0}的代数余子式 = (-1)^{0+0}Q
$$
* 原矩阵中的每个值的代数余子式组成一个新的矩阵就是标准伴随矩阵 ( $ adj(M) $ );
#### 矩阵的逆   
* 矩阵的逆和行列式一样, 计算时要求矩阵应该是方阵; 当矩阵的行列式=0 时, 逆矩阵不存在
* 矩阵 ( $ M $ ) 的逆 (逆矩阵) ( $ M^{-1} $ ) , 原矩阵和逆矩阵相乘会得到一个单位矩阵 ( $ I $ ); 几何意义上逆矩阵用于还原一个进行过线性变换的对象
$$
    M^{-1}m=MM^{-1}=I
$$
* 本文中求矩阵的逆由两种方式组成, 分别为对 4 阶以下的方阵使用 标准伴矩阵 / 行列式 ( $ \frac{adj(M)}{|M|} $ ) 进行比较简单的计算 , 以及对更高阶的矩阵使用高斯消元法
* 高斯消元法 求逆矩阵操作与求行列式有些相似之处; 步骤如下
    * 建立增广矩阵 ( $ M' $ ), 初始化为与原规模相同的单位矩阵
    * 从原矩阵左上开始, 右下结束 ( $ i=0; i\in[0,n); i+=1 $ )
        * 当 $ M_{i,i}=0 $ 时, 向下查找并尝试使用矩阵基本变换的换行操作使 $ M_{i,i} $ 为同列元素中绝对值最大的 ; 如果无法满足 $ M_{i,i}\in=0 $$, 则矩阵行列式为 0, 逆矩阵不存在
        * 缓存 M 和 M' 的第i行上所有值与 $ \frac{1}{M_{i,i}} $ 的积
        * $ (j\not=i)\&j\in[0,n) $ , 将矩阵的所有j行与t的倍数相加, 使 $ M_{i,j} = 0 $$ 
        * 回到第一步, 再次计算直到完成结束条件
    * 计算完成后, M 将会变成单位矩阵, 而 M' 就是原矩阵的逆
* 消元法求逆矩阵代码实现
    ``` cpp

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
        * @param  _idx_m     传入多个矩阵时使用哪个矩阵的值 默认0
        * @return 返回是否成功换行
        */
    bool transformation__ExchangeRow_PivotToMax(var**& mats, Idx_VM length_g, Idx_VM length, Idx_VM width, Idx_VM index, Idx_VM v, Idx_VM step_length, Idx_VM _idx_m){
        Idx_VM f=step_length>0?1:-1;
        Idx_VM v_target=v+f;
        
        Idx_VM max_row=v;
        Idx_VM max_row_pivot_index=index;
        for(Idx_VM i=index+step_length;  i>=0&&i<length;  i+=step_length, v_target+=f){
            if(mats[_idx_m][max_row_pivot_index]<mats[_idx_m][i]){
                max_row_pivot_index=i;
                max_row=v_target;
            }
        }
        if(check_Zero(mats[_idx_m][max_row_pivot_index])){
            return false;
        }
        if(v!=max_row) transformation__ExchangeRow(mats, length_g, width, v, max_row);
        return true;
    }


    /**
     * @brief 矩阵求逆 使用初等变换法(高斯乔丹消元法)
        * 
        * @param out       输出目标
        * @param mat       矩阵数据 (必须是方阵)
        * @param n         表示这个矩阵是n*n方阵
        * @return 返回是否成功计算逆矩阵
        */
    bool setup_Matrix__Inverse__Transformation(var*& out, var*& mat, Idx_VM n){
        Idx_VM length=n*n;
        var *temp_mat=create_Values__Clone(mat, length);
        
        // 初始化 out 为增广矩阵
        setup_Matrix__Identity(out, n, n);
        var **mats=new var*[2]{temp_mat, out};
        
        for(Idx_VM uv=0; uv<n; ++uv){
            Idx_VM idx_v=uv*n;
            Idx_VM idx_mat__uv=idx_v+uv;

            // 换行设置最大主元
            if(!transformation__ExchangeRow_PivotToMax(mats, 2, length, n, idx_mat__uv, uv, n)) {
                delete temp_mat;
                delete mats;
                return false;
            }
            transformation__ScaleRow(mats, 2, n, uv, 1/mats[0][idx_mat__uv]);

            for(Idx_VM i=0, index=0;  i<n;  ++i, index+=n){
                if(i==uv) continue;
                var k=temp_mat[index+uv];
                for(Idx_VM j=0;  j<n;  ++j){
                    temp_mat[index+j] -= k * temp_mat[idx_v+j];
                    out[index+j]      -= k * out     [idx_v+j];
                }
            }
        }

        delete temp_mat;
        delete mats;
        return true;
    }

    ```
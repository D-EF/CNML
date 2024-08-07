# Bezier 贝塞尔曲线部分数学和代码实现
最后编辑于 2024-01-10

* 本文仅用于快速了解贝塞尔曲线的部分应用代码实现和小部分简单的数学, 如果想要更详细地学习相关数学内容, 建议查阅更详细的文档或书籍. 比如我曾经学习时看的就是这部 [A Primer on Bézier Curves](https://pomax.github.io/bezierinfo/);
* 在有些算法中可能会有修改某个控制点的曲率等操作, 但是本文中不会出现这种情况, 所有控制点的曲率都为 1 ;

## 贝塞尔曲线 数据类型
* 贝塞尔曲线 以 *点云访问器 ( Points_Iterator )*  保存; Points_Iterator的数据结构说明见 [readme.md](../readme.md)
* 方案1: 使用各个维度的各次幂系数作为存储格式; 因为可以快速进行采样点/求导等计算, 所以大部分函数都使用该方案
    ```
    +------> d维度
    | 
    | 
    v
    n次幂的系数
    ```
    $$
        C = \begin{pmatrix}
            C_{0,0},   C_{1,0},   \dots   ,C_{d-1,0}   \\
            C_{0,1},   C_{1,1},   \dots   ,C_{d-1,1}   \\
            \vdots\\
            C_{0,n},   C_{1,n},   \dots   ,C_{d-1,n}   \\
        \end{pmatrix}
    $$
* 方案2: 保存控制点集合; 应仅在编辑/绘制图形时使用该方案, 渲染时应转换为方案1
    ```
    +------> d维度
    | 
    | 
    v
    n个控制点
    ```
    $$
        P = \begin{pmatrix}
            P_{0,0},   P_{1,0},   \dots   ,P_{d-1,0}   \\
            P_{0,1},   P_{1,1},   \dots   ,P_{d-1,1}   \\
            \vdots\\
            P_{0,n},   P_{1,n},   \dots   ,P_{d-1,n}   \\
        \end{pmatrix}
    $$

## 采样点 to 计算系数
* 想要使用采样点得到计算系数, 这个过程需要用到一些矩阵运算和推演; 本文仅作简单介绍, 另外有许多文献中都有更详细的说明 如 [贝塞尔曲线的数学原理](https://pomax.github.io/bezierinfo/zh-CN/index.html#explanation) 和 [用矩阵运算来表示贝塞尔曲率](https://pomax.github.io/bezierinfo/zh-CN/index.html#matrixsplit);

### 直接使用控制点与多项式求采样点 
* 使用多项式和控制点求采样点的公式稍微复杂一点, 因为在未知控制点个数的情况下难以仅仅使用一个编程函数来实现的, 这需要一点推导的过程
* 对于已知控制点数量的贝塞尔曲线的采样可以用多项式表示
    * 2个控制点,一阶贝塞尔(直线):       $  F_{linear}(p,t)=(1-t)P_0+tP_1 $
    * 3个控制点,二阶贝塞尔(平方曲线):   $  F_{square}(p,t)=(1-t)^2P_0+2(1-t)tP_1+tP_2 $
    * 4个控制点,三阶贝塞尔(立方曲线):   $  F_{cubic}(p,t)=(1-t)^3P_0+3(1-t)^2P_1t+3(1-t)t^2P_2+t^3P_3 $
    * $\dots$   
* 此时其实已经可以用这些公式进行化简与合并同类项的的操作将采样点转换为计算系数了, 但是需要更进一步, 因为我希望用一个函数能求得任意阶的计算系数; 所以需要找到上面那些式子的规律
    * 将上面几个式子, 忽视掉 控制点 / t / (1-t), 可以发现有一些系数, 这正是帕斯卡三角的数值
    $$
    L_{PASCALS\_TRIANGLE}=\\
    [1],\\
    [1,1],\\
    [1,2,1],\\
    [1,3,3,1],\\
    [1,4,6,4,1],\\
    [1,5,10,10,5,1],\\
    .....
    $$
    * 再看 t / (1-t) 的指数, 其实是有一个此消彼长的关系
    $$
    _{i=0}^n:(1-t)^{i}t^{n-i}
    $$
* n个控制点, n-1阶贝塞尔曲线: 先取出对应的一行帕斯卡三角 $ L'=L_{PASCALS\_TRIANGLE}(n) $ 然后代入下面这段公式
    $$
    F_{bezier}(n,p,t)=\sum_{i=0}^{n}L'_i(1-t)^{n-i}t^{i}p_i
    $$
* 这个公式想要变成程序代码的话比较复杂而且计算开销较大, 所以如果将这个公式改成简单多项式的表示, 将会更简单而且计算开销更小

### 贝塞尔曲线计算矩阵
单凭上面那些还不足以用一个函数将任意个控制点转换为对应的计算系数, 还需要一点矩阵的推导
* 将某个函数展开, 此处使用三阶曲线函数举例 $ (1-t)^3P_0+3(1-t)^2P_1t+3(1-t)t^2P_2+t^3P_3 $    
    可以得到
    $$
        (1-3t+3t^2-1t^3)   P_0   +   \\
        (3^t-6t^2+3t^3)    P_1   +   \\
        (-3t^2+3t^3)       P_2   +   \\
        (t^3)              P_3   ;   \\
    $$
* 分离t和其他数值, 可以将上面的式子记作一个矩阵乘法
    $$
    \begin{bmatrix}
    1,0,0,0 \\
    -3,3,0,0 \\
    3,-6,3,0 \\
    -1,3,-3,1 \\
    \end{bmatrix}
    ·
    \begin{bmatrix}
    p_0\\
    p_1\\
    p_2\\
    p_3\\
    \end{bmatrix}
    ·
    \begin{bmatrix}
    t^0\\
    t^1\\
    t^2\\
    t^3\\
    \end{bmatrix}
    $$
* 其中有一个没有任何代数的矩阵, 而且它是一个三角矩阵, 它的内容仅根据控制点的个数改变, 但它其实可以由一些简单的公式获得:   
    * 已有一个取帕斯卡三角某行的函数 $ L_{PASCALS\_TRIANGLE}(l) $ 下文将简称为 $ L(l) $    
    * 对一个拥有n个控制点的贝塞尔曲线, 即(n-1)阶贝塞尔曲线的计算矩阵, 它是一个下三角矩阵, 它的每个 $ M_{u,v} $ 位置的数值:
    $$ 
    M_{u,v} = (-1)^{u+v} · L(n)_u · L(u)_v
    $$

* 最后只需要将控制点 P 的坐标代入到矩阵乘法中, 即可计算出这个一元n次函数 $ \sum_{i=0}^n t^iC_i $ 的各次幂系数 $ C $ , 当要采样点时将 t 代入到上式中即可快速计算采样点;   
* 将系数还原成控制点也只需要做相应的逆运算即可;   

代码实现比较长, 如有需要请自行查看代码文件, 帕斯卡三角内容请看 [NML_Algebra](https://github.com/D-EF/CNML/blob/master/src/NML_Algebra.hpp), 贝塞尔曲线计算内容请看 [NML_Bezier](https://github.com/D-EF/CNML/blob/master/src/NML_Bezier.hpp)



## 贝塞尔曲线采样点
* 方案1使用的系数可以快速进行采样计算, 具体过程如下   
    * 采样某一维度的坐标
    $$
        C=(C_0,C_1,\dots,C_n)
        \\
        F_{sample\_Bezier\_n}(C,t) = \sum_{i=0}^n t^iC_i
    $$
    采样所有可用维度的坐标就能得到一个采样点
    ``` cpp
        /** 
         * @brief 采样贝塞尔曲线 使用各次幂的系数
         * @param out            输出目标, 采样点, 长度为 coefficients.points_length
         * @param coefficients   贝塞尔曲线各次幂系数 ( 使用 setup_BezierCoefficients 计算 )
         * @param t              时间参数t
         * @return 修改并返回 out (采样点)
         */
        var*& sample_Bezier__Coefficients(var*& out, Points_Iterator& coefficients, var t){
            Idx_Algebra &dimensional=coefficients.dimensional;
            std::fill_n(out, dimensional, 0);
            var power_t=1;
            for(Idx i=0;  i<coefficients.points_length;  ++i){
                var *line=coefficients[i];
                for(Idx_Algebra d=0;  d<dimensional;  ++d){
                    out[d]+=power_t*line[d];
                }
                power_t*=t;
            }
            return out;
        }
    ```

* 方案2使用操作点求采样点, 使用 DeCasteljau 算法, 开销较大不推荐使用
    * 步骤很简单, 就是在每个相邻的控制点组成的线段上求这个线段的 t 采样位置作为新的控制点, 每次进行这个操作后控制点就会少一个, 重复操作直到只剩一个点, 这个点就是采样点   

    ``` cpp
        /**
         * @brief 采样贝塞尔曲线    使用DeCasteljau算法 (不建议使用)
            * @param out      输出目标, 采样点 长度为 points.dimensional
            * @param points   贝塞尔曲线控制点集合 长度为 dimensional*points_length
            * @param t        时间参数 t
            * @return 修改并返回 out
            */
        var *&sample_Bezier__DeCasteljau(var*& out, Points_Iterator& points, var t){
            if(points.points_length>1){
                Points_Iterator__1DList new_points=Points_Iterator__1DList(points.dimensional, points.points_length-1);
                var td=1-t;
                for(int i=0;  i>=0;  --i){
                    var *temp_point__new=new_points[i];
                    var *temp_point__low=points[i];
                    var *temp_point__low1=points[i+1];
                    for(int j=0;  j<points.dimensional;  ++j){
                        temp_point__new[j]=td*temp_point__low[j]+t*temp_point__low1[j];
                    }
                }
                sample_Bezier__DeCasteljau(out, new_points, t);
                new_points.free_Data();
                return out;
            }else{
                for(int i=0; i<points.dimensional;  ++i){
                    out[i]=points[0][i];
                }
                return out;
            }
        }
    ```

## 曲线线性变换
* 在使用控制点时直接对点进行变换即可;
* 在使用计算系数时略有不同, 齐次坐标(平移操作) 仅对 0 次幂的系数进行操作;

## 贝塞尔曲线分割
* 具体的数学推导很复杂, 而且即使我写一遍也估计是会充斥大量的抄袭内容, 请看 [用矩阵分割曲线](https://pomax.github.io/bezierinfo/zh-CN/index.html#matrixsplit)
* 代码实现也略长, 请看 [NML_Bezier](https://github.com/D-EF/CNML/blob/master/src/NML_Bezier.hpp) 中的calc_CutBezierMatrixQ 和 cut_Bezier__ByMatrix 两个函数


## 贝塞尔曲线的导数
* 如果使用方案1 求导将会非常简单, 可以直接套用多项式的求导过程
    ``` cpp
        /**
         * 求一元n次函数集的导数
         * @param out            输出对象, 应满足 out.point_length == coefficients.point_length-1 && out.dimensional == coefficients.dimensional
         * @param coefficients   系数集合, 其中 coefficients[i] 表示 各个函数中 i 次幂的系数
         * @return 修改并返回 out, 一组新的系数表示原函数系数的导函数
         */
        Points_Iterator& setup_Derivatives__UnivariatePolynomials(Points_Iterator& out, Points_Iterator& coefficients){
            Idx_Algebra l=out.points_length, i, j, d=out.dimensional;
            for(i=1;  i<=l;  ++i){
                var* temp_out=out[i-1];
                var* temp_coefficients=coefficients[i];
                for(j=0; j<d;++j){
                    temp_out[j]=temp_coefficients[j]*i;
                }
            }
            return out;
        }
    ```

* 如果使用方案2 求导将略复杂一些, 本文仅放出实现代码, 具体数学内容请看 [导数](https://pomax.github.io/bezierinfo/zh-CN/index.html#derivatives)
    ``` cpp
        /**
         * 求贝塞尔曲线的导函数
         * @param out           输出对象 应满足 out.point_length == coefficients.point_length-1 && out.dimensional == coefficients.dimensional
         * @param ctrl_points   控制点坐标集合
         * @return 修改并返回 out, 一组新的贝塞尔曲线控制点
         */
        Points_Iterator& setup_Derivatives__BezierPoints(Points_Iterator& out, Points_Iterator& ctrl_points){
            // n 指 n阶贝塞尔曲线, 导数的控制点长度为原曲线的控制点个数-1, 导数的 n 为原曲线的控制点个数-2
            Idx_Algebra n=out.points_length-1, i, j, d=out.dimensional;
            for(i=0;i<=n;++i){
                var* temp_out = out[i];
                var* temp_0   = ctrl_points[i];
                var* temp_1   = ctrl_points[i+1];
                for(j=0;  j<d;  ++j){
                    temp_out[j] = n*(temp_1[j]-temp_0[j]);
                }
            }
            return out;
        }
    ```

## 绘制切线和法线
* 此处绘制切线和法线, 仅考虑 2D 和 3D 的绘制

### 绘制切线
* 如果要在贝塞尔曲线的某点上绘制切线, 其实就是沿导向量 ( $ V_{dt} $ ) 在相对于采样点 ( $ V_t $ ) 的位置绘制直线 , 一般使用标准向量表示向量所在的直线, 所以贝塞尔曲线上采样点的切线 ( L ) :
    $$
        V_{tangent} = ||V_{dt}||+V_t;\\
        \\
        L = V_t \Leftrightarrow V_{tangent}
    $$

### 绘制法线
* 贝塞尔曲线上某点的法线, 则需要沿着导向量的垂直方向 $ V_{nt} $ 相对于采样点 $ V_{t} $ 绘制直线; 贝塞尔曲线上采样点的法线 ( L ) :
    $$
        V_{normal}=F_{vertical}(||V_{nt}||)+V_t;
        \\
        L = V_t \Leftrightarrow V_{normal}
    $$
* 上式中, 函数 $ F_{vertical}(V) $ 是用于计算向量的垂直向量的函数; 
* 对于 2D 图形, 这个函数可以简单地使用一个旋转 $ 90deg $ ( $ 0.5\pi $ ) 的矩阵变换实现;
* 但是在绘制 3D 时, 就会出现一个问题: 3D 空间中一条直线的某个点上可能有无数条垂线! 所以如果要绘制一条 3D 贝塞尔曲线的法线时必须要另外使用一个有效的旋转轴; 有各种方法可以得到不同的旋转轴, 此处仅举例一部分比较简单的
    * 使用固定旋转轴, 如起点到终点的直线
    * 用相对于当前采样点 ( $ V_1 $ ) 的上一个采样点 ( $ V_0 $ ) 与下一个采样点 ( $ V_1 $ ) 的叉积
    $$
        (V_0-V_1) \times (V_2-V_1)
    $$
    * 用当前点的导向量 ( $ V_{dt1} $ ) 和下一个点的导向量 ( $ V_{dt2} $ ) 的叉积
    $$
        V_{dt1} \times V_{dt2}
    $$
    * [最小化标架](https://pomax.github.io/bezierinfo/zh-CN/index.html#pointvectors3d)
* 由于 3D 中绘制法线可能有很多不同的结果, 所以很多时候这个法线的重要性都略低, 仅在网格化时使用


## 获取轴对齐包围盒 ( AABB : Axis Aligned Bounding Box )
* 众所周知, 求 AABB 实际上就是在求图形在各个方向上的最大值和最小值; 
* 所以在获取贝塞尔曲线的 AABB 时, 只需要 \[ 0,1,...取值范围在0~1上的曲线每个维度上导数的根 \] 作为 t , 进行采样后比对大小即可

  * 导数根集合:                 $$  R'=\{R'_0,R'_1,R'_2,...,R'_l\} \\    $$
  * 采样点t参数集合:            $$  T'=(R'\cap(0,1))\cup\{0,1\} \\       $$
  * 某维度的采样点集合:         $$  P'=F_{sample\_Bezier\_n(C',T')} \\   $$
  * 当前维度的最大值和最小值:   $$  \max(P'), \min(P') \\                $$

* 对于次数较低的函数, 尚有公式可用; 但是当次数>3时, 就需要使用迭代法求根了; 而且大多情况下还需要求更高阶的导数的根, 此处求一元多项式函数的根的过程比较繁琐, 已经另外建了一个文件专门编写这个内容, 请看[Find_Root_In_Univariate_Polynomials.md](https://github.com/D-EF/CNML/blob/master/doc/Find_Root_In_Univariate_Polynomials.md)


## 给定某一维度的坐标k, 求可用点的t值
* 首先需要抽离这一维度的计算系数, 得到一个多项式的系数集合, 然后在0次幂的系数需要减去k, 最后对这个多项式进行求根;
    $$
    C={C_0-k, C_1, C_2, ... C_n}
    $$
 

## 贝塞尔曲线的长度
* 贝塞尔曲线的长度暂时没有什么公式来计算, 但是可以在曲线上采样点后组成线段路径(下文将称为多边形代理), 然后用计算这个线段路径的长度来获取贝塞尔曲线的近似长度;
* 计算这个线段路径的长度时, 建议保留多边形代理, 并额外生成一个显式查找表 ( LUT ) , 在其他一些操作中很可能会用得上;


## 线性距离插值 ( 沿着曲线匀速移动 )
* 采样时的 t 值, 与当前点在曲线中行进的距离并非正比, 所以想要点沿着曲线匀速移动并不能直接使用固定步长的 t ;
* 如果需要有一个办法求精细的插值, 其中一个方法就是使用曲线的导数进行积分, 但是这样太复杂了并不在本文的考虑范围内;
* 使用上文中计算线段路径长度时生成的 LUT 即可简单地得到近似的线性距离插值 $ t_l $ ;
* 例:
    * 生成距离的 LUT 时的 t 步长为k, 生成的 LUT 如下
    $$
    L=\{l_0,l_1,l_2,...,l_{1/k}\}
    $$
    * 输入当前距离参数 l , 在 L 中查找满足下式的位置
    $$
    l_x < l < l_{x+1}
    $$
    * 求 $ l_x \to l_{x+1} $ 中的 l 插值 $ t_l $
    $$
    t_l=k(x+\frac{l_{x+1}-l_x}{l-l_x})
    $$


## 点在曲线上的投影 (求近点)
* 求一个点在曲线上最近的点, 也需要使用数值求法, 首先需要计算多边形代理中的点与参数点 $ P $ 的距离, 得到多边形代理中的近点 $ P_{low} $;
* 计算一个t的溢出值 $ t' $  ; 如果此时 $ P_{low} $ 为起点, 则使用一个负值, 如果 $ P_{low} $ 为终点则使用一个大于1的值, 采样 $ t' $ 的坐标; 如果溢出值坐标比 $ P_{low} $ 更接近 $ P $ , 则使用 $ P_{low} $ 为近点;
* 对于曲线中间的点, 我的做法是使用这个点的前一个点和后一个点作为初始值, 进行二分法求近点;


## 2D 曲线与线段求交
* 计算曲线的与线段的交点
* 首先需要将曲线和线段同时进行线性变换, 另线段与x轴平行;
* 然后沿用 **给定某一维度的坐标k, 求可用点的t值** 的方法求出 t 值;
* 最后使用 t 值在原曲线上采样点, 判断点是否在线段上的即可.

## 曲线与曲线求交
* *本文求交使用 AABB 迭代求近似交点*
* 初始化时, 需要将曲线区分为多条单调性的曲线, 以保证迭代时不会出现 AABB 与曲线内容不匹配的情况; 
    * 求曲线的导数的根即可实现, 求得:
    $$
        T_0 = \{ t_{0'0}, t_{0'1} , ... , t_{0'l0} \};
        \\
        T_1 = \{ t_{1'0}, t_{1'0} , ... , t_{1'l1} \};
    $$
    其中 $ T_0 $ 和 $ T_1 $ 分别为两曲线的导数的根的集合, l0 和 l1 为 $ T_0 $ 和 $ T_1 $ 的长度;
* 使用 $ T_0 $ 和 $ T_1 $ 生成曲线的 AABB, 得到 $ B_0 $ 和 $ B_1 $ (两曲线拆分后的AABB集合)
* 将 $ B_0 $ 和 $ B_1 $ 进行配对并判断是否重叠,
    * 如果有重叠, 则将重叠项进行二分; 即原本由 $ \{ t_{op} , t_{ed} \} $ 生成的 AABB 替换为 $ \{ t_{op} , ((t_{op}+t_{ed})*0.5) \} $ 和 $ \{ ((t_{op}+t_{ed})*0.5) , t_{ed}  \} $ 的两份 AABB; 
    * 如果无重叠, 则剔除于配对表中;
* 重复上面的操作直到精度达标 (生成 AABB 的两个 t 值的差小于容差), 将精度达标的 AABB 的 $ (t_{op}+t_{end}*0.5) $ 作为 t 采样并添加到输出中.
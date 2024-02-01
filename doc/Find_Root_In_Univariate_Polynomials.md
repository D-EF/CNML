# 一元n次多项式函数求根

## 简述一元n次多项式函数
简单描述一下本文中的多项式和其中用到的一点知识:   

* 数学表达式:  已有系数集合 $ C =\{C_0,C_1,...,C_n\} $
    $$
        F_{UnivariatePolynomials}(x) =\\
        C_0x^0+C_1x^1+C_2x^2+ ... +C_nx^n =\\
        \sum_{i=0}^n C_ix^i
    $$

* 代码中的存储数据结构   
    一元n次多项式直接存储系数 C 内容, 使用指针和长度作为参数

* 计算多项式代码实现
    ``` c++
    /**
     * @brief 计算一元多项式
     * @param coefficients  多项式的系数
     * @param length        系数的长度
     * @param param_value   自变量参数值
     * @return 计算多项式并返回计算结果
     */
    var calc_UnivariatePolynomials(var* coefficients, Idx_Algebra length, var param_value){
        var rtn=0;
        var k=1;
        for(Idx_Algebra i=0;  i<length;  ++i){
            rtn+=coefficients[i]*k;
            k*=param_value;
        }
        return rtn;
    }
    ```

* 求导   
    $$
        F_{UnivariatePolynomials}'(x)=\\
        C_1x^0 + 2C_2x^1 + 3C_3x^2 + ... + nC_nx^{n-1}=\\
        \sum_{i=1}^{n} iC_ix^{i-1}
    $$

* 求导函数代码
    ``` c++
        /** 
         * @brief 求导一元多项式 f(t) >>> f'(dt)=d(f);
         * @param coefficients 各次幂的系数 [t^0, t^1, t^2, t^3, ...]
         * @param length_coefficients coefficients 的长度
         * @return 返回导数的各次幂的系数 [t^0, dt^1, dt^2, dt^3, ...] 长度 = length_coefficients-1
         */
        var*& setup_Derivatives__UnivariatePolynomials(var*& out, var* coefficients, Idx_Algebra length_coefficients){
            Idx_Algebra i;
            for(i=1;  i<length_coefficients;  ++i){
                out[i-1]=coefficients[i]*i;
            }
            return out;
        }
    ```

## 较低阶的多项式求根公式
* 一元一次函数求根公式   
    * 一元一次函数表示为 : $ ax + b = 0 $   
    * 求根: $ x = -b/a $

* 一元二次函数求根公式   
    * 一元二次函数表示为 : $ ax^2 + bx + c = 0 $
    * 求根公式 : $ x = (-b ± \sqrt{b^2 - 4ac}) / (2a) $   
        其中 ( $ b^2 - 4ac $ ) 为判别式 $ △ $ 
        * 当 $△>0$ 时, 函数有两个解; 
        * 当 $△=0$ 时 函数只有一个解; 
        * 当 $△<0$ 时, 函数无解

* 一元三次函数求根, 要用到 Cardano 公式, 内容比较复杂, 请自行查阅专业书籍文献   

## 迭代法寻根
使用迭代法寻根时, 需要指定一些初始化的参数, 比如使用二分法进行寻根时, 需要提供一份内部一定有实数根的区间; 又比如一个函数有很多个根的时候使用牛顿迭代法, 需要提供一些合适的初始值以避免寻到同一个根.

* 在求函数根之前需要先求当前函数的导数根, 后继操作将会用到它

* 单调区间
    * 单调区间的标记可以使用导数的根来获得, 导数根的位置就是单调区间的波峰位置;

    $$
    已按照大小排序的导数根集合 R' = [R'_0, R'_1, R'_2,...,R'_l]\\
    标记区间 [ -\infty, R'_0, R'_1, R'_2,...,R'_l, \infty ]
    $$

    * 实数区间 to 二分法
        * 如果一个单调的区间内有根, 那这个区间就只会有一个根, 这是显而易见的道理;
        * 判断此区间内是否有根, 只需要判断这个区间的首尾位置的值是否异号即可;
        $$
            i\in [0,l)\\
            F_{UnivariatePolynomials}(R'_i)>0 \ne F_{UnivariatePolynomials}(R'_{i+1})>0
        $$
        * 当上式成立时即可使用区间 $ [R'_i, R'_{i+1}] $ 进行二分法寻根
    
    * 在区间 $ [-\infty, R'_0] $ 与 $ [R'_l,\infty] $ 中寻根
        * 寻根前首先必须要判断这两个区间内是否有根, 根据函数图象与最高次项的指数和系数可以清晰的观察到以下几个结论
            * 当最高次数项的系数为正数时, $ [R'_l,\infty] $ 为单调增;
            * 当最高次数项的系数为负数时, $ [R'_l,\infty] $ 为单调减;
            * 当最高次数项的指数为奇数时, 这两个区间的单调性相同;
            * 当最高次数项的指数为偶数时, 这两个区间的单调性相反;

        * 当 $ [-\infty, R'_0] $ 为单调减时, $ F_{UnivariatePolynomials}(R'_0) < 0 $ 表示这个区间有根, 可以使用 ( $ R'_0 - 1 $ ) 初始化(避免出现导数为0的情况) 进行牛顿迭代法寻根, 反之亦然;
        * 当 $ [ R'_l, \infty] $ 为单调增时, $ F_{UnivariatePolynomials}(R'_l) < 0 $ 表示这个区间有根, 可以使用 ( $ R'_l + 1 $ ) 初始化(避免出现导数为0的情况) 进行牛顿迭代法寻根, 反之亦然;

        * 由于考虑到牛顿迭代法要计算导数, 可能开销会大一点, 所以在上述的寻根过程中, 可以在适当的情况下转换成使用二分法寻根;

    * 当 $ R = \varnothing $ 时, 直接任选一个值初始化进行牛顿迭代法即可;

* 代码实现比较长, 请看[NML_Algebra](https://github.com/D-EF/CNML/blob/master/src/NML_Algebra.hpp)

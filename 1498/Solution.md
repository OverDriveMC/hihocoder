假设现在有T个任务,m个机器人,有如下三种选择：

1. 不复制机器人,用时 $$ t_1 = \lceil \frac{T}{m}  \rceil$$

2. 复制全部机器人,用时
   $$
   t_2= \lceil \frac{T}{2m} \rceil +q = \lceil \frac{T}{2m} +q \rceil
   $$

3. x个机器人用来工作,其余的机器人用来复制,用时

   ​
   $$
   t_3=\lceil \frac{T- xq}{2m-x } \rceil + q  = \lceil \frac{T-xq}{2m-x} +q \rceil
   $$




计算如下几个不等式成立的条件:

1. ​


1. $$
   t_1 > t_2     
   $$

   $$
   \frac{T}{m} > \frac{T}{2m}+q
   $$

   $$
   T>2qm
   $$

   意味着,当T>2qm时,全复制比不复制好.

2. ​

3. $$
   t_3> t_2
   $$


$$
\frac{T-xq}{2m-x} +q > \frac{T}{2m} +q
$$

$$
T>2qm
$$

这意味着,当T>2qm时,全复制比复制一部分好。

3.
$$
t_3 > t_1
$$

$$
\frac{T-xq}{2m -x} + q > \frac{T}{m}
$$

$$
m(T-xq) + qm(2m-x) > T(2m-x)
$$

$$
2qm(m-x) >T(m-x)
$$

$$
t<2qm
$$

这意味着,T<2qm时,不复制比复制一部分好。



综上：

* T<2qm   不复制比复制一部分好,复制一部分比全复制好
* T>=2qm时 全复制比不复制好,全复制比复制一部分好
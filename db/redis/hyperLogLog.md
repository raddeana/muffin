Redis HyperLogLog 是用来做基数统计的算法, HyperLogLog的优点是, 在输入元素的数量或者体积非常非常大时, 计算基数所需的空间总是固定的、并且是很小的
每个 HyperLogLog 键只需要花费 12 KB 内存, 就可以计算接近2^64个不同元素的基数
这和计算基数时, 元素越多耗费内存就越多的集合形成鲜明对比
HyperLogLog只会根据输入元素来计算基数, 而不会储存输入元素本身, 所以HyperLogLog不能像集合那样, 返回输入的各个元素

#### 基本命令
- PFADD key element [element ...] 添加指定元素到 HyperLogLog 中
- PFCOUNT key [key ...] 返回给定 HyperLogLog 的基数估算值
- PFMERGE destkey sourcekey [sourcekey ...] 将多个 HyperLogLog 合并为一个 HyperLogLog

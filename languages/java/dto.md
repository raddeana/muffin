#### DTO
- DTO就是数据传输对象(Data Transfer Object)的缩写
- DTO模式，是指将数据封装成普通的JavaBeans，在J2EE多个层次之间传输
- DTO类似信使，是同步系统中的Message
- 该JavaBeans可以是一个数据模型Model

Benefits:
- 依据现有的类代码, 即可方便的构造出DTO对象, 而无需重新进行分析
- 减少请求次数, 大大提高效率
- 按需组织DTO对象, 可以避免传输整个表的字段, 一定程度上提高了安全性

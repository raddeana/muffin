#### 预处理（Preprocessing）
cpp文件首先预处理变为translation unit，translation unit仍然是文本代码文件，它是传入编译器的基本单元，把cpp和h整合到了一起，并且去掉不必要的空格/换行之类的

#### 编译（Compiling）
translation unit传入编译器（compiler）之后会被编译成obj文件（二进制）

#### 链接（Linking）
如果不依赖动态链接库或静态链接库，链接就是把所有obj链接；如果还依赖外部库，链接还包括lib文件

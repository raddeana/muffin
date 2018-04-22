#### Shell 程序设计过程
Shell 语言作为解释型语言，它的程序设计过程跟编译型语言有些区别，其基本过程如下：
- 设计算法
- 用 Shell 编写脚本程序实现算法
- 直接运行脚本程序

#### BASH 的调试手段
- echo/print 
```sh
_loglevel=2
DIE() {
    echo "Critical: $1" >&2
    exit 1
}
INFO() {
    [ $_loglevel -ge 2 ] && echo "INFO: $1" >&2
}
ERROR() {
    [ $_loglevel -ge 1 ] && echo "ERROR: $1" >&2
}
```
- set -x 
  - -x(xtrace) 选项会导致 BASH 在执行命令之前，先把要执行的命令打印出来
- trap/bashdb
  - 为了方便调试，BASH 也提供了陷阱机制。这跟之前介绍的两种方法高级不少。我们可以利用 trap 这个内置命令来指定各个 sigspec 应该执行的命令
  - trap [-lp] [[arg] sigspec ...]


#### 在shell脚本中输出调试信息
- 使用trap命令
- 使用tee命令
- 使用"调试钩子"

#### 使用shell的执行选项
- -n 只读取shell脚本，但不实际执行
- -x 进入跟踪方式，显示所执行的每一条命令
- -c "string" 从strings中读取命令

#### 对"-x"选项的增强

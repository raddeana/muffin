#### Uboot 的启动流程
ARM Linux 的启动流程大致为: Uboot → Kernel → Root filesystem

- Uboot 拿到 CPU 使用权就开始做初始化工作，比如关闭看门狗、设置 CPU 运行模式、设置堆栈、初始化内存、网卡、nand flash 等，最后把 Linux 内核加载到内存中
- 初始化 RAM: 内核要在 RAM 中运行，所以在调用内核之前必须初始化和设置 RAM，为调用内核做好准备
- 初始化串口: 内核在启动过程中可以将信息通过串口输出，这样就可以清楚的知道内核启动信息
- 检测处理器类型: Uboot 在调用内核前需要检测系统的处理器类型，并将其保存在某个变量中提供给内核，内核在启动过程中会根据该处理器的类型调用相应的初始化程序
- 设置内核启动参数: 内核在启动过程中会根据该启动参数进行相应的初始化工作
- 调用内核镜像: nor Flash 支持芯片内执行（XIP，eXecute In Place），这样代码可以在 Flash 上直接执行而不必复制到 RAM 中去执行
  -  Flash 分为 nor Flash 和 nand Flash 两种
    - nor Flash 支持芯片内执行（XIP，eXecute In Place）
    - 这样代码可以在 Flash 上直接执行而不必复制到 RAM 中去执行

#### Linux 内核的启动流程（设备和驱动的加载）
- vmlinusx 是 ELF 格式的 Object 文件，这种文件只是各个源代码经过连接以后得到的文件，并不能在 ARM 平台上运行
- 经过 objcopy 这个工具转换以后，得到了二进制格式文件 Image，Image 文件相比于 vmlinusx 文件，除了格式不同以外，还被去除了许多注释和调试的信息
- Image 文件经过压缩以后得到了 piggy.gz，这个文件仅仅是 Image 的压缩版，并无其他不同
- 接着编译生成另外几个模块文件 misc.o、big_endian.o、head.o、head-xscale.o，这几个文件组成一个叫 Bootstrap Loader 的组件，又叫引导程序，编译生成 piggy.o 文件
- 最后 piggy.o 文件和 Bootstrap Loader 组成一个 Bootable Kernel Image 文件（可启动文件）

#### 平台标识
- 设备树里有对设备根节点的 Compatible 描述，平台文件里有对 __initconst 的描述，如果两个字段一致则找到了对应的板级文件，这样就通过设备树把要用的设备平台与其他平台区分开来了
- 接着是运行时配置，让内核在启动的时候根据参数设置进行不同的处理
- 这是设备和驱动匹配的核心，也是工作中面对最多的情况

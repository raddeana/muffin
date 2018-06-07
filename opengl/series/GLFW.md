#### GLFW
- GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口
- 允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入，这正是我们需要的：
  - 编译生成的库
  - include文件夹

从源代码编译库可以保证生成的库是兼容你的操作系统和CPU的，而预编译的二进制文件可能会出现兼容问题

#### 链接
为了使我们的程序使用GLFW，我们需要把GLFW库链接(Link)进工程

#### Windows上的OpenGL
如果你是Windows平台，opengl32.lib已经包含在Microsoft SDK里了，它在Visual Studio安装的时候就默认安装了

#### Linux上的OpenGL库
在Linux下你需要链接libGL.so库文件，这需要添加-lGL到你的链接器设置中

#### 添加GLFW头文件
```c
#include <GLFW\glfw3.h>
```
> 对于用GCC编译的Linux用户建议使用这个命令行选项-lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi
> 没有正确链接相应的库会产生 undefined reference (未定义的引用) 这个错误

#### GLAD
因为OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的
```c
// 定义函数原型
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);

// 找到正确的函数并赋值给函数指针
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");

// 现在函数可以被正常调用了
GLuint buffer;
glGenBuffers(1, &buffer);
```

#### 配置GLAD
> GLAD是一个开源的库，它能解决我们上面提到的那个繁琐的问题
> <br />
> GLAD的配置与大多数的开源库有些许的不同，GLAD使用了一个在线服务
```c
#include <glad/glad.h> 
```

#### 附加资源
- GLFW: Window Guide: GLFW官方的配置GLFW窗口的指南
- Building applications: 提供了很多编译或链接相关的信息和一大列错误及对应的解决方案
- GLFW with Code::Blocks: 使用Code::Blocks IDE编译GLFW
- Running CMake: 简要的介绍如何在Windows和Linux上使用CMake
- Writing a build system under Linux: Wouter Verholst写的一个autotools的教程，讲的是如何在Linux上编写构建系统，尤其是针对这些教程
- Polytonic/Glitter: 一个简单的样板项目，它已经提前配置了所有相关的库；如果你想要很方便地搞到一个LearnOpenGL教程的范例工程，这也是很不错的

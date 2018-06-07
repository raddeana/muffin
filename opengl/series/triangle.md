#### 三角形
数据
- 顶点数组对象: Vertex Array Object，VAO
- 顶点缓冲对象: Vertex Buffer Object，VBO
- 索引缓冲对象: Element Buffer Object，EBO或Index Buffer Object，IBO
着色器
- 顶点着色器 Vertex Shader
- 形状(图元)装配 Shape Assembly
- 几何着色器 Geometry Shader

2D坐标和像素也是不同的，2D坐标精确表示一个点在2D空间中的位置，而2D像素是这个点的近似值，2D像素受到你的 屏幕/窗口 分辨率的限制
OpenGL着色器是用OpenGL着色器语言(OpenGL Shading Language, GLSL)写成的

- 图形渲染管线的第一个部分是顶点着色器(Vertex Shader)，它把一个单独的顶点作为输入
  - 顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释）
  - 同时顶点着色器允许我们对顶点属性进行一些基本处理
- 图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状
  - 图元装配阶段的输出会传递给几何着色器(Geometry Shader)
- 几何着色器的输出会被传入光栅化阶段(Rasterization Stage)
  - 这里它会把图元映射为最终屏幕上相应的像素
  - 生成供片段着色器(Fragment Shader)使用的片段(Fragment)
- 片段着色器的主要目的是计算一个像素的最终颜色，这也是所有OpenGL高级效果产生的地方
  - 片段着色器包含3D场景的数据（比如光照、阴影、光的颜色等等）
  - 这些数据可以被用来计算最终像素的颜色

在OpenGL中，我们必须定义至少一个顶点着色器和一个片段着色器（因为GPU中没有默认的顶点 / 片段着色器）

#### 顶点输入
OpenGL中的一个片段是OpenGL渲染一个像素所需的所有数据
```c
float vertices[] = {
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f,  0.5f, 0.0f
};
```

#### 标准化设备坐标(Normalized Device Coordinates, NDC)
- 一旦你的顶点坐标已经在顶点着色器中处理过，它们就应该是标准化设备坐标了，标准化设备坐标是一个x、y和z值在-1.0到1.0的一小段空间
- 任何落在范围外的坐标都会被丢弃/裁剪，不会显示在你的屏幕上
- 标准化设备坐标接着会变换为屏幕空间坐标(Screen-space Coordinates)
- 这是使用你通过glViewport函数提供的数据，进行视口变换(Viewport Transform)完成的

#### 顶点缓冲对象
使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
```c
unsigned int VBO;
glGenBuffers(1, &VBO);
```
OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
```c
glBindBuffer(GL_ARRAY_BUFFER, VBO)
```
把之前定义的顶点数据复制到缓冲的内存中
```c
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW)
```
glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数

#### 三种形式
- 第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上
- 第二个参数指定传输数据的大小(以字节为单位)
- 第三个参数是我们希望发送的实际数据
- 第四个参数指定了我们希望显卡如何管理给定的数据
  - GL_STATIC_DRAW: 数据不会或几乎不会改变
  - GL_DYNAMIC_DRAW: 数据会被改变很多
  - GL_STREAM_DRAW: 数据每次绘制时都会改变

#### 顶点着色器
用着色器语言GLSL(OpenGL Shading Language)编写顶点着色器
```c
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

使用in关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)
#### 编译着色器
储存这个顶点着色器为unsigned int，然后用glCreateShader创建这个着色器:
```c
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

> - 需要创建的着色器类型以参数形式提供给glCreateShader
> - 由于我们正在创建一个顶点着色器，传递的参数是GL_VERTEX_SHADER

把这个着色器源码附加到着色器对象上，然后编译它
```c
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```
glShaderSource函数把要编译的着色器对象作为第一个参数
- 可能会希望检测在调用glCompileShader后编译是否成功
- 参数是顶点着色器真正的源码
- 参数我们先设置为NULL
```c
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
```
首先我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器
```c
if(!success)
{
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

#### 顶点着色器
- 顶点着色器(Vertex Shader)是几个可编程着色器中的一个
- 如果我们打算做渲染的话，现代OpenGL需要我们至少设置一个顶点和一个片段着色器
```c
#version 330 core
out vec4 FragColor;

void main() {
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
```

事是用着色器语言GLSL(OpenGL Shading Language)编写顶点着色器，然后编译这个着色器，这样我们就可以在程序中使用它了
```c
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

#### 编译着色器
储存这个顶点着色器为unsigned int，然后用glCreateShader创建这个着色器
```c
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

需要创建的着色器类型以参数形式提供给glCreateShader
```c
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```
检测编译时错误
```c
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
```
编译失败，用glGetShaderInfoLog获取错误消息
```c
if(!success)
{
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

#### 片段着色器
红色、绿色、蓝色和alpha(透明度)分量，通常缩写为RGBA
```c
#version 330 core
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
```
使用GL_FRAGMENT_SHADER常量作为着色器类型
```c
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

#### 着色器程序
- 着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接
```c
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
```
- 用glLinkProgram链接
```c
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```

#### 用glLinkProgram链接
```
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    ...
}
```
todo 
https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/

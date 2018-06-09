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
# version 330 core
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
# version 330 core
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
# version 330 core
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
glCreateProgram函数创建一个程序
```c
glAttachShader(shaderProgram, vertexShader)
glAttachShader(shaderProgram, fragmentShader)
glLinkProgram(shaderProgram)
```
着色器附加到了程序
```c
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    ...
}
```

#### 调用glUseProgram函数
```c
glUseProgram(shaderProgram);
```

```c
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

#### 链接顶点属性
顶点着色器允许我们指定任何以顶点属性为形式的输入，这使其具有很强的灵活性的同时，它还的确意味着我们必须手动指定输入数据的哪一个部分对应顶点着色器的哪一个顶点属性
- 顶点着色器允许我们指定任何以顶点属性为形式的输入
- 位置数据被储存为32位（4字节）浮点值
- 每个位置包含3个这样的值
- 在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列(Tightly Packed)
- 数据中第一个值在缓冲开始的位置

使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据
```c
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

```c
// 复制顶点数组到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// 当我们渲染一个物体时要使用着色器程序
glUseProgram(shaderProgram);

// 绘制物体
someOpenGLFunctionThatDrawsOurTriangle();
```

#### 顶点数组对象
顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中
顶点数组对象会储存以下这些内容
- glEnableVertexAttribArray和glDisableVertexAttribArray的调用
- 通过glVertexAttribPointer设置的顶点属性配置
- 通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象

#### 创建一个VAO和创建一个VBO
```c
unsigned int VAO;
glGenVertexArrays(1, &VAO);
```

```c
# ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
# 绑定VAO
glBindVertexArray(VAO);
# 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
# 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

# ..:: 绘制代码（渲染循环中） :: ..
# 绘制物体
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

#### 三角形
要想绘制我们想要的物体，OpenGL给我们提供了glDrawArrays函数，它使用当前激活的着色器，之前定义的顶点属性配置，和VBO的顶点数据（通过VAO间接绑定）来绘制图元
```c
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```
glDrawArrays函数第一个参数是我们打算绘制的OpenGL图元的类型

#### 索引缓冲对象
在渲染顶点这一话题上我们还有最有一个需要讨论的东西——索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)
- 绘制两个三角形来组成一个矩形（OpenGL主要处理三角形）
```c
float vertices[] = {
  // 第一个三角形
  0.5f, 0.5f, 0.0f,       // 右上角
  0.5f, -0.5f, 0.0f,      // 右下角
  -0.5f, 0.5f, 0.0f,      // 左上角
  
  // 第二个三角形
  0.5f, -0.5f, 0.0f,      // 右下角
  -0.5f, -0.5f, 0.0f,     // 左下角
  -0.5f, 0.5f, 0.0f       // 左上角
};
```
- 定义（不重复的）顶点，和绘制出矩形所需的索引
```c
float vertices[] = {
  0.5f, 0.5f, 0.0f,   // 右上角
  0.5f, -0.5f, 0.0f,  // 右下角
  -0.5f, -0.5f, 0.0f, // 左下角
  -0.5f, 0.5f, 0.0f   // 左上角
};

// 注意索引从 0 开始
unsigned int indices[] = { 
  0, 1, 3, // 第一个三角形
  1, 2, 3  // 第二个三角形
};
```
- 需要创建索引缓冲对象
```c
unsigned int EBO;
glGenBuffers(1, &EBO);
```
- 与VBO类似，我们先绑定EBO然后用glBufferData把索引复制到缓冲里
```c
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```
- 使用glDrawElements时，我们会使用当前绑定的索引缓冲对象中的索引进行绘制
```c
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

#### 线框模式(Wireframe Mode)
要想用线框模式绘制你的三角形，你可以通过glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)函数配置OpenGL如何绘制图元
第一个参数表示我们打算将其应用到所有的三角形的正面和背面，第二个参数告诉我们用线来绘制
之后的绘制调用会一直以线框模式绘制三角形，直到我们用glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)将其设置回默认模式

https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/

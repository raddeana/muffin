#### 变换
尽管我们现在已经知道了如何创建一个物体、着色、加入纹理，给它们一些细节的表现，但因为它们都还是静态的物体，仍是不够有趣

#### 向量
- 向量最基本的定义就是一个方向
- 或者更正式的说，向量有一个方向(Direction)和大小(Magnitude，也叫做强度或长度)

#### 向量与标量运算
标量(Scalar)只是一个数字（或者说是仅有一个分量的向量）

#### 向量取反
对一个向量取反(Negate)会将其方向逆转

#### 向量加减
向量的加法可以被定义为是分量的(Component-wise)相加，即将一个向量中的每一个分量加上另一个向量的对应分量

#### 矩阵与向量相乘
其实就是一个N×1矩阵，N表示向量分量的个数（也叫N维(N-dimensional)向量）

#### 单位矩阵
在OpenGL中，由于某些原因我们通常使用4×4的变换矩阵，而其中最重要的原因就是大部分的向量都是4分量的

#### 缩放
对一个向量进行缩放(Scaling)就是对向量的长度进行缩放，而保持它的方向不变

#### 位移
位移(Translation)是在原始向量的基础上加上另一个向量从而获得一个在不同位置的新向量的过程，从而在位移向量基础上移动了原始向量

#### 旋转
在2D或3D空间中也容易表示出来，但旋转(Rotation)稍复杂些

#### 矩阵的组合
使用矩阵进行变换的真正力量在于，根据矩阵之间的乘法，我们可以把多个变换组合到一个矩阵中

#### 实践
- 我们已经解释了变换背后的所有理论，是时候将这些知识利用起来
- OpenGL没有自带任何的矩阵和向量知识，所以我们必须定义自己的数学类和函数

#### GLM
- GLM是OpenGL Mathematics的缩写，它是一个只有头文件的库，也就是说我们只需包含对应的头文件就行了，不用链接和编译
- GLM库从0.9.9版本起，默认会将矩阵类型初始化为一个零矩阵（所有元素均为0），而不是单位矩阵（对角元素为1，其它元素为0）
- 如果使用的是0.9.9或0.9.9以上的版本，需要将所有的矩阵初始化改为 glm::mat4 mat = glm::mat4(1.0f)

```c
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

```c
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示
glm::mat4 trans;
trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
vec = trans * vec;
std::cout << vec.x << vec.y << vec.z << std::endl;
```

```c
glm::mat4 trans;
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); 
```

```c
# version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main () {
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
```

```c
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```

```c
glm::mat4 trans;
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
```

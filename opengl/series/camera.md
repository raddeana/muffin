#### 摄像机
在OpenGL中配置一个摄像机，并且将会讨论FPS风格的摄像机

#### 摄像机/观察空间
观察矩阵把所有的世界坐标变换为相对于摄像机位置与方向的观察坐标

#### 摄像机位置
```cpp
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
```

#### 摄像机方向
```cpp
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
```

#### 右轴
```cpp
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```

#### 上轴
```cpp
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
```

#### Look At
使用矩阵的好处之一是如果你使用3个相互垂直（或非线性）的轴定义了一个坐标空间，你可以用这3个轴外加一个平移向量来创建一个矩阵，并且你可以用这个矩阵乘以任何向量来将其变换到那个坐标空间
R是右向量，U是上向量，D是方向向量P是摄像机位置向量

#### GLM就会创建一个LookAt矩阵，我们可以把它当作我们的观察矩阵
```cpp
glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
           glm::vec3(0.0f, 0.0f, 0.0f), 
           glm::vec3(0.0f, 1.0f, 0.0f));
```

#### glm::LookAt函数需要一个位置、目标和上向量
```cpp
float radius = 10.0f;
float camX = sin(glfwGetTime()) * radius;
float camZ = cos(glfwGetTime()) * radius;
glm::mat4 view;
view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
```

#### 自由移动
让摄像机绕着场景转的确很有趣
```cpp
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
```
LookAt函数现在成了
```cpp
view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
```
定义过一个processInput函数
```cpp
void processInput(GLFWwindow *window) {
    // adjust accordingly
    float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}
```

希望向左右移动，我们使用叉乘来创建一个右向量(Right Vector)，并沿着它相应移动就可以了

#### 移动速度
图形程序和游戏通常会跟踪一个时间差(Deltatime)变量，它储存了渲染上一帧所用的时间
```cpp
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
```

```cpp
float currentFrame = glfwGetTime();
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;
```

```cpp
void processInput(GLFWwindow *window) {
  float cameraSpeed = 2.5f * deltaTime;
}
```

#### 视角移动
只用键盘移动没什么意思。特别是我们还不能转向，移动很受限制

#### 欧拉角
欧拉角(Euler Angle)是可以表示3D空间中任何旋转的3个值，由莱昂哈德·欧拉(Leonhard Euler)在18世纪提出
一共有3种欧拉角：
- 俯仰角(Pitch)
- 偏航角(Yaw)
- 滚转角(Roll)

#### 定俯仰角的y值等于sin θ
#### 给定俯仰角的y值等于sin θ
```cpp
direction.y = sin(glm::radians(pitch)); // 注意我们先把角度转为弧度
```
#### 只更新了y值，仔细观察x和z分量也被影响了
```cpp
direction.x = cos(glm::radians(pitch));
direction.z = cos(glm::radians(pitch));
```

```cpp
// 译注：direction代表摄像机的前轴(Front)，这个前轴是和本文第一幅图片的第二个摄像机的方向向量是相反的
direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
direction.y = sin(glm::radians(pitch));
direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
```

#### 鼠标输入
偏航角和俯仰角是通过鼠标（或手柄）移动获得的，水平的移动影响偏航角，竖直的移动影响俯仰角
```cpp
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
```

```cpp
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
```

```cpp
glfwSetCursorPosCallback(window, mouse_callback);
```
- 鼠标距上一帧的偏移量
- 把偏移量添加到摄像机的俯仰角和偏航角中
- 对偏航角和俯仰角进行最大和最小值的限制
- 计算方向向量
计算鼠标自上一帧的偏移量
```cpp
float lastX = 400, lastY = 300;
```
计算当前帧和上一帧鼠标位置的偏移量
```cpp
float xoffset = xpos - lastX;
float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
lastX = xpos;
lastY = ypos;

float sensitivity = 0.05f;
xoffset *= sensitivity;
yoffset *= sensitivity;
```
偏移量加到全局变量pitch和yaw上
```cpp
yaw   += xoffset;
pitch += yoffset;
```
值超过限制的时候将其改为极限值来实现
```cpp
if(pitch > 89.0f) {
  pitch =  89.0f;
}
if(pitch < -89.0f) {
  pitch = -89.0f;
}
```
通过俯仰角和偏航角来计算以得到真正的方向向量
```cpp
glm::vec3 front;
front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
front.y = sin(glm::radians(pitch));
front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
cameraFront = glm::normalize(front);
```
鼠标位置坐标来计算偏移量了
```cpp
if(firstMouse) // 这个bool变量初始时是设定为true的
{
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
}
```

```cpp
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; 
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.05;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw   += xoffset;
  pitch += yoffset;

  if(pitch > 89.0f)
      pitch = 89.0f;
  if(pitch < -89.0f)
      pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}
```

#### 缩放
实现一个缩放(Zoom)接口
```cpp
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if (fov >= 1.0f && fov <= 45.0f) {
    fov -= yoffset;
  }
  
  if (fov <= 1.0f) {
    fov = 1.0f;
  }
  
  if(fov >= 45.0f) {
    fov = 45.0f;
  }
}
```

```cpp
projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
```

```cpp
glfwSetScrollCallback(window, scroll_callback);
```

#### 珊瑚红(Coral)
```c
glm::vec3 coral(1.0f, 0.5f, 0.31f);
```

#### 两个颜色向量作分量相乘
```c
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
```

#### 物体从一个光源反射各个颜色分量的大小
```c
glm::m::vec3 c3 lightColorghtColor(0.0f, 1.0f, 0.0f).0f, 1.0f, 0.0f);
glm::glm::vec3 c3 toyColoryColor(1.0f, 0.5f, 0.31f).0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; glm::vec3 result = li // = (0.0f, 0.5f, 0.0f);
```

#### 深橄榄绿色(Dark olive-green)
```c
glm::vec3 lightColor(0.33f, 0.42f, 0.18f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (0.33f, 0.21f, 0.06f);
```

#### 顶点着色器
```c
# version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
```

#### 为这个灯创建一个专门的VAO
```c
unsigned int lightVAO;
glGenVertexArrays(1, &lightVAO);
glBindVertexArray(lightVAO);
// 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

#### 片段着色器
```c
# version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}
```

#### 全局vec3变量来表示光源在场景的世界空间
```c
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
```

#### 灯位移到这里，缩小
```c
model = glm::mat4();
model = glm::translate(model, lightPos);
model = glm::scale(model, glm::vec3(0.2f));
```

#### 绘制灯立方体
```c
lampShader.use();
// 设置模型、视图和投影矩阵uniform

// 绘制灯立方体对象
glBindVertexArray(lightVAO);
glDrawArrays(GL_TRIANGLES, 0, 36);
```

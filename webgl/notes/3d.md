#### WebGL
```
canvas.getContext("webgl") || canvas.getContext("experimental-webgl")
```

#### Shader
- 顶点着色器（Vertex shader）: 绘制每个定点都会调用一次
- 片段着色器（Fragment shader）: 每个片源（可以简单的理解为像素）都会调用一次

#### 坐标系
WebGL使用的是右手系，x水平（右为正），y竖直（上为正），z垂直屏幕（外为正）
WebGL的宽高范围是从 -1 到 1

#### 向shader中传值
- attribute变量，传递与顶点相关的数组，只能在顶点着色器中使用
- uniform变量，传递与顶点无关的数据


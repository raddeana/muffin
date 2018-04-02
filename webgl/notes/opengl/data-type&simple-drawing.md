#### 基本数据类型
- GLenum: 用于GL枚举的无符号整型
- GLboolean: 用于单布尔值。OpenGL ES还定义了其自己的“真”和“假”值（GL_TRUE和GL_FALSE）以避免平台和语言的差别
- GLbitfield: 用于将多个布尔值（最多32个）打包到单个使用位操作变量的四字节整型
- GLbyte: 有符号单字节整型
- GLshort: 有符号双字节整型
- GLint: 有符号四字节整型
- GLsizei: 有符号四字节整型，用于代表数据的尺寸（字节），类似于C中的size_t
- GLubyte: 无符号单字节整型
- GLushort: 无符号双字节整型
- GLuint: 无符号四字节整型
- GLfloat: 四字节精度浮点数
- GLclampf: 0.0到1.0之间的四字节精度浮点数
- GLvoid: void值用于指示一个函数没有返回值，或没有参数
- GLfixed: 定点数，使用整型数存储实数
- GLclampx: 定点型，用于使用定点运算来表示0.0 到 1.0之间的实数

#### 结构体
##### 点
```opengl
typedef struct {  
    GLfloat x;  
    GLfloat y;  
    GLfloat z;  
} Vertex3D;  
  
static inline Vertex3D Vertex3DMake (CGFloat inX, CGFloat inY, CGFloat inZ)  
{  
    Vertex3D ret;  
    ret.x = inX;  
    ret.y = inY;  
    ret.z = inZ;  
    return ret;  
};  

static inline GLfloat Vertex3DCalculateDistanceBetweenVertices (Vertex3D first, Vertex3D second)  
{
    GLfloat deltaX = second.x - first.x;  
    GLfloat deltaY = second.y - first.y;  
    GLfloat deltaZ = second.z - first.z;  
    return sqrtf(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );  
};
```

##### 示例
```
Vertex3D vertex;
vertex.x = 10.0;
vertex.y = 23.75;
vertex.z = -12.532;
```

##### 三角形
```
typedef struct {  
    Vertex3D v1;  
    Vertex3D v2;  
    Vertex3D v3;  
} Triangle3D;

static inline Triangle3D Triangle3DMake(Vertex3D v1, Vertex3D v2, Vertex3D v3)  
{  
    Triangle3D tri;
    tri.v1 = v1;
    tri.v2 = v2;
    tri.v3 = v3;
    
    return tri;  
}
```

##### 绘制三角形
```
// 创建一个三角形  
Vertex3D vertex1 = Vertex3DMake(0.0, 1.0, -3.0);  
Vertex3D vertex2 = Vertex3DMake(1.0, 0.0, -3.0);  
Vertex3D vertex3 = Vertex3DMake(-1.0, 0.0, -3.0);  
Triangle3D triangle = Triangle3DMake(vertex1, vertex2, vertex3);  
  
  
// 绘制三角形  
glLoadIdentity();                                       // 加载单位矩阵,清除虚拟世界中的一切旋转，移动或其他变化并将观察者置于原点  
glClearColor(0.7, 0.7, 0.7, 1.0);                       // 设置背景色的RGBA  
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // 通知OpenGL清除以前的一切图形并将其设为clear颜色。  
glEnableClientState(GL_VERTEX_ARRAY);         // 启动OpenGL的vertex arrays（顶点数组）特性  
glColor4f(1.0, 0.0, 0.0, 1.0);                // 设置了绘图时所需的颜色RGBA  
glVertexPointer(3, GL_FLOAT, 0, &triangle);   // 设置绘制路径  
glDrawArrays(GL_TRIANGLES, 0, 9);             // 绘制三角形  
glDisableClientState(GL_VERTEX_ARRAY);        // 禁止先前启动的顶点数组特效
```

##### 绘制矩阵
```
Triangle3D triangle[2];  
triangle[0].v1 = Vertex3DMake(0.0, 1.0, -3.0);  
triangle[0].v2 = Vertex3DMake(1.0, 0.0, -3.0);  
triangle[0].v3 = Vertex3DMake(-1.0, 0.0, -3.0);  
triangle[1].v1 = Vertex3DMake(-1.0, 0.0, -3.0);  
triangle[1].v2 = Vertex3DMake(1.0, 0.0, -3.0);  
triangle[1].v3 = Vertex3DMake(0.0, -1.0, -3.0);  
  
  
glLoadIdentity();  
glClearColor(0.7, 0.7, 0.7, 1.0);  
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
glEnableClientState(GL_VERTEX_ARRAY);  
glColor4f(1.0, 0.0, 0.0, 1.0);  
glVertexPointer(3, GL_FLOAT, 0, &triangle);  
glDrawArrays(GL_TRIANGLES, 0, 18);  
glDisableClientState(GL_VERTEX_ARRAY);  
```

```
static inline void Vertex3DSet(Vertex3D *vertex, CGFloat inX, CGFloat inY, CGFloat inZ)  
{ 
  vertex->x = inX;  
  vertex->y = inY;  
  vertex->z = inZ;  
}
```

```
Triangle3D  *triangles = malloc(sizeof(Triangle3D) * 2);  
  
  
Vertex3DSet(&triangles[0].v1, 0.0, 1.0, -3.0);  
Vertex3DSet(&triangles[0].v2, 1.0, 0.0, -3.0);  
Vertex3DSet(&triangles[0].v3, -1.0, 0.0, -3.0);  
Vertex3DSet(&triangles[1].v1, -1.0, 0.0, -3.0);  
Vertex3DSet(&triangles[1].v2, 1.0, 0.0, -3.0);  
Vertex3DSet(&triangles[1].v3, 0.0, -1.0, -3.0);  
  
  
glLoadIdentity();  
glClearColor(0.7, 0.7, 0.7, 1.0);  
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
glEnableClientState(GL_VERTEX_ARRAY);  
glColor4f(1.0, 0.0, 0.0, 1.0);  
glVertexPointer(3, GL_FLOAT, 0, triangles);  
glDrawArrays(GL_TRIANGLES, 0, 18);  
glDisableClientState(GL_VERTEX_ARRAY);  
  
  
if (triangles != NULL) {
  free(triangles);
}
```

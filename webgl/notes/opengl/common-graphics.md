#### OpenGL常见平面图形绘制
##### 模板代码
```
#include <glut.h>  

void displayFunc()  
{  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);           // 在RGB模式下，使用glClearColor清空之后画布的颜色  
    glClear(GL_COLOR_BUFFER_BIT);                   // 清空画布  
    glColor3f(1.0f, 0.0f, 0.0f);                    // 设置画笔颜色  
    // do somethins  
    glFlush();                                      // 清空缓冲区，立即执行绘制命令  
}  

int main(int argc, char* argv[])  
{  
    glutInit(&argc, argv);                          // 对GLUT进行初始化  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);    // 设置显示模式(RGB颜色|单缓冲，对应的还有索引颜色和双缓冲)  
    glutInitWindowPosition(100, 100);               // 设置窗口的默认显示位置  
    glutInitWindowSize(400, 400);                   // 设置窗口的大小  
    glutCreateWindow("OpenGL");                     // 设置窗口的标题  
    glutDisplayFunc(&displayFunc);                  // 设置绘图函数  
    glutMainLoop();// 开启消息循环  
    return 0;  
}  
```

##### 画点
```
void displayFunc ()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 在RGB模式下，使用glClearColor清空之后画布的颜色
    glClear(GL_COLOR_BUFFER_BIT);         // 清空画布
    glRectf(0.0f, 0.0f, 0.5f, 0.5f);      // 换一个矩形
    glColor3f(1.0f, 0.0f, 0.0f);          // 设置画笔颜色
    glPointSize(5.0f);                    // 设置点的大小
    // 画直线  
    glBegin(GL_POINTS);                   // 设置绘制模式为点
        glVertex2f(-0.5f, 0.0f);  
        glVertex2f(-0.5f, -0.5f);  
    glEnd();  
    glFlush();                            // 清空缓冲区，立即执行绘制命令
}
```

##### 画线
- 将画点中的GL_POINTS改为GL_LINE就可以画线
- 将画点中的glPointSize改为glLineWidth可以设置线宽

##### 画三角形
```
void displayFunc()  
{  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // 在RGB模式下，使用glClearColor清空之后画布的颜色  
    glClear(GL_COLOR_BUFFER_BIT);           // 清空画布  
    glColor3f(1.0f, 0.0f, 0.0f);            // 设置画笔颜色  
    // 画三角形  
    glBegin(GL_TRIANGLES);                  // GL_POLYGON绘制模式三角形  
        glVertex2f(-0.5f, 0.0f);  
        glVertex2f(-0.5f, -0.5f);  
        glVertex2f(0.0f, -0.5f);  
    glEnd();  
    glFlush();                              // 清空缓冲区，立即执行绘制命令  
}
```

##### 画矩形
```
void displayFunc()  
{  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // 在RGB模式下，使用glClearColor清空之后画布的颜色  
    glClear(GL_COLOR_BUFFER_BIT);           // 清空画布  
    glColor3f(1.0f, 0.0f, 0.0f);            // 设置画笔颜色  
    // 画两个点  
    glBegin(GL_POLYGON);                    // GL_POLYGON绘制模式为多边形  
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.0f, 0.0f);
    glEnd();  
    glFlush();                              // 清空缓冲区，立即执行绘制命令  
}
```

#### 视点变换
相机位置(视点)的变换
void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz)

#### 模型变换
模型位置的变化
- 平移
glTranslate {fd} (TYPE x, TYPE y, TYPE z)

- 旋转
glRotate {fd} (TYPE angle, TYPE x, TYPE,y, TYPE z)

- 缩放
glScale {fd} (TYPE x, TYPE y, TYPE z)

#### 投影变换
将三维模型投影到屏幕上显示
- 透视投影
离视点近的物体大，离视点远的物体小，远到极点即为消失，成为消失点
void glFrustum(GLdouble left, GLdouble Right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)

- 正视投影
无论物体距离相机多远，投影后的物体大小尺寸不变，正投影相当于在无限远处观察得到的结果
void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)

#### 视口变换
将视景体内投影的物体显示在二维的视口平面上
glViewport(GLint x,GLint y,GLsizei width, GLsizei height)

#### 裁剪变换
除了视景体定义的六个裁剪平面外，还可自定义一个或多个附加裁剪平面，以去掉场景中无关的目标
void glClipPlane(GLenum plane,Const GLdouble *equation)

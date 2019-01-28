#include "glcommon.hpp"

static void init ()
{
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT, GL_LINE);   // 正面画线
	glPolygonMode(GL_BACK, GL_FILL);    // 背面填充

	glCullFace(GL_BACK);      // 剔除背面
	glEnable(GL_CULL_FACE);   // 启用剔除
}

static void changeSize (int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, float(width)/float(height), 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void renderScene ()
{
	static float angle = 0.f;
	angle += 0.5f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3, 2, 8, 0, 0, 0, 0, 1, 0);

	glRotatef(angle, 0.0, 1.0, 0.0);
	// 三角形
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.6, -1.6, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.6, -1.6, 0.0);
	glColor3f(0.0, 0.0, 1.0); // 这三个颜色设置后，会产生一个渐变色
	glVertex3f( 0.0,  1.6, 0.0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	// 正方体 正面
	glEdgeFlag(GL_TRUE);     // 绘制三角形的线
	glVertex3f(-1,-1, 1);
	glEdgeFlag(GL_FALSE);    // GL_FALSE 三角形的第二条线，不要绘制出来。这个只影响多边形的GL_LINE画线模式，填充模式没有意义
	glVertex3f( 1,-1, 1);
	glEdgeFlag(GL_TRUE);
	glVertex3f(-1, 1, 1);
	glEdgeFlag(GL_FALSE);
	glVertex3f(-1, 1, 1);
	glEdgeFlag(GL_TRUE);
	glVertex3f( 1,-1, 1);
	glVertex3f( 1, 1, 1);

	// 右面
	glColor3f(0, 1, 0);
	glVertex3f( 1, 1, 1);
	glVertex3f( 1,-1, 1);
	glVertex3f( 1, 1,-1);
	glVertex3f( 1, 1,-1);
	glVertex3f( 1,-1, 1);
	glVertex3f( 1,-1,-1);

	// 下面
	glColor3f(0, 0, 1);
	glVertex3f(-1,-1, 1);
	glVertex3f( 1,-1, 1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f( 1,-1, 1);
	glVertex3f( 1,-1,-1);

	// 上面
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f( 1, 1, 1);
	glVertex3f(-1, 1,-1);
	glVertex3f(-1, 1,-1);
	glVertex3f( 1, 1, 1);
	glVertex3f( 1, 1,-1);

	// 左面
	glColor3f(1, 0, 1);
	glVertex3f(-1,-1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1,-1);
	glVertex3f(-1, 1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1, 1);

	// 背面
	glColor3f(0, 1, 1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1, 1,-1);
	glVertex3f( 1,-1,-1);
	glVertex3f( 1,-1,-1);
	glVertex3f(-1, 1,-1);
	glVertex3f( 1, 1,-1);
	glEnd();

	glutSwapBuffers();
}

static void keyboardFunc (unsigned char key, int x, int y) {
	if (key==27) exit(0); // esc
}

int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
  
	// GLUT_MULTISAMPLE 多重采样抗锯齿
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("glsl");

	GLenum ret = glewInit();
	if (ret != GLEW_OK) {
		printf("glewInit failed...\n");
		exit(1);
	}
	init();
	glutReshapeFunc(changeSize); // 窗口尺寸大小改变回调
	glutDisplayFunc(renderScene); // 绘制回调
	glutIdleFunc(renderScene); // 闲置回调
	glutKeyboardFunc(keyboardFunc); // 键盘回调

	GLuint program = createGLProgram("./src/shader/common/first.vert", "./src/shader/common/first.frag");
	glUseProgram(program);

	glutMainLoop();
	return 0;
}
--------------------- 
作者：Drunkenman_ 
来源：CSDN 
原文：https://blog.csdn.net/huanghuangjin/article/details/84556905 
版权声明：本文为博主原创文章，转载请附上博文链接！

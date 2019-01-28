#include "glcommon.hpp"

static void init()
{
	printf("gl version : %s\n", glGetString(GL_VERSION)); // gl version : 3.0 Mesa 18.0.0-rc5 (4.6.0 NVIDIA 390.77) 笔记本为双显卡 ()中的表示nvidia
	printf("显卡 company : %s\n", glGetString(GL_VENDOR)); // 显卡 company : Intel Open Source Technology Center  (NVIDIA Corporation)
	printf("显卡型号 : %s\n", glGetString(GL_RENDERER)); // 显卡型号 : Mesa DRI Intel(R) Sandybridge Mobile  (GeForce GT 525M/PCIe/SSE2)
	int maxSamples = 0;
	glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
	printf("最大多重采样数 : %d\n", maxSamples); // 最大多重采样数 : 4  (32)

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT, GL_LINE); // 正面画线
	glPolygonMode(GL_BACK, GL_FILL); // 背面填充

	glCullFace(GL_BACK); // 剔除背面
	glEnable(GL_CULL_FACE); // 启用剔除

	GLint buf[1], sbuf[1];
	glGetIntegerv(GL_SAMPLE_BUFFERS_ARB, buf); // 需要在 glutInitDisplayMode 中设置 GLUT_MULTISAMPLE 才会有值
	glGetIntegerv(GL_SAMPLES_ARB, sbuf);
	printf("GL_SAMPLE_BUFFERS_ARB=%d, GL_SAMPLES_ARB=%d\n", *buf, *sbuf); // GL_SAMPLE_BUFFERS_ARB=1, GL_SAMPLES_ARB=4
}

static void changeSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, float(width)/float(height), 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void renderScene()
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
	glEdgeFlag(GL_TRUE); // 绘制三角形的线
	glVertex3f(-1,-1, 1);
	glEdgeFlag(GL_FALSE); // GL_FALSE 三角形的第二条线，不要绘制出来。这个只影响多边形的GL_LINE画线模式，填充模式没有意义
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

static void keyboardFunc(unsigned char key, int x, int y)
{
	if (key==27) exit(0); // esc
}

int main_gl_slias(int argc, char *argv[])
{
	glutInit(&argc, argv);
	// GLUT_MULTISAMPLE 多重采样抗锯齿
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("opengl");

	init();
	glutReshapeFunc(changeSize);      // 窗口尺寸大小改变回调
	glutDisplayFunc(renderScene);     // 绘制回调
	glutIdleFunc(renderScene);        // 闲置回调
	glutKeyboardFunc(keyboardFunc);   // 键盘回调

	glutMainLoop();
	return 0;
}

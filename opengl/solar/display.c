#include <glut.h>
#include <stdio.h> 
#include <time.h>

static int day = 200;
 
double getFPS () {
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;
 
	++count;
	
  if (count <= 50){
		return save;
	}
  
	count = 0;
	last = current;
	current = clock();
	timegap = (current-last) / (double) CLK_TCK;
	save = 50.0f / timegap;
	
  return save;
}
 
void display () {
	// 打印FPS
	double FPS = getFPS();
	printf("FPS = %f\n", FPS);
 
	glEnable(GL_DEPTH_TEST);                              // 开启更新深度缓冲区的功能，被挡住的像素不绘制
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清除颜色缓冲|深度缓冲
 
	glMatrixMode(GL_PROJECTION);                // 设置当前矩阵模式：对投影矩阵应用随后的矩阵操作
	glLoadIdentity();                           // 将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵,即之前的矩阵变换带来的影响到此为止
	gluPerspective(75, 1, 1, 400000);           // 设置透视投影矩阵
 
	glMatrixMode(GL_MODELVIEW);                         // 设置当前矩阵模式：对模型视景矩阵堆栈应用随后的矩阵操作.
	glLoadIdentity();                                   // 将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵,即之前的矩阵变换带来的影响到此为止
	gluLookAt(0, -200000, 200000, 0, 0, 0, 0, 0, 1);    // 设置视点
 
	//sun
	glColor3f(1, 0, 0);                 // 设置绘制颜色为红色
	glutSolidSphere(69600, 20, 20);     // 渲染一个球体
 
	// earth
	glColor3f(0, 0, 1);                 // 设置绘制颜色为蓝色
	glRotatef(day, 0, 0, -1);           // 旋转
	glTranslatef(150000, 0, 0);         // 平移
	glutSolidSphere(15945, 20, 20);     // 渲染一个球体
 
	//moon
	glColor3f(1, 1, 0);
	glRotatef(day / 30.0 * 360 - day, 0, 0, -1);    // 旋转
	glTranslatef(38000, 0, 0);                      // 平移
	glutSolidSphere(4345, 20, 20);                  // 渲染一个球体
 
	glFlush();                          // 清空缓冲区，立即执行绘制命令  
	glutSwapBuffers();                  // 双缓冲时交换两个缓冲区指针
}
 
void idle () {
	++day;
  
	if (day > 360){
		day = 0;
	}
  
	display();                          // 调用display方法进行强制刷新
}
 
int main (int argc, char **argv) {
	glutInit(&argc, argv);// 初始化GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);    // 显示显示模式(RGB颜色|双缓冲)
	glutCreateWindow("earth,moon,sun");             // 设置窗口标题
	glutInitWindowSize(400, 400);       // 设置窗口大小
	glutDisplayFunc(display);           // 设置绘制函数
	glutIdleFunc(&idle);
	glutMainLoop();                     // 开启消息循环
 
	return 0;
}

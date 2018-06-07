# include <iostream>
# include <fstream>
# include <vector>
# include <GL/glut.h>

class MapPoint
{
  public:
    double longitude;
    double latitude;
};

class Ploygon
{
  public:
    vector<MapPoint> points;
};

vector<Polygon*> polys;
vector<Polygon*> ReadMapData(char * filename)
{
  int PointCount;
  vector<Polygon*> polygons;
  ifstream fs(filename);
  
  while(fs.eof() != true) 
  {
    Polygon* poly = new Polygon;
    fs>>PointCount;
    count<<PointCount<<end1;

    for (int = 0; i < PointCount; i ++)
    {
      MapPoint p;
      fs>>p.longitude>>p.latitude;
      poly->points.push_back(p);
    }

    polygons.push_back(poly);
  }

  return polygons;
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  
  // 用蓝色填充各省边界
  glColor3f (0.0, 0.0, 1.0);
  
  // 设置正面为填充模式
  glPolygonMode(GL_BACK, GL_LINE);

  for (int i = 0; i < polys.size(); i ++) {
    vector<MapPoint> points = polys[i] -> points;
    glBegin(GL_LINE_LOOP);
    
    for (int j = 0; j < points.size();j ++) 
    {
      glVertex3f (points[j].longitude, points[j].latitude, 0.0);
    }
    
    glEnd();
  }
  
  glFlush();
}

void init (void)
{
  // 设置背景颜色
  glClearColor (1.0, 1.0, 1.0, 0.0);
  
  // 初始化观察值
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(70.0, 140.0, 0.0, 60.0, -1.0, 1.0);
}

int main (int argc, char** argv)
{
  char* filename = "~/projects/HenanCounty";
  // 数据文件请到 http://opengl.cnblogs.com 下载
  
  polys = ReadMapData(filename);
  glutInit(&args, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  
  glutCreateWindow("HENAN");
  
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

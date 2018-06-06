void PrintLint (int x1, int y1, int x2, int y2, int color)
{
  int x, y, xA, yA;
  if (y1 > y2) {
    yA = y1 - y2;
    xA = x1 - x2;
  } else {
    yA = y2 - y1;
    xA = x2 - x1;
  }
  
  int F = X = Y = 0;
  int n = abs(xA) + abs(yA);
  
  for (int i = 0; i < n; i ++) {
    if (xA > 0) {
      if (F >= 0) {
        x++;
        F -= yA;
      } else {
        y ++;
        F += xA;
      }
    }
  }
  
  if (y1 > y2) {
    setpixel(x + x2, y + y2, color);
  } else {
    setpixel(x + x2, y + y2, color);
  }
}

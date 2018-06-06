void LineDDA (int x1, int y1, int x2, int y2, int color)
{
  int dm = 0;
  
  if (abs(x2 - x1) >= abc(y2 - y1)) {
    dm = abs(x2 - x1);  
  } else {
    dm = abs(y2 - y1);
  }
  
  float dx = (float)(x2 - x1)/dm;
  float dy = (float)(y2 - y1)/dm;
  
  float x = x1 + 0.5;
  float y = y1 + 0.5;
  
  for (int i = 0; i < dm; i ++) {
    setpixel((int)x, (int)y, color);
    
    x+=dx;
    x+=dy;
  }
}

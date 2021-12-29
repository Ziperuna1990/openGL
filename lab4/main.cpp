#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define  COL 800.0
#define ROW 800.0
#define fps 0.5
#define zoom 1.0
#define maxiter 60
#define xoffset -0.5
#define yoffset 0
#define s 1.0
#define v 1.0

void display_callback();
void reshape_callback(int w, int h);
void timer_callback(int);
void color1(int, double *);
void color2(int, double *);
void color3(int, double *);
void color4(int, double *);
void color5(int, double *);
void color6(int, int, double *);
void color7(int, double *);
void color8(int, double *);
void color9(int, double *);
void HSVtoRGB(double, double, double, double *);

int frameCounter = 0;

double map(double val, double frommin, double frommax, double tomin, double tomax) {
  return (val - frommin) / (frommax - frommin) * (tomax - tomin) + tomin;
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(700, 150);
  glutInitWindowSize(COL, ROW);
  glutCreateWindow("mandelbrot !!");
  glutDisplayFunc(display_callback);
  glutReshapeFunc(reshape_callback);
  glutTimerFunc(0, timer_callback, 0);
  init();
  glutMainLoop();
  return 0;
}
void color5(int, double *);

void display_callback() {
  glClear(GL_COLOR_BUFFER_BIT);
  double ca;
  double cb;
  double a;
  double b;
  double aa;
  double bb;
  double rgb[3];
  int n;
  glBegin(GL_POINTS);
  for (int x = 0; x < COL; x++) {
    for (int y = 0; y < ROW; y++) {
      ca = map(x, 0, COL, (-1 * zoom) + xoffset, zoom + xoffset);
      cb = map(y, 0, ROW, (-1 * zoom) + yoffset, zoom + yoffset);
      a = ca;
      b = cb;
      n = 0;
      while (n < maxiter) {
        aa = a * a - b * b;
        bb = 2 * a * b;
        a = aa + ca;
        b = bb + cb;
        if (sqrt(a * a + b * b) > 2) {
          break;
        }
        n++;
      }
      switch (frameCounter % 9) {
        case 0:color1(n, rgb);
          break;
        case 1:color2(n, rgb);
          break;
        case 2:color3(n, rgb);
          break;
        case 3:color4(n, rgb);
          break;
        case 4:color5(n, rgb);
          break;
        case 5:color6(n, 10, rgb);
          break;
        case 6:color7(n, rgb);
          break;
        case 7:color8(n, rgb);
          break;
        case 8:color9(n, rgb);
          break;
      }
      glColor3f(rgb[0], rgb[1], rgb[2]);
      glVertex2i(x, y);

    }
  }
  glEnd();
  glutSwapBuffers();
  frameCounter++;
}

void reshape_callback(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, COL, 00, ROW, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
  glutPostRedisplay();
  glutTimerFunc(1000 / fps, timer_callback, 0);
}

void color1(int n, double output[3]) {
  double bright = 360.0 * n / maxiter;
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0;
  }
  HSVtoRGB(bright, s, tempv, output);
}
void color2(int n, double output[3]) {
  double bright = 360.0 - (360.0 * n / maxiter);
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0;
  }
  HSVtoRGB(bright, s, tempv, output);
}
void color3(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  HSVtoRGB(240, bright, tempv, output);
}
void color4(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  HSVtoRGB(115, bright, tempv, output);
}
void color5(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  HSVtoRGB(359, bright, tempv, output);
}
void color6(int n, int num, double output[3]) {
  double bright = ((double) n) / maxiter;
  bright = bright * (double) num;
  bright = (int) bright;
  bright /= (double) num;
  bright *= 360.0;
  double tempv = v;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  HSVtoRGB(bright, s, tempv, output);
}
void color7(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = 1;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  output[0] = (1.0 - bright) * tempv;
  output[1] = 0.0;
  output[2] = bright * tempv;
}
void color8(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = 1;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  output[0] = 0.0;
  output[1] = (1.0 - bright) * tempv;
  output[2] = bright * tempv;
}
void color9(int n, double output[3]) {
  double bright = ((double) n) / maxiter;
  double tempv = 1;
  if (n >= maxiter) {
    tempv = 0.0;
  }
  output[0] = bright * tempv;
  output[1] = (1.0 - bright) * tempv;
  output[2] = 0.0;
}
void HSVtoRGB(double H, double S, double V, double output[3]) {
  double C = S * V;
  double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
  double m = V - C;
  double Rs, Gs, Bs;

  if (H >= 0 && H < 60) {
    Rs = C;
    Gs = X;
    Bs = 0;
  } else if (H >= 60 && H < 120) {
    Rs = X;
    Gs = C;
    Bs = 0;
  } else if (H >= 120 && H < 180) {
    Rs = 0;
    Gs = C;
    Bs = X;
  } else if (H >= 180 && H < 240) {
    Rs = 0;
    Gs = X;
    Bs = C;
  } else if (H >= 240 && H < 300) {
    Rs = X;
    Gs = 0;
    Bs = C;
  } else {
    Rs = C;
    Gs = 0;
    Bs = X;
  }

  output[0] = (Rs + m);
  output[1] = (Gs + m);
  output[2] = (Bs + m);
}
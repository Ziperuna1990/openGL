#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>

#define WIDTH 650
#define HEIGHT 650

float matCol[] = {1, 1, 1, 1};

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matCol);
  glTranslatef(0.7f, 0.0f, 0.0f);
  glutSolidTeapot(0.1);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matCol);
  glTranslatef(0.4f, 0.0f, 0.0f);
  glRotatef(60, 1, 0, 0);
  glutWireTorus(0.03, 0.1, 8, 16);
  glPopMatrix();
  glFlush();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matCol);
  glTranslatef(0.1f, -0.1f, 0.0f);
  glRotatef(270, 1, 0, 0);
  glutWireCone(0.1, 0.3, 8, 8);
  glPopMatrix();
  glFlush();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matCol);
  glTranslatef(-0.3f, 0.0f, 0.0f);
  glRotatef(15, 1, 1, 0);
  glutSolidCube(0.3);
  glPopMatrix();
  glFlush();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matCol);
  glTranslatef(-0.8f, 0.0f, 0.0f);
//  glRotatef(15, 1, 1, 0);
  glScalef(0.1, 0.1, 0.1);
  glutSolidDodecahedron();
  glPopMatrix();
  glFlush();

}

void init(){
  float pos[] = {1,1,1,0};
  float white[] = {1,1,1,0};
  float shini[] = {70};

  glClearColor(.5,.5,.5,0);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0,GL_AMBIENT,white);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
  glMaterialfv(GL_FRONT,GL_SHININESS,shini);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("task5");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
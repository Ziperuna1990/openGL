#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void draw_line(GLfloat lineVertex[], float h, int pattern) {
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_LINE_STIPPLE);
  glPushAttrib(GL_LINE_BIT);
  glLineWidth(h);
  glLineStipple(1, pattern);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, lineVertex);
  glDrawArrays(GL_LINES, 0, 2);
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopAttrib();
  glDisable(GL_LINE_STIPPLE);
  glDisable(GL_LINE_SMOOTH);
}

void draw_point_with_smooth(GLfloat pointVertex[], GLfloat size) {
  glEnable(GL_POINT_SMOOTH);
  glEnableClientState(GL_VERTEX_ARRAY);
  glPointSize(size);
  glVertexPointer(2, GL_FLOAT, 0, pointVertex);
  glDrawArrays(GL_POINTS, 0, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);
}

GLfloat func(GLfloat x) {
  GLfloat y;
  y = 6.0 + 2.0 * sinh(x / 2.0) * sin(x);
  return y;
}


int main(int argc, char **argv) {
  GLfloat lineVertexXAxis[] = {0, SCREEN_HEIGHT / 2.0, 0,
                               SCREEN_WIDTH, SCREEN_HEIGHT / 2.0, 0};
  GLfloat lineVertexYAxis[] = {SCREEN_WIDTH/2.0, 0, 0,
                               SCREEN_WIDTH/2.0, SCREEN_HEIGHT, 0};

  // region Run main loop
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Task 1", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glViewport(0.0f,
             0.0f,
             SCREEN_WIDTH,
             SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  int scale = 20; // scale for graph
  int point_size = 2;

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_line(lineVertexXAxis, 4.0, 0xAAAA); // draw X axis
    draw_line(lineVertexYAxis, 4.0, 0xAAAA); // draw Y axis

    for (GLfloat i = -6.0; i <= 6.0; i += 0.01) {
      GLfloat x = i;
      GLfloat y = func(x);
      if (std::isinf(y)){
        continue;
      }
      std::cout << "x = " << x << " y = " << y << std::endl;
      GLfloat point[] = {(scale*x+(SCREEN_WIDTH/2)), (scale*y+(SCREEN_HEIGHT/2))};
      draw_point_with_smooth(point, point_size);
    }


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
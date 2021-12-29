#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

void draw_point(GLfloat pointVertex[], GLfloat size) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glPointSize(size);
  glVertexPointer(2, GL_FLOAT, 0, pointVertex);
  glDrawArrays(GL_POINTS, 0, 1);
  glDisableClientState(GL_VERTEX_ARRAY);
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

GLfloat line_equation(GLfloat lineVertex[], GLfloat x) {
  GLfloat dx = lineVertex[3] - lineVertex[0]; // x2-x1
  GLfloat dy = lineVertex[4] - lineVertex[1]; //y2-y1
  GLfloat slope = dy / dx;
  GLfloat intercept = lineVertex[1] - slope * lineVertex[0];

  GLfloat y = slope * x + intercept;
  return y;
}

int main(int argc, char **argv) {
  float x1, y1, x2, y2;
  float line_h = 4.0;

  x1 = -(SCREEN_WIDTH / 5);
  y1 = (SCREEN_HEIGHT / 2.5);
  x2 = (SCREEN_WIDTH / 5);
  y2 = 0.0;

  GLfloat lineVertex1[] = {x1, y1, 0,
                          x2, y2, 0};

  GLfloat y3 = line_equation(lineVertex1, x1);
  GLfloat y4 = line_equation(lineVertex1, x2);

  GLfloat lineVertex2[] = {x1+200, y3, 0,
                           x2+200, y4, 0};

  int line_pattern = 0xFF00;


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

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_line(lineVertex1, line_h, line_pattern);
    draw_line(lineVertex2, line_h, line_pattern);

    for (int i = 1; i <= 1000; i += 100) {
      GLfloat size = ((i + 100) / 100) * 10;
      GLfloat x = i;
      GLfloat y = line_equation(lineVertex1, x);
      GLfloat point[] = {x, y};
      draw_point(point, size);
    }

    for (int i = 1; i <= 1000; i += 100) {
      GLfloat size = ((i + 100) / 100) * 10;
      GLfloat x = i;
      GLfloat y = line_equation(lineVertex2, x);
      GLfloat point[] = {x, y};
      draw_point_with_smooth(point, size);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  // endregion
  return 0;
}

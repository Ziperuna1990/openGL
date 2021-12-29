#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <linux/input.h>

#define WIDTH 650
#define HEIGHT 650

float vert[] = {1, 1, 0, 1, -1, 0, -1, -1, 0, -1, 1, 0};
float xAlfa = 20;

void show_world() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vert);
  glColor3f(0, 0.5, 0);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void move_camera() {
  // TODO: HOW TO KEY STATE???
  glRotatef(-xAlfa, 1, 0, 0);
  glTranslatef(0, 0, -3);
}

int main(int argc, char **argv) {

  // region Run main loop
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(WIDTH, HEIGHT, "Task 6", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

//  glViewport(0.0f,
//             0.0f,
//             WIDTH,
//             HEIGHT);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();

  glFrustum(-1, 1, -1, 1, 2, 8);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    move_camera();
    show_world();
    glPopMatrix();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}


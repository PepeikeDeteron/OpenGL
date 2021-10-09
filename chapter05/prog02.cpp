#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

// 線に色を付ける
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(0, 1, 0);

  glBegin(GL_LINE_LOOP);
  glVertex2d(-0.9, -0.9);
  glVertex2d(0.9, -0.9);
  glVertex2d(0.9, 0.9);
  glVertex2d(-0.9, 0.9);
  glEnd();

  glFlush();
}

void init(void) {
  glClearColor(0, 0, 1, 1);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();

  return 0;
}
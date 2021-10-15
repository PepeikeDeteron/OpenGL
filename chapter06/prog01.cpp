#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

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

// スクリーン上の表示領域をビューポートの大きさに比例させる
void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, -1.0);
}

void init(void) {
  glClearColor(0, 0, 1, 1);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();

  return 0;
}
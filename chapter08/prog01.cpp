#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

// 図形をy軸中心に25度回転させる
void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glRotated(25.0, 0.0, 1.0, 0.0);
  glColor3b(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9, -0.9);
  glColor3d(0.0, 1.0, 0.0);
  glVertex2d(0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0);
  glVertex2d(0.9, 0.9);
  glColor3d(1.0, 1.0, 0.0);
  glVertex2d(-0.9, 0.9);
  glEnd();
  glFlush();
}

void init(void) {
  glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc,char *argv[]) {
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 240);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();

  return 0;
}
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

// ウィンドウを青く塗りつぶす
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
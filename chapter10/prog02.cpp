#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 },
};

int face[][4] = {
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 },
};

GLdouble color[][3] = {
  { 1.0, 0.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 1.0, 0.0 },
  { 1.0, 0.0, 1.0 },
  { 0.0, 1.0, 1.0 },
};

void idle(void) {
  glutPostRedisplay();
}

// 隠面消去処理を行う（デプス・バッファ）
void display(void) {
  static int r = 0;

  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotated((double)r, 0.0, 1.0, 0.0);

  glColor3d(0.0, 0.0, 0.0);

  glBegin(GL_QUADS);

  for (int j = 0; j < 6; j++) {
    glColor3dv(color[j]);

    for (int i = 0; i < 4; i++) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }

  glEnd();

  glutSwapBuffers();

  if (r++ >= 360) r = 0;
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) glutIdleFunc(idle);
      else glutIdleFunc(0);
      break;

    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) glutPostRedisplay();
      break;

    default:
      break;
  }
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 'Q':
    case '\033':
      exit(0);

    default:
      break;
  }
}

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  init();
  glutMainLoop();

  return 0;
}
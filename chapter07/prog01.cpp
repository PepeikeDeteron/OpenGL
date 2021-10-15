#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#define MAXPOINTS 100       // 記憶する点の数
GLint point[MAXPOINTS][2];  // 座標を記憶する配列
int pointnum = 0;           // 記憶した座標の数

void display(void) {
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  // 記録したデータで線を描く
  if (pointnum > 1) {
    glColor3d(0.0, 0.0, 0.0);

    glBegin(GL_LINES);

    for (i = 0; i < pointnum; i++) glVertex2iv(point[i]);

    glEnd();
  }

  glFlush();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

// マウス・ボタンをクリックする
void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      // ボタンを操作した位置を記録する
      point[pointnum][0] = x;
      point[pointnum][1] = y;

      if (state == GLUT_UP) {
        // ボタンを押した位置から離した位置まで線を引く
        glColor3d(0.0, 0.0, 0.0);

        glBegin(GL_LINES);

        glVertex2iv(point[pointnum - 1]);
        glVertex2iv(point[pointnum]);

        glEnd();

        glFlush();
      }
      if (pointnum < MAXPOINTS - 1) pointnum++;
      break;

    case GLUT_MIDDLE_BUTTON:
      break;

    case GLUT_RIGHT_BUTTON:
      break;

    default:
      break;
  }
}

void init(void) {
  glClearColor(0, 0, 1, 1);
}

int main(int argc, char *argv[]) {
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 240);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);

  init();
  glutMainLoop();

  return 0;
}
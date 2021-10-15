#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#define MAXPOINTS 100       // 記憶する点の数
GLint point[MAXPOINTS][2];  // 座標を記憶する配列
int pointnum = 0;           // 記憶した座標の数
int rubberband = 0;         // ラバーバンドの消去

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

// マウスをドラッグする
void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      // ボタンを操作した位置を記録する
      point[pointnum][0] = x;
      point[pointnum][1] = y;

      // ボタンを押した位置から離した位置まで線を引く
      if (state == GLUT_UP) {
        glColor3d(0.0, 0.0, 0.0);

        glBegin(GL_LINES);

        glVertex2iv(point[pointnum - 1]);
        glVertex2iv(point[pointnum]);

        glEnd();

        glFlush();

        // 始点ではラバーバンドを書いていないので消さない
        rubberband = 0;
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

// マウスのドラッグ中は線分をバウスに追従して描くようにする
void motion(int x, int y) {
  static GLint savepoint[2];  // 以前のラバーバンドの端点

  // 論理演算機能 ON
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);

  // 以前のラバーバンドを消す
  if (rubberband) {
    glVertex2iv(point[pointnum - 1]);
    glVertex2iv(savepoint);
  }

  // 新しいラバーバンドを描く
  glVertex2iv(point[pointnum - 1]);
  glVertex2i(x, y);

  glEnd();

  glFlush();

  // 論理演算機能 OFF
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  // 今書いたラバーバンドの端点を保存
  savepoint[0] = x;
  savepoint[1] = y;

  // 今書いたラバーバンドは次のタイミングで消す
  rubberband = 1;
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
  glutMotionFunc(motion);

  init();
  glutMainLoop();

  return 0;
}
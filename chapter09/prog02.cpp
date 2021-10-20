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

int edge[][2] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },
  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },
  { 0, 4 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 },
};

void idle(void) {
  glutPostRedisplay();
}

// 図形を動かす
void display(void) {
  static int r = 0; // 回転角

  glLoadIdentity(); // 変換行列の初期化

  glClear(GL_COLOR_BUFFER_BIT);

  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 視点位置と視線方向
  glRotated((double)r, 0.0, 1.0, 0.0);                    // 図形の回転

  glColor3d(0.0, 0.0, 0.0);

  glBegin(GL_LINES);

  for (int i = 0; i < 12; i++) {
    glVertex3dv(vertex[edge[i][0]]);
    glVertex3dv(vertex[edge[i][1]]);
  }

  glEnd();

  glutSwapBuffers();  // ダブル・バッファリング

  if (r++ >= 360) r = 0;  // 一周回ったら回転角を 0 に戻す
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);  // 透視変換行列の設定
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);   // モデルビュー変換行列の設定
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    // マウスの左ボタンをクリックしている間、キューブが逆回転する
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) glutIdleFunc(idle);
      else glutIdleFunc(0);
      break;

    // マウスの右ボタンをクリックすると、キューブがフレーム毎に回転する
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
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  init();
  glutMainLoop();

  return 0;
}
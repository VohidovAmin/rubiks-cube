#include <GL/glut.h>
#include <iostream>

// Размер окна
const int windowWidth = 800;
const int windowHeight = 600;

// Углы поворота
float angleX = 0.0f;
float angleY = 0.0f;

// Инициализация OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

// Отрисовка кубика
void drawCube() {
    glutSolidCube(1.0);
}

// Отрисовка сцены
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);

    // Вращение кубика
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Отрисовка кубика
    drawCube();

    glutSwapBuffers();
}

// Обновление углов поворота
void update(int value) {
    angleX += 1.0f;
    angleY += 1.0f;
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

// Настройка камеры
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Rubik's Cube");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}

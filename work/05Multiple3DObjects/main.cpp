#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "RgbImage.h"

GLfloat xRotated, yRotated, zRotated;
GLuint texture[5];
GLint winWidth, winHeight;
GLboolean bAmbient;
GLfloat lx, ly, lz = 0.0;

void drawcuboid(void){ // 왼쪽 직사각형
    GLfloat vertices[][3] = {
        {-1., 1.5, -1.5}, {-1., 1.5, 1.5}, {1., 1.5, 1.5},
        {1., 1.5 , -1.5}, {-1., -1.5, -1.5}, {-1., -1.5, 1.5},
        {1., -1.5, 1.5}, { 1., -1.5, -1.5}
};
    glLoadIdentity();
    glTranslatef(-3.0, 0.0, -10);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[6]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[5]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[6]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[5]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[6]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[5]);

    glEnd();
}

void drawrectangular(void){ // 아래 직사각형
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
}

void drawsquare(void){ // cetner cube
    GLfloat vertices[][3] = {
        {-2., 1.5, -0.5}, {-2., 1.5, 0.5}, {2., 1.5, 0.5},
        {2., 1.5, -0.5}, {-2., -1.5, -0.5}, {-2., -1.5, 0.5},
        {2., -1.5, 0.5},{2., -1.5, -0.5}
};
    glLoadIdentity();
    glTranslatef(0.0, -4.0, -10);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[1]);

    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[6]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[5]);

    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[6]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]);

    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[4]);

    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[7]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[5]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[6]);

    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[4]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[0]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[1]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[5]);
    glEnd();
}

void drawteapot(void){
    glLoadIdentity();
    glTranslatef(-3.0, 0.0, -10.0);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glutSolidTeapot(1);
}

void drawsphere(void){
    glLoadIdentity();
    glTranslatef(0.0, 3.0, -10.0);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glutSolidSphere(1.0, 10, 10);
}

void drawpyramid(void){
    GLfloat vCorners[][5] = {
        {0.f, 1.f, 0.f}, {-1.f, 0.f, -1.f},
        {1.f, 0.f, -1.f}, {1.f, 0.f, 1.f}, {-1.f, 0.f, 1.f}
};
    glLoadIdentity();
    glTranslatef(3.0, 0.0, -10);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glBegin(GL_TRIANGLES);

    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vCorners[2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vCorners[4]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vCorners[1]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vCorners[2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vCorners[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vCorners[4]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vCorners[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vCorners[4]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vCorners[3]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vCorners[2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vCorners[1]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vCorners[0]);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vCorners[3]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vCorners[2]);
    glEnd();
}

void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = {1,1,-7,1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    GLfloat ambient[4] = {1,0,1,1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    drawrectangular();

    glBindTexture(GL_TEXTURE_2D,texture[1]);
    drawteapot();

    glBindTexture(GL_TEXTURE_2D,texture[2]);
    drawsphere();

    glBindTexture(GL_TEXTURE_2D,texture[3]);
    drawpyramid();

    glBindTexture(GL_TEXTURE_2D,texture[4]);
    drawsquare();


    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void loadTextureFromFile(char *filename1,char *filename2,char *filename3,char *filename4,char *filename5){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    RgbImage theTexMap1(filename1);
    RgbImage theTexMap2(filename2);
    RgbImage theTexMap3(filename3);
    RgbImage theTexMap4(filename4);
    RgbImage theTexMap5(filename5);

    glGenTextures(5, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap1.GetNumCols(), theTexMap1.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap1.ImageData());

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap2.GetNumCols(), theTexMap2.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap2.ImageData());

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap3.GetNumCols(), theTexMap3.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap3.ImageData());

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap4.GetNumCols(), theTexMap4.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap4.ImageData());

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap5.GetNumCols(), theTexMap5.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap5.ImageData());
}

void resizeWindow(int x, int y){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (GLdouble) x/(GLdouble)y, 0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
    case 'a':
        yRotated += 5;
        zRotated += 5;
    case '1':
        bAmbient = FALSE; break;
    case '2':
        bAmbient = TRUE; break;
    case 'j': lx -= 0.1; break;
    case 'l': lx += 0.1; break;
    case 'i': ly += 0.1; break;
    case 'k': ly -= 0.1; break;
    default:
        break;
    }
    drawScene();
}

char* filename1 = "grass.bmp";
char* filename2 = "floor.bmp";
char* filename3 = "floor.bmp";
char* filename4 = "floor.bmp";
char* filename5 = "floor.bmp";


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW#4");
    loadTextureFromFile(filename1, filename2, filename3, filename4, filename5);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(keyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

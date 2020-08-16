#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>


GLsizei winWidth = 600, winHeight = 500;
GLubyte label[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

GLint dataValue[12] = {420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438};
GLint dataValue_for_pie[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0, 3.0, 16.0, 5.0, 3.0, 17.0, 8.0};

void init(void){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-winWidth, winWidth, -winHeight, winHeight);
    //gluOrtho2D(0, winWidth, 0, winHeight);
}


void Writelabel(){
    glColor3f(1,1,1);
    glRasterPos2i(100,100);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'A');
    glRasterPos2i(150, 150);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'C');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'G');
    glFlush();
}

void drawline(int a, int b, int c, int d){
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    glVertex2i(a,b);
    glVertex2i(c,d);
    glEnd();
    glFlush();
}

void drawstar(int a, int b){
    glColor3f(1,0,0);
    glRasterPos2i(a,b);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
    glFlush();
}

void drawrect(int a, int b, int c, int d){
    glColor3f(1,0,0);
    glRecti(a,b,c,d);
    glFlush();
}

void drawcircle(){
    glColor3f(1,0,0);
    double rad = 100;
    glBegin(GL_LINE_STRIP);

    for (int i = 0;i<360;i++){
        double angle, x, y;
        angle = i*3.141592 / 180;
        x = rad*cos(angle);
        y = rad*sin(angle);
        glVertex2f(x,y);
        if (i == 90 || i == 215 || i == 300){
            glVertex2i(0,0);
            glVertex2i(x,y);
        }
    }
    glEnd();
    glFlush();
}

void linegraph(){
    for (int i = 1;i!=13;i++){
        drawstar(50*i-30, dataValue[i-1]);
    }
    for (int i = 1;i!=12;i++){
        drawline(50*i-30, dataValue[i-1], 50*(i+1)-30, dataValue[i]);
    }
    for (int i = 1; i!=13;i++){
        glColor3f(0,0,0);
        glRasterPos2i(50*i-30,150);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)]);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)+1]);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)+2]);
        glFlush();
    }
}

void barchart(){
    for (int i=1;i!=13;i++){
        drawrect(50*i-30, 175, 50*i-15, dataValue[i-1]);
    }
    for (int i = 1; i!=13;i++){
        glColor3f(0,0,0);
        glRasterPos2i(50*i-30,150);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)]);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)+1]);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[3*(i-1)+2]);
        glFlush();
    }
}

void piechart(){
    glColor3f(0,0,1);
    double rad = 100;
    glBegin(GL_LINE_STRIP);

    for (int i = 0;i<360;i++){
        double angle, x, y;
        angle = i*3.141592 / 180;
        x = rad*cos(angle);
        y = rad*sin(angle);
        glVertex2f(x,y);
        int temp = 360*dataValue_for_pie[0]/114;
        for (int j=0;j!=12;j++){
            if (i==temp){
                glVertex2i(0,0);
                glVertex2i(x,y);
            }
            temp+=360*dataValue_for_pie[j+1]/114;
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Pie Chart");
    init();
    glutDisplayFunc(piechart);
    glutMainLoop();
    return 0;
}

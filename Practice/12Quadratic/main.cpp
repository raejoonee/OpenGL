#include <gl\glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void init(void){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("HW_1");
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    gluOrtho2D(-100,100,-100,100);
}

void parabola(GLfloat x, GLfloat y){
    glBegin(GL_POINTS);
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat midpoint = (0.01)*x*x-y;
    for (GLint i = 0; i < 48; i++){
        if (midpoint < 0){
            midpoint += 0.02*x + 0.03;
        } else {
            y++;
            midpoint += 0.02*x - 0.97;
        }
        glVertex2f(x, y);
        glVertex2f(-x, y);
        x++;
    }
    for (GLint j = 0; j < 50; j++){
        if (midpoint < 0){
            midpoint += 0.02*x+midpoint;
        } else {
            midpoint += 0.02*x-midpoint;
            y+=midpoint;
        }
        glVertex2f(x-1, y);
        glVertex2f(-x+1, y);
        x++;
    }
    glEnd();
    glFlush();
}

void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    parabola(0,0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

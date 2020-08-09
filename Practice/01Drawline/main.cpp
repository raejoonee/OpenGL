#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLsizei winWidth = 1000, winHeight = 800;
GLint entPtCtr = 0;
class scrPt{
public:
    GLint x,y;
};

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,800.0);
}

void displayFcn(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
}

void mouseaction(GLint button, GLint action, GLint xMouse, GLint yMouse){
    printf("exp");
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        int x = xMouse;
        int y = winHeight - yMouse;
        printf("x = %d, ", x);
        printf("y = %d\n", y);
    }
}

scrPt a, b;
void drawline(GLint button, GLint action, GLint xMouse, GLint yMouse){
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && entPtCtr == 1){
        a.x = xMouse;
        a.y = winHeight - yMouse;
        printf("ax = %d, ", a.x);
        printf("ay = %d\n", a.y);
        glColor3f(0,0,1);
        glBegin(GL_LINE_STRIP);
        glVertex2i(b.x,b.y);
        glVertex2i(a.x,a.y);
        entPtCtr = 0;
    }
    else if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && entPtCtr == 0){
        b.x = xMouse;
        b.y = winHeight - yMouse;
        printf("bx = %d, ", b.x);
        printf("by = %d\n", b.y);
        entPtCtr = 1;
    }
    glEnd();
    glFlush();
}

/*void drawline(GLint button, GLint action, GLint xMouse, GLint yMouse){


    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && entPtCtr == 0){
                scrPt *b = new scrPt;
        b->x = xMouse;
        b->y = winHeight - yMouse;
        printf("bx = %d, ", b->x);
        printf("by = %d\n", b->y);
        entPtCtr = 1;
    }
    else if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && entPtCtr == 1){
            scrPt *a = new scrPt;
        a->x = xMouse;
        a->y = winHeight - yMouse;
        printf("ax = %d, ", a->x);
        printf("ay = %d\n", a->y);
        glColor3f(0,0,1);
        glBegin(GL_LINE_STRIP);
        glVertex2i(b->x,b->y);
        glVertex2i(a->x,a->y);
        entPtCtr = 0;
    }
    glEnd();
    glFlush();
}*/

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,800);
    glutCreateWindow("Draw Line");
    init();
    glutDisplayFunc(displayFcn);
    glutMouseFunc(mouseaction);
    glutMouseFunc(drawline);
    glutMainLoop();
    return 0;
}

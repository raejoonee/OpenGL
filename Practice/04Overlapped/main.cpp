#include <gl/glut.h>

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    gluLookAt(-1,-1,5,0,0,0,0,1,0);
    glutSolidCube(1);

    glColor3f(1,0,0);
    glTranslatef(0.1,0.1,1.0);
    glutSolidCube(1);

    glFlush();
}

int main(){
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("overlapped");

    glClearColor(1,1,1,1);
    glutDisplayFunc(myDisplay);
    glFrustum(-1,1,-1,1,5,10);
    //glFrustum(-1,1,-1,1,3,20);

    glutMainLoop();

    return 0;
}

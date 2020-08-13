#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

void init(){
    glClearColor(1.0,1.0,1.0,0.0);
}

void displayFcn(){
    GLfloat ctrlPts[4][3] = {{-40.0,-40.0,0.0},{-10.0,200.0,0.0},
    {10.0,-200.0,0.0},{40.0,40.0,0.0}};

    glMap1f(GL_MAP1_VERTEX_3, 0.0,1.0,3,4,*ctrlPts);
    glEnable(GL_MAP1_VERTEX_3);

    gluOrtho2D(-210,210,-210,210);
    glClear(GL_COLOR_BUFFER_BIT);
    GLint k;

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_STRIP);
    for(k=0;k<=50;k++) glEvalCoord1f(GLfloat(k)/50.0);
    glEnd();

    glColor3f(1.0,0.0,0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(k=0;k<4;k++) glVertex3fv(&ctrlPts[k][0]);
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(420,420);
    glutCreateWindow("opengl Bezier curve");

    init();
    glutDisplayFunc(displayFcn);
    glutMainLoop();

    return 0;

}

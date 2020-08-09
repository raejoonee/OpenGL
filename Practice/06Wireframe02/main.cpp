#include <GL/glut.h>

GLsizei winWidth = 500, winHeight = 500;

void init(void){

    glClearColor(1.0,1.0,1.0,1.0);

}



void displayWirePolyhedra(){

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.0,1.0);

    gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);



    glBegin(GL_LINES);

        glColor3f(1.0,0.0,0.0);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(10.0,0.0,0.0);



        glColor3f(0.0,1.0,0.0);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(0.0,10.0,0.0);



        glColor3f(0.0,0.0,1.0);

        glVertex3f(0.0,0.0,0.0);

        glVertex3f(0.0,0.0,10.0);

    glEnd();



    glPushMatrix();

    //glScalef(1.2,1.0,1.0);

    //glTranslatef(1.0,0.0,0.0);

    //glRotatef(30.0,0.0,1.0,0.0);

    glutWireCube(1.0);

    glPopMatrix();

    glFlush();

}



void wireQuadSurfs(){

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.0,1.0);



    gluLookAt(2.0,2.0,2.0,0.0,0.0,0.0,0.0,0.0,1.0);



    glPushMatrix();

    glTranslatef(1.0,1.0,1.0);

    glutWireSphere(0.75,8,6);

    glPopMatrix();



    glPushMatrix();

    glTranslatef(1.0,-0.5,0.5);

    glutWireCone(0.7,2.0,7,6);

    glPopMatrix();



    GLUquadricObj *cylinder;

    glPushMatrix();

    glTranslatef(0.0,1.2,0.8);

    cylinder = gluNewQuadric();

    gluQuadricDrawStyle(cylinder, GLU_LINE);

    gluCylinder(cylinder,0.6,0.6,1.5,6,4);

    glPopMatrix();

    glFlush();

}



int main(int argc, char **argv){

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowPosition(100,100);

    glutInitWindowSize(winWidth,winHeight);

    glutCreateWindow("wire-Frame Quaric Surfaces");

    init();

    glutDisplayFunc(wireQuadSurfs);

    glOrtho(-2.0,2.0,-2.0,2.0,0.0,5.0);

    glutMainLoop();

}

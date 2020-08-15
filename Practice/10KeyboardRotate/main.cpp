#include <gl/glut.h>
#include <stdio.h>

void myDisplay();

void myKeyboard(unsigned char key, int x, int y);

GLfloat lx, ly, lz = -1.0;
GLfloat xAngle, yAngle, zAngle;

GLboolean bAmbient;


int main(){
    glutCreateWindow("Practice");
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();

    return 0;

}

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
    printf("%d", int(key));

    case 'a':yAngle += 2; break;
    case 'd':yAngle -= 2; break;
    case 'w':xAngle += 2; break;
    case 's':xAngle -= 2; break;
    case 'q':zAngle += 2; break;
    case 'e':zAngle -= 2; break;

    case 'j': lx -= 0.1; break;
    case 'l': lx += 0.1; break;
    case 'i': ly += 0.1; break;
    case 'k': ly -= 0.1; break;

    case 'r': xAngle = yAngle = zAngle = 0.0;
    lx=ly=0; break;

    case '1':
        bAmbient = FALSE; break;
    case '2':
        bAmbient = TRUE; break;
    }

    char info[128];
    sprintf(info, "x=%.1f, y=%.1f, z=%.1f", xAngle, yAngle, zAngle);
    glutSetWindowTitle(info);
    glutPostRedisplay();
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = {lx, ly, lz, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    if (bAmbient){
        GLfloat ambient[4] = {1,0,0,1};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    } else {
        GLfloat ambient[4] = {0,0,0,0};
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    }

    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    glutSolidTeapot(0.5);
    glPopMatrix();
    glFlush();
}

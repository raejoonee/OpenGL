#include <stdlib.h>
#include <GL/glut.h>
#include "RgbImage.h"

GLfloat xRotated, yRotated, zRotated;
GLuint texture[2];
GLfloat lx, ly, lz = 0.0;
GLboolean bAmbient;


void loadTextureFromFile(char *filename1, char *filename2){
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    RgbImage theTexMap1( filename1 );
    RgbImage theTexMap2( filename2 );

    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap1.GetNumCols(), theTexMap1.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap1.ImageData());

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap2.GetNumCols(), theTexMap2.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap2.ImageData());

}

void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
       glEnable(GL_TEXTURE_2D);
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

//    glPopMatrix();

//    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-5);
    glRotatef(yRotated, 0, 1, 0);
    glRotatef(zRotated, 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        //glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
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

    glEnd();


    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
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
//    glPopMatrix();
 glPopMatrix();

    glFlush();
    glDisable(GL_TEXTURE_2D);
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

char* filename1 = "C://grass.bmp";
char* filename2 = "C://floor.bmp";

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Texture");
    loadTextureFromFile(filename1, filename2);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

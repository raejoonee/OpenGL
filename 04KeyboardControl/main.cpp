#include <math.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdlib.h>
GLsizei winWidth=1000, winHeight=1000;
typedef float vec3_t[3];
vec3_t rot = {0.,0.,0.};
vec3_t eye = {0.,0.,-5.};
vec3_t center = {0.,0.,0.};
vec3_t trans = {0.,0.,0.};
vec3_t scale = {0.3,0.3,0.3};

float theta = .0;
float thetaDelta = .125;
float eyeDelta = .125; // added
float centerDelta = .125; // added
float scaleDelta = 1.125; // changed the value
float transitionDelta = .125; // added

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q': // when the object moves in the x-axis direction
            trans[0] += transitionDelta;
            break;
        case 'w': // when the object moves in the y-axis direction
            trans[1] += transitionDelta;
            break;
        case 'e': // when the object moves in the z-axis direction
            trans[2] += transitionDelta;
            break;
        case 'a': // when the object rotates around the x-axis
            rot[0] += thetaDelta;
            break;
        case 's': // when the object rotates around the y-axis
            rot[1] += thetaDelta;
            break;
        case 'd': // when the object rotates around the z-axis
            rot[2] += thetaDelta;
            break;
        case 'z': // when the object scales centered by x-axis
            scale[0] *= scaleDelta;
            break;
        case 'x': // when the object scales centered by y-axis
            scale[1] *= scaleDelta;
            break;
        case 'c': // when the object scales centered by z-axis
            scale[2] *= scaleDelta;
            break;
        case 'j': // when the camera moves sideways while focusing on certain coordinate
            eye[0] += eyeDelta;
            break;
        case 'k': // when the camera moves closer to the object while focusing on certain coordinate
            eye[0] -= eyeDelta;
            eye[1] -= eyeDelta;
            eye[2] -= eyeDelta;
            break;
        case 'l': // when the camera moves sideways with fixed VPN
            eye[0] += eyeDelta;
            center[0] += centerDelta;
            break;
        case ';': // case [2](3)
            rot[0] += thetaDelta;
            eye[2] += eyeDelta;
            break;
    }
    glutPostRedisplay();
}

void myDisplay(){
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],0,1,0);

    glRotatef(rot[0],1.0f,0.0f,0.0f);
    glRotatef(rot[1],0.0f,1.0f,0.0f);
    glRotatef(rot[2],0.0f,0.0f,1.0f);
    glScalef(scale[0],scale[1],scale[2]);
    glPushMatrix();
    glTranslatef(trans[0],trans[1],trans[2]);
    glColor3f(0.7333,0.6902,0.8627);
    glutSolidCube(60);
    glColor3f(0.0,0.0,0.0);
    glutWireCube(60);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void myLookAt(int key){
    if(key == GLUT_KEY_UP){
        eye[2] = eye[2] + 3;
    }
    else if(key == GLUT_KEY_DOWN){
        eye[2] = eye[2] - 3;
    }
    else if(key == GLUT_KEY_LEFT){
        eye[1] = eye[1] - 3;
    }
    else if(key == GLUT_KEY_RIGHT){
        eye[0] = eye[0] + 3;
    }
}

void myResize(int width, int height){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.,(float)width/height,.1,100.);
    eye[0] = 20;
    eye[1] = 30;
    eye[2] = 40;
    myLookAt(0);
    glEnable(GL_DEPTH_TEST);
    winWidth = width;
    winHeight = height;
}

int main(int argc, char **argv){
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(900,500);
    glutCreateWindow("04KeyboardControl");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myResize);
    glutKeyboardFunc(myKeyboard);

    glutMainLoop();
    return 0;
}

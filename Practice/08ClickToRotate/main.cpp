#include <math.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
//우클릭 하면 트랜스포트 하면 됨
//z,x버튼 스케일 변함
//eye를 관찰자 시점의 중점을 변환시키는 것

typedef float vec3_t[3];
vec3_t rot = {0.,0.,0.};
vec3_t eye = {0.,0.,-5.};
vec3_t center = {0.,0.,0.};
vec3_t trans = {0.,0.,0.};

float size = 20;
float theta = .0;
float thetaDelta = .125;
float eyeDelta = .125;
float scale = 0.3;
float scaleDelta = 1.125;
float R = 0;
float G = 0;
float B = 0;
int i, j;
int mouseX = 0;
int mouseY = 0;
int mouseState = 0;
int mouseButton = 0;
int projection = 0;
int depthOn = 0;
int fillOn = 1;
int windowWidth, windowHeight;
float height = 0.01;
float antiheight = 5;
float antitheta = .0;
float antithetaDelta = 0.125;

GLUquadricObj *c = NULL;

void myDisplay(){
    glClearColor(R,G,B,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(!projection)
        gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],0,1,0);
    glRotatef(rot[0],1.0f,0.0f,0.0f);
    glRotatef(rot[1],0.0f,1.0f,0.0f);
    glRotated(rot[2],0.0f,0.0f,1.0f);
    glScalef(scale, scale, scale);
    glRotatef(-80.,1.,0.,0.);

    glPushMatrix();

    glTranslatef(trans[0], 0.0, 0.0);
    glTranslatef(0.0, trans[1], 1.0);
    glTranslatef(0.0, 0.0, trans[2]);

    glScalef(1,1,1);
    glColor3f(1.0,0.0,0.0);
    if(fillOn) glutSolidCube(60);
    glColor3f(0,0,0);
    glutWireCube(60);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void myLookAt(int key){
    /*if (key == GLUT_KEY_UP){
        eye[2] = eye[2]-3;
    } else if (key == GLUT_KEY_DOWN){
        eye[2] = eye[2]+3;
    } else if (key == GLUT_KEY_LEFT){
        eye[1] = eye[1]-3;
    } else if (key == GLUT_KEY_RIGHT){
        eye[0] = eye[0]+3;
    }*/
    if (key == GLUT_KEY_UP){
        center[1] = center[1]-3;
    } else if (key == GLUT_KEY_DOWN){
        center[1] = center[1]+3;
    } else if (key == GLUT_KEY_LEFT){
        center[0] = center[0]-3;
    } else if (key == GLUT_KEY_RIGHT){
        center[0] = center[0]+3;
    }
}

void myResize(int width, int height){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(projection){
        glOrtho(-size*1.75,size*1.75,-size,size,-size*2,size*2);
        eye[2]=0;
    } else {
        gluPerspective(60., (float)width/height,.1,100.);
        eye[2]=38;
        myLookAt(0);
    }
    glEnable(GL_DEPTH_TEST);
    windowWidth = width;
    windowHeight = height;
}

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
    case 'f':
        fillOn = !fillOn;
    case 'p':
        projection = !projection;
        myResize(windowWidth, windowHeight);
        break;
    case 'd':
        depthOn = !depthOn;
        if(depthOn) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
        break;
    case '1':
        R = rand()/32767.0;
        G = rand()/32767.0;
        B = rand()/32767.0;
        break;
    case 'n':
        R = 0;
        G = 0;
        B = 0;
        break;
    case 'q':
        exit(1);
        break;
    case 27:
        exit(1);
        break;
    case 'z':
        scale *= 0.99;
        break;
    case 'x':
        scale *= 1.01;
        break;
    }
    glutPostRedisplay();
}

void myMouse(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    } else if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP){
        mouseState=-1;
    } else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    } else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        mouseState=-1;
    } else return;

    glutPostRedisplay();
}

void myMotion(int x, int y){
    if (mouseButton == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN){
        rot[1] -= (mouseX-x)/5.;
        rot[0] -= (mouseY-y)/5.;
        glutPostRedisplay();
        mouseX = x;
        mouseY = y;
    }
    else if (mouseButton == GLUT_RIGHT_BUTTON && mouseState == GLUT_DOWN){
        trans[1] += (mouseX-x)/5.;
        trans[0] += (mouseY-y)/5.;
        glutPostRedisplay();
        mouseX = x;
        mouseY = y;
    }
}

void mySKeyboard(int key, int x, int y){
    switch(key){
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    case GLUT_KEY_LEFT:
        theta -= thetaDelta;
        break;
    case GLUT_KEY_RIGHT:
        theta += thetaDelta;
        break;
        default:return;
    }
    myLookAt(key);
    glutPostRedisplay();
}

int main(int argc, char** argv){
    srand((unsigned int)time(0));
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(900,500);
    glutCreateWindow("Test_OpenGL_1114");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myResize);
    //glutKeyboardFunc(myKeyboard);
    //glutSpecialFunc(mySKeyboard);
    //glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutMainLoop();

    return 0;

}



#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

#include <gl/gl.h>

#include <time.h>

#include <stdlib.h>

#include <ctime>

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

int i,j;

int mouseX = 0;

int mouseY = 0;

int mouseState=0;

int mouseButton=0;

int projection = 0;

int depthOn = 0;

int fillOn = 1;

int windowWidth, windowHeight;

float height = 0.01;

float antiheight = 5;

float antitheta = .0;

float antithetaDelta = 0.125;



GLUquadricObj * c =NULL;



void myDisplay(){

    GLfloat v0,s,theta,alpha,tx,ty;

    printf("Enter v0,theta,s,alpha\n");

    scanf("%f %f %f %f",&v0,&theta,&s,&alpha);

    tx = 0;

    ty = 0;

    glClearColor(1.0,1.0,1.0,0.0);

    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],0,1,0);

    glRotatef(rot[0],1.0f,0.0f,0.0f);

    glRotatef(rot[1],0.0f,1.0f,0.0f);

    glRotatef(rot[2],0.0f,0.0f,1.0f);

    glScalef(scale,scale,scale);

    glPushMatrix();

    glTranslatef(tx,ty,0.);

    glColor3f(1.0,0.0,0.0);

    glutSolidCube(10);

    glColor3f(0,0,0);

    glutWireCube(10);

    glPopMatrix();

    rot[0] += alpha;

    rot[1] += alpha;

    rot[2] += alpha;



    for(int t=1;t<100;t++){

        tx = v0 * cos(theta) * t;

        ty = v0 * sin(theta) * t - 5*t*t;

        if(ty < 0) break;

        glRotatef(rot[0],1.0f,0.0f,0.0f);

        glRotatef(rot[1],0.0f,1.0f,0.0f);

        glRotatef(rot[2],0.0f,0.0f,1.0f);

        glPushMatrix();

        glTranslatef(tx,ty,0);

        glScalef(s,s,s);

        glColor3f(1.0,0.0,0.0);

        glutSolidCube(10);

        glColor3f(0,0,0);

        glutSolidCube(10);

        glColor3f(0,0,0);

        glutWireCube(10);

        glPopMatrix();

        printf("[%d] %f %f %f\n",t,rot[0],rot[1],s);

    }

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

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    if(projection){

        glOrtho(-size*1.75,size*1.75,-size,size,-size*2,size*2);

        eye[2] = 0;

    }

    else{

        gluPerspective(60.,(float)width/height,.1,100.);

        eye[2] = 38;

        myLookAt(0);

    }

    glEnable(GL_DEPTH_TEST);

    windowWidth = width;

    windowHeight = height;

}

int main(int argc, char **argv){

    srand((unsigned int)time(0));

    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

    glutInitWindowSize(900,500);

    glutCreateWindow("Test_OpenGL_1114");

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

    glutDisplayFunc(myDisplay);

    glutReshapeFunc(myResize);

    glutMainLoop();

    return 0;

}

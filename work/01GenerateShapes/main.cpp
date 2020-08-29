#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

GLsizei winWidth = 600, winHeight = 600;
int N;

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    gluOrtho2D(-winWidth, winWidth, -winHeight, winHeight);
    glClear(GL_COLOR_BUFFER_BIT);
}

#define random_MAX 32767
double rv = random_MAX;

void drawline(){
    //Color
    glColor3f(rand()/rv, rand()/rv, rand()/rv);

    //Width
    glLineWidth(rand()%14+1);

    glBegin(GL_LINE_STRIP);

    //Randomized Coordinate
    glVertex2i(rand()%1200-600,rand()%1200-600);
    glVertex2i(rand()%1200-600,rand()%1200-600);

    glEnd();
    glFlush();
}

void drawrect(){
    //Coordinate Range Condition
    int x = rand()%1200-600;
    int y = rand()%1200-600;
    int side = rand()%600;

    while (x + side > winWidth || y + side > winHeight){
        x = rand()%1200-600;
        y = rand()%1200-600;
        side = rand()%600;
    }

    //Color
    glColor3f(rand()/rv, rand()/rv, rand()/rv);

    //Width
    glLineWidth(rand()%14+1);

    //Fill or not
    if (rand()%2) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON);

    //Coordinate
    glVertex2i(x, y);
    glVertex2i(x, y + side);
    glVertex2i(x + side, y + side);
    glVertex2i(x + side, y);

    glEnd();
    glFlush();
}

void drawtri(){
    //Coordinate Range Condition
    int x = rand()%1200-600;
    int y = rand()%1200-600;
    int side = rand()%600;

    while (x + side > winWidth || sqrt(3)*side/2 + y > winHeight){
        x = rand()%1200-600;
        y = rand()%1200-600;
        side = rand()%600;
    }

    //Color
    glColor3f(rand()/rv, rand()/rv, rand()/rv);

    //Width
    glLineWidth(rand()%14+1);

    //Fill or not
    if (rand()%2) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON);

    //Coordinate
    glVertex2i(x, y);
    glVertex2i(x + side, y);
    glVertex2i(x + (side/2), sqrt(3)*side/2 + y);

    glEnd();
    glFlush();
}

void drawcircle(){
    if (rand()%2) glBegin(GL_LINE_STRIP);
    else glBegin(GL_POLYGON);
    glColor3f(rand()/rv,rand()/rv,rand()/rv);
    int rad = rand()%300;
    int add1 = rand()%300;
    int add2 = rand()%300;
    float val1, val2;
    if (rand()%2) val1 = 1;
    else val1 = -1;
    if (rand()%2) val2 = 1;
    else val2 = -1;
    for (int i = 0;i<361;i++){
        double angle, x, y;
        angle = i*3.141592 / 180;
        x = rad*cos(angle);
        y = rad*sin(angle);
        glVertex2f(val1*(x+add1),val2*(y+add2));
    }
    glEnd();
    glFlush();
}

void hw2(){
    for(int i = 0;i < N;i++){
        if(rand()%4 == 0){
            drawline();
        } else if (rand()%4 == 1){
            drawrect();
        } else if (rand()%4 == 2){
            drawtri();
        } else {
            drawcircle();
        }
    }
}

int main(int argc, char** argv){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("HW#2-1");

    init();
    scanf("%d", &N);
    glutDisplayFunc(hw2);
    glutMainLoop();

    return 0;
}

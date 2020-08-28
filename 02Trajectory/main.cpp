
#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

GLsizei winWidth=600, winHeight=600;

GLfloat xwcMin=0.0, xwcMax=400.0;

GLfloat ywcMin=0.0, ywcMax=400.0;

//100 2.356944 0.9 0.43355



class wcPt2D{

public:

    GLfloat x,y;

};

wcPt2D Verts[3] = {};

typedef GLfloat Matrix3x3[3][3];

Matrix3x3 matComposite;



void init(void){

    glClearColor(1.0, 1.0, 1.0, 0.0);

}



void matrix3x3SetIdentity(Matrix3x3 matIdent3x3){

    GLint row,col;

    for(row=0; row<3; row++){

        for(col=0; col<3; col++)

            matIdent3x3[row][col]= (row == col);

    }

}

void matrix3x3PreMultiply(Matrix3x3 m1, Matrix3x3 m2){

    GLint row, col;

    Matrix3x3 matTemp;



    for(row=0; row<3; row++){

        for(col=0; col<3; col++)

            matTemp[row][col]= m1[row][0]*m2[0][col] + m1[row][1]*m2[1][col] + m1[row][2]*m2[2][col];

    }

    for(row=0; row<3; row++){

        for(col=0; col<3; col++)

            m2[row][col]= matTemp[row][col];

    }

}

void translate2D(GLfloat tx, GLfloat ty){

    Matrix3x3 matTransl;

    matrix3x3SetIdentity(matTransl);



    matTransl[0][2] = tx;

    matTransl[1][2] = ty;



    matrix3x3PreMultiply(matTransl, matComposite);

}

void rotate2D(wcPt2D pivotPt,GLfloat theta){

    Matrix3x3 matRot;

    matrix3x3SetIdentity(matRot);



    matRot[0][0] = cos(theta);

    matRot[0][1] = -sin(theta);

    matRot[0][2] = pivotPt.x*(1-cos(theta)) + pivotPt.y*(sin(theta));

    matRot[1][0] = sin(theta);

    matRot[1][1] = cos(theta);

    matRot[1][2] = pivotPt.y*(1-cos(theta)) -pivotPt.x*(sin(theta));



    matrix3x3PreMultiply(matRot, matComposite);

}

void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt){

    Matrix3x3 matScale;

    matrix3x3SetIdentity(matScale);



    matScale[0][0] = sx;

    matScale[0][2] = (1-sx) * fixedPt.x;

    matScale[1][1] = sy;

    matScale[1][2] = (1-sy) * fixedPt.y;



    matrix3x3PreMultiply(matScale, matComposite);

}



void transformVerts2D(GLint nVerts, wcPt2D* verts){

    GLint k;

    GLfloat temp;

    for(k=0; k<nVerts; k++){

        temp = matComposite[0][0] * verts[k].x + matComposite[0][1]*verts[k].y + matComposite[0][2];

        Verts[k].y = matComposite[1][0]*verts[k].x + matComposite[1][1]*verts[k].y + matComposite[1][2];

        Verts[k].x = temp;

    }

}

void triangle(wcPt2D* verts){

    GLint k;

    glBegin(GL_TRIANGLES);

    for(k=0; k<3; k++)

        glVertex2f(verts[k].x, verts[k].y);

    glEnd();

}

void displayFcn(){

    GLfloat v0;

    GLfloat tx,ty,fixtx,fixty;

    GLfloat s;

    GLfloat theta,alpha;

    printf("Enter v0, theta, s, alpha\n>");

    scanf("%f %f %f %f",&v0,&theta, &s, &alpha);

    printf("%f %f %f\n",v0,theta,sin(theta));

    GLint nVerts = 3;



    wcPt2D centroidPt;

    wcPt2D pivPt, fixedPt;



    tx = v0 * cos(theta);

    ty = v0 * sin(theta) - 5;

    centroidPt.x = tx;

    centroidPt.y = ty;

    fixtx = tx;

    fixty = ty;

    pivPt = centroidPt;

    fixedPt = centroidPt;



    Verts[0].x = tx - 25;

    Verts[0].y = ty - 25;

    Verts[1].x = tx + 25;

    Verts[1].y = ty - 25;

    Verts[2].x = tx;

    Verts[2].y = ty + 50;



    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    triangle(Verts);



    matrix3x3SetIdentity(matComposite);

    for(int k=2; k<100; k+=2.5){



        scale2D(s,s,fixedPt);

        rotate2D(pivPt,alpha);

        translate2D(-tx,-ty);

        tx = v0 * cos(theta) * k;

        ty = v0 * sin(theta) * k - 5*k*k;

        printf("[%d] %f %f\n%f %f\n%f %f\n",k,Verts[0].x,Verts[0].y,Verts[1].x,Verts[1].y,tx,ty);

        translate2D(tx,ty);

        transformVerts2D(nVerts,Verts);

        glColor3f(0.0,0.0,0.0);



        if(Verts[0].y < fixty){

            break;

        }

        triangle(Verts);



        matrix3x3SetIdentity(matComposite);

        centroidPt.x = tx;

        centroidPt.y = ty;

        pivPt = centroidPt;

        fixedPt = centroidPt;

    }

    glFlush();

}



void winReshapeFcn(GLint newWidth, GLint newHeight){

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-xwcMax*3,0, -ywcMax*3/2,ywcMax*3/2);

    glClear(GL_COLOR_BUFFER_BIT);

}

int main(int argc, char** argv){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(50,50);

    glutInitWindowSize(winWidth,winHeight);

    glutCreateWindow("2");



    init();

    glutDisplayFunc(displayFcn);

    glutReshapeFunc(winReshapeFcn);



    glutMainLoop();



    return 0;

}

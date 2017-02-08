//  meGrHw5
//  This program displays a world with trees, buildings, and birds
//  Controls:
//            m-up;n-down;l-right;j-left:i-forward;k-back;
//            right mouse click-rotates around y-axis
//  Created by Melinda on 3/13/16.
//
//
#include <stdio.h>
#include <glut/glut.h>		    //chage for grading
#include <math.h>
#include <stdlib.h>

#define pi 3.14159
#define N 10
int w = 800;
int h = 800;
float phi = 0.5;
float x=0.0,y=0.0,z=0.0;
//int bird_x, bird_z;
float theta=5;
double step=0.5;
int waitTime=100;

float bird_x, bird_z;

/*specify vertices for treeOne*/
GLfloat treeTop[N][3],treeBot[N][3], treeOneLeaves1[N][3],treeOneLeaves2[N][3];
/*specify vertices for treeTwo*/
GLfloat treeTwoLeaves1[N][3],treeTwoLeaves2[N][3];
/*specify vertices for treeThree*/
GLfloat treeThreeLeaves1[N][3],treeThreeLeaves2[N][3],treeThreeLeaves3[N][3],treeThreeLeaves4[N][3];

GLfloat viewer[3]={3.0,4.0,15.0}; //maybe change

/*prototypes*/
void ground(void);
void myDisplay(void);
void init(void);
void polygon(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat v4[3], float a,float b,float c);
void makeTreesOne(void);
void makeTreesTwo(void);
void makeTreesThree(void);
void makeBuildings(void);
void keyBoard(unsigned char key, int x, int y);
void timerFunction(int value);
void makeCone(void);

/*initialization function*/
void init(void)
{
    glClearColor(0.0,0.74,1.0,1.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*perspective projection */
    gluPerspective(60.0, 1.0, 2.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

/* The display callback function */
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(viewer[0], viewer[1], viewer[2],
                    x, y, z, 0.0, 1.0, 0.0);
    //draw ground
    ground();
    
    //first treeOne
    glPushMatrix();
    glTranslatef(0.0, 0.0, -7.0);
    makeTreesOne();
    glPopMatrix();

    // second treeOne
    glPushMatrix();
    glTranslatef(6.0, 0.0, -7.0);
    makeTreesOne();
    glPopMatrix();
 
    // third treeOne
    glPushMatrix();
    glTranslatef(-6.0, 0.0, -7.0);
    makeTreesOne();
    glPopMatrix();
  
    //first treeTwo
    glPushMatrix();
    glTranslatef(-5.0, 0.0, 7.0);
    makeTreesTwo();
    glPopMatrix();
   
    // second treeTwo
    glPushMatrix();
    glTranslatef(5.0, 0.0, 7.0);
    makeTreesTwo();
    glPopMatrix();
    
    // third treeTwo
    glPushMatrix();
    glTranslatef(0.0, 0.0, 7.0);
    makeTreesTwo();
    glPopMatrix();
    
    //first treeThree
    glPushMatrix();
    glTranslatef(8.0, 0.0, 0.0);
    makeTreesThree();
    glPopMatrix();
    
    // second treeThree
    glPushMatrix();
    glTranslatef(-8.0, 0.0, 0.0);
    makeTreesThree();
    glPopMatrix();
    
    //first building
    glPushMatrix();
    glColor3f(0.95,0.64,0.37);
    glTranslatef(-4.0, 0.0, -4.0);
    makeBuildings();
    glPopMatrix();
    
    //second building
    glPushMatrix();
    glColor3f(0.95,0.58,0.47);
    glTranslatef(4.0, 0.0, -4.0);
    makeBuildings();
    glPopMatrix();
    
    //third building
    glPushMatrix();
    glColor3f(0.69,0.13,0.13);
    glTranslatef(-4.0, 0.0, 4.0);
    makeBuildings();
    glPopMatrix();
    
    //fourth building
    glPushMatrix();
    glColor3f(0.82,0.70,0.54);
    glTranslatef(4.0, 0.0, 4.0);
    makeBuildings();
    glPopMatrix();
    
    //the sun
    glPushMatrix();
    glColor3f(1.0,1.0,0.0);
    glTranslatef(0.0, 7.0, 0.0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    
    //bush one
    glPushMatrix();
    glColor3f(0.4,0.8,0.0);
    glTranslatef(-8.0,0,-6.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    
    //bush two
    glPushMatrix();
    glColor3f(0.6,0.8,0.19);
    glTranslatef(8.0, 0.0, -3.0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    
    //bush three
    glPushMatrix();
    glColor3f(0.0,0.93,0.46);
    glTranslatef(8.0, 0.0, 3.0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    
    //bush four
    glPushMatrix();
    glColor3f(0.0,0.54,0.0);
    glTranslatef(-8.0, 0.0, 3.0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    
    //birds
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(9.0);
    glBegin(GL_POINTS);
    glVertex3f( bird_x,6.0,bird_z);
    glEnd();
    glPopMatrix();
    
    //birds
    glPushMatrix();
    glTranslatef(-3.0, 0.0, 3.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glVertex3f( -bird_x,3.0,bird_z);
    glEnd();
    glPopMatrix();
    
    //birds
    glPushMatrix();
    glTranslatef(3.0, 0.0, 3.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(8.0);
    glBegin(GL_POINTS);
    glVertex3f( -bird_x,3.0,-bird_z);
    glEnd();
    glPopMatrix();
    
    //cone
    glPushMatrix();
    makeCone();
    glPopMatrix();
    
    
    glutSwapBuffers();
    
}

/*draws the ground*/
void ground(void) {
    
    int i, j;
    glColor3f(0.0,1.0,0.0);
    glLineWidth(10);
    for (i = 0; i < 20; i++) {
        glBegin(GL_LINES);
        glVertex3f(-10.0 + i, -1.0, 10.0);
        glVertex3f(-10.0 + i, -1.0, -10.0);
        glEnd();
    }
    
    for (j = 0; j < 20; j++){
        glBegin(GL_LINES);
        glVertex3f(-10.0, -1.0, 10.0 - j);
        glVertex3f(10.0, -1.0, 10.0 - j);
        glEnd();
    }
}

/*make vertices*/
void makeVertices(void)
{
    float t;
    for(int i=0;i<N;i++)
    {
        t = i * 2 * pi / N;
        treeTop[i][0] = 0.25 * cos(t);
        treeTop[i][1] = -1;
        treeTop[i][2] = 0.25 * sin(t);
        
        treeBot[i][0] = 0.25 *cos(t);
        treeBot[i][1] = 1;
        treeBot[i][2] = 0.25 * sin(t);
        
        treeOneLeaves1[i][0] = 0.6 * cos(t);
        treeOneLeaves1[i][1] = 1;
        treeOneLeaves1[i][2] = 0.6 * sin(t);
        
        treeOneLeaves2[i][0] = 0.01 * cos(t);;
        treeOneLeaves2[i][1] = 2;
        treeOneLeaves2[i][2] = 0.01 * sin(t);;
        
        treeTwoLeaves1[i][0] = 1.5 * cos(t);
        treeTwoLeaves1[i][1] = 1;
        treeTwoLeaves1[i][2] = 1.5 * sin(t);
        
        treeTwoLeaves2[i][0] = 0.6 * cos(t);;
        treeTwoLeaves2[i][1] = 2;
        treeTwoLeaves2[i][2] = 0.6 * sin(t);;
        
        treeThreeLeaves1[i][0] =0.05*cos(t);
        treeThreeLeaves1[i][1] =2;
        treeThreeLeaves1[i][2] =0.05*sin(t);
        
        treeThreeLeaves2[i][0] =0.5*cos(t);
        treeThreeLeaves2[i][1] =1;
        treeThreeLeaves2[i][2] =0.5*sin(t);
        
        treeThreeLeaves3[i][0] =0.05*cos(t);
        treeThreeLeaves3[i][1] =2;
        treeThreeLeaves3[i][2] =0.05*sin(t);
        
        treeThreeLeaves4[i][0] = 0.8*cos(t);
        treeThreeLeaves4[i][1] = -1;
        treeThreeLeaves4[i][2] = 0.8*sin(t);
    }
}

/*buildings*/
void makeBuildings(void)
{
    //buildings
    glBegin(GL_POLYGON);
    //front
    glVertex3f(  1.0, -1.0, -1.0 );
    glVertex3f(  1.0,  3.0, -1.0 );
    glVertex3f( -1.0,  3.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glEnd();
    //right
    glBegin(GL_POLYGON);
    glVertex3f( 1.0, -1.0, -1.0 );
    glVertex3f( 1.0,  3.0, -1.0 );
    glVertex3f( 1.0,  3.0,  1.0 );
    glVertex3f( 1.0, -1.0,  1.0 );
    glEnd();
    //back
    glBegin(GL_POLYGON);
    glVertex3f(  1.0, -1.0, 1.0 );
    glVertex3f(  1.0,  3.0, 1.0 );
    glVertex3f( -1.0,  3.0, 1.0 );
    glVertex3f( -1.0, -1.0, 1.0 );
    glEnd();
    //left
    glBegin(GL_POLYGON);
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f( -1.0,  3.0,  1.0 );
    glVertex3f( -1.0,  3.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glEnd();
    //top
    glBegin(GL_POLYGON);
    glVertex3f(  1.0,  1.0, 1.0 );
    glVertex3f(  1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0, 1.0);
    glEnd();
    // bottom
    glBegin(GL_POLYGON);
    glVertex3f(  1.0, -1.0, -1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glEnd();
}

/*draw cone*/
void makeCone(void)
{
    int i,j,k;
    makeVertices();
    for(i=0; i<N;i++)
    {
        j=i; k=i+1;
        if(k==N)
            k=0;
        //draw cone
        polygon(treeThreeLeaves4[j], treeThreeLeaves4[k], treeOneLeaves2[k], treeOneLeaves2[j], 1.0,0.0,0.0);
    }
}

/*draws first tree*/
void makeTreesOne(void)
{
    int i,j,k;
    makeVertices();
    for(i=0; i<N;i++)
    {
        j=i; k=i+1;
        if(k==N)
            k=0;
        //stump
        polygon(treeBot[j], treeBot[k], treeTop[k], treeTop[j], 0.5,0.35,0.05);
        //leaves
        polygon(treeOneLeaves1[j], treeOneLeaves1[k], treeOneLeaves2[k],treeOneLeaves2[j], 0.0,1.0,0.0);
    }
}

/*draws second tree*/
void makeTreesTwo(void)
{
    int i,j,k;
    makeVertices();
    for(i=0; i<N;i++)
    {
        j=i; k=i+1;
        if(k==N)
            k=0;
        //stump
        polygon(treeBot[j], treeBot[k], treeTop[k], treeTop[j], 0.5,0.35,0.05);
        //leaves
        polygon(treeTwoLeaves1[j], treeTwoLeaves1[k], treeTwoLeaves2[k],treeTwoLeaves2[j], 0.2,0.6,0.2);
    }
}

/*draws third tree*/
void makeTreesThree(void)
{
    int i,j,k;
    makeVertices();
    for(i=0; i<N;i++)
    {
        j=i; k=i+1;
        if(k==N)
            k=0;
        
        polygon(treeThreeLeaves2[j], treeThreeLeaves2[k], treeThreeLeaves1[k], treeThreeLeaves1[j], 0.0,0.8,0.2);
        polygon(treeThreeLeaves3[j], treeThreeLeaves3[k], treeThreeLeaves2[k],treeThreeLeaves2[j], 0.0,0.8,0.2);
        polygon(treeThreeLeaves4[j], treeThreeLeaves4[k], treeThreeLeaves3[k],treeThreeLeaves3[j], 0.0,0.8,0.2);
        
    }
}

void timerFunction(int value)
{
    bird_x = 5*cos(theta);
    bird_z = 5*sin(theta);
    
    theta+=step;
    glutPostRedisplay();
    glutTimerFunc(waitTime, timerFunction,1);
    
}

void keyBoard(unsigned char key, int a, int b)
{
    if( key=='I' || key=='i')//forward
    {
        viewer[2]-= 0.5;
        z=-0.5;
    }
    if( key=='L' || key=='l')//right
    {
        viewer[0]+= 0.5;
        x+=0.5;
    }
    if( key=='K' || key=='k')//back
    {
        viewer[2]+= 0.5;
        z+=0.5;
    }
    if( key=='J' || key=='j')//left
    {
        viewer[0]-= 0.5;
        x-=0.5;
    }
    if(key =='m'||key =='M')//up
    {
        viewer[1]+=0.5;
        y+=0.5;
    }
    if(key == 'n'|| key =='N')
    {
        viewer[1]-=0.5;
        y-=0.5;
    }
    glutPostRedisplay();
}

/* Change the camera position*/
void mouse(int btn, int state, int i, int j) {
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        
    viewer[0] = 15.0 * sin(phi);
    viewer[2] = 15.0 * cos(phi);
        phi += 0.05;
    glutPostRedisplay();
}

/* Build and color a polygon */
void polygon(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat v4[3], float a,float b,float c)
{
    glColor3f(a,b,c);
    glBegin(GL_POLYGON);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v4);
    glEnd();
}

/* The main function */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    /* Need both double buffering and z buffer */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(800,800);
    glutCreateWindow("Trees, Buildings and Birds");
    init();
    glutDisplayFunc(myDisplay);
    glutTimerFunc(waitTime,timerFunction,1);
    glutKeyboardFunc(keyBoard);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST); 		/* Enable hidden-surface removal */
    glutMainLoop();
    return 0;
}
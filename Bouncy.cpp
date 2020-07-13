#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#ifdef _WIN32
	  #include <windows.h>
	#endif
	
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif
#include<iostream>
#include<stdio.h>
#include<stdlib.h>	
#include<math.h>


#define PI 3.14159265f

GLfloat ballRadius = 0.5f;						//Radius of the bouncing ball
GLfloat ballX = 0.0f;							//Center position of ball; x
GLfloat ballY = 0.0f;							//y position
GLfloat ballXMax, ballXMin, ballYMax, ballYMin; //Bounds
static GLfloat xSpeed = 0.02f;							//Speed: x
static GLfloat ySpeed = 0.007f;						//Speed: y
int refreshMillis = 30;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void initGL()
{
	glClearColor(0.38, 0.38, 0.38, 1.0);
}

//---------------Increase/Decrease speed of ball -----------------------
static void increase_speed(void)
{
    	xSpeed = xSpeed * 2.0;
    	ySpeed = ySpeed * 2.0;
}

static void decrease_speed(void)
{
    	xSpeed = xSpeed / 2.0;
    	ySpeed = ySpeed / 2.0;
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			increase_speed();
			break;	
		case GLUT_KEY_DOWN:
			decrease_speed();
			break;
		//case GLUT_KEY_LEFT:
		//	RIGHT_Button();
		//	break;
		//case GLUT_KEY_RIGHT:
		//do something here
		//	break;
	}
}
//----------------------------------------------------------------------

//----------------- Quiting using Q key --------------------------------
static void KeyboardButton( unsigned char Key, int x, int y )
{
   	switch ( Key )
	{
        case 'q':
		case 'Q': 
           		exit(1);
	}
}

//----------------------------------------------------------------------

//----------------- Displaying Text ------------------------------------
void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}
void drawStrokeText(char*string,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	 // glScalef(0.09f,-0.08f,z);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}
void render(void)
{ 
	//glClear(GL_COLOR_BUFFER_BIT); 
	//glLoadIdentity();
 
	glColor3f(1,0,0);
	drawStrokeText("Osama Hosam's OpenGL Tutorials",200,200,0);

	//glutSwapBuffers(); 
	
} 

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(ballX, ballY, 0.0f);
	
	//xSpeed += change;
	//ySpeed += change;
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.2f, 0.0f, 0.2f);
	glVertex2f(0.0f, 0.0f);
	
	int numSegments = 100;
	
	GLfloat angle;
	
	for(int i = 0; i<=numSegments; i++)
	{
		angle = i* 2.0f * PI/numSegments;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();
	
	glutSwapBuffers();
	
	ballX += xSpeed;
	ballY += ySpeed;
	
	if( ballX > ballXMax)
	{
		ballX = ballXMax;
		xSpeed = -xSpeed;
	}
	else if(ballX < ballXMin)
	{
		ballX = ballXMin;
		xSpeed = -xSpeed;
	}


	if( ballY > ballYMax)
	{
		ballY = ballYMax;
		ySpeed = -ySpeed;
	}
	else if(ballY < ballYMin)
	{
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}
	
	//render();
}

void reshape(GLsizei width, GLsizei height)
{
	if(height == 0)
		height = 1;
	GLfloat aspect = (GLfloat) width/ (GLfloat) height;
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(width >= height)
	{
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else
	{
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0  /aspect;
	}
	
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius; 
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;
	
	//gluOrtho2D(0,width,height,0); 
    //glMatrixMode(GL_MODELVIEW); 
    //glLoadIdentity(); 
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 100;
int windowPosY = 100;

int main(int argc, char** argv)
{
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(windowWidth, windowHeight );
    glutInitWindowPosition( windowPosX, windowPosY );
    glutCreateWindow( "Bouncing Ball using Simple OpenGL" );
	initGL();
	glutReshapeFunc( reshape );
	

	glutDisplayFunc( display );

	
	glutKeyboardFunc( KeyboardButton );
	glutSpecialFunc(SpecialInput);
	glutTimerFunc(0, Timer, 0);
 	glutMainLoop();
	return(0);  

	
	
}
		

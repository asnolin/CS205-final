/*
 * MUST COMPILE WITH -lGL AND -lglut FLAGS TO LINK PROPERLY WITH g++ 
 *
 */

#include<GL/glut.h>
//define height and width of window
GLuint WIDTH = 600;
GLuint HEIGHT = 600;


//initGL is a function from my CS120 code. I do not know what it does
void initGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,WIDTH, HEIGHT, 0.0, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char **argv){
	//init GLUT window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0,0); //position of window's initiial top-left corner
	//
	
	int mainWindow = glutCreateWindow("testing");
	initGL();
	//glutDisplayFunc()
	//glutKeyboardFunc()
	glutMainLoop();
	return 0;
}//end main

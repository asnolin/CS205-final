#include<GL/glut.h>

int main(int argc, char **argv){
	//init GLUT
	glutInit(&argc, argv);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	int mainWindow = glutCreateWindow("testing");
	//register callbacks
	//enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}//end main

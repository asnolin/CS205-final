

#include <string.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
enum screen_type {start};

/** These are the live variables passed into GLUI ***/
bool   running = false;
int   numOfLines = 3;
int   main_window;
GLdouble width, height;
screen_type screen;

/***************************************** myGlutIdle() ***********/


void myGlutIdle()
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  glutPostRedisplay();
}


void init() {
    screen = start;

    width = 1000;
    height = 1000;


}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}

void display_start() {

    std::string meanTimeInStoreTxt = "Mean Time-In-Store: ";
    glColor3f(0, 0, 0);
    glRasterPos2i(40, 80);
    for (int i = 0; i < meanTimeInStoreTxt.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, meanTimeInStoreTxt[i]);
    }

    std::string customersTxt = "Total number of customers: ";
    glColor3f(0, 0, 0);
    glRasterPos2i(40, 180);
    for (int i = 0; i < customersTxt.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, customersTxt[i]);
    }

    for (int i = 1; i<numOfLines+1; ++i){
      int newY = 30*i;
      std::string lineTxt = "Customer line #" + std::to_string(i) + ": ";
      glColor3f(0, 0, 0);
      glRasterPos2i(40, (280 + newY));
      for (int i = 0; i < lineTxt.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lineTxt[i]);
      }
    }
}


/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    switch(screen) {
        case start: display_start();
            break;
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(main_window);
        exit(0);
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {

    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {



    glutPostRedisplay();
}

void timer(int extra) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(300, 300); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    main_window = glutCreateWindow("Store" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop


  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  GLUI *glui = GLUI_Master.create_glui( "GLUI");
  GLUI_Spinner *spin = glui -> add_spinner("Number of Lines:", GLUI_SPINNER_INT,&numOfLines );
  spin->set_int_limits( 1, 10 );
  // spin->set_w(1000);

  glui->set_main_gfx_window( main_window );

  /* We register the idle callback with GLUI, *not* with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle );

  glutMainLoop();

  return 0;
}

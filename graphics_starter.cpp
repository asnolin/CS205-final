#include "shape.h"
#include "Store.hpp"
#include <string.h>
#include <GLUT/glut.h>
//#include <GL/glui.h>
//#include <GL/glu.h>
#include <vector>
#include <iostream>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace std;

string int_to_string(int i);

//variables
GLdouble width, height;
int wd;
int   numOfLines = 3;
Rectangles r1(980,150,(color){1,1,1},(point){10,10});
Rectangles r2(270,150,(color){1,1,1},(point){1000,10});
Rectangles r3(980,600,(color){1,1,1},(point){10,170});
Rectangles r4(270,600,(color){1,1,1},(point){1000,170});

Store theStore;
EventNode<Customer, CheckoutLine> E;

void myGlutIdle()
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != wd )
    glutSetWindow(wd);

  glutPostRedisplay();
}


void init() {
    width = 1280;
    height = 780;
    srand48((long) time(NULL));
    theStore.setTime(0);

    int i;
    for(i = 0; i < 4; i++)
    {
      CheckoutLine *L = new CheckoutLine();
      theStore.addCheckoutLine(L);
    }

    EventNode<Customer,CheckoutLine> E;

    theStore.EventQ.make_event(0, NULL, 0 , NULL,0, CUSTOMER_ARRIVES);

    // theStore.setTime(E.get_time());
    // E = theStore.EventQ.pop();

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque

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
    //draw string

    string time = "- " + to_string(theStore.getTime()) + " -";
    string meanTimeInStore = "Mean Time-In-Store |";
    string meanWaitTime = "Mean Waiting Time";
    string eventQtitle = "Event Queue";
    string storeTitle = "Grocery Store";
    string totalNumberofShopper = "Total Number of Shoppers";
    string chekcoutLine1 = "Checkout Line #1";
    string chekcoutLine2 = "Checkout Line #2";
    string chekcoutLine3 = "Checkout Line #3";
    string chekcoutLine4 = "Checkout Line #4";
    string chekcoutLine5 = "Checkout Line #5";
    string chekcoutLine6 = "Checkout Line #6";
    string chekcoutLine7 = "Checkout Line #7";
    string chekcoutLine8 = "Checkout Line #8";
    string chekcoutLine9 = "Checkout Line #9";
    string chekcoutLine10 = "Checkout Line #10";

    //basic background
    r1.draw();
    r2.draw();
    r3.draw();
    r4.draw();

    //set color to black
    glColor3f(0, 0, 0);
    // set for time
    glRasterPos2i(480, 50);
    for (int i = 0; i < time.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, time[i]);
    }
    // set for event queue title
    glRasterPos2i(1070, 90);
    for (int i = 0; i < eventQtitle.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, eventQtitle[i]);
    }
    // set for mean time in store
    glRasterPos2i(280, 90);
    for (int i = 0; i < meanTimeInStore.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, meanTimeInStore[i]);
    }
    // set for mean time wait in store
    glRasterPos2i(520, 90);
    for (int i = 0; i < meanWaitTime.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, meanWaitTime[i]);
    }
    // set for store title
    glRasterPos2i(450, 200);
    for (int i = 0; i < storeTitle.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, storeTitle[i]);
    }
    // set for total number of shoppers in store
    glRasterPos2i(375, 220);
    for (int i = 0; i < totalNumberofShopper.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, totalNumberofShopper[i]);
    }
    for (int i = 0; i<theStore.Lines.size(); ++i)
    {
      int newY =45*i;
      std::string lineTxt = "Customer line #" + std::to_string(theStore.Lines[i]->getID()) + ": ";
      glColor3f(0, 0, 0);
      glRasterPos2i(50, (240 + newY));
      for (int j = 0; j < lineTxt.length(); ++j)
      {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lineTxt[j]);
      }

      for (int k = 0; k<theStore.Lines[i]->customerLine.size(); ++k)
      {
        glRasterPos2i(200+((k+1)*50), (240 + newY));
        string nmTimes = std::to_string(theStore.Lines[i]->customerLine[k].getNumItems());
        for (int l = 0; l < lineTxt.length(); ++l)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, nmTimes[l]);
        }
      }
    }


    vector<string> vecEvents = theStore.EventQ.to_str();
    for(int i = 0; i < vecEvents.size(); i++)
    {
      glRasterPos2i(1025, 200+(20*i));
      for (int l = 0; l < vecEvents[i].length(); ++l)
      {
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, vecEvents[i][l]);
      }
    }



    E = theStore.EventQ.pop();
    theStore.setTime(E.get_time());
    theStore.handleEvent(E);
    glFlush();  // Render now
    //std::this_thread::sleep_for (std::chrono::seconds(1));
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {


    //glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {



    glutPostRedisplay();
}

void timer(int dummy) {

    glutTimerFunc(2000, timer, 0);
    glutPostRedisplay();

}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fun with Drawing!" /* title */ );

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

    // /****************************************/
    // /*         Here's the GLUI code         */
    // /****************************************/
    //
    // GLUI *glui = GLUI_Master.create_glui( "GLUI");
    // GLUI_Spinner *spin = glui -> add_spinner("Number of Lines:", GLUI_SPINNER_INT,&numOfLines );
    // spin->set_int_limits( 1, 10 );
    // // spin->set_w(1000);
    //
    // glui->set_main_gfx_window( wd );
    //
    // /* We register the idle callmain_windowback with GLUI, *not* with GLUT */
    // GLUI_Master.set_glutIdleFunc( myGlutIdle );
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
string int_to_string(int i){
    char t[256];
    sprintf(t, "%d", i);
    string s = t;
    return s;
}

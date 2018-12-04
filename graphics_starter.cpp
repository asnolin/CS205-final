#include "graphics.h"
#include "shape.h"
#include "Customer.hpp"
#include <string>

using namespace std;

string int_to_string(int i);

//variables
GLdouble width, height;
int wd;
Rectangles r1(980,150,{1,1,1},{10,10});
Rectangles r2(270,150,{1,1,1},{1000,10});
Rectangles r3(980,600,{1,1,1},{10,170});
Rectangles r4(270,600,{1,1,1},{1000,170});
Customer c1(2);
string c1Id = int_to_string(c1.getId());

void init() {
    width = 1280;
    height = 780;
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

    string time = "TIME";
    string meanTimeInStore = "Mean Time-In-Store |";
    string meanWaitTime = "Mean Waiting Time";
    string eventQtitle = "Event Quene";
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
    glRasterPos2i(1070, 50);
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
    glRasterPos2i(375, 240);
    for (int i = 0; i < c1Id.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c1Id[i]);
    }
    glFlush();  // Render now
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


    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {



    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
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
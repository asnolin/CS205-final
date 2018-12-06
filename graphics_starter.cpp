#include "shape.h"
#include "Store.hpp"
#include <string.h>
#include <GLUT/glut.h>
//#include <GL/glui.h>
//#include <GL/glu.h>
#include <vector>
#include <iostream>

using namespace std;

string int_to_string(int i);
string dub_to_string(double i);
//variables
GLdouble width, height;
int wd;
int numLines = 10;
Rectangles r1(980,150,(color){1,1,1},(point){10,10});
Rectangles r2(270,150,(color){1,1,1},(point){1000,10});
Rectangles r3(980,600,(color){1,1,1},(point){10,170});
Rectangles r4(270,600,(color){1,1,1},(point){1000,170});
//function buttons
Rectangles Start(70,50,(color){0,200,0},(point){400,700});
Rectangles Stop(70,50,(color){1,0,0},(point){500,700});

//strategy buttons
Rectangles s1(70,50,(color){0,0,0.2},(point){600,700});
Rectangles s2(70,50,(color){0,0,1},(point){700,700});
Rectangles s3(70,50,(color){0,0,1},(point){800,700});
Rectangles s4(70,50,(color){0,0,1},(point){900,700});

Rectangles HelpBox(40,40,(color){0.9,0.2,0},(point){20,720});

vector<Rectangles> ExpressBoxes;
vector<Rectangles> StatusBoxes;


int LaneLimit = 0;

Store theStore;
EventNode<Customer, CheckoutLine> E;

bool Run = false;
bool ShowHelp = false;

int Show = 0;

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
    for(i = 0; i < numLines; i++)
    {
      CheckoutLine *L = new CheckoutLine();
      theStore.addCheckoutLine(L);
    }

    for(int i = 0; i < numLines; i++)
    {
      Rectangles r(20,20,(color){0,0,1},(point){15,(230+(45*i))});
      ExpressBoxes.push_back(r);
    }

    for(int i = 0; i < numLines; i++)
    {
      Rectangles r(20,20,(color){0,1,0},(point){40,(230+(45*i))});
      StatusBoxes.push_back(r);
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

    string stime = "- " + to_string(theStore.getTime()) + " -";
    string avgWaitTime = "Avg Wait Time: " + dub_to_string(theStore.getAvgWaitTime());
    string checkoutRate = "Checkouts Per Hour: " + dub_to_string(theStore.getCheckoutRate());
    string eventQtitle = "Event Queue";
    string storeTitle = "Super Market";
    string totalNumberofShopper = "Shoppers In Store: " + int_to_string(theStore.Shopping.size());
    string start = "Start";
    string stop = "Stop";
    string strategy = "Strategies";
    //basic background
    if(Show == 0)
    {
      r1.draw();
      r2.draw();
      r3.draw();
      r4.draw();
      s1.draw();
      s2.draw();
      s3.draw();
      s4.draw();
      Start.draw();
      Stop.draw();
      HelpBox.draw();

      for(int i = 0; i < numLines; i++)
      {
        ExpressBoxes[i].draw();
        StatusBoxes[i].draw();
      }
      glColor3f(0, 0, 0);
      glRasterPos2i(730, 685);
      for (int i = 0; i < strategy.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strategy[i]);
      }
      glRasterPos2i(410, 730);
      for (int i = 0; i < start.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
      }
      //stop
      glRasterPos2i(515, 730);
      for (int i = 0; i < stop.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stop[i]);
      }
    //set color to black
    glColor3f(0, 0, 1);
    glRasterPos2i(15, 700);
    string ExLaneLabel = "Express Lane Limit: " + to_string(LaneLimit);
    for (int i = 0; i < ExLaneLabel.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ExLaneLabel[i]);
    }

    glColor3f(0, 0, 0);
    glRasterPos2i(35, 745);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('?'));

    if(!ShowHelp)
    {
      // set for time
      glColor3f(0, 0, 0);
      glRasterPos2i(480, 50);
      for (int i = 0; i < stime.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stime[i]);
      }

      // set for total number of shoppers in store
      glRasterPos2i(30, 90);
      for (int i = 0; i < totalNumberofShopper.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, totalNumberofShopper[i]);
      }

      // set for mean time in store
      glRasterPos2i(280, 90);
      for (int i = 0; i < avgWaitTime.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, avgWaitTime[i]);
      }
      // set for mean time wait in store
      glRasterPos2i(550, 90);
      for (int i = 0; i < checkoutRate.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, checkoutRate[i]);
      }


    }
    else
    {
      //set color to black
      glColor3f(0, 0, 0);
      glRasterPos2i(20, 40);
      string ExLaneLabel2 = "*Use Up and Down Arrow Keys to Change Express Lane Limit*";
      for (int i = 0; i < ExLaneLabel2.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ExLaneLabel2[i]);
      }
      //set color to black
      glColor3f(0, 0, 0);
      glRasterPos2i(20, 70);
      string ExLaneLabel3 = "*Click Blue Boxes Next to Checkout Lines to Toggle Express Lane*";
      for (int i = 0; i < ExLaneLabel3.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ExLaneLabel3[i]);
      }

      //set color to black
      glColor3f(0, 0, 0);
      glRasterPos2i(20, 100);
      string ExLaneLabel4 = "*Click Red/Green Boxes Next to Checkout Lines to Open/Close Them*";
      for (int i = 0; i < ExLaneLabel4.length(); ++i) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ExLaneLabel4[i]);
      }
    }

    // set for event queue title
    glRasterPos2i(1070, 90);
    for (int i = 0; i < eventQtitle.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, eventQtitle[i]);
    }

    // set for store title
    glRasterPos2i(450, 210);
    for (int i = 0; i < string("Super Market").length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string("Super Market")[i]);
    }

    for (int i = 0; i<theStore.Lines.size(); ++i)
    {
      int newY =45*i;

      if(theStore.Lines[i]->getItemLimit() != 100)
      {
        if(theStore.Lines[i]->getItemLimit() < 10)
        {
          glRasterPos2i(22, (245 + newY));
        }
        else
        {
          glRasterPos2i(18, (245 + newY));
        }
        string strLimit = int_to_string(theStore.Lines[i]->getItemLimit());
        for (int j = 0; j < strLimit.length(); ++j)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, strLimit[j]);
        }
      }

      std::string lineTxt = "Checkout Line #" + std::to_string(theStore.Lines[i]->getID()) + ": ";

      glColor3f(0, 0, 0);
      glRasterPos2i(65, (250 + newY));
      for (int j = 0; j < lineTxt.length(); ++j)
      {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lineTxt[j]);
      }

      for (int k = 0; k<theStore.Lines[i]->customerLine.size(); ++k)
      {
        glRasterPos2i(255+(k*85), (250 + newY));
        string nmTimes = "(" + std::to_string(theStore.Lines[i]->customerLine[k].getId()) + ")" + std::to_string(theStore.Lines[i]->customerLine[k].getNumItems());
        for (int l = 0; l < lineTxt.length(); ++l)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, nmTimes[l]);
        }
        if(k > 6) break;
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

    if(Run)
    {
      E = theStore.EventQ.pop();
      theStore.setTime(E.get_time());
      theStore.handleEvent(E);
    }
  }

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

        case GLUT_KEY_UP:
          LaneLimit++;
          break;

        case GLUT_KEY_DOWN:
          if(LaneLimit>0) LaneLimit--;
          break;

        case GLUT_KEY_LEFT:

          break;

        case GLUT_KEY_RIGHT:

          break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    if(Start.pointOverlap(x,y)) {
        Run = true;
    }
    if(Stop.pointOverlap(x,y)){
        Run = false;
    }
    if(s1.pointOverlap(x,y)){
        s1.set_fill(0,0,0.2);
        s2.set_fill(0,0,1);
        s3.set_fill(0,0,1);
        s4.set_fill(0,0,1);
    }
    if(s2.pointOverlap(x,y)){
        s2.set_fill(0,0,0.2);
        s1.set_fill(0,0,1);
        s3.set_fill(0,0,1);
        s4.set_fill(0,0,1);
    }
    if(s3.pointOverlap(x,y)){
        s3.set_fill(0,0,0.2);
        s2.set_fill(0,0,1);
        s1.set_fill(0,0,1);
        s4.set_fill(0,0,1);
    }
    if(s4.pointOverlap(x,y)){
        s4.set_fill(0,0,0.2);
        s2.set_fill(0,0,1);
        s3.set_fill(0,0,1);
        s1.set_fill(0,0,1);
    }

    if(button==GLUT_LEFT_BUTTON & state==GLUT_DOWN & HelpBox.pointOverlap(x,y))
    {
      if(ShowHelp==true) ShowHelp=false;
      else ShowHelp=true;
    }

    if(button==GLUT_LEFT_BUTTON & state==GLUT_DOWN)
    {
      for(int i=0; i<numLines; i++)
      {
        if(ExpressBoxes[i].pointOverlap(x,y) & i!=0)
        {
          if(theStore.Lines[i]->getItemLimit() == 100)
          {
            theStore.Lines[i]->setItemLimit(LaneLimit);
            ExpressBoxes[i].set_fill((color){0.5,0,0.8});
          }
          else
          {
            theStore.Lines[i]->setItemLimit(100);
            ExpressBoxes[i].set_fill((color){0,0,1});
          }
        }
        if(StatusBoxes[i].pointOverlap(x,y) & i!=0)
        {
          if(theStore.Lines[i]->getStatus())
          {
            theStore.Lines[i]->togStatus();
            StatusBoxes[i].set_fill((color){1,0,0});
          }
          else
          {
            theStore.Lines[i]->togStatus();
            StatusBoxes[i].set_fill((color){0,1,0});
          }
        }
      }
    }

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
    wd = glutCreateWindow("Super Market Simulation" /* title */ );

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

string dub_to_string(double i)
{
  char t[256];
  sprintf(t, "%.2f", i);
  string s = t;
  return s;
}

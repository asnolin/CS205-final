#include "Graphics.h"
#include "Store.hpp"
#include "shape.h"

#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

//Functions
string intToString(int i);
string dubToString(double i);

/* Global Variables */

GLdouble Width;
GLdouble Height;
int wd;
int numLines = 10;

//Background Shapes
Rectangles Background1(980,150,(color){1,1,1},(point){10,10});
Rectangles Background2(270,150,(color){1,1,1},(point){1000,10});
Rectangles Background3(980,600,(color){1,1,1},(point){10,170});
Rectangles Background4(270,600,(color){1,1,1},(point){1000,170});

//Start and Stop Buttons
Rectangles buttonStart(70,50,(color){0,200,0},(point){400,700});
Rectangles buttonStop(70,50,(color){1,0,0},(point){500,700});

//Line Joining Strategy Buttons
Rectangles buttonStrat1(70,50,(color){0,0,0.2},(point){600,700});
Rectangles buttonStrat2(70,50,(color){0,0,1},(point){700,700});
Rectangles buttonStrat3(70,50,(color){0,0,1},(point){800,700});
Rectangles buttonStrat4(70,50,(color){0,0,1},(point){900,700});

//Help Button
Rectangles buttonHelp(40,40,(color){0.9,0.2,0},(point){20,720});

//Buttons Next to Checkout Lines
vector<Rectangles> buttonsExpress;
vector<Rectangles> buttonsStatus;

//Express Lane Limit
int ExpressLimit = 0;

//Initialize The Store
Store theStore;
EventNode<Customer, CheckoutLine> E;

//Display Booleans
bool Run = false;
bool ShowHelp = false;

int Show = 0;

void myGlutIdle()
{
    if ( glutGetWindow() != wd ) glutSetWindow(wd);
    glutPostRedisplay();
}

//Initialize the Store and the GUI
void init()
{
    Width = 1280;
    Height = 780;

    srand48((long) time(NULL));

    theStore.setTime(0);

    //Create 10 CheckoutLines
    for(int i = 0; i < numLines; i++)
    {
        CheckoutLine *L = new CheckoutLine();
        theStore.addCheckoutLine(L);
    }

    //Create Express Lane Buttons Next to Each Checkout Line
    for(int i = 0; i < numLines; i++)
    {
        Rectangles r(20,20,(color){0,0,1},(point){15,(230+(45*i))});
        buttonsExpress.push_back(r);
    }

    //Create Open/Closed Button Next to Each Checkout Line
    for(int i = 0; i < numLines; i++)
    {
        Rectangles r(20,20,(color){0,1,0},(point){40,(230+(45*i))});
        buttonsStatus.push_back(r);
    }

    //Create First Event to Kick Off Simulation
    theStore.EventQ.make_event(0, NULL, 0 , NULL,0, CUSTOMER_ARRIVES);
}

//Initialize OpenGL Graphics
void initGL()
{
    // Set Background Color (Black and Opaque)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//Handler for Window-Repaint Event, Call When the Window First Appears and Whenever its Re-Painted
void display()
{
    // Lots of GLUT Neccessities
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, Width, Height, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //=======================================================

    Background1.draw();
    Background2.draw();
    Background3.draw();
    Background4.draw();

    //=======================================================

    //Draw Store Statistics
    if(!ShowHelp)
    {
        //Set Color to Black
        glColor3f(0, 0, 0);

        string strTime = "- " + intToString(theStore.getTime()) + " -";
        glRasterPos2i(480, 50);
        for (int i = 0; i < strTime.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strTime[i]);
        }

        string strNumShoppers = "Shoppers In Store: " + intToString(theStore.Shopping.size());
        glRasterPos2i(30, 90);
        for (int i = 0; i < strNumShoppers.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strNumShoppers[i]);
        }

        string strWaitTime = "Avg Wait Time: " + dubToString(theStore.getAvgWaitTime());
        glRasterPos2i(280, 90);
        for (int i = 0; i < strWaitTime.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strWaitTime[i]);
        }

        string strCheckoutRate = "Checkouts Per Hour: " + dubToString(theStore.getCheckoutRate());
        glRasterPos2i(550, 90);
        for (int i = 0; i < strCheckoutRate.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strCheckoutRate[i]);
        }
    }
    //Draw Help Window
    else
    {
        //Set Color to Black
        glColor3f(0, 0, 0);

        glRasterPos2i(20, 40);
        string strHelp1 = "Customers In Checkout Lines are Formatted: (ID)NumItems";
        for (int i = 0; i < strHelp1.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strHelp1[i]);
        }

        glRasterPos2i(20, 65);
        string strHelp2 = "Click Red/Green Boxes Next to Checkout Lines to Open/Close Them";
        for (int i = 0; i < strHelp2.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strHelp2[i]);
        }

        glRasterPos2i(20, 90);
        string strHelp3 = "Click Blue Boxes Next to Checkout Lines to Toggle Express Lane";
        for (int i = 0; i < strHelp3.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strHelp3[i]);
        }

        glRasterPos2i(20, 115);
        string strHelp4 = "Use Up and Down Arrow Keys to Change Express Lane Limit";
        for (int i = 0; i < strHelp4.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strHelp4[i]);
        }

        string strHelp5 = "Line Joining Strategy: 1 = Random | 2 = Min Customers | 3 = Min Items | 4 = Min Wait Time";
        glRasterPos2i(20, 140);
        for (int i = 0; i < strHelp5.length(); ++i)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strHelp5[i]);
        }
    }

    //=======================================================

    string strEventQ = "Event Queue";
    glRasterPos2i(1070, 90);
    for (int i = 0; i < strEventQ.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strEventQ[i]);
    }

    vector<string> vecEvents = theStore.EventQ.to_str();
    for(int i = 0; i < vecEvents.size(); i++)
    {
        glRasterPos2i(1025, 200+(20*i));
        for (int j = 0; j < vecEvents[i].length(); ++j)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, vecEvents[i][j]);
        }
    }

    //=======================================================

    glRasterPos2i(450, 210);
    string strTitle = "Super Market";
    for (int i = 0; i < strTitle.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strTitle[i]);
    }

    //=======================================================

    glColor3f(0, 0, 0);
    for (int i = 0; i < theStore.Lines.size(); ++i)
    {
        //Print Express Lane and Open/Closed Boxes for Each Checkout Line
        for(int i = 0; i < numLines; i++)
        {
            buttonsExpress[i].draw();
            buttonsStatus[i].draw();
        }

        int newY = 45*i;
        glColor3f(0, 0, 0);

        //Print Express Lane Limit if Checkout Line is Express
        if(theStore.Lines[i]->getItemLimit() != std::numeric_limits<int>::max())
        {
            if(theStore.Lines[i]->getItemLimit() < 10)
            {
                glRasterPos2i(22, (245 + newY));
            }
            else
            {
                glRasterPos2i(18, (245 + newY));
            }

            string strLimit = intToString(theStore.Lines[i]->getItemLimit());
            for (int j = 0; j < strLimit.length(); ++j)
            {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, strLimit[j]);
            }
        }

        //Print Name of Each Checkout Line
        string strLine = "Checkout Line #" + intToString(theStore.Lines[i]->getID()) + ": ";
        glRasterPos2i(65, (250 + newY));
        for (int j = 0; j < strLine.length(); ++j)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strLine[j]);
        }

        //Print Customers in Each Checkout Line
        for (int k = 0; k < theStore.Lines[i]->customerLine.size(); ++k)
        {
            string strCust = "(" + intToString(theStore.Lines[i]->customerLine[k].getId()) + ")" + intToString(theStore.Lines[i]->customerLine[k].getNumItems());
            glRasterPos2i(265+(k*85), (250+newY));
            for (int l = 0; l < strCust.length(); ++l)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strCust[l]);
            }

            //Only Print 6 Customers to Avoid Printing Off Screen
            if(k > 6) break;
        }
    }

    //=======================================================

    glColor3f(0, 0, 0);

    string strStrats = "Line Joining Strategies";
    glRasterPos2i(675, 685);
    for (int i = 0; i < strStrats.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strStrats[i]);
    }

    buttonStrat1.draw();
    buttonStrat2.draw();
    buttonStrat3.draw();
    buttonStrat4.draw();

    //Set Color to White
    glColor3f(1, 1, 1);

    glRasterPos2i(630, 730);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('1'));

    glRasterPos2i(730, 730);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('2'));

    glRasterPos2i(830, 730);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('3'));

    glRasterPos2i(930, 730);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('4'));

    //=======================================================
    buttonStart.draw();
    buttonStop.draw();

    glColor3f(0, 0, 0);

    glRasterPos2i(410, 730);
    string strStart = "Start";
    for (int i = 0; i < strStart.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strStart[i]);
    }

    glRasterPos2i(515, 730);
    string strStop = "Stop";
    for (int i = 0; i < strStop.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strStop[i]);
    }

    //=======================================================

    //Set Color to Blue
    glColor3f(0, 0, 1);

    glRasterPos2i(15, 700);
    string strExLimit = "Express Lane Limit: " + intToString(ExpressLimit);
    for (int i = 0; i < strExLimit.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strExLimit[i]);
    }

    glColor3f(0, 0, 0);

    glRasterPos2i(75, 745);
    string strClickHelp = "<- Click For Help!";
    for (int i = 0; i < strClickHelp.length(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strClickHelp[i]);
    }

    buttonHelp.draw();

    glColor3f(0, 0, 0);
    glRasterPos2i(35, 745);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char('?'));

    //=======================================================

    if(Run)
    {
        E = theStore.EventQ.pop();
        theStore.setTime(E.get_time());
        theStore.handleEvent(E);
    }

    //=======================================================

    glFlush(); //Render
}

//================================================================================

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27)
    {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}
//================================================================================
void kbdS(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            ExpressLimit++;
            break;

        case GLUT_KEY_DOWN:
            if(ExpressLimit>0) ExpressLimit--;
            break;

        case GLUT_KEY_LEFT:
            break;

        case GLUT_KEY_RIGHT:
            break;
    }
    glutPostRedisplay();
}
//================================================================================
void cursor(int x, int y)
{
}
//================================================================================
// Button is GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON, State is GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON)
    {
        if (buttonStart.pointOverlap(x, y))
        {
            Run = true;
        }

        if (buttonStop.pointOverlap(x, y))
        {
            Run = false;
        }

        if (buttonStrat1.pointOverlap(x, y))
        {
            buttonStrat1.set_fill(0, 0, 0.2);
            buttonStrat2.set_fill(0, 0, 1);
            buttonStrat3.set_fill(0, 0, 1);
            buttonStrat4.set_fill(0, 0, 1);
            theStore.setStrategy(Store::RANDOM);
        }

        if (buttonStrat2.pointOverlap(x, y))
        {
            buttonStrat2.set_fill(0, 0, 0.2);
            buttonStrat1.set_fill(0, 0, 1);
            buttonStrat3.set_fill(0, 0, 1);
            buttonStrat4.set_fill(0, 0, 1);
            theStore.setStrategy(Store::NUM_CUSTOMERS);
        }

        if (buttonStrat3.pointOverlap(x, y))
        {
            buttonStrat3.set_fill(0, 0, 0.2);
            buttonStrat2.set_fill(0, 0, 1);
            buttonStrat1.set_fill(0, 0, 1);
            buttonStrat4.set_fill(0, 0, 1);
            theStore.setStrategy(Store::NUM_ITEMS);
        }

        if (buttonStrat4.pointOverlap(x, y))
        {
            buttonStrat4.set_fill(0, 0, 0.2);
            buttonStrat2.set_fill(0, 0, 1);
            buttonStrat3.set_fill(0, 0, 1);
            buttonStrat1.set_fill(0, 0, 1);
            theStore.setStrategy(Store::WAIT_TIME);
        }
    }

    if(button==GLUT_LEFT_BUTTON & state==GLUT_DOWN & buttonHelp.pointOverlap(x,y))
    {
        if(ShowHelp==true) ShowHelp=false;
        else ShowHelp=true;
    }

    if(button==GLUT_LEFT_BUTTON & state==GLUT_DOWN)
    {
        for(int i=0; i<numLines; i++)
        {
            if(buttonsExpress[i].pointOverlap(x,y) & i!=0)
            {
                if(theStore.Lines[i]->getItemLimit() == std::numeric_limits<int>::max())
                {
                    theStore.Lines[i]->setItemLimit(ExpressLimit);
                    buttonsExpress[i].set_fill((color){0.5,0,0.8});
                }
                else
                {
                    theStore.Lines[i]->setItemLimit(std::numeric_limits<int>::max());
                    buttonsExpress[i].set_fill((color){0,0,1});
                }
            }
            if(buttonsStatus[i].pointOverlap(x,y) & i!=0)
            {
                if(theStore.Lines[i]->getStatus())
                {
                    theStore.Lines[i]->togStatus();
                    buttonsStatus[i].set_fill((color){1,0,0});
                }
                else
                {
                    theStore.Lines[i]->togStatus();
                    buttonsStatus[i].set_fill((color){0,1,0});
                }
            }
        }
    }
    glutPostRedisplay();
}
//================================================================================
void timer(int dummy)
{
    glutTimerFunc(500, timer, 0);
    glutPostRedisplay();
}
//================================================================================
// Main Function: GLUT Runs as a Console Application Starting at Main()
int main(int argc, char** argv)
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize((int)Width, (int)Height);

    // Position the Window's Initial Top-Left Corner
    glutInitWindowPosition(100, 200);

    // Create the Window and Store the Handle to It
    wd = glutCreateWindow("Super Market Simulation");

    // Register Callback Handler for Window Re-Paint Event
    glutDisplayFunc(display);

    // Our Own OpenGL Initialization
    initGL();

    // Register Keyboard Press Event Processing Function
    glutKeyboardFunc(kbd);

    // Register Special Event: Function Keys, Arrows, etc.
    glutSpecialFunc(kbdS);

    // Handles Mouse Movement
    glutPassiveMotionFunc(cursor);

    //Handles Mouse Click
    glutMouseFunc(mouse);

    //Handles Timer
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
//================================================================================

string intToString(int i)
{
    char t[256];
    sprintf(t, "%d", i);
    string s = t;
    return s;
}

string dubToString(double i)
{
    char t[256];
    sprintf(t, "%.2f", i);
    string s = t;
    return s;
}

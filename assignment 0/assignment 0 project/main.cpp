#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "Color.h"
#include "Vector2f.h"
#include "modelparser/ObjParser.h"
using namespace std;

// Globals

double angle = 0;
double zoomFactor = 5;
std::pair<int, int> lastMousePos = std::make_pair(-1, -1);
double cameraPosX = 0;
double cameraPosY = 0;
double cameraRotX = 0;
double cameraRotY = 0;
bool wheelPressed = false;
bool leftPressed = false;


// This is the list of points (3D vectors)
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<pair<unsigned int, unsigned int>>> vecf;

// You will need more global variables to implement color and position changes
std::vector<Color> colors{{{1, 1, 1, 1}},{{1, 0, 0, 1}}, {{0, 1, 0, 1}}, {{0, 0, 1, 1}}, {{1, 1, 0, 1}}};
int counter = 0;

Color currentColor = colors[0];
Color colorDiff;
Color activeColor = colors[0];

float lightPos[] = {1.0, 1.0, 5.0, 1.0};

// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
inline void glVertex(const Vector3f &a) 
{ glVertex3fv(a); }

inline void glNormal(const Vector3f &a) 
{ glNormal3fv(a); }

void changeColorInTime(int value)
{
	activeColor.RGBA	= activeColor.RGBA + colorDiff.RGBA/1000;
    glutPostRedisplay();
}

// This function is called whenever a "Normal" key press is received.
void handleInput( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
        counter = (counter+1) % colors.size();
        currentColor = colors[counter];
        colorDiff.RGBA = currentColor.RGBA - activeColor.RGBA;
        for(int i = 0; i < 1000; ++i)
        {
        	glutTimerFunc(i, changeColorInTime, 0);
        }
        break;
    case 'r':
        angle += 30;
        break;
	default:
        cout << "Unhandled key press " << key << "." << endl;
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void changeLightPosition( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
        lightPos[1] += .5;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
        lightPos[1] -= .5;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
		lightPos[0] -= .5;
        break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
        lightPos[0] += .5;
		break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

void drawLoadedObject()
{
    GLuint index = glGenLists(1);

    glNewList(index, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	for(auto& vec : vecf)
    {
	    const unsigned int a = vec[0].first - 1;
	    const unsigned int c = vec[0].second - 1;
	    const unsigned int d = vec[1].first - 1;
	    const unsigned int f = vec[1].second - 1;
	    const unsigned int g = vec[2].first - 1;
	    const unsigned int i = vec[2].second - 1;
		glNormal3d(vecn[c][0], vecn[c][1], vecn[c][2]);
		glVertex3d(vecv[a][0], vecv[a][1], vecv[a][2]);
		glNormal3d(vecn[f][0], vecn[f][1], vecn[f][2]);
		glVertex3d(vecv[d][0], vecv[d][1], vecv[d][2]);
		glNormal3d(vecn[i][0], vecn[i][1], vecn[i][2]);
		glVertex3d(vecv[g][0], vecv[g][1], vecv[g][2]);
    }
	glEnd();
    glEndList();
    glCallList(index);
}


// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glPushMatrix();
    glLoadIdentity();              // Initialize to the identity
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    //glScaled(zoomFactor, zoomFactor, 1);
	glRotatef(angle,0.0,0.0,1.0);

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(cameraRotX, cameraRotY, zoomFactor,
              cameraPosX, cameraPosY, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object

	// Here are some colors you might use - feel free to add more
    GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.9, 0.5, 0.5, 1.0},
                                 {0.5, 0.9, 0.3, 1.0},
                                 {0.3, 0.8, 0.9, 1.0} };

	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, activeColor.asFloatArr());

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	GLfloat Lt0pos[] = {1.0, 1.0, 5.0, 1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// This GLUT method draws a teapot.  You should replace
	// it with code which draws the object you loaded.
	drawLoadedObject();
    //glutSolidTeapot(1.0);

    glPopMatrix();

    // Dump the image to the screen.
    glutSwapBuffers();

}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}

void loadInput()
{
	// load the OBJ file here
    ModelParser* parser = new ObjParser();
    parser->read_file("garg.obj", vecv, vecn, vecf);
	drawLoadedObject();

}

void handleMouseWheel(int wheel, int direction, int x, int y)
{
	if(direction > 0)
	{
		zoomFactor -= 0.05;
	}
    else
    {
	    zoomFactor += 0.05;
    }
    glutPostRedisplay();
}


void handleMouseInput(int button, int state, int x, int y)
{
    switch(button)
    {
		case GLUT_MIDDLE_BUTTON:
			if(state == GLUT_DOWN)
			{
                wheelPressed = true;
				lastMousePos = std::make_pair(x, y);
			}
    		else
			{
				wheelPressed = false;
				lastMousePos = std::make_pair(-1, -1);
			}
			break;
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
			{
                leftPressed = true;
				lastMousePos = std::make_pair(x, y);
			}
    		else
			{
				leftPressed = false;
				lastMousePos = std::make_pair(-1, -1);
			}
			break;
    }
}


void moveCamera(int x, int y)
{
	auto currentPos = std::make_pair(x, y);
	std::cout << currentPos.first - lastMousePos.first << " " << currentPos.second - lastMousePos.second << "\n";
	    
	if(currentPos.first - lastMousePos.first > 0)
	{
		cameraPosX -= .1;
	}
	else
	{
		cameraPosX += .1;
	}
	if(currentPos.second - lastMousePos.second > 0)
	{
		cameraPosY -= .1;
	}
	else
	{
		cameraPosY += .1;
	}
		
	lastMousePos = currentPos;
}

void rotateCamera(int x, int y)
{
	auto currentPos = std::make_pair(x, y);
	std::cout << currentPos.first - lastMousePos.first << " " << currentPos.second - lastMousePos.second << "\n";
	    
	if(currentPos.first - lastMousePos.first > 0)
	{
		cameraRotX -= .1;
	}
	else
	{
		cameraRotX += .1;
	}
	if(currentPos.second - lastMousePos.second > 0)
	{
		cameraRotY -= .1;
	}
	else
	{
		cameraRotY += .1;
	}
		
	lastMousePos = currentPos;
}

void handleMouseMove(int x, int y)
{
    if(wheelPressed)
    {
	    moveCamera(x, y);
    }
    if(leftPressed)
    {
	    rotateCamera(x, y);
    }
    
    glutPostRedisplay();

}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();

    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(handleInput); // Handles "normal" ascii symbols
    glutSpecialFunc(changeLightPosition);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    glutMouseFunc(handleMouseInput);

    glutMouseWheelFunc(handleMouseWheel);

    glutMotionFunc(handleMouseMove);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}

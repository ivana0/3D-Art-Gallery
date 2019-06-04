
/********************************************************************

Created by Ivana Ozakovic
Student number: 4790339
Username: io447
Filename: Source.cpp

Computer Graphics - Assignment 4: Art Gallery

********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <cmath>
#include <gl/glut.h>    //include glut library (automatically includes gl and glu libraries)
#include <windows.h>

#define MY_PI 		3.14159265359f     //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians

/************	Defined Variables	******************/
//RGB values for color struct 
struct Color
{
	double r, g, b;
};
//color array with set colors
Color colorArray[12] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 },{ 0.0, 1.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 0.862745, 0.862745, 0.862745 },{ 0.0, 0.0, 0.0 },{ 1.0, 1.0, 1.0 },{ 0.9, 0.9, 0.9 },{ 1.0, 1.0, 1.0 },{ 0.2, 0.2, 0.2 } };
// red - 0,				green - 1,				blue - 2,			yellow - 3,				cyan - 4,			magenta - 5,				gray - 6,						black - 7,		   white- 8		9 - light gray		10 - can change      11- dark gray

//White plastic
GLfloat plastic_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat plastic_diffuse[] = { 0.55f,0.55f,0.55f,1.0f };
GLfloat plastic_specular[] = { 0.70f,0.70f,0.70f,1.0f };
GLfloat shinePlastic = 32.0f;

//Brass
GLfloat brass_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
GLfloat brass_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
GLfloat brass_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
GLfloat shineBrass = 27.8974f;

// material properties
GLfloat gAmbientMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat gSpecularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLint gShininessMaterial = 50;
GLfloat gDiffuseMaterial[] = { 1.0f, 0.5f, 0.2f, 1.0f };

//red matte
GLfloat red_diffuse_mat[] = { 0.8, 0.2, 0.2, 1.0 }; // red matte 
GLfloat red_specular_mat[] = { 0.8, 0.2, 0.2, 1.0 }; // red shine
GLfloat shininess[] = { 50.0 };

//emission spheres properties
GLfloat redEmission[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat whiteEmission[] = { 0.8f, 0.8f, 0.8f,0.0f };
GLfloat blueEmission[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat gNone[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//light 1  - left blue globe light
GLfloat gAmbientLight[] = { 0.0, 0.0, 0.3, 1.0 };		//ambient light0 blue
GLfloat gDiffuseLight[] = { 0.0, 0.0, 0.5, 1.0 };		//diffuse light0 blue
//light 2  - right red globe light
GLfloat gAmbientLight2[] = { 0.3, 0.0, 0.0, 1.0 };		//ambient light1 red
GLfloat gDiffuseLight2[] = { 0.5, 0.0, 0.0, 1.0 };		//diffuse light1 red
//light 3 - spotlight 1 - front globe
GLfloat gAmbientLight3[] = { 0.2, 0.2, 0.2, 1.0 };		//ambient light2 
GLfloat gDiffuseLight3[] = { 0.3, 0.3, 0.3, 1.0 };		//diffuse light2 
GLfloat spotlightDirection[] = { -1.0, -1.0, 0.0 };		//set spotlight direction
//light 4 - back globe
GLfloat gAmbientLight4[] = { 0.3, 0.3, 0.3, 1.0 };		//ambient light2 
GLfloat gDiffuseLight4[] = { 0.5, 0.5, 0.5, 1.0 };		//diffuse light2 
GLfloat gSpecularLight4[] = { 0.2, 0.2, 0.2, 1.0 };		//diffuse light2 
//light 5 - middle globe
GLfloat gAmbientLight5[] = { 0.2, 0.2, 0.2, 1.0 };		//ambient light5 white
GLfloat gDiffuseLight5[] = { 0.3, 0.3, 0.3, 1.0 };		//diffuse light5 white
//light 6 - spotlight 2 - in front of gallery
GLfloat spotlightDirection2[] = { -1.0, -1.0, 0.0 };		//set spotlight direction

//light positions
GLfloat gLightPosition[] = { -3.6, 1.5-0.3, -4.0-0.5, 0.0 };	//light0 position
GLfloat gLightPosition2[] = { 3.6, 1.5-0.3, -4.0-0.5, 0.0 };	//light1 position
GLfloat gLightPosition3[] = { 0.0, 1.6, 0.0};			//spotlight 1 position
GLfloat gLightPosition4[] = { 0.0, 1.6, -8.0, 0.0};			//spotlight 2 position
GLfloat gLightPosition5[] = { 0.0, 1.6, -4.0, 0.0};			//spotlight 2 position
GLfloat gLightPosition6[] = { 0.0, 2.6, 4.0, 0.0 };			//spotlight 2 position

//gloal ambient light properties - 2 levels
GLfloat gGlobalAmbient1[] = { 0.8f, 0.8f, 0.8f, 1.0f };	//brighter ambient
GLfloat gGlobalAmbient2[] = { 0.2f, 0.2f, 0.2f, 1.0f };	//darker ambient

//camera variables
GLfloat gCameraPosition[] = { 0.0f, 0.3f, 14.0f };
GLfloat gCameraLookAt[] = { 0.0f, 0.3f, 0.0f };
GLfloat gCameraUp[] = { 0.0f, 1.0f, 0.0f };

GLfloat gMoveForward = 0.0;   //camera forward/backward movement variable
GLfloat gLeftRight = 0.0;   //camera forward/backward movement variable

GLfloat gCameraYaw = 0.0;     //camera yaw
GLfloat gCameraPitch = 0.0;   //camera pitch
GLfloat gCameraRoll = 0.0;   //camera roll

//window size
const int windowWidth = 800;
const int windowHeight = 600;

//fps calculation variables
int frameCount = 0, currentTime, previousTime = 0;
float fps;
std::string fpsStr;

//camera rotation 
bool pitch = false;
bool yaw = false;
bool roll = false;
//camera movement 
bool forwardBack = false;
bool leftRight = false;
bool upDown = false;

bool backCull = false;		//back face culling
bool frontCull = false;		//front face culling
bool depthTest = false;		//depth test on/off
bool colorTracking = true;	//color tracking on/off
bool alphaBlend = false;	//alpha blending on/off

//lights on/off booleans
bool leftLight = true;
bool rightLight = true;
bool spotLight1Front = false;
bool spotLight2Ouside = true;
bool middleLight = true;
bool lightBack = true;

bool nightMode = true;	//initally night mode
bool dayMode = false;	// day mode
bool blinkingLights = true;	//blinking lights on/off on 'L'

//wire modes
bool whiteBgBlackWire = false;	
bool blackBgWhiteWire = false;	
bool blueBgYellowWire = false;	

GLfloat gMovementSensitivity = 1;      //movement sensitivity
GLfloat gRotationSensitivity = 2;      //rotational sensitivity

//menu display - h
bool displayMenu = true;

//variables to store texture information
struct TextureInfo {
	unsigned char* tex_image;   //image data
	GLuint textureID;           //texture id
	GLint imageWidth;           //image width info
	GLint imageHeight;          //image height info	
};
//global array of textures generated
TextureInfo textureInfo[10];
GLuint *textures = new GLuint[10];


GLfloat teapotAngle = 0.0;
GLfloat torusAngle = 0.0;
GLfloat sphereMove = 0.0;
GLint frameRate = 60;

/****************************	FUNCTIONS	 ************************/

//reset pressed keys
void resetKeys(bool fb, bool lr, bool ud, bool p, bool y, bool r);			//reset pressed keys							
void displayText(float posX, float posY, std::string text, Color color);	//function for drawing text																		
unsigned char* LoadBMPFile(char *filename, int id);	//function for loading bmp files for textures
void resetCamera();								//reset camera to initial state
void setupTexture(char * filename, int id);		//load texture
void setupLights();								//setup lights
void myTimer(int v);							//timer function
void myIdleFunc();								//idle function - calculates fps


//Functions glEnalble2D and glDisable2D referenced from:
//http://www.gamedev.net/topic/104791-last-post-about-2d-in-opengl-so-please-stop/
//functions were further modified to suit what is needed
void glEnable2D();
void glDisable2D();

//functions to enable/disable alpha blending for drawing translucent objects
void enableBlending();
void disableBlending();

void setInitMaterial();	//set inital material
void disableAllLightning();	//disable all lights

//drawing
void drawBox(float x, float x2, float y, float y2, float z, float z2, Color color, float alpha);	//draw box used for drawing scene objects
void drawRoom();	//draw walls, ceiling, floor
void drawLights();	//draw emission spheres and spotlight
void drawObjects();	//draw objects on the table
void drawMenu();			//draw menu 
void drawTeapot();
void drawTorus();
void drawPyramid();
void drawPainting(int id, float x, float x2, float y, float y2, float z, float z2, Color color, float alpha);



/**************		FUNCTION DEFINITIONS	*******************/
//draw teapot
void drawTeapot()
{
	//red brass teapot
	glMaterialfv(GL_FRONT, GL_AMBIENT, brass_ambient);        //set material ambient component
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brass_diffuse);        //set material diffuse component
	glMaterialfv(GL_FRONT, GL_SPECULAR, brass_specular);      //set material specular component
	glMateriali(GL_FRONT, GL_SHININESS, shineBrass);			//set material shininess	
	
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glColor4f(0.6, 0.1, 0.1, 1.0);

	glPushMatrix();
		glTranslatef(0.0, 0.7, 0.0);
		glRotatef(teapotAngle, 0.0, 1.0, 0.0);
		if (blackBgWhiteWire || whiteBgBlackWire || blueBgYellowWire)
			glutWireTeapot(0.7);
		else
			glutSolidTeapot(0.7);
	glPopMatrix();
}
//draw torus
void drawTorus()
{
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
	{
		//draw glass transparent torus
		glBindTexture(GL_TEXTURE_2D, textures[0]);	//bind glass texture
		enableBlending();							//enable alpha blending
		glColor4f(1.0, 1.0, 1.0, 0.6);
	}

	glPushMatrix();
		glTranslatef(0.0, 0.1, 0.0);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glRotatef(torusAngle, 0.0, 0.0, 1.0);
		if (blackBgWhiteWire || whiteBgBlackWire || blueBgYellowWire)
			glutWireTorus(0.13, 0.6, 16, 32);
		else
			glutSolidTorus(0.13, 0.6, 16, 32);
	glPopMatrix();
	disableBlending();							//disable alpha blending
	glBindTexture(GL_TEXTURE_2D, 0);			//reset texture

}

//set up states for the scene
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	//clears background colour to black
	//hidden surface removal	-	enabled as default
	glEnable(GL_DEPTH_TEST);
	depthTest = true;
	//set blending function and enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//set material properties
	setInitMaterial();
	
	//use color tracking for material properties
	glEnable(GL_COLOR_MATERIAL);        //enable colour tracking
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	
	//adjust light model - set global ambient lightning
	glEnable(GL_LIGHTING);				//enable lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gGlobalAmbient2);
	setupLights();

	glShadeModel(GL_SMOOTH);			//use smooth shading as default

	glEnable(GL_CULL_FACE);				//do not calculate inside of polygons	-	enabled as default
	glCullFace(GL_BACK);				//set culling default to back
	backCull = true;
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//enable texturing
	glEnable(GL_TEXTURE_2D);

	// generate textures
	glGenTextures(10, textures);
	//Reference: http://img08.bibliocad.com/pub/thumb_200x200/00010000/3000/13101.jpg
	setupTexture("glass.bmp", 0);	
	//Reference: http://img08.bibliocad.com/pub/thumb_200x200/00010000/3000/13101.jpg
	setupTexture("whiteMarble2.bmp", 1);
	//Reference: http://subtlepatterns2015.subtlepatterns.netdna-cdn.com/patterns/white_wall.png
	setupTexture("white_wall.bmp", 2);
	//Reference: https://www.artsy.net/artwork/piet-mondrian-composition-with-large-red-plane-yellow-black-grey-and-blue
	setupTexture("piet-mondrain-composition.bmp", 3);
	//Reference: http://www.piet-mondrian.org/images/paintings/composition-with-red-yellow-and-blue.jpg
	setupTexture("composition-with-red-yellow-and-blue.bmp", 4);
	//Reference: https://clairelecoeur.files.wordpress.com/2013/01/londres-fc3a9v-11-154.jpg
	setupTexture("summertime-number-9.bmp", 5);
	//Reference: http://www.jackson-pollock.org/images/paintings/number-32.jpg
	setupTexture("number-32.bmp", 6);
	//Reference: https://en.wikipedia.org/wiki/Abstract_art#/media/File:Fire_in_the_Evening.JPG
	setupTexture("Fire_in_the_Evening.bmp", 7);
	//Reference: https://upload.wikimedia.org/wikipedia/commons/4/4f/Theo_van_Doesburg_Composition_VII_(the_three_graces).jpg
	setupTexture("Theo_van_Doesburg_Composition_VII_(the_three_graces).bmp", 8);
	

}

//sets inital material, made a function as set to this material multiple times
void setInitMaterial() 
{
	//set material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseMaterial);        //set material diffuse component
	glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial);      //set material specular component
	glMateriali(GL_FRONT, GL_SHININESS, gShininessMaterial);     //set material shininess	
}

void setupTexture(char * filename, int id)
{
	// load BMP file into image
	textureInfo[id].tex_image = LoadBMPFile(filename, id);

	glBindTexture(GL_TEXTURE_2D, textures[id]);       // bind texture

	// generate texture mipmaps
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureInfo[id].imageWidth, textureInfo[id].imageHeight, GL_RGB, GL_UNSIGNED_BYTE, textureInfo[id].tex_image);

}

void setupLights()
{
	//setup light 0 - blue left light
	glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight);		//set light0's ambient component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuseLight);		//set light0's diffuse component
	glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);		//set light0's position	
	//set attenuation
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	//setup light 1 - red right light
	glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight2);		//set light1's ambient component
	glLightfv(GL_LIGHT1, GL_DIFFUSE, gDiffuseLight2);		//set light1's diffuse component
	glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition2);		//set light1's position
	//set attenuation
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	//setup light/spotlight 1  - front globe inside gallery
	glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight3);		//set light2's ambient component
	glLightfv(GL_LIGHT2, GL_DIFFUSE, gDiffuseLight3);		//set light2's diffuse component
	glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition3);
	 
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);							//set light2's cut off
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);							//set light2's exponent
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection);		//set light2's direction
	//set attenuation
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);

	//setup light 4  - back globe light
	glLightfv(GL_LIGHT3, GL_AMBIENT, gAmbientLight4);		//set light3's ambient component
	glLightfv(GL_LIGHT3, GL_DIFFUSE, gDiffuseLight4);		//set light3's diffuse component
	glLightfv(GL_LIGHT3, GL_SPECULAR, gSpecularLight4);		//set light3's position
	glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition4);
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.2);

	//setup light 5 - middle globe
	glLightfv(GL_LIGHT4, GL_AMBIENT, gAmbientLight5);		//set light4's ambient component
	glLightfv(GL_LIGHT4, GL_DIFFUSE, gDiffuseLight5);		//set light4's diffuse component
	glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition5);		//set light4's position
	//set attenuation
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.2);
	
	//setup light 6/spotlight 2 - in front of gallery
	glLightfv(GL_LIGHT5, GL_AMBIENT, gAmbientLight3);		//set light5's ambient component
	glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseLight3);		//set light5's diffuse component
	glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition6);		//set light5's position
	//set attenuation
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 1.5);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);							//set light5's cut off
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);							//set light5's exponent
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotlightDirection2);		//set light5's direction
	

	//enable lighting
	glEnable(GL_LIGHT0);      //enable light0 blue
	glEnable(GL_LIGHT1);      //enable light1 red
	//glEnable(GL_LIGHT2);      //enable light 3/enable spotlight 1 - front globe inside gallery - disable as default
	glEnable(GL_LIGHT3);      //enable light 4
	glEnable(GL_LIGHT4);      //enable light 5
	glEnable(GL_LIGHT5);      //enable light 6/spotlight 2 - in front of gallery

}

//called whenever the window is resized (also called once when window is first drawn)
void resizeWindow(int width, int height)   //window width and height
{
	if (height == 0)           //just in case, to prevent divide by zero when calculating aspect ratio
		height = 1;

	glViewport(0, 0, width, height);		//set the viewport
	glMatrixMode(GL_PROJECTION);			//set matrix mode to projection matrix
	glLoadIdentity();						//set projection matrix to identity matrix (analogous to clearing the projection matrix)
	gluPerspective(60.0f, 					//set up perspective projection with 45 degrees field of view
		(GLfloat)width / (GLfloat)height,	//set aspect ratio
		1.0f, 								//set near clipping plane to 1.0
		1000.0f);							//set far clipping plane to 1000.0

	glMatrixMode(GL_MODELVIEW);				//set matrix mode to modelview matrix

	glLoadIdentity();						//set projection matrix to identity matrix (analogous to clearing the modelview matrix)

	gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set camera position
		gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],				//set position where eye/camera is looking at
		gCameraUp[0], gCameraUp[1], gCameraUp[2]);							//set 'up' vector


}

//display handler function - draw scene
void drawScene()
{
	glEnable(GL_NORMALIZE);									//normal vectors are normalized to unit length after transformation and before lighting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear the colour/depth buffer 

	//draw lights
	drawLights();
	//draw paintings and objects
	drawObjects();
	//draw room - walls, ceiling, floor
	drawRoom();
	
	glColor4f(0.0, 0.0, 0.0, 0.0);
	//draw user menu if h key pressed
	if (displayMenu)
		drawMenu();
	glColor4f(0.0, 0.0, 0.0, 0.0);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();  //refresh display

}

//function updates the camera
void updateCamera()
{
	if (gCameraYaw > 360.0)    //keep yaw between 0 to 360 degrees
		gCameraYaw -= 360.0;
	else if (gCameraYaw < 0.0)
		gCameraYaw += 360.0;

	if (gCameraPitch > 360.0)    //keep pitch between 0 to 360 degrees
		gCameraPitch -= 360.0;
	else if (gCameraPitch < 0.0)
		gCameraPitch += 360.0;

	gCameraPosition[0] += sin(DEG2RAD(gCameraYaw))*gMoveForward;    //calculate movement along x axis
	gCameraPosition[2] += -cos(DEG2RAD(gCameraYaw))*gMoveForward;   //calculate movement along z axis
	gMoveForward = 0;     //reset forward/backward movement

	 //rotate camera lookat direction
	gCameraLookAt[0] = gCameraPosition[0] + sin(DEG2RAD(gCameraYaw));
	gCameraLookAt[2] = gCameraPosition[2] - cos(DEG2RAD(gCameraYaw));

	if (pitch) {
		gCameraLookAt[1] = gCameraPosition[1] + tan(DEG2RAD(gCameraPitch));
	}

	glLoadIdentity();     //load modelview matrix with identity matrix, i.e. clear all modelview transformations
	gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set camera position
		gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set position where eye/camera is looking at
		gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector



	glutPostRedisplay();  //refresh display

}

//reset camera once HOME key pressed using this function
void resetCamera()
{
	gCameraPosition[0] = 0.0;
	gCameraPosition[1] = 0.3;
	gCameraPosition[2] = 14.0;

	gCameraLookAt[0] = 0.0;
	gCameraLookAt[1] = 0.3;
	gCameraLookAt[2] = 0.0;

	gCameraUp[0] = 0.0;
	gCameraUp[1] = 1.0;
	gCameraUp[2] = 0.0;

	gCameraYaw = 0.0;     //camera yaw
	gCameraPitch = 0.0;   //camera pitch
	gCameraRoll = 0.0;   //camera roll
}
/*Function displays text, reference:*/
/*http://stackoverflow.com/questions/2183270/what-is-the-easiest-way-to-print-text-to-screen-in-opengl */

void displayText(float posX, float posY, std::string text, Color color)
{
	glColor3f(color.r, color.g, color.b);	//set color to black
	glRasterPos2f(posX, posY);	//set position

	int len;
	len = text.size();	//get the size of string

	for (int i = 0; i <= len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);		//print each character and set font
	}

}

/**************		KEY FUNCTIONS	*******************/
//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
		//if ESC pressed, quit program
	case 27: exit(1);     //quit
		break;
		//show/hide user menu
	case 'H':
	case 'h':  if (displayMenu) { displayMenu = false; }
			   else { drawMenu();  displayMenu = true; }
			   break;
	case 'a':
	case 'A': gCameraYaw -= gRotationSensitivity;               //increment camera yaw
		resetKeys(false, false, false, false, true, false);
		break;
	case 'd':
	case 'D': gCameraYaw += gRotationSensitivity;              //decrement camera yaw
		resetKeys(false, false, false, false, true, false);
		break;
	case 'w':
	case 'W': gCameraPitch += gRotationSensitivity;               //increment camera pitch
		resetKeys(false, false, false, true, false, false);
		break;
	case 's':
	case 'S': gCameraPitch -= gRotationSensitivity;              //decrement camera pitch
		resetKeys(false, false, false, true, false, false);
		break;
	case 'q':
	case 'Q': gCameraRoll -= gRotationSensitivity;               //increment camera roll
		resetKeys(false, false, false, false, false, true);
		break;
	case 'e':
	case 'E': gCameraRoll += gRotationSensitivity;              //decrement camera roll
		resetKeys(false, false, false, false, false, true);
		break;
		//wireframe modes
	case '1':  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //white wireframe mode
		if (!blackBgWhiteWire)
		{
			blackBgWhiteWire = true;
			blueBgYellowWire = false;
			whiteBgBlackWire = false;
			glClearColor(0.0, 0.0, 0.0, 0.0);	//clears background colour to black
			
		}
		else if (blackBgWhiteWire)
		{
			blackBgWhiteWire = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
			if (nightMode)
				glClearColor(0.0, 0.0, 0.0, 1.0);	//clears background colour to black
			else
				glClearColor(colorArray[10].r, colorArray[10].g, colorArray[10].b, 1.0);	//clears background colour to blue

		}
		break;
	case '2':  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //black wireframe mode
		if (!whiteBgBlackWire)
		{
			whiteBgBlackWire = true;
			blueBgYellowWire = false;
			blackBgWhiteWire = false;
			glClearColor(1.0, 1.0, 1.0, 1.0);	//clears background colour to black

		}
		else if (whiteBgBlackWire)
		{
			whiteBgBlackWire = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
			if (nightMode)
				glClearColor(0.0, 0.0, 0.0, 1.0);	//clears background colour to black
			else
				glClearColor(colorArray[10].r, colorArray[10].g, colorArray[10].b, 1.0);	//clears background colour to blue

		}
		break;
	case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //yellow wireframe mode
		if (!blueBgYellowWire)
		{
			blueBgYellowWire = true;
			whiteBgBlackWire = false;
			blackBgWhiteWire = false;
			glClearColor(0.0, 0.0, 1.0, 1.0);	//clears background colour to blue

		}
		else if (blueBgYellowWire)
		{
			blueBgYellowWire = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
			if (nightMode)
				glClearColor(0.0, 0.0, 0.0, 1.0);	//clears background colour to black
			else
				glClearColor(colorArray[10].r, colorArray[10].g, colorArray[10].b, 1.0);	//clears background colour to blue
		}
		break;
	case '4':  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
			
		break;
	case '5':  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
		break;
	case '6':  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
				/*disableAllLightning();
				blinkingLights = false;
				glDisable(GL_LIGHTING);*/
		break;
	case '7': // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
				//init();
				//blinkingLights = true;
		break;
	case 'L':
	case 'l':  
		if (blinkingLights) //if light is on
		{
			//disable red and blue lights
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			blinkingLights = false;
		}
		else
		{
			blinkingLights = true;
		}
		break;
	//day mode
	case '+': glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gGlobalAmbient1);
				glClearColor(colorArray[10].r, colorArray[10].g, colorArray[10].b, 1.0);	//clears background colour to blue
				nightMode = false;
				dayMode = true;
				disableAllLightning();
				blinkingLights = false;		//disable blinking lights for day mode
				//enable lightings for day mode
				glEnable(GL_LIGHT0);      //enable light0 blue
				glEnable(GL_LIGHT1);      //enable light1 red
		break;
	//night mode
	case '-': 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gGlobalAmbient2);
		glClearColor(0.0, 0.0, 0.0, 0.0);	//clears background colour to black
		nightMode = true;
		dayMode = false;
		blinkingLights = true;
		disableAllLightning();
		//enable lightings for night mode
		glEnable(GL_LIGHT0);      //enable light0 blue
		glEnable(GL_LIGHT1);      //enable light1 red
		glEnable(GL_LIGHT3);      //enable light 4
		glEnable(GL_LIGHT4);      //enable light 5
		glEnable(GL_LIGHT5);      //enable light 6/spotlight 2 - in front of gallery
		break;
	default:
		break;

	};

	updateCamera();       //call function to update camera and to refresh the scene

}

void disableAllLightning() {

	//disable lighting
	glDisable(GL_LIGHT0);      // light0 blue
	glDisable(GL_LIGHT1);      // light1 red
	glDisable(GL_LIGHT2);      // light 3/enable spotlight 1 - front globe inside gallery - disable as default
	glDisable(GL_LIGHT3);      // light 4
	glDisable(GL_LIGHT4);      // light 5
	glDisable(GL_LIGHT5);      // light 6/spotlight 2 - in front of gallery

}

//called when non-ASCII key pressed
void mySpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		//if home pressed
	case GLUT_KEY_HOME: resetCamera();
		resetKeys(false, false, false, false, false, false);
		break;
		//if page up pressed
	case GLUT_KEY_PAGE_UP: gCameraPosition[1] += gMovementSensitivity;       //increment camera height
		gCameraLookAt[1] += gMovementSensitivity;
		resetKeys(false, false, true, false, false, false);
		break;
		//if page down pressed
	case GLUT_KEY_PAGE_DOWN:  gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
		gCameraLookAt[1] -= gMovementSensitivity;
		resetKeys(false, false, true, false, false, false);
		break;
		//if arrow up pressed
	case GLUT_KEY_UP:	gMoveForward += gMovementSensitivity;             //increment forward movement
		resetKeys(true, false, false, false, false, false);
		break;
		//if arrow down pressed
	case GLUT_KEY_DOWN: gMoveForward -= gMovementSensitivity;             //increment backward movement
		resetKeys(true, false, false, false, false, false);
		break;
		//if left pressed
	case GLUT_KEY_LEFT: gLeftRight -= gMovementSensitivity;
		if ((gCameraYaw > 225 && gCameraYaw < 315))
		{
			gCameraPosition[2] += gMovementSensitivity;       //decrement camera height
			gCameraLookAt[2] += gMovementSensitivity;
		}
		else if ((gCameraYaw >= 45 && gCameraYaw < 135))
		{
			gCameraPosition[2] -= gMovementSensitivity;       //decrement camera height
			gCameraLookAt[2] -= gMovementSensitivity;
		}
		else if ((gCameraYaw >= 135 && gCameraYaw <= 225)) {
			gCameraPosition[0] += gMovementSensitivity;       //increment camera height
			gCameraLookAt[0] += gMovementSensitivity;

		}
		else {
			gCameraPosition[0] -= gMovementSensitivity;       //decrement camera height
			gCameraLookAt[0] -= gMovementSensitivity;
		}
		resetKeys(false, true, false, false, false, false);
		break;
		//if right pressed
	case GLUT_KEY_RIGHT: gLeftRight += gMovementSensitivity;
		if ((gCameraYaw > 225 && gCameraYaw < 315))
		{
			gCameraPosition[2] -= gMovementSensitivity;       //decrement camera height
			gCameraLookAt[2] -= gMovementSensitivity;
		}
		else if ((gCameraYaw >= 45 && gCameraYaw < 135))
		{
			gCameraPosition[2] += gMovementSensitivity;       //decrement camera height
			gCameraLookAt[2] += gMovementSensitivity;
		}
		else if ((gCameraYaw >= 135 && gCameraYaw <= 225)) {
			gCameraPosition[0] -= gMovementSensitivity;       //increment camera height
			gCameraLookAt[0] -= gMovementSensitivity;

		}
		else {
			gCameraPosition[0] += gMovementSensitivity;       //increment camera height
			gCameraLookAt[0] += gMovementSensitivity;

		}
		resetKeys(false, true, false, false, false, false);
		break;
		/**********		LIGHTS:	F1,F2,F3,F4,F5,F6 *************/
	case GLUT_KEY_F1:
		if (leftLight) //if light is on
		{
			glDisable(GL_LIGHT0);    //disable lighting
			leftLight = false;
		}
		else
		{
			glEnable(GL_LIGHT0);    //enable lighting
			leftLight = true;
		}
		break;
	case GLUT_KEY_F2:
		if (rightLight) //if light is on
		{
			glDisable(GL_LIGHT1);    //disable lighting
			rightLight = false;
		}
		else
		{
			glEnable(GL_LIGHT1);    //enable lighting
			rightLight = true;
		}
		break;
	case GLUT_KEY_F3:
		if (middleLight) //if light is on
		{
			glDisable(GL_LIGHT4);    //disable lighting
			middleLight = false;
		}
		else
		{
			glEnable(GL_LIGHT4);    //enable lighting
			middleLight = true;
		}
		break;
	case GLUT_KEY_F4:
		if (lightBack) //if light is on
		{
			glDisable(GL_LIGHT3);    //disable lighting
			lightBack = false;
		}
		else
		{
			glEnable(GL_LIGHT3);    //enable lighting
			lightBack = true;
		}
		break;
	case GLUT_KEY_F5:
		if (spotLight1Front) //if light is on
		{
			glDisable(GL_LIGHT2);    //disable lighting
			spotLight1Front = false;
		}
		else
		{
			glEnable(GL_LIGHT2);    //enable lighting
			spotLight1Front = true;
		}
		break;
	case GLUT_KEY_F6:
		if (spotLight2Ouside) //if light is on
		{
			glDisable(GL_LIGHT5);    //disable lighting
			spotLight2Ouside = false;
		}
		else
		{
			glEnable(GL_LIGHT5);    //enable lighting
			spotLight2Ouside = true;
		}
		break;
	default:
		break;
	};

	updateCamera();       //call function to update camera and to refresh the scene


}

//reset pressed keys
void resetKeys(bool fb, bool lr, bool ud, bool p, bool y, bool r) {

	forwardBack = fb;
	leftRight = lr;
	pitch = p;
	yaw = y;
	roll = r;

}

std::string convertFloatToStr(float floatNum);		//convert float fps to string
													//function converts float to string
std::string convertFloatToStr(float floatNum)
{
	std::string converted;
	std::stringstream ss;

	ss << floatNum;

	converted = ss.str();

	return converted;
}

bool isRedOn = true;	//check if red light on
int count = 0;			//conter for blinking lights
void myTimer(int v)
{
	//teapot spinning control
	teapotAngle += 0.5;
	if (teapotAngle > 360)
		teapotAngle -= 360;

	//torus spinning control
	torusAngle += 0.1;
	if (torusAngle > 360)
		torusAngle -= 360;

	//blinking lights control
	if (blinkingLights)
	{
		count++;
		if (isRedOn && count > 50) {
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
			isRedOn = false;
			count = 0;

		}
		else if (!isRedOn && count > 50) {
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			isRedOn = true;
			count = 0;
		}
	}

	glutPostRedisplay();  //refresh display
	glutTimerFunc(1000 / frameRate, myTimer, 0);
}

//Reference function for calculating frames per second:
//https://mycodelog.com/2010/04/16/fps/
void myIdleFunc()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}

	fpsStr = convertFloatToStr(fps);

	glutPostRedisplay();  //refresh display
}



/*******	DRAWING FUNCTIONS	********/
//draw box - used to draw walls
void drawBox(float x, float x2, float y, float y2, float z, float z2, Color color, float alpha) {

	//if alpha blending enabled
	if(alphaBlend)
		glColor4f(color.r, color.g, color.b, alpha);		//set alpha color
	else
		glColor3f(color.r, color.g, color.b);		//set color

	glPushMatrix();
	glBegin(GL_QUADS);
	
	//bottom face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(-0.5 - x, -0.5 + y2, 0.5 + z2);
	glTexCoord2f((0.5 + z2) - (-0.5 - z), 0.0f);						glVertex3f(-0.5 - x, -0.5 + y2, -0.5 - z);
	glTexCoord2f((0.5 + z2) - (-0.5 - z), (-0.5 - x) - (0.5 + x2));		glVertex3f(0.5 + x2, -0.5 + y2, -0.5 - z);
	glTexCoord2f(0.0f, (-0.5 - x) - (0.5 + x2));						glVertex3f(0.5 + x2, -0.5 + y2, 0.5 + z2);

	//back face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(0.5 + x2, -0.5 + y2, -0.5 - z);
	glTexCoord2f((0.5 + x2) - (-0.5 - x), 0.0f);						glVertex3f(-0.5 - x, -0.5 + y2, -0.5 - z);
	glTexCoord2f((0.5 + x2) - (-0.5 - x), (-0.5 + y2) - (0.5 - y));		glVertex3f(-0.5 - x, 0.5 - y, -0.5 - z);
	glTexCoord2f(0.0f, (-0.5 + y2) - (0.5 - y));						glVertex3f(0.5 + x2, 0.5 - y, -0.5 - z);

	//right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(0.5 + x2, 0.5 - y, 0.5 + z2);
	glTexCoord2f((0.5 - y)-(-0.5 + y2), 0.0f);							glVertex3f(0.5 + x2, -0.5 + y2, 0.5 + z2);
	glTexCoord2f((0.5 - y) - (-0.5 + y2), (0.5 + z2)-(-0.5 - z));		glVertex3f(0.5 + x2, -0.5 + y2, -0.5 - z);
	glTexCoord2f(0.0f, (0.5 + z2) - (-0.5 - z));						glVertex3f(0.5 + x2, 0.5 - y, -0.5 - z);

	//left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(-0.5 - x, 0.5 - y, 0.5 + z2);
	glTexCoord2f((0.5 + z2) - (-0.5 - z), 0.0f);						glVertex3f(-0.5 - x, 0.5 - y, -0.5 - z);
	glTexCoord2f((0.5 + z2) - (-0.5 - z), (0.5 - y) - (-0.5 + y2) );	glVertex3f(-0.5 - x, -0.5 + y2, -0.5 - z);
	glTexCoord2f(0.0f, (0.5 - y) - (-0.5 + y2));						glVertex3f(-0.5 - x, -0.5 + y2, 0.5 + z2);

	//top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(0.5 + x2, 0.5 - y, 0.5 + z2);
	glTexCoord2f((0.5 + z2)-(-0.5 - z), 0.0);							glVertex3f(0.5 + x2, 0.5 - y, -0.5 - z);
	glTexCoord2f((0.5 + z2)-(-0.5 - z), (0.5 + x2) - (-0.5 - x));		glVertex3f(-0.5 - x, 0.5 - y, -0.5 - z);
	glTexCoord2f(0.0f, (0.5 + x2) - (-0.5 - x));						glVertex3f(-0.5 - x, 0.5 - y, 0.5 + z2);

	//front face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);											glVertex3f(0.5 + x2, 0.5 - y, 0.5 + z2);
	glTexCoord2f((0.5 + x2) - (-0.5 - x), 0.0f);						glVertex3f(-0.5 - x, 0.5 - y, 0.5 + z2);
	glTexCoord2f((0.5 + x2) - (-0.5 - x), (0.5 - y) - (-0.5 + y2));		glVertex3f(-0.5 - x, -0.5 + y2, 0.5 + z2);
	glTexCoord2f(0.0f, (0.5 - y) - (-0.5 + y2));						glVertex3f(0.5 + x2, -0.5 + y2, 0.5 + z2);
	
	glEnd();
	glPopMatrix();


}
//draw room - walls, floor, ceiling using drawBox function
void drawRoom() {

	Color color, color2, color3;
	//wireframe modes checking
	if (blackBgWhiteWire)
	{
		color.r = colorArray[8].r; color.g = colorArray[8].g; color.b = colorArray[8].b;
		color2.r = colorArray[8].r; color2.g = colorArray[8].g; color2.b = colorArray[8].b;
		color3.r = colorArray[8].r; color3.g = colorArray[8].g; color3.b = colorArray[8].b;
	}
	else if (whiteBgBlackWire)
	{
		color.r = colorArray[7].r; color.g = colorArray[7].g; color.b = colorArray[7].b;
		color2.r = colorArray[7].r; color2.g = colorArray[7].g; color2.b = colorArray[7].b;
		color3.r = colorArray[7].r; color3.g = colorArray[7].g; color3.b = colorArray[7].b;
	}
	else if (blueBgYellowWire)
	{
		color.r = colorArray[3].r; color.g = colorArray[3].g; color.b = colorArray[3].b;
		color2.r = colorArray[3].r; color2.g = colorArray[3].g; color2.b = colorArray[3].b;
		color3.r = colorArray[3].r; color3.g = colorArray[3].g; color3.b = colorArray[3].b;
	}
	else
	{
		//set color[10] to medium Turquoise 
		colorArray[10].r = 0.439216; colorArray[10].g = 0.858824; colorArray[10].b = 0.858824;

		color.r = colorArray[10].r; color.g = colorArray[10].g; color.b = colorArray[10].b;
		color2.r = colorArray[9].r; color2.g = colorArray[9].g; color2.b = colorArray[9].b;
		color3.r = colorArray[11].r; color3.g = colorArray[11].g; color3.b = colorArray[11].b;
	}

	/******		DRAW ROOM	***********/
	if(!whiteBgBlackWire && !blackBgWhiteWire && !blueBgYellowWire)
		glBindTexture(GL_TEXTURE_2D, textures[1]);	// bind marble tile texture
	//==**Floor**==
	drawBox(3.5, 3.5, 0.9, -0.15, 12.5, 4.5, color2, 1.0);
	//plane below floor
	drawBox(5.0, 5.0, 1.15, -0.45, 14.5, 6.0, color3, 1.0);
	//||**Walls**||
	if (!whiteBgBlackWire && !blackBgWhiteWire && !blueBgYellowWire)
		glBindTexture(GL_TEXTURE_2D, textures[2]);	//bind wall texture
	//wall left
	drawBox(3.5, -4.15, -2.1, 0.1, 12.25, 2.0, color, 1.0);
	//wall right
	drawBox(-4.15, 3.5, -2.1, 0.1, 12.25, 2.0, color, 1.0);
	//back wall
	drawBox(3.5, 3.5, -2.1, 0.1, 12.5, -13.25, color, 1.0);

	//==**Ceiling**==
	drawBox(3.5, 3.5, -3.11, 3.11, 12.5, 4.5, color3, 1.0);
	
	//front wall --> make it glass
	enableBlending();
	drawBox(3.5, 3.5, -2.1, 0.1, -3.0, 2.2, color, 0.5);
	disableBlending();


}
//enable and disable alpha blending helper functions
void enableBlending() {
	glEnable(GL_BLEND);
	depthTest = false;
	alphaBlend = true;
}
void disableBlending() {
	glDisable(GL_BLEND);
	depthTest = true;
	alphaBlend = false;
}
//draw lights 
void drawLights() {

	/******		DRAW LIGHTS	***********/
	//draw the light0
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);  //set material emission component
		
		glTranslatef(gLightPosition[0], gLightPosition[1], gLightPosition[2]);
		glutSolidSphere(0.4, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	//draw 2 red spheres next to blue light - not lights
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);  //set material emission component

		glTranslatef(gLightPosition[0], gLightPosition[1], gLightPosition[2] + 0.7 + sphereMove);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);  //set material emission component
		
		glTranslatef(gLightPosition[0], gLightPosition[1], gLightPosition[2] - 0.7 - sphereMove);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	//draw the light1
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);  //set material emission component

		glTranslatef(gLightPosition2[0], gLightPosition2[1], gLightPosition2[2]);
		glutSolidSphere(0.4, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	//draw 2 blue spheres next to red light - not lights
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);  //set material emission component

		
		glTranslatef(gLightPosition2[0], gLightPosition2[1], gLightPosition2[2] + 0.7);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);  //set material emission component

		glTranslatef(gLightPosition2[0], gLightPosition2[1], gLightPosition2[2] - 0.7);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();

	//draw the light3 - Spotlight
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);  //set material emission component
		
		glTranslatef(gLightPosition3[0], gLightPosition3[1], gLightPosition3[2]);
		glutSolidSphere(0.15, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();
	//draw light rope
	glColor4f(0.0, 0.0, 0.0, 1.0);		//set color
	glLineWidth(2.5);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3f(0.0, 3.0, 0.0);
		glVertex3f(0.0, 1.6, 0.0);
	glEnd();
	glPopMatrix();

	//draw spotlight 2 - light 4
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);  //set material emission component

		glTranslatef(gLightPosition4[0], gLightPosition4[1], gLightPosition4[2]);
		glutSolidSphere(0.15, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();
	//draw light rope
	glColor4f(0.0, 0.0, 0.0, 1.0);		//set color
	glLineWidth(2.5);
	glPushMatrix();
		glTranslatef(gLightPosition4[0], gLightPosition4[1], gLightPosition4[2]);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.6, 0.0);
		glEnd();
	glPopMatrix();

	//draw light 5
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);  //set material emission component

		glTranslatef(gLightPosition5[0], gLightPosition5[1], gLightPosition5[2]);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();
	//draw light rope
	glColor4f(0.0, 0.0, 0.0, 1.0);		//set color
	glLineWidth(2.5);
	glPushMatrix();
		glTranslatef(gLightPosition5[0], gLightPosition5[1], gLightPosition5[2]);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
		glEnd();
	glPopMatrix();

	//draw light 5
	glPushMatrix();
	if (blackBgWhiteWire)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	else if (whiteBgBlackWire)
		glColor4f(0.0, 0.0, 0.0, 1.0);
	else if (blueBgYellowWire)
		glColor4f(colorArray[3].r, colorArray[3].g, colorArray[3].b, 1.0);
	else
	glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);  //set material emission component

		glTranslatef(gLightPosition6[0], gLightPosition6[1], gLightPosition6[2]);
		glutSolidSphere(0.3, 16, 16);
		glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
	glPopMatrix();
	

}

//draws painting on the walls and sets painting
void drawPainting(int id, float x, float x2, float y, float y2, float z, float z2, Color color, float alpha)
{
	//draw picture frame and bind image
	glBindTexture(GL_TEXTURE_2D, textures[id]);       // bind texture
	glPushMatrix();
		if (blackBgWhiteWire)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			drawBox(x, x2, y, y2, z, z2, colorArray[8], 1.0);
		}
		if (whiteBgBlackWire)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			drawBox(x, x2, y, y2, z, z2, colorArray[7], 1.0);
		}
		if (blueBgYellowWire)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			drawBox(x, x2, y, y2, z, z2, colorArray[3], 1.0);
		}
		else
			drawBox(x, x2, y, y2, z, z2, color, alpha);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);				// reset texture

}

//draw objects on the table
void drawObjects()
{
	Color color;
	color.r = colorArray[8].r;
	color.g = colorArray[8].g;
	color.b = colorArray[8].b;
	if (blackBgWhiteWire)
	{
		color.r = colorArray[8].r; color.g = colorArray[8].g; color.b = colorArray[8].b;
	}
	else if (whiteBgBlackWire)
	{
		color.r = colorArray[7].r; color.g = colorArray[7].g; color.b = colorArray[7].b;
	}
	else if (blueBgYellowWire)
	{
		color.r = colorArray[3].r; color.g = colorArray[3].g; color.b = colorArray[3].b;
	}


	glBindTexture(GL_TEXTURE_2D, 0);							//reset texture
	//set plastic material for pedestals
	glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_ambient);        //set material ambient component
	glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_diffuse);        //set material diffuse component
	glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_specular);      //set material specular component
	glMateriali(GL_FRONT, GL_SHININESS, shinePlastic);			//set material shininess	
	//draw front box pedestal
	glPushMatrix();
		drawBox(0.5, 0.5, 0.5, -0.18, 1.0, 1.0, color, 1.0);
	glPopMatrix();
	//draw back box pedestal
	glPushMatrix();
		drawBox(0.5, 0.5, 0.5, -0.18, 9.0, -7.0, color, 1.0);
	glPopMatrix();
	
	glColor4f(1.0, 1.0, 1.0, 1.0);	//set color

	//draw painting 1
	drawPainting(3, 1.8, -1.8, -1.2, 1.2, 12.3, -13.2, color, 1.0);
	//draw painting 2
	drawPainting(4, -1.8, 1.8, -1.2, 1.2, 12.3, -13.2, color, 1.0);
	//draw painting 3
	drawPainting(5, -4.1, 3.15, -1.2, 1.2, 1.0, 0.0, color, 1.0);
	//draw painting 4
	drawPainting(6, 3.15, -4.1, -1.2, 1.2, 1.0, 0.0, color, 1.0);
	//draw painting 5
	drawPainting(7, -4.1, 3.15, -1.2, 1.2, 9.0, -9.0, color, 1.0);
	//draw painting 6
	drawPainting(8, 3.15, -4.1, -1.2, 1.2, 9.0, -9.0, color, 1.0);
	//draw rotating teapot
	drawTeapot();
	//set material to inital one
	setInitMaterial();
	//draw rotating transparent torus under the teapot
	drawTorus();

	// set material to plastic 
	glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_ambient);        //set material ambient component
	glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_diffuse);        //set material diffuse component
	glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_specular);      //set material specular component
	glMateriali(GL_FRONT, GL_SHININESS, shinePlastic);			//set material shininess	
	
	
	//draw pyramid made of boxes
	drawPyramid();

	//draw poles in front of gallery
	//bottom cones in the poles - opaque
	if (blackBgWhiteWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[8].r; color.g = colorArray[8].g; color.b = colorArray[8].b;
	}
	else if (whiteBgBlackWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[7].r; color.g = colorArray[7].g; color.b = colorArray[7].b;
	}
	else if (blueBgYellowWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[3].r; color.g = colorArray[3].g; color.b = colorArray[3].b;
	}
	else
	{
		color.r = 0.0, color.g = 0.0, color.b = 0.5;
	}

	glColor4f(color.r, color.g, color.b, 1.0);
	glPushMatrix();
		glTranslatef(-3.3, -0.4, 4.5);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		if (blackBgWhiteWire || whiteBgBlackWire)
			glutWireCone(0.25, 3.1, 24, 16);
		else
			glutSolidCone(0.25, 3.1, 24, 16);
	glPopMatrix();
	glColor4f(color.r, color.g, color.b, 1.0);
	glPushMatrix();
		glTranslatef(3.3, -0.4, 4.5);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		if (blackBgWhiteWire || whiteBgBlackWire)
			glutWireCone(0.25, 3.1, 24, 16);
		else
			glutSolidCone(0.25, 3.1, 24, 16);
	glPopMatrix();
	

	if (blackBgWhiteWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[8].r; color.g = colorArray[8].g; color.b = colorArray[8].b;
	}
	else if (whiteBgBlackWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[7].r; color.g = colorArray[7].g; color.b = colorArray[7].b;
	}
	else if (blueBgYellowWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color.r = colorArray[3].r; color.g = colorArray[3].g; color.b = colorArray[3].b;
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);	//bind glass texture
		enableBlending();							//enable alpha blending

		color.r = colorArray[10].r; color.g = colorArray[10].g; color.b = colorArray[10].b;
	}
	
	//top cones in the poles - transparent
	glColor4f(color.r, color.g, color.b, 0.5);
	glPushMatrix();
		glTranslatef(3.3, 2.6, 4.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		if (blackBgWhiteWire || whiteBgBlackWire || blueBgYellowWire)
			glutWireCone(0.25, 3.1, 24, 16);
		else
			glutSolidCone(0.25, 3.1, 24, 16);
	glPopMatrix();
	glColor4f(color.r, color.g, color.b, 0.5);
	glPushMatrix();
		glTranslatef(-3.3, 2.6, 4.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		if (blackBgWhiteWire || whiteBgBlackWire || blueBgYellowWire)
			glutWireCone(0.25, 3.1, 24, 16);
		else
			glutSolidCone(0.25, 3.1, 24, 16);
	glPopMatrix();

	disableBlending();							//disable alpha blending
	glBindTexture(GL_TEXTURE_2D, 0);			//reset texture

}

void drawPyramid() 
{
	Color color1, color2;
	if (blackBgWhiteWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color1.r = colorArray[8].r; color1.g = colorArray[8].g; color1.b = colorArray[8].b;
		color2.r = colorArray[8].r; color2.g = colorArray[8].g; color2.b = colorArray[8].b;
	}
	else if (whiteBgBlackWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color1.r = colorArray[7].r; color1.g = colorArray[7].g; color1.b = colorArray[7].b;
		color2.r = colorArray[7].r; color2.g = colorArray[7].g; color2.b = colorArray[7].b;
	}
	else if (blueBgYellowWire)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		color1.r = colorArray[3].r; color1.g = colorArray[3].g; color1.b = colorArray[3].b;
		color2.r = colorArray[3].r; color2.g = colorArray[3].g; color2.b = colorArray[3].b;
	}
	else
	{
		color1.r = colorArray[2].r, color1.g = colorArray[2].g, color1.b = colorArray[2].b;
		color2.r = colorArray[10].r, color2.g = colorArray[10].g, color2.b = colorArray[10].b;
	}
	//draw pyramid made of boxes
	glPushMatrix();
		drawBox(0.1, 0.1, 0.3, 0.5, 8.1, -7.9, color1, 1.0);
	glPopMatrix();
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glPushMatrix();
		drawBox(-0.1, -0.1, 0.0, 0.8, 7.9, -8.1, color2, 1.0);
	glPopMatrix();
	glPushMatrix();
		drawBox(-0.2, -0.2, -0.3, 1.1, 7.8, -8.2, color1, 1.0);
	glPopMatrix();
	glPushMatrix();
		drawBox(-0.3, -0.3, -0.6, 1.4, 7.7, -8.3, color2, 1.0);
	glPopMatrix();

	//enable texturing if not wireframe mode
	if (!whiteBgBlackWire && !blackBgWhiteWire && !blueBgYellowWire)
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);	//bind glass texture
		enableBlending();							//enable alpha blending
	}
	
	//draw box to hold pyramid
	glPushMatrix();
		drawBox(-0.4, -0.4, -0.8, 0.5, 7.6, -8.4, color2, 0.7);
	glPopMatrix();
	disableBlending();							//disable alpha blending
	glBindTexture(GL_TEXTURE_2D, 0);			//reset texture
}

//function displays user help menu using 2d projection - toggled with 'h'
void drawMenu()
{
	glDisable(GL_DEPTH_TEST);			//disable depth test in order to use 2d projection
	glDisable(GL_LIGHTING);				//disable lightning
	glEnable2D();						//set up 2d projection

	Color color;
	//set color of menu depending on a day or night mode
	if (nightMode)
	{
		color.r = colorArray[1].r; color.g = colorArray[1].g; color.b = colorArray[1].b;
	}
	else {
		color.r = colorArray[0].r; color.g = colorArray[0].g; color.b = colorArray[0].b;
	}

	//display user interaction instructions
	displayText(10, 580, "H - User Interaction Help Menu", color);
	displayText(10, 565, "ESC - quit program", color);
	displayText(10, 550, "---------	CAMERA	----------", color);
	displayText(10, 535, "W/S - pitch up/down", color);
	displayText(10, 520, "A/D - yaw left/right", color);
	displayText(10, 505, "PAGE UP/PAGE DOWN - move up/down", color);
	displayText(10, 490, "UP/DOWN/LEFT/RIGHT - move forward/backward/left/right", color);
	displayText(10, 475, "HOME - return to initial position", color);
	
	displayText(10, 460, "------WIREFRAME MODE-------", color);
	displayText(10, 445, "1 - white wireframe with black background", color);
	displayText(10, 430, "2 - black wireframe with white background", color);
	displayText(10, 415, "3 - yellow wireframe with blue background", color);

	displayText(10, 400, "--------SOLID MODE---------", color);
	displayText(10, 385, "4 - colored without lighting or textures", color);
	displayText(10, 370, "5 - shaded using lighting", color);
	displayText(10, 355, "6 - textured without lighting", color);
	displayText(10, 340, "7 - shaded using lighting and textured", color);


	displayText(10, 325, "----------	LIGHTS	-----------", color);
	displayText(10, 310, "F1 - left blue light", color);
	displayText(10, 295, "F2 - right red light", color);
	displayText(10, 280, "F3 - middle globe light", color);
	displayText(10, 265, "F4 - back globe light", color);
	displayText(10, 250, "F5 - spotlight 1 inside of the gallery", color);
	displayText(10, 235, "F6 - spotlight 2 in front of the gallery", color);
	displayText(10, 220, "'+' - day mode", color);
	displayText(10, 205, "'-' - night mode", color);
	displayText(10, 190, "L/l - toggle blinking lights on/off", color);

	//display if night or day mode
	if(nightMode)
		displayText(600, 580, "Current mode: Night mode", color);
	else if(dayMode)
		displayText(600, 580, "Current mode: Day mode", color);

	//display frames per second
	displayText(600, 565, "Fps: " + fpsStr, color);

	if (whiteBgBlackWire)
		displayText(575, 550, "Wireframe: black, Background: white", color);
	else if (blackBgWhiteWire)
		displayText(575, 550, "Wireframe: black, Background: white", color);
	else if (blueBgYellowWire)
		displayText(575, 550, "Wireframe: yellow, Background: blue", color);

	

	glDisable2D();						//disable 2d projection
	glEnable(GL_DEPTH_TEST);			//enable depth test again
	glEnable(GL_LIGHTING);				//enable lightning

}

//function sets the 2d projection which will be used to display user help menu
void glEnable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
//function disables 2d projection after user menu has been displayed
void glDisable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


// This function reads a RGB bitmap file
unsigned char* LoadBMPFile(char *filename, int id)
{
	BITMAPINFOHEADER BMPInfoHeader;   //bitmap info header
	BITMAPFILEHEADER BMPFileHeader;	  //bitmap file header
	FILE *filePtr;					  //the file pointer
	unsigned char *bitmapImage;		  //bitmap image data
	unsigned char temp;				  //temp variable for swapping RGB values
	int size, i = 0;		          //counter

										  // open filename for reading in binary mode
	if ((filePtr = fopen(filename, "rb")) == NULL)
	{
		return NULL;
	}

	// read bitmap file header
	fread(&BMPFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// check whether file is really a bitmap file
	if (BMPFileHeader.bfType != 0x4D42)
	{
		fclose(filePtr); // if file is not a bitmap file the close and return NULL
		return NULL;
	}

	// read bitmap information header
	fread(&BMPInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// locate beginning of bitmap data
	fseek(filePtr, BMPFileHeader.bfOffBits, SEEK_SET);

	size = BMPInfoHeader.biSizeImage;      // store image size

	textureInfo[id].imageWidth = BMPInfoHeader.biWidth;    // store image width 
	textureInfo[id].imageHeight = BMPInfoHeader.biHeight;  // store image height


										   // allocate memory for image data, check if not allocated properly then close file and return NULL
	if ((bitmapImage = (unsigned char*)malloc(size)) == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// read bitmap data
	fread(bitmapImage, 1, size, filePtr);

	// colours in bitmap are of the format BGR, hence need to swap B and R to get RGB
	for (i = 0; i < size; i += 3)
	{
		temp = bitmapImage[i];
		bitmapImage[i] = bitmapImage[i + 2];
		bitmapImage[i + 2] = temp;
	}

	fclose(filePtr);    // close file
	return bitmapImage; // return pointer to image data
}



/**********************************************/
/**************		MAIN	*******************/
/**********************************************/

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//requests properties for the window (sets up the rendering context)
	glutInitWindowSize(windowWidth, windowHeight);					//set window size in pixels
	glutInitWindowPosition(50, 100);								//set window position from top-left corner of display
	glutCreateWindow("Assignment 4 - Art Gallery");					//set window title

	init();															//call function to setup states 

	glutReshapeFunc(resizeWindow);			//register reshape callback function
	glutDisplayFunc(drawScene);				//register display callback function
	glutKeyboardFunc(myKeypress);			//register keyboard callback function
	glutSpecialFunc(mySpecialKeys);			//register non-ASCII keypress callback function
	glutTimerFunc(100, myTimer, 0);			//timer function
	glutIdleFunc(myIdleFunc);				//idle function
	glutMainLoop();							//enter event loop

	delete textures;
}




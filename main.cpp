/*
to install glut, use:
apt-get install freeglut3-dev
apt-get install libglew-dev
*/
/*
	glew probes your video hardware for support, and alters
	gl.h to use said features if available during compile.
	To be honest, I think what it does is a bit of black
	magic.
*/
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

//used for FPS calculation.
#include <sys/time.h> 
#include <signal.h>

//globals just because - don't do this in production.
GLuint cubeBuffer;
GLuint cubeIndex;
int vBufferSize;//memory size of buffer.
int indexLength;//length of index.
GLint xRot = 0;
GLint yRot = 0;
int frames = 0;
bool bad = false;
bool colored = true;

//OPEN GL 2 TUTORIAL:
//Keep in mind this is being included in a non standard way. 
//I kept it simple for this tutorial.
#include "texture.cpp"

/***************************
* Open GL 1 Tutorial:
****************************/
void FPSTimer(){
	cout << "Ayy, FPS:" << frames << endl;
	frames = 0;	
}

void createFPSTimer(){
	itimerval i;
	i.it_value.tv_sec = 1;
	i.it_value.tv_usec = 0;
	i.it_interval.tv_sec = 1;
	i.it_interval.tv_usec = 0;

	signal( SIGALRM, (void(*)(int))FPSTimer );
	setitimer( ITIMER_REAL, &i, NULL );
}

void keyboard( unsigned char key, int x, int y ){
	int mod = glutGetModifiers();
	switch (key){			
		case 27:
			exit(0);
		break;
		case 98:
			cout << "Switched to bad way." << endl;
			bad = true;
		break;
		case 103:
			cout << "Switched to good way." << endl;
			bad = false;
		break;
		case 'c':
			if (colored) {
				cout << "disabled color code." << endl;
				colored = false;
			} else {
				cout << "enabled color code." << endl;
				colored = true;				
			}
		break;
	}
}

void drawBuffer(){
	//now we draw our cube from video memory.
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer); //bind  o u r 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndex);
	//glEnableClientState, tells ope	n GL 	to reset to  th i s point in memory to begin drawing.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY );
	//tell open gl how to read the buffer.
	//this method works by taking: number of elements, type of data, buffer size, offset in data.
	glVertexPointer(3, GL_FLOAT, vBufferSize, (void*)(0) );
	//glClientActiveTexture(GL_TEXTURE0 ) 		
	glTexCoordPointer(2, GL_FLOAT, vBufferSize, (void*)(sizeof(GLfloat)*3 ) ) ;

	//draw the triangles
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_SHORT, 0);

	//end drawing.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawOldWay(){
	//The bad old way.
	//If you do this, you are a noob.
	glBegin(GL_TRIANGLES);
		if (colored) {
			glColor3f( 1.0f , 0.0f, 0.0f );
		} else {
			glColor3f( 1.0f , 1.0f, 1.0f );
		}
	
		//front
		glVertex3f( -.4, 	-.4, 	.4f);
		glTexCoord2f( 0, 0 );
		glVertex3f( .4, 	-.4, 	.4f);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4,	.4, 	.4f);
		glTexCoord2f( 0, 1 );
		glVertex3f( .4,		-.4, 	.4f);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4,		.4, 	.4f);
		glTexCoord2f( 1, 1 );
		glVertex3f( -.4,	.4, 	.4f);
		glTexCoord2f( 0, 1 );

		//back
		glVertex3f( -.4, 	-.4, 	-.4f);
		glTexCoord2f( 0, 0 );
		glVertex3f( .4, 	-.4, 	-.4f);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4,	.4, 	-.4f);
		glTexCoord2f( 0, 1 );
		glVertex3f( .4,		-.4, 	-.4f);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4,		.4, 	-.4f);
		glTexCoord2f( 1, 1 );
		glVertex3f( -.4,	.4, 	-.4f);
		glTexCoord2f( 0, 1 );

		//top
		glVertex3f( -.4,	.4f, 	-.4);
		glTexCoord2f( 0, 0 );
		glVertex3f( .4, 	.4f, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4,	.4f, 	.4);
		glTexCoord2f( 0, 1 );
		glVertex3f( .4,		.4f, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4,		.4f, 	.4);
		glTexCoord2f( 1, 1 );
		glVertex3f( -.4,	.4f, 	.4);
		glTexCoord2f( 0, 1 );

		//bottom
		glVertex3f( -.4,	-.4f, 	-.4);
		glTexCoord2f( 0, 0 );
		glVertex3f( .4, 	-.4f, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4,	-.4f, 	.4);
		glTexCoord2f( 0, 1 );
		glVertex3f( .4,		-.4f, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4,		-.4f, 	.4);
		glTexCoord2f( 1, 1 );
		glVertex3f( -.4,	-.4f, 	.4);
		glTexCoord2f( 0, 1 );

		//right
		glVertex3f( -.4f, 	-.4, 	-.4);
		glTexCoord2f( 0, 0 );
		glVertex3f( -.4f, 	.4, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4f, 	-.4, 	.4);
		glTexCoord2f( 0, 1 );
		glVertex3f( -.4f, 	.4, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( -.4f, 	.4, 	.4);
		glTexCoord2f( 1, 1 );
		glVertex3f( -.4f, 	-.4, 	.4);
		glTexCoord2f( 0, 1 );

		//right
		glVertex3f( .4f, 	-.4, 	-.4);
		glTexCoord2f( 0, 0 );
		glVertex3f( .4f, 	.4, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4f, 	-.4, 	.4);
		glTexCoord2f( 0, 1 );
		glVertex3f( .4f, 	.4, 	-.4);
		glTexCoord2f( 1, 0 );
		glVertex3f( .4f, 	.4, 	.4);
		glTexCoord2f( 1, 1 );
		glVertex3f( .4f, 	-.4, 	.4);
		glTexCoord2f( 0, 1 );

	glEnd();
}

void render(){
	//clear the buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//tell open GL we are playing with verticies.
	glMatrixMode( GL_MODELVIEW );

	//begin a new drawing matrix:
	glLoadIdentity();

	//push the matrix to begin working on a specific object being rendered.
	glPushMatrix();
	
	//call our method to draw from video memory.
	glTranslated( 0,0,0 );	//move it 0,0,0
	if (colored) {
		glColor3f( 0.0f, 0.0f,1.0f );//make it blue, but light enough to show texture.
	} else {
		glColor3f( 1.0f, 1.0f, 1.0f);//white, means no color.
	}
	glRotated( yRot, 0.0, 1.0, 0.0 );//rotate it around Y
	glRotated( xRot, 1.0, 0.0, 0.0 );//rotate it around X
	//new for OPENGL 2 Tut:
	glBindTexture( GL_TEXTURE_2D, texture.tid );

	if(bad){
		drawOldWay();
	} else {
		drawBuffer();
	}

	glPopMatrix();

	yRot++;
	xRot+=2;
	frames++;
	//Swap buffers for to draw the new scene.
	glutSwapBuffers();
}

void changeSize(int x, int y){
	//do stuff if the window size has changed.
	//nothing here for now, just showing you can create a call back if the window changes size.
}

void loadCubeToMemory(){
	/*
		before we pass our cube to the buffer, we need to create it 
		in data first. This can also be done dynamically, if you want
		to erase the cube from memory afterwards.
	*/
	/*	
		a vertex with x,y,z,u,v,r,g,b in that order.
		u and v are the texture cordinates of the verticy, this will
		be important when you learn texturing.
		a cube has 8 corners, so we only need to fill this with those 
		8 verticies.
	*/
	GLfloat vertex[8][5]; 
	//store the size of one verticy.
	vBufferSize = sizeof(GLfloat) * 5;
	//1
	vertex[0][0] = -.4;
	vertex[0][1] = -.4;
	vertex[0][2] = .4;
	vertex[0][3] = 0;
	vertex[0][4] = 0;
	//2
	vertex[1][0] = .4;
	vertex[1][1] = -.4;
	vertex[1][2] = .4;
	vertex[1][3] = 1;
	vertex[1][4] = 0;
	//3
	vertex[2][0] = .4;
	vertex[2][1] = .4;
	vertex[2][2] = .4;
	vertex[2][3] = 1;
	vertex[2][4] = 1;
	//4
	vertex[3][0] = -.4;
	vertex[3][1] = .4;
	vertex[3][2] = .4;
	vertex[3][3] = 0;
	vertex[3][4] = 1;
	//5
	vertex[4][0] = -.4;
	vertex[4][1] = -.4;
	vertex[4][2] = -.4;
	vertex[4][3] = 1;
	vertex[4][4] = 0;
	//6
	vertex[5][0] = .4;
	vertex[5][1] = -.4;
	vertex[5][2] = -.4;
	vertex[5][3] = 0;
	vertex[5][4] = 0;
	//7
	vertex[6][0] = .4;
	vertex[6][1] = .4;
	vertex[6][2] = -.4;
	vertex[6][3] = 0;
	vertex[6][4] = 1;
	//8
	vertex[7][0] = -.4;
	vertex[7][1] = .4;
	vertex[7][2] = -.4;
	vertex[7][3] = 1;
	vertex[7][4] = 1;


	/*
		Now we need to draw with our verticies. 
		Each face is drawn in two triangles. 
		Each Triangle needs to be drawn counter clockwise for it to display the 
		front of the triangle.
		For the back we go clockwise, because it is on the back of the cube.
	*/
	GLushort index[36];
	//store our index buffer size for later use:
	indexLength = 36;
	//front
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 0;
	index[4] = 2;
	index[5] = 3;
	//back
	index[6] = 4;
	index[7] = 6;
	index[8] = 5;
	index[9] = 4;
	index[10] = 7;
	index[11] = 6;
	//left
	index[12] = 4;
	index[13] = 0;
	index[14] = 3;
	index[15] = 4;
	index[16] = 3;
	index[17] = 7;
	//bottom
	index[18] = 4;
	index[19] = 5;
	index[20] = 1;
	index[21] = 4;
	index[22] = 1;
	index[23] = 0;
	//right
	index[24] = 1;
	index[25] = 5;
	index[26] = 6;
	index[27] = 1;
	index[28] = 6;
	index[29] = 2;
	//top
	index[30] = 3;
	index[31] = 2;
	index[32] = 6;
	index[33] = 3;
	index[34] = 6;
	index[35] = 7;
	
	/*
		Now we tell OpenGL create a buffer in video memory for
		our cube. This is the proper way to load models into
		memory, thus why I teach it first thing in this tutorial.
		It is bad practice to pass data from memory to video 
		memory each frame, it is very slow and will cause your
		game to lag.
	*/
	//this method works by taking: size, reference to integer to store index.
	glGenBuffers( 1, &cubeBuffer );
	//An index of how to draw the vertices as triangles.
	//start at 0 and then draw each verticy in order.
	glGenBuffers( 1, &cubeIndex ); 

	//now we pass our verticies for our cube to memory:
	//GL_ARRAY_BUFFER is the buffer type we need for verticy data.
	//this method works by taking: dest, buffer #
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer); // tell open GL to use this buffer for memory transfer.
	//store our verticy buffer size for later use:
	//this method works by taking: dest, size, reference to entry point of data, what to do with it.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0][0], GL_STATIC_DRAW);//now pass it to memory.
	//now do the same with the index.
	//GL_ELEMENT_ARRAY_BUFFER is the buffer type we need for an index of verticies.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndex); // tell open GL to use this buffer for memory transfer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), &index[0], GL_STATIC_DRAW);//now pass it to memory.
}

void setupLight(){
	glEnable( GL_LIGHTING );

	GLfloat amb[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat dif[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat spec[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat pos[] = {0.0, 0.0, 5.0 };

	glTexEnvi(GL_TEXTURE_ENV_MODE,GL_MODULATE,1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif );
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec );
	glLightfv(GL_LIGHT0, GL_POSITION, pos );
	glEnable( GL_LIGHT0 );
}

void createContext( int argc, char **argv ){
	//	Initialize GLUT, it requires the command line arguments to be passed in.
	glutInit (&argc, argv); //p
	//	set the size of the window we will be creating.
	glutInitWindowSize ( 768, 768 );
	/* 	The next method sets the GL Context Environment. You can also set 
		things like full screen and color mode here. */
	//glutInitDisplayMode ( GLUT_RGB | GLUT_DEPTH ); //no V-Sync
	//use this instead if you want v-sync:
	glutInitDisplayMode ( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE ); //no V-Sync

	glutCreateWindow ("Meme Cube");

	//	Initialize GLEW for extended openGL features.
	glewInit();

	//bind callbacks for GLUT:
	glutDisplayFunc(render); //when the window has changed states.
	glutIdleFunc(render); //a frame
	glutReshapeFunc(changeSize); //window resize
	glutKeyboardFunc(keyboard);

	//prepare Open GL
	// a little trick to see what version of Open GL your hardware can support.
	cout << "Using Open GL, version: " << glGetString(GL_VERSION) << endl;
	/*
		Here we set the matrix mode, default is model.
		This is used to change what matrix we are altering. 
		options are:
		GL_MODELVIEW: the matrix of verticies and normals.
		GL_PROJECTION: The matrix of the environment.
		GL_TEXTURE: The matrix of texturing.
		GL_COLOR: The matrix for coloring.
	*/
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); //load an identy to prepare environment.
	glClearColor( 0, 0, 0, 0 ); //clear the screen to black, default is black.
	//you can set a number of different things here to configure your viewport
	//but in this tutorial we will use the defaults.
	glMatrixMode( GL_MODELVIEW ); //switch back to model so we can render
	glLoadIdentity();
	//point the camera
	//OPTIONAL: Enable perspective viewing:
	//*
	gluPerspective(75.0f, 1.0,0.0f, 10000.0f);
	//*/
	gluLookAt(//WHY IS THIS METHOD SO UGLY!
		0.0, 0.0, -100.0,//position
		0.0, 0.0, 10.0,//pointed at
		0.0, 1.0, 0.0//vector direction, No fucking idea, just always point up.
	);
	glEnable( GL_COLOR_MATERIAL ); //tell GL how to handle texture coloring.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // tell open gl how to clear.
	glEnable(GL_DEPTH_TEST); //enable depth testing, so openGL won't draw polygon's behind others in front.

	setupLight();
}

int main( int argc, char **argv ){
	createContext( argc, argv );
	texture.setup();//This needs to happen to configure Open GL to handle textures.
	texture.load();// Open GL 2 Tutorial, load that texture!
	loadCubeToMemory();
	//createFPSTimer(); //For OGL2, let's not do this, you can turn it back on if you want.
	glutMainLoop();
}	
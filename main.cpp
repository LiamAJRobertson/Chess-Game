#include "Dependencies\glew\glew.h"
#include "Dependencies\freeGlut\freeglut.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include "Window.h"

void DrawGLScene(GLvoid);
void ReSizeGLScene(GLsizei fWidth, GLsizei fHeight);
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void passiveMouseMotion(int x, int y);
void menuFunction1(int Option);
void constructMenus(void);

using namespace std;

Window window;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Liam Robertson 1504603");
	glEnable(GL_DEPTH_TEST);	//enable the depth buffer test

	glutDisplayFunc(DrawGLScene);
	glutReshapeFunc(ReSizeGLScene);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	constructMenus();
	
	window.initGL();

	glutMainLoop();

}

void DrawGLScene(void) {
	window.myDrawGLScene();
}

GLvoid ReSizeGLScene(GLsizei fwidth, GLsizei fheight) {
	window.MyReSizeGLScene(fwidth, fheight);
}


void mouseClick(int button, int state, int x, int y) {
	window.myMouseClick(button, state, x, y);
}

void mouseMotion(int x, int y) {
	window.myMouseMotion(x, y);
}

void passiveMouseMotion(int x, int y) {
	window.myPassiveMouseMotion(x, y);
}


void constructMenus(void)
{
	int myMenu = glutCreateMenu(menuFunction1);
	cout << "Created menu " << myMenu << endl;
	glutAddMenuEntry("Switch Player", 1);
	glutAddMenuEntry("Undo Last Move", 2);
	glutAddMenuEntry("Show Movement History", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuFunction1(int Option) {
	window.myMenuFunction1(Option);
}



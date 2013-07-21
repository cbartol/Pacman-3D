#include <GL/glut.h>

#include <iostream>
#include <cmath>
#include "conventions.h"
#include <stdio.h>
#include <list>
#include <algorithm>
#include "Game.h"
#include "camera/OrthoCamera.h"
#include "camera/Camera3D_1.h"
#include "camera/Camera3D_2.h"
#include "camera/Camera3D_3.h"
#include "light/SpotLight.h"
#include "light/DirecLight.h"
#ifdef __gnu_linux__
	#include <unistd.h>
	#include <signal.h>
	void myInit();
#endif

static int pID;
Game * game;
static char p2Key = '\0', pressedKey = '\0';
static int pressedSpecKey = 0;
static bool help = false, fullscreen = false;	/*help->Boleano que se envia no draw do Game, para indicar se é para mostrar a ajuda ou não*/
static float prevW, prevH;			/*Para quando se sai de fullscreen, a janela voltar
									ás medidas de antes de ser ter entrado em fullscreen*/


/*FUNçÃO CALLBACK PARA DISPLAY*/
void myDisplay( void) {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	game->draw(help);
	glutSwapBuffers();
}
/******************************/

/*FUNçÃO CALLBACK PARA RESHAPE*/
void myReshape(GLsizei width, GLsizei height){     
	glViewport( 0, 0, width, height);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	game->getCamera()->setProjectionMode(width, height);
}
/******************************/

/*FUNçÕES CALLBACK PARA QUANDO TECLA É PREMIDA*/
void keyboardPress(unsigned char c, int i, int j){
	if(c == 'a' || c == 'A'){
		pressedKey = game->getCamera()->convertDirection(game,'a');
	}else if(c == 'w' || c == 'W'){
		pressedKey = game->getCamera()->convertDirection(game,'w');
	}else if(c == 'd' || c == 'D'){
		pressedKey = game->getCamera()->convertDirection(game,'d');
	}else if(c == 's' || c == 'S'){
		pressedKey = game->getCamera()->convertDirection(game,'s');
	}else if(c == 'h' || c == 'H'){
		help = !help;
	}else if(c == 'n' || c == 'N'){
		delete game;
		pressedKey = '\0';
		pressedSpecKey = 0;
		help = false;
		fullscreen = false;
		game = new Game();
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}else if(c == 3){
		game->colision(0);
	}else if (c == 27){
		delete game;
		#ifdef __gnu_linux__
			killpg( 0, SIGKILL);
		#endif
		exit(-1);
	}
}

void specialKeyPress(int c, int i, int j){
	if(c == GLUT_KEY_UP){
		pressedKey = game->getCamera()->convertDirection(game,'w');
		pressedSpecKey = c;
	} else if(c == GLUT_KEY_DOWN){
		pressedKey =  game->getCamera()->convertDirection(game,'s');
		pressedSpecKey = c;
	} else if(c == GLUT_KEY_LEFT){
		pressedKey =  game->getCamera()->convertDirection(game,'a');
		pressedSpecKey = c;
	} else if(c == GLUT_KEY_RIGHT){
		pressedKey =  game->getCamera()->convertDirection(game,'d');
		pressedSpecKey = c;
	} else if(c == GLUT_KEY_F1){
		game->setCamera(new OrthoCamera());
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		if(fullscreen){ glutFullScreen();}
		glutPostRedisplay();
	} else if(c == GLUT_KEY_F2){
		game->setCamera(new Camera3D_1(game));
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		if(fullscreen){ glutFullScreen();}
		glutPostRedisplay();
	} else if(c == GLUT_KEY_F3){
		game->setCamera(new Camera3D_2(game));
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		if(fullscreen){ glutFullScreen();}		
		glutPostRedisplay();
	} else if(c == GLUT_KEY_F4){
		game->setCamera(new Camera3D_3(game));
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		//myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		if(fullscreen){ glutFullScreen();}		
		glutPostRedisplay();
	} else if(c == GLUT_KEY_F9)
		game->setLight(new DirecLight());
	else if(c == GLUT_KEY_F10)
		game->setLight(new SpotLight());
 	else if(c == GLUT_KEY_F12){
		if(fullscreen){
			glutReshapeWindow(prevW, prevH);
    		glutPositionWindow(-1,-1);
		}
		else{
			prevW = glutGet(GLUT_WINDOW_WIDTH);
			prevH = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		fullscreen = !fullscreen;
	}
}
/**********************************************/

/*FUNçÕES CALLBACK PARA VER QUE TECLA SE LARGOU*/
void keyboardUp(unsigned char c, int i, int j){
	if(pressedKey == game->getCamera()->convertDirection(game,tolower(c)))
		pressedKey = '\0';
}

void specialKeyUp(int key, int x, int y){
	if(pressedSpecKey == key){
		//p2Key = '\0'; ---> Para Multiplayer_ Descomentar e apagar linha de baixo.
		pressedKey = '\0';
		pressedSpecKey = 0;
	}
}
/***********************************************/

/*FUNçÃO CALLBACK PARA IDLE*/
void moveAction(){ 
	game->moves(pressedKey, p2Key, glutGet(GLUT_ELAPSED_TIME));
	glutPostRedisplay();
}
/***************************/


int main(int argc, char *argv[]){
	#ifdef __gnu_linux__
		myInit();
	#endif
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1040, 640);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Pacman-Man"); 
	game = new Game();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(moveAction);
	glutKeyboardFunc(keyboardPress);
	glutSpecialFunc(specialKeyPress);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialUpFunc(specialKeyUp);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	game->floorTexture();
	glutMainLoop();
}
#ifdef __gnu_linux__
	/*
	 * We didn't know how to put music in our game,
	 * so we create a new process to run vlc in background with our music.
	 * On exit game we kill the process that is running the music.
	 */
	void myInit(){
		pID = vfork();
		if (pID == 0) {               // child
			// Code only executed by child process
			execl("/usr/bin/cvlc", "/usr/bin/cvlc", "-Z", "./musics/2.mp3", "./musics/3.mp3", 0);
			std::cerr << "Failed to exec" << std::endl;
			exit(0);
		} else if (pID < 0) {           // failed to fork
			std::cerr << "Failed to fork" << std::endl;
			exit(1);
		} else {                                  // parent
		// Code only executed by parent process
			return;
		}
	}
#endif

#include "ScoreBoard.h"

void ScoreBoard::showScore(bool showHelp, bool gameOver, bool gameWin) {
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0.f, glutGet(GLUT_WINDOW_WIDTH), 0.f, glutGet(GLUT_WINDOW_HEIGHT), -2.0f, 2.0f);	// "Mudança" para projecção ortogonal
			drawHUD1();
			if(showHelp)
				drawHUD2();
			if(gameOver)
				drawEndMessage(gameWin);
			glEnable(GL_LIGHTING);	
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


void ScoreBoard::drawHUD1(){	/* HUD Inferior */
	int i;	
	std::stringstream out;			//
	std::string aux_points(_point_text);	// Conversão da variavel _points
	out << _points;				//para string, e junta-se, numa variavel auxiliar,
	aux_points += out.str();		//o texto dos Pontos, com o número de pontos

	glColor3f(0.0f, 0.0f, 0.0f);		// Cor do fundo do HUD		
	glBegin(GL_POLYGON);
		glVertex3f(0.,0.,0.);
		glVertex3f(glutGet(GLUT_WINDOW_WIDTH),0.,0.);	// Rectângulo Inferior
		glVertex3f(glutGet(GLUT_WINDOW_WIDTH),40.,0.);			
		glVertex3f(0.,40.,0.);
	glEnd();

	glColor3f(.7f, .7f, .7f);	// Cor das letras do HUD
	glRasterPos2f(5 , 15.);
	for (i = 0; _helpNote[i] != '\0' ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, _helpNote[i]);
	}
	glRasterPos2f((glutGet(GLUT_WINDOW_WIDTH)/2.) -72. , 3.);
	for (i = 0; aux_points[i] != '\0' ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, aux_points[i]);
	}
	glRasterPos2f((glutGet(GLUT_WINDOW_WIDTH)/2.)-72. , 23.);
	for (i = 0; _lives_text[i] != '\0' ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _lives_text[i]);
	}
	glRasterPos2f((glutGet(GLUT_WINDOW_WIDTH)/2.) + 55. -72., 23.);
	for (i = 0; i < _lives ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,  ' ');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,  'o');
	}
	for (; i < N_LIVES ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,  ' ');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,  248);
	}
}

void ScoreBoard::drawHUD2(){	/* HUD Superior */
	int i;	
	glColor3f(0.0f, 0.0f, 0.0f);		// Cor do fundo do HUD
	glBegin(GL_POLYGON);
		glVertex3f(0.,glutGet(GLUT_WINDOW_HEIGHT) - 40.,0.);
		glVertex3f(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT) - 40.,0.);	// Rectângulo Superior
		glVertex3f(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),0.);			
		glVertex3f(0.,glutGet(GLUT_WINDOW_HEIGHT),0.);
	glEnd();

	glColor3f(.7f, .7f, .7f);	// Cor das letras do HUD
	glRasterPos2f(3., glutGet(GLUT_WINDOW_HEIGHT) - 15.);
	for (i = 0; _helpTop[i] != '\0' ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, _helpTop[i]);
	}
	glRasterPos2f(3., glutGet(GLUT_WINDOW_HEIGHT) - 33.);
	for (i = 0; _helpBottom[i] != '\0' ; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, _helpBottom[i]);
	}
}


void ScoreBoard::drawEndMessage(bool gameWin){		/* HUD de Game Over ou Vitória. */
	int i;	
	float glwidth = glutGet(GLUT_WINDOW_WIDTH);
	float glheight = glutGet(GLUT_WINDOW_HEIGHT)/3.;

	glColor3f(0.0f, 0.0f, 0.0f);		// Cor do fundo do HUD
	glBegin(GL_POLYGON);
		glVertex3f(0   ,glheight   ,0.);
		glVertex3f(glwidth ,glheight   ,0.);	// Rectângulo Inferior
		glVertex3f(glwidth ,glheight*2 ,0.);			
		glVertex3f(0   ,glheight*2 ,0.);
	glEnd();
	
	
	glColor3f(.7f, .7f, .7f);	// Cor das letras do HUD

	if(!gameWin) {
		std::string gameOver = "GAME OVER!";
		glRasterPos2f(glwidth/2.-72, glheight*3./2.);
			for (i = 0; gameOver[i] != '\0' ; i++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
		}
	}
	else {
		std::string greatSucsess = "GREAT SUCCESS!";
		glRasterPos2f(glwidth/2.-72, glheight*3./2.);
			for (i = 0; greatSucsess[i] != '\0' ; i++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, greatSucsess[i]);
		}
	}

	std::string texto1 = "press \"N\" for new game";
	glRasterPos2f(glwidth/2.-65, glheight*3./2. - 40);
		for (i = 0; texto1[i] != '\0' ; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto1[i]);
	}
}

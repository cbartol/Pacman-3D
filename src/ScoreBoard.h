#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <iostream>
#include <GL/glut.h>
#include <string>
#include <sstream>
#define N_LIVES 3


class ScoreBoard {
	private:
		int _points;
		int _lives;
		std::string _point_text;
		std::string _lives_text;
		std::string _helpNote;
		std::string _helpTop;
		std::string _helpBottom;
	public:
		ScoreBoard() : _points(0), _lives(N_LIVES), _point_text("Points: "), _lives_text("Lives: "), _helpNote("Press H for Help"),
													     _helpTop("<HELP>   w:a:s:d:arrowKeys >> Pacman Direction    F1:F2:F3:F4 >> Switch between Cams    F9 >> Directional Light    F10 >> SpotLight"),
													     _helpBottom("              ESC >> Close Game    F12 >> Toggle/Exit FullScreen  H >> Close Help") {}
		void add(int points) { _points += points; }
		bool killLives() { return (--_lives <= 0);}
		void showScore(bool showHelp, bool gameOver, bool gameWin);
		
	private:
		void drawHUD1();
		void drawHUD2();
		void drawEndMessage(bool gameWin);
};
#endif

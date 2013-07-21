#include "Board.h"
#include "Game.h"
#include "conventions.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
position Board::checkPacmanPath(position orig, position dest, char key, int *dir, Game* game){
	float xorig = orig.x + 12., yorig = (-orig.y)+  7., xdest = dest.x + 12., ydest = (-dest.y)+  7.;
	/**
	 * xorig->posição x inicial do Pacman convertida para a matriz
	 * yorig->posição y inicial do Pacman convertida para a matriz
	 * xdest->posição x destino do Pacman convertida para a matriz
	 * ydest->posição y destino do Pacman convertida para a matriz
	**/
	float xx = dest.x - orig.x;	//xx->deslocamento(real) pretendido no eixo dos xx
	float yy = dest.y - orig.y;	//yy->deslocamento(real) pretendido no eixo dos yy
	int auxA, auxB, auxC;

	if(xx < 0){			// Se xx<0, entao Pac esta a movimentar-se para
		*dir = LEFT;		//a ESQUERDA (ex: de 4->2 » 2 - 4 = -2)
		auxA = (int) floor(xorig);		//auxA->xorig arredondado para baixo (ex:8.64->8.00)
		auxB = (int) floor(xdest);		//auxB->igual, mas para o xdest
		auxC = (int) yorig;				//auxC->cast para inteiro do yorig
															/* ESTAMOS NO PACMAN*/
		for( ; auxB <= auxA ; auxA--){
			if(_boardArray[auxC][auxA+1] == B && xorig >= auxA+1 && xdest <= auxA+1){	/** Existe uma bola entre a posição inicial e final do Pacman **/
				_boardArray[auxC][auxA+1] = E;
				if((_ballsArray[auxC][auxA+1])->isSpecial()){
					game->changeState();
				}
				int add = (_ballsArray[auxC][auxA+1])->eaten();	// Nº de pontos a adicionar ao ScoreBoard
				game->scoreBoard()->add(add);			// Actualização do ScoreBoard
				game->ballEaten();
			}
			if(key == 'd' && _boardArray[auxC][auxA+2] != W){							//Tentativa de mudar de direcção para direita
				*dir = RIGHT;		//Mudança de direcção do Pacman
				dest.x = orig.x;
				break;

			} else if(key == 's' && _boardArray[auxC+1][auxA+1] != W && xorig >= auxA+1 && xdest <= auxA+1){	//Tentativa de mudar de direcção para baixo
				*dir = DOWN;		//Mudança de direcção do Pacman
				dest.y -= 0.001;
				dest.x = (float) (auxA+1 - 12.);	// '- 12.' -> conversão para valor real
				break;

			} else if(key == 'w' && _boardArray[auxC-1][auxA+1] != W && xorig >= auxA+1 && xdest <= auxA+1){	//Tentativa de mudar de direcção para cima
				*dir = UP;		//Mudança de direcção do Pacman
				dest.y += 0.001;
				dest.x = (float) (auxA+1 - 12.);
				break;

			} else if(_boardArray[auxC][auxA] == W){	// Caso contrário, se foi encontrada uma parede,
				dest.x = (float) (auxA+1) - 12.;		//coord x destino do Pac será a anterior
				break;
			}
		}
															/* ESTAMOS NO PACMAN*/
	} else if (xx >0){		// Se xx<0, entao Pac esta a movimentar-se para
		*dir = RIGHT;		//a DIREITA (ex: de -6->10 » 10 - (-6) = 16)
		auxA = (int) ceil(xorig);
		auxB = (int) ceil(xdest);
		auxC = (int) yorig;
		for( ; auxB >= auxA ; auxA++){
			if(_boardArray[auxC][auxA-1] == B && xorig <= auxA-1 && xdest >= auxA-1){	/** Existe uma bola entre a posição inicial e final do Pacman **/
				_boardArray[auxC][auxA-1] = E;
				if((_ballsArray[auxC][auxA-1])->isSpecial()){
					game->changeState();
				}
				int add = (_ballsArray[auxC][auxA-1])->eaten();	// Nº de pontos a adicionar ao ScoreBoard
				game->scoreBoard()->add(add);			// Actualização do ScoreBoard
				game->ballEaten();
			}
			if(key == 'a' && _boardArray[auxC][auxA-2] != W){							//Tentativa de mudar de direcção para esquerda
				*dir = LEFT;		//Mudança de direcção do Pacman
				dest.x = orig.x;
				break;

			} else if(key == 's' && _boardArray[auxC+1][auxA-1] != W && xorig <= auxA-1 && xdest >= auxA-1){	//Tentativa de mudar de direcção para baixo
				*dir = DOWN;		//Mudança de direcção do Pacman
				dest.y -= 0.001;
				dest.x = (float) (auxA-1 - 12.);	// '- 12.' -> conversão para valor real
				break;

			} else if(key == 'w' && _boardArray[auxC-1][auxA-1] != W && xorig <= auxA-1 && xdest >= auxA-1){	//Tentativa de mudar de direcção para cima
				*dir = UP;		//Mudança de direcção do Pacman
				dest.y += 0.001;
				dest.x = (float) (auxA-1 - 12.);
				break;

			} else if(_boardArray[auxC][auxA] == W){	// Caso contrário, se foi encontrada uma parede,
				dest.x = (float) (auxA-1 - 12.);		//coord x destino do Pac será a anterior
				break;
			}
		}

	} else if(yy < 0){		// Se yy<0, entao Pac esta a movimentar-se para
		*dir = DOWN;		//BAIXO (ex: de 4->-5 » -5 - 4 = -9)
		auxA = (int) ceil(yorig);
		auxB = (int) ceil(ydest);
		auxC = (int) xorig;
															/* ESTAMOS NO PACMAN*/
		for(; auxB >= auxA ; auxA++){
			if(_boardArray[auxA-1][auxC] == B && yorig <= auxA-1 && ydest >= auxA-1){	/** Existe uma bola entre a posição inicial e final do Pacman **/
				_boardArray[auxA-1][auxC] = E;
				if((_ballsArray[auxA-1][auxC])->isSpecial()){
					game->changeState();
				}
				int add = (_ballsArray[auxA-1][auxC])->eaten();	// Nº de pontos a adicionar ao ScoreBoard
				game->scoreBoard()->add(add);			// Actualização do ScoreBoard
				game->ballEaten();
			}
			if(key == 'a' && _boardArray[auxA-1][auxC-1] != W && yorig <= auxA-1 && ydest >= auxA-1){		//Tentativa de mudar de direcção para esquerda
				*dir = LEFT;		//Mudança de direcção do Pacman
				dest.x -= 0.001;
				dest.y = (float) -((auxA-1) - 7.);	// '- 7.' -> conversão para valor real
				break;

			} else if(key == 'd' && _boardArray[auxA-1][auxC+1] != W && yorig <= auxA-1 && ydest >= auxA-1){	//Tentativa de mudar de direcção para direita
				*dir = RIGHT;		//Mudança de direcção do Pacman
				dest.x += 0.001;
				dest.y = (float) -((auxA-1) - 7.);
				break;

			} else if(key == 'w' && _boardArray[auxA-2][auxC] != W){						//Tentativa de mudar de direcção para cima
				*dir = UP;		//Mudança de direcção do Pacman
				dest.y = orig.y;
				break;

			} else if(_boardArray[auxA][auxC] == W){	// Caso contrário, se foi encontrada uma parede,
				dest.y = (float) -((auxA-1) - 7.);		//coord y destino do Pac será a anterior
				break;
			}
		}
															/* ESTAMOS NO PACMAN*/
	} else if (yy > 0){		// Se xx<0, entao Pac esta a movimentar-se para
		*dir = UP;		//CIMA (ex: de 5->7 » 7 - 5 = 2)
		auxA = (int) floor(yorig);
		auxB = (int) floor(ydest);
		auxC = (int) xorig;
		for(; auxB <= auxA ; auxA--){
			if(_boardArray[auxA+1][auxC] == B && yorig >= auxA+1 && ydest <= auxA+1){	/** Existe uma bola entre a posição inicial e final do Pacman **/
				_boardArray[auxA+1][auxC] = E;
				if((_ballsArray[auxA+1][auxC])->isSpecial()){
					game->changeState();
				}
				int add = (_ballsArray[auxA+1][auxC])->eaten();	// Nº de pontos a adicionar ao ScoreBoard
				game->scoreBoard()->add(add);			// Actualização do ScoreBoard
				game->ballEaten();
			}
			if(key == 'a' && _boardArray[auxA+1][auxC-1] != W && yorig >= auxA+1 && ydest <= auxA+1){		//Tentativa de mudar de direcção para esquerda
				*dir = LEFT;		//Mudança de direcção do Pacman
				dest.x -= 0.001;
				dest.y = (float) -((auxA+1) - 7.);	// '- 7.' -> conversão para valor real
				break;

			} else if(key == 'd' && _boardArray[auxA+1][auxC+1] != W && yorig >= auxA+1 && ydest <= auxA+1){	//Tentativa de mudar de direcção para direita
				*dir = RIGHT;		//Mudança de direcção do Pacman
				dest.x += 0.001;
				dest.y = (float) -((auxA+1) - 7.);
				break;

			} else if(key == 's' && _boardArray[auxA+2][auxC] != W){						//Tentativa de mudar de direcção para baixo
				*dir = DOWN;		//Mudança de direcção do Pacman
				dest.y = orig.y;
				break;

			} else if(_boardArray[auxA][auxC] == W){	// Caso contrário, se foi encontrada uma parede,
				dest.y = (float) -((auxA+1) - 7.);		//coord y destino do Pac será a anterior
				break;
			}
		}
	}
	return dest;
}
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

position Board::checkGhostPath(position orig, position dest, char key, int *dir, Game* game){
	float xorig = orig.x + 12., yorig = (-orig.y)+  7., xdest = dest.x + 12., ydest = (-dest.y)+  7.;
	char rand_array[4] = {'w','a','s','d'};
	int x, i;
	//std::cout << "quero ir para: " << key << "\n";////////////////////////////////////
	/**
	 * xorig->posição x inicial do Ghost convertida para a matriz
	 * yorig->posição y inicial do Ghost convertida para a matriz
	 * xdest->posição x destino do Ghost convertida para a matriz
	 * ydest->posição y destino do Ghost convertida para a matriz
	**/
	float xx = dest.x - orig.x;	//xx->deslocamento(real) pretendido no eixo dos xx
	float yy = dest.y - orig.y;	//yy->deslocamento(real) pretendido no eixo dos yy
	int auxA, auxB, auxC;

	if(xx < 0){			// Se xx<0, entao Ghost esta a movimentar-se para
		*dir = LEFT;		//a ESQUERDA (ex: de 4->2 » 2 - 4 = -2)
		auxA = (int) floor(xorig);		//auxA->xorig arredondado para baixo (ex:8.64->8.00)
		auxB = (int) floor(xdest);		//auxB->igual, mas para o xdest
		auxC = (int) yorig;				//auxC->cast para inteiro do yorig
															/* ESTAMOS NO FANTASMA*/
		for(char orig_key = key ; auxB <= auxA ; auxA--, key = orig_key){
			x = rand() % 100;							// Gera-se um nº de 0 a 100
			if(x < 25){								// Se este for menos que 25, o Ghost não irá tras do Pacman	
				for(i = rand() % 4 ; rand_array[i] == key ; i = rand() % 4);	// Então, aleatoriamente, irá ser escolhida uma nova direção
			key = rand_array[i];							//diferente da recebida
			}
			if(key == 's' && _boardArray[auxC+1][auxA+1] != W && xorig >= auxA+1 && xdest <= auxA+1){	//Tentativa de mudar de direcção para baixo
				*dir = DOWN;		//Mudança de direcção do Ghost
				dest.y -= 0.001;
				dest.x = (float) (auxA+1 - 12.);	// '- 12.' -> conversão para valor real
				break;

			} else if(key == 'w' && _boardArray[auxC-1][auxA+1] != W && xorig >= auxA+1 && xdest <= auxA+1){	//Tentativa de mudar de direcção para cima
				*dir = UP;		//Mudança de direcção do Ghost
				dest.y += 0.001;
				dest.x = (float) (auxA+1 - 12.);
				break;

			} else if(_boardArray[auxC][auxA] == W){	// Caso contrário, se foi encontrada uma parede,	
				if(key == 'd' && _boardArray[auxC][auxA+2] != W){							//Tentativa de mudar de direcção para direita
					*dir = RIGHT;		//Mudança de direcção do Ghost
					dest.x = orig.x;
					break;
				}
				dest.x = (float) (auxA+1) - 12.;		//coord x destino do Ghost será a anterior
				break;
			}
		}
															/* ESTAMOS NO FANTASMA*/
	} else if (xx >0){		// Se xx<0, entao Ghost esta a movimentar-se para
		*dir = RIGHT;		//a DIREITA (ex: de -6->10 » 10 - (-6) = 16)
		auxA = (int) ceil(xorig);
		auxB = (int) ceil(xdest);
		auxC = (int) yorig;
		for(char orig_key = key ; auxB >= auxA ; auxA++, key = orig_key){
			x = rand() % 100;	//Igual ao anterior...
			if(x < 25){
				for(i = rand() % 4 ; rand_array[i] == key ; i = rand() % 4);
				key = rand_array[i];
			}
			if(key == 's' && _boardArray[auxC+1][auxA-1] != W && xorig <= auxA-1 && xdest >= auxA-1){	//Tentativa de mudar de direcção para baixo
				*dir = DOWN;		//Mudança de direcção do Ghost
				dest.y -= 0.001;
				dest.x = (float) (auxA-1 - 12.);	// '- 12.' -> conversão para valor real
				break;

			} else if(key == 'w' && _boardArray[auxC-1][auxA-1] != W && xorig <= auxA-1 && xdest >= auxA-1){	//Tentativa de mudar de direcção para cima
				*dir = UP;		//Mudança de direcção do Ghost
				dest.y += 0.001;
				dest.x = (float) (auxA-1 - 12.);
				break;

			} else if(_boardArray[auxC][auxA] == W){	// Caso contrário, se foi encontrada uma parede,
				if(key == 'a' && _boardArray[auxC][auxA-2] != W){							//Tentativa de mudar de direcção para esquerda
					*dir = LEFT;		//Mudança de direcção do Ghost
					dest.x = orig.x;
					break;
				}
				dest.x = (float) (auxA-1 - 12.);		//coord x destino do Ghost será a anterior
				break;
			}
		}
															/* ESTAMOS NO FANTASMA*/
	} else if(yy < 0){		// Se yy<0, entao Ghost esta a movimentar-se para
		*dir = DOWN;		//BAIXO (ex: de 4->-5 » -5 - 4 = -9)
		auxA = (int) ceil(yorig);
		auxB = (int) ceil(ydest);
		auxC = (int) xorig;

		for(char orig_key = key ; auxB >= auxA ; auxA++, key = orig_key){
			x = rand() % 100;	//Igual ao anterior...
			if(x < 25){
				for(i = rand() % 4 ; rand_array[i] == key ; i = rand() % 4);
				key = rand_array[i];
			}
			if(key == 'a' && _boardArray[auxA-1][auxC-1] != W && yorig <= auxA-1 && ydest >= auxA-1){		//Tentativa de mudar de direcção para esquerda
				*dir = LEFT;		//Mudança de direcção do Ghost
				dest.x -= 0.001;
				dest.y = (float) -((auxA-1) - 7.);	// '- 7.' -> conversão para valor real
				break;

			} else if(key == 'd' && _boardArray[auxA-1][auxC+1] != W && yorig <= auxA-1 && ydest >= auxA-1){	//Tentativa de mudar de direcção para direita
				*dir = RIGHT;		//Mudança de direcção do Ghost
				dest.x += 0.001;
				dest.y = (float) -((auxA-1) - 7.);
				break;

			} else if(_boardArray[auxA][auxC] == W){	// Caso contrário, se foi encontrada uma parede,
				if(key == 'w' && _boardArray[auxA-2][auxC] != W){						//Tentativa de mudar de direcção para cima
					*dir = UP;		//Mudança de direcção do Ghost
					dest.y = orig.y;
					break;
				}
				dest.y = (float) -((auxA-1) - 7.);		//coord y destino do Ghost será a anterior
				break;
			}
		}
											/* ESTAMOS NO FANTASMA*/
	} else if (yy > 0){		// Se xx<0, entao Ghost esta a movimentar-se para
		*dir = UP;		//CIMA (ex: de 5->7 » 7 - 5 = 2)
		auxA = (int) floor(yorig);
		auxB = (int) floor(ydest);
		auxC = (int) xorig;
		for(char orig_key = key ; auxB <= auxA ; auxA--, key = orig_key){
			x = rand() % 100;	//Igual ao anterior...
			if(x < 25){
				for(i = rand() % 4 ; rand_array[i] == key ; i = rand() % 4);
				key = rand_array[i];
			}
			if(key == 'a' && _boardArray[auxA+1][auxC-1] != W && yorig >= auxA+1 && ydest <= auxA+1){		//Tentativa de mudar de direcção para esquerda
				*dir = LEFT;		//Mudança de direcção do Ghost
				dest.x -= 0.001;
				dest.y = (float) -((auxA+1) - 7.);	// '- 7.' -> conversão para valor real
				break;

			} else if(key == 'd' && _boardArray[auxA+1][auxC+1] != W && yorig >= auxA+1 && ydest <= auxA+1){	//Tentativa de mudar de direcção para direita
				*dir = RIGHT;		//Mudança de direcção do Ghost
				dest.x += 0.001;
				dest.y = (float) -((auxA+1) - 7.);
				break;

			} else if(_boardArray[auxA][auxC] == W){	// Caso contrário, se foi encontrada uma parede,
				if(key == 's' && _boardArray[auxA+2][auxC] != W){						//Tentativa de mudar de direcção para baixo
					*dir = DOWN;		//Mudança de direcção do Ghost
					dest.y = orig.y;
					break;
				}
				dest.y = (float) -((auxA+1) - 7.);		//coord y destino do Ghost será a anterior
				break;
			}
		}
	}
	return dest;
}


bool Board::checkColision(position pos1, position pos2){
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	if(fabs(x) < 0.8 && fabs(y) < 0.8){
		if( (x*x + y*y) <1){
			return true;
		}	
	}
	return false;
}


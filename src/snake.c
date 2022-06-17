#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"

struct snake *Snake;
struct apple *Apple;
int dir[2] = {0, -1};

int main(){
	int game_over = 0;
	int T = 0;
	int score = 0, length = 0, digestion = 0, movimientos = 0; 
	char tecla = 0;
	srand(time(NULL));
	
	system("cls");
	imprimir_Escenario();
	crear_Serpiente();
	crear_Manzana();
	imprimir_Serpiente(Snake);
	imprimir_Manzana();
	//Bucle de juego:
	while(!game_over){;
		if(kbhit()){
			tecla = getch();
			//dir[0]=(tecla == DERECHA)-(tecla == IZQUIERDA);
			//dir[1]=(tecla == ABAJO)-(tecla == ARRIBA);
			switch(tecla){
				case ARRIBA:
					Snake->AP = LENGUA_UP;
					dir[0]=0;
					dir[1]=-1;
					break;
				case ABAJO:
					Snake->AP = LENGUA_DOWN;
					dir[0]=0;
					dir[1]=1;
					break;
				case DERECHA:
					Snake->AP = LENGUA_RIGHT;
					dir[0]=1;
					dir[1]=0;
					break;
				case IZQUIERDA:
					Snake->AP = LENGUA_LEFT;
					dir[0]=-1;
					dir[1]=0;
					break;
				default:
					break;
			}
		}		
		Sleep(FRAMERATE);
		T+=FRAMERATE;
		if(T>=SPEED){
			imprimir_Serpiente2(Snake);
			imprimir_Manzana();
			gotoxy(XBOUND, YBOUND-1);
			printf("SCORE: %d", score);
			mover_Serpiente(Snake->X+dir[0],Snake->Y+dir[1], Snake);
			game_over = collision_Tablero() + collision_Self(Snake->next) + (tecla == ESC);
			if(!digestion){
				if(collision_Apple(Snake)){
					score += Apple->PUNTOS;
					digestion = 1;
					movimientos += length+1;
				}
			}
			else{
				if(length < score){
					if(!movimientos){
						crecer_Serpiente(Apple->X, Apple->Y, Snake);
						++length;
					}
					else{
						--movimientos;
					}
				}
				else{
					reset_Apple();
					digestion = 0;
				}
			}
			T = 0;
		}
	}
return 0;
}
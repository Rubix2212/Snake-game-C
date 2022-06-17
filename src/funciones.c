#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "snake.h"

extern struct snake *Snake;
extern struct apple *Apple;
extern int dir[2];
int cola_Anterior[2];

//FUNCIONES DE IMPRESIÓN:
void gotoxy(int x, int y){
	printf("%c[%d;%dH", ESC, y, x);
}

void imprimir_Escenario(){
	int i, j;
	char c;
	gotoxy(XBOUND, YBOUND);
	for(j=0; j<NY+2; ++j){
		for(i=0; i<NX+2; ++i){
			//Columnas:
			if(i==0 || i==NX+1){
				switch(j){
					case 0: c = ESQ_SI*(i==0) + ESQ_SD*(i==NX+1);
					break;
					case NY+1: c = ESQ_II*(i==0) + ESQ_ID*(i==NX+1);
					break;
					default: c = BAR_V;
					break;
				}
			}
			//Entre medias:
			else{
				if(j==0 || j==NY+1){
					c = BAR_H;
				}
				else{
					c = ' ';
				}
			}
			printf("%c",c);
			if(i==NX+1){
				gotoxy(XBOUND, YBOUND+j+1);
			}
		}
	}
}

void imprimir_Serpiente(struct snake *body){
	printf("%c[1;%dm", ESC, body->COLOR);
	gotoxy(body->X, body->Y);
	printf("%c", body->AP);
	printf("%c[0m", ESC);
	if(body->next != NULL){
		imprimir_Serpiente(body->next);
	}
	else{
		gotoxy(cola_Anterior[0], cola_Anterior[1]);
		printf(" ");
	}
}

void imprimir_Serpiente2(struct snake *body){
	if(body->next != NULL){
		if(body == Snake || body == Snake->next){
			printf("%c[1;%dm", ESC, body->COLOR);
			gotoxy(body->X, body->Y);
			printf("%c", body->AP);
			printf("%c[0m", ESC);			
		}
		imprimir_Serpiente(body->next);
	}
	else{
		printf("%c[1;%dm", ESC, body->COLOR);
		gotoxy(body->X, body->Y);
		printf("%c", body->AP);
		printf("%c[0m", ESC);
		gotoxy(cola_Anterior[0], cola_Anterior[1]);
		printf(" ");
	}
}

void imprimir_Manzana(){
	printf("%c[1;%dm", ESC, Apple->COLOR);
	gotoxy(Apple->X, Apple->Y);
	printf("%c", Apple->AP);
	printf("%c[0m", ESC);
}

//GESTION DE SERPIENTE:
void crecer_Serpiente(int x, int y, struct snake *body){
	if(body->next == NULL){
		body->next = (struct snake*)malloc(sizeof(struct snake));
		body->next->X = x;
		body->next->Y = y;
		body->next->AP = CUERPO;
		body->next->COLOR = 32;
		body->next->next = NULL;
	}
	else{
		crecer_Serpiente(x, y, body->next);
	}
}

void crear_Serpiente(){	
	Snake = (struct snake*)malloc(sizeof(struct snake));
	Snake->X = XBOUND + NX/2;
	Snake->Y = YBOUND + NY/2;
	Snake->AP = LENGUA_UP;
	Snake->COLOR = 31;
	Snake->next = NULL;
	crecer_Serpiente(XBOUND + NX/2, YBOUND + NY/2 + 1, Snake);
}

void mover_Serpiente(int x, int y, struct snake *body){
	if(body->next != NULL){
		mover_Serpiente(body->X, body->Y, body->next);
	}
	else{
		cola_Anterior[0] = body->X;
		cola_Anterior[1] = body->Y;
	}
	body->X = x;
	body->Y = y;
}

int collision_Tablero(){
	int B = 0;
	B = (Snake->X <= XBOUND)+(Snake->X > (XBOUND + NX));
	B += (Snake->Y <= YBOUND)+(Snake->Y >(YBOUND + NY));
	return B;
}

int collision_Self(struct snake *body){
	if((Snake->X == body->X) && (Snake->Y == body->Y)){
		return 1;
	}
	else{
		if(body->next != NULL){
			return collision_Self(body->next);
		}
		else{
			return 0;
		}
	}
}

//GESTION DE MANZANA
int collision_Apple(struct snake *body){
	static int colision;
	if(body == Snake){
		colision = 0;
	}
	colision += (body->X == Apple->X)&&(body->Y == Apple->Y);
	if(!colision){
		if(body->next != NULL){
			collision_Apple(body->next);
		}
	}
	return colision;
}

void reset_Apple(){
	Apple->X = XBOUND + rand()%NX + 1;
	Apple->Y = YBOUND + rand()%NY + 1;
	if(collision_Apple(Snake)){
		reset_Apple();
	}
	Apple->PUNTOS = DEF_APPLE + (GOLD_APPLE-DEF_APPLE)*(PROB_GOLD >= rand()%101);
	Apple->COLOR = 31*(Apple->PUNTOS == DEF_APPLE)+33*(Apple->PUNTOS == GOLD_APPLE);
}

void crear_Manzana(){
	Apple = (struct apple*)malloc(sizeof(struct apple));
	Apple->AP = CUERPO;
	reset_Apple();	
}
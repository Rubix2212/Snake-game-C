// snake.h
#define FRAMERATE 32
#define SPEED 150

//Teclas
#define ESC	27
#define ARRIBA	72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

//Caracteres escenario:
#define ESQ_SI 201
#define ESQ_SD 187
#define ESQ_II 200
#define ESQ_ID 188
#define BAR_H	205
#define BAR_V	186

//Dimensiones escenario:
#define NX 50
#define NY 50
#define XBOUND 5
#define YBOUND 5

//Caracteres serpiente:
#define LENGUA_UP 118
#define LENGUA_DOWN 94
#define LENGUA_LEFT 62
#define LENGUA_RIGHT 60
#define CUERPO 219

//Puntos:
#define GOLD_APPLE 5
#define DEF_APPLE	1
#define PROB_GOLD	25

//ESTRUCTURAS
struct snake{
	int X, Y, AP, COLOR;
	struct snake *next;
};

struct apple{ 
	int X, Y, AP, COLOR, PUNTOS;
};

//FUNCIONES DE IMPRESION
void gotoxy(int x, int y);
void imprimir_Escenario();
void imprimir_Serpiente(struct snake *body);
void imprimir_Serpiente2(struct snake *body);
void imprimir_Manzana();

//FUNCIONES SERPIENTE
void crecer_Serpiente(int x, int y, struct snake *body);
void crear_Serpiente();
void mover_Serpiente(int x, int y, struct snake *body);
int collision_Tablero();
int collision_Self();

//FUNCIONES MANZANA
void crear_Manzana();
int collision_Apple(struct snake *body);
void reset_Apple();
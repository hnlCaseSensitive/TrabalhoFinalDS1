#include "combate.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY,COMBATE, ITEM_ESPECIAL, ENDING, ESCOLHEDEST} GameScreen;
typedef enum MenuSelection {PLAY = 0, EXIT} MenuSelection;
typedef enum ItemSelection {LUVA, LASER, SUCO, FACA} ItemSelection;
typedef enum ArmaSelection {ARMA1=0, ARMA2, ARMA3, ARMA4} ArmaSelection;

// ================================ FUNCOES =========================
void Draw_Window();
void Update_Window();

/* ===================================
 *              VARIAVEIS GLOBAIS
 * ===================================*/
GameScreen currentScreen = TITLE;
MenuSelection menuSelection = PLAY;
ItemSelection itemSelection = LUVA;
ArmaSelection armaSelection = DESARMADO;

const int screenWidth = 850;
const int screenHeight = 450;
int framesCounter = 0;          // Useful to count frames

//Jogo
Player *player;
Inimigo *foe;
GrafoLA* Mapa;
NoGrafo* curr;
ArestaGrafo* curr_dest;
Status *status;
// Flags
int jogadorExiste = 0;
int menuArmas = -1;
int emCombate = -1;


// ================= CORES =====================
Color corRetanguloPlay = RED;
Color corRetanguloExit = BLACK;

Color corRetanguloLuva = BLUE;
Color corRetanguloLaser = BLUE;
Color corRetanguloSuco = BLUE;
Color corRetanguloFaca = BLUE;

Color corRetanguloArma1 = GREEN;
Color corRetanguloArma2 = DARKGREEN;
Color corRetanguloArma3 = DARKGREEN;
Color corRetanguloArma4 = GREEN;

const Color corBackgroundCombate = WHITE;

Color corOutputJ = DARKBLUE;
Color corOutputI = DARKBLUE;

Color destaque = GRAY;
//===============================================//


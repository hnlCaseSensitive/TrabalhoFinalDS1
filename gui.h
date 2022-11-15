#ifndef _GUI_H_
#define _GUI_H_

#include "combate.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY,COMBATE, ITEM_ESPECIAL, ENDING, ESCOLHEDEST} GameScreen;
typedef enum ArmaSelection {ARMA1=0, ARMA2, ARMA3, ARMA4} ArmaSelection;


static const int screenWidth = 800;
static const int screenHeight = 450;
GameScreen currentScreen = 0;

Color ButtonColor = WHITE;
Color ButtonHighlight = SKYBLUE;
Color ButtonPressColor = DARKBLUE;

int ButtonFontSize = 40;
int ButtonBorder = 10;

bool Button_is_selected(int y, const char* text);
bool Rectangle_is_hovered(Rectangle rectangle);
void DrawCenteredText(int y, const char* text, int fontSize, Color color);

Texture2D title;
Texture2D choose;
Texture2D over;
Texture2D heal;
Texture2D sucess;
Texture2D start;
Texture2D combat;

void    Screen_change_screens(int screen);
void    Screen_title_init();
void    Screen_title_update();
void    Screen_title_draw();
void    Screen_title_unload();
int     Screen_title_end();
void    Screen_options_init();
void    Screen_options_update();
void    Screen_options_draw();
void    Screen_options_unload();
int     Screen_options_end();
void    Screen_gameplay_init();
void    Screen_gameplay_update();
void    Screen_gameplay_draw();
void    Screen_gameplay_unload();
int     Screen_gameplay_end();
void    Screen_escolhedest_init();
void    Screen_escolhedest_update();
void    Screen_escolhedest_draw();
void    Screen_escolhedest_unload();
int     Screen_escolhedest_end();
void    Screen_combate_init();
void    Screen_combate_update();
void    Screen_combate_draw();
void    Screen_combate_unload();
int     Screen_combate_end();
void    Screen_ending_init();
void    Screen_ending_update();
void    Screen_ending_draw();
void    Screen_ending_unload();
int     Screen_ending_end();


/* ===================================
 *              VARIAVEIS GLOBAIS
 * ===================================*/
int framesCounter = 0;          // Useful to count frames

//Jogo
jogador *player;
Inimigo *foe;
GrafoLA* Mapa;
NoGrafo* curr;
ArestaGrafo* curr_dest;
// Flags
int jogadorExiste = 0;
int menuArmas = -1;
int emCombate = -1;


// ================= CORES =====================



Color corRetanguloArma1 = GREEN;
Color corRetanguloArma2 = DARKGREEN;
Color corRetanguloArma3 = DARKGREEN;
Color corRetanguloArma4 = GREEN;

const Color corBackgroundCombate = WHITE;

Color corOutputJ = DARKBLUE;
Color corOutputI = DARKBLUE;

Color destaque = GRAY;
//===============================================//

#endif

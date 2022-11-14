#ifndef _COMBATE_H_
#define _COMBATE_H_

#include "gameLogic.h"

typedef enum{
    HEAL = 0,
    DMG = 1,
    ITEM = 2,
    SPECIAL
}tipo;

typedef struct {
    char nome[30];
    float valor, cost;
    tipo self_type;
}skill;

typedef struct {
    float hp, stm;
    int lvl, xp;
    skill tecs[5];
    skill** items;
} jogador;

typedef enum {
    CROOK = 0,
    MAFIA_BOSS = 1,
    KING = 2,
    CEO_OF_EVIL
} enemy_type;

typdef struct {
    float hp, stm;
    int lvl;
    skill* tecs;
    enemy_type self_type;
}Inimigo;

void combate(Player* player, Inimigo inimigo);

void escolheArma(Player *player, int arma, Status *status);

void ataque(Player*, Inimigo*);

void turnoJogador(Player *player, Inimigo *inimigo, Status *status);

void turnoInimigo(Player *player, Inimigo *inimigo, Status *status);

void output(Status *status, char *text);

void initArma(Player *);

void selecionaItem(int input, Player*);

void criaJogador(Player*, Status*);
#endif


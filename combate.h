#ifndef _COMBATE_H_
#define _COMBATE_H_

#include "gameLogic.h"

typedef enum{
    HEAL = 0,
    DMG = 1,
    SPECIAL
}tipo;

typedef struct {
    char nome[30];
    float valor;
    tipo self_type;
}skill;

typedef struct {
    float hp, stm;
    int lvl, xp;
    skill tecs[5];
    skill** items;
} jogador;

Inimigo *sorteiaInimigo();

void combate(Player* player, Inimigo *inimigo);

void escolheArma(Player *player, int arma, Status *status);

void ataque(Player*, Inimigo*);

void turnoJogador(Player *player, Inimigo *inimigo, Status *status);

void turnoInimigo(Player *player, Inimigo *inimigo, Status *status);

void output(Status *status, char *text);

void initArma(Player *);

void selecionaItem(int input, Player*);

void criaJogador(Player*, Status*);
#endif


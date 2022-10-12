#include "gameLogic.h"
#include "combate.h"
#include <string.h>



void criaJogador(Player *player, Status *status)
{
    player->vidaAtual = 100;
    player->vidaMaxima = 100;
    player->armaAtual.tipoDano = DESARMADO;
    status->armaEquipada = "Desarmado"; 
}

void selecionaItem(int input, Player *player)
{
    
    switch (input){

    case 0:
        strcpy (player->itemEspecial, "LUVAS DE BOXE");
        break;

    case 1:
        strcpy (player->itemEspecial, "MIRA A LASER");
        break;

    case 2:
        strcpy (player->itemEspecial, "SUQUINHO");
        break;

    case 3:
        strcpy (player->itemEspecial, "FACA");
        break;

    case 5:
        strcpy (player->itemEspecial, "DELETE KEY");
        break;

    }
    printf("player->itemespecial: %s\n", player->itemEspecial);
}

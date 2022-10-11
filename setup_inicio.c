#include "setup_inicio.h"
#include <string.h>


void inicioJogoCombate (Player* player){

    // Inicializando hp
    player->vidaAtual = 100;
    player->vidaMaxima = 100;

    // Declarando as armas do jogador
    arma acido = {.dano = 10, .desc = "Arma de acido", .tipoDano = ACIDO};
    arma eletrico = {.dano = 10, .desc = "Arma eletrica", .tipoDano = ELETRICO};
    arma perfuracao = {.dano = 10, .desc = "Arma de perfuracao", .tipoDano = PERFURACAO};
    arma punhos = {.dano = 10, .desc = "Ataque desarmado", .tipoDano = DESARMADO};

    // Realmente dando as armas usando o vetor
    player->arma[0] = perfuracao;
    player->arma[1] = eletrico;
    player->arma[2] = acido;
    player->arma[3] = punhos;
}

void criaJogador(Player *player)
{
    // Inicializando hp
    player->vidaAtual = 100;
    player->vidaMaxima = 100;

    // Declarando as armas do jogador
    arma acido = {.dano = 10, .desc = "Arma de acido", .tipoDano = ACIDO};
    arma eletrico = {.dano = 10, .desc = "Arma eletrica", .tipoDano = ELETRICO};
    arma perfuracao = {.dano = 10, .desc = "Arma de perfuracao", .tipoDano = PERFURACAO};
    arma punhos = {.dano = 10, .desc = "Ataque desarmado", .tipoDano = DESARMADO};

    // Realmente dando as armas usando o vetor
    player->arma[0] = perfuracao;
    player->arma[1] = eletrico;
    player->arma[2] = acido;
    player->arma[3] = punhos;
    
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

void statusPlayer(Player player){
    // Imprime vida do jogador
    printf ("\nVida max: %d\n", player.vidaMaxima);
    printf ("Vida atual: %d\n", player.vidaAtual);
    // Lista de suas armas
    printf ("\nArmas:\n");

    int i = 0;

    for (i = 0; i < 4; i++){

        printf ("%d: Dano %d, Tipo %d, Desc: %s\n", i+1, player.arma[i].dano, player.arma[i].tipoDano, player.arma[i].desc);

    }
    // E o item especial
    printf ("\nItem especial: %s\n", player.itemEspecial);

}

void statusInimigo(Inimigo inimigo){
    // Imprime o status do inimigo, vida, dano, tipo e nome
    printf ("\nVida: %d\n", inimigo.vida);
    printf ("Dano: %d\n", inimigo.dano);
    printf ("Tipo: %d\n", inimigo.tipo);
    printf ("Nome: %s\n", inimigo.nome);

}

#include "bot.h"
#include <stdlib.h>
#include <time.h>

void turno_bot(Jogo *j){
    if (j->aguardando_cor) {
        escolher_cor(j, rand() % 4);
        return;
    }
    int qtd = mao_quantia(j->mao[j->jogador]);
    for(int i=0; i<qtd; i++){
        Carta c = mao_ver_carta(j->mao[j->jogador], i);
        if(pode_jogar_carta(c,j->carta_atual,j->cor_jogo)){
            jogar_carta(j, i);
            return;
        }
    }
    comprar_carta(j);
}
#include "uno.h"
#include <stdio.h>
#include "bot.h"

int main(){
    Jogo j = inicializar_jogo();
    int vencedor = 0 ;
    int rodada =0;
    const char *nomes_cores[] = {"VERMELHO", "AZUL", "VERDE", "AMARELO", "PRETO"};
    const char *nomes_valores[] = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "PULAR", "INVERTER", "+2", "CORINGA", "+4"
    };


    while(vencedor == 0){

        if(j.jogador == 0){
            // if(j.aguardando_cor){
            //     printf("Escolha a nova cor (0 VERMELHO, 1 AZUL, 2 VERDE, 3 AMARELO):");
            //     int cor;
            //     scanf("%d", &cor);
            //     escolher_cor(&j, (Cor)cor);    
            // }else{
            //     printf("\n ===MESA===\n");
            //     printf("Cor ativa: %s | Carta no topo: %s %s\n", nomes_cores[j.cor_jogo], nomes_cores[j.carta_atual.cor], nomes_valores[j.carta_atual.valor]);

            //     printf("\n Sua mao:\n");
            //     int qtd = mao_quantia(j.mao[0]);
            //     for(int i=0; i<qtd; i++){
            //         Carta c=mao_ver_carta(j.mao[0],i);
            //         printf("[%d] %s %s\n", i, nomes_cores[c.cor],nomes_valores[c.valor]);
            //     }

            //     printf("Escolha qual carta jogar pelo indice (ou -1 para comprar)");
            //     int n;
            //     scanf("%d", &n);
            //     if(n==-1){
            //         comprar_carta(&j);
            //     }
            //     else{
            //         jogar_carta(&j, n);
            //     }
            // }
            turno_bot(&j);
        }else{
            turno_bot(&j);
        }
        for (int p = 0; p < 4; p++) {
            if (mao_quantia(j.mao[p]) == 0) {
            printf("\nJogador %d venceu a partida!\n", p);
            vencedor = 1;
            break;
            }
        }   
    }
}
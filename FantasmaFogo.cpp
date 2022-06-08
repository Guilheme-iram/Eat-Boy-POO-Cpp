#include "Fantasma.hpp"
#include "FantasmaFogo.hpp"
#include <time.h>

FantasmaFogo::FantasmaFogo(char simb, int pos_x, int pos_y, Mapa_jogo *labirinto) : 
    Fantasma(simb, pos_x, pos_y, labirinto) {  
}

void FantasmaFogo::move(char comando){
    for (int i = 0; i < 2; i++){

        if(estou_vivo()) {
        switch (comando) {
        char proxima_posicao;
        case 'w':
            proxima_posicao = mapa->matriz[posicao_x - 1][posicao_y];

            if (proxima_posicao == '-' || proxima_posicao == '|' || proxima_posicao == '#'){
                break;
            } 
            if(tem_heroi_poderoso(proxima_posicao)){
                break;
            } 
            
            mapa->matriz[posicao_x - 1][posicao_y] = simbolo;
            mapa->matriz[posicao_x][posicao_y] = '.';
            posicao_x = posicao_x - 1;
            posicao_y = posicao_y;
            break;

        case 'a':
            proxima_posicao = mapa->matriz[posicao_x][posicao_y - 1];

            if (mapa->matriz[posicao_x][posicao_y - 1] == '-' || mapa->matriz[posicao_x][posicao_y - 1] == '|' || proxima_posicao == '#'){
                break;
            } 
            if(tem_heroi_poderoso(proxima_posicao)){
                break;
            }
            mapa->matriz[posicao_x][posicao_y - 1] = simbolo;
            mapa->matriz[posicao_x][posicao_y] = '.';
            posicao_x = posicao_x;
            posicao_y = posicao_y - 1;
            break;

        case 's':
            proxima_posicao = mapa->matriz[posicao_x + 1][posicao_y];

            if (proxima_posicao == '-' || proxima_posicao == '|' || proxima_posicao == '#'){
                break;
            } 
            if(tem_heroi_poderoso(proxima_posicao)){
                break;
            }
            mapa->matriz[posicao_x + 1][posicao_y] = simbolo;
            mapa->matriz[posicao_x][posicao_y] = '.';
            posicao_x = posicao_x + 1;
            posicao_y = posicao_y;
            break;

        case 'd':
            proxima_posicao = mapa->matriz[posicao_x][posicao_y + 1];

            if (proxima_posicao == '-' || proxima_posicao == '|' || proxima_posicao == '#'){
                break;
            } 
            if(tem_heroi_poderoso(proxima_posicao)){
                break;
            } 
            mapa->matriz[posicao_x][posicao_y + 1] = simbolo;
            mapa->matriz[posicao_x][posicao_y] = '.';
            posicao_x = posicao_x;
            posicao_y = posicao_y + 1;
            break;
        
        default: break;
        }   
    }

    }
    
}
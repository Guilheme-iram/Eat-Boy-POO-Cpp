#include "Fantasma.hpp"
#include "Personagem.hpp"
#include <time.h>

Fantasma::Fantasma(char simb, int pos_x, int pos_y, Mapa_jogo *labirinto) : 
    Personagem(simb, pos_x, pos_y, labirinto) {  
}

void Fantasma::IA() {
    if(estou_vivo() && !existe_heroi_congelante()) {

        int heroi_perto = 0;

        int i, j, x_heroi, y_heroi, dif_x, dif_y;

        for (i = 0; i < mapa->nLinha; i++){
            for (j = 0; j < mapa->nColuna; j++){
                if (mapa->matriz[i][j] == 'c'){
                    x_heroi = i;
                    y_heroi = j;
                    break;
                }
            }
        }

        dif_x = abs(x_heroi - posicao_x);
        dif_y = abs(y_heroi - posicao_y);

        if ((dif_x + dif_y) <= 3)
            heroi_perto = 1;

        if (heroi_perto){

            dif_x = x_heroi - posicao_x;
            dif_y = y_heroi - posicao_y;

            if (dif_x < 0){
                move('w');
                }

            else if (dif_x > 0){
                move('s');
                }

            else if (dif_y < 0){
                move('a');
                }
            
            else if (dif_y > 0){
                move('d');
                }

            else{
                return;
            }
            return;

        }else{

            srand((unsigned) time(0));

            int maior = 4;
            int menor = 1;
                
            int direcao = rand() % ( maior - menor + 1 ) + menor;

            switch (direcao) {
                case 1:
                    move('w'); 
                    break;
                case 2:
                    move('d'); 
                    break;
                case 3:
                    move('s'); 
                    break;
                case 4:
                    move('a'); 
                    break; 
                default:
                    break;
                }      
        }

        return;
    }
}

void Fantasma::move(char comando) {
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

int Fantasma::tem_heroi_poderoso(char objeto) {
    if(objeto == '@'){                              // Na colis�o com o Heroi apos comer a pilula
        mapa->matriz[posicao_x][posicao_y] = '.';   // Ocorre a substitui��o do caracter do fantasma para um .
        return 1;
    }
    return 0; 
}  

bool Fantasma::existe_heroi_congelante() {
    int contador = 0;
    
    int l = mapa->matriz.size(), c = mapa->matriz[0].size();
        for (int i = 0; i < l; i++){
            for (int j = 0; j < c; j++){
                if (mapa->matriz[i][j] == '*') { //Analisa a matriz em busca de um heroi com o poder congelante
                    contador += 1;
                }
            }
        }
    return (contador != 0);
}
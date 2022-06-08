#include "Mapa_jogo.hpp"
#include "Heroi.hpp"
#include "Fantasma.hpp"
#include "Pilula.hpp"
#include "Personagem.hpp"
#include <iostream>
#include <conio.h>
#include <stdexcept>
#include "FantasmaFogo.hpp"

using namespace std;

void movimentoDuplo(Fantasma fantasma){
    fantasma.IA();
}

int main(){

    Mapa_jogo labirinto = Mapa_jogo();

    try{
        labirinto.aloca_mapa("mapas\\mapa_3.txt");
    } catch(ArquivoException ex) {
        ex.printMsg();
        return 1;
    }
    
    Heroi eatboy = Heroi('c', 7, 13, &labirinto);
    Pilula pilula = Pilula('o', 5, 22, &labirinto);
    Pilula pilula_congelante = Pilula('O', 5, 5, &labirinto);
    Fantasma fantasma_green  = Fantasma('#', 8, 8, &labirinto);
    Fantasma fantasma_red = Fantasma('#', 8, 5, &labirinto);
    Fantasma fantasma_yellow = Fantasma('#', 9, 25, &labirinto);
    FantasmaFogo fantasma_fire = FantasmaFogo('F', 1, 1, &labirinto);

    labirinto.imprime_mapa();
    system("color 06");
    
    while(eatboy.estou_vivo()) {

        system("cls");
        labirinto.imprime_mapa();
        if (labirinto.verifica_fim_de_jogo())
            break;

        eatboy.move(_getch());
        if(!eatboy.estou_vivo()) {
            labirinto.imprime_mapa();
            break;
        }
        fantasma_green.IA();
        fantasma_red.IA();
        fantasma_yellow.IA();
        fantasma_fire.IA();
        
    }

    if(eatboy.estou_vivo()){
        system("color 02");
        labirinto.imprime_vitoria();
        cout << "\nVOCE VENCEU! MEUS PARABENS! :D" << endl;}
        
    else{
        system("color 01");
        labirinto.imprime_derrota();
        cout << "\nVOCE PERDEU! :( TENTE DE NOVO!" << endl;}
        
    return 0;

}


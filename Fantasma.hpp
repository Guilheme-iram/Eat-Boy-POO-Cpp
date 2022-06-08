#pragma once

#include "Personagem.hpp"

class Fantasma: public Personagem {
    public:
        
        Fantasma(char simb,
        int pos_x,
        int pos_y,
        Mapa_jogo *labirinto);
        virtual void move(char direcao) override;
        void IA();
        int tem_heroi_poderoso(char objeto);
        bool existe_heroi_congelante();

};



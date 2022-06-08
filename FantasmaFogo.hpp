#pragma once

#include "Fantasma.hpp"

class FantasmaFogo: public Fantasma {
    public:
        
        FantasmaFogo(char simb,
        int pos_x,
        int pos_y,
        Mapa_jogo *labirinto);

        //void move(char direcao) override;

};
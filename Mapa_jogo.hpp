#pragma once

#include <vector>
#include <string>
#include <iostream>

class Mapa_jogo {
public:
    std::vector<std::vector<char>> matriz;
    int nLinha;
    int nColuna;

    Mapa_jogo();
    void aloca_mapa(std::string endereco);
    void aparece_pilula(bool rp, bool bp);
    void imprime_mapa();
    bool verifica_fim_de_jogo();
    void fim_de_jogo();
    void imprime_vitoria();
    void imprime_derrota();

};


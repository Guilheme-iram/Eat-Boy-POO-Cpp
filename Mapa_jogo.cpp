#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Mapa_jogo.hpp"

//#include "eat_boy.hpp"

Mapa_jogo::Mapa_jogo() {
}

void Mapa_jogo::aloca_mapa(std::string endereco){

    std::string linha;
    std::ifstream mapa(endereco);
    std::vector<char> aux;
    mapa >> this->nLinha;
    mapa >> this->nColuna;

    for (int i = 0; i < this->nLinha; i++){
        this->matriz.push_back(aux);
    }

    for (int i = 0; i < this->nLinha; i++){

    mapa >> linha;

    for (char c: linha){
        this->matriz[i].push_back(c);
        }
    }
}

char desenhoparede[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char desenhofantasma[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char desenhoheroi[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char desenhopilula[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char desenhopilula_congelante[4][7] = {
	{"      "},
	{" .+.  "},
	{" '+'  "},
	{"      "}
};

char desenhovazio[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void imprimeparte(char desenho[4][7], int parte) {
	if(desenho == desenhoparede) {
		printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219); //219
	} 
	else {
		printf("%s", desenho[parte]);
	}
}

void Mapa_jogo::imprime_mapa(){
//void imprime_mapa(){

    for(int i = 0; i < this->nLinha; i++) {

		for(int parte = 0; parte < 4; parte++) {
			for(int j = 0; j < this->nColuna; j++) {

				switch(this->matriz[i][j]){
					case '#':
						imprimeparte(desenhofantasma, parte);
						break;
					case 'c':
					case '*':
					case '@':
						imprimeparte(desenhoheroi, parte);
						break;
					case 'o':
						imprimeparte(desenhopilula, parte);
						break;
					case 'O':
						imprimeparte(desenhopilula_congelante, parte);
						break;
					case '-':
					case '|':
						imprimeparte(desenhoparede, parte);
						break;
					case '.':
						imprimeparte(desenhovazio, parte);
						break;
				}
				
			}
			printf("\n");
		}

	}

}

std::vector<std::vector<char>> Mapa_jogo::getMatriz(){
    return this->matriz;
}

void Mapa_jogo::imprime_vitoria(){

	char vitoria[7][35] = {
	{"      (_)    | |                  "},
	{"__   ___  ___| |_ ___  _ __ _   _ "},
	{"\\ \\ / / |/ __| __/ _ \\| '__| | | |"},
	{" \\ V /| | (__| || (_) | |  | |_| |"},
	{"  \\_/ |_|\\___|\\__\\___/|_|   \\__, |"},
	{"                             __/ |"},
	{"                            |___/"}
	};
	std::cout << std:: endl;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 35; j++){
			std::cout << vitoria[i][j];
		}
		std::cout << std::endl;
	}

};

void Mapa_jogo::imprime_derrota(){

	char derrota[7][40] = {
		
		{"( )                    ( )"},
		{"| |      _    ___   __ | |"},
		{"| |  _ / _ \\/  __)/ __ \\ |"},
		{"| |_( ) (_) )__  \\  ___/_)"},
		{"(____/ \\___/(____/\\____)  "},
		{"						 (_)"}

	};

	std::cout << std:: endl;
	for (int i = 0; i < 7; i++){
		for (int j = 0; derrota[i][j] != '\0'; j++){
			std::cout << derrota[i][j];
		}
		std::cout << std::endl;
	}

};


bool Mapa_jogo::verifica_fim_de_jogo(){
	
	int cont_fantasma = 0;
	int cont_heroi = 0;
	
	for (int i = 0; i < this->nLinha; i++){
		for (int j = 0; j < this->nColuna; j++){
			if (this->matriz[i][j] == '@' || this->matriz[i][j] == 'c' || this->matriz[i][j] == '*')
				cont_heroi++;
			if (this->matriz[i][j] == '#')
				cont_fantasma++;
		}
	}

	if (!cont_heroi){
		this->imprime_derrota();
		return true;
	}
		
	if (!cont_fantasma){
		this->imprime_vitoria();
		return true;
	}
		
	return false;
}

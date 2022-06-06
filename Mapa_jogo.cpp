#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
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

void Mapa_jogo::aparece_pilula(bool rp, bool bp){
	
	if (rp && bp)
		return;
	
	if (!rp && !bp){

		unsigned seed = time(0);

    	srand(seed);

		int prob = rand() % 101;
		
		if (prob >= 80){
			if (!rp){
				while (1){
					int random_x = rand() % nLinha - 1;
					int random_y = rand() % nColuna - 1;
					char prox_pos = matriz[random_x][random_y];
					bool condicao = prox_pos == '.';

					if (condicao){
						matriz[random_x][random_y] = 'o';
						break;
					} 
					
				}
			}
			
			if (!bp){
				while (1){
					int random_x = rand() % nLinha - 1;
					int random_y = rand() % nColuna - 1;
					char prox_pos = matriz[random_x][random_y];
					bool condicao = prox_pos == '.';
					
					if (condicao){
						matriz[random_x][random_y] = 'O';
						break;
					} 
					
				}
			}

			return;
		} 
	
	}

	// if (!rp){
	// 	std::cout << "SEM PILULA CONGELANTE" << std::endl; 
	// }
	
	// if (!bp){
	// 	std::cout << "SEM PILULA CONGELANTE" << std::endl; 
	// }

	return;

	 
}
void Mapa_jogo::imprime_mapa(){

	bool redpill = false;
	bool bluepill = false;

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
						redpill = true;
						imprimeparte(desenhopilula, parte);
						break;
					case 'O':
						bluepill = true;
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

	aparece_pilula(redpill, bluepill);

}


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
		return true;
	}
		
	if (!cont_fantasma){
		return true;
	}
		
	return false;
}

std::string center(std::string str, int espacos) {
   int n_espacos = (int)((espacos - str.length())/2);
   return std::string(n_espacos, ' ') + str + std::string(n_espacos + (str.length() > n_espacos * 2 ? 1 : 0), ' ');
}

void Mapa_jogo::imprime_vitoria() {
	int espacos = this->nColuna * 6;
	int linhas_vazias = ((this->nLinha * 4) - 17) / 2;
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < this->nColuna; j++) {
			imprimeparte(desenhoparede, i);
		}
		printf("\n");
	}

	for (int i = 0; i < linhas_vazias; i++){
		imprimeparte(desenhoparede, 0); std::cout << center("                                                            ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	} 

	imprimeparte(desenhoparede, 0); std::cout << center(" __  __              __                           __      ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
    imprimeparte(desenhoparede, 0); std::cout << center("/\\ \\/\\ \\  __        /\\ \\__                       /\\ \\     ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("\\ \\ \\ \\ \\/\\_\\    ___\\ \\ ,_\\   ___   _ __   __  __\\ \\ \\    ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center(" \\ \\ \\ \\ \\/\\ \\  /'___\\ \\ \\/  / __`\\/\\`'__\\/\\ \\/\\ \\\\ \\ \\   ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("  \\ \\ \\_/ \\ \\ \\/\\ \\__/\\ \\ \\_/\\ \\L\\ \\ \\ \\/ \\ \\ \\_\\ \\\\ \\_\\  ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("   \\ `\\___/\\ \\_\\ \\____\\\\ \\__\\ \\____/\\ \\_\\  \\/`____ \\\\/\\_\\ ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("    `\\/__/  \\/_/\\/____/ \\/__/\\/___/  \\/_/   `/___/> \\\\/_/ ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("                                               /\\___/     ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("                                               \\/__/      ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
    
	for (int i = 0; i < linhas_vazias; i++){
		imprimeparte(desenhoparede, 0); std::cout << center("                                                            ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	}
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < this->nColuna; j++) {
			imprimeparte(desenhoparede, i);
		}
		printf("\n");
	}
}

void Mapa_jogo::imprime_derrota() {
	int espacos = this->nColuna * 6;
	int linhas_vazias = ((this->nLinha * 4) - 17) / 2;
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < this->nColuna; j++) {
			imprimeparte(desenhoparede, i);
		}
		printf("\n");
	}

	for (int i = 0; i < linhas_vazias; i++){
		imprimeparte(desenhoparede, 0); std::cout << center("                                                              ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	} 

	imprimeparte(desenhoparede, 0); std::cout << center(" __    __                   ___                           __      ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
    imprimeparte(desenhoparede, 0); std::cout << center("/\\ \\  /\\ \\                 /\\_ \\                         /\\ \\     ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("\\ `\\`\\\\/'/ ___   __  __    \\//\\ \\     ___     ____     __\\ \\ \\    ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center(" `\\ `\\ /' / __`\\/\\ \\/\\ \\     \\ \\ \\   / __`\\  /',__\\  /'__`\\ \\ \\   ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("   `\\ \\ \\/\\ \\L\\ \\ \\ \\_\\ \\     \\_\\ \\_/\\ \\L\\ \\/\\__, `\\/\\  __/\\ \\_\\  ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("     \\ \\_\\ \\____/\\ \\____/     /\\____\\ \\____/\\/\\____/\\ \\____\\\\/\\_\\ ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("      \\/_/\\/___/  \\/___/      \\/____/\\/___/  \\/___/  \\/____/ \\/_/ ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("                                                                  ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	imprimeparte(desenhoparede, 0); std::cout << center("                                                                  ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
    
	for (int i = 0; i < linhas_vazias; i++){
		imprimeparte(desenhoparede, 0); std::cout << center("                                                              ", espacos - 12); imprimeparte(desenhoparede, 0); printf("\n");
	}
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < this->nColuna; j++) {
			imprimeparte(desenhoparede, i);
		}
		printf("\n");
	}
}




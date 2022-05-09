#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "Jogada.h"
#include <vector>

#ifndef BOMBAS_H
#define BOMBAS_H

std::vector<int> gerar_indices(cenario cena);
void preencher_bombas(cenario& cena);
void print_bombas(cenario cena);
bool verifica_bomba(cenario cena, std::vector<int> celula);

std::vector<int> gerar_indices(cenario cena) {
  srand((unsigned)time(0));
  std::vector<int> indices;

  int linha = rand() % cena.dimensoes.x;
  int coluna = rand() % cena.dimensoes.y;

  indices.push_back(linha);
  indices.push_back(coluna);

  return indices;
}

void preencher_bombas(cenario& cena) {
    int count_bombas = 0;
    do {
      std::vector<int> indices = gerar_indices(cena);
      int l = indices[0];
      int c = indices[1];
    
      if (cena.mapa[l][c] != '@'){
        cena.mapa[l][c] = '@';
        count_bombas++;
      }
    } while(count_bombas < cena.dimensoes.minas);
}

void print_bombas(cenario cena) {
  for (int i = 0; i < cena.bombas.size(); i++) {
    for (int j = 0; j < cena.bombas[i].size(); j++) {
      std::cout << " " << cena.bombas[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool verifica_bomba(cenario cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];
  if (cena.mapa[l][c] == '@') {
    return true;
  }
  return false;
}

#endif

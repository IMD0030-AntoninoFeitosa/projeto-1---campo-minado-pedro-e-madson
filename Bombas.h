
// TODO devem estar dentro do ifndef
#include <cstdlib> 
#include <ctime>
#include <iostream>

#include "Game.h"
#include "Jogada.h"
#include <vector>
// TODO tudo isso


#ifndef BOMBAS_H // TODO deve conter todas as declarações do arquivo incluindo a inclusão das bibliotecas acima
#define BOMBAS_H

std::vector<int> gerar_indices(cenario cena);
cenario preencher_bombas(cenario cena);
void print_bombas(cenario cena);
bool verifica_bomba(cenario cena, std::vector<int> celula);

// TODO as implementações das funções devem ficar num arquivo .cpp

std::vector<int> gerar_indices(cenario cena) {
  srand((unsigned)time(0));
  std::vector<int> indices;

  int linha = rand() % cena.dimensoes.x;
  int coluna = rand() % cena.dimensoes.y;

  indices.push_back(linha);
  indices.push_back(coluna);

  return indices;
}

cenario preencher_bombas(cenario cena) {
  // TODO é mais eficiente verificar uma mina de cada vez ao invés de verificar se o mapa é válido

  do {
    // gerando indices aleatorios
    std::vector<int> indices = gerar_indices(cena);

    // verificar se indices já existem
    bool existe = false;
    for (int i = 0; i < cena.bombas.size(); i++) {
      int l = indices[0];
      int c = indices[1];
      if (cena.bombas[i][0] == l && cena.bombas[i][1] == c) {
        existe = true;
        break;
      }
    }

    if (!existe) {
      cena.bombas.push_back(indices);
    }

  } while (cena.bombas.size() < cena.dimensoes.minas);

  return cena;
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

  for (int i = 0; i < cena.bombas.size(); i++) {
    if (cena.bombas[i][0] == l && cena.bombas[i][1] == c) {
      return true;
    }
  }

  return false;
}

#endif

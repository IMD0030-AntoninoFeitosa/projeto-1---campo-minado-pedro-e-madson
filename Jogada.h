#include "Game.h"
#include <vector>
#ifndef JOGADA_H
#define JOGADA_H

std::vector<std::vector<int>> adjacentes(cenario cena, int l, int c) {
  std::vector<std::vector<int>> vetor_saida;
  std::vector<int> temp;

  // pegando celula de cima
  if (l - 1 >= 0) {
    temp.push_back(l - 1);
    temp.push_back(c);
    vetor_saida.push_back(temp);
    // pegando celula da direita acima
    if (c + 1 < cena.dimensoes.y) {
      temp.push_back(l - 1);
      temp.push_back(c + 1);
      vetor_saida.push_back(temp);
    }

    // pegando celula da esquerda acima
    if (c - 1 >= 0) {
      temp.push_back(l - 1);
      temp.push_back(c - 1);
      vetor_saida.push_back(temp);
    }
  }

  // pegando celula de baixo
  if (l + 1 < cena.dimensoes.x) {
    temp.push_back(l + 1);
    temp.push_back(c);
    vetor_saida.push_back(temp);
    
    // pegando celula da direita acima
    if (c + 1 < cena.dimensoes.y) {
      temp.push_back(l + 1);
      temp.push_back(c + 1);
      vetor_saida.push_back(temp);
    }

    // pegando celula da esquerda acima
    if (c - 1 >= 0) {
      temp.push_back(l + 1);
      temp.push_back(c - 1);
      vetor_saida.push_back(temp);
    }
  }

  // pegando celula da esquerda
  if (c - 1 >= 0) {
    temp.push_back(l);
    temp.push_back(c - 1);
    vetor_saida.push_back(temp);
  }

  // pegando celula da direita
  if (c + 1 < cena.dimensoes.y) {
    temp.push_back(l);
    temp.push_back(c + 1);
    vetor_saida.push_back(temp);
  }

  return vetor_saida;
}

#endif

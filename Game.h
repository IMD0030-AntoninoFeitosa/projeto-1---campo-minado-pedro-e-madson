#include <vector>

#ifndef GAME_H
#define GAME_H

enum Difficulty { beginner, intermediary, advanced };

struct cenario {
  std::vector<std::vector<char>> mapa;
  std::vector<std::vector<int>> bombas;
  std::vector<std::vector<int>> lados_adjacentes; 
  std::vector<std::vector<int>> marcacoes; 
  std::vector<std::vector<int>> selecionados; // vetor com todos as celulas que o usuario já clicou

  struct {
    int x;
    int y;
    int minas;
  } dimensoes;

};

#endif

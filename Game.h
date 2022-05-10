
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <array>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

enum Difficulty { beginner, intermediary, advanced };
enum Opcoes { iniciar_jogo = 1, creditos_jogo, instrucoes_jogo, sair_jogo };

struct cenario {
  std::vector<std::vector<char>> mapa;
  std::vector<std::vector<int>> bombas;
  std::vector<std::vector<int>> lados_adjacentes; 
  int reveladas;
  int marcacoes; 
  int quantidade_jogadas;
  std::vector<std::vector<int>> selecionados; // vetor com todos as celulas que o usuario já clicou

  struct {
    int x;
    int y;
    int minas;
  } dimensoes;

};

void store_difficulty(const std::string config_file, Difficulty level);
Difficulty load_difficulty(const std::string config_file);
void print_mapa(cenario cena);


#endif

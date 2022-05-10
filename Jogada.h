#include "Game.h"
#include <vector>
#ifndef JOGADA_H
#define JOGADA_H

#include "Bombas.h"

std::vector<std::vector<int>> adjacentes(cenario cena, std::vector<int> celula);
void revelar(cenario &cena, int l, int c, int controlador);
bool celula_valida(cenario cena, std::vector<int> celula);
void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula);
void marcar_celula(cenario &cena, std::vector<int> celula);
int numero_bombas(cenario cena, std::vector<int> celula);
bool foi_marcada(cenario &cena, std::vector<int> celula);
bool foi_revelada(cenario &cena, std::vector<int> celula);

int numero_bombas(cenario cena, std::vector<int> celula) {
  int bombas = 0;

  int l = celula[0];
  int c = celula[1];

  std::vector<std::vector<int>> lados = adjacentes(cena, celula);

  for (int i = 0; i < lados.size(); i++) {
    if (verifica_bomba(cena, lados[i])) {
      bombas++;
    }
  }

  return bombas;
}

std::vector<std::vector<int>> adjacentes(cenario cena,
                                         std::vector<int> celula) {
  int l = celula[0], c = celula[1];
  std::vector<std::vector<int>> vetor_saida;

  // pegando celula de cima
  if (l - 1 >= 0) {
    std::vector<int> temp;
    temp.push_back(l - 1);
    temp.push_back(c);
    vetor_saida.push_back(temp);

    if (c + 1 < cena.dimensoes.y) {
      std::vector<int> temp;
      temp.push_back(l - 1);
      temp.push_back(c + 1);
      vetor_saida.push_back(temp);
    }

    // pegando celula da esquerda acima
    if (c - 1 >= 0) {
      std::vector<int> temp;
      temp.push_back(l - 1);
      temp.push_back(c - 1);
      vetor_saida.push_back(temp);
    }
  }

  // pegando celula de baixo
  if (l + 1 < cena.dimensoes.x) {
    std::vector<int> temp;
    temp.push_back(l + 1);
    temp.push_back(c);
    vetor_saida.push_back(temp);

    // pegando celula da direita acima
    if (c + 1 < cena.dimensoes.y) {
      std::vector<int> temp;
      temp.push_back(l + 1);
      temp.push_back(c + 1);
      vetor_saida.push_back(temp);
    }

    // pegando celula da esquerda acima
    if (c - 1 >= 0) {
      std::vector<int> temp;
      temp.push_back(l + 1);
      temp.push_back(c - 1);
      vetor_saida.push_back(temp);
    }
  }

  // pegando celula da esquerda
  if (c - 1 >= 0) {
    std::vector<int> temp;
    temp.push_back(l);
    temp.push_back(c - 1);
    vetor_saida.push_back(temp);
  }

  // pegando celula da direita
  if (c + 1 < cena.dimensoes.y) {
    std::vector<int> temp;
    temp.push_back(l);
    temp.push_back(c + 1);
    vetor_saida.push_back(temp);
  }

  return vetor_saida;
}

bool celula_valida(cenario cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];

  if (l >= 0 && l < cena.dimensoes.x && c >= 0 && c < cena.dimensoes.y) {
    return true;
  }

  return false;
}

void revelar(cenario &cena, int l, int c, int controlador) {
  std::vector<int> celula;
  celula.push_back(l);
  celula.push_back(c);

  if (celula_valida(cena, celula)) {
    if (!foi_revelada(cena, celula)) {
      if (!foi_marcada(cena, celula)){
        cena.selecionados.push_back(celula);
        cena.reveladas++;
      }
      if (numero_bombas(cena, celula) == 0 || controlador == 1) {
        revelar(cena, l - 1, c, 0);
        revelar(cena, l - 1, c - 1, 0);
        revelar(cena, l - 1, c + 1, 0);

        revelar(cena, l + 1, c, 0);
        revelar(cena, l + 1, c - 1, 0);
        revelar(cena, l + 1, c + 1, 0);

        revelar(cena, l, c - 1, 0);
        revelar(cena, l, c + 1, 0);

        if (!foi_marcada(cena, celula) && !foi_revelada(cena, celula)){
          cena.selecionados.push_back(celula);
          cena.reveladas++;
        }
      } else {
        if (!foi_marcada(cena, celula) && !foi_revelada(cena, celula)){
          cena.selecionados.push_back(celula);
          cena.reveladas++;
        }
      }
    }
  }
}

void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula) {
  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  for (int i = 0; i < lados.size(); i++) {
    if (!verifica_bomba(cena, lados[i]) && !foi_revelada(cena, lados[i])) {
      revelar(cena, lados[i][0], lados[i][1], 0);
    }
  }
}

void marcar_celula(cenario &cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];

  // ? marcado em posicao que n é bomba
  // & marcado em posicao que é bomba

  char v = cena.mapa[l][c];
  bool revelada = foi_revelada(cena, celula);

  if (!revelada){
      if (v == '@' ){
        cena.mapa[l][c] = '&';
        cena.marcacoes ++;
      } else if (v == '&'){
        cena.mapa[l][c] = '@';
        cena.marcacoes --;
      } else if (v == '?'){
        cena.mapa[l][c] = 'X';
        cena.marcacoes --;
      } else {
        cena.mapa[l][c] = '?';
        cena.marcacoes ++;
      } 
  }
}

bool foi_marcada(cenario &cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];

  char v = cena.mapa[l][c];
  
  if (v == '&' || v == '?'){
    return true;
  }
  
  return false;
}

bool foi_revelada(cenario &cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];
  for (int i = 0; i < cena.selecionados.size(); i++) {
    if (l == cena.selecionados[i][0] && c == cena.selecionados[i][1]) {
      return true;
    }
  }
  return false;
}

#endif

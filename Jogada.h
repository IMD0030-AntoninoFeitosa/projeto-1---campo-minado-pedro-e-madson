#include "Game.h"
#include <vector>
#ifndef JOGADA_H
#define JOGADA_H

// #include "Game.h"
#include "Bombas.h"

std::vector<std::vector<int>> adjacentes(cenario cena, std::vector<int> celula);
void revelar(cenario &cena, int l, int c, int controlador);
bool celula_valida(cenario cena, std::vector<int> celula);
bool esta_aberta(cenario cena, std::vector<int> celula);
void print_lados(cenario cena, std::vector<int> celula);
void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula);
void marcar_celula(cenario &cena, std::vector<int> celula);
int numero_bombas(cenario cena, std::vector<int> celula);
bool esta_marcada(cenario &cena, std::vector<int> celula);
bool foi_relevada(cenario &cena, std::vector<int> celula);

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
    if (!esta_aberta(cena, celula)) {
      cena.selecionados.push_back(celula);
      if (numero_bombas(cena, celula) == 0 || controlador == 1) {
        revelar(cena, l - 1, c, 0);
        revelar(cena, l - 1, c - 1, 0);
        revelar(cena, l - 1, c + 1, 0);

        revelar(cena, l + 1, c, 0);
        revelar(cena, l + 1, c - 1, 0);
        revelar(cena, l + 1, c + 1, 0);

        revelar(cena, l, c - 1, 0);
        revelar(cena, l, c + 1, 0);

        if (!esta_marcada(cena, celula)){
          cena.selecionados.push_back(celula);
        }
      } else {
        if (!esta_marcada(cena, celula)){
          cena.selecionados.push_back(celula);
        }
      }
    }
  }
}

void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula) {
  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  for (int i = 0; i < lados.size(); i++) {
    if (!verifica_bomba(cena, lados[i]) && !esta_aberta(cena, lados[i])) {
      revelar(cena, lados[i][0], lados[i][1], 0);
    }
  }
  // return cena;
}

bool esta_aberta(cenario cena, std::vector<int> celula) {
  for (int i = 0; i < cena.selecionados.size(); i++) {
    std::vector<int> temp = cena.selecionados[i];
    if (temp[0] == celula[0] && temp[1] == celula[1]) {
      return true;
    }
  }
  return false;
}

void marcar_celula(cenario &cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];
  int marcado = -1;
  for (int i = 0; i < cena.marcacoes.size(); i++) {
    if (l == cena.marcacoes[i][0] && c == cena.marcacoes[i][1]) {
      marcado = i;
    }
  }
  if (marcado == -1) {
    if (!foi_relevada(cena, celula) &&
        cena.marcacoes.size() <= cena.dimensoes.minas) {
      cena.marcacoes.push_back(celula);
    }
  } else {
    std::vector<std::vector<int>> marcacoes;
    for (int i = 0; i < cena.marcacoes.size(); i++) {
      if (i != marcado) {
        marcacoes.push_back(cena.marcacoes[i]);
      }
    }
    cena.marcacoes = marcacoes;
  }
}

bool esta_marcada(cenario &cena, std::vector<int> celula) {

  int l = celula[0];
  int c = celula[1];

  for (int i = 0; i < cena.marcacoes.size(); i++) {
    if (l == cena.marcacoes[i][0] && c == cena.marcacoes[i][1]) {
      return true;
    }
  }
  return false;
}

bool foi_relevada(cenario &cena, std::vector<int> celula) {
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

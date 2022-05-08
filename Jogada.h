#include "Game.h"
#include <vector>
#ifndef JOGADA_H
#define JOGADA_H

// #include "Game.h"
#include "Bombas.h"

std::vector<std::vector<int>> adjacentes(cenario cena, std::vector<int> celula);
void revelar(cenario& cena, int l, int c, int controlador);
bool celula_valida(cenario cena, std::vector<int> celula);
bool esta_aberta(cenario cena, std::vector<int> celula);
void print_lados(cenario cena, std::vector<int> celula);
void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula);

int numero_bombas(cenario cena, std::vector<int> celula);

int numero_bombas(cenario cena, std::vector<int> celula) {
  int bombas = 0;

  int l = celula[0];
  int c = celula[1];

  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  
  for (int i = 0; i < lados.size(); i++) {
    if (verifica_bomba(cena, lados[i])){
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

      
void revelar(cenario& cena, int l, int c, int controlador) {
  std::vector<int> celula(l, c);
  if (celula_valida(cena, celula)){
    // std::cout<< " 1 " <<std::endl;
    if (!esta_aberta(cena, celula)){
      cena.selecionados.push_back(celula);
      if (numero_bombas(cena, celula) == 0 || controlador == 1 ) {
        revelar(cena, l - 1, c, 0);
        revelar(cena, l - 1, c - 1, 0);
        revelar(cena, l - 1, c + 1, 0);
        
        revelar(cena, l + 1, c, 0);
        revelar(cena, l + 1, c - 1, 0);
        revelar(cena, l + 1, c + 1, 0);
        
        revelar(cena, l, c - 1, 0);
        revelar(cena, l, c + 1, 0);
        
        cena.selecionados.push_back(celula);
      } else {
        cena.selecionados.push_back(celula);
      }
    }
  }

  // if (celula_valida(cena, celula) && ) {
  //   int bombas = ;
  //   if(bombas == 0){
  //     return abrir_celulas_adjacentes(cena, celula);
  //   }
    
  // } else {
  //   std::cout << "CELULA INVÁLIDA!!!" << std::endl;
  // }
  // return cena;
}

void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula) {
  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  for (int i = 0; i < lados.size(); i++) {
    if (!verifica_bomba(cena, lados[i]) && !esta_aberta(cena, lados[i])) {
      revelar(cena, lados[i][0],  lados[i][1], 0);
    }
  }
  // return cena;
}

void print_lados(cenario cena, std::vector<int> celula) {
  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  for (int i = 0; i < lados.size(); i++) {
    std::vector<int> lado = lados[i];
    std::cout << "L: " << lado[0] << " C: " << lado[1] << std::endl;
  }
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
#endif

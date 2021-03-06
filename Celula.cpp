#include "Celula.h"

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
      if (!verifica_bomba(cena, celula)) {
        if (!foi_marcada(cena, celula)) {
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

          if (!foi_marcada(cena, celula) && !foi_revelada(cena, celula)) {
            cena.selecionados.push_back(celula);
            cena.reveladas++;
          }
        } else {
          if (!foi_marcada(cena, celula) && !foi_revelada(cena, celula)) {
            cena.selecionados.push_back(celula);
            cena.reveladas++;
          }
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

  // ? marcado em posicao que n ?? bomba
  // & marcado em posicao que ?? bomba

  char v = cena.mapa[l][c];

  bool revelada = foi_revelada(cena, celula);

  if (!revelada) {
    if (v == '@') {
      cena.mapa[l][c] = '&';
      cena.marcacoes++;
    } else if (v == '&') {
      cena.mapa[l][c] = '@';
      cena.marcacoes--;
    } else if (v == '?') {
      cena.mapa[l][c] = 'X';
      cena.marcacoes--;
    } else {
      cena.mapa[l][c] = '?';
      cena.marcacoes++;
    }
  }
}

bool foi_marcada(cenario &cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];

  char v = cena.mapa[l][c];

  if (v == '&' || v == '?') {
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

/*
 *
 *Metodos das minas
 *
 */
std::vector<int> gerar_indices(cenario cena) {
  srand((unsigned)time(0));
  std::vector<int> indices;

  int linha = rand() % cena.dimensoes.x;
  int coluna = rand() % cena.dimensoes.y;

  indices.push_back(linha);
  indices.push_back(coluna);

  return indices;
}

void preencher_bombas(cenario &cena) {
  int count_bombas = 0;
  do {
    std::vector<int> indices = gerar_indices(cena);
    int l = indices[0];
    int c = indices[1];

    if (cena.mapa[l][c] != '@') {
      cena.mapa[l][c] = '@';
      count_bombas++;
    }
  } while (count_bombas < cena.dimensoes.minas);
}
void preencher_bombas(cenario &cena, std::vector<std::vector<int>> invalidos) {
  int count_bombas = 0;
  do {
    std::vector<int> indices = gerar_indices(cena);
    int l = indices[0];
    int c = indices[1];

    bool esta_ao_lado = false;

    for (int i = 0; i < invalidos.size(); i++){
      if (l == invalidos[i][0] && c == invalidos[i][1]){
        esta_ao_lado = true;
        break;
      }
    }

    if (cena.mapa[l][c] != '@' && !esta_ao_lado) {
      cena.mapa[l][c] = '@';
      count_bombas++;
    }
  } while (count_bombas < cena.dimensoes.minas);
}
void preencher_bombas(cenario & cena, std::vector<int> celula) {
  srand((unsigned)time(0));
  
  std::vector<std::vector<int>> lados = adjacentes(cena, celula);
  int size = lados.size();
  
  if (size > 4){
    size = size - 4;
  } 
  
  int bombas = (rand() % size) + 1;

  // std::cout << "BOMBAS: " << bombas <<std::endl; 

  for (int i = 0; i < bombas; i++){
    int l = lados[i][0];
    int c = lados[i][1];
    if (l != celula[0] && c != celula[1]){
      cena.mapa[l][c] = '@';
    }
  }
  
  int count_bombas = bombas;
  
  do {
    std::vector<int> indices = gerar_indices(cena);
    int l = indices[0];
    int c = indices[1];

    if (cena.mapa[l][c] != '@' && l != celula[0] && c != celula[1]) {
      // std::cout << "l: " << l << " c: " << c <<std::endl; 
      cena.mapa[l][c] = '@';
      count_bombas++;
    }
  } while (count_bombas < cena.dimensoes.minas);
}

bool verifica_bomba(cenario cena, std::vector<int> celula) {
  int l = celula[0];
  int c = celula[1];
  if (cena.mapa[l][c] == '@' || cena.mapa[l][c] == '&') {
    return true;
  }
  return false;
}


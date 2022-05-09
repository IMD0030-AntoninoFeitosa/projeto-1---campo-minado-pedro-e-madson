
#include <array>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Bombas.h"
#include "Game.h"
#include "Jogada.h"
#include "Mensagens.h"

const std::string CONFIG_FILE = "config.cfg";

void store_difficulty(const std::string config_file, Difficulty level);
Difficulty load_difficulty(const std::string config_file);
void print_mapa(cenario cena);
int contar_bombas(cenario cena, std::vector<int> celula);

int contar_bombas(cenario cena, std::vector<int> celula) {
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

void show_usage(void) {
  std::cout << "Usage: game [option]" << std::endl;
  std::cout << "Option:" << std::endl;
  std::cout << " -h or --help                  Display this information."
            << std::endl;
  std::cout << " -d or --difficulty <option>   Change the game difficulty for "
               "<option>"
            << std::endl;
  std::cout << "                               -b or --beginner" << std::endl;
  std::cout << "                               -i or --intermediary"
            << std::endl;
  std::cout << "                               -a or --advanced" << std::endl;
}

cenario create_map(Difficulty level) {
  cenario cena;
  if (level == 0) {
    cena.dimensoes.minas = 10;
    cena.dimensoes.x = 10;
    cena.dimensoes.y = 10;
    // 10 x 10 + 10 minas
  } else if (level == 1) {
    cena.dimensoes.minas = 40;
    cena.dimensoes.x = 15;
    cena.dimensoes.y = 15;
    // 15 x 15 + 40 minas
  } else if (level == 2) {
    cena.dimensoes.minas = 100;
    cena.dimensoes.x = 15;
    cena.dimensoes.y = 30;
    // 15 x 30 + 100 minas
  } else {
    store_difficulty(CONFIG_FILE, level);
    show_usage();
  }
  int l = cena.dimensoes.x;
  int c = cena.dimensoes.y;
  for (int i = 0; i < l; i++) {
    std::vector<char> temp;
    for (int j = 0; j < c; j++) {
      temp.push_back('X');
    }
    cena.mapa.push_back(temp);
  }

  return cena;
}

void print_mapa(cenario cena) {
  for (int i = 0; i < cena.mapa.size(); i++) {

    if (i < 10 && cena.dimensoes.x > 10)
      std::cout << " ";

    std::cout << i << " - ";

    for (int j = 0; j < cena.mapa[i].size(); j++) {
      std::vector<int> celula;
      celula.push_back(i);
      celula.push_back(j);
      if (esta_aberta(cena, celula)) {
        int bombas = contar_bombas(cena, celula);
        if (verifica_bomba(cena, celula)) {
          std::cout << " "
                    << "X"
                    << " ";
        } else {
          if (esta_marcada(cena, celula)) {
            std::cout << " "
                      << "?"
                      << " ";
          } else {
            std::cout << " " << bombas << " ";
          }
        }
      } else {
        if (verifica_bomba(cena, celula)) {
          std::cout << " "
                    << "X"
                    << " ";
        } else {
          if (esta_marcada(cena, celula)) {
            std::cout << " "
                      << "?"
                      << " ";
          } else {
            std::cout << " " << cena.mapa[i][j] << " ";
          }
        }
      }
    }
    std::cout << std::endl;

    if (i == cena.dimensoes.x - 1) {
      if (cena.dimensoes.y > 10)
        std::cout << " ";
      std::cout << "     ";
      for (int j = 0; j < cena.mapa[i].size(); j++) {
        std::cout << "|  ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "     ";
  if (cena.dimensoes.y > 10)
    std::cout << " ";
  for (int j = 0; j < cena.mapa[0].size(); j++) {
    if (j > 9) {
      std::cout << j << " ";
    } else {
      std::cout << j << "  ";
    }
  }

  std:: cout << std::endl;
  std::cout<<"Marcacoes: " << cena.marcacoes.size() << std::endl;
  std::cout<<"Jogadas: " << cena.quantidade_jogadas << std::endl;
  std::cout<<"Bombas: " << cena.dimensoes.minas - cena.marcacoes.size() << std::endl;
std::cout << std::endl;
}

void start_game(Difficulty level) {
  std::vector<std::vector<char>> mapa;
  cenario cena = create_map(level);
  cena.quantidade_jogadas = 0;
  preencher_bombas(cena);
  std::cout << std::endl;
  print_bombas(cena);
  mensagem_menu();

  bool sair = false;

  do {
    int resposta_usuario;
    std::cin >> resposta_usuario;
    printf("\033c");
    switch (resposta_usuario) {
    case Opcoes::iniciar_jogo: {
      do {
        printf("\033c");
        print_mapa(cena);
        if (cena.selecionados.size() ==
            (cena.dimensoes.x * cena.dimensoes.y - cena.dimensoes.minas)) {
          mensagem_ganhou();
          abort();
        } else {
          std::cout << std::endl;
          int l, c;
          char action;
          std::cout << "A L e C" << std::endl;
          std::cin >> action;
          std::cin >> l >> c;
          std::vector<int> celula;
          celula.push_back(l);
          celula.push_back(c);
          if (action == 'R' || action == 'r') {
            if (verifica_bomba(cena, celula)) {
              mensagem_perdeu();
              abort();
            }
            if (celula_valida(cena, celula)) {
              cena.quantidade_jogadas ++;
              revelar(cena, l, c, 1);
            } else {
              std::cout << "<< OPCAO INVÁLIDA >> " << std::endl;
            }
          } else if (action == 'M' || action == 'm') {
            marcar_celula(cena, celula);
          } else {
            std::cout << "<< OPCAO INVÁLIDA >> " << std::endl;
          }
        }
      } while (true);
      break;
    }
    case Opcoes::creditos_jogo:
      mensagem_creditos();
      break;
    case Opcoes::instrucoes_jogo:
      mensagem_instrucoes();
      break;
    case Opcoes::sair_jogo:
      sair = true;
      break;
    }
  } while (!sair);
}

void store_difficulty(const std::string config_file, Difficulty level) {
  std::ofstream file;
  file.open(config_file.c_str(), std::ifstream::out);
  if (file.is_open()) {
    switch (level) {
    case Difficulty::beginner:
      file << 'b';
      break;
    case Difficulty::intermediary:
      file << 'i';
      break;
    case Difficulty::advanced:
      file << 'a';
      break;
    }
    file.close();
  }
}

Difficulty load_difficulty(const std::string config_file) {
  Difficulty level;
  std::ifstream file;
  file.open(config_file.c_str(), std::ifstream::in);
  if (file.is_open()) {
    char c;
    file >> c;
    switch (c) {
    case 'b':
      level = Difficulty::beginner;
      break;
    case 'i':
      level = Difficulty::intermediary;
      break;
    case 'a':
      level = Difficulty::advanced;
      break;
    }
    file.close();
  } else {
    store_difficulty(config_file, Difficulty::beginner);
    level = Difficulty::beginner;
  }
  return level;
}

int main(int argc, char **argv) {

  if (argc > 1) {
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
      show_usage();
    } else if (arg == "-d" || arg == "--difficulty") {

      if (argc > 2) {
        std::string newlevel = argv[2];
        if (newlevel == "-b" || newlevel == "--beginner") {
          store_difficulty(CONFIG_FILE, Difficulty::beginner);
        } else if (newlevel == "-i" || newlevel == "--intermediary") {
          store_difficulty(CONFIG_FILE, Difficulty::intermediary);
        } else if (newlevel == "-a" || newlevel == "--advanced") {
          store_difficulty(CONFIG_FILE, Difficulty::advanced);
        } else {
          std::cout << "Unknown difficulty argument: " << newlevel << std::endl;
          show_usage();
        }
      } else {
        std::cout << "It was expected a difficulty for: " << argv[1]
                  << std::endl;
        show_usage();
      }
    } else {
      std::cout << "Unknown argument: " << argv[1] << std::endl;
      show_usage();
    }
  } else {
    Difficulty level = load_difficulty(CONFIG_FILE);
    start_game(level);
  }
  return 0;
}

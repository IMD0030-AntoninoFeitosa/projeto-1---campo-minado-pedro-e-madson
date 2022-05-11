#include "Record.hpp"
#include "Celula.h"
#include "Game.h"
#include "Saidas.h"

const std::string CONFIG_FILE = "config.cfg";
std::string file_name = "logs.txt";

void show_usage(void) {
  std::cout << "Usage: game [option]" << std::endl;
  std::cout << "Option:" << std::endl;
  std::cout << " --init to init game"
            << std::endl;
  std::cout << " -r or --ranking display ranking information"
            << std::endl;
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
  cena.marcacoes = 0;
  cena.quantidade_jogadas = 0;
  cena.reveladas = 0;

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
    std::cout << "\033[1;32m";
    if (i < 10 && cena.dimensoes.x > 10) {
      std::cout << " ";
    }

    std::cout << i << " - ";
    std::cout << "\033[0m";

    for (int j = 0; j < cena.mapa[i].size(); j++) {
      std::vector<int> celula;
      celula.push_back(i);
      celula.push_back(j);
      if (foi_revelada(cena, celula)) {

        int bombas = numero_bombas(cena, celula);

        if (verifica_bomba(cena, celula)) {

          if (foi_marcada(cena, celula)) {
            std::cout << "\033[1;33m ? \033[0m";
          } else {
            std::cout << " X ";
          }

        } else {
          if (foi_marcada(cena, celula)) {
            std::cout << "\033[1;33m ? \033[0m";
          } else {
            if (bombas == 0){
               std::cout << "\033[1;32m";
            } else if (bombas > 0 && bombas <= 2){
               std::cout << "\033[0;36m";
            } else if (bombas > 2 && bombas <= 4){
               std::cout << "\033[0;31m";
            } else {
               std::cout << "\033[0;35m";
            }
            std::cout << " " << bombas << " \033[0m";
          }
        }
      } else {
        if (verifica_bomba(cena, celula)) {
          if (foi_marcada(cena, celula)) {
            std::cout << "\033[1;33m ? \033[0m";
          } else {
            std::cout << " X ";
          }
        } else {
          if (foi_marcada(cena, celula)) {
            std::cout << " ? ";
          } else {
            std::cout << " " << cena.mapa[i][j] << " ";
          }
        }
      }
    }
    std::cout << std::endl;
    std::cout << "\033[1;32m";
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
    std::cout << "\033[0m";
}

void start_game(Difficulty level) {
  Record usuario;
  std::vector<Record> vec;
  read_records(vec, file_name);
  
  bool preencheu = false;
  std::vector<std::vector<char>> mapa;
  cenario cena = create_map(level);
  std::cout << "DIGITE SEU NOME: ";
  std::cin >> usuario.name;
  std::cout << std::endl;
  usuario.nivel = level;

  if (level == 0) {
    preencher_bombas(cena);
    preencheu = true;
  }
  std::cout << std::endl;
  mensagem_menu();

  bool sair = false;

  do {
    int resposta_usuario;
    std::cout << "ESCOLHA UMA OPÇÃO: "; std::cin >> resposta_usuario;
    printf("\033c");
    switch (resposta_usuario) {
    case Opcoes::iniciar_jogo: {
      auto start = std::chrono::high_resolution_clock::now();
      bool primeira_volta = true;
      do {
        auto finish = std::chrono::high_resolution_clock::now();
        if(primeira_volta){
          finish = start;
        }
        printf("\033c");
        print_mapa(cena);
        metricas(cena, start, finish);
        primeira_volta = false;
        if (cena.reveladas ==
            ((cena.dimensoes.x * cena.dimensoes.y) - cena.dimensoes.minas)) {  
          std::chrono::duration<double> elapsed = finish - start;

          usuario.milliseconds = elapsed.count();
          vec.push_back(usuario);

          Record ** records {new Record*[vec.size()]};
          
          for(int i=0;i<vec.size();i++){
            records[i] = new Record{vec[i]};
          }
          
          char output [] = "logs.txt";
          
          printf("\033c");
          print_mapa(cena);
          metricas(cena, start, finish);
          mensagem_ganhou();
          
          write(output, vec.size(), records);
          
          for(int i=0;i<vec.size(); i++){
            delete records[i];
          }
          delete [] records;
          abort();
          
        } else {
          int l, c;
          char action;
          std::cout << "A L e C" << std::endl;
          std::cin >> action;
          std::cin >> l >> c;
          std::vector<int> celula;

          celula.push_back(l);
          celula.push_back(c);

          if (action == 'R' || action == 'r') {
            bool eh_valida = celula_valida(cena, celula);
            bool eh_bomba = verifica_bomba(cena, celula);

            // comencando com 0
            if (level == 1 && !preencheu && eh_valida) {
              preencher_bombas(cena, adjacentes(cena, celula));
            }

            // comencando com numero
            if (level == 2 && !preencheu && eh_valida) {
              preencher_bombas(cena, celula);
            }

            printf("\033c");
            print_mapa(cena);
            metricas(cena, start, std::chrono::high_resolution_clock::now());
            preencheu = true;
            
            if (eh_bomba) {
              mensagem_perdeu();
              abort();
            }

            if (eh_valida) {
              cena.quantidade_jogadas++;
              revelar(cena, l, c, 1);
            } else {
              std::cout << "<< OPCAO INVÁLIDA >> " << std::endl;
            }
          } else if (action == 'M' || action == 'm') {
            printf("\033c");
            print_mapa(cena);
            metricas(cena, start, std::chrono::high_resolution_clock::now());
            if (celula_valida(cena, celula)) {
              marcar_celula(cena, celula);
            } else {
              std::cout << "<< OPCAO INVÁLIDA >> " << std::endl;
            }

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
        std::string iniciar = argv[3];
        if (newlevel == "-b" || newlevel == "--beginner") {
          store_difficulty(CONFIG_FILE, Difficulty::beginner);
          if (iniciar == "--init"){
            start_game(Difficulty::beginner);
          }
        } else if (newlevel == "-i" || newlevel == "--intermediary") {
          store_difficulty(CONFIG_FILE, Difficulty::intermediary);
          if (iniciar == "--init"){
            start_game(Difficulty::intermediary);
          }
        } else if (newlevel == "-a" || newlevel == "--advanced") {
          store_difficulty(CONFIG_FILE, Difficulty::advanced);
          if (iniciar == "--init"){
            start_game(Difficulty::advanced);
          }
        } else {
          std::cout << "Unknown difficulty argument: " << newlevel << std::endl;
          show_usage();
        }
      } else {
        std::cout << "It was expected a difficulty for: " << argv[1]
                  << std::endl;
        show_usage();
      }
    } if (arg == "-r" || arg == "--ranking") {
      std::vector<Record> vec;
      read_records(vec, file_name);
      print_ranking(vec);
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

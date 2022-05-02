#include <iostream>

#ifndef MENSAGENS_H
#define MENSAGENS_H

void mensagem_menu(){
	std::cout << "" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
	std::cout << "|                                 Menu                                        |" << std::endl;
	std::cout << "|                           (1) Iniciar Jogo                                  |" << std::endl;
	std::cout << "|                           (2) Créditos                                      |" << std::endl;
	std::cout << "|                           (3) Instruções do Jogo                            |" << std::endl;
	std::cout << "|                           (4) Sair do Jogo                                  |" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
	std::cout << std::endl << std::endl;
}
// Tela de créditos
void mensagem_creditos(){
	std::cout << "" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
	std::cout << "|                                 LP1 2022.1                                  |" << std::endl;
	std::cout << "|                         ANTONINO ALVES FEITOSA NETO                         |" << std::endl;
	std::cout << "|                                                                             |" << std::endl;
	std::cout << "|                                  Grupo:                                     |" << std::endl;
	std::cout << "|                        MÁDSON DUGLAS DOS SANTOS NEVES.                      |" << std::endl;
	std::cout << "|                     PEDRO SCHAUENBERG FIGUEIREDO CANTIDIO                   |" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
}

void mensagem_instrucoes(){
	std::cout << "" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
	std::cout << "|                          Instruçoes do Jogo                                 |" << std::endl;
	std::cout << "|                                                                             |" << std::endl;
	std::cout << "|              R - Revela, exemplo: R 1 2 - Revela posição 12.                |" << std::endl;
	std::cout << "|              F - Flag, exemplo: F 1 2 - Insere uma flag na posição 12.      |" << std::endl;
	std::cout << "|              ? - Interrogação: ? 1 2 - Insere uma ? na posição 12.          |" << std::endl;
	std::cout << "|-----------------------------------------------------------------------------|" << std::endl;
}

void mensagem_perdeu(){
    std::cout << std::endl;
    std::cout << "██╗   ██╗ ██████╗  ██████╗███████╗    ██████╗ ███████╗██████╗ ██████╗ ███████╗██╗   ██╗██╗ " << std::endl;
    std::cout << "██║   ██║██╔═══██╗██╔════╝██╔════╝    ██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝██║   ██║██║ " << std::endl; 
    std::cout << "██║   ██║██║   ██║██║     █████╗      ██████╔╝█████╗  ██████╔╝██║  ██║█████╗  ██║   ██║██║ " << std::endl;
    std::cout << "╚██╗ ██╔╝██║   ██║██║     ██╔══╝      ██╔═══╝ ██╔══╝  ██╔══██╗██║  ██║██╔══╝  ██║   ██║╚═╝ " << std::endl;
    std::cout << " ╚████╔╝ ╚██████╔╝╚██████╗███████╗    ██║     ███████╗██║  ██║██████╔╝███████╗╚██████╔╝██╗ " << std::endl;
    std::cout << "  ╚═══╝   ╚═════╝  ╚═════╝╚══════╝    ╚═╝     ╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝ ╚═════╝ ╚═╝ " << std::endl;
	  std::cout << std::endl << std::endl;
}


#endif

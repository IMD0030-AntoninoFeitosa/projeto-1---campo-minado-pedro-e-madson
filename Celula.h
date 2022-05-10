#ifndef CELULA_H
#define CELULA_H
#include "Game.h"

std::vector<std::vector<int>> adjacentes(cenario cena, std::vector<int> celula);
void revelar(cenario &cena, int l, int c, int controlador);
bool celula_valida(cenario cena, std::vector<int> celula);
void abrir_celulas_adjacentes(cenario cena, std::vector<int> celula);
void marcar_celula(cenario &cena, std::vector<int> celula);
int numero_bombas(cenario cena, std::vector<int> celula);
bool foi_marcada(cenario &cena, std::vector<int> celula);
bool foi_revelada(cenario &cena, std::vector<int> celula);

std::vector<int> gerar_indices(cenario cena);
void preencher_bombas(cenario& cena);
bool verifica_bomba(cenario cena, std::vector<int> celula);

#endif

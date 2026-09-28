/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 * 
 * @file functions.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-28
 * @brief 
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../include/grid.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::vector<State>> MakeGrid(const std::string &filename, int &rows, int &cols);

void PrintSolution(Grid &grid, const std::vector<State> &solution);



#endif //FUNCTIONS_H
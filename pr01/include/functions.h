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
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Grid MakeGrid(const std::string &filename);

void PrintSolution(Grid &grid, const std::vector<State> &solution, const std::string &filename);



#endif //FUNCTIONS_H
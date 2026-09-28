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

#ifndef FUNCTIONS_CC
#define FUNCTIONS_CC

#include "../include/grid.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string>

Grid MakeGrid(const std::string &filename, int &rows, int &cols) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error. No pudo abrirse el archivo " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }


}

#endif //FUNCTIONS_CC

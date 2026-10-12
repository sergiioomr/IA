/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file state.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief Archivo para definir una clase estado. Esta nos permitirá almacenar los diferentes estados
 *        que se puedan encontrar dentro del tablero, uno por coordenada. Teniendo atributos como sus coordenadas,
 *        las de su padre, para poder rehacer el camino, y los valores de coste, h, g y f.
 *  
 */
#ifndef STATE_H
#define STATE_H

#include <utility>


struct State {

  State() = default;
  State(const std::pair<int, int> &coord, int cost) : coord_(coord), parent_coords(-1, -1), cost_(cost) {} 

  std::pair<int, int> coord_{-1, -1};
  std::pair<int, int> parent_coords{-1, -1};
  int cost_ = 0;
  int f = 0;
  int g = 0;
  int h = 0;
};

#endif //STATE_H
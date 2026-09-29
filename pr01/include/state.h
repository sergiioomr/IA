/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file state.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief 
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
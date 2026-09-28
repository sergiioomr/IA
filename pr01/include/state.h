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
  State(const std::pair<int, int> &coord, int cost) : coord_(coord), cost_(cost), parent_coords() {} 

  std::pair<int, int> coord_;
  std::pair<int, int> parent_coords;
  int cost_;
  int f;
  int g;
  int h;
};

#endif //STATE_H
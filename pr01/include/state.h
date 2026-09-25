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
  State(const std::pair<int, int> &coord, int cost) : coord_(coord), cost_(cost) {} 

  std::pair<int, int> coord_;
  int cost_;
};

#endif //STATE_H
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file simulator.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-27
 * @brief 
 */

#include "../include/simulator.h"

int Simulator::FunctionG(const State &state) {
  // If the actual state is the inicial state, it g cost is always 0
  if (state.coord_ == grid_.GetStart()) {
    return 0;
  }
  
  // In other case
  int cost = grid_.GetState(state.parent_coords.first, state.parent_coords.second).g;
  return cost + state.cost_;  
}

int Simulator::Heuristic(const State &state) {       
  int dist_fil = std::abs(grid_.GetEnd().first - state.coord_.second);
  int dist_col = std::abs(grid_.GetEnd().second - state.coord_.first);

  return 2 * (dist_fil + dist_col);
}

int Simulator::FunctionF(const int g, const int h) {
  return g + h;
}
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file grid.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief 
 */

#ifndef GRID_CC
#define GRID_CC

#include "../include/grid.h"

bool Grid::IsValid(int row, int col) const {
  // Check if the position is out of bounds
  if ((row < 0) || (row >= n_row_) || (col < 0) || (col >= n_col_)) {
    return false;
  }

  // Check if its an obstacle
  if (grid_[row][col].cost_ == -1) {
    return false;
  }

  return true;
}

#endif // GRID_CC
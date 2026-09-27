/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file robot.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief 
 */

#ifndef ROBOT_CC
#define ROBOT_CC

#include "../include/robot.h" 

std::pair<int, int> Robot::MoveUp(const State &state) {
  return std::make_pair(state.coord_.first + 1, state.coord_.second);
}

std::pair<int, int> Robot::MoveDown(const State &state) {
  return std::make_pair(state.coord_.first - 1, state.coord_.second);
}

std::pair<int, int> Robot::MoveRight(const State &state) {
  return std::make_pair(state.coord_.first, state.coord_.second + 1);  
}

std::pair<int, int> Robot::MoveLeft(const State &state) {
  return std::make_pair(state.coord_.first, state.coord_.second - 1);
}

#endif // ROBOT_CC
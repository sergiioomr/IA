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

std::pair<int, int> Robot::MoveUp(const std::pair<int, int> &coords) {
  return std::make_pair(coords.first + 1, coords.second);
}

std::pair<int, int> Robot::MoveDown(const std::pair<int, int> &coords) {
  return std::make_pair(coords.first - 1, coords.second);
}

std::pair<int, int> Robot::MoveRight(const std::pair<int, int> &coords) {
  return std::make_pair(coords.first, coords.second + 1);  
}

std::pair<int, int> Robot::MoveLeft(const std::pair<int, int> &coords) {
  return std::make_pair(coords.first, coords.second - 1);
}

#endif // ROBOT_CC
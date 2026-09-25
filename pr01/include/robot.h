/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file robot.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief 
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <utility>

class Robot {
  public:
    Robot() {}

    std::pair<int, int> MoveUp(const std::pair<int, int> &coords);
    std::pair<int, int> MoveDown(const std::pair<int, int> &coords);
    std::pair<int, int> MoveRight(const std::pair<int, int> &coords);
    std::pair<int, int> MoveLeft(const std::pair<int, int> &coords);
};

#endif //ROBOT_H
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file robot.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-25
 * @brief Archivo para declarar la clase robot. Esta representará al robot dentro del tablero, y su 
 *        única responsabilidad será la de saber como moverse a las 4 posibles direcciones. 
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "../include/state.h"
#include <utility>

class Robot {
  public:
    Robot() = default;

    // Métodos para el movimiento
    std::pair<int, int> MoveUp(const State &state);
    std::pair<int, int> MoveDown(const State &state);
    std::pair<int, int> MoveRight(const State &state);
    std::pair<int, int> MoveLeft(const State &state);
};

#endif //ROBOT_H
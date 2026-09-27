/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file simulator.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-27
 * @brief 
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../include/grid.h"
#include "../include/robot.h"
#include "../include/state.h"
#include <utility>
#include <iostream>

class Simulator {
  public:
    Simulator() {}
    Simulator(const Grid &grid, const Robot &robot) : grid_(grid), robot_(robot) {}

    int Heuristic(const State &state);
    int FunctionF(const int g, const int h);
    int FunctionG(const State &state);
    int GetBestNode();
    void Solution(const State &state);
    bool InClosed(const std::pair<int, int> &coord);

    void Algorithm();

  private:

    Grid grid_;
    Robot robot_;
    std::vector<State> open_;
    std::vector<State> closed_;
    std::vector<State> solution_;
};

#endif // SIMULATOR_H

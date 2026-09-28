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

    // Getters
    std::vector<State> GetSolution() const { return solution_; }

    // Métodos para calcular las funciones h, g y f de los estados
    int Heuristic(const State &state);
    int FunctionF(const int g, const int h);
    int FunctionG(const State &state);

    // Método que devolverá el índice del vector de abiertos en el que se encuentra el nodo con menor valor de la función f 
    int GetBestNode();

    // Métodos para comprobar si un nodo está ya en la lista de abiertos o cerrados.
    bool InClosed(const std::pair<int, int> &coord);
    bool InOpen(const std::pair<int, int> &coord);

    // Este método actualiza el estado dentro de la lista de nodos abiertos cuando se modifican sus parámetros
    void UpdateOpen(const State &state);

    void Solution(const State &state);

    // Algoritmo con el bucle principal
    State Algorithm();

  private:

    Grid grid_;
    Robot robot_;

    // Vectores para almacenar los nodos abiertos y cerrados
    std::vector<State> open_;
    std::vector<State> closed_;

    // Lista/vector que almacenará los nodos que pertenecen a la solución en orden 
    std::vector<State> solution_;
};

#endif // SIMULATOR_H

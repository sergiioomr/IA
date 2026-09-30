/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial 
 * @file simulator.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-27
 * @brief Archivo que declara la clase Simulator. Esta será la encargada de ejecutar el algoritmo. Incluye un grid, un robot, y tres listas, una de nodos abiertos
 *        otra de cerrados y una para la solución. Sus métodos son todos para poder ejecutar el algoritmo y calcular la solución.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../include/grid.h"
#include "../include/robot.h"
#include "../include/state.h"
#include <vector>
#include <utility>
#include <iostream>

class Simulator {
  public:
    Simulator() = default;
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

    // Métodos para imprimir los resultados
    void PrintIteration(int iter, std::ostream &out) const;
    void PrintPath(const State &state, std::ostream &out);

    // Método que calcula la solución
    void Solution(const State &state);

    // Algoritmo con el bucle principal
    State Algorithm(std::ostream &file);

  private:
    Grid grid_{};
    Robot robot_{};

    // Vectores para almacenar los nodos abiertos y cerrados
    std::vector<State> open_{};
    std::vector<State> closed_{};

    // Lista/vector que almacenará los nodos que pertenecen a la solución en orden 
    std::vector<State> solution_{};
};

#endif // SIMULATOR_H

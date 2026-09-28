/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file main.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-28
 * @brief 
 */

#include "../include/grid.h"
#include "../include/robot.h"
#include "../include/simulator.h"
#include "../include/state.h"
#include "../include/functions.h"

int main(int argc, char* argv[]) {
  // Obtener el nombre del archivo
  std::string filename = argv[1];

  // Ahora crear la matriz
  int rows, cols;

  Grid grid(MakeGrid(filename, rows, cols), rows, cols);
  Robot robot;
  Simulator simulator(grid, robot);

  std::cout << "Ejecutando algoritmo A*..." << std::endl;
  State final_state = simulator.Algorithm();
  simulator.Solution(final_state);
  std::vector<State> solution = simulator.GetSolution();


  for (size_t i = 0; i < solution.size(); i++) {
    std::cout << "Elemento número " << i << " : (" << solution[i].coord_.first << ", " << solution[i].coord_.second << ")" << std::endl;
  }

  
  return 0;
}
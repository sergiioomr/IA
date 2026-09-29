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
  int rows = 0;
  int cols = 0;
  int start = 0;
  int end = 0;

  Grid grid = MakeGrid(filename);
  Robot robot;
  Simulator simulator(grid, robot);
  
  State final_state = simulator.Algorithm();

  simulator.Solution(final_state);
  std::vector<State> solution = simulator.GetSolution();

  PrintSolution(grid, solution);

  return 0;
}
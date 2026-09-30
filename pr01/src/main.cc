/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file main.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-28
 * @brief Archivo que implementa el programa main. 
 */

#include "../include/grid.h"
#include "../include/robot.h"
#include "../include/simulator.h"
#include "../include/state.h"
#include "../include/functions.h"

int main(int argc, char* argv[]) {
  // Obtener el nombre de los archivos. 
  std::string filename = argv[1];
  std::string output_map = argv[2];
  std::string output_trace = argv[3];

  std::ofstream output(output_trace);

  // Ahora crear la matriz
  Grid grid = MakeGrid(filename);
  Robot robot;
  Simulator simulator(grid, robot);
  
  State final_state = simulator.Algorithm(output);

  // Comprobar si se encontró solución
  if (final_state.coord_ == std::make_pair(-2, -2)) {
    return 0;
  }

  simulator.Solution(final_state);
  simulator.PrintPath(final_state, output);
  simulator.PrintPath(final_state, std::cout);
  std::vector<State> solution = simulator.GetSolution();

  PrintSolution(grid, solution, output_map);

  return 0;
}
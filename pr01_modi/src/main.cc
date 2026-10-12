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
  std::string output_map1 = argv[2];
  std::string output_trace1 = argv[3];

  std::ofstream output_map(output_map1);
  std::ofstream output_trace(output_trace1);
  srand(time(nullptr));

  // Repetir 10 iteraciones cada ejecución. Crear los objetos dentro para que no queden valores de las ejecuciones anteriores
  for (int i = 0; i < 10; i++) {
    
    std::cout << "Solución número: " << i << ": " << std::endl;

    Grid grid = MakeGrid(filename);
    Robot robot;
    Simulator simulator(grid, robot);

    State final_state = simulator.Algorithm(output_trace);

    if (final_state.coord_ == std::make_pair(-2, -2)) {
      return 0;
    }

    simulator.Solution(final_state);
    //simulator.PrintPath(final_state, output_trace);
    //simulator.PrintPath(final_state, std::cout);
    std::vector<State> solution = simulator.GetSolution(); 
    PrintSolution(grid, solution, output_map);
    std::cout << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
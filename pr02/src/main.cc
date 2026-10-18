/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file main.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-12
 * @brief 
 * 
 */

#include "../include/ProblemPSFP.h"
#include "../include/algorithms.h"
#include "../include/GeneticAlgorithm.h"
#include "../include/functions.h"

int main(int argc, char *argv[]) {
    CheckArguments(argc, argv);

    // Crear la instancia del problema introducido
    ProblemPSFP problem(argv[1]);

    // Obtener los parámetros introducidos por el usuario
    int N = std::stoi(argv[2]);
    int Pc = std::stoi(argv[3]);
    int Pm = std::stoi(argv[4]);
    int max_evaluations = std::stoi(argv[5]);

    // Ahora, ejecutar los tres algoritmos contruidos, y mostrar los resultados obtenidos por cada uno de ellos
    std::vector<int> random_search_solution = RandomSearch(problem, max_evaluations);
    std::vector<int> neh_solution = HeuristicNEH(problem);
    AG genetic_algorithm(problem, Pc, Pm, N, max_evaluations, problem.GetSeed());
    Individual genetic_algorithm_solution = genetic_algorithm.Run();

    std::cout << "----------------- Resultados obtenidos -----------------" << std::endl;
    std::cout << "- Algoritmo de búsqueda aleatoria: Makespan = " << problem.CalculateMakespan(random_search_solution) << std::endl;
    std::cout << "- Algoritmo heurístico NEH: Makespan = " << problem.CalculateMakespan(neh_solution) << std::endl;
    std::cout << "- Algoritmo genético: Makespan = " << genetic_algorithm_solution.makespan << std::endl;
    return 0;
}
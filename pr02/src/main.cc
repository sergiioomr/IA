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
#include <fstream>

int main(int argc, char *argv[]) {
    CheckArguments(argc, argv);

    // Crear la instancia del problema introducido
    ProblemPSFP problem(argv[1]);

    // Obtener los parámetros introducidos por el usuario
    int N = std::stoi(argv[2]);
    int Pc = std::stoi(argv[3]);
    int Pm = std::stoi(argv[4]);
    int k = std::stoi(argv[5]);
    int max_evaluations = std::stoi(argv[6]);

    int seed = (argc >= 8) ? std::stoi(argv[7]) : problem.GetSeed(); // Si no se proporciona semilla, usar la de la instancia

    // Ahora, ejecutar los tres algoritmos contruidos, y mostrar los resultados obtenidos por cada uno de ellos
    std::vector<int> random_search_solution = RandomSearch(problem, max_evaluations);
    std::vector<int> neh_solution = HeuristicNEH(problem);
    AG genetic_algorithm(problem, Pc, Pm, N, max_evaluations, k, seed);
    Individual genetic_algorithm_solution = genetic_algorithm.Run();

    std::cout << "----------------- Resultados obtenidos -----------------" << std::endl;
    std::cout << "- Algoritmo de búsqueda aleatoria: Makespan = " << problem.CalculateMakespan(random_search_solution) << std::endl;
    std::cout << "- Algoritmo heurístico NEH: Makespan = " << problem.CalculateMakespan(neh_solution) << std::endl;
    std::cout << "- Algoritmo genético: Makespan = " << genetic_algorithm_solution.makespan << std::endl;


    // Tarea 5. Estudiar los valores de los parámetros en tres instancias diferentes, y con valores de parámetros diferentes.
    // Ya están los algoritmos ejecutados, ahora, calculamos el RPD de cada uno, y envíamos los resultados al fichero de salida
    //      Primera instancia: 20x5_1. Cuatro ejecuciones (N-Pm): 30-5, 30-10, 50-5, 50-10
    //      Segunda instancia: 50x10_1. Cuatro ejecuciones (N-Pm): 30-5, 30-10, 50-5, 50-10
    //      Tercera instancia: 100x20_1. Cuatro ejecuciones (N-Pm): 30-5, 30-10, 50-5, 50-10
    
    double RPD_random_search = RPD(problem.CalculateMakespan(random_search_solution), problem.GetUB());
    double RPD_neh = RPD(problem.CalculateMakespan(neh_solution), problem.GetUB());
    double RPD_genetic_algorithm = RPD(genetic_algorithm_solution.makespan, problem.GetUB());

    std::ofstream output_file("results.txt", std::ios::app);
    
    output_file << "Instancia: " << argv[1] << std::endl;
    output_file << "Parámetros: N = " << N << ", Pc = " << Pc << ", Pm = " << Pm << ", max_evaluations = " << max_evaluations << std::endl;
    output_file << "Resultados obtenidos:" << std::endl;
    output_file << "- Algoritmo de búsqueda aleatoria: Makespan = " << problem.CalculateMakespan(random_search_solution) << ", RPD = " << RPD_random_search << std::endl;
    output_file << "- Algoritmo heurístico NEH: Makespan = " << problem.CalculateMakespan(neh_solution) << ", RPD = " << RPD_neh << std::endl;
    output_file << "- Algoritmo genético: Makespan = " << genetic_algorithm_solution.makespan << ", RPD = " << RPD_genetic_algorithm << std::endl;
    output_file << "--------------------------------------------------------" << std::endl << std::endl;


    return 0;
}
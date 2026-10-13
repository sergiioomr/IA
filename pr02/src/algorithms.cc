/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file algorithms.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-13
 * @brief Este archivo contiene la implementación de los algoritmos "externos" al algoritmo genético usados para comparar 
 * los resultados obtenidos con el algoritmo genético.
 */

#include "../include/algorithms.h"
#include <random>
#include <algorithm>
#include <ctime>

/**
 * @brief Implementación del algoritmo de búsqueda aleatoria
 * 
 * @param problem 
 * @param max_evaluations 
 * @return std::vector<int> 
 */
std::vector<int> RandomSearch(const ProblemPSFP& problem, int max_evaluations) {
  // Crear una permutación inicial ordenada y calcular su makespan
  std::vector<int> best_permutation(problem.getN());
  for (int i = 0; i < problem.getN(); i++) {
    best_permutation[i] = i;
  }

  int best_makespan = problem.CalculateMakespan(best_permutation);
  std::mt19937 generator(std::time(nullptr));
  std::vector<int> current_permutation(problem.getN());
  current_permutation = best_permutation;

  for (int i = 0; i < max_evaluations; i++) {
    std::shuffle(current_permutation.begin(), current_permutation.end(), generator);

    int current_makespan = problem.CalculateMakespan(current_permutation);

    if (current_makespan < best_makespan) {
      best_makespan = current_makespan;
      best_permutation = current_permutation;
    }
  }
  return best_permutation;
}


/**
 * @brief Implementación del algoritmo heurístico NEH
 * 
 * @param problem 
 * @return std::vector<int> 
 */
std::vector<int> HeuristicNEH(const ProblemPSFP& problem) {

}
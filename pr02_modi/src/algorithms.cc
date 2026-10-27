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


/**
 * @brief Implementación del algoritmo de búsqueda aleatoria
 * 
 * @param problem 
 * @param max_evaluations 
 * @return std::vector<int> 
 */
std::vector<int> RandomSearch(const ProblemPSFP& problem, int max_evaluations) {
  // Crear una permutación inicial ordenada y calcular su makespan
  std::vector<int> best_permutation(problem.GetN());
  for (int i = 0; i < problem.GetN(); i++) {
    best_permutation[i] = i;
  }

  int best_makespan = problem.CalculateMakespan(best_permutation);
  std::mt19937 generator(std::time(nullptr));
  std::vector<int> current_permutation(problem.GetN());
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
// Calcular los tiempos totales de procesamiento de cada trabajo
// Se almacenarán en un vector de pares <trabajo, tiempo>, donde cada trabajo irá ligado a su tiempo
  std::vector<std::pair<int, int>> processing_times(problem.GetN());
  for (int i = 0; i< problem.GetN(); i++) {
    // Calcular el tiempo total de cada trabajo i
    int total = 0;
    for (int j = 0; j < problem.GetM(); j++) {
      total += problem.GetProcessingTime(i, j);
    }
    processing_times[i].first = i;
    processing_times[i].second = total;
  }

  // Ahora, ordenamos ese vector en sentido decreciente con el Selection Sort
  for (size_t i = 0; i < processing_times.size(); i++) {
    int max = i;

    for (size_t j = i + 1; j < processing_times.size(); j++) {
      if (processing_times[j].second > processing_times[max].second) {
        max = j;
      }
    }

    std::pair<int, int> aux = processing_times[max];
    processing_times[max] = processing_times[i];
    processing_times[i] = aux;
  }

  // Crear el vector con el primer de los trabajos, que no tendrá que comprobar donde se inserta. Después, a partir del segundo si, por eso
  // los añadimos dentro de un bucle interno
  std::vector<int> current_solution;
  current_solution.push_back(processing_times[0].first);
  int best_makespan = 0;

  for (size_t i = 1; i < processing_times.size(); i++) {
    int current_job = processing_times[i].first; 
    int best_position = -1;

    // Comprobar la mejor posición en la solución actual para el trabajo i
    for (size_t j = 0; j <= i; j++) {
      // Primero. Insertamos en la primera posición, después, j irá aumentando y se irá insertando en las siguientes
      current_solution.insert(current_solution.begin() + j, current_job);

      // Segundo. Calcular el makespan, para ver si es mejor del que ya tenemos
      int temporal_makespan = problem.CalculateMakespan(current_solution);

      // Tercero. Comparamos el makespan de la iteración con el mejor. Si mejora, guardamos la posición y el makespan
      //          También lo haremos si es la primera iteración, para tener un valor inicial válido. 
      if (j == 0 || temporal_makespan < best_makespan) {
        best_makespan = temporal_makespan;
        best_position = j;
      }

      // Por último, eliminar el elemento del vector para que en la siguiente iteración no aparezca repetido
      current_solution.erase(current_solution.begin() + j);
    }

    // Una vez comprobardas todas las posiciones para el trabajo actual i, lo insertamos en la mejor
    current_solution.insert(current_solution.begin() + best_position, current_job);
  }
  return current_solution;
}

/**
 * @brief Retorna el valor de la desviación porcentual relativa, para un makespan dado. 
 * 
 * @param best_makespan 
 * @param UB 
 * @return double 
 */
double RPD(int best_makespan, int UB) {
  if (UB == 0) {
    return 0.0; // Evitar división por cero
  }

  double rpd = 100.0 * (best_makespan - UB) / UB;
  return rpd;
}
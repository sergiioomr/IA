/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file GeneticAlgorithm.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-16
 * @brief Definición de la clase AG (Algoritmo Genético) para resolver el problema PSFP.
 */

#include "../include/GeneticAlgorithm.h"

/**
 * @brief Inicializar la población con 99 individuos aleatorios y uno generado con la heurística NEH.
 *        Retornará la población ya creada. 
 * 
 * @return std::vector<Individual> 
 */
std::vector<Individual> AG::InitializePopulation() {
  std::vector<Individual> population;

  // Crear el primero de los N individuos con la heurística NEH
  Individual neh_individual;
  neh_individual.permutation = HeuristicNEH(instancia_);
  neh_individual.makespan = instancia_.CalculateMakespan(neh_individual.permutation);
  population.push_back(neh_individual);

  // Ahora, hay que añadir N-1 individuos aletorios más a la población P
  // Primero, crear una permutación inicial ordenadar sobre la que mezclar los elementos aleatoriamente
  std::vector<int> initial_permutation(instancia_.getN());
  for (int i = 0; i < instancia_.getN(); i++) {
    initial_permutation[i] = i;
  }

  // Ahora, generar los N-1 elementos de la población a partir de la permutación ordenada
  for (int i = 0; i < N_ - 1; i++) {
    Individual random_individual;
    random_individual.permutation = initial_permutation;
    std::shuffle(random_individual.permutation.begin(), random_individual.permutation.end(), generator_);
    random_individual.makespan = instancia_.CalculateMakespan(random_individual.permutation);
    population.push_back(random_individual);
  }
  
  return population;
}


/**
 * @brief Recibe la población, y realiza el método de selección por torneo para escoger y retornar a un individuo de P.
 * 
 * @return Individual
 */
Individual AG::SeleccionTorneo(const std::vector<Individual> &population) {
  // Elegir primero a uno de los k individuos aleatoriamente, y después, ir generando y comparando con este primero
  int best_index = generator_() % N_;

  for (int i = 1; i < k_; i++) {
    int random_index = generator_() % N_;
    if (population[random_index].makespan < population[best_index].makespan) {
      // Si el makespan mejora al mejor actual, quedarnos con este
      best_index = random_index;
    }
  }

  return population[best_index];
}

/**
 * @brief Recibe dos individuos, y según una probabilidad pc, realizará un cruce entre estos, retornando el resultado del cruce o a los propios padres sino ocurre
 *        Este cruce es el cruce OX. 
 * @param p1 
 * @param p2 
 * @return std::pair<Individual, Individual> 
 */
std::pair<Individual, Individual> AG::CruceOX(const Individual &p1, const Individual &p2) {

}

/**
 * @brief Recibe a un individuo, y según una probabilidad pm, lo mutará usando el método inserción y lo retornará.
 *        Este método inserción consiste en extraer el trabajo de la posición i e insertarlo en j, desplazando todos los intermedios.
 * 
 * @param p 
 * @return Individual 
 */
Individual AG::Mutacion(const Individual &p) {

}

/**
 * @brief Recibe dos poblaciones, vectores de individuos, y las reemplazará, utilizando un reemplazo con elitismo.
 *        Esto es, el mejor individuo de la población anterior sustituirá al peor de la nueva si es mejor que él. 
 *        Se retornará la nueva población.
 * 
 * @param P1 
 * @param P2 
 * @return std::vector<Individual>
 */
std::vector<Individual> AG::ReemplazoPoblacion(const std::vector<Individual> &P1, const std::vector<Individual> &P2) {

}
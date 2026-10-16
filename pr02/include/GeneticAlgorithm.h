/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * 
 * @file GeneticAlgorithm.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-16
 * @brief 
 */

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "ProblemPSFP.h"
#include "algorithms.h"

// Struct para representar a un invididuo
struct Individual {
    std::vector<int> permutation;
    int makespan;
};


class AG {
  public:
  // Constructor
  // Inicializamos el generador con la semilla de la instancia. Así, no hay que crear un generador local en cada método que use datos aleatorios
    AG(const ProblemPSFP &problem, int pc, int pm, int N, int max_evaluations, int seed) : 
      instancia_(problem), pc_(pc), pm_(pm), N_(N), max_evaluations_(max_evaluations), generator_(seed) {}

    std::vector<int> Run();

  private:
    // Atributos
    ProblemPSFP instancia_;
    int pc_;
    int pm_;
    int N_;
    int max_evaluations_;
    std::mt19937 generator_;
    
    // Métodos
    std::vector<Individual> InitializePopulation();
    Individual SeleccionTorneo(const std::vector<Individual> &population);
    std::pair<Individual, Individual> CruceOX(const Individual &p1, const Individual &p2);
    Individual Mutacion(const Individual &p);
    std::vector<Individual> ReemplazoPoblacion(const std::vector<Individual> &P1, const std::vector<Individual> &P2);
};

#endif // GENETICALGORITHM_H
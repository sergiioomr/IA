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
#include <cassert>
#include <iostream>

// Struct para representar a un invididuo
struct Individual {
    std::vector<int> permutation;
    int makespan;
    double prob_seleccion = 0.0;
};


class AG {
  public:
  // Constructor
  // Inicializamos el generador con la semilla de la instancia. Así, no hay que crear un generador local en cada método que use datos aleatorios
    AG(const ProblemPSFP &problem, int pc, int pm, int N, int max_evaluations, int k, int seed, int s = 1.5, int metodo = 0) : 
      instancia_(problem), pc_(pc), pm_(pm), N_(N), max_evaluations_(max_evaluations), k_(k), generator_(seed), s_(s), metodo_seleeccion_(metodo) {}

    Individual Run();

  private:
    // Atributos
    ProblemPSFP instancia_;
    int pc_; // Probabilidad de cruce
    int pm_; // Probabilidad de mutación
    int N_; // Tamaño de las poblaciones
    int max_evaluations_; // Número de evaluaciones a ejecutar en el algoritmo
    int k_; // Parámetro que determina entre cuantos individuos se realiza el torneo de selección
    double s_; // Parámetro para la modificación
    int metodo_seleeccion_; // Si es 0, será por torneo, si es 1, por ranking. Por defecto será 0;
    std::mt19937 generator_;
    
    // Métodos
    std::vector<Individual> InitializePopulation();
    Individual SeleccionTorneo(const std::vector<Individual> &population);
    std::pair<Individual, Individual> CruceOX(const Individual &p1, const Individual &p2);
    void Mutacion(Individual &p);
    std::vector<Individual> ReemplazoPoblacion(const std::vector<Individual> &P1, std::vector<Individual> &P2);
    Individual GetBestIndividual(const std::vector<Individual> &P);
    bool ValidPermutation(const Individual &p);

    // Modificacion
    Individual SeleccionRankingLineal(const std::vector<Individual> &population);
    std::vector<Individual> CalcularProb(const std::vector<Individual> &population);
};

#endif // GENETICALGORITHM_H
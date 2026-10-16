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

class AG {
  public:
    AG();
    std::vector<int> Run();
  private:
    // Atributos
    ProblemPSFP instancia_;
    int pc_;
    int pm_;
    int N_;
    
    // Métodos
    std::vector<int> SeleccionTorneo();
    void CruceOX(std::vector<int> &p1, std::vector<int> &p2);
    std::vector<int> Mutacion(const std::vector<int> &permutation);
    std::vector<std::vector<int>> ReemplazoPoblacion(const std::vector<std::vector<int>> &P1, const std::vector<std::vector<int>> &P2);



};

#endif // GENETICALGORITHM_H
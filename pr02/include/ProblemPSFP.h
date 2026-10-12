/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file ProblemPSFP.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-12
 * @brief 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ProblemPSFP {
  public:
    ProblemPSFP(const std::string &filename);
    
    // Getters
    int getN() const { return n_; }
    int getM() const { return m_; }
    int getUB() const { return UB_; }

    // Método para calcular el makespan de una permutación dada
    int CalculateMakespan(const std::vector<int> &permutation) const;

  private:
    int n_;
    int m_;
    int UB_;
    std::vector<std::vector<int>> processing_times_;
};
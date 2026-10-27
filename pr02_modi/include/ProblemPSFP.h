/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file ProblemPSFP.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-12
 * @brief 
 * Este archivo contiene la implementación de la clase ProblemPSFP
 */
#ifndef PROBLEMPSFP_H
#define PROBLEMPSFP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ProblemPSFP {
  public:
    ProblemPSFP(const std::string &filename);
    
    // Getters
    int GetN() const { return n_; }
    int GetM() const { return m_; }
    int GetUB() const { return UB_; }
    int GetSeed() const { return seed_; }

    // Método para obtener el tiempo de procesamiento de un trabajo i en una máquina j
    int GetProcessingTime(int job, int machine) const;

    // Método para calcular el makespan de una permutación dada
    int CalculateMakespan(const std::vector<int> &permutation) const;

  private:
    int n_;
    int m_;
    int UB_;
    int seed_;
    std::vector<std::vector<int>> processing_times_;
};

#endif // PROBLEMPSFP_H
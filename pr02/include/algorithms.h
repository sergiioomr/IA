/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file algorithms.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-13
 * @brief Este archivo contiene los algoritmos "externos" al algoritmo genético usados para comparar 
 * los resultados obtenidos con el algoritmo genético.
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "ProblemPSFP.h"

// Algoritmos "externos" al algoritmo genético
std::vector<int> RandomSearch(const ProblemPSFP& problem, int max_evaluations);
std::vector<int> HeuristicNEH(const ProblemPSFP& problem);

#endif // ALGORITHMS_H
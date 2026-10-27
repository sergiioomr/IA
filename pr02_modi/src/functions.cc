/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * 
 * @file functions.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-18
 * @brief Implementación de las funciones externas al algoritmo.
 */

#include "../include/functions.h"
#include <iostream>

void CheckArguments(int argc, char *argv[]) {
  if (argc != 9 && argc != 10) {
    ShowHelpMessage(argv[0]);
    exit(EXIT_FAILURE);
  }
}

void ShowHelpMessage(const char *program_name) {
  std::cerr << "Uso: " << program_name << " <archivo_de_entrada> <N> <Pc> <Pm> <k> <max_evaluations>" << std::endl;
  std::cerr << "El archivo de entrada debe ser una instancia del problema PSFP del tipo taiN_M_n.fsp" << std::endl;
  std::cerr << "Parámetros:" << std::endl;
  std::cerr << "  <N>: Tamaño de las poblaciones" << std::endl;
  std::cerr << "  <Pc>: Probabilidad de cruce" << std::endl;
  std::cerr << "  <Pm>: Probabilidad de mutación" << std::endl;
  std::cerr << "  <k>: Número de individuos a comparar en el torneo de selección" << std::endl;
  std::cerr << "  <max_evaluations>: Número máximo de evaluaciones para el algoritmo aleatorio y el algoritmo genético" << std::endl;
  std::cerr << "  <s>: Parámetro s para el torneo de selección por ranking, por defecto será 0" << std::endl;
  std::cerr << "  <metodo>: Elegir el método de selección, si es 0, selección por torneo, en otro caso, será por ranking" << std::endl;
  std::cerr << "  [seed] : Semilla a utilizar, en caso de que no se proporcione una, se usará la de la instancia" << std::endl;
}

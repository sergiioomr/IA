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

#include "../include/ProblemPSFP.h"

/**
 * @brief Constructor de la clase ProblemPSFP. Lee los datos del archivo y los almacena en los atributos de la clase.
 * 
 * @param filename 
 */
ProblemPSFP::ProblemPSFP(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // Ignorar la primera línea, que es una cabecera
    std::string IgnoredLine;
    std::getline(file, IgnoredLine);

    // Ahora, leer n, m y UB
    // Hay algunos valores que no interesan, guardamos n, m y UB en los atributos, el resto en las siguientes variables, pero no se usan
    int seed, lower_bound;
    file >> n_ >> m_ >> seed >> UB_ >> lower_bound;

    std::getline(file, IgnoredLine); // Ignorar el resto de la línea
    std::getline(file, IgnoredLine); // Ignorar la siguiente cabecera

    // Ahora, redimensionar la matriz de tiempos de procesamiento y leer los valores
    processing_times_.resize(m_, std::vector<int>(n_));
    for (int i = 0; i < m_; ++i) {
        for (int j = 0; j < n_; ++j) {
            file >> processing_times_[i][j];
        }
    }
}

/**
 * @brief Calcula el makespan para una permutación dada
 * 
 * @param permutation 
 * @return int 
 */
int ProblemPSFP::CalculateMakespan(const std::vector<int> &permutation) const {
  // No utilizar la n del problema completo, ya que, al calcular la heurística NEH, e ir calculando el makespan de permutaciones parciales,
  //  el tamaño de esta puede ser menor que la n del problema, por eso, usamos el tamaño de la permutación que se nos pasa
  int current_n = permutation.size();

  // Usar una matriz auxiliar, inicializada a cero, para ir rellenandola, la casilla de abajo a la derecha quedará tras rellenarla con el valor del makespan
  std::vector<std::vector<int>> C(m_ + 1, std::vector<int>(current_n + 1, 0));
  // Ahora, ir rellénandola
  for (int i = 1; i < m_+1 ; i++) {
    for (int j = 1; j < current_n + 1; j++) {
      int up_cell = C[i-1][j];
      int left_cell = C[i][j-1];
      if (up_cell >= left_cell) {
        C[i][j] = up_cell + processing_times_[i-1][permutation[j-1]];
      } else {
        C[i][j] = left_cell + processing_times_[i-1][permutation[j-1]];
      }
      
    }
  }

  return C[m_][current_n];
}


/**
 * @brief Obtiene el tiempo de procesamiento de un trabajo en una máquina
 * 
 * @param job 
 * @param machine 
 * @return int 
 */
int ProblemPSFP::GetProcessingTime(int job, int machine) const {
  return processing_times_[machine][job];
}

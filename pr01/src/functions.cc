/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 * 
 * @file functions.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-28
 * @brief 
 */

#include "../include/functions.h"

Grid MakeGrid(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error. No pudo abrirse el archivo " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::vector<std::vector<State>> matrix;
  int rows, cols;
  std::pair<int, int> start, end;

  // Contadores para asegurarme de que siempre haya un solo final y un solo inicio. 
  int counter_end = 0;
  int counter_start = 0;
  std::string line;
  int row_number = 0;


  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    // Ahora la línea de enteros separados por espacio está en ese "flujo de datos", podré ir sacando uno a uno
    std::stringstream ss(line);

    std::vector<State> row;
    int coste;
    int col_number = 0;

    // Mientras podamos seguir extrayendo valores (enteros) del flujo, vamos creando sus respectivos States
    while (ss >> coste) {
      State state;
      state.cost_ = coste;
      state.coord_ = std::make_pair(row_number, col_number);
      state.parent_coords = {-1, -1};

      row.push_back(state);
      col_number++;

      if (coste == 0) {
        start = state.coord_;
        counter_start++;                         
      }

      if (coste == 10) {
        end = state.coord_;
        counter_end++;
      }
    }

    // Ahora ya tenemos la primera fila añadida, así que la insertamos, comprobando antes que no esté vacía
    if (!row.empty()) {
      matrix.push_back(row);
      row_number++;
    }
  }

  // Ahora, hay que guardar las dimensiones de la matriz en las referencias a enteros pasadas por parámetro
  rows = static_cast<int>(matrix.size());

  // Asegurar primero que se añadió al menos una fila, porque sino al acceder a matrix[0] estando vacía, dará un error
  if (rows > 0) {
    cols = static_cast<int>(matrix[0].size());
  } else {
    cols = 0;
  }

  // Asegurar que haya un final y un inicio, exactamente uno.
  if (counter_end != 1 ) {
    std::cerr << "Error en el formato de la matriz de entrada. Debe haber exactamente una casilla de final, ni más ni menos." << std::endl;
    exit(EXIT_FAILURE);
  }

  if (counter_start != 1) {
    std::cerr << "Error en el formato de la matriz de entrada. Debe haber exactamente una casilla de inicio, ni más ni menos" << std::endl;
    exit(EXIT_FAILURE);
  }

  Grid grid(matrix, rows, cols, start, end);

  return grid;
}

void PrintSolution(Grid &grid, const std::vector<State> &solution, const std::string &filename) {
  
  std::ofstream file{filename};

  int rows = grid.GetNRow();
  int cols = grid.GetNCol();
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::pair<int, int> position = {i, j};

      // Comprobar si es una solución
      bool is_solution = false;
      for (size_t k = 0; k < solution.size(); k++) {
        if (solution[k].coord_ == position) {
          is_solution = true;
          break;
        }
      }

      if (is_solution) {
        std::cout << " * ";
        file << " * ";
      } else {
        std::cout << " " << grid.GetState(position.first, position.second).cost_ << " ";
        file << " " << grid.GetState(position.first, position.second).cost_ << " ";
      }
    }
    std::cout << std::endl;
    file << std::endl;
  }
}

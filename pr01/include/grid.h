/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * 
 * @file grid.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-24
 * @brief 
 */

#ifndef GRID_H
#define GRID_H

#include "state.h"
#include <iostream>
#include <utility>
#include <vector>

class Grid {
	public:
	// Constructors
		Grid() = default; // Default
		Grid(const std::vector<std::vector<State>> &grid, int n_row, int n_col, const std::pair<int, int> &start, const std::pair<int, int> &end) 
		: grid_(grid), n_row_(n_row), n_col_(n_col), start_(start), end_(end) {}
		
	// Getters
		int GetNCol() const { return n_col_; }
		int GetNRow() const { return n_row_; }
		std::pair<int, int> GetStart() const { return start_; }
		std::pair<int, int> GetEnd() const { return end_; }

		bool IsValid(int row, int col) const;

		// El método retorna una referencia, para poder modificar los atributos de los estados directamente desde el algoritmo
		State& GetState(const int row, const int col);

	private:
		std::vector<std::vector<State>> grid_{}; // The grid
		int n_row_ = 0;
		int n_col_ = 0;
		std::pair<int, int> start_{-1, -1};
		std::pair<int, int> end_{-1, -1};
};

#endif // GRID_H
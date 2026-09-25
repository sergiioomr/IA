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
		Grid() : grid_{}, n_col_{}, n_row_{} {} // Default
		Grid(const std::vector<std::vector<State>> &grid, const int n_col, const int n_row) : grid_(grid), n_col_(n_col), n_row_(n_row) {}
		
	// Getters
		int GetNCol() const { return n_col_; }
		int GetNRow() const { return n_row_; }

		bool IsValid(int row, int col) const;

	private:
		std::vector<std::vector<State>> grid_; // The grid
		int n_col_;
		int n_row_;
};

#endif // GRID_H
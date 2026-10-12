/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * 
 * @file grid.h
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-24
 * @brief Archivo para declarar la clase Grid. Esta será utilizada como el "tablero" del juego.
 * 				Consta de una matriz de estados, y atributos para acceder a tamaños y casillas inicial y final. 
 * 				Tiene métodos para acceder a atributos, comprobar si una casilla es válida y devolver un estado, por referencia, 
 * 				para poder hacer modificaciones en los estados desde fuera. 
 */

#ifndef GRID_H
#define GRID_H

#include "state.h"
#include <iostream>
#include <utility>
#include <vector>

class Grid {
	public:
	// Constructores
		Grid() = default; 
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
		std::vector<std::vector<State>> grid_{}; 
		int n_row_ = 0;
		int n_col_ = 0;
		std::pair<int, int> start_{-1, -1};
		std::pair<int, int> end_{-1, -1};
};

#endif // GRID_H
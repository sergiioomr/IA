/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * @asignatura
 * @file simulator.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-27
 * @brief 
 */

#include "../include/simulator.h"

int Simulator::FunctionG(const State &state) {
  // If the actual state is the inicial state, it g cost is always 0
  if (state.coord_ == grid_.GetStart()) {
    return 0;
  }
  
  // In other case
  int cost = grid_.GetState(state.parent_coords.first, state.parent_coords.second).g;
  return cost + state.cost_;  
}

int Simulator::Heuristic(const State &state) {       
  int dist_fil = std::abs(grid_.GetEnd().first - state.coord_.second);
  int dist_col = std::abs(grid_.GetEnd().second - state.coord_.first);

  return 2 * (dist_fil + dist_col);
}

int Simulator::FunctionF(const int g, const int h) {
  return g + h;
}

int Simulator::GetBestNode() {
  int best_f = open_[0].cost_;
  int index = 0;
  for (int i = 1; i < open_.size(); i++) {
    if (open_[i].cost_ < best_f) {
      best_f = open_[i].cost_;
      index = i;
    }
  }
}

bool Simulator::InClosed(const std::pair<int, int> &coord) {
  for (size_t i = 0; i < closed_.size(); i++) {
    if (closed_[i].coord_ == coord) {
      return true;
    }
  }

  return false;
}

void Simulator::Algorithm() {
  // 1. Start at the initial state
  State &initial = grid_.GetState(grid_.GetStart().first, grid_.GetStart().second);
  initial.g = 0;
  initial.h = Heuristic(initial);
  initial.f = initial.g + initial.h;

  open_.push_back(initial);

  // 2. Add to the open vector the possible states
  while (!open_.empty()) {
    
    // Coger el nodo con menor f de la lista de nodos abiertos y eliminarlo de esta. Añadirlo a la de cerrados
    int index = GetBestNode();
    State next_state = open_[index];
    open_.erase(open_.begin() + index);
    closed_.push_back(next_state);

    // Comprobar si este nodo es el final
    if (next_state.coord_ == grid_.GetEnd()) {
      Solution(next_state);
      return;
    }

    // Sino es el objetivo, obtener los 4 posibles nuevos estados
    std::vector<std::pair<int, int>> possible_moves = {
      robot_.MoveRight(next_state),
      robot_.MoveLeft(next_state),
      robot_.MoveUp(next_state),
      robot_.MoveDown(next_state)
    };

    // Ahora, hay que evaluar cada uno de estos nuevos estados, si sus coordenadas son válidas, y si lo son, actualizar sus costes
    for (int i = 0; i < 4; i++) {
      // Si está fuera o es un obstáculo se ignora el estado
      if (!grid_.IsValid(possible_moves[i].first, possible_moves[i].second)) {
        continue;
      }

      // Una vez vemos que esas coordenadas son válidas, obtenemos una referencia del estado real con esas coordenadas en el tablero, para poder hacer modificaciones sobre sus atributos
      State& new_state = grid_.GetState(possible_moves[i].first, possible_moves[i].second);
      
      // Si está en la lista de cerrados, es que ya se ha mirado, así que se ignora
      if (InClosed(new_state.coord_)) {
        continue;
      }

      // Sino, calculamos su función f
      Heuristic(new_state);
      FunctionG(new_state);
      FunctionF(new_state.h, new_state.g);

      
    }


    State right = grid_.GetState(robot_.MoveRight(next_state).first, robot_.MoveRight(next_state).second);
    State left = grid_.GetState(robot_.MoveLeft(next_state).first, robot_.MoveLeft(next_state).second);
    State up = grid_.GetState(robot_.MoveUp(next_state).first, robot_.MoveUp(next_state).second);
    State down = grid_.GetState(robot_.MoveDown(next_state).first, robot_.MoveDown(next_state).second);
      
    // Ahora, ya tengo las coordenadas de los 4 movimientos/caminos posibles, sin son válidas, las añadiré al vector de abiertos, sino, al de cerrados.

  }
  // 3. Calculate the f function to make a decission
  
}
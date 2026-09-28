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

bool Simulator::InOpen(const std::pair<int, int> &coord) {
  for (size_t i = 0; i < open_.size(); i++) {
    if (open_[i].coord_ == coord) {
      return true;
    }
  }

  return false;
}

void Simulator::UpdateOpen(const State &state) {
  for (int i = 0; i < open_.size(); i++) {
    if (open_[i].coord_ == state.coord_) {
      open_[i].g = state.g;
      open_[i].f = state.f;
      open_[i].parent_coords = state.parent_coords;
      break;
    }
  }
}

/**
 * @brief That method run the main loop of the A* algorithm
 * 
 */
void Simulator::Algorithm() {
  // 1. Empezar en el estado inicial. Poner todos los parámetros de este nodo y añadir a abiertos.
  State &initial = grid_.GetState(grid_.GetStart().first, grid_.GetStart().second);
  initial.g = 0;
  initial.h = Heuristic(initial);
  initial.f = FunctionF(initial.h, initial.g);

  // El nodo inicial nunca tendrá un padre
  initial.parent_coords = {-1, -1};

  open_.push_back(initial);

  // 2. Empezar el bucle principal, mientras el vector de abiertos no quede vacío, estará ejecutándose, si llegase a terminar, significa que no existe un camino hasta el destino.
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

    // Evaluar estos nuevos estados
    for (int i = 0; i < 4; i++) {
      // Si no es válido se ingora
      if (!grid_.IsValid(possible_moves[i].first, possible_moves[i].second)) {
        continue;
      }

      // Si las coordenadas son válidas, coger una referencia del estado en el tablero para poder modificarlo
      State& new_state = grid_.GetState(possible_moves[i].first, possible_moves[i].second);
      
      // Si está en cerrados, se ignora
      if (InClosed(new_state.coord_)) {
        continue;
      }

      // Actualizar el nodo padre para que los cálculos posteriores de la función g sean correctos. Almacenar el padre antiguo
      std::pair<int, int> previous_parent = new_state.parent_coords;
      new_state.parent_coords = next_state.coord_;


      // Comprobar si está en abiertos. Si lo está, y la nueva g es menor que la anterior, se sustituirá, sino se ignorará. 
      if (InOpen(new_state.coord_)) {
        int old_g = new_state.g;
        int new_g = FunctionG(new_state);
        
        if (new_g < old_g) {
          // Cambiar el valor de g y actualizar f
          new_state.g = new_g;
          new_state.f = FunctionF(new_state.g, new_state.h);  

          // Estos datos se actualizan en el tablero, pero no en el vector de abiertos
          UpdateOpen(new_state);
        } else {
          new_state.parent_coords = previous_parent;
        } 
      } else {
      // Sino, la opción que queda es que sera un nodo nuevo, así que calculamos todos sus parámetros y se pone en abiertos
        new_state.h = Heuristic(new_state);
        new_state.g = FunctionG(new_state);
        new_state.f = FunctionF(new_state.h, new_state.g);
        new_state.parent_coords = next_state.coord_;

        open_.push_back(new_state);
      }
    }
  }

  // Si el bucle termina, es que no se encontró un camino
  std::cout <<"No hay un camino posible" << std::endl;
}
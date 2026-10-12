/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Ingeligencia Artificial
 * @file simulator.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-09-27
 * @brief Archivo que incluye la definición de los métodos de la clase Simulator
 */

#include "../include/simulator.h"

/**
 * @brief Calcula la función g de un estado. Lo hace sumando la g de su nodo padre y la del nodo actual
 * 
 * @param state 
 * @return int 
 */
int Simulator::FunctionG(const State &state) {
  // El nodo inicial siempre tendrá g = 0
  if (state.coord_ == grid_.GetStart()) {
    return 0;
  }
  
  int cost;
  if (state.coord_ == grid_.GetEnd()) {
    cost = 2;
  } else {
    cost = state.cost_;
  }

  return grid_.GetState(state.parent_coords.first, state.parent_coords.second).g + cost;
}


/**
 * @brief Calcula la función heurística. Esta sigue la siguiente fórmula: 2 * ( |num_filas - fila_actual| + |num_col - col_actual|)
 * 
 * @param state 
 * @return int 
 */
int Simulator::Heuristic(const State &state) {       
  int dist_fil = std::abs(grid_.GetEnd().first - state.coord_.first);
  int dist_col = std::abs(grid_.GetEnd().second - state.coord_.second);

  return 2 * (dist_fil + dist_col);
}


/**
 * @brief Calcula la función f. Esta sigue la siguiente fórmula: f(e) = g(e) + h(e)
 * 
 * @param g 
 * @param h 
 * @return int 
 */
int Simulator::FunctionF(const int g, const int h) {
  return g + h;
}


/**
 * @brief Método que recorre la lista de nodos abiertos, y obtiene el que menor valor de f tiene. En caso de empate, se quedará con el más antiguo de la lista. 
 * 
 * @return int 
 */
int Simulator::GetBestNode() {
  int index = 0;

  for (size_t i = 1; i < open_.size(); i++) {
    if (open_[i].f < open_[index].f) {
      index = i;
    }
  }
  return index;
}

// Modificacion
/**
 * @brief Método que busca el estado de la lista de abiertos con mayor valor de f. Ante empate, se quedará con el más antiguo
 * 
 * @return int 
 */
int Simulator::GetWorstNode() {
  int index = 0;

  for (size_t i = 1; i < open_.size(); i++) {
    if (open_[i].f > open_[i].f) {
      index = 1;
    }
  }

  return index;
}

/**
 * @brief Comprueba si un estado/par de coordenadas está en la lista de cerrados
 * 
 * @param coord 
 * @return true 
 * @return false 
 */
bool Simulator::InClosed(const std::pair<int, int> &coord) {
  for (size_t i = 0; i < closed_.size(); i++) {
    if (closed_[i].coord_ == coord) {
      return true;
    }
  }

  return false;
}


/**
 * @brief Comprueba si un estado/par de coordenadas está en la lista de abiertos
 * 
 * @param coord 
 * @return true 
 * @return false 
 */
bool Simulator::InOpen(const std::pair<int, int> &coord) {
  for (size_t i = 0; i < open_.size(); i++) {
    if (open_[i].coord_ == coord) {
      return true;
    }
  }

  return false;
}


/**
 * @brief Actualiza los valores de un nodo que está en abiertos, que ha sido modificado. 
 * 
 * @param state 
 */
void Simulator::UpdateOpen(const State &state) {
    for (size_t i = 0; i < open_.size(); i++) {
    if (open_[i].coord_ == state.coord_) {
      open_[i].g = state.g;
      open_[i].f = state.f;
      open_[i].parent_coords = state.parent_coords;
      break;
    }
  }
}


/**
 * @brief Se encarga de imprimir una iteración con el formato solicitado
 * 
 * @param iter 
 * @param out 
 */
void Simulator::PrintIteration(int iter, std::ostream &out) const {
  out << "Iteración " << iter << "\n-----------\n";

  out << "Abiertos: = ";
  for (size_t i = 0; i < open_.size(); i++) {
    if (i > 0) {
      out << ", "; 
    }

    out << "(" << open_[i].coord_.first + 1 << ", " << open_[i].coord_.second + 1 << ")";
  }

  out << std::endl;
  out << "Cerrados = ";
  for (size_t i = 0; i < closed_.size(); i++) {
    if (i > 0){
      out << " ";
    }

    out << "(" << closed_[i].coord_.first + 1 << ", " << open_[i].coord_.second + 1 << ")";
  }

  out << "\n------------------------\n";
}


/**
 * @brief Se encarga de imprimir la solución en formato (r1, c1) -> (r2, c2) -> (r3, c3) -> ... Y añade el coste total del camino
 * 
 * @param state 
 * @param out 
 */
void Simulator::PrintPath(const State &state, const std::string &filename) {
  std::ofstream out(filename);
  out;

  out << "Camino: ";
  for (size_t i = 0; i < solution_.size(); i++) {
    if (i > 0) {
      out << " -> ";
    }
    out << "(" << solution_[i].coord_.first + 1 << ", " << solution_[i].coord_.second + 1 << ")";
  }

  // Imprimir el coste final del camino
  out << "\nCoste: " << state.g << std::endl;
}



/**
 * @brief Se encarga de simular el algoritmo A*
 * 
 */
State Simulator::Algorithm(std::ofstream &file) {
  // Se empieza en el estado inicial. Poner todos los parámetros de este nodo y añadir a abiertos.
  State &initial = grid_.GetState(grid_.GetStart().first, grid_.GetStart().second);
  initial.g = 0;
  initial.h = Heuristic(initial);
  initial.f = FunctionF(initial.h, initial.g);

  // El nodo inicial nunca tendrá un padre, por tanto ponemos unas coordenadas "nulas"
  initial.parent_coords = {-1, -1};

  int iteration = 0;
  open_.push_back(initial);

  // PrintIteration(iteration, std::cout);
  PrintIteration(iteration, file);

  // Empieza el bucle principal, mientras el vector de abiertos no quede vacío, estará ejecutándose, si llega a terminar, significa que no existe un camino hasta el destino.
  while (!open_.empty()) {
    iteration++;
    int index;
    State next_state;
    std::vector<int> elegir_aleatorio;

    // abiertos nunca tendrá 0 elementos, sino el bucle acabaría. Si tiene un solo elemento, me quedo simplemente con ese. 
    if (open_.size() == 1) {
      // Me quedo con el primer y único elemento
      index = 0;
      next_state = open_[index];
      // Lo elimino de abiertos y lo pongo en cerrados
      open_.erase(open_.begin() + index);
      closed_.push_back(next_state);
    } else {
      index = rand() % 2;
      // En caso de que hayan dos o más elementos, buscaré el mejor y el peor y los añadiré al vector
      int best_index = GetBestNode();
      elegir_aleatorio.push_back(best_index);
      int worst_index = GetWorstNode();
      elegir_aleatorio.push_back(worst_index);

      // Ahora, cogeré un número aleatorio entre 0 y 1
      index = rand() % 2;

      std::cout << "valor de index: " << index << std::endl;

      // Ahora, con ese número, podré elegir cuál será el estado siguiente
      next_state = open_[elegir_aleatorio[index]];

      // Se elimina de abiertos y se introduce en cerrados
      open_.erase(open_.begin() + elegir_aleatorio[index]);
      closed_.push_back(next_state);
    }

    // En este punto, ya tenemos elegido aleatoriamente cual será el siguiente estado, así que procede el algoritmo
    
    // Comprobar si es el final
    if (next_state.coord_ == grid_.GetEnd()) {
      //PrintIteration(iteration, std::cout);
      PrintIteration(iteration, file);
      return next_state;
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

      // Actualizar el estado padre para que los cálculos posteriores de la función g sean correctos. Almacenar el padre antiguo
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
      // Sino, la opción que queda es que sera un estado nuevo, así que calculamos todos sus parámetros y se pone en abiertos
        new_state.h = Heuristic(new_state);
        new_state.g = FunctionG(new_state);
        new_state.f = FunctionF(new_state.h, new_state.g);
        new_state.parent_coords = next_state.coord_;

        open_.push_back(new_state);
      }
    }
    std::cout << "fin iteración n: " << iteration << std::endl;
    //PrintIteration(iteration, std::cout);
    PrintIteration(iteration, file);
  }

  // Si el bucle termina, es que no se encontró un camino. Se retornará un estado con coordenadas -2 para indicar en el main que no había solución
  std::cout <<"No hay un camino posible" << std::endl;
  file << "No hay camino posibles" << std::endl;

  State error;
  error.coord_ = {-2, -2};
  return error;
}


/**
 * @brief A partir del nodo final, obtenido del método Algorithm(), se calculará la solución volviendo hacia atrás y se pondrá en el vector solution. 
 * 
 * @param state 
 */
void Simulator::Solution(const State &state) {
  solution_.clear();

  State current = state;

  // Ahora, en bucle, ir viendo el padre de cada nodo hasta que este tenga coordenadas {-1, -1}
  while (current.parent_coords != std::make_pair(-1, -1)) {
     // Insertar por delante
     solution_.insert(solution_.begin(), current);

     // Mover el estado al padre
     current = grid_.GetState(current.parent_coords.first, current.parent_coords.second);
  }

  // Insertar el primer nodo de la solución
  solution_.insert(solution_.begin(), current);
}
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file GeneticAlgorithm.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-16
 * @brief Definición de la clase AG (Algoritmo Genético) para resolver el problema PSFP.
 */

#include "../include/GeneticAlgorithm.h"

/**
 * @brief Inicializar la población con 99 individuos aleatorios y uno generado con la heurística NEH.
 *        Retornará la población ya creada. 
 * 
 * @return std::vector<Individual> 
 */
std::vector<Individual> AG::InitializePopulation() {
  std::vector<Individual> population;

  // Crear el primero de los N individuos con la heurística NEH
  Individual neh_individual;
  neh_individual.permutation = HeuristicNEH(instancia_);
  neh_individual.makespan = instancia_.CalculateMakespan(neh_individual.permutation);
  population.push_back(neh_individual);

  // Ahora, hay que añadir N-1 individuos aletorios más a la población P
  // Primero, crear una permutación inicial ordenadar sobre la que mezclar los elementos aleatoriamente
  std::vector<int> initial_permutation(instancia_.getN());
  for (int i = 0; i < instancia_.getN(); i++) {
    initial_permutation[i] = i;
  }

  // Ahora, generar los N-1 elementos de la población a partir de la permutación ordenada
  for (int i = 0; i < N_ - 1; i++) {
    Individual random_individual;
    random_individual.permutation = initial_permutation;
    std::shuffle(random_individual.permutation.begin(), random_individual.permutation.end(), generator_);
    random_individual.makespan = instancia_.CalculateMakespan(random_individual.permutation);
    population.push_back(random_individual);
  }
  
  return population;
}


/**
 * @brief Recibe la población, y realiza el método de selección por torneo para escoger y retornar a un individuo de P.
 * 
 * @return Individual
 */
Individual AG::SeleccionTorneo(const std::vector<Individual> &population) {
  // Elegir primero a uno de los k individuos aleatoriamente, y después, ir generando y comparando con este primero
  int best_index = generator_() % N_;

  for (int i = 1; i < k_; i++) {
    int random_index = generator_() % N_;
    if (population[random_index].makespan < population[best_index].makespan) {
      // Si el makespan mejora al mejor actual, quedarnos con este
      best_index = random_index;
    }
  }

  return population[best_index];
}

/**
 * @brief Recibe dos individuos, y según una probabilidad pc, realizará un cruce entre estos, retornando el resultado del cruce o a los propios padres sino ocurre
 *        Este cruce es el cruce OX. 
 * @param p1 
 * @param p2 
 * @return std::pair<Individual, Individual> 
 */
std::pair<Individual, Individual> AG::CruceOX(const Individual &p1, const Individual &p2) {
  // 1. Generar los dos puntos de corte a <= b
  int a = generator_() % p1.permutation.size();
  int b = generator_() % p2.permutation.size();

  if (a > b) {
    std::swap(a, b);
  }

  // 2. Inicializar los dos hijos a -1
  std::vector<int> h1(p1.permutation.size(), -1);
  std::vector<int> h2(p2.permutation.size(), -1);

  // 3. Copiar el tramo a-b en las mismas posiciones
  for (int i = a; i <= b; i++) {
    h1[i] = p1.permutation[i];
    h2[i] = p2.permutation[i];
  }


  // 4. Rellenar los elementos restantes de h1 con p2, y de h2 con p1
  for (int i = 0; i < p1.permutation.size(); i++) {
    int element_p2 = p2.permutation[i];
    int element_p1 = p1.permutation[i];
    bool find_p2 = false;
    bool find_p1 = false;

    // Mirar si el elemento de p2 y se encuentra en h1 y viceversa
    for (int j = 0; j < h1.size(); j++) {
      if (h1[j] == element_p2) {
        find_p2 = true;
      }
      
      if (h2[j] == element_p1) {
        find_p1 = true;
      }
    }

    // En caso de que el elemento no esté, hay que añadirlo. Buscamos el primer elemento que tenga valor -1 y se inserta ahí
    if (!find_p2) {
      for (int j = 0; j < h1.size(); j++) {
        if (h1[j] == -1) {
          h1[j] = element_p2;
          break;
        }
      }
    }

    if (!find_p1) {
      for (int j = 0; j < h2.size(); j++) {
        if (h2[j] == -1) {
          h2[j] = element_p1;
          break;
        }
      }
    }
  }

    Individual child1, child2;
    child1.permutation = h1;
    child1.makespan = instancia_.CalculateMakespan(child1.permutation);

    child2.permutation = h2;
    child2.makespan = instancia_.CalculateMakespan(child2.permutation);

    return std::make_pair(child1, child2);
}

/**
 * @brief Recibe a un individuo, y según una probabilidad pm, lo mutará usando el método inserción y lo retornará.
 *        Este método inserción consiste en extraer el trabajo de la posición i e insertarlo en j, desplazando todos los intermedios.
 * 
 * @param p 
 * @return Individual 
 */
void AG::Mutacion(Individual &p) {
  // Obtener dos índices aleatorios de la permutación
  int i = generator_() % p.permutation.size();
  int j = generator_() % p.permutation.size();

  // Asegurar que esos dos índices sean distintos. Si p tuviera solamente 1 elemento, este bucle se convertiría en infito, comprobarlo antes. 
  if (p.permutation.size() < 2) {
    return;
  }

  while (i == j) {
    j = generator_() % p.permutation.size();
  }

  // Ahora, asegurar que el índice mayor está en j
  if (j < i) {
    std::swap(i, j);
  }

  int aux = p.permutation[i];

  // Ahora, empezando en i, coger el elemento i + 1, y ponerlo en i
  for (int k = i; k < j; k++) {
    p.permutation[k] = p.permutation[k + 1];
  }

  p.permutation[j] = aux;

  // Por último, como se acaba de modificar la permutación, actualizar el nuevo makespan
  p.makespan = instancia_.CalculateMakespan(p.permutation);
}

/**
 * @brief Recibe dos poblaciones, vectores de individuos, y las reemplazará, utilizando un reemplazo con elitismo.
 *        Esto es, el mejor individuo de la población anterior sustituirá al peor de la nueva si es mejor que él. 
 *        Se retornará la nueva población.
 * 
 * @param P1 
 * @param P2 
 * @return std::vector<Individual>
 */
  std::vector<Individual> AG::ReemplazoPoblacion(const std::vector<Individual> &P1, std::vector<Individual> &P2) {
    // Buscar al mejor individuo de la población P y al peor de P'. Ya que ambos deben tener tamaño N_, aprovechar el mismo bucle para las dos búsqedas
    int best_P = 0;
    int worst_P2 = 0;
    for (int i = 0; i < P1.size(); i++) {
      if (P1[i].makespan < P1[best_P].makespan) {
        best_P = i;
      }

      if (P2[i].makespan > P2[worst_P2].makespan) {
        worst_P2 = i;
      }
    }

    // Aplicar el elitismo, si el mejor de P supera al peor de P', interacambiarlos
    if (P1[best_P].makespan < P2[worst_P2].makespan) {
      P2[worst_P2] = P1[best_P];
    }

    return P2;
  }


/**
 * @brief Método para obtener al mejor individuo de una población P
 * 
 * @param P 
 * @return Individual 
 */
Individual AG::GetBestIndividual(const std::vector<Individual> &P) {
  int best = 0;
  for (int i = 0; i < P.size(); i++) {
    if (P[i].makespan < P[best].makespan) {
      best = i;
    }
  }

  return P[best];
}


/**
 * @brief 
 * 
 * @return Individual 
 */
Individual AG::Run() {
  std::vector<Individual> P = InitializePopulation();
  int num_evaluations = 0;
  Individual best = GetBestIndividual(P);
  while (num_evaluations < max_evaluations_) {
    std::vector<Individual> new_P;
    while (new_P.size() < N_) {
      Individual p1 = SeleccionTorneo(P);
      Individual p2 = SeleccionTorneo(P);

      // Generar un número aleatorio entre 0-100. Pc estará en ese rango, si el número es menor o igual que Pc, cruzamos, sino, no.
      int random = generator_() % 100;
      Individual h1 = p1;
      Individual h2 = p2;
      if (random <= pc_) {
        std::pair<Individual, Individual> childs = CruceOX(p1, p2);
        h1 = childs.first;
        h2 = childs.second;
      }

      // Mutar h1 con probabilidad Pm. Seguir el mismo método que con el cruce
      random = generator_() % 100;
      if (random <= pm_) {
        Mutacion(h1);
      }

      random = generator_() % 100;
      if (random <= pm_) {
        Mutacion(h2);
      }

      new_P.push_back(h1);
      new_P.push_back(h2);
    }

    P = ReemplazoPoblacion(P, new_P);
    best = GetBestIndividual(P);
  }

  return best;
}
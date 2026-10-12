/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Inteligencia Artificial
 * @file main.cc
 * @author Sergio Molina Ríos (alu0101718194@ull.edu.es)
 * @date 2026-10-12
 * @brief 
 * 
 */

#include "../include/ProblemPSFP.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_de_entrada>" << std::endl;
        return EXIT_FAILURE;
    }

    ProblemPSFP problem(argv[1]);

    // Ejemplo de permutación para calcular el makespan
    std::vector<int> example_permutation(problem.getN());
    for (int i = 0; i < problem.getN(); ++i) {
        example_permutation[i] = i; // Permutación trivial: [0, 1, 2, ..., n-1]
    }

    int makespan = problem.CalculateMakespan(example_permutation);
    std::cout << "Makespan para la permutación trivial: " << makespan << std::endl;

    return EXIT_SUCCESS;
}
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 29/10/2025
// Referencias:
// Referencia -> 
// Historial de revisiones:
// 29/10/2025 - Creación (primera versión) del código
// 15/10/2025 - Segunda versión del código -> 
// 
// 16/10/2025 - Tercera versión del código -> 
// 

// ./Grammar2CNF ../data/entrada.gra ../data/salida.gra

#include <fstream>
#include <iostream>

#include "gramatica.h"

void MostrarAyuda() {
	std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra" << std::endl;
	std::cout << "Pruebe 'Grammar2CNF --help' para más información." << std::endl;

}

void MostrarError(int i = 0) {
  if (i) std::cerr << "ERROR: Archivos" << std::endl;
  else std::cerr << "ERROR: Argumentos" << std::endl;
  std::cerr << "Modo de empleo: ./p06_automata_simulator input.fa input.txt" << std::endl;
  std::cerr << "Pruebe 'p06_automata_simulator --help' para más información." << std::endl;
  exit(1);
}


int main (int argc, char* argv[]) {
	if (argc == 2 && std::string(argv[1]) == "--help") MostrarAyuda();
	else if (argc != 3) MostrarError();
	std::ifstream archivo_entrada(argv[1]);
	if (!archivo_entrada.is_open()) MostrarError(1);
	std::ofstream archivo_salida(argv[2]);
  if (!archivo_salida.is_open()) MostrarError(1);
	Gramatica grammar;
	grammar.Read(archivo_entrada);
	if(!grammar.Comprobacion()) return 1;
	grammar.FormaNormalChomsky();
	grammar.Write(archivo_salida);
	return 0;
}
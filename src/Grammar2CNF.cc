// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 29/10/2025
// Historial de revisiones:
// 29/10/2025 - Creación (primera versión) del código
// 
// 30/10/2025 - Segunda versión del código -> 

// ./Grammar2CNF ../data/entrada.gra ../data/salida.gra

#include <fstream>
#include <iostream>

#include "gramatica.h"

/**
 * @brief Muestra por pantalla el modo de uso cuando se ejecuta con el argumento "--help"
 * 
 */
void MostrarAyuda() {
	std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra" << std::endl;
	std::cout << "Pruebe 'Grammar2CNF --help' para más información." << std::endl;

}

/**
 * @brief Detecta si hay un error en argumentos o archivos y lo muestra por pantalla
 * 
 * @param i Representa el tipo de error, i = 0 para argumentos y i = 1 para archivos
 */
void MostrarError(int i = 0) {
  if (i) std::cerr << "ERROR: Archivos" << std::endl;
  else std::cerr << "ERROR: Argumentos" << std::endl;
  std::cerr << "Modo de empleo: ./p06_automata_simulator input.fa input.txt" << std::endl;
  std::cerr << "Pruebe 'p06_automata_simulator --help' para más información." << std::endl;
}

/**
 * @brief Función principal que ejecuta la transformación de gramática
 * 
 * Recibe como argumentos un archivo de entrada .gra con la definición de la gramática y 
 * otro de salida .gra con la gramática en Forma Normal de Chomsky
 * 
 * 1.- Comprueba los argumentos de entrada y muestra ayuda o error si son incorrectos.
 * 2.- Abre los archivos de entrada, y si no puede muestra un error.
 * 3.- Crea un objeto Gramatica y lo lee desde el archivo .gra
 * 4.- Comprueba que la gramática ya esté simplificada
 * 5.- Convierte la gramática a Forma Normal de Chomsky
 * 6.- Muestra la gramática en el archivo de salida
 * 
 * @param argc Número de argumentos, deben ser 3 para ejecutar el programa con normalidad
 * @param argv Array de cadenas con los argumentos del programa
 * @return int Devuelve si el programa finalizó correctamente o no
 */
int main (int argc, char* argv[]) {
	if (argc == 2 && std::string(argv[1]) == "--help") {
		MostrarAyuda();
		return 0;
	}
	else if (argc != 3) {
		MostrarError();
		return 1;
	}
	std::ifstream archivo_entrada(argv[1]);
	if (!archivo_entrada.is_open()) MostrarError(1);
	std::ofstream archivo_salida(argv[2]);
  if (!archivo_salida.is_open()) MostrarError(1);
	Gramatica grammar;
	grammar.Read(archivo_entrada);
	if(!grammar.Comprobacion()) return 1;
	grammar.FormaNormalChomsky();
	archivo_salida << grammar << std::endl;
	return 0;
}
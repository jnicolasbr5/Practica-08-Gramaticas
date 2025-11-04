// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 04/11/2025

#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <fstream>
#include <map>
#include <set>

/**
 * @brief Representa la gramática
 * 
 * Contiene el alfabeto de símbolos terminales, el conjunto de los símbolos no terminales 
 * y un multimap con las producciones.	
 * 
 * Estructura de datos principal:
 * - std::set<char> - almacena los símbolos terminales y no terminales
 * - std::multimao<char, std::string> - almacena las producciones
 */
class Gramatica {
	public:
		Gramatica() = default;

		// E/S
		void Read(std::ifstream& archivo_entrada);
		void Write(std::ostream& os);

		// Algoritmos
		bool Comprobacion();
		void FormaNormalChomsky();

		// Modificacion
		bool IsInChomskyNormalForm() const;
		
		private:
		void SustituirTerminales(char ant_terminal, char new_terminal);
		
		// Número de símbolos terminales de la gramática inicial
		int num_terminales_;
		
		// Número de símbolos no terminales de la gramática inicial
		int num_no_terminales_;
		
		// Número de producciones de la gramática inicial
		int num_producciones_;
		
		// Representa el próximo símbolo no terminal que va a ser añadido a la Forma Normal de Chomsky
		char simbolo_no_terminal_ = 'A';

		// Representa el alfabeto de símbolos terminales
		std::set<char> alfabeto_;

		// Representa el conjunto de símbolos no terminales
		std::set<char> conjunto_no_terminal_;

		// Representa las producciones de la gramática char -> std::string
		std::multimap<char, std::string> producciones_;
};

std::ostream& operator<<(std::ostream& os, Gramatica grammar);

#endif
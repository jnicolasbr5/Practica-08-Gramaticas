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

class Gramatica {
	public:
		Gramatica() = default;

		void Read(std::ifstream& archivo_entrada);
		void Write(std::ofstream& archivo_salida);
		bool Comprobacion();
		void FormaNormalChomsky();

	private:
		void SustituirTerminales(char ant_terminal, char new_terminal);
		int num_terminales_;
		int num_no_terminales_;
		int num_producciones_;
		char simbolo_no_terminal_ = 'C';

		std::set<char> alfabeto_;
		std::set<char> conjunto_no_terminal_;
		std::multimap<char, std::string> producciones_;
};

#endif
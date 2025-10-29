// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 04/11/2025


#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

#include "gramatica.h"

void Gramatica::Read(std::ifstream& archivo_entrada) {
	archivo_entrada >> num_no_terminales_;
	char simbolo_terminal;
	for (int i = 0; i < num_no_terminales_; i++) {
		archivo_entrada >> simbolo_terminal;
		alfabeto_.insert(simbolo_terminal);
	}
	archivo_entrada >> num_terminales_;
	char simbolo_no_terminal;
	for (int i = 0; i < num_no_terminales_; i++) {
		archivo_entrada >> simbolo_no_terminal;
		conjunto_no_terminal_.insert(simbolo_no_terminal);
	}
	archivo_entrada >> num_producciones_;
	archivo_entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string linea;
	while(std::getline(archivo_entrada, linea)) {
		std::istringstream ss(linea);
		ss >> simbolo_no_terminal;
		std::string produccion;
		ss >> produccion;
		producciones_.insert({simbolo_no_terminal, produccion});
	}
}

void Gramatica::Write(std::ofstream& archivo_salida) {
	archivo_salida << num_no_terminales_ << std::endl; 
	for (auto iterador = alfabeto_.begin(); iterador != alfabeto_.end(); iterador++) {
		archivo_salida << *iterador << std::endl;
	}
	archivo_salida << conjunto_no_terminal_.size() << std::endl; 
	for (auto iterador = conjunto_no_terminal_.begin(); iterador != conjunto_no_terminal_.end(); iterador++) {
		archivo_salida << *iterador << std::endl;
	}
	archivo_salida << producciones_.size() << std::endl;
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		archivo_salida << iterador->first << " " << iterador->second << std::endl;
	}
}

bool Gramatica::Comprobacion() {
	// Comprobar producciones vacias
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		if (iterador->second == "&") {
			std::cerr << "ERROR: Cadena vacía detectada" << std::endl;
			std::cerr << "La gramática no está simplificada" << std::endl;
			return false;
		}
	}

	// Comprobar producciones vacías
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		if (iterador->second.size() == 1 && isupper(iterador->second[0])) {
			std::cerr << "ERROR: Producción unitaria detectada" << std::endl;
			return false;
		}
	}
	return true;
}

void Gramatica::FormaNormalChomsky() {
	// Símbolos terminales
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) { 
		if (iterador->second.size() >= 2) {
			for (char c : iterador->second) {
				if (islower(c)) {
					Sustituir(c, simbolo_no_terminal_);
					conjunto_no_terminal_.insert(simbolo_no_terminal_);
					simbolo_no_terminal_++;					
				}
			}	
		}
	}		

	// Símbolos no terminales
}

void Gramatica::Sustituir(char antiguo_terminal, char nuevo_terminal) {
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		if (iterador->second.size() >= 2) {
			for (size_t i = 0; i < iterador->second.size(); i++) {
				if (iterador->second[i] == antiguo_terminal) {
					iterador->second[i] = nuevo_terminal;
				} 
			}
		}
	}
	producciones_.insert({nuevo_terminal, std::string(1, antiguo_terminal)});		
}
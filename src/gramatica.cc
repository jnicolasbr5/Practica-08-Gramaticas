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

/**
 * @brief Lee y carga la definición de la gramática desde un archivo de entrada
 * 
 * @param archivo_entrada Archivo .gra que contiene los datos de la gramática
 */
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

/**
 * @brief Escribe en un flujo de salida la información completa de la gramática.
 * 
 * @param os Flujo de salida donde se escribirá la información de la gramática
 */
void Gramatica::Write(std::ostream& os) {
	os << num_no_terminales_ << std::endl; 
	for (auto iterador = alfabeto_.begin(); iterador != alfabeto_.end(); iterador++) {
		os << *iterador << std::endl;
	}
	os << conjunto_no_terminal_.size() << std::endl; 
	for (auto iterador = conjunto_no_terminal_.begin(); iterador != conjunto_no_terminal_.end(); iterador++) {
		os << *iterador << std::endl;
	}
	os << producciones_.size() << std::endl;
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		os << iterador->first << " " << iterador->second << std::endl;
	}
}

/**
 * @brief Comprueba que la gramática no contenga producciones vacías ni unitarias
 * 
 * @return true La gramática está simplificada
 * @return false La gramática no está simplificada
 */
bool Gramatica::Comprobacion() {
	// Comprobar producciones vacias
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		if (iterador->second == "&") {
			std::cerr << "ERROR: Cadena vacía detectada" << std::endl;
			std::cerr << "La gramática no está simplificada" << std::endl;
			return false;
		}

		// Comprobar producciones unitarias
		if (iterador->second.size() == 1 && isupper(iterador->second[0])) {
			std::cerr << "ERROR: Producción unitaria detectada" << std::endl;
			return false;
		}
	}
	return true;
}

/**
 * @brief Aplica el algoritmo de transformación de una CFG a FNC
 * 
 * 1.- Elimina símbolos terminales de las producciones largas
 * 2.- Transforma producciones con más de 2 símbolos no terminales en un conjunto de producciones binarias
 * 
 */
void Gramatica::FormaNormalChomsky() {
	// Símbolos terminales
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) { 
		if (iterador->second.size() >= 2) { // Si n >= 2
			for (char c : iterador->second) {
				if (islower(c)) { // Si contiene un símbolo terminal
					SustituirTerminales(c, simbolo_no_terminal_); // Reemplaza por un símbolo no terminal nuevo
					conjunto_no_terminal_.insert(simbolo_no_terminal_);
					simbolo_no_terminal_++;					
				}
			}	
		}
	}		

	// Símbolos no terminales
	for (auto iterador = producciones_.begin(); iterador != producciones_.end();) { 
		if (iterador->second.size() >= 3) { // m >= 3

			// Obtengo los últimos 2 símbolos no terminales de la produccion
			std::string nuevo_no_terminal = iterador->second.substr(iterador->second.size() - 2, 2);

			// Los sustituyo en la produccion por el nuevo simbolo no terminal que contendra a ambos
			iterador->second.replace(iterador->second.size() - 2, 2, std::string(1, simbolo_no_terminal_));

			// Y creo la nueva produccion
			producciones_.insert({simbolo_no_terminal_, nuevo_no_terminal});
			conjunto_no_terminal_.insert(simbolo_no_terminal_);
			simbolo_no_terminal_++;
		}

		// Si la producción está en FNC, pasa a la siguiente, si no, vuelve a simplificar la produccion
		if (iterador->second.size() < 3) iterador++;
	}	
}

/**
 * @brief Sustituye todos los terminales que no estén solos por un nuevo símbolo no terminal que lo contiene
 * 
 * @param antiguo_terminal Símbolo terminal que va a ser sustituido
 * @param nuevo_terminal Nuevo símbolo no terminal que contiene la produccion del terminal-
 */
void Gramatica::SustituirTerminales(char antiguo_terminal, char nuevo_terminal) {
	// Creo la nueva produccion con forma C -> a
	producciones_.insert({nuevo_terminal, std::string(1, antiguo_terminal)});
	
	// Sustituyo todos los terminales por el no terminal
	for (auto iterador = producciones_.begin(); iterador != producciones_.end(); iterador++) {
		if (iterador->second.size() >= 2) {
			for (size_t i = 0; i < iterador->second.size(); i++) {
				if (iterador->second[i] == antiguo_terminal) {
					iterador->second[i] = nuevo_terminal;
				} 
			}
		}
	}
}

/**
 * @brief Sobrecarga del operador de inserción para mostrar un objeto Gramatica por el 
 * 				flujo de salida. Usa internamente el método Write
 * 
 * @param os Flujo de salida
 * @param grammar Objeto Gramatica donde se almacena la información de esta
 * @return std::ostream& Devuelve el flujo de salida
 */
std::ostream& operator<<(std::ostream& os, Gramatica grammar) {
	grammar.Write(os);
	return os;
}
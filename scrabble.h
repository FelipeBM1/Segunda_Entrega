#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

void mostrarPuntajes(const std::vector<std::string>& nombres, const std::vector<int>& puntajes);
void inicializarDiccionario(const std::string& archivo);
void iniciarDiccionarioInverso(const std::string& archivo, const std::string& salida, std::queue<std::string>& mensajes);
void toLowerCase(std::string& str);
bool esPalabraValida(const std::string& palabra, const std::string& diccionario);
bool contieneSimbolosInvalidos(const std::string& palabra);
int calcularPuntaje(const std::string& palabra);
void obtenerPuntaje(const std::string& palabra, const std::string& diccionario, const std::string& diccionarioInverso, bool simulacion);

int leerVariablePersistente();
void escribirVariablePersistente(int valor);

void mostrarAyuda();

#endif // SCRABBLE_H

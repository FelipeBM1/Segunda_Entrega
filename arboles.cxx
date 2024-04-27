//arboles.cxx
#include "arboles.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool Arboles::inicializarArbol(std::string& nombreArchivo){
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "El archivo " << nombreArchivo << " no existe o no puede ser leído." << endl;
        return false;
    }

    cout << "Inicializando el árbol del diccionario..." << endl;

    string palabra;
    while (archivo >> palabra) {
        if(esPalabraValida(palabra)){
            convertirAMinusculas(palabra, palabra.length());
            arbol.insert(palabra);
        }
    }
    return true;
}


void Arboles::buscarPalabrasPrefijo(const std::string& prefijo, std::set<std::string>& palabras) {
    std::set<std::string>::iterator it = arbol.lower_bound(prefijo);
    while (it != arbol.end() && it->find(prefijo) == 0) {
        palabras.insert(*it);
        ++it;
    }
}

void Arboles::palabrasPorPrefijo(std::string &prefijo) {
    convertirAMinusculas(prefijo, prefijo.length());
    std::set<std::string> palabras;
    buscarPalabrasPrefijo(prefijo, palabras);
    if (palabras.empty()) {
        std::cout << "(Prefijo inválido) Prefijo " << prefijo << " no pudo encontrarse en el diccionario." << std::endl;
    } else {
        std::cout << "(Resultado exitoso) Las palabras que inician con este prefijo son:" << std::endl;
        cout<<endl;
        imprimirPalabrasConPuntuaciones(palabras);
    }
}

void Arboles::imprimirPalabrasConPuntuaciones(const std::set<std::string>& palabras) {
    for (const std::string& palabra : palabras) {
        int puntuacion = PuntuacionPalabra(palabra);
        std::cout << "-> " << palabra << " - (Longitud: " << palabra.length() << ", Puntuación: " << puntuacion << ")" << std::endl;
    }
}

bool Arboles::inicializarArbolInverso(std::string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "El archivo " << nombreArchivo << " no existe o no puede ser leído." << endl;
        return false;
    }

    cout << "Inicializando el árbol del diccionario inverso..." << endl;

    string palabra;
    while (archivo >> palabra) {
        if(esPalabraValida(palabra)) {
            std::reverse(palabra.begin(), palabra.end());
            convertirAMinusculas(palabra, palabra.length());
            arbolInverso.insert(palabra);
        }
    }
    return true;
}

void Arboles::palabrasPorSufijo(std::string& sufijo) {
    convertirAMinusculas(sufijo, sufijo.length());
    std::set<std::string> palabras;
    buscarPalabrasSufijo(sufijo, palabras);
    if (palabras.empty()) {
        std::cout << "(Sufijo inválido) Sufijo " << sufijo << " no pudo encontrarse en el diccionario." << std::endl;
    } else {
        std::cout << "(Resultado exitoso) Las palabras que terminan con este sufijo son:" << std::endl;
        cout<<endl;
        imprimirPalabrasConPuntuaciones(palabras);
    }
}

void Arboles::buscarPalabrasSufijo(const std::string& sufijo, std::set<std::string>& palabras) {
    std::string sufijoInvertido = sufijo;
    std::reverse(sufijoInvertido.begin(), sufijoInvertido.end());
    std::set<std::string>::iterator it = arbolInverso.lower_bound(sufijoInvertido);
    while (it != arbolInverso.end() && it->find(sufijoInvertido) == 0) {
        std::string palabraInvertida = *it;
        std::reverse(palabraInvertida.begin(), palabraInvertida.end());
        palabras.insert(palabraInvertida);
        ++it;
    }
}

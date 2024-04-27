#ifndef ARBOLES_H
#define ARBOLES_H

#include <string>
#include <set>

class Arboles {
private:
    std::set<std::string> arbol;
    std::set<std::string> arbolInverso;

public:
    bool inicializarArbol(std::string& nombreArchivo);
    bool inicializarArbolInverso(std::string& nombreArchivo);
    void palabrasPorPrefijo(std::string &prefijo);
    void palabrasPorSufijo(std::string &sufijo);

private:
    void buscarPalabrasPrefijo(const std::string& prefijo, std::set<std::string>& palabras);
    void buscarPalabrasSufijo(const std::string& sufijo, std::set<std::string>& palabras);
    void imprimirPalabrasConPuntuaciones(const std::set<std::string>& palabras);
    bool esPalabraValida(const std::string& palabra);
    void convertirAMinusculas(std::string& palabra);
    int PuntuacionPalabra(const std::string& palabra);
};

#endif // ARBOLES_H

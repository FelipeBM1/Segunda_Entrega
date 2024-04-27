// scrabble.cxx
#include "scrabble.h"
#include "arboles.h" 
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <unistd.h> // Para usar isatty

// Incluye la librería para unordered_map
#include <unordered_map>

using namespace std;

// Definiciones de funciones aquí...


using namespace std;

unordered_map<char, int> tablaPuntuacion = {
    {'E', 1}, {'A', 1}, {'I', 1}, {'O', 1}, {'N', 1}, {'R', 1}, {'T', 1}, {'L', 1}, {'S', 1}, {'U', 1},
    {'D', 2}, {'G', 2},
    {'B', 3}, {'C', 3}, {'M', 3}, {'P', 3},
    {'F', 4}, {'H', 4}, {'V', 4}, {'W', 4}, {'Y', 4},
    {'K', 5},
    {'J', 8}, {'X', 8},
    {'Q', 10}, {'Z', 10}
};


void mostrarPuntajes(const vector<string>& nombres, const vector<int>& puntajes) {
    cout << "=== Puntajes ===" << endl;
    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << nombres[i] << ": " << puntajes[i] << " puntos" << endl;
    }
}

void inicializarDiccionario(const string& archivo) {
    try {
        ifstream inputFile(archivo);
        if (!inputFile.is_open()) {
            throw runtime_error("(Archivo no existe) El archivo " + archivo + " no existe o no puede ser leído.");
        }

        vector<string> palabrasValidas;
        string palabra;
        while (getline(inputFile, palabra)) {
            if (all_of(palabra.begin(), palabra.end(), [](char c) { return isalpha(c) || isspace(c); })) {
                palabrasValidas.push_back(palabra);
            }
        }

        inputFile.close();

        ofstream outputFile("diccionario.txt");
        for (const auto& palabra : palabrasValidas) {
            outputFile << palabra << '\n';
        }
        outputFile.close();

        cout << "(Resultado exitoso) El diccionario se ha inicializado correctamente.\n";
    } catch (const exception& e) {
        cerr << "(Error) " << e.what() << endl;
    }
}

void iniciarDiccionarioInverso(const string& archivo, const string& salida, queue<string>& mensajes) {
    try {
        ifstream inputFile(archivo);
        if (!inputFile.is_open()) {
            throw runtime_error("(Archivo no existe) El archivo " + archivo + " no existe o no puede ser leído.");
        }

        vector<string> palabrasValidas;
        string palabra;
        while (getline(inputFile, palabra)) {
            if (all_of(palabra.begin(), palabra.end(), [](char c) { return isalpha(c) || isspace(c); })) {
                reverse(palabra.begin(), palabra.end());
                palabrasValidas.push_back(palabra);
            }
        }

        inputFile.close();

        // Verificar si la salida estándar está asociada a una consola
        if (!isatty(fileno(stdout))) {
            mensajes.push("(Resultado exitoso) El diccionario inverso no se crea en la consola.\n");
            return;
        }

        ofstream outputFile(salida);
        for (const auto& palabra : palabrasValidas) {
            outputFile << palabra << '\n';
        }
        outputFile.close();

        cout << "(Resultado exitoso) El diccionario inverso se ha inicializado correctamente.\n";
    } catch (const exception& e) {
        cerr << "(Error) " << e.what() << endl;
        mensajes.push("(Error) " + string(e.what()) + "\n");
    }
}

void toLowerCase(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

bool esPalabraValida(const string& palabra, const string& diccionario) {
    ifstream diccionarioFile(diccionario);
    if (!diccionarioFile.is_open()) {
        throw runtime_error("(Archivo no existe) El archivo " + diccionario + " no existe o no puede ser leído.");
    }

    string palabraDic;
    string palabraLower = palabra;  // Crear una copia de la palabra original

    toLowerCase(palabraLower);  // Convertir la palabra a minúsculas

    while (diccionarioFile >> palabraDic) {
        toLowerCase(palabraDic);  // Convertir la palabra del diccionario a minúsculas
        if (palabraLower == palabraDic) {
            diccionarioFile.close();
            return true;
        }
    }

    return false;
}

bool contieneSimbolosInvalidos(const string& palabra) {
    try {
        if (!all_of(palabra.begin(), palabra.end(), [](char c) { return isalpha(c) || isspace(c); })) {
            throw invalid_argument("(Símbolos inválidos) La palabra contiene caracteres no permitidos.");
        }
    } catch (const exception& e) {
        cerr << "(Error) " << e.what() << endl;
        // Puedes manejar la excepción de acuerdo a tus necesidades
        return true; // o lanzar la excepción nuevamente si deseas que el programa termine
    }

    return false;
}

int calcularPuntaje(const string& palabra) {
    int puntaje = 0;
    for (char letra : palabra) {
        puntaje += tablaPuntuacion[toupper(letra)];
    }
    return puntaje;
}

void obtenerPuntaje(const string& palabra, const string& diccionario, const string& diccionarioInverso, bool simulacion) {
    if (contieneSimbolosInvalidos(palabra)) {
        cout << "(Letras inválidas) La palabra contiene símbolos inválidos.\n";
        return;
    }

    if (esPalabraValida(palabra, diccionario) || esPalabraValida(palabra, diccionarioInverso)) {
        int puntaje = calcularPuntaje(palabra);
        int tamaño = palabra.size();
        cout << "(Resultado exitoso) La palabra '" << palabra << "' tiene un puntaje de " << puntaje << " y un tamaño de " << tamaño << " caracteres.\n";
    } else {
        cout << "(Palabra no existe) La palabra no existe en el diccionario.\n";
    }
}

int leerVariablePersistente() {
    int valor;
    ifstream archivo("variable.txt");
    if (archivo.is_open()) {
        archivo >> valor;
        archivo.close();
    } else {
        valor = 0;
    }
    return valor;
}

void escribirVariablePersistente(int valor) {
    ofstream archivo("variable.txt");
    if (archivo.is_open()) {
        archivo << valor;
        archivo.close();
    } else {
        cerr << "Error: No se puede abrir el archivo para escribir la variable persistente." << endl;
    }
}

void mostrarAyuda() {
    cout << "=== ./main ayuda ===" << endl;
    cout << "Este comando de ayuda al jugador, es para ejecutar el juego en consola y que sepa cual comando debe digitar en concola:" << endl;
    cout << endl << "Comandos disponibles:" << endl;
    cout << endl << "1: ./main inicializar_diccionario" << endl;
    cout << "-> Inicializa el diccionario con las palabras del archivo especificado." << endl;
    cout << "   Este comando carga un archivo de texto que contiene un diccionario de palabras" << endl;
    cout << "   en el idioma original del juego (ingles). Las palabras deben estar escritas" << endl;
    cout << "   en un formato valido y se almacenan para su posterior uso." << endl << endl;
    cout << "2: ./main inicializar_diccionario_inverso" << endl;
    cout << "-> Inicializa el diccionario inverso con las palabras del archivo especificado." << endl;
    cout << "   Similar al comando 'inicializar', pero las palabras se almacenan en sentido" << endl;
    cout << "   inverso (leidas de derecha a izquierda), facilitando ciertas operaciones." << endl;
    cout << "-> Tambien se presenta la opcion de visualizar el diccionario inverso" << endl;
    cout << "   Esta opcion solo se puede usar despues de inicializar el diccionario inverso" << endl;
    cout << "   Lo cual permite visualizar las palabras en orden inverso" << endl << endl;
    cout << "3: ./main calcular_puntaje" << endl;
    cout << "-> Calcula el puntaje de la palabra dada." << endl;
    cout << "   Este comando determina el puntaje que se puede obtener con la palabra proporcionada," << endl;
    cout << "   utilizando las reglas de puntuación del juego Scrabble y verificando su validez en el diccionario." << endl << endl;
    cout << "4: ./main iniciar_arbol diccionario.txt" << endl;
    cout << "-> Inicializa el árbol del diccionario con las palabras del archivo especificado." << endl;
    cout << "   Similar al comando 'inicializar', pero las palabras se almacenan en un arbol de letras," << endl;
    cout << "   facilitando la busqueda de palabras por prefijo." << endl << endl;
    cout << "5: ./main iniciar_arbol_inverso diccionario.txt" << endl;
    cout << "-> Inicializa el arbol inverso del diccionario con las palabras del archivo especificado." << endl;
    cout << "   Similar al comando 'iniciar_inverso', pero las palabras se almacenan en un arbol de letras" << endl;
    cout << "   en sentido inverso, facilitando la busqueda de palabras por sufijo." << endl << endl;
    cout << "6: ./main palabras_por_prefijo prefijo" << endl;
    cout << "-> Busca todas las palabras que empiezan con el prefijo dado." << endl;
    cout << "   Muestra en pantalla todas las palabras que tienen como prefijo la cadena especificada," << endl;
    cout << "   junto con su longitud y puntuacion." << endl << endl;
    cout << "7: ./main palabras_por_sufijo sufijo" << endl;
    cout << "-> Busca todas las palabras que terminan con el sufijo dado." << endl;
    cout << "   Muestra en pantalla todas las palabras que tienen como sufijo la cadena especificada," << endl;
    cout << "   junto con su longitud y puntuacion." << endl << endl;
    cout << "8: ./main salir" << endl;
   cout << "-> Sale del programa." << endl << endl;
}

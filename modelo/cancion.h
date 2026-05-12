//
// Created by xalva on 02/03/2026.
//

#ifndef UNTITLED3_CANCION_H
#define UNTITLED3_CANCION_H

#include "string"
#include <iostream>
using namespace std;

class cancion {

    string titulo;
    string genero;
    int duracion;//en segundos


public:

    // Pre:titulo y genero no vacíos, duracion > 0
    // Post:Construye un objeto cancion  con los parametros que se han proporcionado
    // Complejidad: O(1)
    cancion(const string &titulo, const string &genero, int duracion)
        : titulo(titulo),
          genero(genero),
          duracion(duracion) {
    }
    // Pre:
    // Post:Construye una cancion con valores por defecto
    // Complejidad: O(1)
    cancion() : titulo("Sin titulo"),genero("Desconocido"),duracion(0){}
    // Pre:Un objeto cancion que exista
    // Post: Crea una copia exacta de la canción proporcionada
    // Complejidad: O(1)
    cancion(const cancion &otra) = default;
    // Pre: Un objeto cancion que exista
    // Post:Elimina el objeto y muestra el mensaje
    // Complejidad:O(1)
    ~cancion() {
        cout<<"[Cancion.h] Cancion Destruida"<< titulo<< endl;
    }
    // Pre:
    // Post: Devuelve el titulo de la cancion
    // Complejidad:O(1)
    string getTitulo() const {
        return titulo;
    }
    // Pre:titulo no vacio
    // Post:Actualiza el titulo de la cancion
    // Complejidad: O(1)
    void set_titulo(const string &titulo) {
        this->titulo = titulo;
    }
    // Pre:
    // Post:Devuelve el genero de la cancion
    // Complejidad: O(1)
    string getGenero() const {
        return genero;
    }
    // Pre:genero no vacio
    // Post:Actualiza el genero de la cancion
    // Complejidad: O(1)
    void set_genero(const string &genero) {
        this->genero = genero;
    }
    // Pre:
    // Post:Devuelve la duracion en segundos
    // Complejidad: O(1)
    int getDuracion() const {
        return duracion;
    }
    // Pre:duracion > 0
    // Post:Actualiza la duración de la canción
    // Complejidad: O(1)
    void set_duracion(int duracion) {
        this->duracion = duracion;
    }
    //Pre:
    // Post: Muestra por consola los datos de la canción (titulo, genero, duracion)
    // // Complejidad: O(1)
    void mostrar() const {
        cout << "--- Datos de la Cancion ---" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Genero: " << genero << endl;
        cout << "Duracion: " << duracion << " segundos" << endl;
        cout << "---------------------------" << endl;
    }

    //SobreCarga del operador == (Compara un titulo con otro)
    bool operator==(const cancion &otra) const {
        return this->titulo == otra.titulo;

    }

    //SobraCarga del operador < (Orden alfabetico)
    bool operator!=(const cancion &otra) const {
        return this->titulo < otra.titulo;
    }


};
#endif //UNTITLED3_CANCION_H

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
    cancion(const string &titulo, const string &genero, int duracion)
        : titulo(titulo),
          genero(genero),
          duracion(duracion) {
    }
    cancion() : titulo("Sin titulo"),genero("Desconocido"),duracion(0){}

    cancion(const cancion &otra) = default;
    ~cancion() {
        std::cout<<"[Cancion.h] Cancion Destruida"<< titulo<< endl;
    }

    string getTitulo() const {
        return titulo;
    }

    void set_titulo(const string &titulo) {
        this->titulo = titulo;
    }

    string getGenero() const {
        return genero;
    }

    void set_genero(const string &genero) {
        this->genero = genero;
    }

    int getDuracion() const {
        return duracion;
    }

    void set_duracion(int duracion) {
        this->duracion = duracion;
    }

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

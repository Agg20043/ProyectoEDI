#ifndef ARTISTA_H
#define ARTISTA_H

#include <iostream>
#include <string>
#include "ListaDPI.h"
#include "cancion.h"

using namespace std;

class Artista {
private:
    string nombre;
    string pais;
    int num_seguidores;
    
    ListaDPI<cancion*> *lCanciones;

public:
    Artista();
    Artista(const string &nombre, const string &pais, int num_seguidores); 
    Artista(const Artista& otro); 

    ~Artista();

    string get_nombre() const { return nombre; }
    void set_nombre(const string &nombre) { this->nombre = nombre; }
    string get_pais() const { return pais; }
    void set_pais(const string &pais) { this->pais = pais; }
    int get_num_seguidores() const { return num_seguidores; }
    void set_num_seguidores(int num_seguidores) { this->num_seguidores = num_seguidores; }

   
    void insertarCancion(const string& titulo, const string& genero, int duracion);
    cancion* buscarCancion(const string& titulo) const;
    int numElementos() const;
    
    void mostrar() const;

    bool operator==(const Artista& otro) const { return this->nombre == otro.nombre; }
    bool operator<(const Artista& otro) const { return this->nombre < otro.nombre; }
};

#endif

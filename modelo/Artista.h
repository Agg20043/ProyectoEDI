#ifndef ARTISTA_H
#define ARTISTA_H

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
    //Pre:
    //Post: Construye un objeto Artista por constructor por defecto
    //Complejidad: o(1)
    Artista();
    //Pre:nombre,pais y numeros de seguidores no vacios
    //Post: Construye un objeto Artista para el constructor parametrizado
    //Complejidad: o(1)
    Artista(const string &nombre, const string &pais, int num_seguidores);
    //Pre:Un objeto Artista
    //Post: Una copia exacta del objeto Artista proporcionado
    //Complejidad: o(1)
    Artista(const Artista& otro); 
    //Pre:Un objeto Artista
    //Post: elimina el objeto Artista
    //Complejidad: o(n) (n hace referencia al numero de canciones)
    ~Artista();

    //Pre:
    //Post: Getter que devuelve el nombre de un artista
    //Complejidad: o(1)
    string get_nombre() const { return nombre; }
    //Pre: Un nombre
    //Post:Actualiza el nombre del artista
    //Complejidad: o(1)
    void set_nombre(const string &nombre) { this->nombre = nombre; }
    //Pre: Un nombre
    //Post:Actualiza el nombre del artista
    //Complejidad: o(1)
    string get_pais() const { return pais; }
    void set_pais(const string &pais) { this->pais = pais; }
    int get_num_seguidores() const { return num_seguidores; }
    void set_num_seguidores(int num_seguidores) { this->num_seguidores = num_seguidores; }

   
    void insertarCancion(const string& titulo, const string& genero, int duracion);
    cancion* buscarCancion(const string& titulo) const;
    int numElementos() const;
    
    void mostrar() const;
    void incrementarSeguidores();
    void decrementarSeguidores();
    bool operator==(const Artista& otro) const { return this->nombre == otro.nombre; }
    bool operator<(const Artista& otro) const { return this->nombre < otro.nombre; }
};

#endif

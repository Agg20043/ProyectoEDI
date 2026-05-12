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
    //Pre:
    //Post: Getter que devuelve el pais de un artista
    //Complejidad: o(1)
    string get_pais() const { return pais; }
    //Pre: Un pais
    //Post: Actualiza el pais del artista
    //Complejidad: o(1)
    void set_pais(const string &pais) { this->pais = pais; }
    //Pre:
    //Post:Getter que devuelve el numero de seguidores de un artista
    //Complejidad: o(1)
    int get_num_seguidores() const { return num_seguidores; }
    //Pre: num_seguidores>=0
    //Post: Actualiza los numeros de seguidores de un artista
    //Complejidad: o(1)
    void set_num_seguidores(int num_seguidores) { this->num_seguidores = num_seguidores; }

    //Pre:titulo,genero y una duracion>0
    //Post:Inserta una cancion a la lista de artistas
    //Complejidad: o(1)
    void insertarCancion(const string& titulo, const string& genero, int duracion);
    //Pre:Titulo de la cancion a buscar
    //Post: Devuelve el puntero de la cancion si existe,en caso contrario devuelve null
    //Complejidad: o(1)
    cancion* buscarCancion(const string& titulo) const;
    //Pre:
    //Post: Devuelve la cantidad de canciones de un artista
    //Complejidad: o(1)
    int numElementos() const;
    //Pre:
    //Post: Muestra los datos del artista(canciones,pais,numero de seguidores y canciones)
    //Complejidad: o(n)
    void mostrar() const;
    //Pre:
    //Post:Incrementa el numero de seguidores
    //Complejidad: o(1)
    void incrementarSeguidores();
    //Pre: num_seguidores>0
    //Post: Decrementa el numero de seguidores
    //Complejidad: o(1)
    void decrementarSeguidores();
    //Pre:Objetos Artista
    //Post:Devuelve true si son el mismo artista
    //Complejidad: o(1)
    bool operator==(const Artista& otro) const { return this->nombre == otro.nombre; }
    //Pre:Objetos Artista
    //Post:Devuelve true si el nombre del artista es alfabeticamente menor respecto al otro artista
    //Complejidad: o(1)
    bool operator<(const Artista& otro) const { return this->nombre < otro.nombre; }
};

#endif

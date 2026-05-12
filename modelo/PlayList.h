#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "cancion.h"
#include "Cola.h"


using namespace std;

class PlayList {
    string nombre;
    int numCanciones;
    int duracion; // en segundos
    Cola<cancion*> *colaReproduccion;

public:
    // Constructores y Destructor
    PlayList();
    PlayList(string nombre);
    PlayList(const PlayList &otraPlayList);
    ~PlayList();

    // Métodos de gestión
    //Pre:La cancion no puede estar vacia
    // Post:Añade la cancion al final de la cola,incrementa el numero de canciones y suma la duracion total de la nueva cancion
    // Complejidad:0(1)
    void agregarCancion(cancion *c);
    //Pre:La cola no puede estar vacia
    // Post:elimina la cancion que esta primero en la cola (la mas vieja)
    // Complejidad:0(1)
    void eliminarCancion();
    //Pre:
    // Post:Muestra por consola el nombre de la playlist,el numero de canciones y la duracion total
    // Complejidad:0(n)
    void mostrar();

    // Métodos de reproducción
    //Pre:
    // Post:Reproduce todas las canciones de la cola (de principio a final)
    // Complejidad:0(n)
    void reproducirTodo();
    //Pre:posicion de la cola donde esta la cancion que quieres
    // Post:Salta las canciones hasta llegar ala posicion indicada
    // Complejidad:0(n)
    void reproducirDesde(int posicion);

    string getNombre() const { return nombre; }
    void setNombre(const string &n) { nombre = n; }

    int getNumCanciones() const { return numCanciones; }

    void setNumCanciones(int num) { numCanciones = num; }

    int getDuracion() const { return duracion; }
    void setDuracion(int d) { duracion = d; }
    //Pre:
    // Post:
    // Complejidad:
    Cola<cancion*> *getColaReproduccion() const { return colaReproduccion; }
    //Pre:
    // Post:
    // Complejidad:
    void setColaReproduccion(Cola<cancion*> *cola) { colaReproduccion = cola; }
};

#endif // PLAYLIST_H
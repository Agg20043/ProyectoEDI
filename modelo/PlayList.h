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
    Cola<cancion*> *colaReproduccion; // agregación con las canciones

public:
    // Constructores y Destructor
    PlayList();
    PlayList(string nombre);
    PlayList(const PlayList &otraPlayList);
    ~PlayList();

    // Métodos de gestión
    void agregarCancion(cancion *c);
    void eliminarCancion();
    void mostrar();

    // Métodos de reproducción
    void reproducirTodo();
    void reproducirDesde(int posicion);

    string getNombre() const { return nombre; }
    void setNombre(const string &n) { nombre = n; }

    int getNumCanciones() const { return numCanciones; }

    void setNumCanciones(int num) { numCanciones = num; }

    int getDuracion() const { return duracion; }
    void setDuracion(int d) { duracion = d; }

    Cola<cancion*> *getColaReproduccion() const { return colaReproduccion; }
    void setColaReproduccion(Cola<cancion*> *cola) { colaReproduccion = cola; }
};

#endif // PLAYLIST_H
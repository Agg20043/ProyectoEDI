#include "../modelo/PlayList.h"
#include <iostream>

using namespace std;


PlayList::PlayList() {
    nombre = "Sin nombre";
    numCanciones = 0;
    duracion = 0;
    colaReproduccion = new Cola<cancion*>();
}

PlayList::PlayList(string nombre) {
    this->nombre = nombre;
    numCanciones = 0;
    duracion = 0;
    colaReproduccion = new Cola<cancion*>();
}

PlayList::PlayList(const PlayList &otraPlayList) {
    this->nombre = otraPlayList.nombre;
    this->numCanciones = otraPlayList.numCanciones;
    this->duracion = otraPlayList.duracion;
    
    this->colaReproduccion = new Cola<cancion*>();
    
    // sacamos de la original, copiamos, y volvemos a meter en la original.
    for(int i = 0; i < otraPlayList.numCanciones; i++) {
        cancion* c = otraPlayList.colaReproduccion->getPrimero();
        otraPlayList.colaReproduccion->desencolar();
        
        // Lo metemos en una nueva cola
        this->colaReproduccion->encolar(c);
        
        // Lo devolvemos a la cola original para no destruirla
        otraPlayList.colaReproduccion->encolar(c);
    }
}

PlayList::~PlayList() {


    delete colaReproduccion;
}



void PlayList::agregarCancion(cancion *c) {
    if (c != nullptr) {
        colaReproduccion->encolar(c);
        numCanciones++;
        duracion += c->getDuracion();
    }
}

void PlayList::eliminarCancion() {
    if (!colaReproduccion->estaVacia()) {
        cancion* c = colaReproduccion->getPrimero();
        duracion -= c->getDuracion();
        
        colaReproduccion->desencolar();
        numCanciones--;
    }
}

void PlayList::mostrar() {
    int horas = duracion / 3600;
    int minutos = (duracion % 3600) / 60;
    int segundos = duracion % 60;

    cout << "--- PlayList: " << nombre << " ---" << endl;
    cout << "Total canciones: " << numCanciones << endl;
    cout << "Duracion total: " << horas << "h " << minutos << "m " << segundos << "s" << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < numCanciones; i++) {
        cancion* c = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        
        c->mostrar();
        cout << "-";
        
        colaReproduccion->encolar(c);
    }
}


void PlayList::reproducirTodo() {

    //Control de errores para no reproducir una playlist vacia
    if (numCanciones == 0) {
        cout << "La PlayList esta vacia." << endl;
        return;
    }

    cout << "[Reproduciendo PlayList: " << nombre << "]" << endl;

    for (int i = 0; i < numCanciones; i++) {
        cancion* actual = colaReproduccion->getPrimero();


         actual->mostrar();

        colaReproduccion->desencolar();
        colaReproduccion->encolar(actual);
    }
}

void PlayList::reproducirDesde(int posicion) {
    if (posicion < 1 || posicion > numCanciones) {
        cout << "Posicion invalida." << endl;
        return;
    }

    // Movemos la cola hasta llegar a la cancion seleccionada
    for (int i = 0; i < posicion - 1; i++) {
        cancion* temp = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        colaReproduccion->encolar(temp);
    }

    // Una vez que la cancion elegida es la primera se reproduce las demas de la lista
    reproducirTodo();

    // Devolvemos la lista a su estado original
    int rotacionesRestantes = numCanciones - (posicion - 1);
    for (int i = 0; i < rotacionesRestantes; i++) {
        cancion* temp = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        colaReproduccion->encolar(temp);
    }
}
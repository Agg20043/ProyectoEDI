#include "../modelo/PlayList.h"
#include <iostream>

using namespace std;

// --- Constructores y Destructor ---

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

// Constructor por copia (Agregación: copia la cola, no las canciones)
PlayList::PlayList(const PlayList &otraPlayList) {
    this->nombre = otraPlayList.nombre;
    this->numCanciones = otraPlayList.numCanciones;
    this->duracion = otraPlayList.duracion;
    
    // Creamos una nueva estructura de cola vacía
    this->colaReproduccion = new Cola<cancion*>();
    
    // Para copiar los elementos sin perderlos en la original, 
    // sacamos de la original, copiamos, y volvemos a meter en la original.
    for(int i = 0; i < otraPlayList.numCanciones; i++) {
        cancion* c = otraPlayList.colaReproduccion->getPrimero();
        otraPlayList.colaReproduccion->desencolar();
        
        // Lo metemos en nuestra nueva cola
        this->colaReproduccion->encolar(c);
        
        // Lo devolvemos a la cola original para no destruirla
        otraPlayList.colaReproduccion->encolar(c);
    }
}

PlayList::~PlayList() {
    // Al ser agregación, el destructor de la Cola eliminará los nodos internos,
    // pero los punteros a cancion* no harán un "delete" del objeto real.
    delete colaReproduccion;
}

// --- Métodos de Gestión ---

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

    cout << "\n=== PlayList: " << nombre << " ===" << endl;
    cout << "Total canciones: " << numCanciones << endl;
    cout << "Duracion total: " << horas << "h " << minutos << "m " << segundos << "s" << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < numCanciones; i++) {
        cancion* c = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        
        // c->mostrar();
        cout << "- "; // Imprimir algo visual
        
        colaReproduccion->encolar(c);
    }
}

// --- Métodos de Reproducción ---

void PlayList::reproducirTodo() {
    if (numCanciones == 0) {
        cout << "La PlayList esta vacia." << endl;
        return;
    }

    cout << "\n[Reproduciendo PlayList: " << nombre << "]" << endl;

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

    // 1. Rotamos la cola hasta llegar a la canción deseada
    for (int i = 0; i < posicion - 1; i++) {
        cancion* temp = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        colaReproduccion->encolar(temp);
    }

    // 2. Ahora que la canción deseada está la primera, reproducimos toda la lista
    reproducirTodo();

    // 3. Devolvemos la lista a su estado original rotando lo que falta para completar la vuelta
    int rotacionesRestantes = numCanciones - (posicion - 1);
    for (int i = 0; i < rotacionesRestantes; i++) {
        cancion* temp = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        colaReproduccion->encolar(temp);
    }
}
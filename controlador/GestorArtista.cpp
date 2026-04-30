//
// Created by xalva on 07/04/2026.
//
#include "../modelo/GestorArtista.h"
#include <iostream>

GestorArtistas::GestorArtistas() {
    lArtistas = new ListaDPI<Artista*>();
}

GestorArtistas::GestorArtistas(const GestorArtistas& otro) {
    lArtistas = new ListaDPI<Artista*>();
    otro.lArtistas->moverPrimero();
    while (!otro.lArtistas->alFinal()) {
        Artista* original = otro.lArtistas->consultar();
        Artista* copia = new Artista(*original);
        lArtistas->insertar(copia);
        otro.lArtistas->avanzar();
    }
}

GestorArtistas::~GestorArtistas() { // [cite: 25]
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        delete lArtistas->consultar();
        lArtistas->eliminar();
    }
    delete lArtistas;
}

void GestorArtistas::insertar(Artista* artista) { // [cite: 20, 21, 22]
    lArtistas->moverPrimero();
    bool existe = false;

    while (!lArtistas->alFinal()) {
        Artista* a = lArtistas->consultar();
        if (a->get_nombre() == artista->get_nombre()) {
            existe = true;
            break; // Sin duplicados [cite: 22]
        }
        if (a->get_nombre() > artista->get_nombre()) {
            break; // Inserción en orden alfabético [cite: 21]
        }
        lArtistas->avanzar();
    }

    if (!existe) {
        lArtistas->insertar(artista);
    }
}

Artista* GestorArtistas::buscar(const string& nombre) const { // [cite: 23]
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        Artista* a = lArtistas->consultar();
        if (a->get_nombre() == nombre) {
            return a;
        }
        lArtistas->avanzar();
    }
    return nullptr;
}

void GestorArtistas::mostrar() const {
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        lArtistas->consultar()->mostrar(); // Esto mostrara los artista y sus canciones
        lArtistas->avanzar();
    }
}
int GestorArtistas::numElementos() const {
    int contador = 0;
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        contador++;
        lArtistas->avanzar();
    }
    return contador;
}
void GestorArtistas::mostrarTop() const {

    if (lArtistas->estaVacia()) {
        cout << "No hay artistas en el sistema." << endl;
        return;
    }


    int maxSeguidores = 0;
    Artista* artistaTop = nullptr;

    // Recorremos la estructura para buscar el máximo
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        Artista* a = lArtistas->consultar();

        if (a->get_num_seguidores() > maxSeguidores) {
            maxSeguidores = a->get_num_seguidores();
            artistaTop = a;
        }

        lArtistas->avanzar();
    }

    // Imprimimos el resultado
    if (artistaTop) {
        cout << "El artista mas seguidores es: " << artistaTop->get_nombre()
             << " con " << maxSeguidores << " seguidores." << endl;
    } else {
        cout << "No se pudo determinar el artista top." << endl;
    }
}
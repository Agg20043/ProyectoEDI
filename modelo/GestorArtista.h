#ifndef GESTORARTISTA_H
#define GESTORARTISTA_H

#define LISTA_ARTISTAS

#include "Artista.h"
#include <iostream>
#include <string>

#if defined(LISTA_ARTISTAS)
    #include "ListaDPI.h"

#else

    #include "bstree.h"
    #include "KeyValue.h"

#endif

using namespace std;

class GestorArtistas {

private:

#if defined(LISTA_ARTISTAS)

    ListaDPI<Artista *> *lArtistas;

#else

    BSTree<KeyValue<string, Artista>>aArtistas;

    Artista* buscarArb(
        BSTree<KeyValue<string, Artista>> nodo,
        const string& nombre
    ) const;

    void mostrarArbrec(
        BSTree<KeyValue<string, Artista>> nodo
    ) const;

    int contarArbrec(
        BSTree<KeyValue<string, Artista>> nodo
    ) const;

    void topArblrec(
        BSTree<KeyValue<string, Artista>> nodo,
        Artista& top,
        int& maxSeguidores
    ) const;

    void copiarArbolrec(
        BSTree<KeyValue<string, Artista>>* nodo
    );

#endif

public:

    GestorArtistas();

    GestorArtistas(const GestorArtistas& otro);

    ~GestorArtistas();

    void insertar(Artista* artista);

    int numElementos() const;

    void mostrarTop() const;

    Artista* buscar(const string& nombre) const;

    void mostrar() const;
};

#endif

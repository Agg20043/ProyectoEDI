#ifndef GESTORARTISTA_H
#define GESTORARTISTA_H

//#define LISTA_ARTISTAS

#include "Artista.h"

#if defined(LISTA_ARTISTAS)
    #include "ListaDPI.h"
#else
    #include "bstree.h"
    #include "KeyValue.h"
#endif

class GestorArtistas {
private:

    ListaDPI<Artista*> *lArtistas;

    BSTree<KeyValue<string, Artista*>> *aArtistas;
    Artista* buscarRec(BSTree<KeyValue<string, Artista*>>* nodo,
                       const string& nombre) const;


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

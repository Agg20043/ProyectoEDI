//
// Created by xalva on 07/04/2026.
//

#ifndef UNTITLED3_GESTORARTISTA_H
#define UNTITLED3_GESTORARTISTA_H
#include "ListaDPI.h"
#include "Artista.h"

class GestorArtistas {
private:
    ListaDPI<Artista*> *lArtistas;

public:
    GestorArtistas();
    GestorArtistas(const GestorArtistas& otro);
    ~GestorArtistas();

    void insertar(Artista* artista);
    int numElementos() const;
    Artista* buscar(const string& nombre) const;
    void mostrar() const;
};

#endif //UNTITLED3_GESTORARTISTA_H
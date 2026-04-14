#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

#include "ListaDPI.h"
#include "persona.h"
#include <string>
#include <iostream>

using namespace std;

class GestorUsuarios {
private:
    ListaDPI<persona*> *lUsuarios;

public:
    GestorUsuarios();
    GestorUsuarios(const GestorUsuarios& otro);

    ~GestorUsuarios();

    void insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a);

    persona* buscar(const string& id);

    int numElementos() const;

    void mostrar() const;
};

#endif



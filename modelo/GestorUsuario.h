#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

#define LISTA_USUARIOS

#include "persona.h"
#include <string>
#include <iostream>

#if defined(LISTA_USUARIOS)
    #include "ListaDPI.h"
#else
    #include "bstree.h"
    #include "KeyValue.h"
#endif

using namespace std;

class GestorUsuarios {

private:

#if defined(LISTA_USUARIOS)

    ListaDPI<persona *> *lUsuarios;

#else

    BSTree<KeyValue<string, persona *>> *aUsuarios;

    persona* buscarRec(
        BSTree<KeyValue<string, persona *>> *nodo,
        const string &nombre
    ) const;

    void mostrarRec(
        BSTree<KeyValue<string, persona *>> *nodo
    ) const;

    int contarRec(
        BSTree<KeyValue<string, persona *>> *nodo
    ) const;
#endif

public:
    GestorUsuarios();

    GestorUsuarios(const GestorUsuarios& otro);

    ~GestorUsuarios();

    void insertar(
        const string& id,
        const string& nombre,
        const string& email,
        const string& password,
        int d,
        int m,
        int a
    );

    persona* buscar(const string& nombre);

    int numElementos() const;

    void mostrar() const;
};

#endif

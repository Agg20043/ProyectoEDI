#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

//#define LISTA_USUARIOS

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
    persona* buscarArbolRec(BSTree<KeyValue<string, persona *>> *nodo, const string &nombre) const;
    void mostrarArbolRec(BSTree<KeyValue<string, persona *>> *nodo) const;
    int contarArbolRec(BSTree<KeyValue<string, persona *>> *nodo) const;
    void copiarRec(BSTree<KeyValue<string, persona*>>* origen, BSTree<KeyValue<string, persona*>>* destino);

#endif

public:
    GestorUsuarios();
    GestorUsuarios(const GestorUsuarios& otro);
    ~GestorUsuarios();

    void insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a);
    persona* buscar(const string& nombre);
    int numElementos() const;
    void mostrar() const;
};

#endif

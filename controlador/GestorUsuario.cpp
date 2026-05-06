#include "GestorUsuarios.h"

GestorUsuarios::GestorUsuarios() {
#if defined(LISTA_USUARIOS)
    lUsuarios = new ListaDPI<persona*>();
#else
    aUsuarios = new BSTree<KeyValue<string, persona*>>();
#endif
}
GestorUsuarios::~GestorUsuarios() {
#if defined(LISTA_USUARIOS)

    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        delete lUsuarios->consultar();
        lUsuarios->eliminar();
    }
    delete lUsuarios;

#else
    delete aUsuarios;
#endif
}

void GestorUsuarios::insertar(const string& id, const string& nombre,
                             const string& email, const string& password,
                             int d, int m, int a) {

    persona* p = new persona(id, nombre, email, password, d, m, a);

#if defined(LISTA_USUARIOS)

    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal() &&
           lUsuarios->consultar()->getNombre() < nombre) {
        lUsuarios->avanzar();
    }
    lUsuarios->insertar(p);

#else

    KeyValue<string, persona*> kv(nombre, p);

    if (!aUsuarios->existe(kv)) {
        aUsuarios->insertar(kv);
    }

#endif
}

persona* GestorUsuarios::buscar(const string& nombre) {

#if defined(LISTA_USUARIOS)

    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        if (lUsuarios->consultar()->getNombre() == nombre)
            return lUsuarios->consultar();
        lUsuarios->avanzar();
    }
    return nullptr;

#else

    return buscarRec(aUsuarios, nombre);

#endif
}

#if !defined(LISTA_USUARIOS)

persona* GestorUsuarios::buscarRec(
    BSTree<KeyValue<string, persona*>>* nodo,
    const string& nombre) const {

    if (nodo == nullptr || nodo->estaVacio())
        return nullptr;

    KeyValue<string, persona*> kv = nodo->getDato();

    if (kv.getKey() == nombre)
        return kv.getValue();

    if (nombre < kv.getKey())
        return buscarRec(nodo->getIzq(), nombre);
    else
        return buscarRec(nodo->getDer(), nombre);
}

#endif

int GestorUsuarios::numElementos() const {
#if defined(LISTA_USUARIOS)

    int count = 0;
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        count++;
        lUsuarios->avanzar();
    }
    return count;

#else
    return 0;
#endif
}

void GestorUsuarios::mostrar() const {
#if defined(LISTA_USUARIOS)

    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        lUsuarios->consultar()->mostrar();
        lUsuarios->avanzar();
    }

#else
    cout << "[MOSTRAR NO IMPLEMENTADO EN ARBOL]" << endl;
#endif
}

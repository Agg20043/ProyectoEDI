//
// Created by xalva on 23/03/2026.
//
#include "../modelo/GestorUsuario.h"

#if defined(LISTA_USUARIOS)


// Lista


GestorUsuarios::GestorUsuarios() {
    lUsuarios = new ListaDPI<persona*>();
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios& otro) {

    lUsuarios = new ListaDPI<persona*>();

    otro.lUsuarios->moverPrimero();

    while (!otro.lUsuarios->alFinal()) {

        persona* original = otro.lUsuarios->consultar();

        persona* copia = new persona(*original);

        lUsuarios->insertar(copia);

        otro.lUsuarios->avanzar();
    }
}

GestorUsuarios::~GestorUsuarios() {

    lUsuarios->moverPrimero();

    while (!lUsuarios->alFinal()) {

        persona* p = lUsuarios->consultar();

        delete p;

        lUsuarios->eliminar();
    }

    delete lUsuarios;
}

void GestorUsuarios::insertar(
    const string& id,
    const string& nombre,
    const string& email,
    const string& password,
    int d,
    int m,
    int a
) {

    lUsuarios->moverPrimero();

    bool existe = false;

    while (!lUsuarios->alFinal()) {

        persona* p = lUsuarios->consultar();

        if (p->get_nombre() == nombre) {
            existe = true;
            break;
        }

        lUsuarios->avanzar();
    }

    if (!existe) {

        persona* nueva =
            new persona(id, nombre, email, password, d, m, a);

        lUsuarios->insertar(nueva);
    }
}

persona* GestorUsuarios::buscar(const string& nombre) {

    lUsuarios->moverPrimero();

    while (!lUsuarios->alFinal()) {

        persona* p = lUsuarios->consultar();

        if (p->get_nombre() == nombre ||
            p->get_id() == nombre) {

            return p;
        }

        lUsuarios->avanzar();
    }

    return nullptr;
}

int GestorUsuarios::numElementos() const {

    int contador = 0;

    lUsuarios->moverPrimero();

    while (!lUsuarios->alFinal()) {

        contador++;

        lUsuarios->avanzar();
    }

    return contador;
}

void GestorUsuarios::mostrar() const {

    cout << "===== USUARIOS =====" << endl;

    lUsuarios->moverPrimero();

    while (!lUsuarios->alFinal()) {

        persona* p = lUsuarios->consultar();

        p->mostrar();

        lUsuarios->avanzar();
    }

    cout << "TOTAL: " << numElementos() << endl;
}

#else


// Arbol


GestorUsuarios::GestorUsuarios() {

    aUsuarios = new BSTree<KeyValue<string, persona*>>();
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios& otro) {

    aUsuarios =new BSTree<KeyValue<string, persona*>>();

 
}

GestorUsuarios::~GestorUsuarios() {

    while (!aUsuarios->estaVacio()) {

        KeyValue<string, persona*> kv =
            aUsuarios->getDato();

        persona* p = kv.getValue();

        aUsuarios->eliminar(kv);

        delete p;
    }

    delete aUsuarios;
}

void GestorUsuarios::insertar(
    const string& id,
    const string& nombre,
    const string& email,
    const string& password,
    int d,
    int m,
    int a
) {

    KeyValue<string, persona*> clave(nombre);

    if (!aUsuarios->existe(clave)) {

        persona* nueva =new persona(id, nombre, email, password, d, m, a);

        KeyValue<string, persona*> kv(nombre, nueva);

        aUsuarios->insertar(kv);
    }
    else {

        cout << "[Aviso] Usuario repetido." << endl;
    }
}

persona* GestorUsuarios::buscarRec(BSTree<KeyValue<string, persona*>>* nodo,const string& nombre) const {

    if (nodo->estaVacio()) {
        return nullptr;
    }

    KeyValue<string, persona*> kv =
        nodo->getDato();

    if (kv.getKey() == nombre) {

        return kv.getValue();
    }

    if (nombre < kv.getKey()) {

        return buscarRec(nodo->getIzq(), nombre);
    }

    return buscarRec(nodo->getDer(), nombre);
}

persona* GestorUsuarios::buscar(const string& nombre) {

    return buscarRec(aUsuarios, nombre);
}

int GestorUsuarios::contarRec(
    BSTree<KeyValue<string, persona*>>* nodo
) const {

    if (nodo->estaVacio()) {
        return 0;
    }

    return 1 +
           contarRec(nodo->getIzq()) +
           contarRec(nodo->getDer());
}

int GestorUsuarios::numElementos() const {

    return contarRec(aUsuarios);
}

void GestorUsuarios::mostrarRec(
    BSTree<KeyValue<string, persona*>>* nodo
) const {

    if (nodo->estaVacio()) {
        return;
    }

    mostrarRec(nodo->getIzq());

    nodo->getDato().getValue()->mostrar();

    mostrarRec(nodo->getDer());
}

void GestorUsuarios::mostrar() const {

    cout << " USUARIOS BST =" << endl;

    mostrarRec(aUsuarios);

    cout << "TOTAL: "
         << numElementos()
         << endl;
}

#endif

//
// Created by xalva on 23/03/2026.
//
#include "../modelo/GestorUsuario.h"


#if defined(LISTA_USUARIOS)

// En caso de usarse por listas

GestorUsuarios::GestorUsuarios() {
    lUsuarios = new ListaDPI<persona*>();
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios& otro) {
    lUsuarios = new ListaDPI<persona*>();
    
    otro.lUsuarios->moverPrimero();
    while (!otro.lUsuarios->alFinal()) {
        persona* original = otro.lUsuarios->consultar();
        lUsuarios->insertar(new persona(*original));
        otro.lUsuarios->avanzar();
    }
}

GestorUsuarios::~GestorUsuarios() {
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        delete lUsuarios->consultar();
        lUsuarios->eliminar();
    }
    delete lUsuarios;
}

void GestorUsuarios::insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a) {
    
    if (buscar(nombre) == nullptr) {
        persona* nueva = new persona(id, nombre, email, password, d, m, a);
        lUsuarios->insertar(nueva);
    } else {
        cout << "Error: El usuario '" << nombre << "' ya existe." << endl;
    }
}

persona* GestorUsuarios::buscar(const string& criterio) {
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        persona* p = lUsuarios->consultar();
        if (p->get_nombre() == criterio || p->get_id() == criterio) {
            return p;
        }
        lUsuarios->avanzar();
    }
    return nullptr;
}

int GestorUsuarios::numElementos() const {
    int total = 0;
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        total++;
        lUsuarios->avanzar();
    }
    return total;
}

void GestorUsuarios::mostrar() const {
    cout << "Usuarios mostrados por lista: " << endl;
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        lUsuarios->consultar()->mostrar();
        lUsuarios->avanzar();
    }
    cout << "El Total: " << numElementos() << endl;
}

#else

// En caso de usarse por árbol

GestorUsuarios::GestorUsuarios() {
    aUsuarios = new BSTree<KeyValue<string, persona*>>();
}

void GestorArtistas::copiarRec(BSTree<KeyValue<string, persona*>>* origen, BSTree<KeyValue<string, persona*>>* destino) {
    if (!origen->estaVacio()) {
        
        KeyValue<string, persona*> kv = nodo->getDato();
        persona* original = kv.getValue();
        persona* copia = new persona(*original);
        
        KeyValue<string, persona*> nuevoKV(kv.getKey(), copia);
        aUsuarios->insertar(nuevoKV);
        copiarRecursivo(origen->getIzq(), destino);
        copiarRecursivo(origen->getDer(), destino);
    }
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios& otro) {
    aUsuarios = new BSTree<KeyValue<string, persona*>>();
    copiarRec(otro.aUsuarios, this->aUsuarios);
}

GestorUsuarios::~GestorUsuarios() {
    while (!aUsuarios->estaVacio()) {
        KeyValue<string, persona*> kv = aUsuarios->getDato();
        delete kv.getValue();
        aUsuarios->eliminar(kv);
    }
    delete aUsuarios;
}

void GestorUsuarios::insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a) {
    
    KeyValue<string, persona*> clave(nombre);
    if (!aUsuarios->existe(clave)) {
        persona* nueva = new persona(id, nombre, email, password, d, m, a);
        aUsuarios->insertar(KeyValue<string, persona*>(nombre, nueva));
    } else {
        cout << "Este usuario " << nombre << " ya existe." << endl;
    }
}

persona* GestorUsuarios::buscarRec(BSTree<KeyValue<string, persona*>>* nodo, const string& nombre) const {
    if (nodo->estaVacio()) return nullptr;

    string claveActual = nodo->getDato().getKey();
    if (claveActual == nombre) return nodo->getDato().getValue();
    
    if (nombre < claveActual) 
        return buscarRec(nodo->getIzq(), nombre);
    else 
        return buscarRec(nodo->getDer(), nombre);
}

persona* GestorUsuarios::buscar(const string& nombre) {
    return buscarRec(aUsuarios, nombre);
}

int GestorUsuarios::contarRec(BSTree<KeyValue<string, persona*>>* nodo) const {
    if (nodo->estaVacio()) return 0;
    return 1 + contarRec(nodo->getIzq()) + contarRec(nodo->getDer());
}

int GestorUsuarios::numElementos() const {
    return contarRec(aUsuarios);
}

void GestorUsuarios::mostrarRec(BSTree<KeyValue<string, persona*>>* nodo) const {
    if (nodo->estaVacio()) return;
    mostrarRec(nodo->getIzq());
    nodo->getDato().getValue()->mostrar();
    mostrarRec(nodo->getDer());
}

void GestorUsuarios::mostrar() const {
    cout << "Usuarios que hay, mostrador por el árbol:" << endl;
    mostrarRec(aUsuarios);
    cout << "El total: " << numElementos() << endl;
}

#endif

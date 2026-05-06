#include "GestorArtista.h"

GestorArtistas::GestorArtistas() {
#if defined(LISTA_ARTISTAS)
    lArtistas = new ListaDPI<Artista*>();
#else
    aArtistas = new BSTree<KeyValue<string, Artista*>>();
#endif
}

GestorArtistas::~GestorArtistas() {
#if defined(LISTA_ARTISTAS)

    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        delete lArtistas->consultar();
        lArtistas->eliminar();
    }
    delete lArtistas;

#else
    delete aArtistas;
#endif
}

void GestorArtistas::insertar(Artista* artista) {

#if defined(LISTA_ARTISTAS)

    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        if (lArtistas->consultar()->get_nombre() > artista->get_nombre())
            break;
        lArtistas->avanzar();
    }
    lArtistas->insertar(artista);

#else

    KeyValue<string, Artista*> kv(artista->get_nombre(), artista);

    if (!aArtistas->existe(kv)) {
        aArtistas->insertar(kv);
    }

#endif
}

Artista* GestorArtistas::buscar(const string& nombre) const {

#if defined(LISTA_ARTISTAS)

    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        if (lArtistas->consultar()->get_nombre() == nombre)
            return lArtistas->consultar();
        lArtistas->avanzar();
    }
    return nullptr;

#else

    return buscarRec(aArtistas, nombre);

#endif
}

#if !defined(LISTA_ARTISTAS)

Artista* GestorArtistas::buscarRec(
    BSTree<KeyValue<string, Artista*>>* nodo,
    const string& nombre) const {

    if (nodo == nullptr || nodo->estaVacio())
        return nullptr;

    KeyValue<string, Artista*> kv = nodo->getDato();

    if (kv.getKey() == nombre)
        return kv.getValue();

    if (nombre < kv.getKey())
        return buscarRec(nodo->getIzq(), nombre);
    else
        return buscarRec(nodo->getDer(), nombre);
}

#endif

int GestorArtistas::numElementos() const {
    return 0;
}

void GestorArtistas::mostrar() const {
    cout << "[MOSTRAR ARBOL NO IMPLEMENTADO]" << endl;
}

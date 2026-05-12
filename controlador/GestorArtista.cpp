
#include "../modelo/GestorArtista.h"

#if defined(LISTA_ARTISTAS)


// En caso de usarse por Listas

GestorArtistas::GestorArtistas() {

    lArtistas = new ListaDPI<Artista*>();
}

GestorArtistas::GestorArtistas(const GestorArtistas& otro) {

    lArtistas = new ListaDPI<Artista*>();
    otro.lArtistas->moverPrimero();
    while (!otro.lArtistas->alFinal()) {
        Artista* original = otro.lArtistas->consultar();
        Artista* copia = new Artista(*original);
        lArtistas->insertar(copia);
        otro.lArtistas->avanzar();
    }
}

GestorArtistas::~GestorArtistas() {

    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        delete lArtistas->consultar();
        lArtistas->eliminar();
    }
    delete lArtistas;
}

void GestorArtistas::insertar(Artista* artista) {
    lArtistas->moverPrimero();
    bool existe = false;
    while (!lArtistas->alFinal()) {
        Artista* a = lArtistas->consultar();
        if (a->get_nombre() == artista->get_nombre()) {
            existe = true;
            break;
        }
        if (a->get_nombre() > artista->get_nombre()) {
            break;
        }
        lArtistas->avanzar();
    }
    if (!existe) {
        lArtistas->insertar(artista);
    }
}

Artista* GestorArtistas::buscar(const string& nombre) const {
    lArtistas->moverPrimero();
    while (!lArtistas->alFinal()) {
        Artista* a = lArtistas->consultar();
        if (a->get_nombre() == nombre) {
            return a;
        }
        lArtistas->avanzar();
    }

    return nullptr;
}

void GestorArtistas::mostrar() const {

    lArtistas->moverPrimero();

    while (!lArtistas->alFinal()) {

        lArtistas->consultar()->mostrar();

        lArtistas->avanzar();
    }
}

int GestorArtistas::numElementos() const {

    int contador = 0;

    lArtistas->moverPrimero();

    while (!lArtistas->alFinal()) {

        contador++;

        lArtistas->avanzar();
    }

    return contador;
}

void GestorArtistas::mostrarTop() const {

    if (lArtistas->estaVacia()) {
        cout << "No hay artistas." << endl;
        return //como no hay artistas, acaba la función;
    }

    int maxSeguidores = 0;
    Artista* top = nullptr;
    lArtistas->moverPrimero();

    while (!lArtistas->alFinal()) {
        
        Artista* a = lArtistas->consultar();
        
        if (a->get_num_seguidores() > maxSeguidores) {
        maxSeguidores = a->get_num_seguidores();
	    top = a;
        }
        lArtistas->avanzar();
    }

    if (top != nullptr) {

        cout << "El artista más top es: " << top->get_nombre() << " tiene " << maxSeguidores << " seguidores." << endl;
    }
}

#else


// En caso de usarse por Árbol


GestorArtistas::GestorArtistas() {
    aArtistas = new BSTree<KeyValue<string, Artista*>>();
}

GestorArtistas::GestorArtistas(const GestorArtistas& otro) {
    aArtistas = new BSTree<KeyValue<string, Artista*>>();
    copiarRec(otro.aArtistas);
}

void GestorArtistas::copiarRec(BSTree<KeyValue<string, Artista*>>* nodo) {
    if (nodo->estaVacio()) {
        return;
    }

    KeyValue<string, Artista*> kv = nodo->getDato();
    Artista* original = kv.getValue();
    Artista* copia = new Artista(*original);

    KeyValue<string, Artista*> nuevoKV(kv.getKey(),copia);
    aArtistas->insertar(nuevoKV);
    copiarRec(nodo->getIzq());
    copiarRec(nodo->getDer());
}


GestorArtistas::~GestorArtistas() {
    while (!aArtistas->estaVacio()) {
        KeyValue<string, Artista*> kv = aArtistas->getDato();
        Artista* a = kv.getValue();
        aArtistas->eliminar(kv);
        delete a;
    }
    delete aArtistas;
}

void GestorArtistas::insertar(Artista* artista) {

    KeyValue<string, Artista*> clave(artista->get_nombre());

    if (!aArtistas->existe(clave)) {
        KeyValue<string, Artista*> kv(artista->get_nombre(),artista);
        aArtistas->insertar(kv);
    }
}

Artista* GestorArtistas::buscarArbrec(BSTree<KeyValue<string, Artista*>>* nodo, const string& nombre) const {

    if (nodo->estaVacio()) {
        return nullptr;
    }

    KeyValue<string, Artista*> kv = nodo->getDato();

    if (kv.getKey() == nombre) {
        return kv.getValue();
    }

    if (nombre < kv.getKey()) {
        return buscarArbrec(nodo->getIzq(),nombre);
    }
    return buscarArbrec(nodo->getDer(),nombre);
}

Artista* GestorArtistas::buscar(const string& nombre) const {
    return buscarArbrec(aArtistas, nombre);
}

void GestorArtistas::mostrarArbRec(BSTree<KeyValue<string, Artista*>>* nodo) const {
    if (nodo->estaVacio()) {
        return;
    }

    mostrarArbRec(nodo->getIzq());
    nodo->getDato().getValue()->mostrar();
    mostrarArbRec(nodo->getDer());
}

void GestorArtistas::mostrar() const {
    
    mostrarArbRec(aArtistas);
}

int GestorArtistas::contarArbolrecursivoYtal(BSTree<KeyValue<string, Artista*>>* nodo) const {
    if (nodo->estaVacio()) {
        return 0;
    }

    return 1 + contarArbolRecursivoYtal(nodo->getIzq()) + contarArbolRecursivoyTal(nodo->getDer());
}

int GestorArtistas::numElementos() const {
    return contarArbolRecursivoYtal(aArtistas);
}

void GestorArtistas::topArblrec(BSTree<KeyValue<string, Artista*>>* nodo, Artista*& top, int& maxSeguidores) const {
    if (nodo->estaVacio()) {
        return;
    }
    
    topArblrec(nodo->getIzq(), top, maxSeguidores);
    Artista* actual = nodo->getDato().getValue();
    if (actual->get_num_seguidores() > maxSeguidores) {

        maxSeguidores = actual->get_num_seguidores();
        top = actual;
    }

    topArblrec(nodo->getDer(), top, maxSeguidores);
}

void GestorArtistas::mostrarTop() const {
    if (aArtistas->estaVacio()) {
        cout << "No hay artistas top en esta lista." << endl;
        return;
    }
    Artista* top = nullptr;
    
    int maxSeguidores = 0;
    topArblrec(aArtistas, top, maxSeguidores);
    
    if (top != nullptr) {
        cout << "Top artista: " << top->get_nombre() << " con " << maxSeguidores << " seguidores." << endl;
    }
}

#endif

//
// Created by xalva on 02/03/2026.
//
#include "../modelo/Artista.h"

Artista::Artista() : nombre("Desconocido"), pais("Desconocido"), num_seguidores(0) {
    lCanciones = new ListaDPI<cancion*>();
}

Artista::Artista(const string &nombre, const string &pais, int num_seguidores)
    : nombre(nombre), pais(pais), num_seguidores(num_seguidores) {
    lCanciones = new ListaDPI<cancion*>();
}

Artista::Artista(const Artista& otro) {
    this->nombre = otro.nombre;
    this->pais = otro.pais;
    this->num_seguidores = otro.num_seguidores;

    this->lCanciones = new ListaDPI<cancion*>();

    otro.lCanciones->moverPrimero();
    while (!otro.lCanciones->alFinal()) {
        cancion* cancionOriginal = otro.lCanciones->consultar();
        cancion* nuevaCancion = new cancion(*cancionOriginal);
        this->lCanciones->insertar(nuevaCancion);
        otro.lCanciones->avanzar();
    }
}


Artista::~Artista() {
    lCanciones->moverPrimero();
    while (!lCanciones->alFinal()) {
        cancion* c = lCanciones->consultar();
        delete c;
        lCanciones->eliminar();
    }
    delete lCanciones;
}

void Artista::insertarCancion(const string& titulo, const string& genero, int duracion) {
    lCanciones->moverPrimero();
    bool existe = false;

    while (!lCanciones->alFinal()) {
        cancion* c = lCanciones->consultar();

        if (c->getTitulo() == titulo) {
            existe = true;
            cout << "[Aviso] La cancion '" << titulo << "' ya pertenece a este artista." << endl;
            break;
        }

        if (c->getTitulo() > titulo) {
            break;
        }

        lCanciones->avanzar();
    }

    if (!existe) {
        cancion* nuevaCancion = new cancion(titulo, genero, duracion);
        lCanciones->insertar(nuevaCancion);
    }
}

cancion* Artista::buscarCancion(const string& titulo) const {
    lCanciones->moverPrimero();
    while (!lCanciones->alFinal()) {
        cancion* c = lCanciones->consultar();
        if (c->getTitulo() == titulo) {
            return c;
        }
        lCanciones->avanzar();
    }
    return nullptr;
}

int Artista::numElementos() const {
    int contador = 0;
    lCanciones->moverPrimero();
    while (!lCanciones->alFinal()) {
        contador++;
        lCanciones->avanzar();
    }
    return contador;
}

void Artista::mostrar() const {
    cout << "\n=== ARTISTA: " << nombre << " (" << pais << ") ===" << endl;
    cout << "Seguidores: " << num_seguidores << endl;
    cout << "Repertorio (" << numElementos() << " canciones):" << endl;

    if (numElementos() == 0) {
        cout << "  [No hay canciones registradas aun]" << endl;
    } else {
        lCanciones->moverPrimero();
        while (!lCanciones->alFinal()) {
            cancion* c = lCanciones->consultar();
            c->mostrar();
            lCanciones->avanzar();
        }
    }
    cout << "=====================================" << endl;
}
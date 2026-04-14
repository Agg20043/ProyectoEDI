//
// Created by xalva on 23/03/2026.
//
#include "../modelo/GestorUsuario.h"

GestorUsuarios::GestorUsuarios() {
    lUsuarios = new ListaDPI<persona*>();
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios& otro) {
    lUsuarios = new ListaDPI<persona*>();

    // Recorre la lista del gestor original
    otro.lUsuarios->moverPrimero();
    while (!otro.lUsuarios->alFinal()) {
        persona* personaOriginal = otro.lUsuarios->consultar();

        // Crea una nueva instancia usando el constructor por copia de Persona
        persona* nuevaPersona = new persona(*personaOriginal);


        lUsuarios->insertar(nuevaPersona);

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

void GestorUsuarios::insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a) {
    lUsuarios->moverPrimero();
    bool existe = false;

    while (!lUsuarios->alFinal()) {
        persona* p = lUsuarios->consultar();

        if (p->get_nombre() == nombre) {
            existe = true;
            cout << "[Aviso] La persona " << nombre << " ya esta registrada." << endl;
            break;
        }

        if (p->get_nombre() > nombre) {
            break;
        }

        lUsuarios->avanzar();
    }

    if (!existe) {
        persona* nuevaPersona = new persona(id, nombre, email, password, d, m, a);

        lUsuarios->insertar(nuevaPersona);
    }
}

// 3. Buscar
persona* GestorUsuarios::buscar(const string& apellidosNombre) {
    lUsuarios->moverPrimero();

    while (!lUsuarios->alFinal()) {
        persona* p = lUsuarios->consultar();
        if (p->get_nombre() == apellidosNombre) {
            return p; // Devuelve el puntero a la persona encontrada
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
    cout << "--- Lista de Usuarios (" << numElementos() << " registrados) ---" << endl;

    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        persona* p = lUsuarios->consultar();
        p->mostrar(); // Asumimos que Persona tiene un método mostrar()
        lUsuarios->avanzar();
    }
    cout << "--------------------------------------" << endl;
}
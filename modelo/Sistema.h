//
// Created by xalva on 07/04/2026.
//

#ifndef UNTITLED3_SISTEMA_H
#define UNTITLED3_SISTEMA_H
#include "persona.h"
#include "GestorArtista.h"
#include "GestorUsuario.h"
#include <string>

using namespace std;

class Sistema {
private:
    string nombreSistema;
    GestorUsuarios *usuarios;   // Instancia dinámica
    GestorArtistas *artistas;   // Instancia dinámica

    // Métodos privados de carga de datos
    void cargarUsuarios();
    void cargarArtistas();
    void cargarCanciones();
    void cargarPlayList();

public:
    // 1. Constructores
    Sistema();
    Sistema(string nombreSistema);
    Sistema(const Sistema &otro); // Constructor por copia

    // 10. Destructor
    ~Sistema();

    // Operaciones principales
    void mostrarUsuarios() const;   // 6
    void mostrarArtistas() const;   // 7
    void buscarUsuario(string nombreYApellidos) const; // 8
    void registrarArtista(Artista* a);
    Artista* buscarArtista(const string& nombre) const;
    // 9. Compartir playlist
    void compartirPlaylist(string nombreOrigen, string nombrePlaylist, string nombreReceptor);

    // Getters básicos
    string getNombreSistema() const { return nombreSistema; }
};

#endif
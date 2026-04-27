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

    Sistema();
    Sistema(string nombreSistema);
    Sistema(const Sistema &otro);


    ~Sistema();


    void mostrarUsuarios() const;   // 6
    void mostrarArtistas() const;   // 7
    void buscarUsuario(string nombreYApellidos) const; // 8
    void registrarArtista(Artista* a);
    Artista* buscarArtista(const string& nombre) const;

    void compartirPlaylist(string nombreOrigen, string nombrePlaylist, string nombreDestino);

    // Getters básicos
    string getNombreSistema() const { return nombreSistema; }

    void reproducirPlaylistsUsuario(string nombreUsuario) const;
    void eliminarPlaylistUsuario(string nombreUsuario, string nombrePlaylist);
    void anadirFavoritoUsuario(string nombreUsuario, string nombreArtista);
    void eliminarFavoritoUsuario(string nombreUsuario, string nombreArtista);
    void mostrarArtistaTop() const;
};

#endif
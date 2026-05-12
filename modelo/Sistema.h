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
    GestorUsuarios *usuarios;
    GestorArtistas *artistas;

    //Carga de datos
    // Pre:Los archivoos .csv
    // Post:Carga la informacion de los ficheros
    // Complejidad:O(n)
    void cargarUsuarios();
    void cargarArtistas();
    void cargarCanciones();
    void cargarPlayList();

public:

    Sistema();
    Sistema(string nombreSistema);
    Sistema(const Sistema &otro);


    ~Sistema();

    //Pre:
    //Post:Muestra una lista de todos los usuarios
    //Complejidad:0(n)
    void mostrarUsuarios() const;
    //Pre:
    //Post:Muestra una lista de todos los artistas
    //Complejidad:0(n)
    void mostrarArtistas() const;
    //Pre:Nombre de usuario existente
    //Post:Muestra por consola la informacion del usuario,los artistas favoritos del usuario y reproduce todas las playlist
    //Complejidad:0(n)
    void buscarUsuario(string idUsuario) const;
    //Pre:artista no vacio
    //Post:Añade un nuevo artista
    //Complejidad:0(1)
    void registrarArtista(Artista* a);
    //Pre:artista no vacio
    //Post:Devuelve el artista buscado
    //Complejidad:0(1)
    Artista* buscarArtista(const string& nombre) const;
    //Pre:Usuario origen,destino y la playlist deben de existir
    //Post:copia la playlist del usuario origen y la añade al usuario destino
    //Complejidad:0(n)
    void compartirPlaylist(string nombreOrigen, string nombrePlaylist, string nombreDestino);

    string getNombreSistema() const { return nombreSistema; }
    //Pre:Nombre de usuario existente
    //Post:Llama al metodo reproducir playlist de reproducir playlist de la clase persona
    //Complejidad:0(n)
    void reproducirPlaylistsUsuario(string idUsuario) const;
    //Pre:Nombre usuario y nombre playlist existente
    //Post:Elimina la playList de la memoria ( y del archivo csv)
    //Complejidad:0(1)
    void eliminarPlaylistUsuario(string idUsuario, string nombrePlaylist);
    //Pre:Usuario y artista existente
    //Post:añade el artista a favoritos de un usuario y incrementa el numero de seguidores
    //Complejidad:0(1)
    void anadirFavoritoUsuario(string nombreUsuario, string nombreArtista);
    //Pre:Uusario existente
    //Post:Elimina el artista de los favoritos del usuario y decrementa el numero de seguidores
    //Complejidad:0(1)
    void eliminarFavoritoUsuario(string nombreUsuario, string nombreArtista);
    //Pre:
    //Post:Muestra un lista de artistas de mas a menos seguidores
    //Complejidad:0(n)
    void mostrarArtistaTop() const;
};

#endif
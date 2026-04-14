//
// Created by xalva on 07/04/2026.
//
#include "../modelo/Sistema.h"
#include "../modelo/GestorUsuario.h"
#include "../modelo/Artista.h"
#include <fstream>
#include <sstream>

Sistema::Sistema() : nombreSistema("Sistema por defecto") {
    usuarios = new GestorUsuarios();
    artistas = new GestorArtistas();
    // Carga automática
    cargarUsuarios();
    cargarArtistas();
    cargarCanciones();
    cargarPlayList();
}

Sistema::Sistema(string nombreSistema) : nombreSistema(nombreSistema) {
    usuarios = new GestorUsuarios();
    artistas = new GestorArtistas();
    // Carga automática
    cargarUsuarios();
    cargarArtistas();
    cargarCanciones();
    cargarPlayList();
}

Sistema::Sistema(const Sistema &otro) {
    this->nombreSistema = otro.nombreSistema;
    // Copia profunda usando los constructores por copia de los gestores
    this->usuarios = new GestorUsuarios(*(otro.usuarios));
    this->artistas = new GestorArtistas(*(otro.artistas));
}

Sistema::~Sistema() {
    delete usuarios;
    delete artistas;
}

// --- MÉTODOS PRIVADOS DE CARGA (CSV) ---

void Sistema::cargarUsuarios() {
    ifstream archivo("usuarios.csv");
    if (!archivo.is_open()) return;

    string linea, id, nombre, correo, pass, fechaStr;
    getline(archivo, linea); // Saltar cabecera si existe

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, correo, ';');
        getline(ss, pass, ';');
        getline(ss, fechaStr, ';');

        // Parsear fecha d/m/a
        int d, m, a;
        char slash;
        stringstream ssFecha(fechaStr);
        ssFecha >> d >> slash >> m >> slash >> a;

        persona* p = new persona(id, nombre, correo, pass,);
        usuarios->insertar(p);
    }
    archivo.close();
}

void Sistema::cargarArtistas() {
    ifstream archivo("artistas.csv");
    if (!archivo.is_open()) return;

    string linea, nombre, pais;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, nombre, ';');
        getline(ss, pais, ';');

        artistas->insertar(new Artista(nombre, pais, 0));
    }
    archivo.close();
}

void Sistema::cargarCanciones() {
    ifstream archivo("canciones.csv");
    if (!archivo.is_open()) return;

    string linea, nArtista, titulo, genero, durStr;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, nArtista, ';');
        getline(ss, titulo, ';');
        getline(ss, genero, ';');
        getline(ss, durStr, ';');

        Artista* a = artistas->buscar(nArtista);
        if (a) {
            a->insertarCancion(titulo, genero, stoi(durStr));
        }
    }
    archivo.close();
}

void Sistema::cargarPlayList() {
    ifstream archivo("playList.csv");
    if (!archivo.is_open()) return;

    string linea, nUsuario, nPlaylist, nArtista, nCancion;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, nUsuario, ';');
        getline(ss, nPlaylist, ';');
        getline(ss, nArtista, ';');
        getline(ss, nCancion, ';');

        persona* u = usuarios->buscar(nUsuario); // Buscar usuario
        if (u) {
            u->crearPlayList(nPlaylist); // Crea si no existe (lógica interna de persona)
            Artista* art = artistas->buscar(nArtista);
            if (art) {
                cancion* c = art->buscarCancion(nCancion);
                if (c) {
                    u->anadirCancionPlayList(nPlaylist, c);
                }
            }
        }
    }
    archivo.close();
}

// --- OPERACIONES PÚBLICAS ---

void Sistema::mostrarUsuarios() const {
    cout << "Total Usuarios: " << usuarios->numElementos() << endl;
    usuarios->mostrar();
}

void Sistema::mostrarArtistas() const {
    cout << "Total Artistas: " << artistas->numElementos() << endl;
    artistas->mostrar();
}

void Sistema::buscarUsuario(string nombreYApellidos) const {
    persona* u = usuarios->buscar(nombreYApellidos);
    if (u) {
        u->mostrar();           // Info básica
        u->mostrarFavoritos();  // Favoritos
        u->reproducirPlayList(); // Muestra sus playlists
    } else {
        cout << "Usuario no encontrado." << endl;
    }
}

void Sistema::compartirPlaylist(string nombreOrigen, string nombrePlaylist, string nombreReceptor) {
    persona* origen = usuarios->buscar(nombreOrigen);
    persona* receptor = usuarios->buscar(nombreReceptor);

    if (origen && receptor) {
        PlayList* copia = origen->compartirPlayList(nombrePlaylist);
        if (copia) {
            receptor->anadirPlayListCompartida(copia);
            cout << "Playlist '" << nombrePlaylist << "' compartida con exito." << endl;
        }
    }
}
void Sistema::registrarArtista(Artista* a) {
    // El sistema deja la inserccion a Gestor Artistas
    artistas->insertar(a);
}

Artista* Sistema::buscarArtista(const string& nombre) const {
    // El sistema deja la busqueda a Gestor Artistas
    return artistas->buscar(nombre);
}
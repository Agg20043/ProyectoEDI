//
// Created by xalva on 07/04/2026.
//
#include "../modelo/Sistema.h"
#include "../modelo/GestorUsuario.h"
#include "../modelo/Artista.h"
#include <fstream>
#include <sstream>
#include <vector>


Sistema::Sistema() : nombreSistema("Sistema por defecto") {
    usuarios = new GestorUsuarios();
    artistas = new GestorArtistas();

    cargarUsuarios();
    cargarArtistas();
    cargarCanciones();
    cargarPlayList();
}

Sistema::Sistema(string nombreSistema) : nombreSistema(nombreSistema) {
    usuarios = new GestorUsuarios();
    artistas = new GestorArtistas();

    cargarUsuarios();
    cargarArtistas();
    cargarCanciones();
    cargarPlayList();
}

Sistema::Sistema(const Sistema &otro) {
    this->nombreSistema = otro.nombreSistema;
    this->usuarios = new GestorUsuarios(*(otro.usuarios));
    this->artistas = new GestorArtistas(*(otro.artistas));
}

Sistema::~Sistema() {
    delete usuarios;
    delete artistas;
}


void Sistema::cargarUsuarios() {
    ifstream archivo("usuarios.csv");
    if (!archivo.is_open()) return;

    string linea, id, nombre, correo, pass, fechaStr;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        //Salta la primera linea del csv (ya que es el nombre de las columnas)
        stringstream ss(linea);
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, correo, ';');
        getline(ss, pass, ';');
        getline(ss, fechaStr, ';');


        int d = 0, m = 0, a = 0;
        char slash;
        stringstream ssFecha(fechaStr);
        ssFecha >> d >> slash >> m >> slash >> a;

        usuarios->insertar(id, nombre, correo, pass, d, m, a);
    }
    archivo.close();
}

void Sistema::cargarArtistas() {
    ifstream archivo("artistas.csv");
    if (!archivo.is_open()) return;
    string linea, nombre, pais;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
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
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        //Salta la primera linea del csv (ya que es el nombre de las columnas)

        stringstream ss(linea);
        getline(ss, nArtista, ';');
        getline(ss, titulo, ';');
        getline(ss, genero, ';');
        getline(ss, durStr, ';');

        Artista* a = artistas->buscar(nArtista);
        if (a) {
            int duracion = stoi(durStr);
            a->insertarCancion(titulo, genero, duracion);
        }

    }
    archivo.close();
}

void Sistema::cargarPlayList() {
    ifstream archivo("playList.csv");
    if (!archivo.is_open()) return;

    string linea, nUsuario, nPlaylist, nArtista, nCancion;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        //Salta las primera fila del csv(Nombres)
        stringstream ss(linea);
        getline(ss, nUsuario, ';');
        getline(ss, nPlaylist, ';');
        getline(ss, nArtista, ';');
        getline(ss, nCancion);

        persona* u = usuarios->buscar(nUsuario);
        if (u) {
            u->crearPlayList(nPlaylist);
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
        u->mostrar();
        u->mostrarArtistasFavoritos();
        u->reproducirPlayList();
    } else {
        cout << "Usuario no encontrado." << endl;
    }
}

void Sistema::compartirPlaylist(string nombreOrigen, string nombrePlaylist, string nombreDestino) {

    persona* origen = usuarios->buscar(nombreOrigen);
    persona* destino = usuarios->buscar(nombreDestino);

    //Control de errores que comprueba si el usuario origen y el usuario destino existen
    if (!origen) {
        cout << "Error: El usuario origen: '" << nombreOrigen << "' no existe." << endl;
        return;
    }
    if (!destino) {
        cout << "Error: El usuario Destino: '" << nombreDestino << "' no existe." << endl;
        return;
    }

    if (origen && destino) {

        // Comprueba si el usuario destino ya tiene la playList
        if (destino->compartirPlayList(nombrePlaylist)) {
            cout << "Error: El usuario destino ya tiene una playlist llamada '" << nombrePlaylist << "'." << endl;
            return;
        }

        PlayList* copia = origen->compartirPlayList(nombrePlaylist);

        if (copia) {
            destino->anadirPlayListCompartida(copia);
            cout << "Playlist '" << nombrePlaylist << "' compartida con exito." << endl;


            string nombreRealOrigen = origen->get_nombre();
            string nombreRealDestino = destino->get_nombre();

            ifstream archivoLectura("playList.csv");
            vector<string> lineasNuevas;

            if (archivoLectura.is_open()) {
                string linea, nUsu, nPlay, nArt, nCan;
                getline(archivoLectura, linea);

                while (getline(archivoLectura, linea)) {
                    if (linea.empty()) continue;

                    stringstream ss(linea);
                    getline(ss, nUsu, ';');
                    getline(ss, nPlay, ';');
                    getline(ss, nArt, ';');
                    getline(ss, nCan);

                    if (!nCan.empty() && nCan.back() == '\r') nCan.pop_back();


                    if (nUsu == nombreRealOrigen && nPlay == nombrePlaylist) {
                        lineasNuevas.push_back(nombreRealDestino + ";" + nombrePlaylist + ";" + nArt + ";" + nCan);
                    }
                }
                archivoLectura.close();
            }

            if (!lineasNuevas.empty()) {
                ofstream archivoEscritura("playList.csv", ios::app);
                if (archivoEscritura.is_open()) {
                    for (const string& nuevaLinea : lineasNuevas) {
                        archivoEscritura << nuevaLinea << endl;
                    }
                    archivoEscritura.close();
                }
            }
        } else {
            //Control de errores que avisa si la playList seleccionada la tiene el usuario origen.
            cout << "[ERROR] La playlist '" << nombrePlaylist << "' no existe en el usuario de origen." << endl;
        }
    }
}

void Sistema::registrarArtista(Artista* a) {
    artistas->insertar(a);
}

Artista* Sistema::buscarArtista(const string& nombre) const {
    return artistas->buscar(nombre);
}

void Sistema::reproducirPlaylistsUsuario(string nombreUsuario) const {
    persona* u = usuarios->buscar(nombreUsuario);

    //Si el usuario existe reproduce la playlist seleccionada si no saltara un error
    if (u) u->reproducirPlayList();
    else cout << "[ERROR] Usuario no encontrado." << endl;
}

void Sistema::eliminarPlaylistUsuario(string nombreUsuario, string nombrePlaylist) {
    //Buscamos al usuario a traves del id
    persona* u = usuarios->buscar(nombreUsuario);

    // Control de errores para verificar si el usuario existe.
    if (!u) {
        cout << "[ERROR] El usuario con ID '" << nombreUsuario << "' no existe en el sistema." << endl;
        return;
    }

    bool eliminada = u->eliminarPlayList(nombrePlaylist);

    if (eliminada) {

        //actualiza 'playlist.csv' para borrar la playlist del archivo
        string nombreRealUsuario = u->get_nombre();

        ifstream archivoLectura("playList.csv");
        vector<string> lineasRestantes;

        if (archivoLectura.is_open()) {
            string linea, nUsu, nPlay;

            // Guardamos la cabecera para no perderla a la hora de borrar una playList
            getline(archivoLectura, linea);
            lineasRestantes.push_back(linea);

            while (getline(archivoLectura, linea)) {
                if (linea.empty()) continue;

                stringstream ss(linea);
                getline(ss, nUsu, ';');
                getline(ss, nPlay, ';');

                // Si la línea no es del usuario y no es la playlist que vamos a borrar, se queda
                if (!(nUsu == nombreRealUsuario && nPlay == nombrePlaylist)) {
                    lineasRestantes.push_back(linea);
                }
            }
            archivoLectura.close();

            ofstream archivoEscritura("playList.csv", ios::trunc);
            if (archivoEscritura.is_open()) {
                for (const string& l : lineasRestantes) {
                    archivoEscritura << l << endl;
                }
                archivoEscritura.close();
                cout << "[EXITO] La playlist ha sido borrada." << endl;
            }
        }
    } else {
        // Control de errores por si la PlayList no existe
        cout << "[ERROR] El usuario no tiene ninguna playlist llamada '" << nombrePlaylist << "'." << endl;
    }
}

void Sistema::anadirFavoritoUsuario(string nombreUsuario, string nombreArtista) {
    persona* u = usuarios->buscar(nombreUsuario);
    Artista* a = artistas->buscar(nombreArtista);

    if (!u) {
        cout << "[ERROR] El usuario con ID '" << nombreUsuario << "' no existe en el sistema." << endl;
        return;
    }
    if (!a) {
        cout << "[ERROR] El artista '" << nombreArtista << "' no existe en el sistema." << endl;
        return;
    }

    u->insertarArtistaFavorito(a);

    a->incrementarSeguidores();

    cout << "[EXITO] Artista '" << a->get_nombre() << "' añadido a los favoritos de " << u->get_nombre() << "." << endl;
}

void Sistema::eliminarFavoritoUsuario(string nombreUsuario, string nombreArtista) {
    persona* u = usuarios->buscar(nombreUsuario);

    if (!u) {
        cout << "[ERROR] El usuario con ID '" << nombreUsuario << "' no existe en el sistema." << endl;
        return;
    }

    bool eliminado = u->eliminarArtistaFavorito(nombreArtista);

    if (eliminado) {

        Artista* a = artistas->buscar(nombreArtista);
        if (a) {
            a->decrementarSeguidores();
        }

        cout << "[EXITO] Se ha eliminado a '" << nombreArtista << "' de los favoritos de " << u->get_nombre() << "." << endl;
    } else {
        cout << "[ERROR] El artista '" << nombreArtista << "' no estaba en los favoritos de este usuario." << endl;
    }
}

void Sistema::mostrarArtistaTop() const {
cout << "--- TOP ARTISTAS CON MAS SEGUIDORES DEL SISTEMA ---" << endl;
artistas->mostrarTop();
}

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
        if (linea.empty()) continue; //if para ignorar las lineas vacias

        stringstream ss(linea);
        getline(ss, nArtista, ';');
        getline(ss, titulo, ';');
        getline(ss, genero, ';');
        getline(ss, durStr, ';');

        Artista* a = artistas->buscar(nArtista);
        if (a) {
            try {

                int duracion = stoi(durStr);
                a->insertarCancion(titulo, genero, duracion);
            } catch (...) {
                cout << "[Aviso] Duracion no valida para la cancion: " << titulo << endl;
            }
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
        u->mostrarFavoritos();
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

            /* Guarda la playList compartida en Playlist.csv y
             Se añaden los nombres reales para guardarlo en PlayList*/
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
            cout << "Error: La playlist '" << nombrePlaylist << "' no existe en el usuario de origen." << endl;
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
    if (u) u->reproducirPlayList();
    else cout << "Usuario no encontrado." << endl;
}

void Sistema::eliminarPlaylistUsuario(string nombreUsuario, string nombrePlaylist) {
    // 1. Buscamos al usuario por su ID
    persona* u = usuarios->buscar(nombreUsuario);

    // Control de errores: ¿Existe el usuario?
    if (!u) {
        cout << "[ERROR] El usuario con ID '" << nombreUsuario << "' no existe en el sistema." << endl;
        return;
    }

    // 2. Intentamos eliminar la playlist en memoria
    bool eliminada = u->eliminarPlayList(nombrePlaylist);

    if (eliminada) {

        // 3. ACTUALIZAR EL CSV (Para que el borrado sea permanente)
        string nombreRealUsuario = u->get_nombre(); // Tu getter para sacar "Apellidos, Nombre"

        ifstream archivoLectura("playList.csv");
        vector<string> lineasRestantes;

        if (archivoLectura.is_open()) {
            string linea, nUsu, nPlay;

            // Guardamos la cabecera para no perderla
            getline(archivoLectura, linea);
            lineasRestantes.push_back(linea);

            while (getline(archivoLectura, linea)) {
                if (linea.empty()) continue;

                stringstream ss(linea);
                getline(ss, nUsu, ';');
                getline(ss, nPlay, ';');

                // Si la línea NO es del usuario y NO es la playlist a borrar, nos la quedamos
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
                cout << "La playlist ha sido borrada del archivo permanentemente." << endl;
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

    if (u && a) {
        u->insertarArtistaFavorito(a);
        cout << "Artista '" << nombreArtista << "' anadido a los favoritos de " << nombreUsuario << "." << endl;
    } else {
        cout << "Error: Usuario o Artista no encontrado en el sistema." << endl;
    }
}

void Sistema::eliminarFavoritoUsuario(string nombreUsuario, string nombreArtista) {
    persona* u = usuarios->buscar(nombreUsuario);
    if (u) {
        u->eliminarArtistaFavorito(nombreArtista);
        cout << "Se ha intentado eliminar al artista de favoritos." << endl;
    } else {
        cout << "Usuario no encontrado." << endl;
    }
}

void Sistema::mostrarArtistaTop() const {
    cout << "Metodo en desarrollo (requiere recorrer la lista de GestorArtistas y comparar num_seguidores)." << endl;
}

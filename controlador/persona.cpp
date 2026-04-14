//
// Created by xalva on 04/02/2026.
//

#include "../modelo/persona.h"
#include "string"
#include "iostream"
#include <fstream>
#include <sstream>
using namespace std;

persona::persona() : id(""), nombre(""), email(""), password(""), edad(0) {
    fechaNacimiento = new Fecha();
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

persona::persona(string id, string nombre, string email, string password, int d, int m, int a)
    : id(id), nombre(nombre), email(email), password(password), edad(0) {
    this->fechaNacimiento = new Fecha(d, m, a);
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

persona::persona(const string &nombre, const int edad, const string &email, const string &password, const string &id, Fecha * const fecha_nacimiento)
    : nombre(nombre), edad(edad), email(email), password(password), id(id), fechaNacimiento(fecha_nacimiento) {
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

persona::~persona() {
    delete fechaNacimiento;

    // Destruir listas dinámicas [cite: 85]
    lPlayLists->moverPrimero();
    while (!lPlayLists->alFinal()) {
        delete lPlayLists->consultar();
        lPlayLists->eliminar();
    }
    delete lPlayLists;

    lArtistasFavoritos->moverPrimero();
    while (!lArtistasFavoritos->alFinal()) {
        lArtistasFavoritos->eliminar(); // No hacemos delete del Artista porque el sistema es el dueño
    }
    delete lArtistasFavoritos;
}
void persona::mostrar() const {
    cout << id << endl;
    cout << email << endl;
    cout << password << endl;
    fechaNacimiento->mostrar();
}


string persona::pasarCadena() const {
    return nombre + ";" + to_string(edad) + ";" + email + ";" + password + ";" + fechaNacimiento->pasarCadena() ;
}

// ==========================================
// MÉTODOS DE PLAYLISTS
// ==========================================
void persona::crearPlayList(const string& nombre) {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        if(lPlayLists->consultar()->getNombre() == nombre) return; // Ya existe
        lPlayLists->avanzar();
    }
    PlayList* nueva = new PlayList(nombre);
    lPlayLists->insertar(nueva);
}

void persona::anadirCancionPlayList(const string& nombrePlayList, cancion* c) {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        if(lPlayLists->consultar()->getNombre() == nombrePlayList) {
            // Usamos tu método agregarCancion()
            lPlayLists->consultar()->agregarCancion(c);
            return;
        }
        lPlayLists->avanzar();
    }
}

void persona::reproducirPlayList() const {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        // Usamos tu método reproducirTodo()
        lPlayLists->consultar()->reproducirTodo();
        lPlayLists->avanzar();
    }
}

PlayList* persona::compartirPlayList(const string& nombrePlayList) const {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        if(lPlayLists->consultar()->getNombre() == nombrePlayList) {
            return new PlayList(*(lPlayLists->consultar())); // Constructor de copia de PlayList
        }
        lPlayLists->avanzar();
    }
    return nullptr;
}

void persona::anadirPlayListCompartida(PlayList* playlist) {
    lPlayLists->insertar(playlist);
}

// ==========================================
// MÉTODOS DE ARTISTAS FAVORITOS
// ==========================================
void persona::insertarArtistaFavorito(Artista* artista) { // [cite: 81, 82]
    lArtistasFavoritos->moverPrimero();
    while(!lArtistasFavoritos->alFinal()) {
        if(lArtistasFavoritos->consultar()->get_nombre() == artista->get_nombre()) return; // Sin duplicados
        lArtistasFavoritos->avanzar();
    }
    lArtistasFavoritos->insertar(artista);
}

void persona::eliminarArtistaFavorito(const string& nombreArtista) { // [cite: 83]
    lArtistasFavoritos->moverPrimero();
    while(!lArtistasFavoritos->alFinal()) {
        if(lArtistasFavoritos->consultar()->get_nombre() == nombreArtista) {
            lArtistasFavoritos->eliminar();
            return;
        }
        lArtistasFavoritos->avanzar();
    }
}

void persona::mostrarFavoritos() const { // [cite: 84]
    cout << "Favoritos de " << nombre << ":" << endl;
    lArtistasFavoritos->moverPrimero();
    while(!lArtistasFavoritos->alFinal()) {
        cout << "- " << lArtistasFavoritos->consultar()->get_nombre() << endl;
        lArtistasFavoritos->avanzar();
    }
}

void cargarUsuarios(TVector& vector, const string& nombreFichero) {
    ifstream archivo(nombreFichero);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el fichero." << endl;
        return;
    }

    string linea, id, nombre, email, password, temp;
    int d, m, a, i = 0;

    getline(archivo, linea); // Saltar cabecera

    while (getline(archivo, linea) && i < MAX) {
        if (linea.empty()) continue;

        stringstream ss(linea);

        // Extraer campos básicos
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, email, ';');
        getline(ss, password, ';');

        try {
            // Extraer fecha: dd/mm/aaaa
            getline(ss, temp, '/');
            d = std::stoi(temp);
            getline(ss, temp, '/');
            m = std::stoi(temp);
            getline(ss, temp); // Lee hasta el final de la línea
            a = std::stoi(temp);

            // --- EL PASO QUE FALTABA ---
            // Creamos el objeto y lo metemos en el vector
            // Asumiendo que guardas punteros:
            vector[i] = new persona(id, nombre, email, password, d, m, a);

            i++; // ¡No olvides aumentar el índice!

        } catch (const std::exception& e) {
            cerr << "Error procesando línea: " << linea << " -> " << e.what() << endl;
        }
    }

    // Rellena el resto con nullptr
    for (; i < MAX; i++) {
        vector[i] = nullptr;
    }

    archivo.close();
}

void mostrarVector(const TVector& vector) {
    for (int i = 0; i < MAX; ++i) {
        if (vector[i] != nullptr) {
            vector[i]->mostrar();
            cout << "-------------------" << endl;
        }
    }
}
void guardarUsuariosPorAnio(const TVector& vector, int anio) {
    ofstream archivoOut("usuarios_out.csv");
    if (!archivoOut.is_open()) {
        cout << "Error al crear el fichero de salida." << endl;
        return;
    }

    for (int i = 0; i < MAX; ++i) {
        if (vector[i] != nullptr && vector[i]->get_anio_nacimiento() == anio) {
            archivoOut << vector[i]->pasarCadena() << endl;
        }
    }
    archivoOut.close();
}

void destruirVector(TVector& vector) {
    for (int i = 0; i < MAX; ++i) {
        if (vector[i] != nullptr) {
            delete vector[i];
            vector[i] = nullptr;
        }
    }
}
void mostrarInversoRecursivo(ifstream& archivo) {
    string linea;
    if (getline(archivo, linea)) {
        mostrarInversoRecursivo(archivo);

        cout << linea << endl;
    }
}

// Funcion para facilitar la lectura inversa
void leerYMostrarInverso(const string& nombreFichero) {

    ifstream archivo(nombreFichero);
    if (archivo.is_open()) {
        mostrarInversoRecursivo(archivo);
        archivo.close();
    } else {
        cout << "Error al abrir el fichero para lectura inversa." << endl;
    }
}

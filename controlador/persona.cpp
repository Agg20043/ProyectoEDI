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

    //Destruye las listas dinamicas
    lPlayLists->moverPrimero();
    while (!lPlayLists->alFinal()) {
        delete lPlayLists->consultar();
        lPlayLists->eliminar();
    }
    delete lPlayLists;

    lArtistasFavoritos->moverPrimero();
    while (!lArtistasFavoritos->alFinal()) {
        lArtistasFavoritos->eliminar();
    }
    delete lArtistasFavoritos;
}
void persona::mostrar() const {
    cout << "--- PERFIL DE USUARIO ---" << endl;
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Email: " << email << endl;
    cout << "Contrasenia: " << password << endl;
    cout << "Nacimiento: ";
    if (fechaNacimiento != nullptr) fechaNacimiento->mostrar();
    cout << "-------------------------" << endl;
}


string persona::pasarCadena() const {
    return nombre + ";" + to_string(edad) + ";" + email + ";" + password + ";" + fechaNacimiento->pasarCadena() ;
}



//Metodos de las playlist
void persona::crearPlayList(const string& nombre) {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        if(lPlayLists->consultar()->getNombre() == nombre) return;
        lPlayLists->avanzar();
    }
    PlayList* nueva = new PlayList(nombre);
    lPlayLists->insertar(nueva);
}

void persona::anadirCancionPlayList(const string& nombrePlayList, cancion* c) {
    lPlayLists->moverPrimero();
    while(!lPlayLists->alFinal()) {
        if(lPlayLists->consultar()->getNombre() == nombrePlayList) {
            lPlayLists->consultar()->agregarCancion(c);
            return;
        }
        lPlayLists->avanzar();
    }
}

void persona::reproducirPlayList() const {
    lPlayLists->moverPrimero();
    if (lPlayLists->alFinal()) {
        cout<<"[AVISO]Este usuario no tiene ninguna PlayList creada"<<endl;
    }
    while(!lPlayLists->alFinal()) {

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
bool persona::eliminarPlayList(string nombrePlaylist) {
    lPlayLists->moverPrimero();

    while (!lPlayLists->alFinal()) {

        if (lPlayLists->consultar()->getNombre() == nombrePlaylist) {
            lPlayLists->eliminar();
            return true;
        }
        lPlayLists->avanzar();
    }
    return false;
}

//Metodos de artistas favoritos
void persona::insertarArtistaFavorito(Artista* artista) {
    lArtistasFavoritos->moverPrimero();

    while(!lArtistasFavoritos->alFinal()) {

        if(lArtistasFavoritos->consultar()->get_nombre() == artista->get_nombre()) return;

        lArtistasFavoritos->avanzar();
    }
    lArtistasFavoritos->insertar(artista);
}

bool persona::eliminarArtistaFavorito(const string &nombreArtista) {
    lArtistasFavoritos->moverPrimero();

    while(!lArtistasFavoritos->alFinal()) {

        if(lArtistasFavoritos->consultar()->get_nombre() == nombreArtista) {

            lArtistasFavoritos->eliminar();


            return true;
        }
        lArtistasFavoritos->avanzar();
    }

    return false;
}

void persona::mostrarArtistasFavoritos() const {

    if (!lArtistasFavoritos->estaVacia()) {
        cout << "Artistas favoritos de " << nombre << ":" << endl;

        lArtistasFavoritos->moverPrimero();

        while(!lArtistasFavoritos->alFinal()) {

            cout << "- " << lArtistasFavoritos->consultar()->get_nombre() << endl;

            lArtistasFavoritos->avanzar();
        }
    } else {
        cout<< "Este Usuario no tiene ningun artista en favoritos."<<endl;
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

    getline(archivo, linea);

    while (getline(archivo, linea) && i < MAX) {
            vector[i] = new persona(id, nombre, email, password, d, m, a);
            i++;
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


void leerYMostrarInverso(const string& nombreFichero) {

    ifstream archivo(nombreFichero);
    if (archivo.is_open()) {
        mostrarInversoRecursivo(archivo);
        archivo.close();
    } else {
        cout << "Error al abrir el fichero para lectura inversa." << endl;
    }
}

//
// Created by xalva on 04/02/2026.
//

#ifndef UNTITLED3_PERSONA_H
#define UNTITLED3_PERSONA_H
#include <iostream>
#include <string>
#include "Fecha.h"
#include "ListaDPI.h"
#include "PlayList.h"
#include "Artista.h"

using namespace std;
class persona {

private:
    string nombre;
    int edad;
    string email;
    string password;
    string id;
    Fecha* fechaNacimiento;

    ListaDPI<PlayList*> *lPlayLists;
    ListaDPI<Artista*> *lArtistasFavoritos;

public:

    //Pre:nombre, email, password, id, fecha_nacimiento.
    //Post:Crea un objeto persona con los datos.
    //Complejidad: O(1)
    persona(const string &nombre, const int edad, const string &email, const string &password, const string &id, Fecha * const fecha_nacimiento);
    //Pre:datos de fecha validos
    //Post:Crea un objeto persona inicializando la fecha.
    //Complejidad: O(1)
    persona(string id, string nombre, string email, string password, int d, int m, int a);
    //Pre:
    //Post:Crea una persona con valores por defecto
    //Complejidad: O(1)
    persona();
    //Pre: Un objeto persona que exista
    //Post: Libera la memoria de fecha_nacimiento y de todas las listas (playlists y artistas favoritos).
    //Complejidad: O(n),0(m), (n = playlists, m = artistas)
    ~persona();


    //GETTER AND SETTERS
    //GETTER
    //Pre:
    //Post:Devuelve el dato seleccionado
    //Complejidad:O(1)

    //SETTER
    //Pre:Dato existente
    //Post:Actualiza el dato de la persona
    //Complejidad:
    string get_nombre() const { return nombre; }
    void set_nombre(const string &nombre) { this->nombre = nombre; }

    int get_edad() const { return edad; }
    void set_edad1(int edad) { this->edad = edad; }

    string get_email() const { return email; }
    void set_email1(const string &email) { this->email = email; }

    string get_password() const { return password; }
    void set_password1(const string &password) { this->password = password; }

    string get_id() const { return id; }
    void set_id1(const string &id) { this->id = id; }


    // Pre:dia,mes y año forman una fecha valida
    // Post:Actualiza la fecha de nacimiento del usuario.
    // Complejidad: O(1)
    Fecha * get_fecha_nacimiento() const { return fechaNacimiento; }
    void set_fecha_nacimiento(int d, int m, int a) {
        fechaNacimiento->setDia(d);
        fechaNacimiento->setMes(m);
        fechaNacimiento->setAnio(a);
    }

    int get_anio_nacimiento() const { return fechaNacimiento->getAnio(); }


    //Pre:
    //Post:Muestra los datos personales de un usuario.
    //Complejidad: O(n)
    void mostrar() const;

    //Pre:
    //Post:Devuelve una cadena con ols datos basicos.
    //Complejidad: O(1)
    string pasarCadena() const;

    //Pre:Nombre de la playlist
    //Post:Añade una playList vacia al usuario
    //Complejidad: O(1)
    void crearPlayList(const string& nombre);
    //Pre:Nombre de PlayList existente y la cancion no puede estar vacia
    // Post:Inserta la cancion en la playlist indicada.
    // Complejidad: O(n)
    void anadirCancionPlayList(const string& nombrePlayList, cancion* c);
    //Pre:
    // Post:Reproduce todas las playList de un usuario
    // Complejidad:0(n)
    void reproducirPlayList() const;
    //Pre:nombrePlayList debe de existir
    // Post:Devuelve un puntero a una copia de la playList
    // Complejidad:0(1)
    PlayList* compartirPlayList(const string& nombrePlayList) const;
    //Pre:playList no puede estar vacia
    // Post:Añade la playlist compartida a la lista del usuario
    // Complejidad:0(1)
    void anadirPlayListCompartida(PlayList* playlist);
    //Pre:nombre de la playList para borrar
    // Post:Elimina la PlayList  si existe y devuelve true
    // Complejidad:0(n)
    bool eliminarPlayList(string nombrePlaylist);
    //Pre:artista no vacio
    // Post:Añade dicho artista a la lista de favoritos de un usuario
    // Complejidad:0(1)
    void insertarArtistaFavorito(Artista* artista);
    //Pre:nombre del artista favorito a eliminar
    // Post:Elimina el artista favoritos y devuelve true si lo encontro
    // Complejidad:0(n)
    bool eliminarArtistaFavorito(const string &nombreArtista);
    //Pre:
    // Post:Imprime una lista de artistas favoritos de una persona
    // Complejidad:0(n)
    void mostrarArtistasFavoritos() const;
};

const int MAX = 100;

typedef persona* TVector[MAX];

//Pre:fichero existente
// Post:Carga los usuarios de "usuarios.csv" en el vector
// Complejidad:0(n)
void cargarUsuarios(TVector& vector, const string& nombreFichero);
//Pre:
// Post:muestra todos los usuarios cargados en el vector en la consola
// Complejidad:0(n)
void mostrarVector(const TVector& vector);
//Pre:Año de nacimiento que quieras almacenar en el fichero
// Post:Almacena los usuarios del año seleccionado en 'usuarios_out.csv'
// Complejidad:0(n)
void guardarUsuariosPorAnio(const TVector& vector, int anio);
//Pre:
// Post:Destruye el vector para liberar la memoria
// Complejidad:0(n)
void destruirVector(TVector& vector);
//Pre:el fichero existente
// Post:Lee el archivo y lo muestra de forma inversa
// Complejidad:0(n)
void leerYMostrarInverso(const string& nombreFichero);


#endif //UNTITLED3_PERSONA_H
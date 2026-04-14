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
    persona(const string &nombre, const int edad, const string &email, const string &password, const string &id,
        Fecha * const fecha_nacimiento)
        : nombre(nombre),
          edad(edad),
          email(email),
          password(password),
          id(id),
          fechaNacimiento(fecha_nacimiento) {
    }

     persona(string id, string nombre, string email, string password, int d, int m, int a);

     persona();

     ~persona();

    string get_nombre() const {
        return nombre;
    }

    void set_nombre(const string &nombre) {
        this->nombre = nombre;
    }

    int get_edad() const {
        return edad;
    }

    void set_edad1(int edad) {
        this->edad = edad;
    }

    string get_email() const {
        return email;
    }

    void set_email1(const string &email) {
        this->email = email;
    }

    string get_password() const {
        return password;
    }

    void set_password1(const string &password) {
        this->password = password;
    }

    string get_id() const {
        return id;
    }

    void set_id1(const string &id) {
        this->id = id;
    }

    Fecha * get_fecha_nacimiento() const {
        return fechaNacimiento;
    }

    void set_fecha_nacimiento(int d, int m, int a) {
    fechaNacimiento->setDia(d);
        fechaNacimiento->setMes(m);
        fechaNacimiento->setAnio(a);
    }

     int get_anio_nacimiento() const {
        return fechaNacimiento->getAnio(); // Asumiendo que Fecha tiene getAnio()
    }


    void mostrar() const;

    string pasarCadena() const;

     void crearPlayList(const string& nombre);
     void anadirCancionPlayList(const string& nombrePlayList, cancion* c);
     void reproducirPlayList() const;
     PlayList* compartirPlayList(const string& nombrePlayList) const;
     void anadirPlayListCompartida(PlayList* playlist);


     void insertarArtistaFavorito(Artista* artista);
     void eliminarArtistaFavorito(const string& nombreArtista);
     void mostrarFavoritos() const;
 };
const int MAX = 100;

typedef persona* TVector[MAX];

void cargarUsuarios(TVector& vector, const string& nombreFichero);
void mostrarVector(const TVector& vector);
void guardarUsuariosPorAnio(const TVector& vector, int anio);
void destruirVector(TVector& vector);
void leerYMostrarInverso(const string& nombreFichero);
#endif //UNTITLED3_PERSONA_H
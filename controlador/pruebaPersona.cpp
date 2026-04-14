//
// Created by xalva on 16/02/2026.
//

#include "../modelo/pruebaPersona.h"
#include "../modelo/persona.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void ejecutarPrueba() {

    persona* p1 = new persona();
    persona* p2 = new persona("001", "Paco Garcia", "paco@gmail.com","0000",5,2,2000);
    persona* p3 = new persona(*p2);
    p1->set_id1("111");
    p1->set_nombre("Juan Cuevas");
    p1->set_edad1(24);
    p1->set_email1("Juan@gmail.com");
    p1->set_password1("1111");
    p1->set_fecha_nacimiento(3,4,2010);


    p1->mostrar();
    p2->mostrar();
    p3->mostrar();

    leerFichero1();

}

void leerFichero1() {
    string linea;
    int cont = 0;
    ifstream fEnt;
    fEnt.open("usuarios.csv");
    if (fEnt.is_open()) {
        getline(fEnt, linea);
        // lee la línea cabecera y la ignora
        while(!fEnt.eof()){
            getline(fEnt, linea);
            if (!fEnt.eof()) { // doble comprobación del eof
                cont++;
                cout << cont << " - " << linea << endl;
            }
        }
        fEnt.close();
        ejecutarPrueba2();

    }else cerr << "Error al abrir el fichero" << endl;
}



void ejecutarPrueba2() {

    TVector misUsuarios;
    TVector misUsuariosOut;
    //Nombre del archivo
    string ficheroOriginal = "usuarios.csv";
    string ficheroOutFecha ="usuarios_out.csv";

    //Carga el archivo
    cout << "--- CARGANDO USUARIOS DESDE EL FICHERO ---" << endl;
    cargarUsuarios(misUsuarios, ficheroOriginal);

    //Muestra el archivo
    cout << "\n--- MOSTRANDO USUARIOS ---" << endl;
    mostrarVector(misUsuarios);


    int anioBuscado = 2000; //Busca el año
    cout << "\n--- GUARDANDO USUARIOS NACIDOS EN " << anioBuscado << " ---" << endl;
    guardarUsuariosPorAnio(misUsuarios, anioBuscado);

    //Carga el archivo
    cout << "--- CARGANDO USUARIOS NACIDOS EN EL " << anioBuscado << " DESDE EL FICHERO ---" << endl;
    cargarUsuarios(misUsuariosOut, ficheroOutFecha);

    //Muestra el archivo
    cout << "\n--- MOSTRANDO USUARIOS NACIDOS EN " << anioBuscado << " ---" << endl;
    mostrarVector(misUsuariosOut);


    //Lee Inverso
    cout << "\n--- MOSTRANDO FICHERO ORIGINAL EN ORDEN INVERSO ---" << endl;
    leerYMostrarInverso(ficheroOriginal);

    //Libera la memoria memoria
    cout << "\n--- LIBERANDO MEMORIA ---" << endl;
    destruirVector(misUsuarios);
    destruirVector(misUsuariosOut);
    cout << "Memoria liberada con exito." << endl;
}
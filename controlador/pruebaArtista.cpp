//
// Created by xalva on 06/03/2026.
//
#include "../modelo/Artista.h"
#include <iostream>

using namespace std;

void ejecutar_pruebas_artista() {
    cout << "\n=== INICIANDO PRUEBAS DINÁMICAS DE ARTISTA ===" << endl;

    cout << "Creando artista1 (Por defecto)..." << endl;
    Artista* artista1 = new Artista();

   cout << "Modificando artista1 con setters..." << endl;
    artista1->set_nombre("Kanye West");
    artista1->set_pais("EEUU");
    artista1->set_num_seguidores(5000000);
    artista1->mostrar();

    //Constructor parametrizado
    cout << "Creando artista2 (Parametrizado)..." << endl;
    Artista* artista2 = new Artista("Aung Lean", "Suiza", 40000000);
    artista2->mostrar();

    //Constructor por copia
    cout << "Creando artista3 (Copia de artista2)..." << endl;
    Artista* artista3 = new Artista(*artista2);
    artista3->mostrar();

    //Prueba de operadores
    cout << "Evaluando operadores sobrecargados..." << endl;
    if (*artista2 == *artista3) {
        cout << " -> CORRECTO: artista2 y artista3 tienen el mismo nombre." << endl;
    } else {
        cout << " -> ERROR: Deberían ser iguales." << endl;
    }

    if (*artista1 < *artista2) {
        cout << artista1->get_nombre() << " va antes que " << artista2->get_nombre() << " alfabeticamente." << endl;
    } else {
        cout << artista2->get_nombre() << " va antes que " << artista1->get_nombre() << " alfabeticamente." << endl;

    }


    //Nuevos artistas
    cout << "=== INICIANDO PRUEBAS DE LISTA DE CANCIONES ===" << endl;

    cout << "[Prueba Búsqueda en Lista Vacia]" << endl;
    if (artista1->buscarCancion("Stronger") == nullptr) {
        cout << " -> CORRECTO: No encontro nada porque la lista esta vacia." << endl;
    }

    cout << "[Prueba Insercion en Lista Vacia ('Champion')]..." << endl;
    artista1->insertarCancion("Champion", "Rap", 180);

    cout << "[Prueba Insercion al Final ('Stronger')]..." << endl;
    artista1->insertarCancion("Stronger", "Rap", 210);

    cout << "[Prueba Insercion al Principio ('All Falls Down')]..." << endl;
    artista1->insertarCancion("All Falls Down", "Rap", 200);

    cout << "[Prueba Insercion Intermedia ('Heartless')]..." << endl;
    artista1->insertarCancion("Heartless", "Pop", 195);

    cout << "[Prueba Mostrar Lista Llena (Validando orden)]" << endl;
    cout << "El orden esperado es: All Falls Down -> Champion -> Heartless -> Stronger" << endl;
    artista1->mostrar();

    cout << "[Prueba Busqueda de Cancion EXISTENTE ('Heartless')]" << endl;
    cancion* encontrada = artista1->buscarCancion("Heartless");
    if (encontrada != nullptr) {
        cout << " -> CORRECTO: Cancion encontrada." << endl;
    }

    cout << "[Prueba Busqueda de Cancion INEXISTENTE ('Runaway')]" << endl;
    if (artista1->buscarCancion("Runaway") == nullptr) {
        cout << " -> CORRECTO: 'Runaway' no esta registrada y devolvio nullptr." << endl;
    }
    // =========================================================================


    cout << "Delete..." << endl;
    delete artista1;
    delete artista2;
    delete artista3;
    cout << "Memoria liberada correctamente. " << endl;

    cout << "FIN DE PRUEBAS" << endl;
}

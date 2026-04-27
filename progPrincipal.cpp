//============================================================================
// Name        : progPrincipal.cpp
// Author      : Profesores de la asignatura EDI
// Version     : Curso 25/26
// Copyright   :
// Description : Programa principal proyecto EDI
//============================================================================


#include <iostream>
#include <string>
#include "modelo/Sistema.h"
using namespace std;



int menu(string nombreSistema) {
    int opcion;
    do {
       cout << endl<<endl;
       cout << " -------- " << nombreSistema << " --------" << endl <<endl;
       cout << " 1. Mostrar todos los usuarios" << endl;
       cout << " 2. Buscar y mostrar un usuario" << endl;
       cout << " 3. Mostrar artistas y sus canciones" << endl;
       cout << " 4. Buscar y mostrar un artista" << endl;
       cout << " 5. Reproducir playlists de un usuario" << endl; // Adaptado a tu método
       cout << " 6. Compartir playlist entre dos usuarios" << endl;
       cout << " 7. Eliminar playlist de un usuario" << endl;
       cout << " 8. Añadir artista a favoritos de un usuario" << endl;
       cout << " 9. Eliminar artista de favoritos de un usuario" << endl;
       cout << " 10. Artista con mas seguidores" << endl;

       cout << " 0. Finalizar. " << endl;
       cout << " Opción: ";
       cout<<"_";

       //Controladoro de errores por si se escribe algo tipo String.
       if (!(cin>>opcion)) {
          cin.clear();
          cin.ignore(1000, '\n');
         opcion = -1;
       } else {

          cin.ignore();
       }



    } while (opcion < 0);
   return opcion;
}

int main() {

    Sistema* reproductorMusic= new Sistema("Reproductor de Musica");
    bool salir = false;
    int opcion;

    string esc1, esc2, esc3;

    while (!salir) {

       opcion = menu(reproductorMusic->getNombreSistema());
       switch (opcion) {
       case 1:
          reproductorMusic->mostrarUsuarios();
          break;
       case 2:
          cout << "Inserte el nombre del usuario: ";
          getline(cin, esc1);
          reproductorMusic->buscarUsuario(esc1);
          break;
       case 3:
          reproductorMusic->mostrarArtistas();
          break;
       case 4:
          cout << "Inserte nombre del artista: ";
          getline(cin, esc1);
          {
             Artista* a = reproductorMusic->buscarArtista(esc1);
             if (a != nullptr) {
                a->mostrar();
             } else {
                cout << "El artista: " << esc1 << " no existe." << endl;
             }
          }
          break;
       case 5:
             cout << "Introduce el id del usuario: ";
             getline(cin, esc1);
             reproductorMusic->reproducirPlaylistsUsuario(esc1);

             break;

       case 6:
          cout << "Inserte el nombre del usuario ORIGEN: ";
          getline(cin, esc1);
          cout << "Inserte el nombre de la playlist a compartir: ";
          getline(cin, esc2);
          cout << "Inserte el nombre del usuario RECEPTOR: ";
          getline(cin, esc3);
          reproductorMusic->compartirPlaylist(esc1, esc2, esc3); // Este ya lo tenías hecho ;)
          break;
       case 7:
          cout << "Inserte el nombre del usuario: ";
          getline(cin, esc1);
          cout << "Inserte el nombre de la playlist a eliminar: ";
          getline(cin, esc2);
          reproductorMusic->eliminarPlaylistUsuario(esc1, esc2);
          break;
       case 8:
          cout << "Inserte el nombre del usuario: ";
          getline(cin, esc1);
          cout << "Inserte el nombre del artista a añadir a favoritos: ";
          getline(cin, esc2);
          reproductorMusic->anadirFavoritoUsuario(esc1, esc2);
          break;
       case 9:
          cout << "Inserte el nombre del usuario: ";
          getline(cin, esc1);
          cout << "Inserte el nombre del artista a eliminar de favoritos: ";
          getline(cin, esc2);
          reproductorMusic->eliminarFavoritoUsuario(esc1, esc2);
          break;
       case 10:
          reproductorMusic->mostrarArtistaTop();
          break;
       case 0:
          salir = true;
          break;
       default:
          cout << "Opcion invalida." << endl;
          break;
       }
    }

    delete reproductorMusic; // Evitamos memory leaks
    return 0;
}




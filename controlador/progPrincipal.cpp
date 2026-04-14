//============================================================================
// Name        : progPrincipal.cpp
// Author      : Profesores de la asignatura EDI
// Version     : Curso 25/26
// Copyright   :
// Description : Programa principal proyecto EDI
//============================================================================


#include <iostream>
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
		cout << " 5. Reproducir una playlist de un usuario" << endl;
		cout << " 6. Compartir playlist entre dos usuarios" << endl;
		cout << " 7. Eliminar playlist de un usuario" << endl;
		cout << " 8. Añadir artista a favoritos de un usuario" << endl;
		cout << " 9. Eliminar artista de favoritos de un usuario" << endl;
		cout << " 10. Artista con mas seguidores" << endl;

		cout << " 0. Finalizar. " << endl;
		cout << " Opción: ";
		cout<<"_";
		cin>>opcion;
		cin.ignore();
		cout<<endl;

	} while ((opcion < 0) || (opcion > 11));
	return opcion;
}


int main() {


	bool salir = false;
	int opcion;

	while (!salir) {

		opcion = menu("Reproductor de musica");
		switch (opcion) {
		case 1:

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 0:
			salir = true;
			break;
		default:
			break;
		}
	}

	return 0;
}




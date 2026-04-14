//
// Created by xalva on 07/04/2026.
//

#include "../modelo/PruebaSistema.h"
#include "../modelo/Sistema.h";
#include "../modelo/Artista.h";

using namespace std;

void ejecutar_pruebas_sistema() {

    cout << "\n=============================================" << endl;
    cout << "    EJECUTANDO PRUEBAS DE LA CLASE SISTEMA" << endl;
    cout << "=============================================\n" << endl;

    Sistema* miApp = new Sistema();

    cout << "--- PRUEBAS DE INSERCION DE ARTISTAS ---" << endl;

    // Inserción en lista vacía
    cout << "[Prueba] Insertando 'Fakemink' (Lista vacia)..." << endl;
    miApp->registrarArtista(new Artista("Fakemink", "UK", 500));

    // Inserción al principio
    cout << "[Prueba] Insertando 'offset' (Va al principio)..." << endl;
    miApp->registrarArtista(new Artista("offset", "EEUU", 900));

    // Inserción al final
    cout << "[Prueba] Insertando 'Extremoduro' (Va al final)..." << endl;
    miApp->registrarArtista(new Artista("Extremoduro", "Spain", 300));

    // Inserción intermedia
    cout << "[Prueba] Insertando 'Manolo Garcia' (Intermedio)..." << endl;
    miApp->registrarArtista(new Artista("Manolo Garcia", "Spain", 700));

    cout << "\nMostrando catalogo para verificar orden (Fakemink, offset, Extremoduro, Manolo Garciap):" << endl;
    miApp->mostrarArtistas();

    cout << "\n--- PRUEBAS DE BÚSQUEDA ---" << endl;

    if (miApp->buscarArtista("Manolo Garcia") != nullptr) {
        cout << "[CORRECTO] 'Manolo Garcia' encontrado con exito en el Sistema." << endl;
    } else {
        cout << "[ERROR] No se encontro a Manolo Garcia." << endl;
    }

    if (miApp->buscarArtista("Sex pistols") == nullptr) {
        cout << "[CORRECTO] 'Sex Pistols' no existe y el Sistema devolvio nullptr." << endl;
    }

    cout << "\n--- PRUEBAS DE INTEGRACION DE USUARIOS ---" << endl;
    // Pasa el nombre real de tu fichero de usuarios (ej: "usuarios.csv" o el que uses)
    // miApp->inicializarSistema("usuarios.csv");
    // miApp->mostrarTodosLosUsuarios();

    cout << "\nLiberando memoria del Sistema..." << endl;
    delete miApp; // Se encargará de destruir Usuarios, GestorArtistas y Artistas
    cout << "\n=============================================" << endl;
    cout << "            FIN DE PRUEBAS DEL SISTEMA" << endl;
    cout << "=============================================\n" << endl;
}

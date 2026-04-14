//
// Created by xalva on 23/03/2026.
//

#include "../modelo/PruebaGestorUsuarios.h"

#include <iostream>

using namespace std;

void ejecutar_pruebas_gestor_usuarios() {

    cout <<"INICIANDO PRUEBAS GESTOR USUARIOS"<<endl;

    GestorUsuarios* gestor = new GestorUsuarios();


    cout<<"[PRUEBA 1 Mostrar lista vacia]"<<endl;
    gestor->mostrar();

    cout<<"[PRUEBA 3 BUSQUEDA EN LISTA VACIA]"<<endl;
    if (gestor->buscar("Lopez")==nullptr) {
        cout<<"NO SE ENCONTRO EL USUARIO Lopez(LISTA VACIA"<<endl;

    }

    cout<<"[PRUEBA 6 INSERCCION EN LISTA VACIA]"<<endl;
    gestor->insertar("003","Lopez","Lopez@gmail.com","pass123",1,1,2000);

    cout<<"[Prueba 7 INSERCCION FINAL]"<<endl;
    gestor->insertar("333","Garcia","garcia@gmail.com","pass222",3,3,2003);

    cout << "[PRUEBA 8 INSERTAR AL PRINCNIPIO]" << endl;
    gestor->insertar("001", "Alonso", "alonso@mail.com", "pass1", 3, 3, 1995);

    cout << "[PRUEBA 9 INSERCCION INTERMEDIA]" << endl;
    gestor->insertar("002", "Gomez", "gomez@mail.com", "pass2", 4, 4, 1985);


    cout << "[PRUEBAS 2 MOSTRAR LISTA LLENA]" << endl;
    gestor->mostrar();


    cout<<"[PRUEBA 4 BUSQUEDA DE USUARIO EXISTENTE 'Gomez']"<<endl;
    persona* encontrado = gestor->buscar("Gomez");
    if (encontrado != nullptr) {
        cout<<"USUARIO 'GOMEZ' ENCONTRADO "<<endl;

    } else {
        cout<<"USUARIO NO ENCONTRADO"<<endl;
    }

    cout<<"[PRUEBA 5 BUSQUEDA DE USUARIO INEXISTENTE 'Xavier'"<<endl;
    if (gestor->buscar("Xavier")==nullptr) {
        cout<<"CORRECTO USUARIO XAVIER NO ENCONTRADO"<<endl;

    } else {
        cout<<"ERROR USUARIO XAVIER ENCONTRADO"<<endl;

    }

    delete gestor;
    cout<<"FIN DE PRUEBAS"<<endl;

}
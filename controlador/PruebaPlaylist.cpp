//
// Created by xalva on 20/03/2026.
//
#include "../modelo/PruebaPlaylist.h"

using namespace std;

void PruebaPlaylist::testInserccion() {

    cout<<"-----PRUEBA 1:Insercion y Actualizacion-----" << endl;

    PlayList* miLista= new PlayList("New Wave");
     cancion* c1= new cancion("Same mistakes","Rap", 240);
    cancion* c2=new cancion("Fever","Cloud Rap",300);

    miLista->agregarCancion(c1);
    miLista->agregarCancion(c2);

    if (miLista->getNumCanciones() == 2 && miLista->getDuracion() == (240+300)) {
        cout<<"[INSERCION REALIZADA CON EXITO]"<<endl;
    }else {
        cout<<"[ERROR EN LA INSERCION O EN EL CALCULO DE LA DURACION]"<<endl;
    }

    delete miLista;
    delete c1;
    delete c2;
}

void PruebaPlaylist::testEliminacion() {
    cout<<"-----PRUEBA 2: ELIMINACION-----"<<endl;

    PlayList* miLista= new PlayList("Classics");
    cancion* c1= new cancion("Same mistakes","Rap", 240);
    cancion* c2=new cancion("Fever","Cloud Rap",300);

    miLista->agregarCancion(c1);
    miLista->agregarCancion(c2);

    //Eliminamos la primera cancion(Same mistakes)
    miLista->eliminarCancion();

    if (miLista->getNumCanciones() ==1 && miLista->getDuracion() == 300) {
        cout<<"[INSERCION REALIZADA CON EXITO]"<<endl;


    } else {
        cout<<"[ERROR EN ELIMINAR LA CANCION]"<<endl;
    }

    delete miLista;
    delete c1;
    delete c2;

}

void PruebaPlaylist::testCopiaYDestruccion() {
    cout<<"PRUEBA 3: COPIA Y DESTRUCCION"<<endl;

    cancion* c1=new cancion("Wrk Wrk","Electronica",233);

    PlayList* listaOriginal=new PlayList("Lista original");

    listaOriginal->agregarCancion(c1);

    //Llamada al constructor por copia
    PlayList* listaCopia=new PlayList(*listaOriginal);

    delete listaOriginal;

    if (listaCopia->getNumCanciones()==1 && listaCopia->getDuracion() == 233) {
        cout<<"[COPIA CREADA CORRECTAMENTE.LISTA ORIGINAL ELIMINADA]"<<endl;
    } else {
        cout<<"[ERROR EN EL CONSTRUCTOR POR COPIA]"<<endl;
    }
    delete listaCopia;
    delete c1;
}

void PruebaPlaylist::testReproduccion() {
    cout<<"-----PRUEBA 4: REPRODUCCION"<<endl;
    PlayList* miLista= new PlayList("Musica");

    cancion* c1=new cancion("CANCION A","GENERO 1", 100);
    cancion* c2= new cancion("CANCION B","GENERO 2",200);
    cancion* c3= new cancion("CANCION C","GENERO 3",300);
    miLista->agregarCancion(c1);
    miLista->agregarCancion(c2);
    miLista->agregarCancion(c3);

    cout<<"----- REPRODUCCION LISTA----"<<endl;
    miLista->reproducirTodo();

    cout<<"---- REPRODUCIR DESDE CANCION 2-----"<<endl;
    miLista->reproducirDesde(2);

    if (miLista->getNumCanciones()==3 && miLista->getDuracion() == 600) {
        cout<<"[REPRODUCCION FUNCIONO CON EXITO]"<<endl;
    }else {
        cout<<"[ERROR EN LA REPRODUCCION]"<<endl;
    }
    delete miLista;
    delete c1;
    delete c2;
    delete c3;


}

void PruebaPlaylist::ejecutarTodasLasPruebas() {
    cout<<"INICIANDO PRUEBAS"<<endl;

    testInserccion();
    testEliminacion();
    testCopiaYDestruccion();
    testReproduccion();
    cout<<"FIN DE PRUEBAS"<<endl;
}


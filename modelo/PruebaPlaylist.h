//
// Created by xalva on 20/03/2026.
//

#ifndef UNTITLED3_PRUEBAPLAYLIST_H
#define UNTITLED3_PRUEBAPLAYLIST_H

#include "PlayList.h"
#include "cancion.h"


class PruebaPlaylist{
public:


    //Se crea una PlayList vacia y se insertan dos canciones
    void testInserccion();

    //Elimina y actualiza los atributos
    void testEliminacion();

    //Se crea una PlayList originl y luego una copia a traves del constructor por copia
    void testCopiaYDestruccion();

    //Eejecuta el metodo reproducirTodo() y reproducirTodoDesde(posicion)
    void testReproduccion();

    //Meotodo principal que llama a todos los demas de forma secuencial
    void ejecutarTodasLasPruebas();
};


#endif //UNTITLED3_PRUEBAPL AYLIST_H
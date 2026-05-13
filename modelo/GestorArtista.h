
#ifndef GESTORARTISTA_H
#define GESTORARTISTA_H

//#define LISTA_ARTISTAS

#include "Artista.h"
#include <iostream>
#include <string>

#if defined(LISTA_ARTISTAS)
    #include "ListaDPI.h"

#else

    #include "bstree.h"
    #include "KeyValue.h"

#endif

using namespace std;

class GestorArtistas {

private:

#if defined(LISTA_ARTISTAS)
    ListaDPI<Artista*> *lArtistas;
#else

    BSTree<KeyValue<string, Artista*>> *aArtistas;
//Pre: Un árbol
//Post: Devuelve el artista que se ha pedido o nullptr si nno lo encunetran en el gestor.
//Complejidad: O(log n)
    Artista* buscarArbrec(BSTree<KeyValue<string, Artista*>>* nodo, const string& nombre) const;
//Pre: Un árbol
//Post: Muestra los artistas del arbol
//Complejidad: O(n)
    void mostrarArbRec(BSTree<KeyValue<string, Artista*>>* nodo) const;
//Pre: Un árbol
//Post: Devuelve el total de artistas que hay en el árbol que ponen
//Complejidad: O(n)
    int contarArbolrecursivoYtal(BSTree<KeyValue<string, Artista*>>* nodo) const;
//Pre: Un árbol
//Post: Devuelve por pantalla el artista con más seguidores 
//Complejidad: O(n)
    void topArblrec(BSTree<KeyValue<string, Artista*>>* nodo,Artista*& top,int& maxSeguidores) const;
//Pre: Un árbol
//Post: Copia todos los artistas del arbol que pones. Al igual que con el gestorUsuarios, es una función auxiliar para el generador por copia.
//Complejidad: O(n)
    void copiarRec(BSTree<KeyValue<string, Artista*>>* nodo);
//Pre: 
//Post: Devuelve la profundidad del árbol
//Complejidad: O(n)
    int calcularProfundidad(BSTree<KeyValue<string, Artista *>> *nodo) const;

#endif

public:

//Pre:
//Post: Crea un gestor vacío
//Complejidad: O(1)
    GestorArtistas();
//Pre: Un gestor correcto
//Post: Crea una copia del gestor que dan
//Complejidad: O(n)
    GestorArtistas(const GestorArtistas& otro);
//Pre:
//Post: Elimina una gestor
//Complejidad:O(n)
    ~GestorArtistas();

//Pre:
//Post: Inserta un artista si no estaba ya, en caso contrario, manda un mensaje de que ese artista ya existe por consola
//Complejidad: O(log n)
    void insertar(Artista* artista);
//Pre:
//Post:Devuelve el número de artistas en el gestor
//Complejidad: O(n)
    int numElementos() const;
//Pre:
//Post: Muestra el artista con más seguidores del gestor
//Complejidad: O(n)
    void mostrarTop() const;
//Pre:
//Post: Devuelve el artista que se haya pedido o nullptr si artista no se ha encontrado.
//Complejidad: O(log n)
    Artista* buscar(const string& nombre) const;
//Pre:
//Post: Muestra el artista con más seguidores.
//Complejidad: O(n)
    void mostrar() const;
};

#endif

#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

//#define LISTA_USUARIOS

#include "persona.h"
#include <string>
#include <iostream>

#if defined(LISTA_USUARIOS)
    #include "ListaDPI.h"
#else
    #include "bstree.h"
    #include "KeyValue.h"
#endif
using namespace std;

class GestorUsuarios {
private:
#if defined(LISTA_USUARIOS)

    ListaDPI<persona *> *lUsuarios;

#else

    BSTree<KeyValue<string, persona *>> *aUsuarios;

//Pre: Un árbol
//Post: Devuelve el punero del ususario si existe, si no, devuelve un mensaje y nullptr
//Complejidad: 
    persona *buscarRec(BSTree<KeyValue<string, persona *>> *nodo, const string &nombre) const;
//Pre: Un árbol
//Post: Muestra todos los usuarios del arbol que recorre
//Complejidad: O(n)
    void mostrarRec(BSTree<KeyValue<string, persona *>> *nodo) const;
//Pre: Un árabol
//Post: Devuelve el número total de usuarios en el árbol
//Complejidad: O(n)
    int contarRec(BSTree<KeyValue<string, persona *>> *nodo) const;
//Pre: Un árbol
//Post: Copia los usuarios del árbol que se da en el árbol nuevo creado. (Sirve como una función de soporte al generador por copia.
//Complejidad: O(n)
    void copiarRec(BSTree<KeyValue<string, persona*>>* origen, BSTree<KeyValue<string, persona*>>* destino);
//Pre: Un árbol
//Post: Devuelve la profundidad de un árbol
//Complejidad: O(n)
    int calcularProfundidad(BSTree<KeyValue<string, persona *>> *nodo) const;

#endif

public:
//Pre:
//Post: Crea un gestor vacío
//Complejidad:O(1)
    GestorUsuarios();
//Pre: Un gestor válido
//Post: Se crea una copia de un gestor válido
//Complejidad: O(n)
    GestorUsuarios(const GestorUsuarios& otro);
//Pre:Un gestor a destruir
//Post:Se destruye el gestor
//Complejidad: O(n)
    ~GestorUsuarios();

//Pre: Valores válidos
//Post: Se inserta y crea un objeto persona en el sistema si esta no existía
//Complejidad: O(log n)
    void insertar(const string& id, const string& nombre, const string& email, const string& password, int d, int m, int a);
//Pre:Valores válidos
//Post: Devuelve el puntero del usuario si exite, si no, devolverá un mensaje por pantalla y nullptr
//Complejidad:O(n)
    persona* buscar(const string& nombre);
//Pre: 
//Post:Devuelve el número de ususarios
//Complejidad: O(n)
    int numElementos() const;
//Pre: 
//Post:Muestra todos los usuarios
//Complejidad: O(n)
    void mostrar() const;

};

#endif

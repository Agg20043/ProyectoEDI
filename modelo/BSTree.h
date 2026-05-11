#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
using namespace std;

template <class TipoDato>
class BSTree {
private:

    // =============================
    // Clase interna privada
    // =============================

    class Nodo {
    public:
        TipoDato dato;
        BSTree<TipoDato>* izq;
        BSTree<TipoDato>* der;

        Nodo ( const TipoDato &dato ) {
        	this->dato = dato;
            this->izq = new BSTree<TipoDato> ( );
            this->der = new BSTree<TipoDato> ( );
        };

    }; // class Nodo

    // =============================
    // Atributo
    // =============================

    Nodo* raiz;

    // =============================
    // Métodos privados
    // =============================

    // PRE: nodo != nullptr
    // DESC: devuelve true si d está en el árbol con raíz en el nodo d;
    //       en caso contrario, devuelve false.
    // COMP: O (log n)
    bool existe ( Nodo *nodo, const TipoDato &d ) const;

    // PRE: nodo es nullptr o un puntero a un nodo válido.
    // DESC: Inserta el dato d en árbol con raíz en nodo.
    // COMP: O (log n)
    void insertar ( Nodo *&nodo, const TipoDato &d );

    // PRE: nodo es nullptr o un puntero a un nodo válido
    // DESC: Elimina el dato d del árbol con raíz en nodo si existe;
    //		 en caso contrario, no hace nada.
    // COMP: O (log n)
    void eliminar ( Nodo *&nodo, const TipoDato &d );

    // PRE: nodo != nullptr
    // DESC: Devuelve el valor mayor de los hijos menores del nodo
    //       (máximo valor de su subárbol izquierdo).
    // COMP: O (log n)
    TipoDato encontrarMayorDeMenores ( Nodo *nodo ) const;

    // PRE: nodo != nullptr
    // DESC: Devuelve el valor menor de los hijos mayores del nodo
    //       (mínimo valor de su subárbol derecho).
    // COMP: O (log n)
    TipoDato encontrarMenorDeMayores ( Nodo *nodo ) const;

    // PRE: !a->estaVacio ( )
    // DESC: Libera recursivamente todos los nodos del árbol a.
    // COMP: O (n)
    void destruir ( Nodo *&nodo );

public:
    // =============================
    // Métodos públicos
    // =============================

    // PRE: Ninguna
    // DESC: Constructor por defecto. Crea un BSTree vacío (raiz = nullptr).
    // COMP: O(1)
    BSTree ( );

    // PRE: Ninguna
    // DESC: Constructor parametrizado. Crea un BSTree con raíz en un nuevo
    // 		 nodo que almacena el dato d y cuyos hijos son dos BSTrees vacíos
    //		 (ambos creados utilizando el constructor por defecto de BSTree).
    // COMP: O(1)
    BSTree ( const TipoDato &d );

    // PRE: Ninguna
    // DESC: Devuelve true si el ABB está vacío; false en caso contrario.
    // COMP: O(1)
    bool estaVacio ( ) const;

    // PRE: !a->estaVacio ( )
    // DESC: Devuelve el dato almacenado en la raíz del árbol.
    // COMP: O(1)
    TipoDato getDato ( ) const;

    // PRE: !a->estaVacio ( )
    // DESC: Devuelve un puntero al subárbol izquierdo del árbol.
    // COMP: O(1)
    BSTree<TipoDato> *getIzq ( ) const;

    // PRE: !a->estaVacio ( )
    // DESC: Devuelve un puntero al subárbol derecho del árbol.
    // COMP: O(1)
    BSTree<TipoDato> *getDer ( ) const;

    // PRE: Ninguna
    // DESC: Devuelve true si el dato d existe en el árbol;
    //		 false en caso contrario.
    // COMP: O(log n)
    bool existe ( const TipoDato &d ) const;

    // PRE: Ninguna
    // DESC: Inserta un nuevo dato en el árbol si no existe previamente.
    //		 Si existe, no modifica el árbol (no se insertan repetidos).
    // COMP: O(log n)
    void insertar ( const TipoDato &d );

    // PRE: Ninguna
    // DESC: Elimina el dato d del árbol si existe. Si no existe, no
    //       hace nada.
    // COMP: O(log n)
    void eliminar ( const TipoDato &d );

    // PRE: Ninguna
    // DESC: Destructor. Libera recursivamente toda la memoria del árbol.
    // COMP: O(n)
    ~BSTree ( );
};

// ==================================
// Implementación de métodos privados
// ==================================

template <class TipoDato>
bool BSTree<TipoDato>::existe ( Nodo *nodo, const TipoDato &d ) const {
	bool encontrado = false;
   	if ( nodo->dato == d ) {
    	encontrado = true;
    }
    else if ( !nodo->izq->estaVacio ( ) && d < nodo->dato ) {
    	encontrado = existe ( nodo->izq->raiz, d );
    }
    else if ( !nodo->der->estaVacio ( ) && d > nodo->dato ) {
    	encontrado = existe ( nodo->der->raiz, d );
    }
	return encontrado;
}

template <class TipoDato>
void BSTree<TipoDato>::insertar ( Nodo *&nodo, const TipoDato &d ) {
    if ( nodo == nullptr ) {
        nodo = new Nodo ( d );
    }
    else if ( d < nodo->dato ) {
        insertar ( nodo->izq->raiz, d );
    }
    else if ( d > nodo->dato ) {
        insertar ( nodo->der->raiz, d );
    }
}

template <class TipoDato>
void BSTree<TipoDato>::eliminar ( Nodo *&nodo, const TipoDato &d ) {
	if ( nodo != nullptr) {
		if ( d < nodo->dato )
			eliminar ( nodo->izq->raiz, d );
		else if ( d > nodo->dato )
			eliminar ( nodo->der->raiz, d );
		else {
			TipoDato valor;
			if ( nodo->izq->estaVacio ( ) && nodo->der->estaVacio ( ) ) {
				// Eliminamos una hoja => Único escenario en el que se hace delete
				// Cuando eliminamos un nodo intermedio o la raíz, siempre se
				// reemplaza su valor por el de una hoja y se elimna la hoja!!
				delete nodo;
				nodo = nullptr;		// La raíz del árbol donde está el nodo
									// eliminando se pone a nullptr =>
									// queda vacío
			}
			else if ( nodo->izq->estaVacio ( ) ) {
				// El nodo sólo tiene hijo derecho =>
				// * obtener el valor del menor de sus hijos mayores = nuevoValor;
				// * colocar nuevoValor como valor del nodo que estamos eliminando
				// * invocar a eliminar pasando el hijo derecho y nuevoValor =>
				//   eliminará la hoja cuyo nuevoValor se ha subido al nodo eliminado
				valor = encontrarMenorDeMayores ( nodo->der->raiz );
				nodo->dato = valor;
				eliminar ( nodo->der->raiz, valor );
			} else {
				// Tiene hijo izquierdo (puede que también derecho, pero es irelevante) =>
				// * obtener el valor del mayor de sus hijos menores = nuevoValor;
				// * colocar nuevoValor como valor del nodo que estamos eliminando
				// * invocar a eliminar pasando el hijo izquierdo y nuevoValor =>
				//   eliminará la hoja cuyo nuevoValor se ha subido al nodo eliminado
				valor = encontrarMayorDeMenores ( nodo->izq->raiz );
				nodo->dato = valor;
				eliminar ( nodo->izq->raiz, valor );
			}
		}
	}
}

// Implementación iterativa; también podría hacerse de forma recursiva.
template <class TipoDato>
TipoDato BSTree<TipoDato>::encontrarMayorDeMenores ( Nodo* nodo ) const {
    Nodo* actual = nodo;
    while ( !actual->der->estaVacio ( ) ) {
        actual = actual->der->raiz;
    }
    return actual->dato;
}

// Implementación iterativa; también podría hacerse de forma recursiva.
template <class TipoDato>
TipoDato BSTree<TipoDato>::encontrarMenorDeMayores ( Nodo* nodo ) const {
    Nodo* actual = nodo;
    while ( !actual->izq->estaVacio ( ) ) {
        actual = actual->izq->raiz;
    }
    return actual->dato;
}

template <class TipoDato>
void BSTree<TipoDato>::destruir ( Nodo *&nodo ) {
	// Recorrido en post-orden
	if ( !nodo->izq->estaVacio ( ) ) {
		destruir ( nodo->izq->raiz );
	}
	if ( !nodo->der->estaVacio ( ) ) {
		destruir ( nodo->der->raiz );
	}
	delete nodo;
	nodo = nullptr;
}

// ==================================
// Implementación de métodos públicos
// ==================================

template <class TipoDato>
BSTree<TipoDato>::BSTree ( ) {
	raiz = nullptr;
}

template <class TipoDato>
BSTree<TipoDato>::BSTree ( const TipoDato &d ) {
	raiz = new Nodo ( d );
}

template <class TipoDato>
bool BSTree<TipoDato>::estaVacio ( ) const {
    return raiz == nullptr;
}

template <class TipoDato>
TipoDato BSTree<TipoDato>::getDato ( ) const {
    return raiz->dato;
}

template <class TipoDato>
BSTree<TipoDato>* BSTree<TipoDato>::getIzq ( ) const {
	return raiz->izq;
}

template <class TipoDato>
BSTree<TipoDato>* BSTree<TipoDato>::getDer ( ) const {
	return raiz->der;
}

template <class TipoDato>
bool BSTree<TipoDato>::existe ( const TipoDato &d ) const {
	bool encontrado = false;
	if ( !this->estaVacio ( ) )
		encontrado = existe ( this->raiz, d );
	return encontrado;
}

template <class TipoDato>
void BSTree<TipoDato>::insertar ( const TipoDato &d ) {
    insertar ( this->raiz, d );
}

template <class TipoDato>
void BSTree<TipoDato>::eliminar ( const TipoDato &d ) {
	if ( !this->estaVacio ( ) )
		eliminar ( raiz, d );
}

template <class TipoDato>
BSTree<TipoDato>::~BSTree ( ) {
	if ( !estaVacio ( ) )
		destruir ( this->raiz );
}

#endif // BSTREE_H

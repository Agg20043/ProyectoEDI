//============================================================================
// Name        : Cola.h
// Author      : Profesores de EDI
// Version     : 1.0
// Description : Template Cola (implementación basada en punteros)
//============================================================================

#ifndef COLA_H_
#define COLA_H_

#include <iostream>
using namespace std;

template <class TipoDato> class Cola {

private:
	/**
	* Clase genérica Nodo (sólo accesible para el template Cola).
	* Modela los nodos que se almacenan en la Cola.
	* Cada Nodo contiene un dato de tipo TipoDato y un puntero al siguiente nodo.
	*/
	class Nodo {
	public:
		TipoDato  dato;
		Nodo     *sig;
		Nodo (const TipoDato &dato) {
			this->dato = dato;
			this->sig= nullptr;
		}

	};

	typedef Nodo *PtrNodo;
	PtrNodo ini;
	PtrNodo fin;

public:
	// PRE: ---
	// DES: Constructor por defecto. Crea una cola vacía
	// COM: O(1)
	Cola ( );

	// PRE: this->estaVacia () = false
	// DES: Devuelve el primer elemento de la cola.
	// COM: O(1)
	TipoDato getPrimero ( ) const;

	// PRE: this->estaVacia () = false
	// DES: Devuelve en d el primer elemento de la cola.
	// COM: O(1)
	void getPrimero ( TipoDato &d ) const;

	// PRE: ---
	// DES: Devuelve true si la cola está vacía; false en caso contrario.
	// COM: O(1)
	bool estaVacia ( ) const;


	void encolar ( const TipoDato &d );


	void desencolar ( );


	~Cola ( );
};

template <class TipoDato>
Cola<TipoDato>::Cola ( ) {
	ini = nullptr;
	fin = nullptr;
}

template <class TipoDato>
TipoDato Cola<TipoDato>::getPrimero ( ) const {
	return ini->dato;
}

template <class TipoDato>
void Cola<TipoDato>::getPrimero ( TipoDato &d ) const {
	d = ini->dato;
}

template <class TipoDato>
bool Cola<TipoDato>::estaVacia ( ) const {
	return ini == nullptr;
}

template <class TipoDato>
void Cola<TipoDato>::encolar ( const TipoDato &d ) {
	PtrNodo p = new Nodo ( d );
	if ( estaVacia ( ) )  {
		ini = p;
	}
	else {
		fin->sig = p;
	}
	fin = p;
}

template <class TipoDato>
void Cola<TipoDato>::desencolar ( ) {
	PtrNodo p;
	if ( ! estaVacia ( ) ) {
		p = ini;
		if ( ini == fin ) {		// Solo queda un elemento => tras desencolar la cola queda vacía
			ini = nullptr;
			fin = nullptr;
		}
		else {
			ini = ini->sig;
		}
		delete p;
	}
}

template <class TipoDato>
Cola<TipoDato>::~Cola( ) {
	while ( !estaVacia ( ) ) {
		desencolar ( );
	}
}

#endif /* COLA_H_ */

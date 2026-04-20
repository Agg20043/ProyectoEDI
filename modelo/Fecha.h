//
// Created by xalva on 16/02/2026.
//

#ifndef UNTITLED3_FECHA_H
#define UNTITLED3_FECHA_H
#include <string>

using namespace std;
class Fecha {
    int dia;
    int mes;
    int anio;
public:

//Pre:
//Post: Construye una fecha parametrizada
//Complejidad: o(1)
    Fecha(int dia, int mes, int anio){
          dia(dia),
          mes(mes),
          anio(anio) 
    }

//Pre:
//Post: Por defecto construye una fecha
//Complejidad:o(1)
    Fecha();

//Pre:
//Post: Construye una fecha copiandose de otra fecha dada
//Complejidad: O(1)
    Fecha(const Fecha &otra);

//Pre:
//Post: Getter que devuelve el dia de una fecha
//Complejidad: O(1)
    int getDia() const;

//Pre:
//Post: Getter que devuelve el mes de una fecha
//Complejidad:O(1)
    int getMes() const;

//Pre:
//Post: Getter que devuelve el año de una fecha
//Complejidad:O(1)
    int getAnio() const;

//Pre:
//Post: Setter que modifica el dia de una fecha
//Complejidad:O(1)
    void setDia(int dia);

//Pre:
//Post: Setter que modifica el mes de una fecha
//Complejidad:O(1)
    void setMes(int mes);

//Pre:
//Post: Setter que modifica el año de una fecha
//Complejidad:O(1)
    void setAnio(int anio);


//Pre:
//Post: Muestra por pantalla una fecha con su día, mes y año
//Complejidad:O(1)
    void mostrar() const;

//Pre:
//Post: Devuelve una fecha en forma de string
//Complejidad:O(1)
    string pasarCadena() const;
};




#endif //UNTITLED3_FECHA_H

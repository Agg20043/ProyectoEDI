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
//Complejidad:
    int getMes() const;

//Pre:
//Post:
//Complejidad:
    int getAnio() const;

//Pre:
//Post:
//Complejidad:
    void setDia(int dia);

//Pre:
//Post:
//Complejidad:
    void setMes(int mes);

//Pre:
//Post:
//Complejidad:
    void setAnio(int anio);


//Pre:
//Post:
//Complejidad:
    void mostrar() const;

//Pre:
//Post:
//Complejidad:
    string pasarCadena() const;
};




#endif //UNTITLED3_FECHA_H

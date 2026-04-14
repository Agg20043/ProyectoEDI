//
// Created by xalva on 16/02/2026.
//

#ifndef UNTITLED3_FECHA_H
#define UNTITLED3_FECHA_H
#include <string>

class Fecha {
    int dia;
    int mes;
    int anio;
public:
    Fecha(int dia, int mes, int anio)
        : dia(dia),
          mes(mes),
          anio(anio) {
    }

    Fecha();

    Fecha(const Fecha &otra);

    int getDia() const;

    int getMes() const;

    int getAnio() const;

    void setDia(int dia);

    void setMes(int mes);

    void setAnio(int anio);



    void mostrar() const;

    std::string pasarCadena() const;
};




#endif //UNTITLED3_FECHA_H
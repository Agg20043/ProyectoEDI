//
// Created by xalva on 16/02/2026.
//

#include "../modelo/Fecha.h"
#include <iostream>
#include <string>
using namespace std;


Fecha::Fecha() {
    cout << "Constructor Fecha defecto";
    dia = 1;
    mes = 1;
    anio = 1982;
}



Fecha::Fecha(const Fecha& otra) {
    cout << "Constructor Fecha por copia";
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}


int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int dia) { this->dia = dia; }
void Fecha::setMes(int mes) { this->mes = mes; }
void Fecha::setAnio(int anio) { this->anio = anio; }

void Fecha::mostrar() const {
    cout << dia << "/" << mes << "/" << anio << endl;
}

string Fecha::pasarCadena() const {
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio)  ;
}
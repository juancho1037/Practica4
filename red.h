#ifndef RED_H
#define RED_H

#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include "router.h"

using namespace std;

class Red
{
private:
    vector<Router> Vrouters;

public:
    Red();

    void asignarEnrutador(Router dispositivo);

    void nuevoRouter(char Nombre);
    void eliminarRouter(Router dispositivo);

    void GenerarRed(void);

    Router obtenerRouter(char nombre);
    vector<Router> obtenerRouter();

    void actualizarRouter(Router enrutador);
    void actualizarRelaciones(char nombre);
    bool existeRouter(char nombre);

    int obtenerCostoTotal(char Ra, char Rb);
    void obtenerMejorRuta(char Ra, char Rb, string &ruta);
    void verRouter();
    void verCamino();

    map<char,int>calcular(Router primero, Router final, vector<char>relaciones, int costo, int numero, bool bandera);
    void crear();

    int cargarArchivo(string nombre);

};

#endif // RED_H


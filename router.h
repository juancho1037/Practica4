#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Router
{

private:
    char nombre;
    map<char, int>enrutador;
    map<char, map<char, int>> ruta;

public:
    Router(char nombre);

    void asignarEnrutador(char nombre, int cantidad);
    void eliminarEnrutador(char nombre);

    void asignarRuta(char nombre, char vecino, int cantidad);
    void eliminarRuta();
    void actualizarRuta(char nombre, int cantidad);

    char obtenerNombre(void);
    int obtenerCantidadEnrutadores();

    bool verificar(char nombre);

    //Funcion que retorna las rutas
    map<char, map<char, int>> obtenerRuta();

    //Funcion que retorna los enrutadores
    map<char,int> obtenerEnrutadores(const vector<char> &routers);
};

#endif // ROUTER_H

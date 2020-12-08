#include "router.h"

Router::Router(char nombre)
{
    this->nombre=nombre;
}

void Router::asignarEnrutador(char nombre, int cantidad)
{
    this->enrutador[nombre]=cantidad;
}

void Router::eliminarEnrutador(char nombre)
{
    this->enrutador.erase(nombre); //Usamos el metodo erase propio de la libreria mapa.
}

void Router::asignarRuta(char nombre, char Nombre, int cantidad)
{
    map<char, int> nuevo;//creamos el nuevo vecino
    nuevo[nombre]= cantidad;//asignamos el nombre y el costo

    this->ruta[Nombre]=nuevo;//Lo agregamos a nuestra Red
}

void Router::eliminarRuta()
{
    this->ruta.clear();
}

void Router::actualizarRuta(char nombre, int cantidad)
{
    this->enrutador[nombre]=cantidad;
}

char Router::obtenerNombre()
{
    return this->nombre;
}

int Router::obtenerCantidadEnrutadores()
{
    map<char,int>enrutador = this->enrutador;
    enrutador.erase(this->obtenerNombre());
    return enrutador.size();
}

bool Router::verificar(char nombre)//Verificamos si existe algun enrutador conocido
{
    bool bandera=false;
    for(auto const &i: this->enrutador){
        if(i.first==nombre){
            bandera = true;
            break;
        }
    }
    return bandera;
}

map<char, map<char, int> > Router::obtenerRuta()
{
    return this->ruta;
}

map<char, int> Router::obtenerEnrutadores(const vector<char> &routers)
{
    map<char,int>Enrutadores = this->enrutador;
    vector<char>::const_iterator it; //Creamos un iterador para recorrer el vector

    for (it = routers.begin(); it!=routers.end() ; it++)
    {
        Enrutadores.erase(*(it));
    }
    return Enrutadores;
}

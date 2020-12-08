#include <iostream>

#include "router.h"
#include "red.h"

using namespace std;

Red conexion;
bool solicitar(char *nombre);

enum{NUEVO_ROUTER = 1,
    NUEVA_RELACION,
    GENERAR_RED_ALEATORIA,
    ELIMINAR_ROUTER,
    VISUALIZAR_ROUTERS,
    CAMBIAR_COSTO,
    VISUALIZAR_COSTO,
    VISUALIZAR_RUTA,
    VISUALIZAR_TABLA,
    CARGAR_ARCHIVO,
    TERMINAR};


int main()
{
    int opcion (0);
    do {

        cout<<endl;
        cout<<"                ...::: BIENVENIDO :::... "<<endl;

        cout<<"...::: ADMINISTRACION DE LA RED DE COMUNICACIONES :::... "<<endl;

        cout<<endl<<"         ...::: MENU PRINCIPAL :::... ";
        cout<<endl<<"      ::: 1 ::: NUEVO ROUTER ";
        cout<<endl<<"      ::: 2 ::: NUEVA RELACION ";
        cout<<endl<<"      ::: 3 ::: GENERAR RED ALEATORIA ";
        cout<<endl<<"      ::: 4 ::: ELIMINAR ROUTER ";
        cout<<endl<<"      ::: 5 ::: VISUALIZAR ROUTERS ";
        cout<<endl<<"      ::: 6 ::: CAMBIAR COSTO ";
        cout<<endl<<"      ::: 7 ::: VISUALIZAR COSTO ";
        cout<<endl<<"      ::: 8 ::: VISUALIZAR RUTA ";
        cout<<endl<<"      ::: 9 ::: VISUALIZAR TABLA DE ENRUTAMIENTO ";
        cout<<endl<<"      ::: 10 :: CARGAR ARCHIVO ";
        cout<<endl<<"      ::: 11 ::: SALIR "<<endl;

        cout<<endl<<"            ::: Opcion: ";cin>>opcion;

        switch (opcion) {

        case NUEVO_ROUTER:{
            char nombre;

            unsigned short int cantidad=0;
            cout<<"     ...::: Cantidad de Routers que quiere ingresar: "; cin>>cantidad;cout<<endl<<endl;

            bool bandera=false;
            vector<Router>::iterator it;
            for (unsigned short int i=0; i<cantidad; i++) {
                cout<<endl<<"       ...::: Ingrese el nombre del router: ";cin>>nombre;

                for (it = conexion.obtenerRouter().begin() ; it != conexion.obtenerRouter().end() ; it ++) {
                    if(nombre == it->obtenerNombre()){
                        bandera = true;
                        cout<<endl<<"       ...::: ADVERTENCIA: "<<endl;
                        cout<<"             ...::: El router con el nombre "<< nombre <<" ya no esta disponible."<<endl;
                        break;
                    }
                }
                if(!bandera){   //Validacion de la bandera, si es falso encontes no encontro coincidencia y agregue el router nuevo
                    conexion.nuevoRouter(nombre);
                }
            }
            break;
        }

        case NUEVA_RELACION:{
            char nombres[2]={};
            int costo=0;

            if(!solicitar(nombres)){
                continue;
            }
            cout<<endl<<"       ...::: Ingrese el COSTO de la nueva relacion ";cin>>costo;cout<<endl;

            //verificar que la entrada no sea cero o negativo
            if(costo>0){
                Router primero = conexion.obtenerRouter(nombres[0]);
                Router segundo = conexion.obtenerRouter(nombres[1]);

                primero.asignarEnrutador(nombres[1],costo);
                segundo.asignarEnrutador(nombres[0],costo);

                conexion.actualizarRouter(primero);
                conexion.actualizarRouter(segundo);
                conexion.crear();
            }
            else{
                cout<<endl<<"   ...::: ADVERTENCIA: "<<endl;
                cout<<"         ...::: El costo no puede ser menor o igual a cero."<<endl;
            }
            system("pause");
            break;
        }

        case GENERAR_RED_ALEATORIA:{
            conexion.GenerarRed();
            system("pause");
            break;
        }

        case ELIMINAR_ROUTER:{
            char nombre;
            cout<<endl<<"       ...::: Ingrese el nombre del router: ";cin>>nombre;cout<<endl<<endl;

            if(conexion.existeRouter(nombre)){
                conexion.eliminarRouter(conexion.obtenerRouter(nombre));
            }
            else{
                cout<<endl<<"   ...::: ADVERTENCIA: "<<endl;
                cout<<"         ...::: El router con el nombre "<< nombre <<" NO existe."<<endl;
            }
            system("pause");
            break;
        }
        case VISUALIZAR_ROUTERS:{
            conexion.verRouter();
            system("pause");
            break;
        }
        case CAMBIAR_COSTO:{
            char nombres[2]={};

            if(!solicitar(nombres)){
                continue;
            }

            Router uno = conexion.obtenerRouter(nombres[0]);
            Router dos = conexion.obtenerRouter(nombres[1]);

            if(!uno.verificar(nombres[1])){
                cout<<endl<<"       ...::: ADVERTENCIA :::... "<<endl;
                cout<<"             ...::: Los Routers no estan relacionados."<<endl;
            }
            else {
                int costo = 0;
                cout<<endl<<"       ...::: Cual es el nuevo costo de la conexion: ";
                cin>> costo;

                if(costo < 0){
                    cout<<endl<<"       ...::: ADVERTENCIA :::... "<<endl;
                    cout<<"             ...::: El costo no puede ser igual o menor a cero."<<endl;
                }
                else{
                    uno.actualizarRuta(nombres[1],costo);
                    dos.actualizarRuta(nombres[0],costo);

                    conexion.actualizarRouter(uno);
                    conexion.actualizarRouter(dos);
                    conexion.crear();
                }
            }
            system("pause");
            break;

        }
        case VISUALIZAR_COSTO:{
            char nombres[2]={};

            if(!solicitar(nombres)){
                continue;
            }
            int respuesta = conexion.obtenerCostoTotal(nombres[0],nombres[1]);

            if(respuesta == -1){
                cout<<endl<<"       ...::: Los elementos "<<nombres[0]<<" y "<<nombres[1]<<" no estan relacionados."<<endl;
            }
            else{
                cout<<endl<<"       ...::: El costo de enviar "<<nombres[0]<<" a "<<nombres[1]<< "es: "<<respuesta<<endl;
            }
            system("pause");
            break;
        }
        case VISUALIZAR_RUTA:{
            char nombres[2]={};

            if(!solicitar(nombres)){
                continue;
            }
            string ruta="";
            conexion.obtenerMejorRuta(nombres[0] , nombres[1], ruta);
            cout<<endl<<"       ...::: La major ruta para enviar informacion de "<<nombres[0]<<" a "<<nombres[1]<<" es: "<<ruta<<endl;
            system("pause");
            break;
        }
        case VISUALIZAR_TABLA:{
            conexion.verCamino();
            system("pause");
            break;
        }
        case CARGAR_ARCHIVO:{
            string nombre = "";
            cout<<endl<<"       ...::: Ingrese el nombre del archivo: "; cin>> nombre;

            int verificador = conexion.cargarArchivo("C:/Users/juanc/Desktop/INFORMATICA 2/Practica4/"+nombre);
            if (verificador == -1){
                cout<<endl<<"       ...::: ADVERTENCIA :::... "<<endl;
                cout<<"             ...::: Apreciado usuario, ha ocurrido un error leyendo el archivo. "<<endl;
            }
            else if(verificador == -2){
                cout<<endl<<"       ...::: ADVERTENCIA :::... "<<endl;
                cout<<"             ...::: Apreciado usuario, no se ha podido abrir el archivo. "<<endl;
            }
            system("pause");
            break;
        }
        case TERMINAR:{
            cout<<"\n           ...::: Saliendo del sistema...";
            system("pause");
            break;
        }
        default:
            cout<<"\n           ...::: No introdujo una seleccion valida. Intente de nuevo."<<endl;
            system("pause");
            break;
        }
        system("cls");
    } while (opcion != TERMINAR);
    return (0);
}


bool solicitar(char *nombre){
    bool bandera = true;

    for (short int i=1 ; i<3; i++) {
        cout<<endl;
        cout<<"         ...::: Ingrese el nombre del Router: "; cin>> nombre[i];

        if(! conexion.existeRouter(nombre[i])){
            cout<<endl;
            cout<<"         ......::: IMPORTANTE: "<<endl;
            cout<<"         ......::: El router"<<nombre[i]<<" no existe."<<endl;

            bandera=false;
            break;
        }
    }
    return bandera;
}

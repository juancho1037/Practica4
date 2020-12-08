#include "red.h"
#include <iomanip>

Red::Red()
{

}

void Red::asignarEnrutador(Router dispositivo)
{
    this->Vrouters.push_back(dispositivo);
}

void Red::nuevoRouter(char Nombre)
{
    Router dispositivo(Nombre);
    dispositivo.asignarEnrutador(Nombre,0);//Agregamos la relacion a si mismo, esta no cambia, es cero.
    this->asignarEnrutador(dispositivo);
}

void Red::eliminarRouter(Router dispositivo)
{
    char N=dispositivo.obtenerNombre();
    vector<Router>::iterator it;

    for(it=this->Vrouters.begin() ; it !=this->Vrouters.end() ; it++){
        if(dispositivo.obtenerNombre() == (it)->obtenerNombre())
        {
            break;
        }
    }
    this->Vrouters.erase(it); //Eliminar el enrutador justo donde se encuentra el iterador
    this->actualizarRelaciones(N);//Actualiza el mapa de la red, eliminando el router deseado
}

void Red::GenerarRed()
{
    string lETRAS="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(time(NULL));
    unsigned int cR= 2+rand() % (10-2); //Creamos un numero aleatorio para controlar la cantidad de routers

    int aux=0; //variable auxiliar
    int cr=cR; //copia cantidad de relaciones

    vector<char> NOMBRES; //vector que almacenara los routers creados

    while (NOMBRES.size() < cR) { //Mientras la dimension del vector sea menor a la cantidad de routers
        int posicion = rand() % (lETRAS.length()-1);//obtenemos un valor logico
        bool bandera = true;

        vector<char>::iterator it; //creamos un iterador para recorrer el vector de routers
        for (it=NOMBRES.begin() ; it != NOMBRES.end(); it++) { //creamos el ciclo que recorre el vector de routers
            if (lETRAS.at(posicion) == *it){ //condicion para verificar que la posicion escogida no este ya dentro del vector de routers
                bandera = false;
                break;
            }
        }
        if(bandera)
        {
            aux +=(cr-- -1);//actualizamos la variable r
            NOMBRES.push_back(lETRAS.at(posicion));//agregamos el router al vector siempre y cuando no exista
            this->nuevoRouter(lETRAS.at(posicion));//creamos los routers en nuestra Red
        }
    }

    //Obtenemos el numero de relaciones
    cr = cR + rand() % (aux-cR); //Debe ser el mismo que nR para poder agregar los costos
    aux=0;

    vector<char>relaciones; //Creamos el vector para almacenar la realciones de los routers
    char na; // dos char para almacenar los nombres de los dos routers que se van a relacionar
    char nb;

    while (aux<cr) { //Ciclo para crear las relaciones entre dos routers
        int a = rand() % NOMBRES.size(); //creamos una variable que escoja uno de los routers creados que estan en el vector R de routers
        na = *(NOMBRES.begin()+a); // Elemento a

        //primera relacion
        if (aux == 0) {
            int b= rand() % (NOMBRES.size()-1);
            nb = *(NOMBRES.begin()+b); //Elemento b

            if (a == b){ // Cuando son el mismo nombre entonces vuelva y empiece
                continue;
            }
            Router enrA(this->obtenerRouter(na));
            Router enrB(this->obtenerRouter(nb));

            int costoRuta= 1+rand()%19; //Creamos un valor elatorio para el costo de la relacion

            //Asignamos los costos a los routers relacionados
            enrA.asignarEnrutador(nb,costoRuta);
            enrB.asignarEnrutador(na,costoRuta);

            this->actualizarRouter(enrA);
            this->actualizarRouter(enrB);

            //Agregamos al vector las relaciones creadas
            relaciones.push_back(na);
            relaciones.push_back(nb);
            aux ++;
        }
        else{//a partir de la segunda iteracion, entra aca.
            int b=rand()%(relaciones.size()-1);
            nb= *(relaciones.begin()+b);
            Router enrB(this->obtenerRouter(nb));

            //Verificamos si ya la relacion entre na y nb existe
            if (enrB.verificar(na)){ //si verificar retorna true, entonces ya existe la relacion y por tanto vuelve a empezar el ciclo
                continue;
            }
            //Ahora verificamos si el router existe
            bool bandera=false;
            vector<char>::iterator it;
            for(it=relaciones.begin() ; it != relaciones.end() ; it++){
                if(*it == na){
                    bandera=true;
                    break;
                }
            }
            //verificamos la bandera
            if(!bandera){
                relaciones.push_back(na);
            }
            Router enrA(this->obtenerRouter(na));

            int costoRuta = 1+rand()%19;

            //Asignamos los costos a los routers relacionados
            enrA.asignarEnrutador(nb,costoRuta);
            enrB.asignarEnrutador(na,costoRuta);

            this->actualizarRouter(enrA);
            this->actualizarRouter(enrB);
            aux++;
        }
    }
    cout<< "...::: Generacion de Red Aleatoria Finalizada :::... "<<endl<<endl;
    this->crear();
}


Router Red::obtenerRouter(char nombre)
{
    vector<Router>::iterator it;
    for (it=this->Vrouters.begin(); it != this->Vrouters.end(); it++)
    {
        if (nombre == it->obtenerNombre()){
            break;
        }
    }
    return *it;
}

vector<Router> Red::obtenerRouter()
{
    return this->Vrouters;
}

void Red::actualizarRouter(Router enrutador)
{
    vector<Router>::iterator it;
    for (it=this->Vrouters.begin(); it != this->Vrouters.end(); it++)
    {
        if (it->obtenerNombre() == enrutador.obtenerNombre()){
            *(it) = enrutador;
        }
    }
}

void Red::actualizarRelaciones(char nombre)
{
    vector<Router>::iterator it;
    for (it=this->Vrouters.begin() ; it != this->Vrouters.end() ; it++)
    {
        map<char, int> relaciones(it->obtenerEnrutadores({})); //Obtenemos el mapa de la red

        for(auto const &i:relaciones)
        {
            if(i.first == nombre){
                it->eliminarEnrutador(nombre);
            }
        }
    }
    this->crear(); //Volvemos a crear la tabla, ya que se elimino una relacion, por tando el mapa queda desactualizado
}

bool Red::existeRouter(char nombre)
{
    bool bandera=false;
    vector<Router>::iterator it;
    for (it=this->Vrouters.begin(); it != this->Vrouters.end(); it++){
        if(nombre == it->obtenerNombre()){
            bandera = true;
            break;
        }
    }
    return bandera;
}

int Red::obtenerCostoTotal(char Ra, char Rb)
{
    int costo=-1;
    Router enrutador = this->obtenerRouter(Ra);
    map<char,map<char, int>> relaciones(enrutador.obtenerRuta());//Obtengo las realciones

    //Recorremos las relaciones para llegar a B y obtener el costo
    for(auto const &transporte : relaciones){
        if(transporte.first == Rb){
            map<char,int>mapa(transporte.second);
            costo = mapa.begin()->second;
            break;
        }
    }
    return costo;
}

void Red::obtenerMejorRuta(char Ra, char Rb, string &ruta)
{
    Router enrutador = this->obtenerRouter(Ra);
    map<char,map<char, int>> relaciones(enrutador.obtenerRuta());

    for(auto const &transporte : relaciones)
    {
        if(transporte.first == Rb)
        {
            map<char,int>mapa = transporte.second;
            char costo = mapa.begin()->first;
            ruta+= costo;

            if(costo == Rb)
                break;
            //vuelve y se llama a si misma, lo hace una vez, y sigue haciendolo hasta encontrar el menos costo
            obtenerMejorRuta(costo, Rb, ruta);
        }
    }
}

void Red::verRouter()
{
    cout << endl;
    cout << "   ...::: La Red contiene " << this->Vrouters.size() << " routers." << endl;

    vector<Router>::iterator it;
    for (it = this->Vrouters.begin() ; it != this->Vrouters.end() ; it++)
    {
        cout << endl;
        cout << "    ...::: Enrutador " << it->obtenerNombre() << endl;
        vector<char> nombres;
        map<char, int> mapa(it->obtenerEnrutadores(nombres));
        for(auto const &n : mapa)
        {
            cout << "          |- " <<n.first << " con costo de: " << n.second <<endl;
        }
    }
}

void Red::verCamino()
{
    vector<Router>::iterator it;
    for (it = this->Vrouters.begin() ; it != this->Vrouters.end(); it++){
        map<char, map<char, int>> rutas(it->obtenerRuta());
        cout<<endl<<" ...::: Red de Conexiones de: "<<it->obtenerNombre()<<endl;

        for(auto const &i : rutas){
            cout<<" |"<< i.first <<": ";
            map<char, int> mapa(i.second);
            if (mapa.begin()->second == -1){
                cout << "  ";
            }
            else{
                cout << mapa.begin()->first << "," << mapa.begin()->second << " ";
            }
        }
        cout << endl;
    }
}


map<char, int> Red::calcular(Router primero, Router final, vector<char> relaciones, int costo, int numero, bool bandera)
{
    map<char,int>matriz;
    matriz[primero.obtenerNombre()] = 1000;
    if(primero.obtenerNombre() == final.obtenerNombre()){ //Condicion cuando el router inicial y final son iguales, siempre tiene valor cero
        matriz[primero.obtenerNombre()] = 0;
        return matriz;
    }

    map<char,int> enrutamiento(primero.obtenerEnrutadores(relaciones));
    int aux=0;

    for(auto const &i: enrutamiento){ //Ciclo de recorrido del mapa, eliminando basura
        if(bandera && relaciones.size() >1){
            relaciones.pop_back();
        }

        Router router = this->obtenerRouter(i.first);
        if(i.first == final.obtenerNombre()){

            if((aux-numero) > 0){
                costo = (aux-numero);
            }
            costo += (i.second +numero);

            if(costo < matriz.begin()->second){
                matriz.clear();
                matriz[i.first] = costo;
            }
            costo = 0;
        }
        else{
            relaciones.push_back(i.first);
            costo += numero;

            map<char,int> matriz2(this->calcular(router,final,relaciones,costo,i.second, false)); //Se vuelve a llamar a si misma con los nuevos valores

            if(matriz2.begin()->second < matriz.begin()->second){ //verificar los costos de los enrutadores
                matriz.clear();
                matriz[i.first] = matriz2.begin()->second;
            }
            aux=costo;
            costo =0;
        }
    }
    return matriz;
}

void Red::crear()
{
    vector<char>NOMBRE;
    vector<Router>::iterator it;

    for(it = this->Vrouters.begin(); it != this->Vrouters.end() ; it++){
        it->eliminarRuta(); //Eliminamos la basura

        vector<Router>::iterator it2;
        for(it2 = this->Vrouters.begin() ; it2 != this->Vrouters.end() ; it2++){
            NOMBRE.clear();
            NOMBRE.push_back(it->obtenerNombre());
            map<char,int>matriz;
            matriz = (this->calcular(*it,*it2,NOMBRE,0,0,true));
            it->asignarRuta(matriz.begin()->first, it2->obtenerNombre(), matriz.begin()->second == 1000 ? -1 : matriz.begin()->second);
        }
    }
}

int Red::cargarArchivo(string nombre)
{
    int verificador= -1;
    ifstream archivo;
    archivo.open(nombre);

    if(archivo.is_open()){
        char caracter;
        bool bandera = false;

        string datos = "";
        bool ban = false;

        while (archivo.get(caracter)) {
            if(caracter == '\n' && bandera){
                if(datos.length() > 1){
                    ban = true;
                }

                //Crearemos los Routers
                if(!ban){
                    this->nuevoRouter(datos.at(0));
                }
                else{//Creamos las conexiones
                    char uno = datos.substr(0,1).at(0);
                    char dos = datos.substr(2,1).at(0);

                    string nombre = datos.substr(4,(datos.length()-4));
                    int vecino = atoi(nombre.c_str());

                    Router a = this->obtenerRouter(uno);
                    Router b = this->obtenerRouter(dos);

                    a.asignarEnrutador(dos,vecino);
                    b.asignarEnrutador(uno,vecino);

                    this->actualizarRouter(a);
                    this->actualizarRouter(b);
                }
                datos = "";
                bandera = false;
            }
            else{
                datos += caracter;
                bandera = true;
            }
        }
        //Creamos la Tabla de enrutamiento
        this->crear();
        verificador = 1;
    }
    else {
        verificador=-2; //si toma este valor, hay un error
    }
    archivo.close();
    return verificador;
}

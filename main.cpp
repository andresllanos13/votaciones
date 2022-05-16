#include <iostream>
#include "ListaUsuarios.h"
#include "ListaAdministradores.h"
#include "ListaCandidatos.h"
using namespace std;

ListaUsuarios listaUsuarios;
ListaCandidatos listaCandidatos;

void menuAdmin(){ //MENU PARA EL USUARIO ADMINISTRADOR
    int op;
    do{
        cout << "MODO ADMINISTRADOR" << endl;
        cout << "1. Administrar Usuarios\n2. Administrar Candidatos\n3. Ver estadisticas\n4. Finalizar votaciones\n";
        cin >> op;
        system("cls");
        switch (op){
            case 1:
                //FUNCIONES
                break;
            case 2:
                //MAS FUNCIONES
                break;
            case 3:
                //MAAAAS FUNCIONES
                break;
            case 4:
                //MUCHO TEXTO
                break;
            case 0:
                //REGRESAR O SALIR
                break;
            default:
                cout << "Ingrese una funcion válida" << endl;
        }
    }while (op!=0);
}

void menuvotante(){
	int op;
	int clave, cedula;
    do{
        //cout << "Usted esta incrito en la region: "<<endl<<Usuario.region<<endl; ;
        cout << "Ingrese la opcion que desea "<<endl;
        cout << "Recuerde guardar su voto para que sea contado"<<endl;
        cout << "1. Ver candidatos\n.2. Votar\n3. Guardar voto\n0. Salir"<<endl;
        cin>>op;
        switch (op){
            case 1:
                //funcion que muestra los candidatos 
                break;
            case 2:
                //funcion que retorna el valor de el voto
                break;
            case 3:
                //esta funcion guarda el voto definitivo y solo se podra usar una vez
                break;
            case 0:
                //REGRESAR O SALIR
                break;
            default:
                cout << "Ingrese una funcion válida" << endl;
        }                         
    }while(op!=0);
}

void menuReportero(){
	int op;
	int usuario3;
    cout<<"MODO REPORTERO"<<endl;
    do{
        // cout<<"usted esta reportando "<<endl<<Usuario.region<<endl; ;
        cout<<"Ingrese la opcion que desea:"<<endl;
        cout<<"1. Candidato con mayoria de votos\n2.Ver tabla de votos actual\n3. Ganador por regiones\n4. Dos candidatos mejor posicionados\n5. Saber si hay segunda vuelta\n0. Salir"<<endl;
        cin>>op;
        switch (op){
            case 1:
                //Funcion que muestra quien va ganando 
                break;
            case 2:
                //Funcion muestra el total de votos para cada candidato
                break;
            case 3:
                //Esta funcion muestra quien gana en cada region 
                break;
            case 4:
                //Esta funcion muestra los dos candidatos mas votados 
                break;
            case 5:
                //esta funcion muestra si hay segunda vuelta y quienes son los dos candidatos 
                break;
            case 0:
                //salir
            default:
                cout << "Ingrese una funcion válida" << endl;
        }      
    }while(op!=0);
}

int main(){
    iniciarListaAdmin();
    mostrarListaAdmin();

    system("pause");
    return 0;
}
#include <iostream>
#include "ListaUsuarios.h"
using namespace std;

FILE *archivoUsuarios;
ListaUsuarios listaUsuarios;

//CADENAS DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_USUARIO_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";

//Leer los datos del archivo usuarios.txt y guardarlos en la estructura
void inicListaUsuarios(){
    int i=0;
    fopen_s(&archivoUsuarios, "Datos/usuarios.txt", "r+");
    fseek(archivoUsuarios, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoUsuarios, FORMATO_USUARIO_OUT, listaUsuarios.usuario[i].nombre, &listaUsuarios.usuario[i].cedula, &listaUsuarios.usuario[i].edad, listaUsuarios.usuario[i].region, &listaUsuarios.usuario[i].clave);
        i++;
    }
    fclose(archivoUsuarios);
}

//Imprimir la estructura de usuarios (No necesario)
void mostrarListaUsuario(){
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0'){
            cout << i+1 << endl;
            cout << "Nombre: " << listaUsuarios.usuario[i].nombre << endl;
            cout << "Cedula: " << listaUsuarios.usuario[i].cedula << endl;
            cout << "Edad: " << listaUsuarios.usuario[i].edad << endl;
            cout << "Region: " << listaUsuarios.usuario[i].region << endl;
            cout << "Clave: " << listaUsuarios.usuario[i].clave << endl;
        }
    }
}

//Buscar si la cedula corresponde a un usuario y retornar su clave para validarla
int buscarUsuario(int cedula){
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            return listaUsuarios.usuario[i].clave;
        }
    }
    return -1;
}

//Busca la cedula que corresponde a un usuario y retorna su posicion en el arreglo
int buscarNumeroUsuario(int cedula){
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            return i;
        }
    }
    return -1;
}

//MENU PARA EL USUARIO VOTANTE
void menuVotante(int numeroUsuario){ 
	int op;
    do{
        cout << "SISTEMA DE VOTACION" << endl;
        cout << "USUARIO: " << listaUsuarios.usuario[numeroUsuario].cedula << "\t" << listaUsuarios.usuario[numeroUsuario].nombre << endl;
        cout << "Ingrese la opcion que desea "<<endl;
        cout << "Recuerde guardar su voto para que sea contado"<<endl;
        cout << "1. Ver candidatos\n2. Votar\n3. Cambiar Voto\n4. Guardar voto\n0. Salir (Cerrar sesion)"<<endl;
        cin>>op;
        system("cls");
        switch (op){
            case 1:
                //funcion que muestra los candidatos 
                break;
            case 2:
                //funcion que retorna el valor de el voto
                break;
            case 3:
                //esta funcion cambia el voto
                break;
            case 4:
                //esta funcion guarda el voto definitivo y solo se podra usar una vez
                break;
            case 0:
                //REGRESAR O SALIR
                cout << "Cerrando sesion..." << endl;
                break;
            default:
                cout << "Ingrese una funcion valida" << endl;
        }                         
    }while(op!=0);
}

//MENU PARA EL USUARIO REPORTERO
void menuReportero(){
	int op;
    do{
        cout<<"MODO REPORTERO"<<endl;
        cout<<"Ingrese la opcion que desea:"<<endl;
        cout<<"1. Candidato con mayoria de votos\n2.Ver tabla de votos actual\n3. Ganador por regiones\n4. Dos candidatos mejor posicionados\n5. Saber si hay segunda vuelta\n0. Salir"<<endl;
        cin>>op;
        system("cls");
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
                cout << "Ingrese una funcion valida" << endl;
        }      
    }while(op!=0);
}
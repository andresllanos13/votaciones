#include <iostream>
#include <string.h>
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

FILE *archivoUsuarios;
ListaUsuarios listaUsuarios;

//CADENAS DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_USUARIO_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";
const char* FORMATO_USUARIO_IN = "{\n\t\"nombre\": \"%s\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%s\",\n\t\"clave\":%d\n}\n";

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

//REGISTRAR NUEVO USUARIO
void agregarUsuario(){
    char nombre[50];
    int cedula;
    int edad;
    char region[30];
    int clave;

    cout << "Ingrese el nombre del nuevo usuario: ";
    fflush(stdin);
    gets(nombre);
    cout << "Ingrese la cedula: ";
    fflush(stdin);
    cin >> cedula;
    cout << "Ingrese la edad: ";
    fflush(stdin);
    cin >> edad;
    cout << "Ingrese la region del nuevo usuario: ";
    fflush(stdin);
    gets(region);
    cout << "Ingrese la clave: ";
    fflush(stdin);
    cin >> clave;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] == '\0'){
           for (int j=0; j<strlen(nombre); j++){
               listaUsuarios.usuario[i].nombre[j] = nombre[j];
           }
           for (int j=0; j<strlen(region); j++){
               listaUsuarios.usuario[i].region[j] = region[j];
           }
            listaUsuarios.usuario[i].cedula = cedula;
            listaUsuarios.usuario[i].edad = edad;
            listaUsuarios.usuario[i].clave = clave;
            break;
        }
    }
    actualizarArchivo();
}

//ELIMINAR USUARIO DE LA ESTRUCTURA
void eliminarUsuario(){
    int cedula;
    cout << "Ingrese la cedula a eliminar: ";
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre << endl;
            cout << "Desea eliminarlo? (1. Si, 2. No)" << endl;
            cin >> cedula;
            if (cedula == 1){
                listaUsuarios.usuario[i].nombre[0] = '\0';
                listaUsuarios.usuario[i].region[0] = '\0';
                listaUsuarios.usuario[i].cedula = 0;
                listaUsuarios.usuario[i].edad = 0;
                system("cls");
                cout << "Eliminado exitosamente" << endl;
                break; 
            }
            else{
                system("cls");
                cout << "No se elimino el usuario" << endl;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "No se encontro la cedula" << endl;
        }
    }
    actualizarArchivo();
}

//CAMBIAR LA CLAVE DE UN USUARIO
void cambiarClave(){
    int cedula, clave;
    cout << "Ingrese la cedula: ";
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre << endl;
            cout << "Desea cambiar su clave? (1. Si, 2. No)" << endl;
            cin >> cedula;
            if (cedula == 1){
                cout << "Ingrese su nueva clave: ";
                cin >> clave;
                listaUsuarios.usuario[i].clave = clave;
                system("cls");
                cout << "Clave cambiada exitosamente" << endl;
                break;
            }
            else{
                system("cls");
                cout << "No se elimino el usuario" << endl;
                break;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "No se encontro la cedula" << endl;
        }
    }
    actualizarArchivo();
}

//ACTUALIZAR ARCHIVO DE USUARIOS
void actualizarArchivo(){
    fopen_s(&archivoUsuarios, "Datos/usuarios.txt", "w+");
    fseek(archivoUsuarios, 0, SEEK_SET);
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0'){
            fprintf_s(archivoUsuarios, FORMATO_USUARIO_IN, listaUsuarios.usuario[i].nombre, listaUsuarios.usuario[i].cedula, listaUsuarios.usuario[i].edad, listaUsuarios.usuario[i].region, listaUsuarios.usuario[i].clave);
        }
    }
    fclose(archivoUsuarios);
}
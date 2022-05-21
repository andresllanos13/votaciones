#include <iostream>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

FILE *archivoAdmin;
ListaAdministradores listaAdministradores;

//CADENAS DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_ADMIN_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";

//Leer los datos del archivo administradores.txt y guardarlos en la estructura
void iniciarListaAdmin(){
    int i=0;
    fopen_s(&archivoAdmin, "Datos/administradores.txt", "r+");
    fseek(archivoAdmin, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoAdmin, FORMATO_ADMIN_OUT, listaAdministradores.administradores[i].nombre, &listaAdministradores.administradores[i].cedula, &listaAdministradores.administradores[i].edad, listaAdministradores.administradores[i].region, &listaAdministradores.administradores[i].clave);
        i++;
    }
    fclose(archivoAdmin);
}

//Imprimir la estructura de administradores (No necesario)
void mostrarListaAdmin(){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0]!='\0'){
            cout << i+1 << "." << endl;
            cout << "Nombre: " << listaAdministradores.administradores[i].nombre << endl;
            cout << "Cedula: " << listaAdministradores.administradores[i].cedula << endl;
            cout << "Edad: " << listaAdministradores.administradores[i].edad << endl;
            cout << "Region: " << listaAdministradores.administradores[i].region << endl;
            cout << "Clave: " << listaAdministradores.administradores[i].clave << endl;
        }
        else{
            break;
        }
    }
}

//Buscar si la cedula coincide con un administrador y retornar su clave para validarla
int buscarAdmin(int cedula){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0] != '\0' && listaAdministradores.administradores[i].cedula == cedula){
            return listaAdministradores.administradores[i].clave;
        }
    }
    return -1;
}

//Busca la cedula que coincide con un administrador y retorna su posicion en el arreglo
int buscarNumeroAdmin(int cedula){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0] != '\0' && listaAdministradores.administradores[i].cedula == cedula){
            return i;
        }
    }
    return -1;
}

//MENU PARA EL USUARIO ADMINISTRADOR
void menuAdmin(int numeroUsuario){ 
    int op;
    do{
        cout << "MODO ADMINISTRADOR" << endl;
        cout << "No. " << listaAdministradores.administradores[numeroUsuario].cedula << "\t" << listaAdministradores.administradores[numeroUsuario].nombre << endl;
        cout << "1. Administrar Usuarios\n2. Administrar Candidatos\n3. Ver estadisticas\n4. Finalizar votaciones\n0. Salir\n";
        cin >> op;
        system("cls");
        switch (op){
            case 1:
                administrarUsuarios();
                break;
            case 2:
                //ADMINISTRAR CANDIDATOS
                break;
            case 3:
                //FUNCIONES ESTADISTICAS
                break;
            case 4:
                //FINALIZAR VOTACIONES NO SE COMO
                break;
            case 0:
                //REGRESAR O SALIR
                cout << "Saliendo del modo adminstrador..." << endl;
                break;
            default:
                cout << "Ingrese una funcion válida" << endl;
        }
    }while (op!=0);
}

//MENU DE ADMINISTRAR USUARIOS
void administrarUsuarios(){
    int op;
    do{
        cout << "ADMINISTRAR USUARIOS" << endl;
        cout << "1. Agregar usuario\n2. Eliminar usuario\n3. Cambiar clave de usuario\n0. Volver\n" << endl;
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                agregarUsuario();
                system("cls");
                cout << "Usuario agregado exitosamente" << endl;
                break;
            case 2:
                eliminarUsuario();
                break;
            case 3:
                cambiarClave();
                mostrarListaUsuario();
                break;
            case 0:
                system("cls");
                cout << "Regresando..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida" << endl;
        }
    }while(op!=0);
}

//MENU ADMINISTRAR CANDIDATOS
void administrarCandidatos(){
    int op;
    do{
        cout << "ADMINISTRAR CANDIDATOS" << endl;
        cout << "1. Agregar candidato\n2. Eliminar candidato\n0. Volver\n" << endl;
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                //agregarCandidato();
                system("cls");
                cout << "Candidato agregado exitosamente" << endl;
                break;
            case 2:
                
                break;
            case 0:
                system("cls");
                cout << "Regresando..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida" << endl;
        }
    }while(op!=0);
}
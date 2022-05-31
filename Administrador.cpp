#include <iostream>
#include <windows.h>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/Gotoxy.h"
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
            Box(80,9);
            gotoxy(3,1);
            cout << i+1 << "." << endl;
            gotoxy(4,3);
            cout << "Nombre: " << listaAdministradores.administradores[i].nombre << endl;
            gotoxy(4,4);
            cout << "Cedula: " << listaAdministradores.administradores[i].cedula << endl;
            gotoxy(4,5);
            cout << "Edad: " << listaAdministradores.administradores[i].edad << endl;
            gotoxy(4,6);
            cout << "Region: " << listaAdministradores.administradores[i].region << endl;
            gotoxy(4,7);
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
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Box(15,10);
        SetConsoleTextAttribute(hConsole,3);
        gotoxy(6,1);
        cout << "MODO ADMINISTRADOR" << endl;
       gotoxy(4,3);
        cout << "No. " << listaAdministradores.administradores[numeroUsuario].cedula << "\t" << listaAdministradores.administradores[numeroUsuario].nombre <<"|" <<endl;
        
        SetConsoleTextAttribute(hConsole,12);
        gotoxy(4,4);
        cout << "1. Administrar Usuarios" << endl;
        gotoxy(4,5);
        cout << "2. Administrar Candidatos" << endl;
        gotoxy(4,6);
        cout << "3. Ver estadisticas" << endl;
        gotoxy(4,7);
        cout << "4. Finalizar votaciones" << endl;
        gotoxy(4,8);
        cout << "0. Salir" << endl;
        
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
                Box(20,5);
                SetConsoleTextAttribute(hConsole,4);
                gotoxy(4,3);
                cout << "Saliendo del modo adminstrador..." << endl;
                
                break;
            default:
                Box(20,5);
                SetConsoleTextAttribute(hConsole,2);
                gotoxy(4,3);
                cout << "Ingrese una funcion válida" << endl;
                
        }
    }while (op!=0);
}

//MENU DE ADMINISTRAR USUARIOS
void administrarUsuarios(){
    int op;
    do{
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
       Box(20,8);
         SetConsoleTextAttribute(hConsole,14);
         gotoxy(6,1);
        cout << "ADMINISTRAR USUARIOS      " << endl;
        gotoxy(4,3);
        cout << "1. Agregar usuario        " << endl;
        gotoxy(4,4);
        cout << "|2. Eliminar usuario       |" << endl;
        gotoxy(4,5);
        cout << "|3.Cambiar clave de usuario|" << endl;
        gotoxy(4,6);
        cout << "0. Volver                 " << endl;
        
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                agregarUsuario();
                system("cls");
                 Box(20,5);
                 SetConsoleTextAttribute(hConsole,15);
                 gotoxy(4,3);
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
                Box(15,5);
                 SetConsoleTextAttribute(hConsole,14);
                 gotoxy(4,3);
                cout << "Regresando..." << endl;
                
                break;
            default:
                Box(20,5);
                 SetConsoleTextAttribute(hConsole,14);
                 gotoxy(4,3);
                cout << "Ingrese una opcion valida" << endl;
                 
        }
    }while(op!=0);
}

//MENU ADMINISTRAR CANDIDATOS
void administrarCandidatos(){
    int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Box(20,8);
         SetConsoleTextAttribute(hConsole,14); 
         gotoxy(5,1);
        cout << "ADMINISTRAR CANDIDATOS " << endl;
        gotoxy(4,3);
        cout << "1. Agregar candidato" << endl;
        gotoxy(4,4);
        cout << "2. Eliminar candidato " << endl;
        gotoxy(4,5);
        cout << " 0. Volver              " << endl;
         
        
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                //agregarCandidato();
                system("cls");
                 Box(25,5);
                 SetConsoleTextAttribute(hConsole,14);
                 gotoxy(4,3);
                cout << "Candidato agregado exitosamente" << endl;
               
                break;
            case 2:
                
                break;
            case 0:
                system("cls");
                Box(15,5);
                 SetConsoleTextAttribute(hConsole,14);
                 gotoxy(4,3);
                cout << "Regresando..." << endl;
                 
                break;
            default:
                 Box(20,5);
                 SetConsoleTextAttribute(hConsole,14);
                 gotoxy(4,3),
                cout << "Ingrese una opcion valida " << endl;
               
        }
    }while(op!=0);
}
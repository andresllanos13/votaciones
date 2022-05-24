#include <iostream>
#include <windows.h>
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
<<<<<<< HEAD
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout<<"________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "| MODO ADMINISTRADOR         |" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,4);
        cout << " | No. " << listaAdministradores.administradores[numeroUsuario].cedula << "\t" << listaAdministradores.administradores[numeroUsuario].nombre <<"|" <<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,5);
        cout << "| 1. Administrar Usuarios |"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"_________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout<<"| 2. Administrar Candidatos |"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"__________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,1);
        cout<<"| 3. Ver estadisticas   |"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"__________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,2);
        cout<<"| 4. Finalizar votaciones  | "<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"___________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,5);
        cout<<"|  5. Salir    |"<<endl;
        SetConsoleTextAttribute(hConsole,7);

=======
        cout << "MODO ADMINISTRADOR" << endl;
        cout << "No. " << listaAdministradores.administradores[numeroUsuario].cedula << "\t" << listaAdministradores.administradores[numeroUsuario].nombre << endl;
        cout << "1. Administrar Usuarios\n2. Administrar Candidatos\n3. Ver estadisticas\n4. Finalizar votaciones\n0. Salir\n";
>>>>>>> 0574ce27038671f049744c535fecb807fd21afff
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
                cout<<"________________________________________"<<endl;
                SetConsoleTextAttribute(hConsole,4);
                cout << "| Saliendo del modo adminstrador...  |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"________________________________________"<<endl;
                break;
            default:
                cout<<"__________________________________"<<endl;
                SetConsoleTextAttribute(hConsole,2);
                cout << "|  Ingrese una funcion válida  |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"__________________________________"<<endl;

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
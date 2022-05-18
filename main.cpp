#include <iostream>
#include <windows.h>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

//VALIDAR QUE SOLO SE INGRESEN ENTEROS
int get_int(void)
{
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    char str[5];
    char* end;
    int num;
    do{
        GetConsoleMode(hStdInput, &mode);
        SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

        fgets(str,5,stdin);
        fflush(stdin);
        num=strtol(str,&end,10);
        if(!(*end))
            return num;
        else
        {
            cout << endl;
            system("cls");
            puts("Ingrese una clave numerica de 4 digitos");
            cout << endl;
            num=0;
        }
    }while(num==0);
}

//FUNCION PARA OBTENER LA CONTRASEÑA
int capturarClave(){
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(hStdInput, &mode);
    SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

    int clave = get_int();

    cout << endl;
    SetConsoleMode(hStdInput, mode);

    return clave;
}


//INICIAR SESION Y VALIDAR TIPO DE USUARIO
void inicSesion(){
    int cedula, clave, claveIngresada, op;
    int numeroUsuario;
    bool sesionIniciada = false;
    do {
        op = 0;
        cout << "Ingrese su cedula: " << endl;

        fflush(stdin);
        cin >> cedula;
        fflush(stdin);

        clave = buscarAdmin(cedula); //Revisar si la cedula corresponde a un admin
        numeroUsuario = buscarNumeroAdmin(cedula);
        if (clave != -1){

            cout << "Ingrese su clave: ";
            claveIngresada = capturarClave();

            if (claveIngresada == clave){
                system("cls");
                menuAdmin(numeroUsuario);
                sesionIniciada = true;
            }else{
                system("cls");
                cout << "Clave incorrecta, intente de nuevo" << endl;
            }
        }else{

            cout << "Ingrese su clave: ";
            clave = buscarUsuario(cedula); //Revisar si la cedula corresponde a un usuario
            numeroUsuario = buscarNumeroUsuario(cedula);
            
            if (clave != -1){
                claveIngresada = capturarClave();
                if (claveIngresada == clave){
                    system("cls");
                    menuVotante(numeroUsuario);
                    sesionIniciada = true;
                }else{
                    system("cls");
                    cout << "Clave incorrecta, intente de nuevo" << endl;
                }
            }else{
                system("cls");
                cout << "No se encuentra la cedula, Desea ingresar como reportero? (0. No, 1. Si)" << endl;
                cin >> op;
                if (op==1){
                    system("cls");
                    menuReportero();
                }
                system("cls");
            }
        }
    }while(sesionIniciada == false);
}

//MENU PRINCIPAL
void menuPrincipal(){
    int op;
    do{
        cout << "PROTOTIPO VOTACIONES" << endl;
        cout << "1. Iniciar sesion\n2. Salir\n";
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                system("cls");
                inicSesion();
                break;
            case 0: 
                cout << "Adios" << endl;
                break;
            default:
                cout << "Ingrese una opcion valida" << endl;
        }
    }while(op!=0);
    
}

//FUNCION PRINCIPAL
int main(){
    iniciarListaAdmin();
    inicListaUsuarios();
    iniciarListaCandidatos();
    
    menuPrincipal();

    //mostrarListaAdmin();
    //mostrarListaUsuario();

    system("pause");
    return 0;
}
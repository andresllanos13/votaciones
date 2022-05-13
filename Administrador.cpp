#include <iostream>
#include "Administrador.h"
using namespace std;

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

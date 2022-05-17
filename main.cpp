#include <iostream>
#include <windows.h>
#include "ListaUsuarios.h"
#include "ListaAdministradores.h"
#include "ListaCandidatos.h"
using namespace std;

ListaCandidatos listaCandidatos;

//MENU PARA EL USUARIO ADMINISTRADOR
void menuAdmin(){ 
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

//MENU PARA EL USUARIO VOTANTE
void menuVotante(){ 
	int op;
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

//MENU PARA EL USUARIO REPORTERO
void menuReportero(){
	int op;
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

//Validar que solo ingresen enteros
int get_int(void)
{
    char str[5];
    char* end;
    int num;
    do{
        fgets(str,5,stdin);
        num=strtol(str,&end,10);
        if(!(*end))
            return num;
        else
        {
            cout << endl;
            puts("Ingrese una clave numerica de 4 digitos");
            cout << endl;
            num=0;
        }
    }while(num==0);
}

//Funcion para obtener la contraseña
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
    int cedula, clave, claveIngresada;
    bool sesionIniciada = false;
    do {
        cout << "Ingrese su cedula: " << endl;
        fflush(stdin);
        cin >> cedula;
        fflush(stdin);
        clave = buscarAdmin(cedula);
        if (clave != -1){
            cout << "Ingrese su clave: ";
            claveIngresada = capturarClave();
            if (claveIngresada == clave){
                cout << "Funciona Admin" << endl;
                sesionIniciada = true;
            }else{
                system("cls");
                cout << "Clave incorrecta, intente de nuevo" << endl;
            }
        }else{
            cout << "Ingrese su clave: ";
            clave = buscarUsuario(cedula);
            if (clave != -1){
                claveIngresada = capturarClave();
                if (claveIngresada == clave){
                    cout << "Funciona usuario" << endl;
                    sesionIniciada = true;
                }else{
                    system("cls");
                    cout << "Clave incorrecta, intente de nuevo" << endl;
                }
            }else{
                system("cls");
                cout << "No se encuentra la cedula" << endl;
            }
        }
    }while(sesionIniciada == false);
}

//FUNCION PRINCIPAL
int main(){
    iniciarListaAdmin();
    inicListaUsuarios();

    inicSesion();

    //mostrarListaAdmin();
    //mostrarListaUsuario();

    system("pause");
    return 0;
}
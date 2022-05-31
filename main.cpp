#include <iostream>
#include <windows.h>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

 void gotoxy (int x,int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void Box (int w,int h){
	int i,j;
	putchar(218);
	for(i=0;i<w-2;i++){
		putchar(196);
	}
	putchar(191);
	cout<<endl;
	for(i=0;i<h-2;i++){
		putchar(179);
		for(j=0;j<w-2;j++){
			cout<<" ";
		}
		putchar(179);
		cout<<endl;
	}
	putchar(192);
	for(i=0;i<w-2;i++){
		putchar(196);
	}
	putchar(217);
}   

//VALIDAR QUE SOLO SE INGRESEN ENTEROS
int get_int(void)
{    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
            Box(30,5);
             SetConsoleTextAttribute(hConsole,2);
             gotoxy(4,3);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula, clave, claveIngresada, op;
    int numeroUsuario;
    bool sesionIniciada = false;
    do {
        op = 0;
        Box(20,5);
        
         SetConsoleTextAttribute(hConsole,3);
         gotoxy(4,3);
        cout << "Ingrese su cedula:" << endl;
        

        fflush(stdin);
        cin >> cedula;
        fflush(stdin);

        clave = buscarAdmin(cedula); //Revisar si la cedula corresponde a un admin
        numeroUsuario = buscarNumeroAdmin(cedula);
        if (clave != -1){
            Box(20,5);
             SetConsoleTextAttribute(hConsole,3);
             gotoxy(4,3);
            cout << "Ingrese su clave:"<<endl;
            claveIngresada = capturarClave();

            if (claveIngresada == clave){
                system("cls");
                menuAdmin(numeroUsuario);
                sesionIniciada = true;
            }else{
                system("cls");
               Box(25,5);
                SetConsoleTextAttribute(hConsole,12);
                gotoxy(4,3);
                cout << "Clave incorrecta, intente de nuevo" << endl;
               
            }
        }else{
            Box(20,5);
            SetConsoleTextAttribute(hConsole,3);
            gotoxy(4,3);
            cout << "Ingrese su clave:"<<endl;
            
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
                   Box(35,5);
                    SetConsoleTextAttribute(hConsole,3);
                    gotoxy(4,3);
                    cout << "Clave incorrecta, intente de nuevo" << endl;
                   
                }
            }else{
                system("cls");
                Box(40,5);
                SetConsoleTextAttribute(hConsole,3);
                gotoxy(4,3);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int op;
    do{
       Box(20,5);
        Box(30,6);
        SetConsoleTextAttribute(hConsole,7);
        gotoxy(4,2);
        cout << "PROTOTIPO VOTACIONES" << endl;
        gotoxy(4,3);
        cout << "1. Iniciar sesion"<<endl;
        gotoxy(4,4);
        cout << "|0. Salir            |"<<endl;
        
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                system("cls");
                inicSesion();
                break;
            case 0:
                Box(15,5);
                SetConsoleTextAttribute(hConsole,4);
                cout << "  Adios          " << endl;
                
                break;
            default:
                Box(15,5);
                SetConsoleTextAttribute(hConsole,5);
                cout << "Ingrese una opcion valida " << endl;
                
        }
    }while(op!=0);
    
}

//FUNCION PRINCIPAL
int main(){
    
    iniciarListaAdmin();
    inicListaUsuarios();
    iniciarListaCandidatos();
    inicListaVotos();
    
    menuPrincipal();

    //mostrarListaAdmin();
    //mostrarListaUsuario();
    //mostrarListaCandidatos();

    system("pause");
    return 0;
}
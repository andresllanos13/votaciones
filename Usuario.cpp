#include <iostream>
#include <windows.h>
#include <string.h>
#include "HeaderFiles/ListaUsuarios.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaVotos.h"
using namespace std;

//FUNCIONES PARA IMPRIMIR
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

//Archivo y lista de usuarios
FILE *archivoUsuarios;
ListaUsuarios listaUsuarios;

//Archivo y lista de votos
FILE *archivoVotos;
ListaVotos listavotos;

//CADENAS DE FORMATO PARA LECTURA Y ESCRITURA DE ARCHIVOS
const char* FORMATO_USUARIO_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";
const char* FORMATO_USUARIO_IN = "{\n\t\"nombre\": \"%s\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%s\",\n\t\"clave\":%d\n}\n";
const char* FORMATO_VOTO_OUT = "{\n\t\"cedula\":%d,\n\t\"voto\":%d,\n}\n";
const char* FORMATO_VOTO_IN = "{\n\t\"cedula\":%d,\n\t\"voto\":%d,\n}\n";

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

//Iniciar la estructura que guarda los votos de los usuarios
void inicListaVotos(){
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        listavotos.candidato[i].central = 0;
        listavotos.candidato[i].norte = 0;
        listavotos.candidato[i].sur = 0;
        listavotos.candidato[i].joven = 0;
        listavotos.candidato[i].adulto = 0;
        listavotos.candidato[i].mayor = 0;
    }
}

//Imprimir la estructura de usuarios (No necesario)
void mostrarListaUsuario(){
     
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (listaUsuarios.usuario[i].nombre[0] != '\0'){
            Box(35,15);
            SetConsoleTextAttribute(hConsole,2);
            gotoxy(3,1);
            cout << i+1 << endl;
            gotoxy(4,3);
            cout << "Nombre: " << listaUsuarios.usuario[i].nombre << endl;
            gotoxy(4,4);
            cout << "Cedula: " << listaUsuarios.usuario[i].cedula <<endl;
            gotoxy(4,5);
            cout << "Edad: " << listaUsuarios.usuario[i].edad <<endl;
            gotoxy(4,6);
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
	int op, voto=-1;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Box(30,15);
        SetConsoleTextAttribute(hConsole,3);
        gotoxy(6,1);
        cout << "SISTEMA DE VOTACION" << endl;
        gotoxy(4,3);
        cout << "USUARIO:" << listaUsuarios.usuario[numeroUsuario].cedula << "\n" << listaUsuarios.usuario[numeroUsuario].nombre <<endl;
       gotoxy(4,4);
        cout << "Ingrese la opcion que desea"<<endl;
        gotoxy(4,5);
        cout << "Recuerde guardar su voto"<<endl;
        gotoxy(4,6);
        cout << "1. Ver candidatos" << endl;
        gotoxy(4,7);
        cout << "2. Votar" << endl;
        gotoxy(4,8);
        cout << "3. Cambiar Voto" << endl;
        gotoxy(4,9);
        cout << "4. Guardar voto" << endl;
        gotoxy(4,10);
        cout << "0. Salir (Cerrar sesion)" << endl;
       
        cin>>op;
        system("cls");
        switch (op){
            case 1:
                //funcion que muestra los candidatos
                mostrarListaCandidatos();
                break;
            case 2:
                //funcion que retorna el valor de el voto
                voto = votar();
                break;
            case 3:
                voto = votar();
                break;
            case 4:
                //esta funcion guarda el voto definitivo y solo se podra usar una vez
                if (voto != -1){
                    if (registrarVoto(listaUsuarios.usuario[numeroUsuario].cedula, voto) == 0){
                        op = 0;
                    }
                }else{
                    Box(40,5);
                    SetConsoleTextAttribute(hConsole,13);
                    gotoxy(4,3);
                    cout << "El usuario aun no ha seleccionado un candidato. " << endl;
                    
                }
                break;
            case 0:
                //REGRESAR O SALIR
                Box(30,5);
                SetConsoleTextAttribute(hConsole,1);
                gotoxy(4,3);
                cout << "Cerrando sesion...   " << endl;
                
                break;
            default:
               Box(30,5);
                SetConsoleTextAttribute(hConsole,5);
                gotoxy(4,3);
                cout << "Ingrese una funcion valida  " << endl;  
        }                         
    }while(op!=0);
}

//MENU PARA EL USUARIO REPORTERO
void menuReportero(){
	int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Box(30,13);
        SetConsoleTextAttribute(hConsole,3);
        gotoxy(6,1);
        cout<<"MODO REPORTERO"<<endl;
        gotoxy(4,3);
        cout<<"Ingrese la opcion que desea:"<<endl;
        gotoxy(4,4);
        cout<<"1. Candidato con mayoria de votos"<<endl;
        gotoxy(4,5);
        cout<<"2. Ver tabla de votos actual"<<endl;
        gotoxy(4,6);
        cout<<"3. Ganador por regiones"<<endl;
        gotoxy(4,7);
        cout<<"4. Dos candidatos mejor posicionados"<<endl;
        gotoxy(4,8);
        cout<<"5. Saber si hay segunda vuelta"<<endl;
        gotoxy(4,9);
        cout<<"0. Salir"<<endl;
        
        cin>>op;
        system("cls");
        switch (op){
            case 1:
                //Funcion que muestra quien va ganando 
                ganador();
                break;
            case 2:
                //Funcion muestra el total de votos para cada candidato
                totalVotos(4);
                break;
            case 3:
                //Esta funcion muestra quien gana en cada region 
                gpr();
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
                Box(20,5);
                 SetConsoleTextAttribute(hConsole,1);
                 gotoxy(4,3);
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
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Box(25,20);
     SetConsoleTextAttribute(hConsole,12);
     gotoxy(4,3);
    cout << "Ingrese el nombre del nuevo usuario:";
     
    fflush(stdin);
    gotoxy(4,4);
    gets(nombre);
    gotoxy(4,5);
    cout << "Ingrese la cedula: "<<endl;
     
    fflush(stdin);
    gotoxy(4,6);
    cin >> cedula;
    gotoxy(4,7);
    cout << "Ingrese la edad: "<<endl;
    
    fflush(stdin);
    gotoxy(4,8);
    cin >> edad;
    gotoxy(4,9);
    cout << "Ingrese la region del nuevo usuario:"<<endl;
    
    fflush(stdin);
    gotoxy(4,10);
    gets(region);
    gotoxy(4,11);
    cout << "Ingrese la clave:"<<endl;
   
    fflush(stdin);
    gotoxy(4,12);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula;
    Box(25,5);
    gotoxy(4,2);
    cout << "Ingrese la cedula a eliminar: "<<endl;
    gotoxy(4,3);
    cin >> cedula;
    
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            gotoxy(4,4);
            Box(18,4);
            SetConsoleTextAttribute(hConsole,13);
            gotoxy(6,5);
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre  <<endl;
            gotoxy(6,6);
            cout << "Desea eliminarlo? (1. Si, 2. No) " << endl; 
            gotoxy(6,7);

            cin >> cedula;
            if (cedula == 1){
                listaUsuarios.usuario[i].nombre[0] = '\0';
                listaUsuarios.usuario[i].region[0] = '\0';
                listaUsuarios.usuario[i].cedula = 0;
                listaUsuarios.usuario[i].edad = 0;
                system("cls");
                gotoxy(4,9);
                Box(17,3);
                SetConsoleTextAttribute(hConsole,13);
                gotoxy(6,11);
                cout << "Eliminado exitosamente " << endl;
                break; 
            }
            else{
                system("cls");
                gotoxy(4,9);
                Box(16,3);
                gotoxy(6,11);
                cout << "No se elimino el usuario " << endl;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            gotoxy(4,9);
            Box(18,5);
            SetConsoleTextAttribute(hConsole,13);
            cout << "No se encontro la cedula " << endl; 
        }
    }
    actualizarArchivo();
}

//CAMBIAR LA CLAVE DE UN USUARIO
void cambiarClave(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula, clave;

    Box(35,25);
    SetConsoleTextAttribute(hConsole,13);
    gotoxy(4,2);
    cout << "Ingrese la cedula: "<<endl;
    gotoxy(4,3);
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){     
            SetConsoleTextAttribute(hConsole,13);
            gotoxy(4,4);
            Box(15,5);
            gotoxy(6,6);
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre << endl;
            gotoxy(6,7);
            cout << "Desea cambiar su clave? (1. Si, 2. No) " << endl;
            gotoxy(6,8);
            cin >> cedula;
            if (cedula == 1){

                gotoxy(4,8),
                Box(15,4);
                SetConsoleTextAttribute(hConsole,11);
                gotoxy(6,10);
                cout << "Ingrese su nueva clave: "<<endl;
                gotoxy(6,11);
                cin >> clave;
                listaUsuarios.usuario[i].clave = clave;
                system("cls");
                gotoxy(6,12);
                cout << "Clave cambiada exitosamente " << endl;
                break;
            }
            else{
                system("cls");
                gotoxy(4,8),
                Box(16,3);
                SetConsoleTextAttribute(hConsole,13);
                gotoxy(6,10);
                cout << "No se elimino el usuario " << endl;
                break;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            gotoxy(4,19);
            SetConsoleTextAttribute(hConsole,13);
            cout << "No se encontro la cedula " << endl;
            SetConsoleTextAttribute(hConsole,7);
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

//PREGUNTAR POR QUE CANDIDATO VA A VOTAR Y VALIDAR
int votar(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int voto;
    mostrarListaCandidatos();
    Box(35,20);
    gotoxy(5,1);
    SetConsoleTextAttribute(hConsole,13);
    cout << "Seleccione su candidato: "<<endl;
    gotoxy(4,3);
    cin >> voto;
    system("cls");
    if (voto >= 1 && voto <= 5){
        gotoxy(4,4);
        Box(15,3);
        SetConsoleTextAttribute(hConsole,13);
        gotoxy(6,6);
        cout << "Usted esta votando por: " << voto << endl;
        return voto;
    }else{
        gotoxy(4,4);
        Box(16,3);
        SetConsoleTextAttribute(hConsole,13);
        gotoxy(6,6);
        cout << "Ingrese un voto valido " << endl;
        SetConsoleTextAttribute(hConsole,7);
        return -1;
    }
}

int registrarVoto(int cedula, int voto){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedulaYaUsada, votoUsado, i=0;
    fopen_s(&archivoVotos, "Datos/votos.txt", "r+");
    fseek(archivoVotos, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoVotos, FORMATO_VOTO_OUT, &cedulaYaUsada, &votoUsado);
        i++;
        if (cedulaYaUsada == cedula){
            Box(35,5);
            SetConsoleTextAttribute(hConsole,13);
            gotoxy(4,3);
            cout << "Este usuario ya ha votado, su voto fue por el candidato: " << votoUsado  <<endl;
            SetConsoleTextAttribute(hConsole,7);
            
            fclose(archivoVotos);
            return -1;
        }
    }
    fclose(archivoUsuarios);
    listavotos.candidato[voto].votos++;
    //FALTA VERIFICAR SU EDAD Y REGION
    fopen_s(&archivoVotos, "Datos/votos.txt", "at+");
    fseek(archivoVotos, 0, SEEK_END);
    fprintf_s(archivoVotos, FORMATO_VOTO_IN, cedula, voto);
    fclose(archivoVotos);
    Box(30,5);
    SetConsoleTextAttribute(hConsole,13);
    gotoxy(4,3);
    cout << "Voto registrado exitosamente, cerrando sesion..." << endl;
   
    return 0;
}

/*
void masVotos(){ //TENGO QUE TERMINAR ESTO
    int arregloVotos[CANTIDAD_CANDIDATOS];
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        //COSAS PARA MIRAR QUIEN TIENE MAS VOTOS
    }
}*/

void mostrarVotos(){
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        cout << i+1 << ". ";
        getNombre(i);
        cout << "Numero de votos: " << listavotos.candidato[i].votos << endl;
        cout << "Numero de votos por region: " << endl;
        cout << "Central: " << listavotos.candidato[i].central << endl;
        cout << "Norte: " << listavotos.candidato[i].norte << endl;
        cout << "Sur: " << listavotos.candidato[i].sur << endl;
        cout << "Numero de votos por edad: " << endl;
        cout << "Joven: " << listavotos.candidato[i].joven << endl;
        cout << "Adulto: " << listavotos.candidato[i].adulto << endl;
        cout << "Mayor: " << listavotos.candidato[i].mayor << endl;
    }
}

void dosMas(){
    if((listavotos.candidato[0].votos>listavotos.candidato[1].votos) && (listavotos.candidato[0].votos>listavotos.candidato[3].votos) && (listavotos.candidato[0].votos>listavotos.candidato[2].votos)){
        totalVotos(0);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<listavotos.candidato[0].votos;
    }
}

void gpr(){
    ganaRegionC();
    ganaRegionN();
    ganaRegionS();
}

void ganaRegionN(){
    if(listavotos.candidato[0].norte>listavotos.candidato[1].norte&&listavotos.candidato[0].norte>listavotos.candidato[2].norte&&listavotos.candidato[0].norte>listavotos.candidato[3].norte){
        totalVotos(0);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region norte";
        gotoxy(6,6);
        cout<<listavotos.candidato[0].norte;
    }
    if(listavotos.candidato[1].norte>listavotos.candidato[0].norte&&listavotos.candidato[1].norte>listavotos.candidato[2].norte&&listavotos.candidato[1].norte>listavotos.candidato[3].norte){
        totalVotos(1);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region norte";
        gotoxy(6,6);
        cout<<listavotos.candidato[1].norte;
    }
    if(listavotos.candidato[2].norte>listavotos.candidato[0].norte&&listavotos.candidato[2].norte>listavotos.candidato[1].norte&&listavotos.candidato[2].norte>listavotos.candidato[3].norte){
        totalVotos(2);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region norte";
        gotoxy(6,6);
        cout<<listavotos.candidato[2].norte;
    }
    if(listavotos.candidato[3].norte>listavotos.candidato[0].norte&&listavotos.candidato[3].norte>listavotos.candidato[1].norte&&listavotos.candidato[3].norte>listavotos.candidato[2].norte){
        totalVotos(3);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region norte";
        gotoxy(6,6);
        cout<<listavotos.candidato[3].norte;
    }
}

void ganaRegionS(){
    if(listavotos.candidato[0].sur>listavotos.candidato[1].sur&&listavotos.candidato[0].sur>listavotos.candidato[2].sur&&listavotos.candidato[0].sur>listavotos.candidato[3].sur){
        totalVotos(0);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region sur";
        gotoxy(6,6);
        cout<<listavotos.candidato[0].sur;
    }
    if(listavotos.candidato[1].sur>listavotos.candidato[0].sur&&listavotos.candidato[1].sur>listavotos.candidato[2].sur&&listavotos.candidato[1].sur>listavotos.candidato[3].sur){
        totalVotos(1);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region sur";
        gotoxy(6,6);
        cout<<listavotos.candidato[1].sur;
    }
    if(listavotos.candidato[2].sur>listavotos.candidato[0].sur&&listavotos.candidato[2].sur>listavotos.candidato[1].sur&&listavotos.candidato[2].sur>listavotos.candidato[3].sur){
        totalVotos(2);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region sur";
        gotoxy(6,6);
        cout<<listavotos.candidato[2].sur;
    }
    if(listavotos.candidato[3].sur>listavotos.candidato[0].sur&&listavotos.candidato[3].sur>listavotos.candidato[1].sur&&listavotos.candidato[3].sur>listavotos.candidato[2].sur){
        totalVotos(3);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region sur";
        gotoxy(6,6);
        cout<<listavotos.candidato[3].sur;
    }
}

void ganaRegionC(){
    if(listavotos.candidato[0].central>listavotos.candidato[1].central&&listavotos.candidato[0].central>listavotos.candidato[2].central&&listavotos.candidato[0].central>listavotos.candidato[3].central){
        totalVotos(0);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region central";
        gotoxy(6,6);
        cout<<listavotos.candidato[0].central;
    }
    if(listavotos.candidato[1].central>listavotos.candidato[0].central&&listavotos.candidato[1].central>listavotos.candidato[2].central&&listavotos.candidato[1].central>listavotos.candidato[3].central){
        totalVotos(1);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region central";
        gotoxy(6,6);
        cout<<listavotos.candidato[1].central;
    }
    if(listavotos.candidato[2].central>listavotos.candidato[0].central&&listavotos.candidato[2].central>listavotos.candidato[1].central&&listavotos.candidato[2].central>listavotos.candidato[3].central){
        totalVotos(2);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region central";
        gotoxy(6,6);
        cout<<listavotos.candidato[2].central;
    }
    if(listavotos.candidato[3].central>listavotos.candidato[0].central&&listavotos.candidato[3].central>listavotos.candidato[1].central&&listavotos.candidato[3].central>listavotos.candidato[2].central){
        totalVotos(3);
        gotoxy(4,3);
        Box(25,6);
        gotoxy(6,5);
        cout<<"region central";
        gotoxy(6,6);
        cout<<listavotos.candidato[3].central;
    }
}

void totalVotos1(){
    for(int j=0;j<CANTIDAD_CANDIDATOS;j++){
    totalVotos(j);
    gotoxy(4,3);
    Box(25,7);
    gotoxy(6,5);
    cout<<listavotos.candidato[j].votos;
    cout<<endl;
    }
    
}

void ganador(){
    if(listavotos.candidato[0].votos>listavotos.candidato[1].votos&&listavotos.candidato[0].votos>listavotos.candidato[2].votos&&listavotos.candidato[0].votos>listavotos.candidato[3].votos){
        Box(30,25);
        gotoxy(5,1);
        cout<<"El ganador es: "<< endl;
        gotoxy(4,3);
        cout <<listavotos.candidato[0].votos;

    }else if(listavotos.candidato[1].votos>listavotos.candidato[0].votos&&listavotos.candidato[1].votos>listavotos.candidato[2].votos&&listavotos.candidato[1].votos>listavotos.candidato[3].votos){
        Box(30,15);
        gotoxy(5,1);
        cout<<"El ganador es: "<< endl;
        gotoxy(4,3);
        cout <<listavotos.candidato[1].votos;

    }else if(listavotos.candidato[2].votos>listavotos.candidato[0].votos&&listavotos.candidato[2].votos>listavotos.candidato[1].votos&&listavotos.candidato[2].votos>listavotos.candidato[3].votos){
        Box(30,15);
        gotoxy(5,1);
        cout<<"El ganador es: "<< endl;
        gotoxy(4,3);
        cout <<listavotos.candidato[2].votos;

    }else if(listavotos.candidato[3].votos>listavotos.candidato[0].votos&&listavotos.candidato[3].votos>listavotos.candidato[1].votos&&listavotos.candidato[3].votos>listavotos.candidato[2].votos){
        Box(30,15);
        gotoxy(5,1);
        cout<<"El ganador es: "<< endl;
        gotoxy(4,3);
        cout <<listavotos.candidato[3].votos;
    }
}
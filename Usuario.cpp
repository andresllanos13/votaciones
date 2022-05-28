#include <iostream>
#include <windows.h>
#include <string.h>
#include "HeaderFiles/ListaUsuarios.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaVotos.h"
using namespace std;

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
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,2);
            cout <<"|    "<< i+1 <<"                 |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,1);
            cout << "| Nombre: " << listaUsuarios.usuario[i].nombre <<" |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,3);
            cout << "|  Cedula: " << listaUsuarios.usuario[i].cedula <<" |" <<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,4);
            cout << "|  Edad: " << listaUsuarios.usuario[i].edad <<"    |" <<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,5);
            cout << "|  Region: " << listaUsuarios.usuario[i].region <<"  |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,6);
            cout << "| Clave: " << listaUsuarios.usuario[i].clave <<"  |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
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
        cout << "_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "|SISTEMA DE VOTACION\t\t|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout <<"_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "USUARIO:" << listaUsuarios.usuario[numeroUsuario].cedula << "\n" << listaUsuarios.usuario[numeroUsuario].nombre <<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<< "_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,5);
        cout << "|Ingrese la opcion que desea\t|"<<endl;
        cout << "|Recuerde guardar su voto\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,12);
        cout << "|1. Ver candidatos\t\t|" << endl;
        cout << "|2. Votar\t\t\t|" << endl;
        cout << "|3. Cambiar Voto\t\t|" << endl;
        cout << "|4. Guardar voto\t\t|" << endl;
        cout << "|0. Salir (Cerrar sesion)\t|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"_______________________________"<<endl;
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
                    if (registrarVoto(listaUsuarios.usuario[numeroUsuario].cedula, voto, numeroUsuario) == 0){
                        op = 0;
                    }
                }else{
                    cout << "___________________________________________________" << endl;
                      SetConsoleTextAttribute(hConsole,13);
                    cout << "| El usuario aun no ha seleccionado un candidato. |" << endl;
                      SetConsoleTextAttribute(hConsole,7);
                    cout << "___________________________________________________" << endl;
                }
                break;
            case 0:
                //REGRESAR O SALIR
                cout<<"__________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,1);
                cout << "|   Cerrando sesion...   |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                 cout<<"___________________________"<<endl;
                break;
            default:
                cout<<"________________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,5);
                cout << "| Ingrese una funcion valida  |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout<<"________________________________" <<endl;
        }                         
    }while(op!=0);
}

//MENU PARA EL USUARIO REPORTERO
void menuReportero(){
	int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout<<"|MODO REPORTERO\t\t\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout<<"|Ingrese la opcion que desea:\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"|1. Candidato con mayoria de votos\t|"<<endl;
        cout<<"|2. Ver tabla de votos actual\t\t|"<<endl;
        cout<<"|3. Ganador por regiones\t\t|"<<endl;
        cout<<"|4. Dos candidatos mejor posicionados\t|"<<endl;
        cout<<"|5. Saber si hay segunda vuelta\t\t|"<<endl;
        cout<<"|0. Salir\t\t\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
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
                cout << "_____________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,1);
                cout << "| Ingrese una funcion valida |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                 cout<<"______________________________"<<endl;
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
    cout << "_______________________________________"<<endl;
     SetConsoleTextAttribute(hConsole,12);
    cout << "| Ingrese el nombre del nuevo usuario: |";
     SetConsoleTextAttribute(hConsole,7);
    cout << "_______________________________________"<<endl;
    fflush(stdin); 
    gets(nombre);
    cout << "______________________"<<endl;
     SetConsoleTextAttribute(hConsole,12);
    cout << "| Ingrese la cedula: |"<<endl;
     SetConsoleTextAttribute(hConsole,7);
    cout << "______________________"<<endl;
    fflush(stdin);
    cin >> cedula;
    cout << "____________________"<<endl;
     SetConsoleTextAttribute(hConsole,12);
    cout << "| Ingrese la edad: |"<<endl;
     SetConsoleTextAttribute(hConsole,7);
    cout << "____________________"<<endl;
    fflush(stdin);
    cin >> edad;
    cout << "________________________________________"<<endl;
     SetConsoleTextAttribute(hConsole,12);
    cout << "| Ingrese la region del nuevo usuario: |"<<endl;
     SetConsoleTextAttribute(hConsole,7);
    cout << "________________________________________"<<endl;
    fflush(stdin);
    gets(region);
    cout << "_____________________"<<endl;
    cout << "| Ingrese la clave: |"<<endl;
    cout << "_____________________"<<endl;
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
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula;
    cout << "_________________________________"<<endl;
     SetConsoleTextAttribute(hConsole,13);
    cout << "| Ingrese la cedula a eliminar: |"<<endl;
     SetConsoleTextAttribute(hConsole,7);
    cout << "_________________________________"<<endl;
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "________________________________________"<<endl;
             SetConsoleTextAttribute(hConsole,13);
            cout << "|Corresponde a: " << listaUsuarios.usuario[i].nombre <<"|" <<endl;
            cout << "|Desea eliminarlo? (1. Si, 2. No)      |" << endl;
             SetConsoleTextAttribute(hConsole,7);
            cout << "________________________________________" << endl;

            cin >> cedula;
            if (cedula == 1){
                listaUsuarios.usuario[i].nombre[0] = '\0';
                listaUsuarios.usuario[i].region[0] = '\0';
                listaUsuarios.usuario[i].cedula = 0;
                listaUsuarios.usuario[i].edad = 0;
                system("cls");
                cout << "__________________________"<<endl; 
                 SetConsoleTextAttribute(hConsole,13);
                cout << "| Eliminado exitosamente |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "__________________________"<<endl;
                break; 
            }
            else{
                system("cls");
                cout << "____________________________" << endl;
                cout << "| No se elimino el usuario |" << endl;
                cout << "____________________________" << endl;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "____________________________" << endl;
             SetConsoleTextAttribute(hConsole,13);
            cout << "| No se encontro la cedula |" << endl;
             SetConsoleTextAttribute(hConsole,7);
            cout << "____________________________" << endl;
        }
    }
    actualizarArchivo();
}

//CAMBIAR LA CLAVE DE UN USUARIO
void cambiarClave(){
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula, clave;

    cout << "______________________"<<endl;
    SetConsoleTextAttribute(hConsole,13);
    cout << "| Ingrese la cedula: |"<<endl;
    SetConsoleTextAttribute(hConsole,7);
    cout << "______________________"<<endl;
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "__________________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,13);
            cout << "|Corresponde a: " << listaUsuarios.usuario[i].nombre <<"|"<< endl;
            cout << "|Desea cambiar su clave? (1. Si, 2. No)  |" << endl;
            SetConsoleTextAttribute(hConsole,7);
            cout << "__________________________________________" << endl;
            cin >> cedula;
            if (cedula == 1){
                cout << "___________________________"<<endl;
                SetConsoleTextAttribute(hConsole,11);
                cout << "| Ingrese su nueva clave: |"<<endl;
                SetConsoleTextAttribute(hConsole,7);
                cout << "___________________________"<<endl;
                cin >> clave;
                listaUsuarios.usuario[i].clave = clave;
                system("cls");
                cout << "_______________________________" << endl;
                cout << "| Clave cambiada exitosamente |" << endl;
                cout << "_______________________________" << endl;
                break;
            }
            else{
                system("cls");
                cout << "____________________________" << endl;
                SetConsoleTextAttribute(hConsole,13);
                cout << "| No se elimino el usuario |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout << "____________________________" << endl;
                break;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "____________________________" << endl;
            SetConsoleTextAttribute(hConsole,13);
            cout << "| No se encontro la cedula |" << endl;
            SetConsoleTextAttribute(hConsole,7);
            cout << "____________________________" << endl;
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
    
    cout << endl;
    cout << "____________________________"<<endl;
    SetConsoleTextAttribute(hConsole,13);
    cout << "| Seleccione su candidato: |"<<endl;
    SetConsoleTextAttribute(hConsole,7);
    cout << "____________________________"<<endl;
    cin >> voto;
    system("cls");
    if (voto >= 1 && voto <= 5){
        cout << "_________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,13);
        cout << "| Usted esta votando por: " << voto <<"|"<< endl;
        SetConsoleTextAttribute(hConsole,7);
        cout << "_________________________________"<<endl;
        return voto;
    }else{
        cout << "__________________________" << endl;
        SetConsoleTextAttribute(hConsole,13);
        cout << "| Ingrese un voto valido |" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout << "__________________________" << endl;
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
            cout << "__________________________________________________________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,13);
            cout << "Este usuario ya ha votado, su voto fue por el candidato: " << votoUsado <<"|" <<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout << "__________________________________________________________________________________"<<endl;
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
    cout << "_____________________________________________________" << endl;
    SetConsoleTextAttribute(hConsole,13);
    cout << "|Voto registrado exitosamente, cerrando sesion...   |" << endl;
    SetConsoleTextAttribute(hConsole,7);
    cout << "_____________________________________________________" << endl;
    return 0;
}

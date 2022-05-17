#include <iostream>
#include "ListaUsuarios.h"
using namespace std;

FILE *archivoUsuarios;
ListaUsuarios listaUsuarios;

//CADENAS DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_USUARIO_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";

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
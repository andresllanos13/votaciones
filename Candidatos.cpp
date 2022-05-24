#include <iostream>
#include "HeaderFiles/ListaCandidatos.h"
using namespace std;

FILE *archivoCandidatos;
ListaCandidatos listaCandidatos;

//CADENA DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_CANDIDATO_OUT = "{\n\t\"presidente\":\"%[^\"]\",\n\t\"vicepresidente\":\"%[^\"]\",\n\t\"partido\":\"%[^\"]\",\n\t\"votos\":%d\n}\n";

//Leer los datos del archivo candidatos.txt y guardarlos en la estructura
void iniciarListaCandidatos(){
    int i=0; 
    fopen_s(&archivoCandidatos, "Datos/candidatos.txt", "r+");
    fseek(archivoCandidatos, 0, SEEK_SET);
    int ret=0;
    while (ret!=EOF){
        ret = fscanf(archivoCandidatos, FORMATO_CANDIDATO_OUT, listaCandidatos.candidatos[i].presidente, listaCandidatos.candidatos[i].vicepresidente, listaCandidatos.candidatos[i].partido, &listaCandidatos.candidatos[i].votos);
        i++;
    }
    fclose(archivoCandidatos);
}

//MOSTRAR LA ESTRUCTURA DE CANDIDATOS
void mostrarListaCandidatos(){
    for(int i=0; i<CANTIDAD_CANDIDATOS; i++){
        if (listaCandidatos.candidatos[i].presidente[0] != '\0'){
            cout << i+1 << endl;
            cout << "Presidente: " << listaCandidatos.candidatos[i].presidente << endl;
            cout << "Vicepresidente: " << listaCandidatos.candidatos[i].vicepresidente << endl;
            cout << "Partido: " << listaCandidatos.candidatos[i].partido << endl;
            cout << "Votos: " << listaCandidatos.candidatos[i].votos << endl;
        }
    }
}

//MODIFICAR CANDIDATOS (FALTA TERMINAR)
void agregarCandidato(){
    char presidente[50];
    char vicepresidente[50];
    char partido[50];
    int votos;
}
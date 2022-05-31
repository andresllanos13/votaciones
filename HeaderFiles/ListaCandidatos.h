#pragma once
#include "Candidatos.h"
#include "Gotoxy.h"
#define CANTIDAD_CANDIDATOS 4

//BASE DE DATOS DE CANDIDATOS
struct ListaCandidatos
{
    Candidatos candidatos[CANTIDAD_CANDIDATOS];
};

void iniciarListaCandidatos();
void mostrarListaCandidatos();
void getNombre(int pos);
void totalVotos(int n);
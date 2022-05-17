#pragma once
#define CANTIDAD_ADMINISTRADORES 10
#include "Administrador.h"

struct ListaAdministradores
{
    Administrador administradores[CANTIDAD_ADMINISTRADORES];
};



void iniciarListaAdmin();
void mostrarListaAdmin();
int buscarAdmin(int cedula);
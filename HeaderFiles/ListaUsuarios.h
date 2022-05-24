#pragma once
#include "Usuario.h"
#define CANTIDAD_USUARIOS 100

//BASE DE DATOS DE USUARIOS VOTANTES
struct ListaUsuarios
{
    Usuario usuario[CANTIDAD_USUARIOS];
};


void inicListaUsuarios();
void mostrarListaUsuario();
int buscarUsuario(int cedula);
int buscarNumeroUsuario(int cedula);
void menuVotante(int numeroUsuario);
void menuReportero();
void agregarUsuario();
void eliminarUsuario();
void cambiarClave();
void actualizarArchivo();
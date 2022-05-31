#pragma once
#include "Usuario.h"
#define CANTIDAD_USUARIOS 100

//BASE DE DATOS DE USUARIOS VOTANTES
struct ListaUsuarios
{
    Usuario usuario[CANTIDAD_USUARIOS];
};

//INICIAR LISTAS
void inicListaUsuarios();
void inicListaVotos();
void mostrarListaUsuario();

//BUSCAR PARA INICIAR SESION
int buscarUsuario(int cedula);
int buscarNumeroUsuario(int cedula);

//MENUS
void menuVotante(int numeroUsuario);
void menuReportero();

//MODIFICAR USUARIOS
void agregarUsuario();
void eliminarUsuario();
void cambiarClave();
void actualizarArchivo();

//VOTACION
int votar();
int registrarVoto(int cedula, int voto);

//FUNCIONES REPORTERO
void mostrarVotos();
void dosMas();
void gpr();
void ganaRegionN();
void ganaRegionS();
void ganaRegionC();
void ganaRegionC();
void totalVotos1();
void ganador();
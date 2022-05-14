#include <iostream>
#include "Administrador.h"
#include <ListaUsuarios.h>
#include <Usuario.h>
using namespace std;

void menuAdmin(){ //MENU PARA EL USUARIO ADMINISTRADOR
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
void menuvotante(){
	int op;
	int usuario2;
	
	
	
	
		cout<<"este es el modo votante "<<endl;
		cout<<"por favor ingrese su usuario"<<endl;
		cin>>usuario2;
		system("cls");
		if(usuario2==usuario[usuario2]){
		    cout<<"ingrese su clave"<<endl;
			cin>>clave;
			if (clave==Usuario.clave){
				do{
					cout<<"usted esta incrito en la region  "<<endl<<Usuario.region<<endl; ;
					cout<<"ingrese la opcion que desea "<<endl;
					cout<<"recuerde guardar su voto para que sea contado"<<endl;
					cout<<"1 para ver candidato\n. 2 para votar \n2. 3 para cambiar voto\n3. 4 guardar voto \n5. 0 cero para salir"<<endl;
					cin>>op;
					switch (op){
                            case 1:
                                    //funcion que muestra los candidatos 
                               break;
                           case 2:
                                   //funcion que retorna el valor de el voto
                              break;
                           case 3:
                                   //esta funcion cambia el voto en caso de un cambio de desicion 
                              break;
                           case 4:
                              //esta funcion guarda el voto definitivo y solo se podra usar una vez
                               break;
                           case 0:
                           //REGRESAR O SALIR
                               break;
                          default:
                                 cout << "Ingrese una funcion válida" << endl;
        }while(op!=0)
					
					
				}
			}
				
		}
	}
}

void menuvotante(){
	int op;
	int usuario3;
	
	
	
	
		cout<<"este es el modo reportero"<<endl;
		cout<<"por favor ingrese su usuario"<<endl;
		cin>>usuario3;
		system("cls");
		if(usuario2==usuario[usuario2]){
		    cout<<"ingrese su clave"<<endl;
			cin>>clave;
			if (clave==Usuario.clave){
				do{
					cout<<"usted esta reportando "<<endl<<Usuario.region<<endl; ;
					cout<<"ingrese la opcion que desea "<<endl;
				
					cout<<"1 para ver candidato con mayoria de votos \n. 2 para ver talba de votos actual\n2. 3 para ganador por regiones \n3.4 para los dos candidatos mejor posicionados\n5."<<endl;
					cout<<"5 para saber si hay segunda vuelta\n. 0 para salir  "
					cin>>op;
					switch (op){
                            case 1:
                                    //funcion que muestra quien va ganando 
                               break;
                           case 2:
                                   //funcion muestra el totalde votos para cada candidato
                              break;
                           case 3:
                                   //esta funcion muestra quien gana en cada rigion 
                              break;
                           case 4:
                              //esta funcion muestra los dos candidatos a mejor votados 
                               break;
                           case 5:
                                //esta funcio muestra si hay segunda vuelta  quienes son los dos candidatos 
                               break;
                            case 0:
							   //salir
                          default:
                                 cout << "Ingrese una funcion válida" << endl;
        }while(op!=0)
					
					
				}
			}
				
		}
	}
}



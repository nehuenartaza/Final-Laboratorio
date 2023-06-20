#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dimInt 15
#define dimChar 50
#define Fastronautas "astronauts"
#define Fnaves "ships"
#define Fmisiones "missions"

typedef struct {
	char nombre[dimChar];
	char apellido[dimChar];
	char apodo[dimChar];
	int ID;
	int edad;
	char nacionalidad[dimChar];
	char especialidad[dimChar]; //piloto, astrofisico, ingeniero espacial, biologo
	int horas_vuelo;
	int misiones;
	int horas_estacion_espacial;
	int estado; //1-activo, 2-retirado
} STastronauta;
typedef struct {
	int ID;
	int tipo_nave; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
	int vuelos;
	int horas_vuelo;
	int estado; //0-mantenimiento, 1-lista para usar, 2-en uso, 3-de baja
} STnave;
typedef struct {
	int ID;
	int ID_nave;
	int estado; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
	int destino; //1-EEI, 2-orbita terrestre, 3-luna
	int cargamento; //1-satelite, 2-insumos para la EE
	int tripulantes[dimInt];
	char detalle_mision[dimChar]; //breve descripcion
	int cant_tripulantes;
} STmision;

int main()
{
	int opcion = 0, inicio = 1, search_astronauta = 0, search_nave = 0, search_mision = 0, posicion = NULL;
	printf ( "Para entrar al menu ingrese 1\n" );
	scanf ( "%d", &inicio );
	while ( inicio == 1 ) {
		drawmenu_principal();
		scanf ( "%d", &opcion );
		switch ( opcion ) {
        case 0:
			inicio = 0;
			break;

		case 1:
			drawmenu_1();
			scanf ( "%d", &opcion );
			switch ( opcion ) {
			case 1:
				registrar_astronauta();
				break;

			case 2:
				registrar_nave();
				break;

			case 3:
				registrar_mision();
				break;

			case 4:
                system("cls");
				break;
			}
			break;
        case 2:
            drawmenu_2();
            scanf ( "%d", &opcion );
            switch ( opcion ) {
            case 1:
                modificar_astronauta();
                break;

            case 2:
                modificar_nave();
                break;

            case 3:
                modificar_mision();
                break;

            case 4:
                system("cls");
                break;
            }
            break;
        case 3:
            drawmenu_3();
            scanf ( "%d", &opcion );
            switch ( opcion ) {
            case 1:
                system("cls");
                printf ( "Ingrese ID del astronauta: \n" );
                scanf ( "%d", &search_astronauta );
                posicion = consultar_astronauta(search_astronauta);
                if ( posicion != NULL ) {
                    mostrar_al_astronauta(posicion);
                } else {
                        printf ( "El astronauta no existe\n" );
                    }
                break;

            case 2:
                system("cls");
                printf ( "Ingrese ID de la nave \n" );
                scanf ( "%d", &search_nave );
                posicion = consultar_nave(search_nave);
                if ( posicion != NULL ) {

                } else {
                        printf ( "La nave no existe \n" );
                    }
                break;

            case 3:
                system("cls");
                printf ( "Ingrese ID de la mision \n" );
                scanf ( "%d", &search_nave );
                posicion = consultar_nave(search_nave);
                if ( posicion != NULL ) {

                } else {
                        printf ( "La mision no existe \n" );
                    }
                break;
            }
            break;
		default:
			printf ( "opcion inexistente\n" );
			break;
		}
		//system("cls");
		posicion = NULL;
	}
  	return 0;
}

void registrar_astronauta() //crear la funcion de validar que no se repitan las ID de astronautas
{
	STastronauta user;
	int opcion = 1;
	while ( opcion == 1 ) {
		printf ( "Nombre del astronauta:\n" );
		fflush(stdin);
		gets ( user.nombre );
		printf ( "Apellido del astronauta:\n" );
		fflush(stdin);
		gets ( user.apellido );
		printf ( "Apodo del astronauta:\n" );
		fflush(stdin);
		gets ( user.apodo );
		printf ( "Su ID:\n" );
		scanf ( "%d", &user.ID );
		//Lorenzo: crear la funcion de validar que no se repitan las ID de astronautas

		printf ( "Su edad:\n" );
		scanf ( "%d", &user.edad );
		printf ( "Nacionalidad:\n" );
		fflush(stdin);
		gets ( user.nacionalidad );
		printf ( "Especialidad:\n" );
		fflush(stdin);
		gets ( user.especialidad );
		printf ( "Horas de vuelo acumuladas:\n" );
		scanf ( "%d", &user.horas_vuelo );
		printf ( "Cantidad de misiones en las que ha participado:\n" );
		scanf ( "%d", &user.misiones );
		printf ( "Horas invertidas en la estacion espacial:\n" );
		scanf ( "%d", &user.horas_estacion_espacial );
		user.estado = 1; //lo registra automaticamente en 'activo'
		guardar_astronauta(user);
		printf ( "para registrar otro astronauta ingrese 1:\n" );
		scanf ( "%d", &opcion );
	}
}

void guardar_astronauta(STastronauta user)
{
	FILE *archivo = fopen(Fastronautas, "ab");
	if ( archivo != NULL ) {
		fwrite(&user, sizeof(STastronauta), 1, archivo);
		fclose(archivo);
	}
}

void modificar_astronauta() //funcion que verifique que no se repita la ID
{
    STastronauta user, aux;
    int valor = 0, opcion = 0;
    mostrar_astronautas();
    printf ( "Modifique un astronauta\n" );
    scanf ( "%d", &valor );
    FILE *archivo = fopen(Fastronautas,"r+b");
    if ( archivo != NULL ) {
        fseek(archivo, sizeof(STastronauta) * valor, SEEK_SET);
        fread(&aux, sizeof(STastronauta), 1, archivo);
        user = aux;

        printf ( "modificar nombre? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevo nombre: \n" );
            fflush(stdin);
            gets ( user.nombre );
        }
        printf ( "cambiar apodo? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevo apodo: \n" );
            fflush(stdin);
            gets ( user.apodo );
        }
        printf ( "modificar apellido? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevo apellido: \n" );
            fflush(stdin);
            gets ( user.apellido );
        }
        printf ( "modificar ID? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) { //funcion que verifique que no se repita la ID
            printf ( "Nueva ID: \n" );
            scanf ( "%d", &user.ID );
        }
        printf ( "modificar edad? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva edad: \n" );
            scanf ( "%d", &user.edad );
        }
        printf ( "modificar nacionalidad? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva nacionalidad: \n" );
            fflush(stdin);
            gets ( user.nacionalidad );
        }
        printf ( "modificar especialidad? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva especialidad: \n" );
            fflush(stdin);
            gets ( user.especialidad );
        }
        printf ( "modificar horas de vuelo? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva cantidad de hrs de vuelo: \n" );
            scanf ( &user.horas_vuelo );
        }
        printf ( "modificar horas en la estacion espacial? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva cantidad de hrs en la estacion espacial: \n" );
            scanf ( &user.horas_estacion_espacial );
        }
        printf ( "modificar cantidad de misiones hechas? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva cantidad de misiones: \n" );
            scanf ( &user.misiones );
        }
        fseek(archivo, sizeof(STastronauta) * valor, SEEK_SET);
        fwrite(&user, sizeof(STastronauta), 1, archivo);
        fclose(archivo);
    }
}

void mostrar_astronautas()
{
    STastronauta aux;
    int i = 0;
    FILE *archivo = fopen(Fastronautas, "rb");
    if ( archivo != NULL ) {
        while ( !feof(archivo)) {
            fread(&aux, sizeof(STastronauta), 1, archivo);
            if ( !feof(archivo)) {
                printf ( "|%d| %s '%s' %s, Edad:%d, ID:%d, horas de vuelo:%d, horas en la estacion:%d\n", i, aux.nombre, aux.apodo, aux.apellido, aux.edad, aux.ID, aux.horas_vuelo, aux.horas_estacion_espacial );
                printf ( "Especialidad: %s, nacionalidad: %s, misiones hechas: %d ", aux.especialidad, aux.nacionalidad, aux.misiones );
                if ( aux.estado == 1 ) {
                    printf ( "Astronauta activo\n" );
                } else {
                        printf ( "Astronauta retirado\n" );
                    }
            }
            i++;
        }
    }
}

int consultar_astronauta(int buscador)
{
    STastronauta user;
    int posicion = NULL, i = 0;
    FILE *archivo = fopen(Fastronautas, "rb");
    if ( archivo != NULL ) {
        while ( !feof(archivo) && posicion == NULL ) {
            fread (&user, sizeof(STastronauta), 1, archivo);
            if ( !feof(archivo) && buscador == user.ID ) {
                posicion = i;
            }
            i++;
        }
    }
    return posicion;
}

void mostrar_al_astronauta(int posicion)
{
    STastronauta user;
    FILE *archivo = fopen(Fastronautas, "rb");
    if ( archivo != NULL ) {
        fseek(archivo, sizeof(STastronauta) * posicion, SEEK_SET);
        fread(&user, sizeof(STastronauta), 1, archivo);
        printf ( "%s '%s' %s, Edad:%d, ID:%d, horas de vuelo:%d, horas en la estacion:%d\n", user.nombre, user.apodo, user.apellido, user.edad, user.ID, user.horas_vuelo, user.horas_estacion_espacial );
        printf ( "Especialidad: %s, nacionalidad: %s, misiones hechas: %d \n", user.especialidad, user.nacionalidad, user.misiones );
        fclose(archivo);
    }
}

void registrar_nave() //crear la funcion que verifique que no se repitan las ID de naves
{
	STnave ship;
	int opcion = 1;
	while ( opcion == 1 ) {
		printf ( "ID de la nave:\n" );
		scanf ( "%d", &ship.ID );
		//Lorenzo: crear la funcion que verifique que no se repitan las ID de naves

		printf ( "Tipo de nave: 1-Starship, 2-Falcon 9, 3-Falcon Heavy\n" );
		scanf ( "%d", &ship.tipo_nave );
		while ( ship.tipo_nave < 0 || ship.tipo_nave > 3 ) {
			printf ( "No existe esa nave, intente de nuevo:\n" );
			scanf ( "%d", &ship.tipo_nave );
		}
		printf ( "Cantidad de vuelos:\n" );
		scanf ( "%d", &ship.vuelos );
		printf ( "Horas de vuelo:\n" );
		scanf ( "%d", &ship.horas_vuelo );
		ship.estado = 1; //lo registra automaticamente en 'lista para su uso'
		guardar_nave(ship);
		printf ( "para registrar otra nave ingrese 1:\n" );
		scanf ( "%d", &opcion );
	}

}

void guardar_nave(STnave ship)
{
	FILE *archivo = fopen(Fnaves, "ab");
	if ( archivo != NULL ) {
		fwrite(&ship, sizeof(STnave), 1, archivo);
		fclose(archivo);
	}
}

void modificar_nave()
{

}

void mostrar_naves()
{

}

int consultar_nave(int buscador)
{
    STnave nave;
    int posicion = NULL, i = 0;
    FILE *archivo = fopen(Fnaves, "rb");
    if ( archivo != NULL ) {
        while ( !feof(archivo) && posicion == NULL ) {
            fread (&nave, sizeof(STnave), 1, archivo);
            if ( !feof(archivo) && buscador == nave.ID ) {
                posicion = i;
            }
            i++;
        }
    }
    return posicion;
}

void mostrar_la_nave(int posicion)
{
    STnave nave;
    FILE *archivo = fopen(Fnaves, "rb");
    if ( archivo != NULL ) {
        fseek(archivo, sizeof(STnave) * posicion, SEEK_SET);
        fread(&nave, sizeof(STnave), 1, archivo);
        printf ( "ID de nave:%d, cantidad de vuelos:%d, horas de vuelo:%d ", nave.ID, nave.vuelos, nave.horas_vuelo );
        if ( nave.tipo_nave == 1 ) {
            printf ( "Tipo nave: Starship, " );
        } else if ( nave.tipo_nave == 2 ) {
                printf ( "Tipo nave: Falcon 9, " );
            } else {
                    printf ( "Tipo nave: Falcon-Heavy, " );
                }
        if ( nave.estado == 0 ) {
            printf ( "Estado: Mantenimiento\n" );
        } else if ( nave.estado == 1 ) {
                printf ( "Estado: lista para su uso\n" );
            } else if ( nave.estado == 2 ) {
                    printf ( "Estado: actualmente en uso\n" );
                } else {
                        printf ( "Estado: de baja" );
                    }
        fclose(archivo);
    }
}

void registrar_mision() //muchas funciones por hacer
{
	STmision mision;
	int opcion = 1, i = 0; //contador de tripulantes por mision
	while ( opcion == 1 ) {
		printf ( "ID de la mision\n" );
		scanf ( "%d", &mision.ID );
		//Lorenzo: crear la funcion que verifique que no se repitan las ID de misiones

		printf ( "ID de la nave:\n" );
		scanf ( "%d", &mision.ID_nave );
		//Lorenzo: crear la funcion que verifique si existe el ID de la nave

		printf ( "destino de la mision: 1-EEI, 2-orbita terrestre, 3-luna\n" );
		scanf ( "%d", &mision.destino );
		while ( mision.destino < 0 || mision.destino > 3 ) {
			printf ( "destino desconocido, intente de nuevo\n" );
			scanf ( "%d", &mision.destino );
		}
		printf ( "tipo de cargamento de la mision: 1-satelite, 2-insumos para la EE\n" );
		scanf ( "%d", &mision.cargamento );
		while ( mision.cargamento < 0 || mision.cargamento > 2 ) {
			printf ( "cargamento desconocido, intente de nuevo\n" );
			scanf ( "%d", &mision.cargamento );
		}
		printf ( "Ingrese las ID de los tripulantes que van a estar presentes en la mision: (hasta %d tripulantes)\n", dimInt );
		while ( opcion == 1 && i < dimInt ) {
			scanf ( "%d", &mision.tripulantes[i] );

			//Lorenzo: crear la funcion para verificar que el tripulante exista


			i++;
			printf ( "para meter otro tripulante ingrese 1:\n" );
			scanf ( "%d", &opcion );
		}
		mision.cant_tripulantes = i;
		printf ( "agregue una breve descripcion de la mision: (%d caracteres)\n", dimChar );
		fflush(stdin);
		gets ( mision.detalle_mision );
		guardar_mision(mision);
		printf ( "para registrar otra mision ingrese 1:\n" );
		scanf ( "%d", &opcion );
	}
}

void guardar_mision(STmision mision)
{
	FILE *archivo = fopen(Fmisiones, "ab");
	if ( archivo != NULL ) {
		fwrite(&mision, sizeof(STmision), 1, archivo);
		fclose(archivo);
	}
}

void modificar_mision() //funcion que verifique si existe el astronauta
{
    STmision mision, aux;
    int valor = 0, opcion = 0, i = 0;
    mostrar_misiones();
    printf ( "Modifique una mision\n" );
    scanf ( "%d", &valor );
    FILE *archivo = fopen(Fmisiones,"r+b");
    if ( archivo != NULL ) {
        fseek(archivo, sizeof(STmision) * valor, SEEK_SET);
        fread(&aux, sizeof(STmision), 1, archivo);
        mision = aux;

        printf ( "modificar ID? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva ID: \n" );
            scanf ( "%d", &mision.ID );
        }
        printf ( "modificar ID de la nave? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nueva ID de nave: \n" );
            scanf ( "%d", &mision.ID_nave );
        }
        printf ( "modificar detalles de la mision? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevos detalles: \n" );
            fflush(stdin);
            gets ( mision.detalle_mision );
        }
        printf ( "modificar cargamento? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevo cargamento: 1-satelite, 2-insumos para la EE\n" );
            scanf ( "%d", &mision.cargamento );
        }
        printf ( "modificar destino? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            printf ( "Nuevo destino: 1-EEI, 2-orbita terrestre, 3-luna" );
            scanf ( "%d", &mision.destino );
        }
        printf ( "Modificar tripulantes? 1-Si\n" );
        scanf ( "%d", &opcion );
        if ( opcion == 1 ) {
            mostrar_astronautas();
            printf ( "Seleccione los tripulantes por sus IDs:\n" );
            for ( i = 0; i < dimInt && opcion == 1; i++ ) {
                scanf ( "%d", &mision.tripulantes[i] );
                //funcion que verifique si existe el astronauta
                printf ( "Continuar? 1-Si\n" );
                scanf ( "%d", &opcion );
            }
        }

        fseek(archivo, sizeof(STastronauta) * valor, SEEK_SET);
        fwrite(&mision, sizeof(STastronauta), 1, archivo);
        fclose(archivo);
    }
}

void mostrar_misiones()
{
    STmision mision;
    int i = 0, j = 0;
    FILE *archivo = fopen(Fmisiones, "rb");
    if ( archivo != NULL ) {
        while ( !feof(archivo)) {
            fread(&mision, sizeof(STmision), 1, archivo);
            if ( !feof(archivo)) {
                printf ( "|%d| ID:%d, ID de nave:%d, ", i, mision.ID, mision.ID_nave );
                if ( mision.cargamento == 1 ) {
                    printf ( "Cargamento: satelite, " );
                } else {
                        printf ( "Cargamento: insumos para la EE, " );
                    }
                if ( mision.destino == 1 ) {
                    printf ( "Destino: EEI, " );
                } else if ( mision.destino == 2 ) {
                        printf ( "Destino: orbita terrestre\n" );
                    } else {
                            printf ( "Destino: Luna\n" );
                        }
                printf ( "Mision: %s\n", mision.detalle_mision );
                for ( j = 0; j < mision.cant_tripulantes; j++ ) {
                    printf ( "ID Tripulante n%d: %d\n", j+1, mision.tripulantes[j] );
                }
                if ( mision.estado == 1 ) {
                    printf ( "Estado de mision: Lista" );
                } else if ( mision.estado == 2 ) {
                        printf ( "Estado de mision: En vuelo" );
                    } else if ( mision.estado == 3 ) {
                            printf ( "Estado de mision: Retornada" );
                        } else if ( mision.estado == 4 ) {
                                printf ( "Estado de mision: Cancelada" );
                            } else {
                                    printf ( "Estado de mision: Fallida" );
                                }
            }
            i++;
        }
    }
}

int consultar_mision(int buscador)
{
    int posicion = NULL, i = 0;
    return posicion;
}

void drawmenu_principal()
{
	printf ( "1- Registrar\n" );
	printf ( "2- Modificar\n" );
	printf ( "3- Consultar\n" );
	printf ( "0- Cerrar programa\n" );
	printf ( "opcion: " );
}
void drawmenu_1()
{
	printf ( "1 | 1- Registrar astronautas\n" );
	printf ( "1 | 2- Registrar naves\n" );
	printf ( "1 | 3- Registrar misiones\n" );
	printf ( "1 | 4- Regresar al menu principal\n" );
	printf ( "opcion: " );
}
void drawmenu_2()
{
    printf ( "2 | 1- Modificar astronauta\n" );
    printf ( "2 | 2- Modificar nave\n" );
    printf ( "2 | 3- Modificar mision\n" );
    printf ( "2 | 4- Regresar\n" );
    printf ( "opcion: " );
}
void drawmenu_3()
{
    printf ( "3 | 1- Consultar astronautas por ID\n" );
    printf ( "3 | 2- Consultar naves por ID\n" );
    printf ( "3 | 3- Consultar misiones por ID\n" );
    printf ( "3 | 4- Regresar\n" );
    printf ( "opcion: " );
}

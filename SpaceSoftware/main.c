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
} STmision;

int main()
{
	int opcion = 0, inicio = 1;
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

				break;
			}
		default:
			printf ( "opcion inexistente\n" );
		}
	}
  	return 0;
}

void registrar_astronauta()
{
	STastronauta user;
	int opcion = 1;
	while ( opcion == 1 ) {
		printf ( "Nombre del astronauta:\n" );
		gets ( user.nombre );
		printf ( "Apellido del astronauta:\n" );
		gets ( user.apellido );
		printf ( "Apodo del astronauta:\n" );
		gets ( user.apodo );
		printf ( "Su ID:\n" );
		scanf ( "%d", &user.ID );
		//Lorenzo: crear la funcion de validar que no se repitan las ID de astronautas

		printf ( "Su edad:\n" );
		scanf ( "%d", &user.edad );
		printf ( "Nacionalidad:\n" );
		gets ( user.nacionalidad );
		printf ( "Especialidad:\n" );
		gets ( user.nacionalidad );
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

void registrar_nave()
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
		printf ( "para registrar otranave ingrese 1:\n" );
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

void registrar_mision()
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

			//Lorenzo: crear la funcion para verificar que el tripulante exista, no este de baja y no este en otra mision


			i++;
			printf ( "para meter otro tripulante ingrese 1:\n" );
			scanf ( "%d", &opcion );
		}
		printf ( "agregue una breve descripcion de la mision: (%d caracteres)\n", dimChar );
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



drawmenu_principal()
{
	printf ( "1- Registrar\n" );
	printf ( "2- Modificar\n" );
	printf ( "3- Consultar\n" );
	printf ( "0- Cerrar programa\n" );
	printf ( "opcion..." );
}

drawmenu_1()
{
	printf ( "1 | 1- Registrar astronautas\n" );
	printf ( "1 | 2- Registrar naves\n" );
	printf ( "1 | 3- Registrar misiones\n" );
	printf ( "1 | 4- Regresar al menu principal\n" );
	printf ( "opcion..." );
}
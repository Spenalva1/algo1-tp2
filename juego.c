#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define COLUMNAS_NIVEL1 15
#define FILAS_NIVEL1 15
#define COLUMNAS_NIVEL2 15
#define FILAS_NIVEL2 15
#define COLUMNAS_NIVEL3 20
#define FILAS_NIVEL3 20
#define COLUMNAS_NIVEL4 20
#define FILAS_NIVEL4 20
#define ELFOS 'L'
#define ENANOS 'G'
#define ORCOS 'O'
#define ENANOS_ATAQUE 60
#define ENANOS_ATAQUE_LETAL 100
#define ENANOS_NIVEL_1 5
#define ENANOS_NIVEL_3 3
#define ENANOS_NIVEL_4 4
#define ELFOS_ATAQUE 30
#define ELFOS_ATAQUE_LETAL 70
#define ELFOS_NIVEL_2 5
#define ELFOS_NIVEL_3 3
#define ELFOS_NIVEL_4 4
#define ORCOS_NIVEL_1 100
#define ORCOS_NIVEL_2 200
#define ORCOS_NIVEL_3 300
#define ORCOS_NIVEL_4 500
#define JUEGO_PERDIDO -1
#define JUEGO_JUGANDO 0
#define NIVEL_JUGANDO 0
#define ENANOS_COSTE 50
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL1 25
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL2 50
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 50
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 50
#define ELFOS_COSTE 50
#define SI 'S'
#define NO 'N'

/*
* Inicializara un nivel, cargando sus caminos, defensores y enemigos.
* nivel_numero debera ser un entero entre 1 y 4 (inlcusive ambos).
*/
void inicializar_nivel(nivel_t* nivel, int nivel_numero);

/*
* Creara y ubicará los defensores iniciales segun el nivel actual de juego.
* Juego deberá estar ya iniciaizado.
*/
void defensores_iniciales(juego_t* juego);

/*
* Se desarrollará el nivel indicado por nivel_numero (numero entero entre 1 y 4 ambos inclusive) del juego
* hasta que todos los orcos sean eliminados o una de las torres sea destruida.
* Juego deberá estar ya iniciaizado
*/
void jugar_nivel(juego_t* juego, int nivel_numero);

/*
* Agregará la cantidad indicada por tope de defensores del tipo indicado por "tipo" en el tablero del nivel actual de juego.
* Juego deberá estar ya iniciaizado
* tipo debe ser "G" o "L".
* tope debe ser positivo.
*/
void agregar_varios_defensores(juego_t* juego, char tipo, int tope);

/*
* Devuelve variable del tipo coordenada_t con informacón obtenida del usuario
* tipo debe ser "G" o "L"
*/
coordenada_t pedir_coordenadas_defensor(char tipo);

/*
* numero_nivel: numero entero entre 1 y 4 ambos inclusive
* devuelve TRUE: si coordenada esta dentro de los límites del tablero perteneciente al tablero del nivel indicado por numero_nivel.
* devuelve FALSE: si coordenada NO esta dentro de los límites del tablero perteneciente al tablero del nivel indicado por numero_nivel.
*/
bool coordenada_valida(coordenada_t coordenada, int numero_nivel);

/*
* Agrega un defensor (indicado por tipo) al nivel actual de juego, actualizando la resistensia de las torres y la cantidad de defensores extras restantes.
* tipo debe ser "G" o "L".
* Juego deberá estar ya iniciaizado.
*/
void agregar_defensor_extra(juego_t* juego, char tipo);

/*
* Dependiendo del nivel y de las condiciones actuales de juego, agregará, en caso de que el jugador lo desee, un defensor extra al nivel actual del juego.
* Juego deberá estar ya iniciaizado.
*/
void defensor_extra(juego_t* juego);

/*
* Pregunta al usuario si quiere agregar un defensor del tipo "tipo" al tablero del nivel actual.
* Devuelve TRUE en caso de que SÍ lo desee.
* Devuelve FALSE en caso de que NO lo desee.
* tipo debe ser "G" o "L".
*/
bool quiere_defensor_extra(char tipo);

/*
* Devuelve TRUE si alguna coordenada de camino coincide con las coordenadas de entrada y/o torre.
* camino deberá ser un camino válido.
* tope_camino positivo.
* entrada y torre coordenadas validas del tablero.
*/
bool camino_valido(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, coordenada_t entrada, coordenada_t torre);

/*
* Imprimirá en pantalla un cartel indicandole al usuario cómo termino la partida
* Si estado es -1 le indicará que perdió la partida.
* Si estado es distinto de -1 le indicará que ganó la partida.
*/
void mostrar_resultado(int estado);

int main(){
    int viento, humedad;
    char animo_legolas, animo_gimli;
	srand ((unsigned)time(NULL));
    animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    juego_t juego;
    inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);

    int i = 0;
    while(estado_juego(juego) == JUEGO_JUGANDO){
        i++;
        jugar_nivel(&juego, i);
    }

    mostrar_resultado(estado_juego(juego));

    return 0;
}

void mostrar_resultado(int estado){
    if(estado == JUEGO_PERDIDO){
        printf("*****************************************\n");
        printf("*****************************************\n");
        printf("**                                     **\n");
        printf("**            ¡HAS PERDIDO!            **\n");
        printf("**         SUERTE EN LA PROXIMA        **\n");
        printf("**                                     **\n");
        printf("*****************************************\n");
        printf("*****************************************\n");
    }else{
        printf("*****************************************\n");
        printf("*****************************************\n");
        printf("**                                     **\n");
        printf("**            ¡HAS GANADO!             **\n");
        printf("**          GRACIAS POR JUGAR          **\n");
        printf("**                                     **\n");
        printf("*****************************************\n");
        printf("*****************************************\n");
    }
}

bool coordenada_valida(coordenada_t coordenada, int numero_nivel){
	switch (numero_nivel){
		case 1:
			return (coordenada.fil < FILAS_NIVEL1 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL1 && coordenada.col >= 0);
			break;
		case 2:
			return (coordenada.fil < FILAS_NIVEL2 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL2 && coordenada.col >= 0);
			break;
		case 3:
			return (coordenada.fil < FILAS_NIVEL3 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL3 && coordenada.col >= 0);
			break;
		case 4:
			return (coordenada.fil < FILAS_NIVEL4 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL4 && coordenada.col >= 0);
			break;
		default:
			break;
	}
    return false;
}

coordenada_t pedir_coordenadas_defensor(char tipo){
    coordenada_t coordenada;
    if(tipo == ENANOS){
        printf("Coordenadas para un enano (F C): ");
    }else{
        printf("Coordenadas para un elfo (F C): ");
    }
    scanf("%d %d", &coordenada.fil, &coordenada.col);
    return coordenada;
}

void agregar_varios_defensores(juego_t* juego, char tipo, int tope){
    coordenada_t posicion;
    for(int i = 0; i < tope; i++){
        mostrar_juego(*juego);
        posicion = pedir_coordenadas_defensor(tipo);
        while(agregar_defensor(&(juego->nivel), posicion, tipo) == -1 || !coordenada_valida(posicion, juego->nivel_actual)){
            printf("Recuerde que debe ingresar una posicion que se encuentre dentro de los limites del tablero, y que no coincida con ningun camino ni defensor existente.\n");
            posicion = pedir_coordenadas_defensor(tipo);
        }
    }

}

void defensores_iniciales(juego_t* juego){
	juego->nivel.tope_defensores = 0;
    switch (juego->nivel_actual){
        case 1:
            agregar_varios_defensores(juego, ENANOS, ENANOS_NIVEL_1);
            break;
        
        case 2:
            agregar_varios_defensores(juego, ELFOS, ELFOS_NIVEL_2);
            break;
        
        case 3:
            agregar_varios_defensores(juego, ENANOS, ENANOS_NIVEL_3);
            agregar_varios_defensores(juego, ELFOS, ELFOS_NIVEL_3);
            break;
        
        case 4:
            agregar_varios_defensores(juego, ENANOS, ENANOS_NIVEL_4);
            agregar_varios_defensores(juego, ELFOS, ELFOS_NIVEL_4);
            break;
        
        default:
            break;
    }
}

void inicializar_nivel(nivel_t* nivel, int nivel_numero){
	coordenada_t entrada;
	coordenada_t torre;
	nivel->tope_enemigos = 0;

	switch (nivel_numero){
	case 1:
		entrada.col = COLUMNAS_NIVEL1 - 1;
		entrada.fil = rand() % FILAS_NIVEL1;
		torre.col = 0;
		torre.fil = rand() % FILAS_NIVEL1;

		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		nivel->tope_camino_2 = 0;

        nivel->max_enemigos_nivel = ORCOS_NIVEL_1;
		break;

	case 2:
		entrada.col = 0;
		entrada.fil = rand() % FILAS_NIVEL2;
		torre.col = COLUMNAS_NIVEL2 - 1;
		torre.fil = rand() % FILAS_NIVEL2;

		nivel->tope_camino_1 = 0;
		obtener_camino(nivel->camino_2, &(nivel->tope_camino_2), entrada, torre);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_2;
		break;

	case 3:
		entrada.fil = 0;
		entrada.col = rand() % (COLUMNAS_NIVEL3 / 2);
		torre.fil = FILAS_NIVEL3 - 1;
		torre.col = rand() % (COLUMNAS_NIVEL3 / 2);
		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		entrada.col = (rand() % (COLUMNAS_NIVEL3 / 2)) + (COLUMNAS_NIVEL3 / 2);
		torre.col = (rand() % (COLUMNAS_NIVEL3 / 2)) + (COLUMNAS_NIVEL3 / 2);
		obtener_camino(nivel->camino_2, &(nivel->tope_camino_2), entrada, torre);
        while(!camino_valido(nivel->camino_2, nivel->tope_camino_2, nivel->camino_1[0], nivel->camino_1[nivel->tope_camino_1 - 1]))
		    obtener_camino(nivel->camino_2, &(nivel->tope_camino_2), entrada, torre);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_3;
		break;
		
	case 4:
		entrada.fil = FILAS_NIVEL4 - 1;;
		entrada.col = rand() % (COLUMNAS_NIVEL4 / 2);
		torre.fil = 0;
		torre.col = rand() % (COLUMNAS_NIVEL4 / 2);
		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		entrada.col = (rand() % (COLUMNAS_NIVEL4 / 2)) + (COLUMNAS_NIVEL4 / 2);
		torre.col = (rand() % (COLUMNAS_NIVEL4 / 2)) + (COLUMNAS_NIVEL4 / 2);
		obtener_camino(nivel->camino_2, &(nivel->tope_camino_2), entrada, torre);
        while(!camino_valido(nivel->camino_2, nivel->tope_camino_2, nivel->camino_1[0], nivel->camino_1[nivel->tope_camino_1 - 1]))
		    obtener_camino(nivel->camino_2, &(nivel->tope_camino_2), entrada, torre);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_4;
		break;

	default:
		break;
	}
}

bool camino_valido(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, coordenada_t entrada, coordenada_t torre){
    bool camino_valido = true;
    int i = 0;
    while(i < tope_camino && camino_valido){
        if((camino[i].fil == entrada.fil && camino[i].col == entrada.col) || (camino[i].fil == torre.fil && camino[i].col == torre.col))
            camino_valido = false;
        i++;
    }
    return camino_valido;
}

void jugar_nivel(juego_t* juego, int nivel_numero){
    bool ultimo_extra_preguntado = false;
    juego->nivel_actual = nivel_numero;
    inicializar_nivel(&(juego->nivel), nivel_numero);
    defensores_iniciales(juego);

    mostrar_juego(*juego);
    while(estado_nivel(juego->nivel) == NIVEL_JUGANDO && estado_juego(*juego) != JUEGO_PERDIDO){
        detener_el_tiempo(0.5);
        jugar_turno(juego);
        mostrar_juego(*juego);
        if(juego->nivel.tope_enemigos > 0 && juego->nivel.tope_enemigos <= juego->nivel.max_enemigos_nivel && !ultimo_extra_preguntado)
		    defensor_extra(juego);
        if(juego->nivel.tope_enemigos == juego->nivel.max_enemigos_nivel)
            ultimo_extra_preguntado = true;
    }
}

void agregar_defensor_extra(juego_t* juego, char tipo){
	coordenada_t posicion;
	posicion = pedir_coordenadas_defensor(tipo);
	while(agregar_defensor(&(juego->nivel), posicion, tipo) == -1 || !coordenada_valida(posicion, juego->nivel_actual)){
		printf("Recuerde que debe ingresar una posicion que se encuentre dentro de los limites del tablero, y que no coincida con ningun camino ni defensor existente.\n");
        posicion = pedir_coordenadas_defensor(tipo);
	}
	if(tipo == ENANOS){
		juego->torres.resistencia_torre_1 -= ENANOS_COSTE;
		(juego->torres.enanos_extra)--;
	}else if(tipo == ELFOS){
		juego->torres.resistencia_torre_2 -= ELFOS_COSTE;
		(juego->torres.elfos_extra)--;
	}
}



void defensor_extra(juego_t* juego){
    bool agrego_enano = false;
	switch (juego->nivel_actual){
		case 1:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL1 == 0 && juego->torres.resistencia_torre_1 > ENANOS_COSTE && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS))
					agregar_defensor_extra(juego, ENANOS);
			}
			break;
		case 2:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL2 == 0 && juego->torres.resistencia_torre_2 > ELFOS_COSTE && juego->torres.elfos_extra > 0){
				if(quiere_defensor_extra(ELFOS))
					agregar_defensor_extra(juego, ELFOS);
			}
			break;
		case 3:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 == 0 && juego->torres.resistencia_torre_1 > ENANOS_COSTE && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS)){
					agregar_defensor_extra(juego, ENANOS);
                    agrego_enano = true;
                }
			}
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 == 0 && juego->torres.resistencia_torre_2 > ELFOS_COSTE && juego->torres.elfos_extra > 0 && !agrego_enano){
				if(quiere_defensor_extra(ELFOS))
					agregar_defensor_extra(juego, ELFOS);
			}
			break;
		case 4:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 == 0 && juego->torres.resistencia_torre_1 > ENANOS_COSTE && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS)){
					agregar_defensor_extra(juego, ENANOS);
                    agrego_enano = true;
                }
			}
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 == 0 && juego->torres.resistencia_torre_2 > ELFOS_COSTE && juego->torres.elfos_extra > 0 && !agrego_enano){
				if(quiere_defensor_extra(ELFOS))
					agregar_defensor_extra(juego, ELFOS);
			}
			break;
		
		default:
			break;
	}
}

bool quiere_defensor_extra(char tipo){
	char respuesta;
    if(tipo == ENANOS){
        printf("Desea agregar un enano extra? le costará %d de resistencia la torre 1 (S | N): ", ENANOS_COSTE);
    }else if((tipo == ELFOS)){
        printf("Desea agregar un elfo extra? le costará %d de resistencia la torre 2 (S | N): ", ELFOS_COSTE);
    }
	scanf(" %c", &respuesta);
	while(respuesta != SI && respuesta != NO){
        printf("Debe ingresar el caracter 'S' o 'N': ");
		scanf(" %c", &respuesta);
	}
    return respuesta == SI;
}
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include <stdio.h>
#include <stdbool.h>

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

/*
* Inicializara un nivel, cargando sus caminos, defensores y enemigos.
* nivel_numero debera ser un entero entre 1 y 4 (inlcusive ambos).
*/
void inicializar_nivel(nivel_t* nivel, int nivel_numero);

/*
*
*/
void ubicar_defensores(nivel_t* nivel, int tope_defensores, int tope_filas, int tope_columnas);

/*
*
*/
void defensores_iniciales(juego_t* juego);

/*
*
*/
void jugar_nivel(juego_t* juego, int nivel_numero);

/*
*
*/
bool coordenada_valida(coordenada_t coordenada, int numero_nivel);

/*
*
*/
void agregar_varios_defensores(juego_t* juego, char tipo, int tope);

int main(){
    // int viento, humedad;
    // char animo_legolas, animo_gimli;
    // animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    // juego_t juego;
    // inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);

    /* INICIALIZACION HARDCODEADA PARA PROBAR*/
    juego_t juego;
    inicializar_juego(&juego, 25, 25, 'B', 'B');
    /* -------------------------------------- */

    int i = 0;
    while(estado_juego(juego) == JUEGO_JUGANDO){
        i++;
        jugar_nivel(&juego, i);
    }
    
    system("clear");
    if(estado_juego(juego) == JUEGO_PERDIDO){
        printf("PERDISTE\n");
    }else{
        printf("GANASTE\n");
    }


    return 0;
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
    scanf(" %d %d", &coordenada.fil, &coordenada.col);
    return coordenada;
}

void agregar_varios_defensores(juego_t* juego, char tipo, int tope){
    coordenada_t posicion;
    for(int i = 0; i < tope; i++){
        mostrar_juego(*juego);
        posicion = pedir_coordenadas_defensor(tipo);
        while(agregar_defensor(&(juego->nivel), posicion, tipo) == -1 || !coordenada_valida(posicion, juego->nivel_actual)){
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

	switch (nivel_numero){
	case 1:
		entrada.col = COLUMNAS_NIVEL1 - 1;
		entrada.fil = rand() % FILAS_NIVEL1;
		torre.col = 0;
		torre.fil = rand() % FILAS_NIVEL1;

		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		nivel->tope_camino_2 = 0;

		nivel->tope_enemigos = 0;
        nivel->max_enemigos_nivel = ORCOS_NIVEL_1;
		break;

	case 2:
		entrada.col = 0;
		entrada.fil = rand() % FILAS_NIVEL2;
		torre.col = COLUMNAS_NIVEL2 - 1;
		torre.fil = rand() % FILAS_NIVEL2;

		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		nivel->tope_camino_2 = 0;

		nivel->tope_enemigos = 0;
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

		nivel->tope_enemigos = 0;
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

		nivel->tope_enemigos = 0;
        nivel->max_enemigos_nivel = ORCOS_NIVEL_4;
		break;

	default:
		break;
	}
}

void jugar_nivel(juego_t* juego, int nivel_numero){
    juego->nivel_actual = nivel_numero;
    inicializar_nivel(&(juego->nivel), nivel_numero);
    defensores_iniciales(juego);

    mostrar_juego(*juego);
    while(estado_nivel(juego->nivel) == NIVEL_JUGANDO && estado_juego(*juego) != JUEGO_PERDIDO){
        detener_el_tiempo(0.5);
        mostrar_juego(*juego);
        jugar_turno(juego);
    }
}
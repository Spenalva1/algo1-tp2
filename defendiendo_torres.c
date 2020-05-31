#include "defendiendo_torres.h"
#include "utiles.h"
#include <stdbool.h>

#define VIDA_INICIAL_TORRE 600
#define ENANOS_EXTRA 10
#define ELFOS_EXTRA 10
#define ENANOS_COSTE 50
#define DIVISOR_VIENTO 2
#define DIVISOR_HUMEDAD 2
#define ELFOS_COSTE 50
#define ANIMO_BUENO 'B'
#define ANIMO_REGULAR 'R'
#define CRITICO_GIMLI_MALO 0
#define CRITICO_GIMLI_REGULAR 10
#define CRITICO_GIMLI_BUENO 25
#define CRITICO_LEGOLAS_MALO 0
#define CRITICO_LEGOLAS_REGULAR 10
#define CRITICO_LEGOLAS_BUENO 25
#define NIVEL_ULTIMO 4
#define NIVEL_TERMINADO 1
#define NIVEL_JUGANDO 0
#define JUEGO_GANADO 1
#define JUEGO_PERDIDO -1
#define JUEGO_JUGANDO 0
#define TORRES_CON_VIDA 1
#define TORRE_DESTRUIDA 0
#define COLUMNAS_NIVEL1 15
#define FILAS_NIVEL1 15
#define COLUMNAS_NIVEL2 15
#define FILAS_NIVEL2 15
#define COLUMNAS_NIVEL3 20
#define FILAS_NIVEL3 20
#define COLUMNAS_NIVEL4 20
#define FILAS_NIVEL4 20
#define VACIO ' '
#define CAMINO_1 'X'
#define CAMINO_2 'R'
#define ENTRADA 'E'
#define TORRE 'T'
#define ELFOS 'L'
#define ENANOS 'G'
#define ORCOS 'O'
#define ENANOS_ATAQUE 60
#define ENANOS_NIVEL_1 5
#define ENANOS_NIVEL_3 3
#define ENANOS_NIVEL_4 4
#define ELFOS_ATAQUE 30
#define ELFOS_NIVEL_2 5
#define ELFOS_NIVEL_3 3
#define ELFOS_NIVEL_4 4
#define ORCOS_NIVEL_1 100
#define ORCOS_NIVEL_2 200
#define ORCOS_NIVEL_3 300
#define ORCOS_NIVEL_4 500
#define ORCOS_VIDA 200
#define ORCOS_MAX_EXTRA 99
#define ALCANCE_ENANO 8



void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli){
	juego->torres.resistencia_torre_1 = VIDA_INICIAL_TORRE;
	juego->torres.resistencia_torre_2 = VIDA_INICIAL_TORRE;
	juego->torres.enanos_extra = ENANOS_EXTRA;
	juego->torres.elfos_extra = ELFOS_EXTRA;
	juego->fallo_legolas = viento / DIVISOR_VIENTO;
	juego->fallo_gimli = humedad / DIVISOR_VIENTO;
	if(animo_gimli == ANIMO_BUENO)
		juego->critico_gimli = CRITICO_GIMLI_BUENO;
	else if(animo_gimli == ANIMO_REGULAR)
		juego->critico_gimli = CRITICO_GIMLI_REGULAR;
	else
		juego->critico_gimli = CRITICO_GIMLI_MALO;


	if(animo_legolas == ANIMO_BUENO)
		juego->critico_legolas = CRITICO_LEGOLAS_BUENO;
	else if(animo_legolas == ANIMO_REGULAR)
		juego->critico_legolas = CRITICO_LEGOLAS_REGULAR;
	else
		juego->critico_legolas = CRITICO_LEGOLAS_MALO;

	juego->nivel_actual = 1;
}

int estado_nivel(nivel_t nivel){
	int nivel_estado = NIVEL_TERMINADO;
	int i = 0;
	while((nivel_estado == NIVEL_TERMINADO) && (i < nivel.tope_enemigos)){
		if(nivel.enemigos[i].vida > 0)
			nivel_estado = NIVEL_JUGANDO;
		i++;
	}
	return nivel_estado;
}

/*
*
*/
int torres_con_vida(torres_t torres){
	if ((torres.resistencia_torre_1 > 0) && (torres.resistencia_torre_2 > 0))
		return TORRES_CON_VIDA;
	return TORRE_DESTRUIDA;
}

int estado_juego(juego_t juego){
	if(torres_con_vida(juego.torres) == TORRE_DESTRUIDA)
		return JUEGO_PERDIDO;
	if((juego.nivel_actual == NIVEL_ULTIMO) && (estado_nivel(juego.nivel) == 1))
		return JUEGO_GANADO;
	return JUEGO_JUGANDO;
}

/*
*
*/
bool hay_defensor(coordenada_t coordenada, defensor_t defensores[MAX_DEFENSORES], int tope_defensores){
	bool hay_defensor = false;
	for (int i = 0; i < tope_defensores; i++){
		if(defensores[i].posicion.fil == coordenada.fil && defensores[i].posicion.col == coordenada.col)
			hay_defensor = true;
	}
	return hay_defensor;
}

/*
*
*/
bool hay_camino(coordenada_t coordenada, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	bool hay_camino = false;
	for (int i = 0; i < tope_camino; i++){
		if(camino[i].fil == coordenada.fil && camino[i].col == coordenada.col)
			hay_camino = true;
	}
	return hay_camino;
}

/*
*
*/
bool coordenada_ocupada(coordenada_t coordenada, nivel_t nivel, int defensores_ubicados){
	bool hay_camino1 = hay_camino(coordenada, nivel.camino_1, nivel.tope_camino_1);
	bool hay_camino2 = hay_camino(coordenada, nivel.camino_2, nivel.tope_camino_2);
	bool hay_defensor1 = hay_defensor(coordenada, nivel.defensores, defensores_ubicados);
	return hay_camino1 || hay_camino2 || hay_defensor1;
}


/*
*
*/
void ubicar_defensores(nivel_t* nivel, int tope_defensores, int tope_filas, int tope_columnas){
	for(int i = 0; i < tope_defensores; i++){
		nivel->defensores[i].posicion.fil = rand() % tope_filas;
		nivel->defensores[i].posicion.col = rand() % tope_columnas;
		while(coordenada_ocupada(nivel->defensores[i].posicion, *nivel, i)){
			nivel->defensores[i].posicion.fil = rand() % tope_filas;
			nivel->defensores[i].posicion.col = rand() % tope_columnas;
		}
	}
}

/*
*
*/
void cargar_orcos(enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos, int camino){
	enemigo_t orco;
	orco.camino = camino;
	if(camino == 1){
		for(int i = 1; i <= tope_enemigos; i++){
			orco.vida = 200 + (rand() % ORCOS_MAX_EXTRA + 1);
			orco.pos_en_camino = i * -1;
			enemigos[i - 1] = orco;
		}
	}else if(camino == 2){
		for(int i = tope_enemigos + 1; i <= tope_enemigos * 2; i++){
			orco.vida = 200 + (rand() % ORCOS_MAX_EXTRA + 1);
			orco.pos_en_camino = (i - tope_enemigos)  * -1;
			enemigos[i - 1] = orco;
		}
	}
}

void inicializar_nivel(nivel_t* nivel, int nivel_numero){
	coordenada_t entrada;
	coordenada_t torre;
	defensor_t defensor;

	switch (nivel_numero){
	case 1:
		entrada.col = COLUMNAS_NIVEL1 - 1;
		entrada.fil = rand() % FILAS_NIVEL1;
		torre.col = 0;
		torre.fil = rand() % FILAS_NIVEL1;

		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		nivel->tope_camino_2 = 0;

		defensor.tipo = ENANOS;
		defensor.fuerza_ataque = ENANOS_ATAQUE;
		for(int i = 0; i < ENANOS_NIVEL_1; i++){
			nivel->defensores[i] = defensor;
		}
		nivel->tope_defensores = ENANOS_NIVEL_1;
		ubicar_defensores(nivel, nivel->tope_defensores, FILAS_NIVEL1, COLUMNAS_NIVEL1);

		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_1, 1);
		nivel->tope_enemigos = ORCOS_NIVEL_1;
		break;

	case 2:
		entrada.col = 0;
		entrada.fil = rand() % FILAS_NIVEL2;
		torre.col = COLUMNAS_NIVEL2 - 1;
		torre.fil = rand() % FILAS_NIVEL2;

		obtener_camino(nivel->camino_1, &(nivel->tope_camino_1), entrada, torre);
		nivel->tope_camino_2 = 0;

		defensor.tipo = ELFOS;
		defensor.fuerza_ataque = ELFOS_ATAQUE;
		for(int i = 0; i < ELFOS_NIVEL_2; i++){
			nivel->defensores[i] = defensor;
		}
		nivel->tope_defensores = ELFOS_NIVEL_2;
		ubicar_defensores(nivel, nivel->tope_defensores, FILAS_NIVEL2, COLUMNAS_NIVEL2);

		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_2, 1);
		nivel->tope_enemigos = ORCOS_NIVEL_2;
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

		defensor.tipo = ENANOS;
		defensor.fuerza_ataque = ENANOS_ATAQUE;
		for(int i = 0; i < ENANOS_NIVEL_3; i++){
			nivel->defensores[i] = defensor;
		}
		defensor.tipo = ELFOS;
		defensor.fuerza_ataque = ELFOS_ATAQUE;
		for(int i = ENANOS_NIVEL_3; i < (ELFOS_NIVEL_3 + ENANOS_NIVEL_3); i++){
			nivel->defensores[i] = defensor;
		}
		nivel->tope_defensores = ELFOS_NIVEL_3 + ENANOS_NIVEL_3;
		
		ubicar_defensores(nivel, nivel->tope_defensores, FILAS_NIVEL3, COLUMNAS_NIVEL3);

		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_3 / 2, 1);
		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_3 / 2, 2);
		nivel->tope_enemigos = ORCOS_NIVEL_3;
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

		defensor.tipo = ENANOS;
		defensor.fuerza_ataque = ENANOS_ATAQUE;
		for(int i = 0; i < ENANOS_NIVEL_4; i++){
			nivel->defensores[i] = defensor;
		}
		defensor.tipo = ELFOS;
		defensor.fuerza_ataque = ELFOS_ATAQUE;
		for(int i = ELFOS_NIVEL_4; i < (ELFOS_NIVEL_4 + ELFOS_NIVEL_4); i++){
			nivel->defensores[i] = defensor;
		}
		nivel->tope_defensores = ELFOS_NIVEL_4 + ELFOS_NIVEL_4;
		
		ubicar_defensores(nivel, nivel->tope_defensores, FILAS_NIVEL4, COLUMNAS_NIVEL4);

		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_4 / 2, 1);
		cargar_orcos(nivel->enemigos, ORCOS_NIVEL_4 / 2, 2);
		nivel->tope_enemigos = ORCOS_NIVEL_4;
		break;

	default:
		break;
	}
}

/* 
*	inicializa la matriz con valores VACIO
*/
void inicializar_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], int tope_filas, int tope_columnas){
	for (int i = 0; i < tope_filas; i++){
		for (int j = 0; j < tope_columnas; j++){	
			tablero[i][j] = VACIO;
		} 
	}
}

/* 
*	Representa el camino con caracteres CAMINO en una matriz tablero ya inicializada
*/
void insertar_camino_en_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, char caracter){
	if(tope_camino > 0){
		tablero[camino[0].fil][camino[0].col] = ENTRADA;
		for (int i = 1; i < tope_camino - 1; i++){
			tablero[camino[i].fil][camino[i].col] = caracter;
		}
		tablero[camino[tope_camino - 1].fil][camino[tope_camino - 1].col] = TORRE;
	}
}

/* 
*	
*/
void insertar_defensores_en_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], defensor_t defensores[MAX_LONGITUD_CAMINO], int tope_defensores){
	for (int i = 0; i < tope_defensores; i++){
		tablero[defensores[i].posicion.fil][defensores[i].posicion.col] = defensores[i].tipo;
	}
}

/* 
*	
*/
void insertar_enemigos_en_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], nivel_t nivel){
	for (int i = 0; i < nivel.tope_enemigos; i++){
		if ((nivel.enemigos[i].vida > 0) && (nivel.enemigos[i].pos_en_camino >= 0)){
			if(nivel.enemigos[i].camino == 1){
				tablero[nivel.camino_1[nivel.enemigos[i].pos_en_camino].fil][nivel.camino_1[nivel.enemigos[i].pos_en_camino].col] = ORCOS;
			}
			if(nivel.enemigos[i].camino == 2){
				tablero[nivel.camino_2[nivel.enemigos[i].pos_en_camino].fil][nivel.camino_2[nivel.enemigos[i].pos_en_camino].col] = ORCOS;
			}
		}
	}
}

void mostrar_juego(juego_t juego){
	system("clear");
	char tablero[MAX_COLUMNAS][MAX_FILAS];
	int tope_filas, tope_columnas;
	printf("Nivel actual: %d\n", juego.nivel_actual);
	printf("Vida torre 1: %d\n", juego.torres.resistencia_torre_1);
	printf("Vida torre 2: %d\n", juego.torres.resistencia_torre_2);
	printf("Enanos extra: %d\n", juego.torres.enanos_extra);
	printf("Elfos torre 1: %d\n", juego.torres.elfos_extra);

	switch (juego.nivel_actual){
		case 1:
			tope_filas = FILAS_NIVEL1;
			tope_columnas = COLUMNAS_NIVEL1;
			break;
		case 2:
			tope_filas = FILAS_NIVEL2;
			tope_columnas = COLUMNAS_NIVEL2;
			break;
		case 3:
			tope_filas = FILAS_NIVEL3;
			tope_columnas = COLUMNAS_NIVEL3;
			break;
		case 4:
			tope_filas = FILAS_NIVEL4;
			tope_columnas = COLUMNAS_NIVEL4;
			break;
		default:
			break;
	}

	inicializar_tablero(tablero, tope_filas, tope_columnas);
	insertar_camino_en_tablero(tablero, juego.nivel.camino_1, juego.nivel.tope_camino_1, CAMINO_1);
	insertar_camino_en_tablero(tablero, juego.nivel.camino_2, juego.nivel.tope_camino_2, CAMINO_2);
	insertar_defensores_en_tablero(tablero, juego.nivel.defensores, juego.nivel.tope_defensores);
	insertar_enemigos_en_tablero(tablero, juego.nivel);
	for (int i = 0; i < tope_filas; i++){
		for (int j = 0; j < tope_columnas; j++){	
			printf("%c",tablero[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
*
*/
void mover_enemigos(juego_t* juego){
	for(int i = 0; i < juego->nivel.tope_enemigos; i++){
		if(juego->nivel.enemigos[i].vida > 0){
			(juego->nivel.enemigos[i].pos_en_camino)++;
			if(juego->nivel.enemigos[i].camino == 1){
				if(juego->nivel.enemigos[i].pos_en_camino >= (juego->nivel.tope_camino_1 - 1)){
					juego->torres.resistencia_torre_1 -= juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = -1;
				}
			}
			if(juego->nivel.enemigos[i].camino == 2){
				if(juego->nivel.enemigos[i].pos_en_camino >= (juego->nivel.tope_camino_2 - 1)){
					juego->torres.resistencia_torre_2 -= juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = -1;
				}
			}
		}
	}
}

/*
*
*/
void ataque_enano(nivel_t* nivel, int atacante, int fallo, int critico){
	int distancia_fila, distancia_columna;
	bool ataque_realizado = false;
	int i = 0;
	while((i < nivel->tope_enemigos) && !ataque_realizado){
		if ((nivel->enemigos[i].vida > 0 ) && (nivel->enemigos[i].pos_en_camino >= 0)){
			if(nivel->enemigos[i].camino == 1){
				distancia_fila = abs(nivel->defensores[atacante].posicion.fil - nivel->camino_1[nivel->enemigos[i].pos_en_camino].fil);
				distancia_columna = abs(nivel->defensores[atacante].posicion.col - nivel->camino_1[nivel->enemigos[i].pos_en_camino].col);
			}
			if(nivel->enemigos[i].camino == 2){
				distancia_fila = abs(nivel->defensores[atacante].posicion.fil - nivel->camino_2[nivel->enemigos[i].pos_en_camino].fil);
				distancia_columna = abs(nivel->defensores[atacante].posicion.col - nivel->camino_2[nivel->enemigos[i].pos_en_camino].col);
			}
			if(distancia_fila <= 1 && distancia_columna <=1){
				ataque_realizado = true;
				nivel->enemigos[i].vida -= ENANOS_ATAQUE;
				// printf("el enano de la posicion %d %d ataco al orco de la posicion %d %d y este le quedó %d de vida\n", nivel->defensores[atacante].posicion.fil, nivel->defensores[atacante].posicion.col, nivel->camino_1[nivel->enemigos[i].pos_en_camino].fil, nivel->camino_1[nivel->enemigos[i].pos_en_camino].col, nivel->enemigos[i].vida);
				// detener_el_tiempo(5);
			}
		}
		i++;
	}
}

/*
*
*/
void ataque_defensores(juego_t* juego){
	for(int i = 0; i < juego->nivel.tope_defensores; i++){
		if(juego->nivel.defensores[i].tipo == ENANOS)
			ataque_enano(&(juego->nivel), i, juego->fallo_gimli, juego->critico_gimli);
	}
}



void jugar_turno(juego_t* juego){
	ataque_defensores(juego);
	mover_enemigos(juego);
}
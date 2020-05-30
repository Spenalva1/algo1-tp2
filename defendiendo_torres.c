#include "defendiendo_torres.h"
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


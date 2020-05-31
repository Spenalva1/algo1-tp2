#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"

int main(){
    // int viento, humedad;
    // char animo_legolas, animo_gimli;
    // animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    // juego_t juego;
    // inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);

    /* INICIALIZACION HARDCODEADA PARA PROBAR*/
    juego_t juego;
    inicializar_juego(&juego, 75, 50, 'B', 'M');
    /* -------------------------------------- */


    juego.nivel_actual = 3;
    inicializar_nivel(&(juego.nivel), 3);
    mostrar_juego(juego);
    for(int i = 0; i < 1150; i++){
        detener_el_tiempo(1);
        mostrar_juego(juego);
        jugar_turno(&juego);
    }

    // for(int i = 0; i < juego.nivel.tope_enemigos; i++){
    //     printf("%d | ", juego.nivel.enemigos[i].pos_en_camino);
    // }
    // printf("\n--------------------------\n");
    // jugar_turno(&juego);

    // for(int i = 0; i < juego.nivel.tope_enemigos; i++){
    //     printf("%d | ", juego.nivel.enemigos[i].pos_en_camino);
    // }

    return 0;
}
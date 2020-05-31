#include "animos.h"
#include "defendiendo_torres.h"

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


    inicializar_nivel(&(juego.nivel), 2);

    mostrar_juego(juego);

    return 0;
}
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"

int main(){
    int viento, humedad;
    char animo_legolas, animo_gimli;
    animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    juego_t juego;
    inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);
    printf("resistencia 1: %d. resistencia 2: %d. enanos: %d. elfos: %d.\n", juego.torres.resistencia_torre_1, juego.torres.resistencia_torre_2, juego.torres.enanos_extra, juego.torres.elfos_extra);
    printf("critico_l: %d. critico_g: %d. fallo_l: %d. fallo_g: %d\n", juego.critico_legolas, juego.critico_gimli, juego.fallo_legolas, juego.fallo_gimli);
    return 0;
}
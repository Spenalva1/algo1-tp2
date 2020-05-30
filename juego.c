#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"

int main(){
    int viento, humedad;
    char animo_legolas, animo_gimli;
    animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    juego_t juego;
    inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);
    return 0;
}
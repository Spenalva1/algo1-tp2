#include "animos.h"
#include <stdio.h>
#include <stdbool.h>


const int DIA_MIN = 1;
const int DIA_MAX = 30;
const char MANANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char IZQUIERDO = 'I';
const char DERECHO = 'D';
const int PUNTOS_DERECHO = 10;
const char ENSALADA = 'E';
const int PUNTOS_ENSALADA = 20;
const char HAMBURGUESA = 'H';
const int PUNTOS_HAMBURGUESA = 15;
const char PIZZA = 'P';
const int PUNTOS_PIZZA = 10;
const char GUISO = 'G';
const int PUNTOS_GUISO = 5;
const int DORMIDAS_MIN = 0;
const int DORMIDAS_MAX = 12;
const int DORMIDAS_POCO = 4;
const int PUNTOS_DORMIDAS_POCO = 0;
const int DORMIDAS_MEDIO = 8;
const int PUNTOS_DORMIDAS_MEDIO = 10;
const int PUNTOS_DORMIDAS_MUCHO = 20;
const char ANIMO_MALO = 'M';
const int PUNTOS_ANIMO_MALO = 20;
const char ANIMO_REGULAR = 'R';
const int PUNTOS_ANIMO_REGULAR = 35;
const char ANIMO_BUENO = 'B';
const int DIA_BAJO = 10;
const int DIA_MEDIO = 20;
const int VIENTO_BAJO = 25;
const int VIENTO_MEDIO = 50;
const int VIENTO_ALTO = 75;
const int HUMEDAD_BAJA = 25;
const int HUMEDAD_MEDIA = 50;
const int HUMEDAD_ALTA = 75;

/*post: devuelve TRUE si el valor recibido se encuentra dentro de un rango especifico. Si no, devuelve FALSE */
bool es_dia_valido(int dia){
    return ((dia >= DIA_MIN) && (dia <= DIA_MAX));
}

/*post: devuelve TRUE si el valor recibido se encuentra dentro de los valores válidos. Si no, devuelve FALSE */
bool es_hora_valida(char hora){
    return ((hora == MANANA) || (hora == TARDE) || (hora == NOCHE));
}

/*post: devuelve TRUE si el valor recibido se encuentra dentro de los valores válidos. Si no, devuelve FALSE */
bool es_pie_valido(char pie){
    return ((pie == IZQUIERDO) || (pie == DERECHO));
}

/*post: devuelve TRUE si el valor recibido se encuentra dentro de los valores válidos. Si no, devuelve FALSE */
bool es_cena_valida(char cena){
    return ((cena == ENSALADA) || (cena == HAMBURGUESA) || (cena == PIZZA) || (cena == GUISO));
}

/*post: devuelve TRUE si el valor recibido se encuentra dentro de un rango especifico. Si no, devuelve FALSE */
bool es_horas_dormidas_valida(int horas_dormidas){
    return ((horas_dormidas >= DORMIDAS_MIN) && (horas_dormidas <= DORMIDAS_MAX));
}

/*post: asigna un dia ingresado por el usuario y validado a la variable de la referencia recibida  */
void obtener_dia(int* dia){
    int auxiliar;
    printf("Ingresar dia del mes: ");
    scanf("%d", &auxiliar);
    while(!es_dia_valido(auxiliar)){
        printf("El dia debe ser un numero entre 1 y 30 (ambos inclusive): ");
        scanf("%d", &auxiliar);
    }
    *dia = auxiliar;
}

/*pre: recibe referencia de una variable que contenga un numero entre DIA_MIN Y DIA_MAX */
/*post: devuelve la velocidad del viento a partir del valor ingresado  */
int calcular_viento(int* dia){
    if(*dia <= DIA_BAJO){
        return VIENTO_ALTO;
    }else if(*dia <= DIA_MEDIO){
        return VIENTO_MEDIO;
    }
    return VIENTO_BAJO;
}

/*post: asigna una hora ingresada por el usuario y validada a la variable de la referencia recibida  */
void obtener_hora(char* hora){
    char auxiliar;
    printf("Ingresar hora del dia (M -> mañana || T -> tarde || N -> noche): ");
    scanf(" %c", &auxiliar);
    while(!es_hora_valida(auxiliar)){
        printf("La hora debe ser un caracter 'M', 'T' o 'N': ");
        scanf(" %c", &auxiliar);
    }
    *hora = auxiliar;
}

/*pre: recibe referencia de una variable que contenga un caracter que sea igual a MANANA, TARDE o NOCHE  */
/*post: devuelve un valor de humedad dependiente del valor ingresado  */
int calcular_humedad(char* hora){
    if(*hora == MANANA){
        return HUMEDAD_ALTA;
    }else if(*hora == TARDE){
        return HUMEDAD_BAJA;
    }
    return HUMEDAD_MEDIA;
}

/*post: asigna un pie ingresado por el usuario y validado a la variable de la referencia recibida  */
void obtener_pie(char* pie){
    char auxiliar;
    printf("Ingresar pie con el cual se levantó (D -> derecho || I -> izquierdo): ");
    scanf(" %c", &auxiliar);
    while(!es_pie_valido(auxiliar)){
        printf("El pie debe ser un caracter 'D' o 'I': ");
        scanf(" %c", &auxiliar);
    }
    *pie = auxiliar;
}

/*post: asigna una cena ingresada por el usuario y validada a la variable de la referencia recibida  */
void obtener_cena(char* cena){
    char auxiliar;
    printf("Ingresar cena de la noche anterior (E -> ensalada | H -> hamburguesa || P -> pizza || G -> guiso): ");
    scanf(" %c", &auxiliar);
    while(!es_cena_valida(auxiliar)){
        printf("El cena debe ser un caracter 'E', 'H', 'P' o 'G': ");
        scanf(" %c", &auxiliar);
    }
    *cena = auxiliar;
}

/*post: asigna unas horas dormidas ingresadas por el usuario y validadas a la variable de la referencia recibida  */
void obtener_horas_dormidas(int* horas_dormidas){
    int auxiliar;
    printf("Ingresar horas dormidas: ");
    scanf("%d", &auxiliar);
    while(!es_horas_dormidas_valida(auxiliar)){
        printf("Las horas dormidas deben ser un numero entre 0 y 12 (ambos inclusive): ");
        scanf("%d", &auxiliar);
    }
    *horas_dormidas = auxiliar;
}

/* pre:  */
/*      pie: caracter igual a DERECHO O IZQUIERDO*/
/*      cena: caracter igual a ENSALADA, PIZZA, HAMBURGUESA O GUISO*/
/*      horas_dormidas: numero entre DORMIDAS_MIN y DORMIDAS_MAX*/
/* post: devuelve el puntaje calculado a partir de los valores ingresados */
int calcular_puntos_animo(char pie, char cena, int horas_dormidas){
    int puntos = 0;

    if(pie == DERECHO){
        puntos += PUNTOS_DERECHO;       
    }

    if(cena == ENSALADA){
        puntos += PUNTOS_ENSALADA;
    }else if(cena == HAMBURGUESA){
        puntos += PUNTOS_HAMBURGUESA;
    }else if(cena == PIZZA){
        puntos += PUNTOS_PIZZA;
    }else if(cena == GUISO){
        puntos += PUNTOS_GUISO;
    }

    if(horas_dormidas <= DORMIDAS_POCO){
        puntos += PUNTOS_DORMIDAS_POCO;
    }else if(horas_dormidas <= DORMIDAS_MEDIO){
        puntos += PUNTOS_DORMIDAS_MEDIO;
    }else{
        puntos += PUNTOS_DORMIDAS_MUCHO;
    }

    return puntos;
}

/*post: asigna la informacion de un personaje ingresada por el usuario y validada a las variables de la referencias recibidas  */
void obtener_informacion_personaje(char* pie, char* cena, int* horas_dormidas){
    obtener_pie(pie);
    obtener_cena(cena);
    obtener_horas_dormidas(horas_dormidas);
}

/* pre:  */
/*      pie: caracter igual a DERECHO O IZQUIERDO*/
/*      cena: caracter igual a ENSALADA, PIZZA, HAMBURGUESA O GUISO*/
/*      horas_dormidas: numero entre DORMIDAS_MIN y DORMIDAS_MAX*/
/* post: devuelve el animo de un personaje calculado a partir de los valores ingresados */
char calcular_animo(char pie, char cena, int horas_dormidas){
    int puntos = calcular_puntos_animo(pie, cena, horas_dormidas);
    if(puntos <= PUNTOS_ANIMO_MALO){
        return ANIMO_MALO;
    } else if (puntos <= PUNTOS_ANIMO_REGULAR){
        return ANIMO_REGULAR;
    }
    return ANIMO_BUENO;
}


void animos(int* viento, int* humedad , char* animo_legolas , char* animo_gimli){
    int dia;
    char hora;
    char pie_legolas, cena_legolas;
    int horas_dormidas_legolas;
    char pie_gimli, cena_gimli;
    int horas_dormidas_gimli;

    obtener_dia(&dia);
    *viento = calcular_viento(&dia);

    obtener_hora(&hora);
    *humedad = calcular_humedad(&hora);

    printf("----------------------------------------------------\n");
    printf("Le haremos unas preguntas acerca de Legolas.\n");
    obtener_informacion_personaje(&pie_legolas, &cena_legolas, &horas_dormidas_legolas);
    printf("----------------------------------------------------\n");
    printf("Le haremos unas preguntas acerca de GIMLI.\n");
    obtener_informacion_personaje(&pie_gimli, &cena_gimli, &horas_dormidas_gimli);

    *animo_legolas = calcular_animo(pie_legolas, cena_legolas, horas_dormidas_legolas);
    *animo_gimli = calcular_animo(pie_gimli, cena_gimli, horas_dormidas_gimli);

    printf("----------------------------------------------------\n");
    printf("Viento: %d km/h.\nHumedad: %%%d.\nEl animo de Legolas es %c.\nEl animo de Gimli es %c.\n", *viento, *humedad, *animo_legolas, *animo_gimli);
}
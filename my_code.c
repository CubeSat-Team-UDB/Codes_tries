#include <stdio.h>

#define TEMP_MAX 40 // Temperatura máxima en grados Celsius
#define ALT_MAX 30 // Altura máxima en km (30 km)
#define MEM_MAX 16 // Memoria máxima en GB (16 GB)
#define VOLT_PAYLOAD_MIN 5 // Voltaje mínimo para payload en V
#define VOLT_TRANS_MIN 3.3 // Voltaje mínimo para transmisión en V

// Funciones para cada modo
void mod_surv() {
    printf("Entrando al modo de supervivencia\n");
}

void mod_norm() {
    printf("Entrando al modo normal\n");
}

void mod_trans() {
    printf("Entrando al modo de transmisión\n");
}

void mod_pay() {
    printf("Entrando al modo de payload\n");
}

int main() {
    float temperatura, voltaje;
    int altura_km, espacio_memoria_GB;

    // Paso 1: Pedir valores de los sensores y validar cada uno
    printf("Introduce la temperatura en grados Celsius: ");
    scanf("%f", &temperatura);
    if (temperatura <= TEMP_MAX) {
        printf("Temperatura dentro del rango.\n");
    } else {
        printf("Temperatura fuera del rango. (Límite: %.1d °C)\n", TEMP_MAX);
    }
    
    printf("Introduce la altura en kilómetros: ");
    scanf("%d", &altura_km);
    if (altura_km <= ALT_MAX) {
        printf("Altura dentro del rango.\n");
    } else {
        printf("Altura fuera del rango. (Límite: %d km)\n", ALT_MAX);
    }
    
    printf("Introduce el voltaje actual en voltios: ");
    scanf("%f", &voltaje);
    if (voltaje >= VOLT_TRANS_MIN) {
        printf("Voltaje adecuado para transmisión.\n");
    } else {
        printf("Voltaje insuficiente para transmisión. (Límite: %.1f V)\n", VOLT_TRANS_MIN);
    }

    printf("Introduce el espacio disponible en memoria en GB: ");
    scanf("%d", &espacio_memoria_GB);
    if (espacio_memoria_GB <= MEM_MAX) {
        printf("Espacio en memoria dentro del rango.\n");
    } else {
        printf("Espacio en memoria fuera del rango. (Límite: %d GB)\n", MEM_MAX);
    }

    // Paso 2: Validación de los modos
    if (temperatura <= TEMP_MAX && altura_km <= ALT_MAX && espacio_memoria_GB <= MEM_MAX) {
        mod_surv();

        if (voltaje >= VOLT_TRANS_MIN) {
            mod_norm();

            if (voltaje >= VOLT_TRANS_MIN) {
                mod_trans();

                if (voltaje >= VOLT_PAYLOAD_MIN) {
                    mod_pay();
                } else {
                    printf("Error: Voltaje insuficiente para el modo de payload.\n");
                    mod_surv();  // Regresa al modo de supervivencia
                }
            } else {
                printf("Error: Voltaje insuficiente para el modo de transmisión.\n");
                mod_surv();  // Regresa al modo de supervivencia
            }
        } else {
            printf("Error: Voltaje insuficiente para el modo normal.\n");
            mod_surv();  // Regresa al modo de supervivencia
        }
    } else {
        printf("Error: Fallo en las condiciones iniciales. El cubesat entra en modo de supervivencia.\n");
        mod_surv();
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PACIENTES 50
#define LONG_NOMBRE 20
#define LONG_DIRECCION 20
#define LONG_TELEFONO 11
#define LONG_CP 6

typedef struct {
    char calle[LONG_DIRECCION];
    int numero;
    char colonia[LONG_DIRECCION];
    char cp[LONG_CP];
    char ciudad[LONG_DIRECCION];
} Domicilio;

typedef struct {
    char nombre[LONG_NOMBRE];
    int edad;
    char sexo;
    int condicion;
    Domicilio domicilio;
    char telefono[LONG_TELEFONO];
} Paciente;

void leerPacientes(Paciente pacientes[], int cantidad);
void mostrarEstadisticasGenero(Paciente pacientes[], int cantidad);
void mostrarDistribucionCondiciones(Paciente pacientes[], int cantidad);
void listarPacientesGraves(Paciente pacientes[], int cantidad);

int main(void) {
    Paciente hospital[MAX_PACIENTES];
    int numPacientes;

    do {
        printf("Ingrese el número de pacientes (1-%d): ", MAX_PACIENTES);
        scanf("%d", &numPacientes);
        while(getchar() != '\n');
    } while (numPacientes > MAX_PACIENTES || numPacientes < 1);

    leerPacientes(hospital, numPacientes);

    printf("\n=== Estadísticas del Hospital ===\n");
    mostrarEstadisticasGenero(hospital, numPacientes);
    mostrarDistribucionCondiciones(hospital, numPacientes);
    listarPacientesGraves(hospital, numPacientes);

    return 0;
}

void leerPacientes(Paciente pacientes[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("\n=== Datos del Paciente %d ===\n", i + 1);

        printf("Nombre completo: ");
        fgets(pacientes[i].nombre, LONG_NOMBRE, stdin);
        pacientes[i].nombre[strcspn(pacientes[i].nombre, "\n")] = '\0';

        printf("Edad: ");
        scanf("%d", &pacientes[i].edad);
        while(getchar() != '\n');

        printf("Sexo (F/M): ");
        scanf("%c", &pacientes[i].sexo);
        pacientes[i].sexo = toupper(pacientes[i].sexo);
        while(getchar() != '\n');

        printf("Condición (1-5, donde 5 es más grave): ");
        scanf("%d", &pacientes[i].condicion);
        while(getchar() != '\n');

        printf("\n--- Domicilio ---\n");
        printf("Calle: ");
        fgets(pacientes[i].domicilio.calle, LONG_DIRECCION, stdin);
        pacientes[i].domicilio.calle[strcspn(pacientes[i].domicilio.calle, "\n")] = '\0';

        printf("Número: ");
        scanf("%d", &pacientes[i].domicilio.numero);
        while(getchar() != '\n');

        printf("Colonia: ");
        fgets(pacientes[i].domicilio.colonia, LONG_DIRECCION, stdin);
        pacientes[i].domicilio.colonia[strcspn(pacientes[i].domicilio.colonia, "\n")] = '\0';

        printf("Código Postal: ");
        fgets(pacientes[i].domicilio.cp, LONG_CP, stdin);
        pacientes[i].domicilio.cp[strcspn(pacientes[i].domicilio.cp, "\n")] = '\0';

        printf("Ciudad: ");
        fgets(pacientes[i].domicilio.ciudad, LONG_DIRECCION, stdin);
        pacientes[i].domicilio.ciudad[strcspn(pacientes[i].domicilio.ciudad, "\n")] = '\0';

        printf("Teléfono (10 dígitos): ");
        fgets(pacientes[i].telefono, LONG_TELEFONO, stdin);
        pacientes[i].telefono[strcspn(pacientes[i].telefono, "\n")] = '\0';
    }
}

void mostrarEstadisticasGenero(Paciente pacientes[], int cantidad) {
    int mujeres = 0, hombres = 0;

    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].sexo == 'F') mujeres++;
        else if (pacientes[i].sexo == 'M') hombres++;
    }

    printf("\nDistribución por género:\n");
    printf("Mujeres: %d (%.1f%%)\n", mujeres, (float)mujeres/cantidad*100);
    printf("Hombres: %d (%.1f%%)\n", hombres, (float)hombres/cantidad*100);
}

void mostrarDistribucionCondiciones(Paciente pacientes[], int cantidad) {
    int condiciones[5] = {0};

    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].condicion >= 1 && pacientes[i].condicion <= 5) {
            condiciones[pacientes[i].condicion - 1]++;
        }
    }

    printf("\nDistribución por condición:\n");
    for (int i = 0; i < 5; i++) {
        printf("Condición %d: %d pacientes\n", i+1, condiciones[i]);
    }
}

void listarPacientesGraves(Paciente pacientes[], int cantidad) {
    printf("\nPacientes en condición grave (5):\n");
    int encontrados = 0;

    for (int i = 0; i < cantidad; i++) {
        if (pacientes[i].condicion == 5) {
            printf("- %s, %d años, Tel: %s\n",
                   pacientes[i].nombre,
                   pacientes[i].edad,
                   pacientes[i].telefono);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No hay pacientes en condición grave.\n");
    }
}

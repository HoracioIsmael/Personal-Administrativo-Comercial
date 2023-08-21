/*
    Identificacion del grupo; Error501
    Apellido y nombre de los integrantes:
    Farias Milagros, Fernandes Maciel Anahi, Correa Horacio, Estrada Guillermo, Condori Fernando.
    Fecha de realizacion: 14 de Junio de 2023.
    Otros datos identificatorios
    !!!!IMPORTANTEEEE!!!!
    =====!!!!!EJECUTAR DESDE LA INTERFAZ DE LINEA DE COMANDOS ( CMD )!!!!!====
    Una vez accedido al directorio ejecutar los siguientes comandos:
    1-    gcc -c personal.c -o personal.o  //Compila personal.c a personal.o (archivo objeto).
    2-    ar rcs libpersonal.a personal.o  //Crea o actualiza libreria libpersonal.a.
    3-    gcc main.c -L. -lpersonal -o programa   //Compila main.c y enlaza con libpersonal.a.
    4-    programa.exe   //Ejecutar el programa compilado
    5-    Disfruta del programa!!!
*/
#include "personal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definición de macros para el formato de texto en la consola
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define UNDERLINE "\x1B[4m"

// Colores de fondo
#define BG_BLACK "\x1B[40m"
#define BG_RED "\x1B[41m"
#define BG_GREEN "\x1B[42m"
#define BG_YELLOW "\x1B[43m"
#define BG_BLUE "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN "\x1B[46m"
#define BG_WHITE "\x1B[47m"

// Colores de texto
#define FG_BLACK "\x1B[30m"
#define FG_RED "\x1B[31m"
#define FG_GREEN "\x1B[32m"
#define FG_YELLOW "\x1B[33m"
#define FG_BLUE "\x1B[34m"
#define FG_MAGENTA "\x1B[35m"
#define FG_CYAN "\x1B[36m"
#define FG_WHITE "\x1B[37m"

int main()
{
    int opcion;
    do
    {
        // system("clear"); // Limpiar la consola (para sistemas tipo UNIX)
        system("cls"); // Descomenta esta linea si estas en Windows
        printf(BOLD FG_RED BG_BLACK 
               " ==========  ========    ========      ======    ========             // //\n");
        printf(" ==========  ==========  ==========  ==========  ==========       ============\n");
        printf(" ==          ==      ==  ==      ==  ==      ==  ==      ==      ============\n");
        printf(" ==          ==      ==  ==      ==  ==      ==  ==      ==         // //\n");
        printf(" =======     ==========  ==========  ==      ==  ==========\n");
        printf(" =======     ========    ========    ==      ==  ========      =======    ===      =\n");
        printf(" ==          ==    ==    ==    ==    ==      ==  ==    ==      ==       ==   ==  ===\n");
        printf(" ==          ==     ==   ==     ==   ==      ==  ==     ==     ======   ==   ==   ==\n");
        printf(" ==========  ==      ==  ==      ==  ==========  ==      ==         ==  ==   ==   ==\n");
        printf(" ==========  ==      ==  ==      ==    ======    ==      ==    ======     ===     ==\n" RESET);
        printf("\n" RESET);
        printf(BOLD FG_GREEN BG_BLACK " ===== MENU =====\n" RESET);
        printf(BOLD FG_CYAN BG_BLACK " 1. Alta de personal administrativo\n");
        printf(" 2. Baja de personal administrativo\n");
        printf(" 3. Consulta de personal administrativo\n");
        printf(" 4. Listado general de personal administrativo\n");
        printf(" 5. Listado particular de personal administrativo\n");
        printf(" 6. Modificacion de personal administrativo\n");
        printf(" 7. Ordenamiento de personal administrativo por menor o mayor Fecha de Ingreso\n");
        printf(" 8. Ordenamiento de personal administrativo por minimo y maximo de sueldo\n");
        printf(" 9. Salir\n");
        printf(RESET BOLD " Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            AltaPersonalAdministrativo();
            break;
        case 2:
            BajaPersonalAdministrativo();
            break;
        case 3:
            ConsultaPersonalAdministrativo();
            break;
        case 4:
            ListadoGeneralPersonalAdministrativo();
            break;
        case 5:
            ListadoParticularPersonalAdministrativo();
            break;
        case 6:
            ModificarPersonalAdministrativo();
            break;
        case 7:
            OrdenamientoIngresoPersonalAdministrativo();
            break;
        case 8:
            MinimoMaximoPersonalAdministrativo();
            break;
        case 9:
            printf("Hasta luego!!\n");
            break;
        default:
            printf(UNDERLINE FG_RED "Opcion invalida. Por favor, seleccione una opcion valida.\n" RESET);
            break;
        }

        printf("\n");
        printf("Presione Enter para continuar...");
        limpiarBuffer();
    } while (opcion != 9);

    return 0;
}

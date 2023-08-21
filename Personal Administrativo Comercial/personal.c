/*
    Identificacion del grupo; Error501
    Apellido y nombre de los integrantes:
    Farias Milagros, Fernandes Maciel Anahi, Correa Horacio, Estrada Guillermo, Condori Fernando.
    Fecha de realizacion: 14 de Junio de 2023.
    Otros datos identificatorios.
*/

#include "personal.h"
#include <ctype.h>

// Definicion de macros para el formato de texto en la consola
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
#define MAX_NOMBRE 50
struct FechaIngreso fechaIngreso;

void convertirMayusculas(char *cadena);

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//------------------------------------------------------------------------------------------//

int validarFechaIngreso(int dia, int mes, int anio)
{
    struct tm fechaActual;
    time_t tiempoActual = time(NULL);
    fechaActual = *localtime(&tiempoActual);

    // Obtener el a�o actual
    int anioActual = fechaActual.tm_year + 1900;

    if (anio > anioActual || (anio == anioActual && mes > fechaActual.tm_mon + 1) ||
        (anio == anioActual && mes == fechaActual.tm_mon + 1 && dia > fechaActual.tm_mday))
    {
        return 0; // La fecha de ingreso es posterior a la fecha actual
    }

    return 1; // La fecha de ingreso es valida
}

//------------------------------------------------------------------------------------------//

int buscarLegajo(PersonalAdministrativo personal[], int totalPersonal, int legajo)
{
    for (int i = 0; i < totalPersonal; i++)
    {
        if (personal[i].legajo == legajo)
        {
            return i; // Se encontro el legajo en la posicion i
        }
    }
    return -1; // No se encontro el legajo
}

void AltaPersonalAdministrativo()
{
    PersonalAdministrativo nuevoPersonal;
    PersonalAdministrativo personal[MAX_REGISTROS];
    puts(BOLD FG_CYAN BG_BLACK "Ingrese los datos del nuevo personal administrativo:" RESET);

    int totalPersonal = 0;

    srand(time(NULL)); // Inicializar la semilla para generar numeros aleatorios

    do
    {
        nuevoPersonal.legajo = rand() % 50 + 1; // Generar legajo aleatorio entre 1 y 50

        if (buscarLegajo(personal, totalPersonal, nuevoPersonal.legajo) != -1)
        {
            continue; // El legajo ya esta en uso, generar uno nuevo
        }

        break;
    } while (1);

    int numeroDocumento;
    bool numeroDocumentoValido = false;

    do
    {
        printf(FG_GREEN "Ingrese el Numero de Documento del personal administrativo: " RESET);
        scanf("%d", &numeroDocumento);
        limpiarBuffer();

        if (numeroDocumento <= 0 || !validarLongitudNumerica(numeroDocumento, MAX_NUMERO))
        {
            printf(FG_RED "El Numero de Documento ingresado no es valido. Por favor, ingrese nuevamente.\n" RESET);
        }
        else
        {
            FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
            if (archivo == NULL)
            {
                // Si el archivo no existe, lo creamos con modo "wb" para escritura binaria
                archivo = fopen(ARCHIVO_DATOS, "wb");
                if (archivo == NULL)
                {
                    printf(FG_RED "Error al crear el archivo.\n" RESET);
                    exit(EXIT_FAILURE);
                }
                fclose(archivo);
            }

            archivo = fopen(ARCHIVO_DATOS, "rb+");
            if (archivo == NULL)
            {
                printf(FG_RED "Error al abrir el archivo.\n" RESET);
                exit(EXIT_FAILURE);
            }

            if (!validarNumeroDocumento(numeroDocumento, archivo))
            {
                printf(FG_RED "El Numero de Documento ingresado ya existe en el archivo. Por favor, ingrese un numero de documento diferente.\n" RESET);
            }
            else
            {
                nuevoPersonal.numeroDocumento = numeroDocumento;
                numeroDocumentoValido = true;
            }

            fclose(archivo);
        }
    } while (!numeroDocumentoValido);

    do
    {
        printf(FG_GREEN "Apellido y Nombre: " RESET);
        fgets(nuevoPersonal.apellidoNombre, sizeof(nuevoPersonal.apellidoNombre), stdin);
        limpiarBuffer();

        if (strlen(nuevoPersonal.apellidoNombre) > MAX_NOMBRE - 1)
        {
            puts("El apellido y nombre ingresado excede la longitud permitida.");
            continue;
        }

        break;
    } while (1);

    do
    {
        printf(FG_GREEN "Domicilio: " RESET);
        fgets(nuevoPersonal.domicilio, sizeof(nuevoPersonal.domicilio), stdin);
        limpiarBuffer();

        if (strlen(nuevoPersonal.domicilio) > MAX_NOMBRE - 1)
        {
            puts("El domicilio ingresado excede la longitud permitida.");
            continue;
        }

        break;
    } while (1);

    do
    {
        printf(FG_GREEN "Localidad: " RESET);
        fgets(nuevoPersonal.localidad, sizeof(nuevoPersonal.localidad), stdin);
        limpiarBuffer();

        if (strlen(nuevoPersonal.localidad) > MAX_NOMBRE - 1)
        {
            puts("La localidad ingresada excede la longitud permitida.");
            continue;
        }

        break;
    } while (1);

    do
    {
        printf(FG_GREEN "Provincia: " RESET);
        fgets(nuevoPersonal.provincia, sizeof(nuevoPersonal.provincia), stdin);
        limpiarBuffer();

        if (strlen(nuevoPersonal.provincia) > MAX_NOMBRE - 1)
        {
            puts("La provincia ingresada excede la longitud permitida.");
            continue;
        }

        break;
    } while (1);

    int puestoValido = 0;
    do
    {
        printf(FG_GREEN "Puesto: (1-ADMINISTRATIVO, 2-CONTADOR, 3-ANALISTA, 4-PROGRAMADOR, 5-OTRO) " RESET);
        char puestoStr[MAX_NOMBRE];
        fgets(puestoStr, sizeof(puestoStr), stdin);

        int opcion = atoi(puestoStr);
        switch (opcion)
        {
        case 1:
            nuevoPersonal.puesto = ADMINISTRATIVO;
            puestoValido = 1;
            break;
        case 2:
            nuevoPersonal.puesto = CONTADOR;
            puestoValido = 1;
            break;
        case 3:
            nuevoPersonal.puesto = ANALISTA;
            puestoValido = 1;
            break;
        case 4:
            nuevoPersonal.puesto = PROGRAMADOR;
            puestoValido = 1;
            break;
        case 5:
            nuevoPersonal.puesto = OTRO;
            puestoValido = 1;
            break;
        default:
            puts("Opcion de puesto no valida. Por favor, ingrese un valor valido.");
            break;
        }
    } while (!puestoValido);

    int categoriaValida = 0;
    do
    {
        printf(FG_GREEN "Categoria: (1-JUNIOR, 2-SEMISENIOR, 3-SENIOR, 4-GERENTE, 5-DIRECTOR) " RESET);
        char categoriaStr[MAX_NOMBRE];
        fgets(categoriaStr, sizeof(categoriaStr), stdin);

        int opcion = atoi(categoriaStr);
        switch (opcion)
        {
        case 1:
            nuevoPersonal.categoria = JUNIOR;
            categoriaValida = 1;
            break;
        case 2:
            nuevoPersonal.categoria = SEMISENIOR;
            categoriaValida = 1;
            break;
        case 3:
            nuevoPersonal.categoria = SENIOR;
            categoriaValida = 1;
            break;
        case 4:
            nuevoPersonal.categoria = GERENTE;
            categoriaValida = 1;
            break;
        case 5:
            nuevoPersonal.categoria = DIRECTOR;
            categoriaValida = 1;
            break;
        default:
            puts("Opcion de categoria no valida. Por favor, ingrese un valor valido.");
            break;
        }
    } while (!categoriaValida);

    do
    {
        struct FechaIngreso fechaIngreso;

        printf(FG_GREEN "Fecha de ingreso (dd/mm/aaaa): " RESET);
        scanf("%d/%d/%d", &fechaIngreso.dia, &fechaIngreso.mes, &fechaIngreso.anio);
        limpiarBuffer();

        if (!validarFechaIngreso(fechaIngreso.dia, fechaIngreso.mes, fechaIngreso.anio))
        {
            printf("La fecha de ingreso ingresada es invalida o posterior a la fecha actual.\n");
            continue;
        }
        nuevoPersonal.fechaIngreso = fechaIngreso;
        break;
    } while (1);

    int sectorAsignadoValido = 0;
    do
    {
        printf(FG_GREEN "Sector Asignado: (1-VENTAS, 2-MARKETING, 3-RECURSOS_HUMANOS, 4-FINANZAS, 5-PRODUCCION) " RESET);
        char sectorAsignadoStr[MAX_NOMBRE];
        fgets(sectorAsignadoStr, sizeof(sectorAsignadoStr), stdin);

        int opcion = atoi(sectorAsignadoStr);
        switch (opcion)
        {
        case 1:
            nuevoPersonal.sectorAsignado = VENTAS;
            sectorAsignadoValido = 1;
            break;
        case 2:
            nuevoPersonal.sectorAsignado = MARKETING;
            sectorAsignadoValido = 1;
            break;
        case 3:
            nuevoPersonal.sectorAsignado = RECURSOS_HUMANOS;
            sectorAsignadoValido = 1;
            break;
        case 4:
            nuevoPersonal.sectorAsignado = FINANZAS;
            sectorAsignadoValido = 1;
            break;
        case 5:
            nuevoPersonal.sectorAsignado = PRODUCCION;
            sectorAsignadoValido = 1;
            break;
        default:
            puts("Opcion de puesto no valida. Por favor, ingrese un valor valido.");
            break;
        }
    } while (!sectorAsignadoValido);

    int tareasValida = 0;
    do
    {
        printf(FG_GREEN "Tareas:  (1-PLANIFICACION, 2-GESTION_PROYECTOS, 3-SOPORTE_TECNICO, 4-ANALISIS_DATOS, 5-QA_TESTER)" RESET);
        char tareasStr[MAX_NOMBRE];
        fgets(tareasStr, sizeof(tareasStr), stdin);

        int opcion = atoi(tareasStr);
        switch (opcion)
        {
        case 1:
            nuevoPersonal.tareas = PLANIFICACION;
            tareasValida = 1;
            break;
        case 2:
            nuevoPersonal.tareas = GESTION_PROYECTOS;
            tareasValida = 1;
            break;
        case 3:
            nuevoPersonal.tareas = SOPORTE_TECNICO;
            tareasValida = 1;
            break;
        case 4:
            nuevoPersonal.tareas = ANALISIS_DATOS;
            tareasValida = 1;
            break;
        case 5:
            nuevoPersonal.tareas = QA_TESTER;
            tareasValida = 1;
            break;
        default:
            puts("Opcion de puesto no valida. Por favor, ingrese un valor valido.");
            break;
        }
    } while (!tareasValida);

    do
    {
        printf(FG_GREEN "Sueldo nominal: " RESET);
        scanf("%f", &nuevoPersonal.sueldoNominal);
        limpiarBuffer();

        if (!validarLongitudNumericaDecimal(nuevoPersonal.sueldoNominal, 10))
        {
            puts("El sueldo ingresado excede la longitud permitida.");
            continue;
        }

        break;
    } while (1);

    // Guardar los datos del nuevo personal administrativo solo si el legajo es unico
    if (totalPersonal < MAX_REGISTROS)
    {
        personal[totalPersonal] = nuevoPersonal;
        totalPersonal++;

        FILE *archivo = fopen(ARCHIVO_DATOS, "ab");
        if (archivo == NULL)
        {
            puts("Error al abrir el archivo.");
            return;
        }

        fwrite(&nuevoPersonal, sizeof(PersonalAdministrativo), 1, archivo);

        fclose(archivo);

        puts(BOLD FG_GREEN "El personal administrativo ha sido dado de alta exitosamente." RESET);
        // Preguntar si desea seguir dando de alta personal
        int seguirDandoDeAlta;
        do
        {
            printf(FG_CYAN BOLD "Desea seguir dando de alta personal administrativo? (1: Si, 2: No): " RESET);
            scanf("%d", &seguirDandoDeAlta);
            limpiarBuffer();

            if (seguirDandoDeAlta == 1)
            {
                AltaPersonalAdministrativo();
                return;
            }
            else if (seguirDandoDeAlta == 2)
            {
                return;
            }
            else
            {
                printf(FG_RED "Opcion invalida. Por favor, ingrese una opcion valida.\n" RESET);
            }
        } while (1);
    }
    else
    {
        puts(BOLD FG_RED "No se pueden agregar mas personal administrativo. Se ha alcanzado el limite maximo." RESET);
    }
}

//------------------------------------------------------------------------------------------//

void BajaPersonalAdministrativo()
{
    char apellidoNombreBusqueda[MAX_NOMBRE];

    do
    {
        printf(FG_YELLOW "Ingrese el Apellido y Nombre del personal administrativo a dar de baja: " RESET);
        fgets(apellidoNombreBusqueda, sizeof(apellidoNombreBusqueda), stdin);
        limpiarBuffer();

        if (strlen(apellidoNombreBusqueda) > MAX_NOMBRE - 1)
        {
            puts(FG_RED "El apellido y nombre ingresado excede la longitud permitida." RESET);
        }
        else
        {
            break;
        }
    } while (1);

    PersonalAdministrativo personal;
    FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
    FILE *archivoTemp = fopen("temp.bin", "wb");
    FILE *archivoEliminados = fopen(ARCHIVO_ELIMINADOS, "ab");

    if (archivo == NULL || archivoTemp == NULL || archivoEliminados == NULL)
    {
        puts(FG_RED "Error al abrir los archivos." RESET);
        return;
    }

    int encontrado = 0;

    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        if (strcmp(personal.apellidoNombre, apellidoNombreBusqueda) == 0)
        {
            encontrado = 1;

            // Mostrar los datos del personal antes de dar de baja
            printf(BOLD FG_GREEN "Datos del personal a dar de baja:\n" RESET);
            printf(FG_GREEN "Legajo: %d\n" RESET, personal.legajo);
            printf(FG_GREEN "Numero de Documento: %d\n" RESET, personal.numeroDocumento);
            printf(FG_GREEN "Apellido y Nombre: %s\n" RESET, personal.apellidoNombre);
            printf(FG_GREEN "Domicilio: %s\n" RESET, personal.domicilio);
            printf(FG_GREEN "Localidad: %s\n" RESET, personal.localidad);
            printf(FG_GREEN "Provincia: %s\n" RESET, personal.provincia);

            switch (personal.puesto)
            {
            case ADMINISTRATIVO:
                printf(FG_GREEN "Puesto: ADMINISTRATIVO\n" RESET);
                break;
            case CONTADOR:
                printf(FG_GREEN "Puesto: CONTADOR\n" RESET);
                break;
            case ANALISTA:
                printf(FG_GREEN "Puesto: ANALISTA\n" RESET);
                break;
            case PROGRAMADOR:
                printf(FG_GREEN "Puesto: PROGRAMADOR\n" RESET);
                break;
            case OTRO:
                printf(FG_GREEN "Puesto: OTRO\n" RESET);
                break;
            }

            switch (personal.categoria)
            {
            case JUNIOR:
                printf(FG_GREEN "Categoria: JUNIOR\n" RESET);
                break;
            case SEMISENIOR:
                printf(FG_GREEN "Categoria: SEMISENIOR\n" RESET);
                break;
            case SENIOR:
                printf(FG_GREEN "Categoria: SENIOR\n" RESET);
                break;
            case GERENTE:
                printf(FG_GREEN "Categoria: GERENTE\n" RESET);
                break;
            case DIRECTOR:
                printf(FG_GREEN "Categoria: DIRECTOR\n" RESET);
                break;
            }

            printf(FG_GREEN "Fecha de ingreso: %d/%d/%d\n" RESET, personal.fechaIngreso.dia, personal.fechaIngreso.mes, personal.fechaIngreso.anio);

            switch (personal.sectorAsignado)
            {
            case VENTAS:
                printf(FG_GREEN "Sector asignado: VENTAS\n" RESET);
                break;
            case MARKETING:
                printf(FG_GREEN "Sector asignado: MARKETING\n" RESET);
                break;
            case RECURSOS_HUMANOS:
                printf(FG_GREEN "Sector asignado: RECURSOS HUMANOS\n" RESET);
                break;
            case FINANZAS:
                printf(FG_GREEN "Sector asignado: FINANZAS\n" RESET);
                break;
            case PRODUCCION:
                printf(FG_GREEN "Sector asignado: PRODUCCION\n" RESET);
                break;
            }

            switch (personal.tareas)
            {
            case PLANIFICACION:
                printf(FG_GREEN "Tareas: PLANIFICACION\n" RESET);
                break;
            case GESTION_PROYECTOS:
                printf(FG_GREEN "Tareas: GESTION DE PROYECTOS\n" RESET);
                break;
            case SOPORTE_TECNICO:
                printf(FG_GREEN "Tareas: SOPORTE TECNICO\n" RESET);
                break;
            case ANALISIS_DATOS:
                printf(FG_GREEN "Tareas: ANALISIS DE DATOS\n" RESET);
                break;
            case QA_TESTER:
                printf(FG_GREEN "Tareas: QA TESTER\n" RESET);
                break;
            }

            printf(FG_GREEN "Sueldo nominal: %.2f\n" RESET, personal.sueldoNominal);
            printf("\n");
            // Preguntar si se desea dar de baja al personal
            int darDeBaja;
            do
            {
                printf(FG_YELLOW BOLD "¿Desea dar de baja a este personal administrativo? (1: Si, 0: No): " RESET);
                scanf("%d", &darDeBaja);
                limpiarBuffer();

                if (darDeBaja == 1)
                {
                    // Guardar los datos eliminados en el archivo de eliminados
                    fwrite(&personal, sizeof(PersonalAdministrativo), 1, archivoEliminados);
                    puts(BOLD FG_GREEN "El personal administrativo ha sido dado de baja exitosamente." RESET);
                }
                else if (darDeBaja == 0)
                {
                    fwrite(&personal, sizeof(PersonalAdministrativo), 1, archivoTemp);
                    puts(FG_YELLOW "El personal administrativo no ha sido dado de baja." RESET);
                }
                else
                {
                    printf(FG_RED "Opcion invalida. Por favor, ingrese una opcion valida.\n" RESET);
                }
            } while (darDeBaja != 1 && darDeBaja != 0);
        }
        else
        {
            fwrite(&personal, sizeof(PersonalAdministrativo), 1, archivoTemp);
        }
    }

    fclose(archivo);
    fclose(archivoTemp);
    fclose(archivoEliminados);

    remove(ARCHIVO_DATOS);
    rename("temp.bin", ARCHIVO_DATOS);

    if (encontrado)
    {
        int seguirDandoDeBaja;
        do
        {
            printf(FG_CYAN BOLD "¿Desea seguir dando de baja personal administrativo? (1: Si, 0: No): " RESET);
            scanf("%d", &seguirDandoDeBaja);
            limpiarBuffer();

            if (seguirDandoDeBaja == 1)
            {
                BajaPersonalAdministrativo();
                return;
            }
            else if (seguirDandoDeBaja == 0)
            {
                return;
            }
            else
            {
                printf(FG_RED "Opcion invalida. Por favor, ingrese una opcion valida.\n" RESET);
            }
        } while (seguirDandoDeBaja != 1 && seguirDandoDeBaja != 0);
    }
    else
    {
        puts(FG_RED "No se encontro ningun registro de personal administrativo con ese Apellido y Nombre." RESET);
    }
}

//------------------------------------------------------------------------------------------//

void ConsultaPersonalAdministrativo()
{
    int opcion;
    int opcionValida = 0;
    printf(FG_YELLOW "Seleccione una opcion de consulta:\n" RESET);
    printf(FG_YELLOW "1. Apellido y Nombre\n" RESET);
    printf(FG_YELLOW "2. Domicilio\n" RESET);
    printf(FG_YELLOW "3. Localidad\n" RESET);
    printf(FG_YELLOW "4. Provincia\n" RESET);
    printf(FG_YELLOW "5. Puesto\n" RESET);
    printf(FG_YELLOW "6. Categoria\n" RESET);
    printf(FG_YELLOW "7. Fecha de ingreso\n" RESET);
    printf(FG_YELLOW "8. Sector asignado\n" RESET);
    printf(FG_YELLOW "9. Tareas\n" RESET);
    scanf("%d", &opcion);

    getchar(); // Consumir el caracter de nueva linea

    PersonalAdministrativo personal;
    FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
    if (archivo == NULL)
    {
        puts(FG_RED "Error al abrir el archivo." RESET);
        return;
    }

    int encontrado = 0;
    char busqueda[MAX_NOMBRE];
    int categoria;
    struct FechaIngreso fechaIngreso;

    switch (opcion)
    {
    case 1:
        do
        {
            printf(FG_GREEN "Ingrese el Apellido y Nombre del personal administrativo a buscar: " RESET);
            fgets(busqueda, sizeof(busqueda), stdin);
            limpiarBuffer();

            int encontrado = validarCampoTexto(busqueda, archivo);
            if (encontrado)
            {
                // Si la validacion fue exitosa y se encontro el dato, se muestra la informacion.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }
            else
            {
                // Si la validacion fallo o no se encontro el dato, se pregunta si desea continuar.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }

        } while (1); // Repetir el bucle do-while indefinidamente hasta que se elija salir.

        break;

    case 2:
        do
        {
            printf(FG_GREEN "Ingrese el Domicilio del personal administrativo a buscar: " RESET);
            fgets(busqueda, sizeof(busqueda), stdin);
            limpiarBuffer();

            int encontrado = validarCampoTexto(busqueda, archivo);
            if (encontrado)
            {
                // Si la validacion fue exitosa y se encontro el dato, se muestra la informacion.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }
            else
            {
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);
                if (opcionContinuar == 2)
                {
                    break;
                }
            }
        } while (1);
        break;
    case 3:
        do
        {
            printf(FG_GREEN "Ingrese la Localidad del personal administrativo a buscar: " RESET);
            fgets(busqueda, sizeof(busqueda), stdin);
            limpiarBuffer();

            int encontrado = validarCampoTexto(busqueda, archivo);
            if (encontrado)
            {
                // Si la validacion fue exitosa y se encontro el dato, se muestra la informacion.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }
            else
            {
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);
                if (opcionContinuar == 2)
                {
                    break;
                }
            }
        } while (1);
        break;
    case 4:

        do
        {
            printf(FG_GREEN "Ingrese la Provincia del personal administrativo a buscar: " RESET);
            fgets(busqueda, sizeof(busqueda), stdin);
            limpiarBuffer();

            int encontrado = validarCampoTexto(busqueda, archivo);
            if (encontrado)
            {
                // Si la validacion fue exitosa y se encontro el dato, se muestra la informacion.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }
            else
            {
                // Si la validacion fallo o no se encontro el dato, se pregunta si desea continuar.
                int opcionContinuar;
                do
                {
                    printf(FG_RED "Desea continuar ingresando datos? (1-Si / 2-No): " RESET);
                    char opcionContinuarStr[MAX_NOMBRE];
                    fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
                    opcionContinuar = atoi(opcionContinuarStr);
                } while (opcionContinuar != 1 && opcionContinuar != 2);

                if (opcionContinuar == 2)
                {
                    break; // Salir del bucle do-while y volver al menu principal.
                }
            }

        } while (1); // Repetir el bucle do-while indefinidamente hasta que se elija salir.

        break;
    case 5:
        do
        {
            printf(FG_GREEN "Seleccione el Puesto del personal administrativo a buscar:\n" RESET);
            printf(FG_GREEN "1. ADMINISTRATIVO\n" RESET);
            printf(FG_GREEN "2. CONTADOR\n" RESET);
            printf(FG_GREEN "3. ANALISTA\n" RESET);
            printf(FG_GREEN "4. PROGRAMADOR\n" RESET);
            printf(FG_GREEN "5. OTRO\n" RESET);
            printf(FG_GREEN "Ingrese una opcion: ");

            char opcionPuestoStr[MAX_NOMBRE];
            fgets(opcionPuestoStr, sizeof(opcionPuestoStr), stdin);
            int opcionPuesto = atoi(opcionPuestoStr);

            if (opcionPuesto >= 1 && opcionPuesto <= 5)
            {
                Puesto puesto = (Puesto)(opcionPuesto - 1);

                while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
                {
                    if (personal.puesto == puesto)
                    {
                        mostrarInformacionPersonal(&personal);
                        encontrado = 1;
                    }
                }
            }
            else
            {
                puts(FG_RED "Opcion de puesto ingresada no valida." RESET);
            }
        } while (1);
        break;
    case 6:
        do
        {
            printf(FG_GREEN "Seleccione la Categoria del personal administrativo a buscar:\n" RESET);
            printf(FG_GREEN "1. JUNIOR\n" RESET);
            printf(FG_GREEN "2. SEMISENIOR\n" RESET);
            printf(FG_GREEN "3. SENIOR\n" RESET);
            printf(FG_GREEN "4. GERENTE\n" RESET);
            printf(FG_GREEN "5. DIRECTOR\n" RESET);
            printf(FG_GREEN "Ingrese una opcion: ");

            char opcionCategoriaStr[MAX_NOMBRE];
            fgets(opcionCategoriaStr, sizeof(opcionCategoriaStr), stdin);
            int opcionCategoria = atoi(opcionCategoriaStr);

            if (opcionCategoria >= 1 && opcionCategoria <= 5)
            {
                Categoria categoria = (Categoria)(opcionCategoria - 1);

                while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
                {
                    if (personal.categoria == categoria)
                    {
                        mostrarInformacionPersonal(&personal);
                        encontrado = 1;
                    }
                }
            }
            else
            {
                puts(FG_RED "Opcion de categoria ingresada no valida." RESET);
            }
        } while (1);
        break;

    case 7:
        do
        {
            printf(FG_GREEN "Ingrese la Fecha de ingreso del personal administrativo a buscar (dd/mm/aaaa): " RESET);
            scanf("%d/%d/%d", &fechaIngreso.dia, &fechaIngreso.mes, &fechaIngreso.anio);
            limpiarBuffer();

            if (!validarFechaIngreso(fechaIngreso.dia, fechaIngreso.mes, fechaIngreso.anio))
            {
                printf(FG_RED "La fecha de ingreso ingresada es invalida o posterior a la fecha actual.\n" RESET);
                continue;
            }
            break;
        } while (1);

        while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
        {
            if (personal.fechaIngreso.dia == fechaIngreso.dia &&
                personal.fechaIngreso.mes == fechaIngreso.mes &&
                personal.fechaIngreso.anio == fechaIngreso.anio)
            {
                mostrarInformacionPersonal(&personal);
                encontrado = 1;
            }
        }
        break;
    case 8:
        do
        {
            printf(FG_GREEN "Seleccione el Sector Asignado del personal administrativo a buscar:\n" RESET);
            printf(FG_GREEN "1. VENTAS\n" RESET);
            printf(FG_GREEN "2. MARKETING\n" RESET);
            printf(FG_GREEN "3. RECURSOS HUMANOS\n" RESET);
            printf(FG_GREEN "4. FINANZAS\n" RESET);
            printf(FG_GREEN "5. PRODUCCION\n" RESET);
            printf(FG_GREEN "Ingrese una opcion: ");

            char opcionSectorStr[MAX_NOMBRE];
            fgets(opcionSectorStr, sizeof(opcionSectorStr), stdin);
            int opcionSector = atoi(opcionSectorStr);

            if (opcionSector >= 1 && opcionSector <= 5)
            {
                SectorAsignado sector = (SectorAsignado)(opcionSector - 1);

                while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
                {
                    if (personal.sectorAsignado == sector)
                    {
                        mostrarInformacionPersonal(&personal);
                        encontrado = 1;
                    }
                }

                break; // Salir del bucle do-while si la opcion es valida
            }
            else
            {
                puts(FG_RED "Opcion de sector asignado ingresada no valida." RESET);
            }
        } while (1); // Repetir el bucle do-while hasta que se ingrese una opcion valida
        break;
    case 9:
        do
        {
            printf(FG_GREEN "Seleccione las Tareas del personal administrativo a buscar:\n" RESET);
            printf(FG_GREEN "1. PLANIFICACION\n" RESET);
            printf(FG_GREEN "2. GESTION DE PROYECTOS\n" RESET);
            printf(FG_GREEN "3. SOPORTE TECNICO\n" RESET);
            printf(FG_GREEN "4. ANALISIS DE DATOS\n" RESET);
            printf(FG_GREEN "5. QA TESTER\n" RESET);
            printf(FG_GREEN "Ingrese una opcion: ");

            char opcionTareasStr[MAX_NOMBRE];
            fgets(opcionTareasStr, sizeof(opcionTareasStr), stdin);
            int opcionTareas = atoi(opcionTareasStr);

            if (opcionTareas >= 1 && opcionTareas <= 5)
            {
                Tareas tareas = (Tareas)(opcionTareas - 1);

                while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
                {
                    if (personal.tareas == tareas)
                    {
                        mostrarInformacionPersonal(&personal);
                        encontrado = 1;
                    }
                }

                break; // Salir del bucle do-while si la opcion es valida
            }
            else
            {
                puts(FG_RED "Opcion de tareas ingresada no valida." RESET);
            }
        } while (1); // Repetir el bucle do-while hasta que se ingrese una opcion valida
        break;

    default:
        puts(FG_RED "Opcion invalida. Por favor, seleccione una opcion valida." RESET);
        break;
    }

    fclose(archivo);

    if (!encontrado)
    {
        //puts(FG_YELLOW "No se encontro ningun registro de personal administrativo con los criterios de busqueda especificados." RESET);
    }
}

//------------------------------------------------------------------------------------------//

void mostrarInformacionPersonal(PersonalAdministrativo *personal)
{
    printf(FG_GREEN "Legajo: %d\n" RESET, personal->legajo);
    printf(FG_GREEN "Numero de Documento: %d\n" RESET, personal->numeroDocumento);
    printf(FG_GREEN "Apellido y Nombre: %s\n" RESET, personal->apellidoNombre);
    printf(FG_GREEN "Domicilio: %s\n" RESET, personal->domicilio);
    printf(FG_GREEN "Localidad: %s\n" RESET, personal->localidad);
    printf(FG_GREEN "Provincia: %s\n" RESET, personal->provincia);

    switch (personal->puesto)
    {
    case ADMINISTRATIVO:
        printf(FG_GREEN "Puesto: ADMINISTRATIVO\n" RESET);
        break;
    case CONTADOR:
        printf(FG_GREEN "Puesto: CONTADOR\n" RESET);
        break;
    case ANALISTA:
        printf(FG_GREEN "Puesto: ANALISTA\n" RESET);
        break;
    case PROGRAMADOR:
        printf(FG_GREEN "Puesto: PROGRAMADOR\n" RESET);
        break;
    case OTRO:
        printf(FG_GREEN "Puesto: OTRO\n" RESET);
        break;
    }

    switch (personal->categoria)
    {
    case JUNIOR:
        printf(FG_GREEN "Categoria: JUNIOR\n" RESET);
        break;
    case SEMISENIOR:
        printf(FG_GREEN "Categoria: SEMISENIOR\n" RESET);
        break;
    case SENIOR:
        printf(FG_GREEN "Categoria: SENIOR\n" RESET);
        break;
    case GERENTE:
        printf(FG_GREEN "Categoria: GERENTE\n" RESET);
        break;
    case DIRECTOR:
        printf(FG_GREEN "Categoria: DIRECTOR\n" RESET);
        break;
    }

    printf(FG_GREEN "Fecha de ingreso: %d/%d/%d\n" RESET, personal->fechaIngreso.dia, personal->fechaIngreso.mes, personal->fechaIngreso.anio);

    switch (personal->sectorAsignado)
    {
    case VENTAS:
        printf(FG_GREEN "Sector asignado: VENTAS\n" RESET);
        break;
    case MARKETING:
        printf(FG_GREEN "Sector asignado: MARKETING\n" RESET);
        break;
    case RECURSOS_HUMANOS:
        printf(FG_GREEN "Sector asignado: RECURSOS HUMANOS\n" RESET);
        break;
    case FINANZAS:
        printf(FG_GREEN "Sector asignado: FINANZAS\n" RESET);
        break;
    case PRODUCCION:
        printf(FG_GREEN "Sector asignado: PRODUCCION\n" RESET);
        break;
    }

    switch (personal->tareas)
    {
    case PLANIFICACION:
        printf(FG_GREEN "Tareas: PLANIFICACION\n" RESET);
        break;
    case GESTION_PROYECTOS:
        printf(FG_GREEN "Tareas: GESTION DE PROYECTOS\n" RESET);
        break;
    case SOPORTE_TECNICO:
        printf(FG_GREEN "Tareas: SOPORTE TECNICO\n" RESET);
        break;
    case ANALISIS_DATOS:
        printf(FG_GREEN "Tareas: ANALISIS DE DATOS\n" RESET);
        break;
    case QA_TESTER:
        printf(FG_GREEN "Tareas: QA TESTER\n" RESET);
        break;
    }

    printf(FG_GREEN "Sueldo nominal: %.2f\n" RESET, personal->sueldoNominal);
    printf("\n");
}

//------------------------------------------------------------------------------------------//

void ListadoGeneralPersonalAdministrativo()
{
    PersonalAdministrativo personal;
    FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
    if (archivo == NULL)
    {
        printf(FG_RED "Error al abrir el archivo.\n" RESET);
        return;
    }
    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        printf(FG_GREEN BOLD "Legajo: %d\n" RESET, personal.legajo);
        printf(FG_GREEN "Numero de Documento: %d\n" RESET, personal.numeroDocumento);
        printf(FG_GREEN "Apellido y Nombre: %s\n" RESET, personal.apellidoNombre);
        printf(FG_GREEN "Domicilio: %s\n" RESET, personal.domicilio);
        printf(FG_GREEN "Localidad: %s\n" RESET, personal.localidad);
        printf(FG_GREEN "Provincia: %s\n" RESET, personal.provincia);

        switch (personal.puesto)
        {
        case ADMINISTRATIVO:
            printf(FG_GREEN "Puesto: ADMINISTRATIVO\n" RESET);
            break;
        case CONTADOR:
            printf(FG_GREEN "Puesto: CONTADOR\n" RESET);
            break;
        case ANALISTA:
            printf(FG_GREEN "Puesto: ANALISTA\n" RESET);
            break;
        case PROGRAMADOR:
            printf(FG_GREEN "Puesto: PROGRAMADOR\n" RESET);
            break;
        case OTRO:
            printf(FG_GREEN "Puesto: OTRO\n" RESET);
            break;
        }

        switch (personal.categoria)
        {
        case JUNIOR:
            printf(FG_GREEN "Categoria: JUNIOR\n" RESET);
            break;
        case SEMISENIOR:
            printf(FG_GREEN "Categoria: SEMISENIOR\n" RESET);
            break;
        case SENIOR:
            printf(FG_GREEN "Categoria: SENIOR\n" RESET);
            break;
        case GERENTE:
            printf(FG_GREEN "Categoria: GERENTE\n" RESET);
            break;
        case DIRECTOR:
            printf(FG_GREEN "Categoria: DIRECTOR\n" RESET);
            break;
        }

        printf(FG_GREEN "Fecha de ingreso: %d/%d/%d\n" RESET, personal.fechaIngreso.dia, personal.fechaIngreso.mes, personal.fechaIngreso.anio);

        switch (personal.sectorAsignado)
        {
        case VENTAS:
            printf(FG_GREEN "Sector asignado: VENTAS\n" RESET);
            break;
        case MARKETING:
            printf(FG_GREEN "Sector asignado: MARKETING\n" RESET);
            break;
        case RECURSOS_HUMANOS:
            printf(FG_GREEN "Sector asignado: RECURSOS HUMANOS\n" RESET);
            break;
        case FINANZAS:
            printf(FG_GREEN "Sector asignado: FINANZAS\n" RESET);
            break;
        case PRODUCCION:
            printf(FG_GREEN "Sector asignado: PRODUCCION\n" RESET);
            break;
        }

        switch (personal.tareas)
        {
        case PLANIFICACION:
            printf(FG_GREEN "Tareas: PLANIFICACION\n" RESET);
            break;
        case GESTION_PROYECTOS:
            printf(FG_GREEN "Tareas: GESTION DE PROYECTOS\n" RESET);
            break;
        case SOPORTE_TECNICO:
            printf(FG_GREEN "Tareas: SOPORTE TECNICO\n" RESET);
            break;
        case ANALISIS_DATOS:
            printf(FG_GREEN "Tareas: ANALISIS DE DATOS\n" RESET);
            break;
        case QA_TESTER:
            printf(FG_GREEN "Tareas: QA TESTER\n" RESET);
            break;
        }

        printf(FG_GREEN "Sueldo nominal: %.2f\n" RESET, personal.sueldoNominal);
        printf("\n");
    }

    fclose(archivo);
}

//------------------------------------------------------------------------------------------//

void ListadoParticularPersonalAdministrativo()
{
    bool realizarNuevaBusqueda = true;
    do
    {
        char apellidoNombreBusqueda[MAX_NOMBRE];
        int valido = 0;

        do
        {
            printf(FG_CYAN BOLD "Ingrese el Apellido y Nombre del personal administrativo a buscar:\n" RESET);
            fgets(apellidoNombreBusqueda, sizeof(apellidoNombreBusqueda), stdin);
            apellidoNombreBusqueda[strcspn(apellidoNombreBusqueda, "\n")] = '\0'; // Eliminar el caracter de nueva linea

            if (strlen(apellidoNombreBusqueda) <= MAX_NOMBRE - 1)
            {
                valido = 1;
            }
            else
            {
                printf(FG_RED "El Apellido y Nombre ingresado es demasiado largo. Por favor, ingrese nuevamente.\n" RESET);
            }
        } while (!valido);

        PersonalAdministrativo personal;
        FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
        if (archivo == NULL)
        {
            printf(FG_RED "Error al abrir el archivo.\n" RESET);
            return;
        }

        int encontrado = 0;

        while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
        {
            if (strstr(personal.apellidoNombre, apellidoNombreBusqueda) != NULL)
            {
                printf(FG_GREEN BOLD "Legajo: %d\n" RESET, personal.legajo);
                printf(FG_GREEN "Numero de Documento: %d\n" RESET, personal.numeroDocumento);
                printf(FG_GREEN "Apellido y Nombre: %s\n" RESET, personal.apellidoNombre);
                printf(FG_GREEN "Domicilio: %s\n" RESET, personal.domicilio);
                printf(FG_GREEN "Localidad: %s\n" RESET, personal.localidad);
                printf(FG_GREEN "Provincia: %s\n" RESET, personal.provincia);

                switch (personal.puesto)
                {
                case ADMINISTRATIVO:
                    printf(FG_GREEN "Puesto: ADMINISTRATIVO\n" RESET);
                    break;
                case CONTADOR:
                    printf(FG_GREEN "Puesto: CONTADOR\n" RESET);
                    break;
                case ANALISTA:
                    printf(FG_GREEN "Puesto: ANALISTA\n" RESET);
                    break;
                case PROGRAMADOR:
                    printf(FG_GREEN "Puesto: PROGRAMADOR\n" RESET);
                    break;
                case OTRO:
                    printf(FG_GREEN "Puesto: OTRO\n" RESET);
                    break;
                }

                switch (personal.categoria)
                {
                case JUNIOR:
                    printf(FG_GREEN "Categoria: JUNIOR\n" RESET);
                    break;
                case SEMISENIOR:
                    printf(FG_GREEN "Categoria: SEMISENIOR\n" RESET);
                    break;
                case SENIOR:
                    printf(FG_GREEN "Categoria: SENIOR\n" RESET);
                    break;
                case GERENTE:
                    printf(FG_GREEN "Categoria: GERENTE\n" RESET);
                    break;
                case DIRECTOR:
                    printf(FG_GREEN "Categoria: DIRECTOR\n" RESET);
                    break;
                }

                printf(FG_GREEN "Fecha de ingreso: %d/%d/%d\n" RESET, personal.fechaIngreso.dia, personal.fechaIngreso.mes, personal.fechaIngreso.anio);

                switch (personal.sectorAsignado)
                {
                case VENTAS:
                    printf(FG_GREEN "Sector asignado: VENTAS\n" RESET);
                    break;
                case MARKETING:
                    printf(FG_GREEN "Sector asignado: MARKETING\n" RESET);
                    break;
                case RECURSOS_HUMANOS:
                    printf(FG_GREEN "Sector asignado: RECURSOS HUMANOS\n" RESET);
                    break;
                case FINANZAS:
                    printf(FG_GREEN "Sector asignado: FINANZAS\n" RESET);
                    break;
                case PRODUCCION:
                    printf(FG_GREEN "Sector asignado: PRODUCCION\n" RESET);
                    break;
                }

                switch (personal.tareas)
                {
                case GESTION_PROYECTOS:
                    printf(FG_GREEN "Tareas: GESTION DE PROYECTOS\n" RESET);
                    break;
                case SOPORTE_TECNICO:
                    printf(FG_GREEN "Tareas: SOPORTE TECNICO\n" RESET);
                    break;
                case ANALISIS_DATOS:
                    printf(FG_GREEN "Tareas: ANALISIS DE DATOS\n" RESET);
                    break;
                case QA_TESTER:
                    printf(FG_GREEN "Tareas: QA TESTER\n" RESET);
                    break;
                }

                printf(FG_GREEN "Sueldo nominal: %.2f\n" RESET, personal.sueldoNominal);
                encontrado = 1;
                break;
            }
        }
        fclose(archivo);

        if (!encontrado)
        {
            printf(FG_YELLOW "No se encontro ningun registro de personal administrativo con ese Apellido y Nombre.\n" RESET);
        }

        // Preguntar si desea realizar otra búsqueda
        char opcionContinuarStr[MAX_NOMBRE];
        int opcionContinuar;
        do
        {
            printf(FG_RED "Desea realizar otra busqueda? (1-Si / 2-No): " RESET);
            fgets(opcionContinuarStr, sizeof(opcionContinuarStr), stdin);
            opcionContinuar = atoi(opcionContinuarStr);
        } while (opcionContinuar != 1 && opcionContinuar != 2);

        if (opcionContinuar == 2)
        {
            realizarNuevaBusqueda = false;
        }

    } while (realizarNuevaBusqueda);
}

//------------------------------------------------------------------------------------------//

void ModificarPersonalAdministrativo()
{
    char apellidoNombreBusqueda[MAX_NOMBRE];
    int categoriaValida;
    do
    {
        puts(FG_MAGENTA BOLD "Ingrese el Apellido y Nombre del personal administrativo a modificar:" RESET);
        fgets(apellidoNombreBusqueda, sizeof(apellidoNombreBusqueda), stdin);
        apellidoNombreBusqueda[strcspn(apellidoNombreBusqueda, "\n")] = '\0'; // Eliminar el caracter de nueva línea

        if (strlen(apellidoNombreBusqueda) > MAX_NOMBRE - 1)
        {
            puts(FG_RED "El apellido y nombre ingresado excede la longitud permitida." RESET);
            continue;
        }
        break;
    } while (1);

    PersonalAdministrativo personal;
    FILE *archivo = fopen(ARCHIVO_DATOS, "r+b");
    if (archivo == NULL)
    {
        puts(FG_RED "Error al abrir el archivo." RESET);
        return;
    }

    int encontrado = 0;

    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        if (strstr(personal.apellidoNombre, apellidoNombreBusqueda) != NULL)
        {
            encontrado = 1;
            int opcion;
            do
            {
                puts(FG_MAGENTA BOLD "Seleccione la variable a modificar:" RESET);
                puts(FG_MAGENTA "1. Apellido y Nombre");
                puts("2. Domicilio");
                puts("3. Localidad");
                puts("4. Provincia");
                puts("5. Puesto");
                puts("6. Categoria");
                puts("7. Fecha de ingreso");
                puts("8. Sector asignado");
                puts("9. Tareas");
                puts("10. Sueldo nominal");
                puts("0. Salir" RESET);
                scanf("%d", &opcion);
                limpiarBuffer();

                switch (opcion)
                {
                case 1:
                    do
                    {
                        puts(FG_MAGENTA "Nuevo Apellido y Nombre:" RESET);
                        fgets(personal.apellidoNombre, sizeof(personal.apellidoNombre), stdin);
                        personal.apellidoNombre[strcspn(personal.apellidoNombre, "\n")] = '\0';

                        if (strlen(personal.apellidoNombre) > MAX_NOMBRE - 1)
                        {
                            puts(FG_RED "El apellido y nombre ingresado excede la longitud permitida." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 2:
                    do
                    {
                        puts(FG_MAGENTA "Nuevo Domicilio:" RESET);
                        fgets(personal.domicilio, sizeof(personal.domicilio), stdin);
                        personal.domicilio[strcspn(personal.domicilio, "\n")] = '\0';

                        if (strlen(personal.domicilio) > MAX_NOMBRE - 1)
                        {
                            puts(FG_RED "El domicilio ingresado excede la longitud permitida." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 3:
                    do
                    {
                        puts(FG_MAGENTA "Nueva Localidad:" RESET);
                        fgets(personal.localidad, sizeof(personal.localidad), stdin);
                        personal.localidad[strcspn(personal.localidad, "\n")] = '\0';

                        if (strlen(personal.localidad) > MAX_NOMBRE - 1)
                        {
                            puts(FG_RED "La localidad ingresada excede la longitud permitida." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 4:
                    do
                    {
                        puts(FG_MAGENTA "Nueva Provincia:" RESET);
                        fgets(personal.provincia, sizeof(personal.provincia), stdin);
                        personal.provincia[strcspn(personal.provincia, "\n")] = '\0';

                        if (strlen(personal.provincia) > MAX_NOMBRE - 1)
                        {
                            puts(FG_RED "La provincia ingresada excede la longitud permitida." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 5:
                    do
                    {
                        puts(FG_MAGENTA "Nuevo Puesto:");
                        puts("1. ADMINISTRATIVO");
                        puts("2. CONTADOR");
                        puts("3. ANALISTA");
                        puts("4. PROGRAMADOR");
                        puts("5. OTRO");
                        scanf("%d", &personal.puesto);
                        limpiarBuffer();

                        if (personal.puesto < ADMINISTRATIVO || personal.puesto > OTRO)
                        {
                            puts(FG_RED "El puesto ingresado es invalido. Por favor, ingrese un valor valido." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 6:
                    do
                    {
                        puts(FG_MAGENTA "Nueva Categoria:");
                        puts("1. JUNIOR");
                        puts("2. SEMISENIOR");
                        puts("3. SENIOR");
                        puts("4. GERENTE");
                        puts("5. DIRECTOR");
                        scanf("%d", &personal.categoria);
                        limpiarBuffer();

                        if (personal.categoria < JUNIOR || personal.categoria > DIRECTOR)
                        {
                            puts(FG_RED "La categoria ingresada es invalida. Por favor, ingrese un valor valido." RESET);
                        }
                        else
                        {
                            categoriaValida = 1;
                        }
                    } while (!categoriaValida);
                    break;
                case 7:
                    do
                    {
                        puts(FG_MAGENTA "Nueva Fecha de ingreso (dd/mm/aaaa):");
                        scanf("%d/%d/%d", &personal.fechaIngreso.dia, &personal.fechaIngreso.mes, &personal.fechaIngreso.anio);
                        limpiarBuffer();

                        if (!validarFechaIngreso(personal.fechaIngreso.dia, personal.fechaIngreso.mes, personal.fechaIngreso.anio))
                        {
                            puts(FG_RED "La fecha de ingreso ingresada es invalida o posterior a la fecha actual." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 8:
                    do
                    {
                        puts(FG_MAGENTA "Nuevo Sector asignado:");
                        puts("1. VENTAS");
                        puts("2. MARKETING");
                        puts("3. RECURSOS_HUMANOS");
                        puts("4. FINANZAS");
                        puts("5. PRODUCCION");
                        scanf("%d", &personal.sectorAsignado);
                        limpiarBuffer();

                        if (personal.sectorAsignado < VENTAS || personal.sectorAsignado > PRODUCCION)
                        {
                            puts(FG_RED "El sector asignado ingresado es invalido. Por favor, ingrese un valor valido." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 9:
                    do
                    {
                        puts(FG_MAGENTA "Nuevas Tareas:");
                        puts("1. PLANIFICACION");
                        puts("2. GESTION_PROYECTOS");
                        puts("3. SOPORTE_TECNICO");
                        puts("4. ANALISIS_DATOS");
                        puts("5. QA_TESTER");
                        scanf("%d", &personal.tareas);
                        limpiarBuffer();

                        if (personal.tareas < PLANIFICACION || personal.tareas > QA_TESTER)
                        {
                            puts(FG_RED "Las tareas ingresadas son invalidas. Por favor, ingrese un valor valido." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 10:
                    do
                    {
                        puts(FG_MAGENTA "Nuevo Sueldo nominal:");
                        scanf("%f", &personal.sueldoNominal);
                        limpiarBuffer();

                        if (!validarLongitudNumericaDecimal(personal.sueldoNominal, 10))
                        {
                            puts(FG_RED "El sueldo ingresado excede la longitud permitida." RESET);
                            continue;
                        }
                        break;
                    } while (1);
                    break;
                case 0:
                    break;
                default:
                    puts(FG_RED "Opcion no valida. Intente nuevamente." RESET);
                    break;
                }
            } while (opcion != 0);

            // Regresar el puntero del archivo para escribir los cambios
            fseek(archivo, ftell(archivo) - sizeof(PersonalAdministrativo), SEEK_SET);
            fwrite(&personal, sizeof(PersonalAdministrativo), 1, archivo);
            break; // Salir del bucle while
        }
    }

    fclose(archivo);

    if (encontrado)
    {
        puts(FG_GREEN BOLD "Personal administrativo modificado exitosamente." RESET);
    }
    else
    {
        puts(FG_YELLOW "No se encontro al personal administrativo solicitado." RESET);
    }
}

//------------------------------------------------------------------------------------------//

void OrdenamientoIngresoPersonalAdministrativo()
{
    // Implementar el ordenamiento de los registros del archivo segun el año de ingreso (de menor a mayor)
    PersonalAdministrativo registros[MAX_REGISTROS];
    int contador = 0;

    FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
    if (archivo == NULL)
    {
        puts(FG_RED "Error al abrir el archivo." RESET);
        return;
    }

    PersonalAdministrativo personal;
    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        registros[contador] = personal;
        contador++;
    }

    fclose(archivo);

    int opcion;
    do
    {
        puts(FG_CYAN BOLD "Seleccione una opcion:");
        puts("1. Ordenar por fecha de ingreso de menor a mayor.");
        puts("2. Ordenar por fecha de ingreso de mayor a menor." RESET);
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            // Ordenar el arreglo de registros por fecha de ingreso de menor a mayor usando el algoritmo de selección
            for (int i = 0; i < contador - 1; i++)
            {
                int minIndex = i;
                for (int j = i + 1; j < contador; j++)
                {
                    if (registros[j].fechaIngreso.anio < registros[minIndex].fechaIngreso.anio ||
                        (registros[j].fechaIngreso.anio == registros[minIndex].fechaIngreso.anio &&
                         registros[j].fechaIngreso.mes < registros[minIndex].fechaIngreso.mes) ||
                        (registros[j].fechaIngreso.anio == registros[minIndex].fechaIngreso.anio &&
                         registros[j].fechaIngreso.mes == registros[minIndex].fechaIngreso.mes &&
                         registros[j].fechaIngreso.dia < registros[minIndex].fechaIngreso.dia))
                    {
                        minIndex = j;
                    }
                }
                if (minIndex != i)
                {
                    PersonalAdministrativo temp = registros[i];
                    registros[i] = registros[minIndex];
                    registros[minIndex] = temp;
                }
            }
            break;
        case 2:
            // Ordenar el arreglo de registros por fecha de ingreso de mayor a menor usando el algoritmo de seleccion
            for (int i = 0; i < contador - 1; i++)
            {
                int maxIndex = i;
                for (int j = i + 1; j < contador; j++)
                {
                    if (registros[j].fechaIngreso.anio > registros[maxIndex].fechaIngreso.anio ||
                        (registros[j].fechaIngreso.anio == registros[maxIndex].fechaIngreso.anio &&
                         registros[j].fechaIngreso.mes > registros[maxIndex].fechaIngreso.mes) ||
                        (registros[j].fechaIngreso.anio == registros[maxIndex].fechaIngreso.anio &&
                         registros[j].fechaIngreso.mes == registros[maxIndex].fechaIngreso.mes &&
                         registros[j].fechaIngreso.dia > registros[maxIndex].fechaIngreso.dia))
                    {
                        maxIndex = j;
                    }
                }
                if (maxIndex != i)
                {
                    PersonalAdministrativo temp = registros[i];
                    registros[i] = registros[maxIndex];
                    registros[maxIndex] = temp;
                }
            }
            break;
        default:
            puts(FG_RED "Opcion invalida. Por favor, seleccione una opcion valida." RESET);
            break;
        }
    } while (opcion != 1 && opcion != 2);
    // Imprimir los nombres y fechas de ingreso del personal ordenados
    puts(FG_CYAN BOLD "Nombres y fechas de ingreso del personal administrativo ordenados por fecha de ingreso:");
    for (int i = 0; i < contador; i++)
    {
        printf("%s - Fecha de ingreso: %d/%d/%d\n", registros[i].apellidoNombre, registros[i].fechaIngreso.dia, registros[i].fechaIngreso.mes, registros[i].fechaIngreso.anio);
    }
    puts(RESET);
}

//------------------------------------------------------------------------------------------//

void OrdenarSueldos(PersonalAdministrativo registros[], int contador, int opcion)
{
    switch (opcion)
    {
    case 1:
        // Ordenar de menor a mayor
        for (int i = 0; i < contador - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < contador; j++)
            {
                if (registros[j].sueldoNominal < registros[minIndex].sueldoNominal)
                {
                    minIndex = j;
                }
            }
            if (minIndex != i)
            {
                PersonalAdministrativo temp = registros[i];
                registros[i] = registros[minIndex];
                registros[minIndex] = temp;
            }
        }
        // Mostrar la lista ordenada de menor a mayor
        puts(FG_RED BOLD "Lista de sueldos de menor a mayor:");
        for (int i = 0; i < contador; i++)
        {
            printf("Apellido y Nombre: %s\n", registros[i].apellidoNombre);
            printf("Sueldo: %.2f\n", registros[i].sueldoNominal);
            printf("\n");
        }
        puts(RESET);
        break;

    case 2:
        // Ordenar de mayor a menor
        for (int i = 0; i < contador - 1; i++)
        {
            int maxIndex = i;
            for (int j = i + 1; j < contador; j++)
            {
                if (registros[j].sueldoNominal > registros[maxIndex].sueldoNominal)
                {
                    maxIndex = j;
                }
            }
            if (maxIndex != i)
            {
                PersonalAdministrativo temp = registros[i];
                registros[i] = registros[maxIndex];
                registros[maxIndex] = temp;
            }
        }
        // Mostrar la lista ordenada de mayor a menor
        puts(FG_RED BOLD "Lista de sueldos de mayor a menor:");
        for (int i = 0; i < contador; i++)
        {
            printf("Apellido y Nombre: %s\n", registros[i].apellidoNombre);
            printf("Sueldo: %.2f\n", registros[i].sueldoNominal);
            printf("\n");
        }
        puts(RESET);
        break;

    default:
        puts(FG_RED "Opcion invalida. Por favor, seleccione una opcion valida." RESET);
        // Pedir una nueva opcion
        do
        {
            printf(FG_RED "Seleccione una opcion:\n");
            printf("1. Ordenar sueldos de menor a mayor.\n");
            printf("2. Ordenar sueldos de mayor a menor." RESET "\n");
            scanf("%d", &opcion);
            limpiarBuffer(); // Limpia el bufer de entrada
        } while (opcion < 1 || opcion > 2);
        // Llamar nuevamente a la funcion con la opcion vlida
        OrdenarSueldos(registros, contador, opcion);
        break;
    }
}

//------------------------------------------------------------------------------------------//

void MinimoMaximoPersonalAdministrativo()
{
    PersonalAdministrativo registros[MAX_REGISTROS];
    int contador = 0;

    FILE *archivo = fopen(ARCHIVO_DATOS, "rb");
    if (archivo == NULL)
    {
        puts(FG_RED "Error al abrir el archivo." RESET);
        return;
    }

    PersonalAdministrativo personal;
    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        registros[contador] = personal;
        contador++;
    }

    fclose(archivo);

    int opcion;
    puts(FG_RED "Seleccione una opcion:");
    puts("1. Ordenar sueldos de menor a mayor.");
    puts("2. Ordenar sueldos de mayor a menor." RESET);
    scanf("%d", &opcion);
    limpiarBuffer(); // Limpia el bufer de entrada

    OrdenarSueldos(registros, contador, opcion);
}

//------------------------------------------------------------------------------------------//

int validarCategoria(int categoria)
{
    return (categoria >= 1 && categoria <= 5);
}

//------------------------------------------------------------------------------------------//

void convertirMayusculas(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        cadena[i] = toupper(cadena[i]);
    }
}

int validarCampoTexto(const char *campo, FILE *archivo)
{
    if (strlen(campo) >= MAX_NOMBRE - 1)
    {
        printf(FG_RED "La longitud del campo excede el limite permitido. Por favor, ingrese nuevamente.\n" RESET);
        return 0; // La longitud del campo excede el limite permitido
    }

    // Convertir el texto ingresado en mayusculas para hacer una busqueda no sensible a mayusculas/minusculas
    char busqueda[MAX_NOMBRE];
    strcpy(busqueda, campo);
    convertirMayusculas(busqueda);

    // Realizar la busqueda en los registros del archivo
    PersonalAdministrativo personal;
    int encontrado = 0;
    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        // Convertir el texto del registro en mayusculas para hacer una comparacion no sensible a mayusculas/minusculas
        char textoRegistro[MAX_NOMBRE];
        strcpy(textoRegistro, personal.apellidoNombre);
        convertirMayusculas(textoRegistro);

        if (strcmp(textoRegistro, busqueda) == 0)
        {
            mostrarInformacionPersonal(&personal);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        // Si no se encuentra coincidencia, mostrar el mensaje
        //printf(FG_YELLOW "No se encontro ningun registro de personal administrativo con los criterios de busqueda especificados.\n" RESET);
        return 0;
    }

    return 1; // Coincide con un registro existente
}

//------------------------------------------------------------------------------------------//

int validarLongitudNumericaDecimal(float numero, int longitudMaxima)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", numero); // Convertir el numero a una cadena con 2 decimales
    return strlen(buffer) <= longitudMaxima;
}

bool validarLongitudNumerica(int numero, int max)
{
    int digitos = 0;
    while (numero != 0)
    {
        numero /= 10;
        digitos++;
    }
    return digitos <= max;
}

bool validarNumeroDocumento(int numeroDocumento, FILE *archivo)
{
    PersonalAdministrativo personal;
    while (fread(&personal, sizeof(PersonalAdministrativo), 1, archivo) == 1)
    {
        if (personal.numeroDocumento == numeroDocumento)
        {
            return false; // El número de documento ya existe en los registros
        }
    }
    return true; // El número de documento es válido
}

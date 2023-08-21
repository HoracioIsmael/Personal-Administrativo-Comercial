/*
    Identificacion del grupo; Error501
    Apellido y nombre de los integrantes:
    Farias Milagros, Fernandes Maciel Anahi, Correa Horacio, Estrada Guillermo, Condori Fernando.
    Fecha de realizacion: 14 de Junio de 2023.
    Otros datos identificatorios.
*/

#ifndef PERSONAL_H
#define PERSONAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUMERO 8
#define MAX_PERSONAL 50
#define MAX_NOMBRE 50
#define MAX_REGISTROS 50
#define ARCHIVO_DATOS "personal.bin"
#define ARCHIVO_ELIMINADOS "personalBaja.bin"

//------------------------------------------------------------------------------------------//

typedef enum
{
    ADMINISTRATIVO,
    CONTADOR,
    ANALISTA,
    PROGRAMADOR,
    OTRO
} Puesto;

typedef enum
{
    JUNIOR,
    SEMISENIOR,
    SENIOR,
    GERENTE,
    DIRECTOR
} Categoria;

typedef enum
{
    VENTAS,
    MARKETING,
    RECURSOS_HUMANOS,
    FINANZAS,
    PRODUCCION
} SectorAsignado;

typedef enum
{
    PLANIFICACION,
    GESTION_PROYECTOS,
    SOPORTE_TECNICO,
    ANALISIS_DATOS,
    QA_TESTER
} Tareas;

//------------------------------------------------------------------------------------------//

typedef struct
{
    int legajo;
    int numeroDocumento;
    char apellidoNombre[MAX_NOMBRE];
    char domicilio[MAX_NOMBRE];
    char localidad[MAX_NOMBRE];
    char provincia[MAX_NOMBRE];
    Puesto puesto;
    Categoria categoria;
    struct FechaIngreso
    {
        int dia;
        int mes;
        int anio;
    } fechaIngreso;
    SectorAsignado sectorAsignado;
    Tareas tareas;
    float sueldoNominal;
} PersonalAdministrativo;

//------------------------------------------------------------------------------------------//

void AltaPersonalAdministrativo();
int buscarLegajo(PersonalAdministrativo personal[], int totalPersonal, int legajo);
void BajaPersonalAdministrativo();
void mostrarInformacionPersonal(PersonalAdministrativo *personal);
void ConsultaPersonalAdministrativo();
void convertirMayusculas(char *cadena);
void limpiarBuffer();
void ListadoGeneralPersonalAdministrativo();
void ListadoParticularPersonalAdministrativo();
void ModificarPersonalAdministrativo();
void OrdenamientoIngresoPersonalAdministrativo();
void OrdenarSueldos(PersonalAdministrativo registros[], int contador, int opcion);
void MinimoMaximoPersonalAdministrativo();
int validarCategoria(int categoria);
int validarFechaIngreso(int dia, int mes, int anio);
//int validarLongitudTexto(const char *texto, int longitudMaxima);
int validarCampoTexto(const char* campo, FILE* archivo);
int validarLongitudNumericaDecimal(float numero, int longitudMaxima);
bool validarLongitudNumerica(int numero, int max);
bool validarNumeroDocumento(int numeroDocumento, FILE *archivo);


#endif // PERSONAL_H

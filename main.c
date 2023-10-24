#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
///#include "InicioSesion.h"

// Máximo número de empleados permitidos
#define MAX_EMPLEADOS 60

// Estructura de empleados de laboratorio
typedef struct
{
    int DNI;
    char ApellidoNombre[41];
    char Usuario[21];
    char Contrasena[21];
    char Perfil[21];
} EmpleadoLaboratorio;
// Estructura para el nodo de árbol binario
typedef struct NodoArbol {
    EmpleadoLaboratorio empleado;
    struct arbol *izquierda;
    struct arbol *derecha;
} NodoArbol;


// Prototipos de funciones
int mostrarMenu();
void mostrarContenidoArchivo(const char *nombreArchivo);
void crearArchivoEmpleados(const char *nombreArchivo);
int empleadoExiste(const EmpleadoLaboratorio *empleados, int numEmpleados, int dni);
void cargarEmpleadosDesdeArchivo(EmpleadoLaboratorio *empleados, int *numEmpleados, const char *nombreArchivo);
void cargarEmpleado(EmpleadoLaboratorio *empleados, int *numEmpleados);
EmpleadoLaboratorio* buscarEmpleadoPorDNI(const EmpleadoLaboratorio *empleados, int numEmpleados, int dni) ;
NodoArbol *construirArbolDesdeArchivo(const char *nombreArchivo);
NodoArbol *insertarEmpleado(NodoArbol *arbol, EmpleadoLaboratorio empleado) ;
NodoArbol *buscarEmpleadoPorDNIArbol(NodoArbol *arbol, int dniABuscar);
void mostrarEmpleadoEnOrdenDNI(NodoArbol *arbol,int dniABuscar);

int main()
{
  /*  ///LOGIN
    char use[30];
    char pass[5];
    char AdminCorrecto[30]=ADMIN;
    char ProCorrecto[30]=PROFESIONAL;
    char SecCorrecto[30]=SECRETARIO;
    ///PRINTS PARA SABER QUE CARGAR
    printfInstructivos();
    gets(user);
    ///validacion para ingresar los nombres correctos
    while (strcmp(user,AdminCorrecto)!=0 && strcmp(user, ProCorrecto)!=0 && strcmp(user, SecCorrecto)!=0)
    {
        sonidoError();
        barraPunteada();
        printf("\t Usuario invalido , vuelva a ingresarlo: \n") ;
        gets(user);
        barraPunteada();
    }
    sonidoExito();
///validacion para ingresar bien la contraseña
printf("\t Password: \n");
gets(pass);
barraPunteada();
int longitud=strlen(pass);
int contador=0;
while(longitud!=4 && contador <3)
{
    sonidoError();
    barraPunteada();
    longitud=srtlen(pass);
    contador++;

}
if (contador>=3)
{
    sonidoError();
    barraPunteado();
    printf("\tDemasiados intentos, acceso denegado\n");
    barraPunteada();
    return 1;
}
sonidoExito();
///si ingresa mas de 4 digitos muestra datos incorrectos
int rol;
rol= InicioSesion(user,pass);
///fin login
*/
    const char *nombreArchivo = "empleados.txt";
    EmpleadoLaboratorio empleados[MAX_EMPLEADOS];
    EmpleadoLaboratorio empleadosEliminados[MAX_EMPLEADOS];
    int numEmpleados = 0;
    int numEmpleadosEliminados = 0;
 NodoArbol *arbolEmpleados;
    int opcion;
    while (1)
    {
        opcion = mostrarMenu();

        switch (opcion)
        {
        case 1:

            mostrarContenidoArchivo(nombreArchivo);
            mostrarEmpleadosArreglo(empleados, numEmpleados);
            system("pause");
            break;

        case 2:
            cargarEmpleado(empleados, &numEmpleados);
            grabarEmpleadosEnArchivo(empleados, numEmpleados, nombreArchivo);
            mostrarEmpleadosArreglo(empleados, numEmpleados);
            system("pause");
            break;

        case 3:
            cargarEmpleadosDesdeArchivo(&empleados, &numEmpleados, nombreArchivo);
            int dniABuscar;
            printf("Ingrese el DNI del empleado a eliminar: ");
            scanf("%d", &dniABuscar);

            buscarYEliminarEmpleadoPorDNI(nombreArchivo, dniABuscar,&empleadosEliminados, &numEmpleadosEliminados);
            grabarEmpleadosEnArchivo(&empleados, numEmpleados,nombreArchivo);
            mostrarContenidoArchivo(nombreArchivo);
            mostrarEmpleadosEliminados(empleadosEliminados, numEmpleadosEliminados);
            system("pause");
            break;

        case 4:



            printf("Ingrese el DNI del empleado a buscar: ");
            scanf("%d", &dniABuscar);

            EmpleadoLaboratorio *empleadoEncontrado = buscarEmpleadoPorDNI(empleados, numEmpleados, dniABuscar);

            if (empleadoEncontrado != NULL)
            {
                printf("Empleado encontrado:\n");
                printf("DNI: %d\n", empleadoEncontrado->DNI);
                printf("Apellido y Nombre: %s\n", empleadoEncontrado->ApellidoNombre);
                printf("Usuario: %s\n", empleadoEncontrado->Usuario);
                printf("Contrasena: %s\n", empleadoEncontrado->Contrasena);
                printf("Perfil: %s\n", empleadoEncontrado->Perfil);
            }
            else
            {
                printf("Empleado no encontrado.\n");
            }
            modificarEmpleadoPorDNI(nombreArchivo,&empleados,  numEmpleados, &dniABuscar);

            system("pause");
            break;

        case 5:
            arbolEmpleados = construirArbolDesdeArchivo(nombreArchivo);

    if (arbolEmpleados != NULL) {
        printf("Empleados ordenados por apellido:\n");
        mostrarEmpleadosEnOrden(arbolEmpleados);
    } else {
        printf("El árbol está vacío. Asegúrate de que el archivo tenga datos.\n");
    }

            system("pause");
            break;

        case 6:
              if (arbolEmpleados != NULL) {

        printf("Ingrese el DNI del empleado a buscar: ");
        scanf("%d", &dniABuscar);

        mostrarEmpleadoEnOrdenDNI(arbolEmpleados, dniABuscar);
    } else {
        printf("El arbol esta vacio. Asegurate de que el archivo tenga datos.\n");
    }

            system("pause");
            break;

        case 7:
            printf("Saliendo del programa...\n");
            exit(0);

        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    }

    return 0;
}

// Función para mostrar el menú y obtener la opción seleccionada
int mostrarMenu()
{
    int opcion;
    printf("---------Menu Empleados laboratorio--------\n");
    printf("1. Mostrar Archivo Empleados del laboratorio\n");
    printf("2. Alta Empleado de laboratorio\n");
    printf("3. Baja Empleado de laboratorio\n");
    printf("4. Modificacion empleado de laboratorio\n");
    printf("5. Ver listado general de empleados por Apellido y Nombre\n");
    printf("6. Buscar empleado por DNI\n");
    printf("7. Salir del Sistema\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}




//Funcion para mostrar archivo "empleados.dat"

void mostrarContenidoArchivo(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    EmpleadoLaboratorio empleado;
    while (fread(&empleado, sizeof(EmpleadoLaboratorio), 1, archivo) == 1)
    {
        printf("------------------------------------------------\n");
        printf("---Empleados del Laboratorio---\n");
        printf("DNI: %d\n", empleado.DNI);
        printf("Apellido y Nombre: %s\n", empleado.ApellidoNombre);
        printf("Usuario: %s\n", empleado.Usuario);
        printf("Contrasena: %s\n", empleado.Contrasena);
        printf("Perfil: %s\n", empleado.Perfil);
        printf("------------------------------------------------\n");
    }

    fclose(archivo);
}
//Funcion para crear archivo
void crearArchivoEmpleados(const char *nombreArchivo)
{


    FILE *archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL)
    {
        printf("No se pudo crear el archivo %s.\n", nombreArchivo);
        return;
    }

    int numEmpleados;
    printf("Ingrese el numero de empleados a agregar: ");
    scanf("%d", &numEmpleados);

    EmpleadoLaboratorio *empleados = (EmpleadoLaboratorio *)malloc(numEmpleados * sizeof(EmpleadoLaboratorio));

    for (int i = 0; i < numEmpleados; i++)
    {

        printf("Empleado #%d:\n", i + 1);
        printf("DNI: ");
        scanf("%d", &empleados[i].DNI);
        printf("Apellido y Nombre: ");
        scanf(" %40[^\n]", empleados[i].ApellidoNombre);
        printf("Usuario: ");
        scanf(" %20s", empleados[i].Usuario);
        printf("Contrasena: ");
        scanf(" %20s", empleados[i].Contrasena);
        printf("Perfil: ");
        scanf(" %20s", empleados[i].Perfil);

    }

    // Escribir los empleados en el archivo
    fwrite(empleados, sizeof(EmpleadoLaboratorio), numEmpleados, archivo);

    free(empleados);
    fclose(archivo);
    printf("Archivo %s creado con exito.\n", nombreArchivo);
}
// Función para verificar si ya existe un empleado con el mismo DNI
int empleadoExiste(const EmpleadoLaboratorio *empleados, int numEmpleados, int dni)
{
    for (int i = 0; i < numEmpleados; i++)
    {
        if (empleados[i].DNI == dni)
        {
            return 1; // Empleado ya existe
        }
    }
    return 0; // Empleado no existe
}
// Función para cargar empleados desde el archivo al arreglo
void cargarEmpleadosDesdeArchivo(EmpleadoLaboratorio *empleados, int *numEmpleados, const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Error: No se pudo abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    while (!feof(archivo))
    {
        int dni;
        if (fscanf(archivo, "DNI: %d\n", &dni) == 1)
        {
            if (!empleadoExiste(empleados, *numEmpleados, dni))
            {
                empleados[*numEmpleados].DNI = dni;
                fscanf(archivo, "Apellido y Nombre: %40[^\n]\n", empleados[*numEmpleados].ApellidoNombre);
                fscanf(archivo, "Usuario: %20s\n", empleados[*numEmpleados].Usuario);
                fscanf(archivo, "Contrasena: %20s\n", empleados[*numEmpleados].Contrasena);
                fscanf(archivo, "Perfil: %20s\n", empleados[*numEmpleados].Perfil);
                (*numEmpleados)++;
            }
        }
    }

    fclose(archivo);
    printf("Empleados cargados desde el archivo con exito.\n");
}

// Función para cargar un nuevo empleado
void cargarEmpleado(EmpleadoLaboratorio *empleados, int *numEmpleados)
{
    int dni;
    printf("Ingrese el DNI del empleado: ");
    scanf("%d", &dni);

    if (empleadoExiste(empleados, *numEmpleados, dni))
    {
        printf("Error: Ya existe un empleado con el mismo DNI.\n");
        return;
    }

    empleados[*numEmpleados].DNI = dni;

    printf("Ingrese el Apellido y Nombre del empleado: ");
    scanf(" %[^\n]", empleados[*numEmpleados].ApellidoNombre);

    printf("Ingrese el Usuario: ");
    scanf(" %s", empleados[*numEmpleados].Usuario);

    printf("Ingrese la Contraseña: ");
    scanf(" %s", empleados[*numEmpleados].Contrasena);

    printf("Ingrese el Perfil (admin, secretaria, bioquimico): ");
    scanf(" %s", empleados[*numEmpleados].Perfil);

    (*numEmpleados)++;
    printf("Empleado cargado con éxito.\n");
}








// Función para grabar empleados en el archivo
void grabarEmpleadosEnArchivo(const EmpleadoLaboratorio *empleados, int numEmpleados, const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        printf("Error: No se pudo crear el archivo %s.\n", nombreArchivo);
        return;
    }

    for (int i = 0; i < numEmpleados; i++)
    {
        fprintf(archivo, "DNI: %d\n", empleados[i].DNI);
        fprintf(archivo, "Apellido y Nombre: %s\n", empleados[i].ApellidoNombre);
        fprintf(archivo, "Usuario: %s\n", empleados[i].Usuario);
        fprintf(archivo, "Contrasena: %s\n", empleados[i].Contrasena);
        fprintf(archivo, "Perfil: %s\n", empleados[i].Perfil);
    }

    fclose(archivo);
    printf("Empleados grabados en el archivo con exito.\n");
}
//Funcion para buscar y eliminar al empleado segun dni , el empleado eliminado va al arreglo de empleadoseliminados
void buscarYEliminarEmpleadoPorDNI(const char *nombreArchivo, int dniABuscar, EmpleadoLaboratorio *empleadosEliminados, int *numEmpleadosEliminados)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Error: No se pudo abrir el archivo %s.\n", nombreArchivo);
        return;
    }

    FILE *archivoTemp = fopen("temp.txt", "w");
    if (archivoTemp == NULL)
    {
        printf("Error: No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    int encontrado = 0;
    EmpleadoLaboratorio empleado;

    while (fscanf(archivo, "DNI: %d\n", &empleado.DNI) == 1)
    {
        if (empleado.DNI == dniABuscar)
        {
            // Copiar los datos del empleado encontrado en el arreglo de empleados eliminados
            empleadosEliminados[*numEmpleadosEliminados] = empleado;
            (*numEmpleadosEliminados)++;
            encontrado = 1;
        }
        else
        {
            // Escribir el empleado en el archivo temporal (siguiendo el mismo formato)
            fprintf(archivoTemp, "DNI: %d\n", empleado.DNI);
            fprintf(archivoTemp, "Apellido y Nombre: %s\n", empleado.ApellidoNombre);
            fprintf(archivoTemp, "Usuario: %s\n", empleado.Usuario);
            fprintf(archivoTemp, "Contrasena: %s\n", empleado.Contrasena);
            fprintf(archivoTemp, "Perfil: %s\n", empleado.Perfil);
        }
    }

    fclose(archivo);
    fclose(archivoTemp);

    if (encontrado)
    {
        // Eliminar el archivo original
        remove(nombreArchivo);

        // Renombrar el archivo temporal como el archivo original
        if (rename("temp.txt", nombreArchivo) != 0)
        {
            printf("Error: No se pudo renombrar el archivo temporal.\n");
        }
        else
        {
            printf("Empleado eliminado con éxito.\n");
        }
    }
    else
    {
        remove("temp.txt");
        printf("Empleado no encontrado en el archivo.\n");
    }
}
//Funcion para mostrar los empleados eliminados del arreglo de eliminados
void mostrarEmpleadosEliminados(const EmpleadoLaboratorio *empleadosEliminados, int numEmpleadosEliminados)
{
    if (numEmpleadosEliminados == 0)
    {
        printf("No se han eliminado empleados.\n");
        return;
    }

    printf("Empleados Eliminados:\n");

    for (int i = 0; i < numEmpleadosEliminados; i++)
    {
        printf("-----------------------------------------\n");
        printf("DNI: %d\n", empleadosEliminados[i].DNI);
        printf("Apellido y Nombre: %s\n", empleadosEliminados[i].ApellidoNombre);
        printf("Usuario: %s\n", empleadosEliminados[i].Usuario);
        printf("Contrasena: %s\n", empleadosEliminados[i].Contrasena);
        printf("Perfil: %s\n", empleadosEliminados[i].Perfil);
        printf("-----------------------------------------\n");
        printf("\n");
    }
}
void mostrarEmpleadosArreglo(const EmpleadoLaboratorio *empleados, int numEmpleados)
{

    printf("Arreglo de Empleados :\n");

    for (int i = 0; i < numEmpleados; i++)
    {
        printf("-----------------------------------------\n");
        printf("DNI: %d\n", empleados[i].DNI);
        printf("Apellido y Nombre: %s\n", empleados[i].ApellidoNombre);
        printf("Usuario: %s\n", empleados[i].Usuario);
        printf("Contrasena: %s\n", empleados[i].Contrasena);
        printf("Perfil: %s\n", empleados[i].Perfil);
        printf("-----------------------------------------\n");
        printf("\n");
    }
}
//Funcion para buscar un empleado por dni en el arreglo
EmpleadoLaboratorio* buscarEmpleadoPorDNI(const EmpleadoLaboratorio *empleados, int numEmpleados, int dni)
{
    for (int i = 0; i < numEmpleados; i++)
    {
        if (empleados[i].DNI == dni)
        {
            return &empleados[i];  // Devuelve un puntero al empleado encontrado
        }
    }
    return NULL;  // Si no se encuentra el empleado, devuelve NULL
}
//Funcion que modifica y graba en el archivo
void modificarEmpleadoPorDNI(const char *nombreArchivo, EmpleadoLaboratorio *empleados, int numEmpleados, int *dniABuscar)
{


    EmpleadoLaboratorio *empleadoEncontrado = buscarEmpleadoPorDNI(empleados, numEmpleados, dniABuscar);

    if (empleadoEncontrado != NULL)
    {
        int opcion;
        printf("Empleado encontrado. Seleccione el campo a modificar:\n");
        printf("1. DNI\n");
        printf("2. Apellido y Nombre\n");
        printf("3. Usuario\n");
        printf("4. Contrasena\n");
        printf("5. Perfil\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el nuevo DNI: ");
            scanf("%d", &empleadoEncontrado->DNI);
            break;
        case 2:
            printf("Ingrese el nuevo Apellido y Nombre: ");
            scanf(" %40[^\n]", empleadoEncontrado->ApellidoNombre);
            break;
        case 3:
            printf("Ingrese el nuevo Usuario: ");
            scanf(" %20s", empleadoEncontrado->Usuario);
            break;
        case 4:
            printf("Ingrese la nueva Contrasena: ");
            scanf(" %20s", empleadoEncontrado->Contrasena);
            break;
        case 5:
            printf("Ingrese el nuevo Perfil: ");
            scanf(" %20s", empleadoEncontrado->Perfil);
            break;
        default:
            printf("Opción no válida.\n");
            return;
        }

        // Actualizar el archivo
        FILE *archivo = fopen(nombreArchivo, "w");
        if (archivo == NULL)
        {
            printf("Error: No se pudo abrir el archivo %s.\n", nombreArchivo);
            return;
        }

        for (int i = 0; i < numEmpleados; i++)
        {
            fprintf(archivo, "DNI: %d\n", empleados[i].DNI);
            fprintf(archivo, "Apellido y Nombre: %s\n", empleados[i].ApellidoNombre);
            fprintf(archivo, "Usuario: %s\n", empleados[i].Usuario);
            fprintf(archivo, "Contrasena: %s\n", empleados[i].Contrasena);
            fprintf(archivo, "Perfil: %s\n", empleados[i].Perfil);
        }

        fclose(archivo);
        printf("Empleado modificado y cambios guardados en el archivo.\n");
    }
    else
    {
        printf("Empleado no encontrado.\n");
    }
}
// Función para realizar un recorrido inorden (ordenado por apellido)
void mostrarEmpleadosEnOrden(NodoArbol *arbol) {
    if (arbol != NULL) {
        mostrarEmpleadosEnOrden(arbol->izquierda);
        printf("Apellido y Nombre: %s\n", arbol->empleado.ApellidoNombre);
        printf("DNI: %d\n", arbol->empleado.DNI);
        printf("Usuario: %s\n", arbol->empleado.Usuario);
        printf("Contrasena: %s\n", arbol->empleado.Contrasena);
        printf("Perfil: %s\n", arbol->empleado.Perfil);
        printf("\n");
        mostrarEmpleadosEnOrden(arbol->derecha);
    }
}
//Funcion para construir un arbol desde el archivo
NodoArbol *construirArbolDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", nombreArchivo);
        return NULL;
    }

    NodoArbol *arbol = NULL;
    EmpleadoLaboratorio empleado;

    while (fscanf(archivo, "DNI: %d\n", &empleado.DNI) == 1) {
        fscanf(archivo, "Apellido y Nombre: %40[^\n]\n", empleado.ApellidoNombre);
         fscanf(archivo, "DNI: %40[^\n]\n", empleado.DNI);
          fscanf(archivo, "Usuario: %40[^\n]\n", empleado.Usuario);
           fscanf(archivo, "Contrasena: %40[^\n]\n", empleado.Contrasena);
            fscanf(archivo, "Perfil: %40[^\n]\n", empleado.Perfil);
        arbol = insertarEmpleado(arbol, empleado);
    }

    fclose(archivo);
    return arbol;
}
// Función para insertar un empleado en el árbol
NodoArbol *insertarEmpleado(NodoArbol *arbol, EmpleadoLaboratorio empleado) {
    if (arbol == NULL) {
        NodoArbol *nuevoNodo = (NodoArbol*)malloc(sizeof(NodoArbol));
        nuevoNodo->empleado = empleado;
        nuevoNodo->izquierda = NULL;
        nuevoNodo->derecha = NULL;
        return nuevoNodo;
    }

    if (strcmp(empleado.ApellidoNombre, arbol->empleado.ApellidoNombre) < 0) {
        arbol->izquierda = insertarEmpleado(arbol->izquierda, empleado);
    } else if (strcmp(empleado.ApellidoNombre, arbol->empleado.ApellidoNombre) > 0) {
        arbol->derecha = insertarEmpleado(arbol->derecha, empleado);
    }

    return arbol;
}
//Funcion para buscarEmpleadoPorDNIen el arbol
NodoArbol *buscarEmpleadoPorDNIArbol(NodoArbol *arbol, int dniABuscar) {
    if (arbol == NULL) {
        return NULL; // No se encontró el empleado con el DNI especificado
    }

    if (dniABuscar < arbol->empleado.DNI) {
        return buscarEmpleadoPorDNIArbol(arbol->izquierda, dniABuscar);
    } else if (dniABuscar > arbol->empleado.DNI) {
        return buscarEmpleadoPorDNIArbol(arbol->derecha, dniABuscar);
    }

    return arbol; // Se encontró el empleado
}

// Función para realizar un recorrido inorden (ordenado por dni)


void mostrarEmpleadoEnOrdenDNI(NodoArbol *arbol,int dniABuscar) {
    if (arbol == NULL) {
        printf("Empleado con DNI %d no encontrado.\n", dniABuscar);
        return;
    }

    if (dniABuscar < arbol->empleado.DNI) {
        mostrarEmpleadoEnOrdenDNI(arbol->izquierda, dniABuscar);
    } else if (dniABuscar > arbol->empleado.DNI) {
        mostrarEmpleadoEnOrdenDNI(arbol->derecha, dniABuscar);
    } else {
        // Se encontró el empleado
        printf("Empleado encontrado:\n");
        printf("DNI: %d\n", arbol->empleado.DNI);
        printf("Apellido y Nombre: %s\n", arbol->empleado.ApellidoNombre);
        printf("Usuario: %s\n", arbol->empleado.Usuario);
        printf("Contrasena: %s\n", arbol->empleado.Contrasena);
        printf("Perfil: %s\n", arbol->empleado.Perfil);

    }
}




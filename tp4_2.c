#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

typedef struct Nodo Nodo;

struct Nodo{
    Tarea T;
    Nodo *Siguiente;
};

Nodo *crearListaVacia();
Nodo *crearNodo(int id);
void insertarNodo(Nodo **Start, Nodo * nodo);
void mostrarTareas(Nodo **Start);
void eliminarNodo(Nodo **Start, int id);
Nodo * buscarTareaPorID(Nodo **Start, int idBuscado);
Nodo * buscarTareaPorPalabra(Nodo **Start, char *fraseBuscada);
Nodo * crearNodoRealizado(Nodo **Start, int id);

int main(){
    srand (time(NULL));
    //Cargar tareas
    int duracion, opcion, idBuscado, idRealizada; 
    int tareaID = 1000;
    char bandera;

    Nodo * listaTareasPendientes = crearListaVacia();
    Nodo * listaTareasRealizadas = crearListaVacia();

    do
    {
        printf("Ingrese la opcion que desee o el numero 0 para salir: \n");
        printf("1. Agregar una nueva tarea.\n");
        printf("2. Marcar una tarea como realizada.\n");
        printf("3. Mostrar la lista de tareas pendientes.\n");
        printf("4. Mostrar la lista de tareas realizadas.\n");
        printf("5. Buscar tarea por ID.\n");
        printf("6. Buscar tarea por palabra.\n");

        
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            do
            {
                insertarNodo(&listaTareasPendientes, crearNodo(tareaID));
                printf("Tarea agregada con exito\n");
                fflush(stdin);
                puts("Desea ingresar una nueva tarea? s/n: ");
                scanf("%c", &bandera);
                tareaID++;
            } while (bandera == 's');
            break;
        case 2:
            printf("Ingrese el ID de la tarea que desee marcar como realizada: ");
            scanf("%d", &idRealizada);
            insertarNodo(&listaTareasRealizadas,crearNodoRealizado(&listaTareasPendientes,idRealizada));
            break;
        case 3:
            printf("*** Lista de tareas pendientes ***\n");
            mostrarTareas(&listaTareasPendientes);
            break;
        case 4:
            printf("*** Lista de tareas realizadas ***\n");
            mostrarTareas(&listaTareasRealizadas);
            break;
        case 5:
            fflush(stdin);
            printf("Ingrese el ID buscado: ");
            scanf("%d", &idBuscado);

            Nodo *aux = buscarTareaPorID(&listaTareasPendientes, idBuscado);
            if (aux)
            {
                printf("--- Información de la tarea encontrada ---\n");
                printf("Descripción: %s\n",aux->T.Descripcion);
                printf("Duracion: %d\n", aux->T.Duracion);
            }else
            {
                printf("Tarea no encontrada\n");
            }
            free(aux);
            break;
        case 6:
            fflush(stdin);
            char *fraseBuscada;
            fraseBuscada = (char *) malloc(100* sizeof(char));
            printf("Ingrese la palabra buscada: ");
            gets(fraseBuscada);
            printf("--- En lista de tareas pendientes ---\n");
            Nodo *aux2 = buscarTareaPorPalabra(&listaTareasPendientes,fraseBuscada);
            if (aux2)
            {
                printf("Descripcion: %s\n", aux2->T.Descripcion);
                printf("Duracion: %d\n", aux2->T.Duracion);
                printf("ID: %d\n", aux2->T.TareaID);
            }else
            {
                printf("No se encontro en esta lista.\n");

            }
            
            
            printf("--- En lista de tareas realizadas ---\n");
            Nodo *aux3 = buscarTareaPorPalabra(&listaTareasRealizadas,fraseBuscada);
            if (aux3)
            {
                printf("Descripcion: %s\n", aux3->T.Descripcion);
                printf("Duracion: %d\n", aux3->T.Duracion);
                printf("ID: %d\n", aux3->T.TareaID);
            }else
            {
                printf("No se encontro en esta lista.\n");
            }
            
            

            break;
        default:
            printf("Ingrese una opcion valida\n");
            break;
        }
    } while (opcion != 0);
    
    
    return 0;
}

Nodo *crearListaVacia(){
    return NULL;
}

Nodo *crearNodo(int id){
    int duracion;
    char * Buff, *Descripcion;
    Buff = (char *)malloc(100*sizeof(char));

    Nodo *nuevaTarea = (Nodo *) malloc(sizeof(Nodo));
    fflush(stdin);
    puts("Ingrese descripcion de la tarea:");
    gets(Buff);
    Descripcion = (char *)malloc(strlen(Buff)*sizeof(char));
    strcpy(Descripcion, Buff);
    free(Buff);
    nuevaTarea->T.Descripcion = Descripcion;
    
    nuevaTarea->T.TareaID = id;

    fflush(stdin);
    puts("Ingrese la duracion (10 - 100): ");
    scanf("%d", &duracion);
    nuevaTarea->T.Duracion = duracion;

    nuevaTarea->Siguiente = NULL;
    return nuevaTarea;
    free(Descripcion);
}

void insertarNodo(Nodo **Start, Nodo * nodo){
    nodo->Siguiente = * Start;
    *Start = nodo;
}

void mostrarTareas(Nodo **Start){
    Nodo *aux = *Start;

    while (aux != NULL)
    {
        printf("\n");
        printf("Tarea ID: %d\n", aux->T.TareaID);
        printf("Descripcion: %s\n", aux->T.Descripcion);
        printf("Duración: %d\n", aux->T.Duracion);
        printf("-------\n");
        aux = aux->Siguiente;
    }
}

void eliminarNodo(Nodo **Start, int id){
    Nodo **aux = Start;
    while (*aux != NULL && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }
    
    if (*aux)
    {
        Nodo *temporal = *aux; 
        *aux = (*aux)->Siguiente;
        free(temporal);
    }
}

Nodo * buscarTareaPorID(Nodo **Start, int idBuscado){
    Nodo *aux = *Start;
    while (aux && aux->T.TareaID != idBuscado)
    {
        aux = aux->Siguiente;
    }
    return aux;
}

Nodo * buscarTareaPorPalabra(Nodo **Start, char *fraseBuscada){
    Nodo *aux = *Start;
    while (aux != NULL && strcmp(fraseBuscada,aux->T.Descripcion) != 0)
    {
        aux = aux->Siguiente;
    }
    return aux;
}

Nodo * crearNodoRealizado(Nodo **Start, int id){
    Nodo * aux = buscarTareaPorID(Start,id);
    Nodo * nodoRealizado = (Nodo *) malloc( sizeof(Nodo));
    if (aux == NULL)
    {
        printf("No se encontro la tarea solicitada\n");
        return NULL;
    }

    nodoRealizado->T.Duracion = aux->T.Duracion;
    nodoRealizado->T.TareaID = aux->T.TareaID;
    nodoRealizado->T.Descripcion = (char *)malloc((strlen(aux->T.Descripcion) + 1 )*sizeof(char));
    strcpy(nodoRealizado->T.Descripcion,aux->T.Descripcion);
    eliminarNodo(Start,id);
    return nodoRealizado;
}
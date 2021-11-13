#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Util.h"

int ingresarString(char *destino, char *mensaje, int min, int max)
{
    int todoOk = -1;
    char* auxString = (char*) malloc(sizeof(char) * 1000);

    if(destino != NULL && mensaje != NULL && auxString != NULL)
    {
        printf("%s: ", mensaje);
        fflush(stdin);
        gets(auxString);
        while(strlen(auxString) < min || strlen(auxString) > max)
        {
            printf("Error. %s (minimo %d y maximo %d caracteres): ", mensaje, min, max);
            fflush(stdin);
            gets(auxString);
        }

        strcpy(destino, auxString);
        todoOk = 0;
    }
    free(auxString);

    return todoOk;
}

int validarLetras(char str[])
{
    int todoOk = 0;
    int* i = (int*) malloc(sizeof(int));

    if(i != NULL)
    {
        while(str[*i] != '\0')
        {
            if((str[*i] != ' ') && (str[*i] < 'a' || str[*i] > 'z') && (str[*i] < 'A' || str[*i] > 'Z'))
            {
                todoOk = -1;
                break;
            }
            (*i)++;
        }
        free(i);
    }
    
    return todoOk;
}

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int todoOk = -1;
    int* intAux = (int*) malloc(sizeof(int));

    if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && intAux != NULL)
    do
    {

        printf("%s",mensaje);
        scanf("%d", intAux);
        if(*intAux >= minimo && *intAux <= maximo)
        {
            *pResultado = *intAux;
            todoOk = 0;
            break;
        }
        printf("%s", mensajeError);

        reintentos--;
    }
    while(reintentos > 0);
    free(intAux);

    return todoOk;
}

void pausar(char* mensaje)
{
    if(mensaje != NULL)
    {
        printf("%s, ", mensaje);
    }
    printf("presione enter para continuar.\n");
    fflush(stdin);
    getchar();
}

int preguntar(char* mensaje)
{
    char input = '\0';
    int* intentos = (int*) malloc(sizeof(int));

    if(mensaje != NULL && intentos != NULL)
    {
        *intentos = 7;

        printf("%s s/n: ", mensaje);
        fflush(stdin);
        input = getchar();
        input = tolower(input);
        while (input != 'n' && input != 's' && intentos)
        {
            printf("%s s/n: ", mensaje);
            fflush(stdin);
            input = getchar();
            input = tolower(input);
            (*intentos)--;
        }
    }
    free(intentos);

    return input == 's';
}

int cancelarOperacion(char* mensaje)
{
    char input = '\0';
    int* intentos = (int*) malloc(sizeof(int));

    if(mensaje != NULL && intentos != NULL)
    {
        *intentos = 7;

        printf("%s, desea cancelar la operacion? s/n: ", mensaje);
        fflush(stdin);
        input = getchar();
        input = tolower(input);
        while (input != 'n' && input != 's' && intentos)
        {
            printf("Desea cancelar la operacion? s/n: ");
            fflush(stdin);
            input = getchar();
            input = tolower(input);
            (*intentos)--;
        }
    }
    free(intentos);

    return input == 's';
}

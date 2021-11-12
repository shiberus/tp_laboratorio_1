#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "Util.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
	setbuf(stdout, NULL);

    int option, fail, nextId;
    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
        printf("*** Menu de Opciones ***\n\n");
        printf("1- Cargar los datos de los empleados desde el archivo data.csv (modo texto)\n");
        printf("2- Cargar los datos de los empleados desde el archivo data.csv (modo binario)\n");
        printf("3- Alta de empleado\n");
        printf("4- Modificar datos de empleado\n");
        printf("5- Baja de empleado\n");
        printf("6- Listar empleados\n");
        printf("7- Ordenar empleados\n");
        printf("8- Guardar los datos de los empleados en el archivo data.csv (modo texto)\n");
        printf("9- Guardar los datos de los empleados en el archivo data.csv (modo binario)\n");
        printf("10- Finalizar programa\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
            	if(ll_isEmpty(listaEmpleados))
            	{
            		fail = controller_loadFromText("data.csv",listaEmpleados);

            		if(fail)
            		{
            			pausar("Oh oh, hubo un error");
            		}
            		else
            		{
            			pausar("Los datos se cargaron exitosamente");
            		}
            	}
            	else
            	{
            		pausar("Ya se cargaron los empleados");
            	}
                break;

            case 2:
            	if(ll_isEmpty(listaEmpleados))
            	{
            		fail = controller_loadFromBinary("data.csv",listaEmpleados);

            		if(fail)
            		{
            			pausar("Oh oh, hubo un error");
            		}
            		else
            		{
            			pausar("Los datos se cargaron exitosamente");
            		}
            	}
            	else
            	{
            		pausar("Ya se cargaron los empleados");
            	}
                break;

            case 3:
            	if(!ll_isEmpty(listaEmpleados))
				{
					nextId = controller_getMaxId(listaEmpleados) + 1;

					fail = controller_addEmployee(listaEmpleados, nextId);

            		if(fail)
            		{
            			pausar("Oh oh, hubo un error");
            		}
            		else
            		{
            			pausar("Alta exitosa");
            		}
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 4:
            	if(!ll_isEmpty(listaEmpleados))
				{
            		fail = controller_editEmployee(listaEmpleados);

            		if(fail)
            		{
            			pausar("Parece que hubo un error");
            		}
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 5:
            	if(!ll_isEmpty(listaEmpleados))
				{
            		controller_removeEmployee(listaEmpleados);
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 6:
            	if(!ll_isEmpty(listaEmpleados))
				{
					controller_ListEmployee(listaEmpleados);
					pausar(NULL);
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 7:
            	if(!ll_isEmpty(listaEmpleados))
				{
					// ordenar empleados
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 8:
            	if(!ll_isEmpty(listaEmpleados))
				{
            		fail = controller_saveAsText("data.csv",listaEmpleados);

            		if(fail)
            		{
            			pausar("Oh oh, hubo un error");
            		}
            		else
            		{
            			pausar("Los datos se guardaron exitosamente");
            		}
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 9:
            	if(!ll_isEmpty(listaEmpleados))
				{
            		fail = controller_saveAsBinary("data.csv",listaEmpleados);

            		if(fail)
            		{
            			pausar("Oh oh, hubo un error");
            		}
            		else
            		{
            			pausar("Los datos se guardaron exitosamente");
            		}
				}
				else
				{
					pausar("Cargue la lista de empleados antes de empezar a operar");
				}
                break;

            case 10:
            	printf("Apruebeme profe.");
                break;

            default:
                pausar("Opcion invalida");
                break;
        }

    }
    while(option != 10);

    return 0;
}


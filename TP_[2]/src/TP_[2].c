/*
 ============================================================================
 Name        : TP_[2].c
 Author      : Santiago Lopez Cane
 Version     :
 Copyright   : Your copyright notice
 Description : Segundo trabajo practico
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ArrayEmployees.h"
#define TAM 1000

int main(void) {
	setbuf(stdout, NULL);
	int nextId = 20000;
	int cEmpleados = 0;
	int seguir = 1;
	int id, i, cancelar;
	char input;
	Employee e;
	Employee list[TAM];
	initEmployees(list, TAM);

	do
	{
		switch (menu())
		{
		case 1:
			if(findEmpty(list, TAM) >= 0 && newEmployee(&e) == 0)
			{
				e.id = nextId;
				if(addEmployee(list, TAM, e.id, e.name, e.lastName, e.salary, e.sector) == 0)
				{
					nextId++;
					cEmpleados++;
				}
				else
				{
					printf("Error en alta de empleado, presione enter para continuar\n");
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				printf("Error en alta de empleado, presione enter para continuar\n");
				fflush(stdin);
				getchar();
			}
			break;
		case 2:
			if(!cEmpleados)
			{
				printf("No hay empleados cargados, presione enter para continuar.\n");
				fflush(stdin);
				getchar();
			}
			else
			{
				printf("                  Modificar empleado                     \n");
				printf("-------------------------------------------------------\n\n");
				printEmployees(list, TAM);
				printf("Ingrese id del empleado\n");
				scanf("%d", &id);
				i = findEmployeeById(list, TAM, id);
				cancelar = 0;
				while (i == -1 && !cancelar)
				{
					printf("No se encontro al empleado, desea cancelar la operacion? s/n\n");
					fflush(stdin);
					input = getchar();
					input = tolower(input);
					while (input != 'n' && input != 's')
					{
						printf("Desea cancelar la operacion? s/n\n");
						fflush(stdin);
						input = getchar();
						input = tolower(input);
					}

					if(input == 's')
					{
						cancelar = 1;
					}
					else
					{
						printEmployees(list, TAM);
						printf("ingrese id del empleado\n");
						scanf("%d", &id);
						i = findEmployeeById(list, TAM, id);
					}

				}

				if(!cancelar)
				{
					modifyEmployee(list, TAM, i);
				}
			}
			break;
		case 3:
			if(!cEmpleados)
			{
				printf("No hay empleados cargados, presione enter para continuar.\n");
				fflush(stdin);
				getchar();
			}
			else
			{
				if(removeEmployee(list, TAM) == 0)
				{
					cEmpleados--;
				}
			}
			break;
		case 4:
			if(!cEmpleados)
			{
				printf("No hay empleados cargados, presione enter para continuar.\n");
				fflush(stdin);
				getchar();
			}
			else
			{
				informes(list, TAM);
			}
			break;
		case 5:
			seguir = 0;
			break;
		
		default:
			printf("Opcion invalida, presione enter para continuar\n");
			fflush(stdin);
			getchar();
			break;
		}
	} while (seguir);
	
	return EXIT_SUCCESS;
}

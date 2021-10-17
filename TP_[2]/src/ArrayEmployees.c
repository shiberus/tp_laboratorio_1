/*
 * ArrayEmployees.c
 *
 *  Created on: 16 oct. 2021
 *      Author: Dell
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ArrayEmployees.h"


int initEmployees(Employee* list, int len)
{
	int todoOk = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		todoOk = 0;
	}
	return todoOk;
}

int menu()
{
	int opcion = 0;
	printf("  Sistema de ABM para Empleados \n");
	printf("1- Cargar Empleado\n");
	printf("2- Modificar Empleado\n");
	printf("3- Baja Empleado\n");
	printf("4- Informes\n");
	printf("5- Salir\n");
	printf("Ingrese opcion:\n");
	fflush(stdin);
	scanf("%d", &opcion);
	return opcion;
}

int newEmployee(Employee* newEmployee)
{
	int todoOk = -1;
	char auxString[1000];
	int auxNumber;
	float auxFloat;

	if(newEmployee != NULL)
	{
		printf("                  Alta de empleado                     \n");
		printf("-------------------------------------------------------\n\n");
		printf("Ingrese nombre\n");
		fflush(stdin);
		gets(auxString);
		while (strlen(auxString) < 2 && strlen(auxString) > 15)
		{
			printf("Ingrese nombre (min 2 caracteres - max 15 caracteres)\n");
			fflush(stdin);
			gets(auxString);
		}
		strcpy(newEmployee->name, auxString);

		printf("Ingrese apellido\n");
		fflush(stdin);
		gets(auxString);
		while (strlen(auxString) < 2 || strlen(auxString) > 15)
		{
			printf("Ingrese apellido (min 2 caracteres - max 15 caracteres)\n");
			fflush(stdin);
			gets(auxString);
		}
		strcpy(newEmployee->lastName, auxString);

		printf("Ingrese salario\n");
		scanf("%f", &auxFloat);
		while (auxFloat < 1000 || auxFloat > 1000000)
		{
			printf("Ingrese salario (min 1.000 - max 1.000.000)\n");
			scanf("%f", &auxFloat);
		}
		newEmployee->salary = auxFloat;

		printf("Ingrese sector\n");
		scanf("%d", &auxNumber);
		while (auxNumber <= 0)
		{
			printf("Ingrese sector (numero positivo)\n");
			scanf("%d", &auxNumber);
		}
		newEmployee->sector = auxNumber;

		newEmployee->isEmpty = 0;
		todoOk = 0;
	}

	return todoOk;
}

int addEmployee(Employee* list, int len, int id, char name[],char
lastName[],float salary,int sector)
{
	int todoOk = -1;
	int i;

	if (list != NULL && len > 0 && name != NULL && lastName != NULL)
	{
		i = findEmpty(list,len);

		if(i >= 0)
		{
			list[i].id = id;
			strcpy(list[i].name, name);
			strcpy(list[i].lastName, lastName);
			list[i].salary = salary;
			list[i].sector = sector;
			list[i].isEmpty = 0;

			todoOk = 0;
			printf("Alta exitosa\n\n");
			printf("     Id     Nombre     	Apellido     Salario   	Sector \n");
			printf("-------------------------------------------------------\n");
			printEmployee(list[i]);
		}
		else
		{
			printf("No se hallo un espacio libre para agragar al empleado\n");
		}
	}
	

	return todoOk;
}

int findEmployeeById(Employee* list, int len,int id)
{
	int res = -1;

	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++) 
		{
			if (list[i].id == id && !list[i].isEmpty) 
			{
				res = i;
				break;
			}
		}
	}
	
	return res;
}

int removeEmployee(Employee* list, int len)
{
	int todoOk = -1;
	int cancelar = 0;
	int i, id;
	char input;

	if (list != NULL && len > 0)
	{
		printf("ingrese id del empleado\n");
		scanf("%d", &id);
		i = findEmployeeById(list, len, id);
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
				printf("ingrese id del empleado\n");
				scanf("%d", &id);
				i = findEmployeeById(list, len, id);
			}
			
		}

		printf(" Id       Nombre     	Apellido     Salario   	Sector \n");
		printf("-------------------------------------------------------\n");
		printEmployee(list[i]);
		printf("-------------------------------------------------------\n");

		do
		{
			printf("Confirmar operacion? s/n\n");
			fflush(stdin);
			input = getchar();
			input = tolower(input);

		} while (input != 'n' && input != 's');

		if (input == 's')
		{
			list[i].isEmpty = 1;
			printf("Operacion exitosa, presione enter para continuar\n");
			getchar();
		}
		else
		{
			printf("Operacion cancelada\n");
		}

		todoOk = 0;
	}
	
	
	return todoOk;
}

int sortEmployees(Employee list[], int len, int order) {
	int todoOk = -1;
	Employee auxEmployee;
	if (list != NULL && len > 0 && order >= 0 && order <= 1) {
		todoOk = 0;
		switch (order) {
		case 1:
			for (int i = 0; i < len - 1; i++) {
				for (int j = i + 1; j < len; j++) {
					if (strcmp(list[i].lastName, list[j].lastName) > 0 
					|| (strcmp(list[i].lastName, list[j].lastName) == 0
						&& list[i].sector > list[j].sector)) 
					{
						auxEmployee = list[j];
						list[j] = list[i];
						list[i] = auxEmployee;
					}
				}
			}
			break;
		case 0:
			for (int i = 0; i < len - 1; i++) {
				for (int j = i + 1; j < len; j++) {
					if (strcmp(list[i].lastName, list[j].lastName) < 0 
					|| (strcmp(list[i].lastName, list[j].lastName) == 0
						&& list[i].sector < list[j].sector)) 
					{
						auxEmployee = list[j];
						list[j] = list[i];
						list[i] = auxEmployee;
					}
				}
			}
			break;
		}
	}
	return todoOk;
}

int printEmployees(Employee* list, int len)
{
	int todoOk = -1;

	if (list != NULL && len > 0)
	{
		printf(" Id       Nombre     	Apellido     Salario   	Sector \n");
		printf("-------------------------------------------------------\n");
		for (int i = 0; i < len; i++)
		{
			if(!list[i].isEmpty)
			{
				printEmployee(list[i]);
			}
		}
		
		todoOk = 0;
	}

	return todoOk;
}

int printEmployee(Employee e)
{
	int todoOk = -1;
	printf("  %4d %10s    %10s      $%5.2f     %4d \n",e.id,e.name,e.lastName,e.salary,e.sector);
	todoOk = 0;
	return todoOk;
}

int findEmpty(Employee* list, int len)
{
	int res = -1;
	for (int i = 0; i < len; i++) {
		if (list[i].isEmpty) {
			res = i;
			break;
		}
	}
	return res;
}

int modifyEmployee(Employee* list, int len, int i)
{
	int todoOk = -1;
	int opcion = 0;
	int continuar = 1;
	char auxString[1000];
	float auxFloat;
	int auxNumber;

	while (continuar)
	{
		printf(" Id       Nombre     	Apellido     Salario   	Sector \n");
		printf("-------------------------------------------------------\n");
		printEmployee(list[i]);
		printf("-------------------------------------------------------\n");
		printf("1- Modificar nombre\n");
		printf("2- Modificar apellido\n");
		printf("3- Modificar salario\n");
		printf("4- Modificar sector\n");
		printf("5- Salir\n");
		printf("Ingrese opcion:\n");
		scanf("%d", &opcion);

		switch (opcion)
		{
		case 1:
			printf("Ingrese nombre\n");
			fflush(stdin);
			gets(auxString);
			while (strlen(auxString) < 2 && strlen(auxString) > 15)
			{
				printf("Ingrese nombre (min 2 caracteres - max 15 caracteres)\n");
				fflush(stdin);
				gets(auxString);
			}
			strcpy(list[i].name, auxString);
			break;
		case 2:
			printf("Ingrese apellido\n");
			fflush(stdin);
			gets(auxString);
			while (strlen(auxString) < 2 && strlen(auxString) > 15)
			{
				printf("Ingrese apellido (min 2 caracteres - max 15 caracteres)");
				fflush(stdin);
				gets(auxString);
			}
			strcpy(list[i].lastName, auxString);
			break;
		case 3:
			printf("Ingrese salario\n");
			scanf("%f", &auxFloat);
			while (auxFloat < 1000 || auxFloat > 1000000)
			{
				printf("Ingrese salario (min 1.000 - max 1.000.000)\n");
				scanf("%f", &auxFloat);
			}
			list[i].salary = auxFloat;
			break;
		case 4:
			printf("Ingrese sector\n");
			scanf("%d", &auxNumber);
			while (auxNumber <= 0)
			{
				printf("Ingrese sector (numero positivo)\n");
				scanf("%d", &auxNumber);
			}
			list[i].sector = auxNumber;
			break;
		case 5:
			continuar = 0;
			todoOk = 0;
			break;
	
		default:
			printf("Ingrese opcion valida\n");
			break;
		}
	}

	return todoOk;

}

int informes(Employee* list, int len)
{
	int todoOk = -1;
	int opcion;
	int continuar = 1;
	int cEmpleadosArribaDelPromedio = 0;
	int cEmpleados = 0;
	float totalSalarios = 0; 
	float promedioSalarios;

	while (continuar)
	{
		printf("       Informes de Empleados       \n");
		printf("1- Listado ordenado de empleados\n");
		printf("2- Informe de salarios\n");
		printf("3- salir\n");
		printf("Ingrese opcion:\n");
		scanf("%d", &opcion);

		switch (opcion)
		{
		case 1:
			sortEmployees(list, len, 1);
			printEmployees(list, len);
			printf("Presione enter para continuar\n");
			getchar();
			break;
		case 2:
			for (int i = 0; i < len; i++)
			{
				if(!list[i].isEmpty)
				{
					cEmpleados++;
					totalSalarios += list[i].salary;
				}
			}

			promedioSalarios = (float) cEmpleados / totalSalarios;

			for (int i = 0; i < len; i++)
			{
				if(!list[i].isEmpty && list[i].salary > promedioSalarios)
				{
					cEmpleadosArribaDelPromedio++;
				}
			}

			printf("El total de salarios es %f.2\n", totalSalarios);
			printf("El promedio de salarios es %f.2\n", promedioSalarios);
			printf("Hay %d empleados que ganan por encima del promedio\n", cEmpleadosArribaDelPromedio);
			
			break;
		case 3:
			continuar = 0;
			todoOk = 0;
			break;
		default:
			printf("Ingrese opcion valida\n");
			printf("Presione enter para continuar\n");
			getchar();
			break;
		}
	}
	return todoOk;
}

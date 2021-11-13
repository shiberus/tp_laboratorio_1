#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	Employee* pEmpleado;
	char* idAux = (char*) malloc(sizeof(char) * 256);
	char* nombreAux = (char*) malloc(sizeof(char) * 256);
	char* horasAux = (char*) malloc(sizeof(char) * 256);
	char* sueldoAux = (char*) malloc(sizeof(char) * 256);

	if(idAux != NULL && nombreAux != NULL && horasAux != NULL && sueldoAux != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", idAux, nombreAux, horasAux, sueldoAux);

		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", idAux, nombreAux, horasAux, sueldoAux))
			{
				pEmpleado = employee_newParametros(idAux, nombreAux, horasAux, sueldoAux);
				if(pEmpleado != NULL)
				{
					ll_add(pArrayListEmployee,pEmpleado);
					todoOk = 0;
				}
				else
				{
					employee_delete(pEmpleado);
					todoOk = -1;
					break;
				}
			}
			else
			{
				employee_delete(pEmpleado);
				break;
			}
		}
		while(!feof(pFile));
	}
	free(idAux);
	free(nombreAux);
	free(horasAux);
	free(sueldoAux);

    return todoOk;
}

int parser_EmployeeToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* tam = (int*) malloc(sizeof(int));
	int* id = (int*) malloc(sizeof(int));
	int* horasTrabajadas = (int*) malloc(sizeof(int));
	int* sueldo = (int*) malloc(sizeof(int));
	char* nombre = (char*) malloc(sizeof(char) * 256);
	Employee* pEmpleado;

	if (pFile != NULL && pArrayListEmployee != NULL && tam != NULL && id != NULL &&
	horasTrabajadas != NULL && sueldo != NULL && nombre != NULL)
	{
		*tam = ll_len(pArrayListEmployee);

		fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");

		for(int i = 0; i < *tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(!employee_getId(pEmpleado,id) &&
			!employee_getNombre(pEmpleado,nombre) &&
			!employee_getHorasTrabajadas(pEmpleado,horasTrabajadas) &&
			!employee_getSueldo(pEmpleado,sueldo))
			{
				fprintf(pFile,"%d,%s,%d,%d\n", *id, nombre, *horasTrabajadas, *sueldo);
			}
		}
		todoOk = 0;
	}
	free(tam);
	free(id);
	free(horasTrabajadas);
	free(sueldo);
	free(nombre);

	return todoOk;
}


int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* success = (int*) malloc(sizeof(int));

	Employee* pEmpleado;

	if (pFile != NULL && pArrayListEmployee != NULL && success != NULL)
	{
		*success = 0;
		do
        {
            pEmpleado = employee_new();
			if(pEmpleado != NULL)
			{
				*success = fread(pEmpleado, sizeof(Employee), 1, pFile);

				if(*success)
				{
					ll_add(pArrayListEmployee, pEmpleado);
				}
				else
				{
					employee_delete(pEmpleado);
					break;
				}
				todoOk = 0;
			}

        }
		while(!feof(pFile));
	}
	free(success);
	

    return todoOk;
}

int parser_EmployeeToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* tam = (int*) malloc(sizeof(int));
	Employee* pEmpleado;

	if (pFile != NULL && pArrayListEmployee != NULL && tam != NULL)
	{
		*tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < *tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				fwrite(pEmpleado, sizeof(Employee), 1, pFile);
			}
		}
		todoOk = 0;
	}
	free(tam);

	return todoOk;
}

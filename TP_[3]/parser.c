#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	Employee* pEmpleado;
	char idAux[256];
	char nombreAux[256];
	char horasAux[256];
	char sueldoAux[256];

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

    return todoOk;
}

int parser_EmployeeToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int tam, id, horasTrabajadas, sueldo;
	char nombre[128];
	Employee* pEmpleado;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		tam = ll_len(pArrayListEmployee);

		fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");

		for(int i = 0; i < tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(!employee_getId(pEmpleado,&id) &&
			!employee_getNombre(pEmpleado,nombre) &&
			!employee_getHorasTrabajadas(pEmpleado,&horasTrabajadas) &&
			!employee_getSueldo(pEmpleado,&sueldo))
			{
				fprintf(pFile,"%d,%s,%d,%d\n", id, nombre, horasTrabajadas, sueldo);
			}
		}
		todoOk = 0;
	}

	return todoOk;
}


int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;

	Employee* pEmpleado;
	int success = 0;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		do
        {
            pEmpleado = employee_new();
			if(pEmpleado != NULL)
			{
				success = fread(pEmpleado, sizeof(Employee), 1, pFile);

				if(success)
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
	

    return todoOk;
}

int parser_EmployeeToBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int tam;
	Employee* pEmpleado;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				fwrite(pEmpleado, sizeof(Employee), 1, pFile);
			}
		}
		todoOk = 0;
	}

	return todoOk;
}

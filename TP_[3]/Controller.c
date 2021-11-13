#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "Util.h"


int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));
	
	FILE* pFile;
	
	if(path != NULL && pArrayListEmployee != NULL && fail != NULL)
	{
		*fail = 1;
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			*fail = parser_EmployeeFromText(pFile, pArrayListEmployee);

			if (!(*fail))
			{
				todoOk = 0;
			}
		}
		fclose(pFile);
	}
	free(fail);

	return todoOk;
}

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));
	
	FILE* pFile;
	
	if(path != NULL && pArrayListEmployee != NULL && fail != NULL)
	{
		*fail = 1;
		pFile = fopen(path, "rb");
		if(pFile != NULL)
		{
			*fail = parser_EmployeeFromBinary(pFile, pArrayListEmployee);

			if (!(*fail))
			{
				todoOk = 0;
			}
		}
		fclose(pFile);
	}
	free(fail);

	return todoOk;
}

int controller_addEmployee(LinkedList* pArrayListEmployee, int nextId)
{
	int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));
	int* horas = (int*) malloc(sizeof(int));
	int* sueldo = (int*) malloc(sizeof(int));
	char* nombre = (char*) malloc(sizeof(char) * 128);
	
	Employee* pEmpleado = employee_new();

	if(pArrayListEmployee != NULL && pEmpleado != NULL && fail != NULL && nombre != NULL && sueldo != NULL && horas != NULL)
	{
		*fail = 1;
		ingresarString(nombre, "Ingrese nombre", 2, 127);
		*fail = utn_getNumero(horas, "Ingrese horas trabajadas: ", "Ingrese un numero valido (entre 0 y 9999): ", 0, 9999, 5);
		if(*fail)
		{
			pausar("No se pudieron ingresar las horas");
		}

		*fail = utn_getNumero(sueldo, "Ingrese sueldo: ", "Ingrese un numero valido (entre 8000 y 1.000.000): ", 0, 1000000, 5);
		if(*fail)
		{
			pausar("No se pudo ingresar el sueldo");
		}

		if(!employee_setNombre(pEmpleado, nombre) &&
		!employee_setHorasTrabajadas(pEmpleado, *horas) &&
		!employee_setSueldo(pEmpleado, *sueldo) &&
		!employee_setId(pEmpleado, nextId))
		{
			ll_add(pArrayListEmployee, pEmpleado);

			printf("   id  |       nombre       | horas |  sueldo \n");
			printf("----------------------------------------------- \n");
			employee_print(pEmpleado);

			todoOk = 0;
		}
	}

	free(fail);
	free(horas);
	free(sueldo);
	free(nombre);

    return todoOk;
}

int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));
	int* continuar = (int*) malloc(sizeof(int));
	int* id = (int*) malloc(sizeof(int));
	int* horas = (int*) malloc(sizeof(int));
	int* sueldo = (int*) malloc(sizeof(int));
	int* index = (int*) malloc(sizeof(int));
	int* option = (int*) malloc(sizeof(int));
	char* nombre = (char*) malloc(sizeof(char) * 128);
	Employee* pEmpleado;


    if(pArrayListEmployee != NULL && fail != NULL && continuar != NULL && id != NULL && horas != NULL &&
	sueldo != NULL && index != NULL && option != NULL && nombre != NULL)
    {
		*continuar = 1;
		controller_ListEmployee(pArrayListEmployee);
		utn_getNumero(id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
		
		*index = controller_findEmployeeById(pArrayListEmployee, *id);
		while(*index == -1 && *continuar)
		{
			*continuar = !cancelarOperacion("No se encontro al empleado");
			utn_getNumero(id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
			*index = controller_findEmployeeById(pArrayListEmployee, *id);
		}

		if(*index != -1)
		{
			pEmpleado = ll_get(pArrayListEmployee, *index);

			if(pEmpleado == NULL)
			{
				*continuar = 0;
			}
			else
			{
				todoOk = 0;
			}
		}

		while(*continuar)
		{
			printf("   id  |       nombre       | horas |  sueldo \n");
			printf("----------------------------------------------- \n");
			employee_print(pEmpleado);
			printf("----------------------------------------------- \n");
	    	printf("*** Editar empleado ***\n\n");
	    	printf("1- modificar nombre\n");
	    	printf("2- modificar horas trabajadas\n");
	    	printf("3- modificar sueldo\n");
	    	printf("4- salir\n\n");
	    	scanf("%d", option);

			switch (*option)
			{
				case 1:
					ingresarString(nombre, "Ingrese nombre", 2, 127);
					if(!employee_setNombre(pEmpleado, nombre))
					{
						pausar("\n Operacion exitosa");
					}
					break;

				case 2:
					*fail = utn_getNumero(horas, "Ingrese horas trabajadas: ", "Ingrese un numero valido (entre 0 y 9999): ", 0, 9999, 5);
					if(*fail)
					{
						pausar("No se pudieron ingresar las horas");
					}
					else
					{
						if(!employee_setHorasTrabajadas(pEmpleado, *horas))
						{
							pausar("\n Operacion exitosa");
						}
					}
					break;

				case 3:
					*fail = utn_getNumero(sueldo, "Ingrese sueldo: ", "Ingrese un numero valido (entre 8000 y 1.000.000): ", 0, 1000000, 5);
					if(*fail)
					{
						pausar("No se pudo ingresar el sueldo");
					}
					else
					{
						if(!employee_setSueldo(pEmpleado, *sueldo))
						{
							pausar("\n Operacion exitosa");
						}
						else
						{
							pausar("\n Hubo un error");
						}
					}
					break;

				case 4:
					*continuar = 0;
					break;

				default:
					pausar("Opcion invalida");
					break;
			}
		}
    }

	free(fail);
	free(continuar);
	free(id);
	free(horas);
	free(sueldo);
	free(index);
	free(option);
	free(nombre);

	return todoOk;
}

int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* continuar = (int*) malloc(sizeof(int));
	int* id = (int*) malloc(sizeof(int));
	int* index = (int*) malloc(sizeof(int));

	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && continuar != NULL && id != NULL && index != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		utn_getNumero(id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
		
		*index = controller_findEmployeeById(pArrayListEmployee, *id);
		while(*index == -1 && *continuar)
		{
			*continuar = !cancelarOperacion("No se encontro al empleado");
			utn_getNumero(id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
			*index = controller_findEmployeeById(pArrayListEmployee, *id);
		}

		if(*index != -1)
		{
			pEmpleado = ll_get(pArrayListEmployee, *index);

			if(pEmpleado != NULL)
			{
				printf("   id  |       nombre       | horas |  sueldo \n");
				printf("----------------------------------------------- \n");
				employee_print(pEmpleado);
				printf("----------------------------------------------- \n\n");
				if(preguntar("Eliminar al empleado?"))
				{
					ll_remove(pArrayListEmployee, *index);
					employee_delete(pEmpleado);
					pausar("Operacion exitosa");
				}
				else
				{
					pausar("Operacion cancelada");
				}
				todoOk = 0;
			}
		}
	}

	free(continuar);
	free(id);
	free(index);

	return todoOk;
}

int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int* tam = (int*) malloc(sizeof(int));

	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && tam != NULL)
	{
		*tam = ll_len(pArrayListEmployee);

		printf("   id  |       nombre       | horas |  sueldo \n");
		printf("----------------------------------------------- \n");
		for(int i = 0; i < *tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				employee_print(pEmpleado);
			}
		}
		todoOk = 0;
	}
	free(tam);

	return todoOk;
}

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int* option = (int*) malloc(sizeof(int));

	if(pArrayListEmployee != NULL && option != NULL)
	{
		*option = 0;
		do
		{
			printf("*** Ordenar empleados ***\n\n");
			printf("1- Id ascendente\n");
			printf("2- Id descendente\n");
			printf("3- Nombre ascendente\n");
			printf("4- Nombre descendente\n");
			printf("5- Horas trabajadas ascendente\n");
			printf("6- Horas trabajadas descendente\n");
			printf("7- Sueldo ascendente\n");
			printf("8- Sueldo descendente\n");
			printf("9- Salir\n");
			fflush(stdin);
			scanf("%d", option);

			switch(*option)
			{
				case 1:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareIds, 1);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 2:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareIds, 0);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 3:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareNombres, 1);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 4:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareNombres, 0);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 5:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareHoras, 1);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 6:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareHoras, 0);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 7:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareSueldos, 1);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 8:
					printf("Ordenando...\n");
					ll_sort(pArrayListEmployee, controller_compareSueldos, 0);
					controller_ListEmployee(pArrayListEmployee);
					pausar("Elementos ordenados");
					break;

				case 9:
					break;

				default:
					pausar("Opcion invalida");
					break;
			}
		} while (*option != 9);
		todoOk = 0;
	}
	free(option);

	return todoOk;
}

int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));

	if(path != NULL && pArrayListEmployee != NULL && fail != NULL)
	{
		*fail = 1;
		FILE* f = fopen(path,"w");
		if(f != NULL)
		{
			*fail = parser_EmployeeToText(f, pArrayListEmployee);

			if(!(*fail))
			{
				todoOk = 0;
			}

			fclose(f);
		}
	}
	free(fail);

    return todoOk;
}

int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int* fail = (int*) malloc(sizeof(int));

	if(path != NULL && pArrayListEmployee != NULL && fail != NULL)
	{
		*fail = 1;
		FILE* f = fopen(path,"wb");
		if(f != NULL)
		{
			*fail = parser_EmployeeToBinary(f, pArrayListEmployee);

			if(!(*fail))
			{
				todoOk = 0;
			}

			fclose(f);
		}
	}
	free(fail);

    return todoOk;
}

int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int index = -1;
	int* tam = (int*) malloc(sizeof(int));
	int* idAux = (int*) malloc(sizeof(int));
	int* fail = (int*) malloc(sizeof(int));

	*fail = 1;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && tam != NULL && idAux != NULL && fail != NULL && id > 0)
	{
		*tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < *tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				*fail = employee_getId(pEmpleado, idAux);

				if(!(*fail) && *idAux == id)
				{
					index = i;
					break;
				}
			}
		}
	}
	free(tam);
	free(idAux);
	free(fail);

    return index;
}

int controller_getMaxId(LinkedList* pArrayListEmployee)
{
	int idMax = 0;
	int* tam = (int*) malloc(sizeof(int));
	int* idAux = (int*) malloc(sizeof(int));
	int* fail = (int*) malloc(sizeof(int));
	int* index = (int*) malloc(sizeof(int));


	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && tam != NULL && idAux != NULL && fail != NULL && index != NULL)
	{
		*fail = 1;
		*tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < *tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				*fail = employee_getId(pEmpleado, idAux);

				if(!(*fail))
				{
					if(*idAux > idMax)
					{
						idMax = *idAux;
					}
				}
			}
		}
	}
	free(tam);
	free(idAux);
	free(fail);
	free(index);

    return idMax;
}

int controller_compareIds(void* first, void* second)
{
	int resultado = 0;
	int* firstId = (int*) malloc(sizeof(int));
	int* secondId = (int*) malloc(sizeof(int));
	
	Employee* firstEmp;
	Employee* secondEmp;

	if(first != NULL && second != NULL && firstId != NULL && secondId != NULL)
	{
		firstEmp = (Employee*) first;
		secondEmp = (Employee*) second;

		if(!employee_getId(firstEmp, firstId) && !employee_getId(secondEmp, secondId))
		{
			resultado = *firstId - *secondId;
		}
	}
	free(firstId);
	free(secondId);

	return resultado == 0 ? 0 : resultado > 0 ? 1 : -1;
}

int controller_compareNombres(void* first, void* second)
{
	int resultado = 0;
	char* firstNombre = (char*) malloc(sizeof(char) * 128);
	char* secondNombre = (char*) malloc(sizeof(char) * 128);

	Employee* firstEmp;
	Employee* secondEmp;

	if(first != NULL && second != NULL && firstNombre != NULL && secondNombre != NULL)
	{
		firstEmp = (Employee*) first;
		secondEmp = (Employee*) second;
		 
		if(!employee_getNombre(firstEmp, firstNombre) && !employee_getNombre(secondEmp, secondNombre))
		{
			resultado = strcmp(firstNombre, secondNombre);
		}
	}
	free(firstNombre);
	free(secondNombre);

	return resultado == 0 ? 0 : resultado > 0 ? 1 : -1;
}

int controller_compareHoras(void* first, void* second)
{
	int resultado = 0;
	int* firstHoras = (int*) malloc(sizeof(int));
	int* secondHoras = (int*) malloc(sizeof(int));

	Employee* firstEmp;
	Employee* secondEmp;

	if(first != NULL && second != NULL && firstHoras != NULL && secondHoras != NULL)
	{
		firstEmp = (Employee*) first;
		secondEmp = (Employee*) second;

		if(!employee_getHorasTrabajadas(firstEmp, firstHoras) && !employee_getHorasTrabajadas(secondEmp, secondHoras))
		{
			resultado = *firstHoras - *secondHoras;
		}
	}
	free(firstHoras);
	free(secondHoras);

	return resultado == 0 ? 0 : resultado > 0 ? 1 : -1;	
}

int controller_compareSueldos(void* first, void* second)
{
	int resultado = 0;
	int* firstSueldo = (int*) malloc(sizeof(int));
	int* secondSueldo = (int*) malloc(sizeof(int));

	Employee* firstEmp;
	Employee* secondEmp;

	if(first != NULL && second != NULL && firstSueldo != NULL && secondSueldo != NULL)
	{
		firstEmp = (Employee*) first;
		secondEmp = (Employee*) second;

		if(!employee_getSueldo(firstEmp, firstSueldo) && !employee_getSueldo(secondEmp, secondSueldo))
		{
			resultado = firstSueldo - secondSueldo;
		}
	}
	free(firstSueldo);
	free(secondSueldo);

	return resultado == 0 ? 0 : resultado > 0 ? 1 : -1;	
}

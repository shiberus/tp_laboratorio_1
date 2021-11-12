#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "Util.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int fail = 1;
	FILE* pFile;
	
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			fail = parser_EmployeeFromText(pFile, pArrayListEmployee);

			if (!fail)
			{
				todoOk = 0;
			}
		}
		fclose(pFile);
	}

	return todoOk;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int fail = 1;
	FILE* pFile;
	
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile != NULL)
		{
			fail = parser_EmployeeFromBinary(pFile, pArrayListEmployee);

			if (!fail)
			{
				todoOk = 0;
			}
		}
		fclose(pFile);
	}

	return todoOk;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int nextId)
{
	int todoOk = -1;
	int fail, horas, sueldo;
	char nombre[128];
	Employee* pEmpleado = employee_new();

	if(pArrayListEmployee != NULL && pEmpleado != NULL)
	{
		ingresarString(nombre, "Ingrese nombre", 2, 127);
		fail = utn_getNumero(&horas, "Ingrese horas trabajadas: ", "Ingrese un numero valido (entre 0 y 9999): ", 0, 9999, 5);
		if(fail)
		{
			pausar("No se pudieron ingresar las horas");
		}

		fail = utn_getNumero(&sueldo, "Ingrese sueldo: ", "Ingrese un numero valido (entre 8000 y 1.000.000): ", 0, 1000000, 5);
		if(fail)
		{
			pausar("No se pudo ingresar el sueldo");
		}

		if(!employee_setNombre(pEmpleado, nombre) &&
		!employee_setHorasTrabajadas(pEmpleado, horas) &&
		!employee_setSueldo(pEmpleado, sueldo) &&
		!employee_setId(pEmpleado, nextId))
		{
			ll_add(pArrayListEmployee, pEmpleado);

			printf("   id  |       nombre       | horas |  sueldo \n");
			printf("----------------------------------------------- \n");
			employee_print(pEmpleado);

			todoOk = 0;
		}
	}


    return todoOk;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int continuar = 1;
	int id, index, option, fail, sueldo, horas;
	char nombre[128];
	Employee* pEmpleado;

    if(pArrayListEmployee != NULL)
    {
		controller_ListEmployee(pArrayListEmployee);
		utn_getNumero(&id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
		
		index = controller_findEmployeeById(pArrayListEmployee, id);
		while(index == -1 && continuar)
		{
			continuar = !cancelarOperacion("No se encontro al empleado");
			utn_getNumero(&id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
			index = controller_findEmployeeById(pArrayListEmployee, id);
		}

		if(index != -1)
		{
			pEmpleado = ll_get(pArrayListEmployee, index);

			if(pEmpleado == NULL)
			{
				continuar = 0;
			}
			else
			{
				todoOk = 0;
			}
		}

		while(continuar)
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
	    	scanf("%d", &option);

			switch (option)
			{
				case 1:
					ingresarString(nombre, "Ingrese nombre", 2, 127);
					if(!employee_setNombre(pEmpleado, nombre))
					{
						pausar("\n Operacion exitosa");
					}
					break;

				case 2:
					fail = utn_getNumero(&horas, "Ingrese horas trabajadas: ", "Ingrese un numero valido (entre 0 y 9999): ", 0, 9999, 5);
					if(fail)
					{
						pausar("No se pudieron ingresar las horas");
					}
					else
					{
						if(!employee_setHorasTrabajadas(pEmpleado, horas))
						{
							pausar("\n Operacion exitosa");
						}
					}
					break;

				case 3:
					fail = utn_getNumero(&sueldo, "Ingrese sueldo: ", "Ingrese un numero valido (entre 8000 y 1.000.000): ", 0, 1000000, 5);
					if(fail)
					{
						pausar("No se pudo ingresar el sueldo");
					}
					else
					{
						if(!employee_setSueldo(pEmpleado, sueldo))
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
					continuar = 0;
					break;

				default:
					pausar("Opcion invalida");
					break;
			}
		}
    }

	return todoOk;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int index, continuar, id;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		utn_getNumero(&id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
		
		index = controller_findEmployeeById(pArrayListEmployee, id);
		while(index == -1 && continuar)
		{
			continuar = !cancelarOperacion("No se encontro al empleado");
			utn_getNumero(&id, "Ingrese id: ", "Ingrese un numero valido (entre 1 y 9999): ", 1, 9999, 20);
			index = controller_findEmployeeById(pArrayListEmployee, id);
		}

		if(index != -1)
		{
			pEmpleado = ll_get(pArrayListEmployee, index);

			if(pEmpleado != NULL)
			{
				printf("   id  |       nombre       | horas |  sueldo \n");
				printf("----------------------------------------------- \n");
				employee_print(pEmpleado);
				printf("----------------------------------------------- \n\n");
				if(preguntar("Eliminar al empleado?"))
				{
					ll_remove(pArrayListEmployee, index);
					free(pEmpleado);
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

	return todoOk;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int tam;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL)
	{
		tam = ll_len(pArrayListEmployee);

		printf("   id  |       nombre       | horas |  sueldo \n");
		printf("----------------------------------------------- \n");
		for(int i = 0; i < tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				employee_print(pEmpleado);
			}
		}
	}

	return todoOk;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = -1;

	return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int todoOk = -1;
	int fail;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE* f = fopen(path,"w");
		if(f != NULL)
		{
			fail = parser_EmployeeToText(f, pArrayListEmployee);

			if(!fail)
			{
				todoOk = 0;
			}

			fclose(f);
		}
	}

    return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int todoOk = -1;
	int fail;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE* f = fopen(path,"wb");
		if(f != NULL)
		{
			fail = parser_EmployeeToBinary(f, pArrayListEmployee);

			if(!fail)
			{
				todoOk = 0;
			}

			fclose(f);
		}
	}

    return todoOk;
}

int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int tam, idAux, fail;
	int index = -1;
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && id > 0)
	{
		tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				fail = employee_getId(pEmpleado, &idAux);

				if(!fail && idAux == id)
				{
					index = i;
					break;
				}
			}
		}
	}

    return index;
}

int controller_getMaxId(LinkedList* pArrayListEmployee)
{
	int idMax = -1;
	int tam, idAux, fail;

	Employee* pEmpleado;

	if(pArrayListEmployee != NULL)
	{
		tam = ll_len(pArrayListEmployee);

		for(int i = 0; i < tam; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

			if(pEmpleado != NULL)
			{
				fail = employee_getId(pEmpleado, &idAux);

				if(!fail)
				{
					if(idAux > idMax)
					{
						idMax = idAux;
					}
				}
			}
		}
	}

    return idMax;
}

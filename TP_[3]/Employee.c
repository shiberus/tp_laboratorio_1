#include "Employee.h"

Employee* employee_new()
{
	Employee* pEmpleado = (Employee*) malloc(sizeof(Employee));

	pEmpleado ->id = 0;
	pEmpleado ->horasTrabajadas = 0;
	pEmpleado ->sueldo = 0;
	strcpy(pEmpleado->nombre, "Natalia Natalia");

	return pEmpleado;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	int auxId, auxHoras, auxSueldo;
	Employee* pEmpleado = NULL;

	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		auxId = atoi(idStr);
		auxHoras = atoi(horasTrabajadasStr);
		auxSueldo = atoi(sueldoStr);

		Employee* auxEmpleado = employee_new();
		
		if(auxEmpleado != NULL)
		{
			if(!employee_setId(auxEmpleado, auxId) &&
			!employee_setNombre(auxEmpleado, nombreStr) &&
			!employee_setHorasTrabajadas(auxEmpleado, auxHoras) &&
			!employee_setSueldo(auxEmpleado, auxSueldo))
			{
				pEmpleado = auxEmpleado;
			}
		}
	}
	return pEmpleado;
}

void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

int employee_setId(Employee *this, int id)
{
	int todoOk = -1;

	if(this != NULL && id > 0)
	{
		this->id = id;
		todoOk = 0;
	}
	return todoOk;
}

int employee_getId(Employee *this, int *id)
{
	int todoOk = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->id;
		todoOk = 0;
	}
	return todoOk;
}

int employee_setNombre(Employee *this, char *nombre)
{
	int todoOk = -1;

	if(this != NULL && nombre != NULL && strlen(nombre) < 128)
	{
		strcpy(this->nombre, nombre);
		todoOk = 0;
	}
	return todoOk;
}

int employee_getNombre(Employee *this, char *nombre)
{
	int todoOk = -1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		todoOk = 0;
	}
	return todoOk;
}

int employee_setHorasTrabajadas(Employee *this, int horasTrabajadas)
{
	int todoOk = -1;

	if(this != NULL && horasTrabajadas > -1)
	{
		this->horasTrabajadas = horasTrabajadas;
		todoOk = 0;
	}
	return todoOk;
}

int employee_getHorasTrabajadas(Employee *this, int *horasTrabajadas)
{
	int todoOk = -1;

	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		todoOk = 0;
	}
	return todoOk;
}

int employee_setSueldo(Employee *this, int sueldo)
{
	int todoOk = -1;

	if(this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		todoOk = 0;
	}
	return todoOk;
}

int employee_getSueldo(Employee *this, int *sueldo)
{
	int todoOk = -1;

	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		todoOk = 0;
	}
	return todoOk;
}

int employee_print(Employee* this)
{
	int todoOk = -1;
	int* id = (int*) malloc(sizeof(int));
	int* horas = (int*) malloc(sizeof(int));
	int* sueldo = (int*) malloc(sizeof(int));
	char* nombre = (char*) malloc(sizeof(char) * 256);

	if(this != NULL && id != NULL && nombre != NULL && sueldo != NULL && horas != NULL)
	{
		if(!employee_getNombre(this, nombre) &&
		!employee_getHorasTrabajadas(this, horas) &&
		!employee_getSueldo(this, sueldo) &&
		!employee_getId(this, id))
		{
			printf("%4d  %18s      %3d      %5d \n", *id, nombre, *horas, *sueldo);
		}
		todoOk = 0;
	}
	free(id);
	free(horas);
	free(sueldo);
	free(nombre);

	return todoOk;
}

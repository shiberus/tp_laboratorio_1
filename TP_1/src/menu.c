/*
 * menu.c
 *
 *  Created on: 24 sep. 2021
 *      Author: Dell
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "operaciones.h"

void realizarOperaciones(int a, int b, int* rSuma, int* rResta, int* rMult, float* rDiv, int* rFactA, int* rFactB)
{
	*rSuma = sumar(a, b);
	*rResta = restar(a, b);
	*rMult = multiplicar(a, b);

	if(b != 0)
	{
		*rDiv = dividir(a, b);
	}

	if(a >= 0 && a <=12)
	{
		*rFactA = factorial(a);
	}

	if(b >= 0 && b <=12)
	{
		*rFactB = factorial(b);
	}
}

void informarResultados(int a, int b, int rSuma, int rResta, int rMult, float rDiv, int rFactA, int rFactB)
{
	printf("El resultado de A+B es: %d\n", rSuma);
	printf("El resultado de A-B es: %d\n", rResta);
	if(b != 0)
	{
		printf("El resultado de A/B es: %.2f\n", rDiv);
	}
	else
	{
		printf("No es posible dividir por cero\n");
	}
	printf("El resultado de A*B es: %d\n", rMult);

	if(a >= 0 && a <= 12)
	{
		printf("El factorial de A es: %d\n", rFactA);
	}
	else
	{
		printf("No es posible calcular el factorial de %d\n", a);
	}

	if(b >= 0 && b <= 12)
	{
		printf("El factorial de B es: %d\n", rFactB);
	}
	else
	{
		printf("No es posible calcular el factorial de %d\n", b);
	}

	printf("Presione enter para continuar\n");
	fflush(stdin);
	getchar();
}

void menu()
{
	int a,b;
	int flagA = 0;
	int flagB = 0;
	int flagOperaciones = 0;

	int opcion;
	int seguir = 1;

	int resultadoSuma,
		resultadoResta,
		resultadoMult,
		factorialA,
		factorialB;

	float resultadoDiv;

	do
	{
		printf("ingrese una opcion:\n");
		printf("1. Ingresar primer operando.\n");
		printf("2. Ingresar segundo operando.\n");
		printf("3. Realizar operaciones.\n");
		printf("4. Mostrar resultados.\n");
		printf("5. Salir.\n");
		scanf("%d", &opcion);

		while(opcion < 0 || opcion > 5)
		{
			printf("Ingrese una opcion valida.\n");
			scanf("%d", &opcion);
		}

		switch(opcion)
		{
			case 1:
				printf("Ingrese un entero.\n");
				scanf("%d", &a);
				flagA = 1;
				flagOperaciones = 0;
				break;
			case 2:
				printf("Ingrese un entero.\n");
				scanf("%d", &b);
				flagB = 1;
				flagOperaciones = 0;
				break;
			case 3:
				if(flagA && flagB)
				{
					realizarOperaciones(a, b, &resultadoSuma, &resultadoResta, &resultadoMult, &resultadoDiv, &factorialA, &factorialB);
					flagOperaciones = 1;
				}
				else
				{
					printf("Debe ingresar ambos operandos para realizar las operaciones, presione enter para continuar\n");
					fflush(stdin);
					getchar();
				}
				break;
			case 4:
				if(flagOperaciones)
				{
					informarResultados(a, b, resultadoSuma, resultadoResta, resultadoMult, resultadoDiv, factorialA, factorialB);
				}
				else
				{
					printf("Debe realizar las operaciones con los operandos actuales para saber los resultados, presione enter para continuar\n");
					fflush(stdin);
					getchar();
				}
				break;
			case 5:
				seguir = 0;
				break;
		}
	}
	while(seguir);
}

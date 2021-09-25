/*
 * operaciones.c
 *
 *  Created on: 24 sep. 2021
 *      Author: Dell
 */

int sumar(int a, int b)
{
	return a + b;
}


int restar(int a, int b)
{
	return a - b;
}

int multiplicar(int a, int b)
{
	return a * b;
}

float dividir(int a, int b)
{
	return (float) a / b;
}

int factorial(int a)
{
	if(a == 0)
	{
		return 1;
	}
	else
	{
		return a * factorial(a - 1);
	}
}

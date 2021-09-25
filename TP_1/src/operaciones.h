/*
 * operaciones.h
 *
 *  Created on: 24 sep. 2021
 *      Author: Dell
 */

#ifndef OPERACIONES_H_
#define OPERACIONES_H_

/**
 * calcula la suma de dos valores
 * @param a valor del primer operando de la suma
 * @param b valor del segundo operando de la suma
 * @return resultado de la suma
 */
int sumar(int a, int b);

/**
 * calcula la resta de dos valores
 * @param int a valor del primer operando de la resta
 * @param int b valor del operando que sera substraido del anterior
 * @return int resultado de la resta
 */
int restar(int a, int b);

/**
 * calcula la multiplicacion de dos valores
 * @param int a valor del primer factor
 * @param int b valor del segundo factor
 * @return int resultado de la multiplicacion
 */
int multiplicar(int a, int b);

/**
 * calcula la division entre dos valores
 * @param int a valor del dividendo
 * @param int b valor del divisor
 * @return int cociente de la division
 */
float dividir(int a, int b);

/**
 * calcula el factorial de un valor
 * @param int a valor del cual se calcula el factorial
 * @return resultado del factorial
 */
int factorial(int a);

#endif /* OPERACIONES_H_ */

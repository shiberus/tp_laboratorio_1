/*
 * menu.h
 *
 *  Created on: 24 sep. 2021
 *      Author: Dell
 */

#ifndef MENU_H_
#define MENU_H_

/**
 *
 * @param a valor del primer operando
 * @param b valor del segundo operando
 * @param rSuma referencia al resultado de la suma
 * @param rResta referencia al resultado de la resta
 * @param rMult referencia al resultado de la multiplicacion
 * @param rDiv referencia al resultado de la division
 * @param rFactA referencia al factorial de A
 * @param rFactB referencia al factorial de B
 */
void realizarOperaciones(int a, int b, int* rSuma, int* rResta, int* rMult, float* rDiv, int* rFactA, int* rFactB);

/**
 *
 * @param a valor de A
 * @param b valor de B
 * @param rSuma valor del resultado de la suma
 * @param rResta valor del resultado de la resta
 * @param rMult valor del resultado de la multiplicacion
 * @param rDiv valor del resultado de la division
 * @param rFactA valor del factorial de A
 * @param rFactB valor del factorial de B
 */
void informarResultados(int a, int b, int rSuma, int rResta, int rMult, float rDiv, int rFactA, int rFactB);

/**
 * muestra el menu
 */
void menu();

#endif /* MENU_H_ */

/*
 * ArrayEmployees.h
 *
 *  Created on: 16 oct. 2021
 *      Author: Dell
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

typedef struct {
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;
} Employee;


/**
 * @brief Para indicar que todas las posiciones del array estan vacias, esta funcion pone la bandera (isEmpty)
 * en TRUE en todas las posiciones del array
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @return si hay un Error (-1) [tamanio invalido o puntero nulo] - (0) Ok
 */
int initEmployees(Employee* list, int len);

/**
 * @brief muestra el menu principal
 *
 * @return int opcion elegida
 */
int menu();

/**
 * @brief Toma los datos necesarios para dar de alta a un empleado
 *
 * @param newEmployee
 * @return int Error (-1) - Ok (0)
 */
int newEmployee(Employee* newEmployee);

/**
 * @brief Agrega en un array de empleados existente los valores recibidos como parametro en la primer posicion libre
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @param id int
 * @param name[] char
 * @param lastName[] char
 * @param salary float
 * @param sector int
 * @return si hay un Error (-1) [tamanio invalido, puntero nulo o sin espacio libre] - (0) Ok
 */
int addEmployee(Employee* list, int len, int id, char name[],char
lastName[],float salary,int sector);

/**
 * @brief Busca un empleado recibiendo como parametro de busqueda su Id
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @param id int
 * @return indice de la posicion del empleado o (-1) [tamanio invalido, puntero nulo o no se encuentra al empleado]
 */
int findEmployeeById(Employee* list, int len,int id);

/**
 * @brief Elimina de manera logica (isEmpty Flag en 1) un empleado recibiendo como parametro su Id
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @return si hay un Error (-1) [tamanio invalido, puntero nulo o no se encuentra al empleado]
 */
int removeEmployee(Employee* list, int len);

/**
 * @brief Ordena el array de empleados por apellido y sector de manera ascendente o descendente
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @param order int [1] indica ascendente - [0] indica descendente
 * @return si hay un Error (-1) [tamanio invalido o puntero nulo] - (0) Ok
 */
int sortEmployees(Employee* list, int len, int order);

/**
 * @brief Imprime el array de empleados de forma encolumnada
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @return int Error (-1) - Ok (0)
 */
int printEmployees(Employee* list, int length);

/**
 * @brief Imprime un solo empleado de manera encolumnada
 *
 * @param e Employee
 * @return int Error (-1) - Ok (0)
 */
int printEmployee(Employee e);

/**
 * @brief Busca la primer posicion vacia en el array de empleados
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @return Indice de la primer posicion libre en el array de empleados o (-1) si hay error o no hay lugar
 */
int findEmpty(Employee* list, int len);

/**
 * @brief Permite modificar datos de un empleado
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @param i int posicion del empleado en el array
 * @return int Error (-1) - Ok (0)
 */
int modifyEmployee(Employee* list, int len, int i);

/**
 * @brief Muestra los informes al usuario
 *
 * @param list puntero al array de empleados
 * @param len int tamanio del array de empleados
 * @return int Error (-1) - Ok (0)
 */
int informes(Employee* list, int len);


#endif /* ARRAYEMPLOYEES_H_ */

#ifndef controller_H_INCLUDED
#define controller_H_INCLUDED

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int nextId);

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee);

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee);

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee);

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee);

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);

/** \brief Guarda los datos de los empleados en el archivo data.bin (modo binario).
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

/** \brief Busca un empleado por su Id.
 *
 * \param pArrayListEmployee LinkedList*
 * \param id int
 * \return int indice en que se encuentra el empleado
 *
 */
int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id);

/** \brief Busca el Id mas alto registrado.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int el id mas alto
 *
 */
int controller_getMaxId(LinkedList* pArrayListEmployee);

/** \brief Compara el id de dos empleados.
 *
 * \param first void* puntero al primer empleado
 * \param second void* puntero al segundo empleado
 * \return int -1, 0 o 1 si el primero es mas pequeño, igual o mas grande que el segundo
 *
 */
int controller_compareIds(void* first, void* second);

/** \brief Compara el nombre de dos empleados.
 *
 * \param first void* puntero al primer empleado
 * \param second void* puntero al segundo empleado
 * \return int -1, 0 o 1 si el primero es mas pequeño, igual o mas grande que el segundo
 *
 */
int controller_compareNombres(void* first, void* second);

/** \brief Compara las horas trabajadas de dos empleados.
 *
 * \param first void* puntero al primer empleado
 * \param second void* puntero al segundo empleado
 * \return int -1, 0 o 1 si el primero es mas pequeño, igual o mas grande que el segundo
 *
 */
int controller_compareHoras(void* first, void* second);

/** \brief Compara el sueldo de dos empleados.
 *
 * \param first void* puntero al primer empleado
 * \param second void* puntero al segundo empleado
 * \return int -1, 0 o 1 si el primero es mas pequeño, igual o mas grande que el segundo
 *
 */
int controller_compareSueldos(void* first, void* second);

#endif // controller_H_INCLUDED

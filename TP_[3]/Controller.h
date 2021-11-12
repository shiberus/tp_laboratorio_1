int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee, int nextId);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);
int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id);
int controller_getMaxId(LinkedList* pArrayListEmployee);
int controller_compareIds(void* first, void* second);
int controller_compareNombres(void* first, void* second);
int controller_compareHoras(void* first, void* second);
int controller_compareSueldos(void* first, void* second);
int controller_setModoDeDato(int modo);
int controller_getModoDeDato(int* modo);



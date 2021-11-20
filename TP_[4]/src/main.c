/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"

int main(void)
{
	startTesting(1);  // ll_newLinkedList
    startTesting(2);  // ll_len
	startTesting(3);  // getNode - test_getNode
 	startTesting(4);  // addNode - test_addNode
 	startTesting(5);  // ll_add
	startTesting(6);  // ll_get
	startTesting(7);  // ll_set
	startTesting(8);  // ll_remove
	startTesting(9);  // ll_clear
	startTesting(10); // ll_deleteLinkedList
	startTesting(11); // ll_indexOf
	startTesting(12); // ll_isEmpty
	startTesting(13); // ll_push
	startTesting(14); // ll_pop
	startTesting(15); // ll_contains
	startTesting(16); // ll_containsAll
	startTesting(17); // ll_subList
	startTesting(18); // ll_clone
	startTesting(19); // ll_sort

	printf("\n\nPresione enter para iniciar demostracion.\n\n");
	getchar();

	LinkedList* numeros = NULL;
	LinkedList* subLista = NULL;
	int* numero = NULL;
	

	numeros = ll_newLinkedList();
	printf("Creo una linked list.\n");

	if(numeros == NULL)
	{
		exit(1); //Solo para no meter todo adentro de un if.
	}

	printf("Le cargo los numeros del 0 al 99\n\n");
	printf("los primeros 50 desordenados.\n\n");
	printf("los ultimos 50 son puestos en reversa al principio de la lista.\n\n");

	for(int i = 0; i < 100; i++)
	{
		numero = (int*) malloc(sizeof(int));
		*numero = i;
		
		if(i < 10)
		{
			ll_add(numeros, numero);//los primeros 10 al final de la lista.
		}
		else if(i < 50)
		{
			ll_push(numeros, i / 3, numero);//los siguiente 40 desordenados. (esto tambien desordena los que ya estaban)
		}
		else
		{
			ll_set(numeros, 0, numero);// los ultimos 50 son puestos en reversa al principio de la lista.
		}

	}

	ll_forEach(numeros, printInt);

	numero = (int*) ll_get(numeros, 90);
	printf("\n\nEl numero en el indice 90 es %d\n\n", *numero);

	ll_sort(numeros, compararNums, 0);

	printf("Luego de ordenar la lista en orden descendente el %d esta en el indice %d\n\n", *numero, ll_indexOf(numeros, numero));

	subLista = ll_subList(numeros, 50, 60);

	printf("Creo una sublista que incluye los numeros entre los indices 50 y 59 inclusive.\n\n");
	ll_forEach(subLista, printInt);

	if(ll_containsAll(numeros, subLista))
	{
		printf("\n\nLogicamente todos los elementos de la subLista estan incluidos en la lista principal.\n\n");
	}

	numero = (int*) ll_pop(numeros, 20);

	printf("Saco el numero que estaba en el indice 20.'\n\n");

	if (!ll_contains(numeros, numero))
	{
		printf("El numero (%d) ya no esta incluido en la lista.\n\n", *numero);
	}

	printf("Llamo a ll_clear para ambas listas\n\n");
	ll_clear(numeros);
	ll_clear(subLista);

	if(ll_isEmpty(numeros) && ll_isEmpty(subLista))
	{
		printf("Ahora ambas listas estan vacias.\n\n");
	}

	printf("Por ultimo elimino ambas listas.");
	ll_deleteLinkedList(subLista);
	ll_deleteLinkedList(numeros);
	

    return 0;
}


/*
 * UTN_Ingreso.c
 *
 *  Created on: 9 sep. 2021
 *      Author: Julián Zubini
 */
#include <stdio.h>
#include <stdlib.h>
/*
*\ brief La función sirve para desplegar el menú de opciones verificando los valores ingresados y la respuesta del usuario.
*\ param pIngreso: puntero al espacio de memoria donde quiere que se almacene la respuesta del usuario
*\ param banderaPrimerOperando: determina si se ha ingresado el primer operando o no (0 = no se ha ingresado | 1 = valor ingresado)
*\ param banderaSegundoOperando: determina si se ha ingresado el segundo operando o no (0 = no se ha ingresado | 1 = valor ingresado)
*\ param primerOperando: en caso de que se haya ingresado el primer operando, esta variable recibe dicho valor para luego mostrarlo
*\ param segundoOperando: en caso de que se haya ingresado el segundo operando, esta variable recibe dicho valor para luego mostrarlo
*\ return la función es del tipo "void" así que no tiene retorno.
*/
void menuDeOpciones(int* pIngreso, int banderaPrimerOperando, int banderaSegundoOperando, float primerOperando, float segundoOperando){
	int salidaScanf;
	int buffer;
	int intentos = 3;
	printf("----------------------------------------------------------------------------------\n");
	if(banderaPrimerOperando == 0){
		printf("No se ha ingresado primer operando.\n");
	}else{
		printf("Primer operando: %f\n" ,primerOperando);
	}
	if(banderaSegundoOperando == 0){
		printf("No se ha ingresado segundo operando.\n");
	}else{
		printf("Segundo operando: %f\n" ,segundoOperando);
	}
	printf("----------------------------------------------------------------------------------\n");
	printf("Selecciones una de las siguientes opciones matematicas: \n");
	printf("\t1-Ingresar primer operando\n");
	printf("\t2-Ingresar segundo operando\n");
	printf("\t3-Calcular.\n");
	printf("\t4-Mostrar resultados\n");
	printf("\t5-Salir\n");
	salidaScanf = scanf("%d",&buffer);
	while(salidaScanf < 0 || (buffer < 1 || buffer > 6)){
		printf("ERROR, el ingreso es incorrecto. Reingrese a continuacion: ");
		salidaScanf = scanf("%d",&buffer);
		intentos--;
		if(intentos == 0){
			printf("Demasiados intentos, por favor reinicie el programa e intentelo de nuevo.\n");
			exit(-1);
		}
	}
	*pIngreso = buffer;
}

/*
 * brief La función solicita que ingrese un valor al usuario y lo valida.
 * param pIngreso: puntero al espacio de memoria donde quiero que se almacene el valor ingresado.
 * param reintentos: cantidad de intentos que tiene el usuario para ingresar el numero
 * param variableTexto: mensaje que se va a mostrar al usuario indicandole que debe ingresar un numero
 * param textoError: mensaje que se va a mostrar al usuario en caso de que no ingrese correctamente el valor
 * return devuelve el estado del ingreso (0 si ingreso correctamente el valor | 1 si no ingreso correctamente los valores)
 */

int pedirFloatAUsuario(float* pIngreso,int reintentos, char* variableTexto, char* textoError)
{
	float buffer;
	int retorno;
	int i;
	int salidaScanf;
	if(pIngreso != NULL && reintentos >=0 && variableTexto != NULL && textoError != NULL)
	{
		for (i=reintentos; i!=0; i--)
		{
			printf("%s",variableTexto);
			fflush(stdin);
			salidaScanf=scanf("%f", &buffer);
			if (salidaScanf>0)
			{
				retorno = 0; // OK
				*pIngreso=buffer;
				break;
			}
			else
			{
				if(i != 1){
					retorno=1;
					printf("%s\n",textoError);
				}else{
					printf("ERROR, demasiados intentos fallidos. Reinicie el programa.");
					exit(-1);
				}
			}
		}

	}
	return retorno;
}









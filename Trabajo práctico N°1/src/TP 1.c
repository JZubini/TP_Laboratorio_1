/*
 ============================================================================
 Name        : TP.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UTN_Calculadora.h"
#include "UTN_Ingreso.h"

int main(void) {
	setbuf(stdout,NULL);
	float primerOperando;
	float segundoOperando;
	int banderaPrimerOperando = 0;
	int banderaSegundoOperando = 0;
	float resultadoSuma = 0;
	float resultadoResta = 0;
	float resultadoMultiplicacion = 0;
	int estadoDivision;
	float resultadoDivision = 0;
	int estadoFactorial;
	int resultadoFactorialPrimerOperando;
	int resultadoFactorialSegundoOperando;
	int respuestaUsuario;
	menuDeOpciones(&respuestaUsuario,banderaPrimerOperando,banderaSegundoOperando,primerOperando,segundoOperando);
	do{
		switch(respuestaUsuario){
			case 1:
				pedirFloatAUsuario(&primerOperando,3,"Ingrese el primer operando: ", "ERROR, el valor esta afuera de los parámetros. Reingrese: ");
				banderaPrimerOperando = 1;
				break;
			case 2:
				pedirFloatAUsuario(&segundoOperando,3,"Ingrese el segundo operando: ", "ERROR, el valor esta afuera de los parámetros. Reingrese: ");
				banderaSegundoOperando = 1;
				break;
			case 3:
				if(banderaPrimerOperando == 1 && banderaSegundoOperando == 1){
					resultadoSuma = sumaDeNumeros(primerOperando, segundoOperando);
					resultadoResta = restaDeNumeros(primerOperando, segundoOperando);
					resultadoMultiplicacion = multiplicacionDeNumeros(primerOperando, segundoOperando);
					estadoDivision = divisionDeNumeros(primerOperando, segundoOperando,&resultadoDivision);
					estadoFactorial = factorialDeNumeros((int)primerOperando,(int)segundoOperando, &resultadoFactorialPrimerOperando, &resultadoFactorialSegundoOperando);
					printf("¡Exito en la operacion!\n");
				}else{
					printf("Por favor ingrese los dos operando antes de seleccionar esta opcion\n");
				}
				break;
			case 4:
				if(banderaPrimerOperando == 1 && banderaSegundoOperando == 1){
					printf("El resultado de (%f+%f) es: %f\n" ,primerOperando,segundoOperando,resultadoSuma);
					printf("El resultado de (%f-%f) es: %f\n" ,primerOperando,segundoOperando,resultadoResta);
					printf("El resultado de (%f*%f) es: %f\n" ,primerOperando,segundoOperando,resultadoMultiplicacion);
					if(estadoDivision == 1){
						printf("El resultado de (%f/%f) es: %f\n" ,primerOperando,segundoOperando,resultadoDivision);
					}else{
						printf("No es posible dividir por cero\n");
					}
					switch(estadoFactorial){
						case 0:
							printf("Ninguno de los dos numeros ingresados puede ser factorizado porque son numeros negativo.\n");
							break;
						case 1:
							printf("El factorial del primer numero es: %d | El segundo numeros ingresado no puede ser factorizado porque es un numero negativo\n" ,resultadoFactorialPrimerOperando);
							break;
						case 2:
							printf("El primer numeros ingresado no puede ser factorizado porque es un numero negativo | El factorial del segundo numero es: %d\n" ,resultadoFactorialSegundoOperando);
							break;
						case 3:
							printf("El factorial del primer numero es: %d | El factorial del segundo numero es: %d\n" ,resultadoFactorialPrimerOperando,resultadoFactorialSegundoOperando);
							break;
					}
					printf("----------------------------------------------------------------------------------\n");
				}else{
					printf("Por favor ingrese los dos operando antes de seleccionar esta opcion\n");
				}
				break;
				case 5:
					printf("Fin del programa");
					exit(-1);
					break;
			}
		menuDeOpciones(&respuestaUsuario,banderaPrimerOperando,banderaSegundoOperando,primerOperando,segundoOperando);
	}while(respuestaUsuario != 6);
	return EXIT_SUCCESS;
}

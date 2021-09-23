/*
 * calculadora.c
 *
 *  Created on: 9 sep. 2021
 *      Author: Juli�n Zubini
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * brief la funci�n sirve para sumar dos valores
 * param numeroUno: el primer valor ingresado
 * param numeroDos: el segundo valor ingresado
 * return devuelve la suma entre numeroUno y numeroDos
 */

float sumaDeNumeros(float numeroUno, float numeroDos){
	return numeroUno + numeroDos;
}

/*
 * brief la funci�n sirve para restar dos valores
 * param numeroUno: el primer valor ingresado
 * param numeroDos: el segundo valor ingresado
 * return devuelve la resta entre numeroUno y numeroDos
 */

float restaDeNumeros(float numeroUno, float numeroDos){
	return numeroUno - numeroDos;
}

/*
 * brief la funci�n sirve para multiplicar dos valores
 * param numeroUno: el primer valor ingresado
 * param numeroDos: el segundo valor ingresado
 * return devuelve la multiplicaci�n entre numeroUno y numeroDos
 */

float multiplicacionDeNumeros(float numeroUno, float numeroDos){
	return numeroUno * numeroDos;
}

/*
 * brief la funcion verifica que el divisor no sea 0, si ese no fuera el caso realiza la divisi�n.
 * param numeroUno: el primer valor ingresado
 * param numeroDos: el segundo valor ingresado
 * param pResultado: puntero al espacio de memoria donde quiero almacenar el resultado de esa divisi�n
 * return devuelve el estado de la division (1 = se pudo hacer la divison | 0 = no se pudo hacer la divisi�n)
 */

int divisionDeNumeros(float numeroUno, float numeroDos, float* pResultado){
	int estado;
	int resultado;
	if(numeroDos != 0){
		resultado = numeroUno / numeroDos;
		*pResultado = resultado;
		estado = 1;
		return estado;
	}else{
		estado = 0;
	}
	return estado;
}

/*
 * brief la funcion sirve para calcular el factorial de uno o mas numeros ingresados y tambien contempla la posibilidad de que alguno de los dos sea negativo, en ese caso no se puede realizar el factoreo
 * param numeroUno: el primer valor ingresado
 * param numeroDos: el segundo valor ingresado
 * param pResultadoA: puntero al espacio de memoria donde quiero almacenar el resultado de factorizar el primer operando ingresado
 * param pResultadoB: puntero al espacio de memoria donde quiero almacenar el resultado de factorizar el segundo operando ingresado
 * return devuelve el estado del factore (0 = ninguno de los dos n�meros se puede factorizar | 1 = solamente el primer numero se puede factorizar | 2 = solamente el segundo numero se puede factorizar | 3 = ambos numeros se pueden factorizar)
 */

int factorialDeNumeros(float numeroUno,float numeroDos, int* pResultadoA, int* pResultadoB){
	int estado;
	int resultadoA = 1;
	int resultadoB = 1;
	if(numeroUno < 0 && numeroDos < 0){
		// CASO 0: Ninguno de los dos n�meros puede ser factorizado ya que son negativos.
		estado = 0;
		return estado;
	}
	if(numeroUno > 0 && numeroDos < 0){
		// CASO 1: Solamente el primer n�mero puede ser factorizado.
		estado = 1;
	    for(int i = numeroUno;i > 0;i--){
	    	resultadoA *= i;
	    }
	    *pResultadoA = resultadoA;
		return estado;
	}
	if(numeroUno < 0 && numeroDos > 0){
		// CASO 2: Solamente el segundo n�mero puede ser factorizado.
		estado = 2;
		for(int i = numeroDos;i > 0;i--){
			resultadoB *= i;
		}
		*pResultadoB = resultadoB;
		return estado;
	}
	// CASO 3: Ambos numeros pueden ser factorizados.
	estado = 3;
	for(int i = numeroUno;i > 0;i--){
		resultadoA *= i;
	}
	*pResultadoA = resultadoA;
	for(int i = numeroDos;i > 0;i--){
		resultadoB *= i;
	}
	*pResultadoB = resultadoB;
	return estado;
}

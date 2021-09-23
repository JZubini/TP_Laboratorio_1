/*
 * UTN_Ingreso.h
 *
 *  Created on: 9 sep. 2021
 *      Author: Julián Zubini
 */

#ifndef UTN_INGRESO_H_
#define UTN_INGRESO_H_

int pedirFloatAUsuario(float* pResultado,int reintentos, char* variableTexto, char* textoError);
int pedirFloatAUsuarioMinMax(float* pResultado, float min, float max, int reintentos, char* variableTexto, char* textoError);
int pedirIntAUsuario(int* pResultado,int reintentos, char* variableTexto, char* textoError);
int pedirIntAUsuarioMinMax(int* pResultado, int min, int max, int reintentos, char* variableTexto, char* textoError);
int pedirCharAUsuario(char* pResultado,int reintentos, char* variableTexto, char* textoError);
int pedirCharAUsuarioMinMax(char* pResultado, char min, char max, int reintentos, char* variableTexto, char* textoError);
void menuDeOpciones(int* pIngreso, int banderaPrimerOperando, int banderaSegundoOperando,float primerOperando, float SegundoOperando);
#endif /* UTN_INGRESO_H_ */

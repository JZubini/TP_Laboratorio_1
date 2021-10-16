/*
 * menu.c
 *
 *  Created on: 13 oct. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayEmpleados.h"
#include "UTN_Ingreso.h"
#define TRUE 1
#define FALSE 0
#define REINTENTOS 5
#define MIN_RESPUESTA_MENU 1
#define MAX_RESPUESTA_MENU 5
#define MIN_RESPUESTA_MOD_MENU 1
#define MAX_RESPUESTA_MOD_MENU 6
#define MIN_EMPLEADOS 1
#define MAX_EMPLEADOS 1000

/* Brief: la funcion se encarga de generador ID's para cada empleados ingresado, al ser static su valor no se reinicia cada vez que se invoca a la función.
 */

int newID(void){
	static int contador = 1;
	return contador++;
}

void modMenu(Employee* employeeList, int len, int modID);
void finalReport(Employee* employeeList, int len);

/* Brief: la funcion se encarga de mostrar el menú con el que va a interactuar el usuario. El menu se sigue mostrando hasta que el usuario ingresé la opción numero 5 para salir del programa.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 */

void menu(Employee* employeeList, int len){
	int respuestaUsuario;
	int auxID;
	int banderaAltaDeEmpleados = FALSE;
	char auxName[LEN_NAME];
	char auxLastName[LEN_NAME];
	float auxSalary;
	int auxSector;
	int estadoIngresoNombre;
	int estadoIngresoApellido;
	int estadoIngresoSalario;
	int estadoIngresoSector;
	int IDMod;
	int IDBaja;
	int order;
	int estadoIngresoOrden;
	do{
		printf("-------------------------------------------------------------------------------------\n");
		printf("--------------------------------MENU PRINCIPAL---------------------------------------\n");
		printf("Bienvenido, seleccione una de las siguientes opciones: \n");
		printf("\t1-ALTA\n");
		printf("\t2-MODIFICACION\n");
		printf("\t3-BAJA\n");
		printf("\t4-INFORME FINAL\n");
		printf("\t5-SALIR\n");
		if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario,"Ingrese su respuesta: " ,"ERROR, el valor ingresado esta fuera del rango de opciones, reingrese a continuacion: ", MIN_RESPUESTA_MENU, MAX_RESPUESTA_MENU, REINTENTOS) == TRUE){
			switch(respuestaUsuario){
			case 1:
				banderaAltaDeEmpleados = TRUE;
				auxID = newID();
				printf("------------------------ID empleado: %d------------------------\n" ,auxID);
				estadoIngresoNombre = UTN_ingresoTextoReintentos(auxName, LEN_NAME, "Ingrese el nombre del empleado: ", "ERROR, reingrese a continuacion:\n",REINTENTOS);
				estadoIngresoApellido = UTN_ingresoTextoReintentos(auxLastName, LEN_NAME, "Ingrese el apellido del empleado: ", "ERROR, reingrese el apellido a continuacion: ",REINTENTOS);
				estadoIngresoSalario = UTN_ingresoFloatReintentos(&auxSalary, "Ingrese el salario del empleado: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuación: ", REINTENTOS);
				estadoIngresoSector = UTN_ingresoIntReintentos(&auxSector, "Ingrese el sector del empleado: ", "ERROR, el valor es incorrecto, reingrese a continuacion: ", REINTENTOS);
				if(estadoIngresoNombre == TRUE && estadoIngresoApellido == TRUE && estadoIngresoSalario == TRUE && estadoIngresoSector == TRUE){
					if(addEmployees(employeeList, len, auxID, auxName, auxLastName, auxSalary, auxSector) == TRUE){
						printf("Éxito en la operacion!\n");
					}else{
						printf("Ha ocurrido un error inesperado, vuelva al menu e intentelo de nuevo.\n");
					}
				}else{
					printf("Hubo un error en el ingreso de datos, vuelva al menu e intentelo de nuevo.\n");
				}
				break;
			case 2:
				printEmployees(employeeList, len);
				if(banderaAltaDeEmpleados == TRUE){
					if(UTN_ingresoIntReintentosMinMax(&IDMod, "Ingrese la ID del empleado que desea modificar: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ", MIN_EMPLEADOS, MAX_EMPLEADOS, REINTENTOS) == TRUE){
						modMenu(employeeList,len,IDMod);
					}else{
						printf("ERROR en el ingreso del ID, vuelva al menu e intentelo de nuevo\n");
					}
				}else{
					printf("Todavía no se ha realizado ninguna carga de empleados, vuelva al menu y cargue los datos antes de seguir\n");
				}
				break;
			case 3:
				printEmployees(employeeList, len);
				if(banderaAltaDeEmpleados == TRUE){
					if(UTN_ingresoIntReintentosMinMax(&IDBaja, "Ingrese la ID del empleado que desea dar de baja: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ", MIN_EMPLEADOS, MAX_EMPLEADOS, REINTENTOS) == TRUE){
						if(removeEmployee(employeeList,len,IDBaja) == TRUE){
							printf("¡Éxito en la operacion!\n");
						}else{
							printf("Ocurrió un error inesperado al intentar dar de baja al empleado, vuelva al menu e intentelo de nuevo\n");
						}
					}else{
						printf("Hubo un error en el ingreso de datos, vuelva al menu e intentelo de nuevo.\n\n");
					}
				}else{
					printf("Todavía no se ha realizado ninguna carga de empleados, vuelva al menu y cargue los datos antes de seguir\n");
				}
				break;
			case 4:
				if(banderaAltaDeEmpleados == TRUE){
					printf("------------------------1------------------------\n");
					estadoIngresoOrden = UTN_ingresoIntReintentosMinMax(&order, "Ingrese el orden de apellidos (0 - Descendente | 1 - Ascendente): ", "ERROR, el valor es incorrecto, reingrese a continuacion: ", 0,1,REINTENTOS);
					if(estadoIngresoOrden == FALSE){
						printf("ERROR en el ingreso de datos, vuelva al menú e intentelo de nuevo.");
					}else{
						sortEmployees(employeeList,len, order);
						printEmployees(employeeList, len);
						printf("------------------------2------------------------\n");
						finalReport(employeeList,len);
					}
				}else{
					printf("Todavía no se ha realizado ninguna carga de empleados, vuelva al menu y cargue los datos antes de seguir\n");
				}
				break;
			case 5:
				printf("Fin del programa.");
				break;
			}
		}else{
			printf("Ha ingresado demasiados valores incorrectos, vuelva a intentarlo dentro de unos minutos.\n");
		}
	}while(respuestaUsuario != 5);
}

/* Brief: la funcion se encarga de mostrar un menu para la modificación de datos sobre un empleado. El menú se repite hasta que el usuario ingresa la opción 6 para salir del programa.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param modID: ID del empleado que se desea modificar sus datos.
 */


void modMenu(Employee* employeeList, int len, int modID){
	int indexMod;
	int respuestaUsuario;
	char auxName[LEN_NAME];
	char auxLastName[LEN_NAME];
	indexMod = findEmployeeById(employeeList,len, modID);
	do{
		printf("-------------------------------------------------------------------------------------\n");
		printf("-----------------------------MENU DE MODIFICACIONES----------------------------------\n");
		printf("¿Que dato desea modificar?\n");
		printf("\t1-ID\n");
		printf("\t2-Nombre\n");
		printf("\t3-Apellido\n");
		printf("\t4-Salario\n");
		printf("\t5-Sector\n");
		printf("\t6-Salir\n");
		if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario,"Ingrese su respuesta: ","ERROR, el numero ingresado no coincide con ninguno del menu", MIN_RESPUESTA_MOD_MENU, MAX_RESPUESTA_MOD_MENU, REINTENTOS) == TRUE){
			switch(respuestaUsuario){
				case 1:
					if(UTN_ingresoIntReintentosMinMax(&employeeList[indexMod].id,"Ingrese el nuevo ID: \n","ERROR, reingrese el valor\n",MIN_EMPLEADOS,MAX_EMPLEADOS,REINTENTOS)){
						printf("Éxito en la modificación!\n");
					}else{
						printf("Hubo un error inesperado en la modificación, por favor intentelo de nuevo.\n");
					}
					break;
				case 2:
					if(UTN_ingresoTextoReintentos(auxName,LEN_NAME,"Ingrese el nombre del empleado: \n","ERROR, reingrese el nombre: \n",REINTENTOS)){
						strcpy(employeeList[indexMod].name,auxName);
						printf("Éxito en la modificación!\n");
					}else{
						printf("Hubo un error inesperado en la modificación, por favor intentelo de nuevo.\n");
					}
					break;
				case 3:
					if(UTN_ingresoTextoReintentos(auxLastName,LEN_NAME,"Ingrese el apellido del empleado: \n","ERROR, reingrese el apellido: \n",REINTENTOS)){
						strcpy(employeeList[indexMod].lastName,auxLastName);
						printf("Éxito en la modificación!\n");
					}else{
						printf("Hubo un error inesperado en la modificación, por favor intentelo de nuevo.\n");
					}
					break;
				case 4:
					if(UTN_ingresoFloatReintentos(&employeeList[indexMod].salary,"Ingrese el nuevo salario del empleado: \n","ERROR, reingrese el valor\n",REINTENTOS)){
						printf("Éxito en la modificación!\n");
					}else{
						printf("Hubo un error inesperado en la modificación, por favor intentelo de nuevo.\n");
					}
					break;
				case 5:
					if(UTN_ingresoIntReintentos(&employeeList[indexMod].sector,"Ingrese el nuevo sector del empleado: \n","ERROR, reingrese el valor\n",REINTENTOS)){
						printf("Éxito en la modificación!\n");
					}else{
						printf("Hubo un error inesperado en la modificación, por favor intentelo de nuevo.\n");
					}
					break;
				case 6:
					printf("¡Fin de las modificaciones!\n");
					break;
			}
		}else{
			printf("Ha ingresado demasiados valores incorrectos, vuelva a intentarlo dentro de unos minutos.\n");
		}
	}while(respuestaUsuario != 6);
}

/* Brief: la funcion se encarga de calcular el promedio de sueldos y contar cuantos de ellos superan dicho promedio.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 */

void finalReport(Employee* employeeList, int len){
	float acumuladorDeSueldos = 0;
	int contadorDeEmpleados = 0;
	float promedioDeSueldos;
	int contadorDeEmpleadosQueSuperanElPromedio = 0;
	for(int i = 0;i<= len;i++){
		if(employeeList[i].isEmpty == FALSE){
			acumuladorDeSueldos += employeeList[i].salary;
			contadorDeEmpleados++;
		}
	}
	promedioDeSueldos = acumuladorDeSueldos / contadorDeEmpleados;
	printf("Promedio de sueldos: %f\n" ,promedioDeSueldos);
	for(int x = 0;x<= len;x++){
		if(employeeList[x].isEmpty == FALSE){
			if(employeeList[x].salary > promedioDeSueldos){
				contadorDeEmpleadosQueSuperanElPromedio++;
			}
		}
	}
	printf("Contador de empleados que superan el promedio: %d\n" ,contadorDeEmpleadosQueSuperanElPromedio);
}

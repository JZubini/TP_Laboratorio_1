/*
 * funciones.c
 *
 *  Created on: 28 sep. 2021
 *      Author: Julián Zubini
 */

#include "arrayEmpleados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UTN_Ingreso.h"
#define TRUE 1
#define FALSE 0
#define LEN_NAME 51
#define REINTENTOS 5

void printEmployees(Employee* employeeList,int len);
int initEmployees(Employee* employeeList,int len);

/* Brief: la funcion se encarga de devolver un contador con la cantidad de empleados activos
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 */


int activeEmployeeCount(Employee* employeeList, int len){
	int contadorDeEmpleadosActivos = 0;
	for(int i = 0;i<= len;i++){
		if(employeeList[i].isEmpty == FALSE){
			contadorDeEmpleadosActivos++;
		}
	}
	return contadorDeEmpleadosActivos;
}

/* Brief: la funcion se encarga de verificar en que orden desea ordenar los empleados según el usuario y luego procede a ordenarlos de forma ascendente o descendente.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param order: determina en que forma se ordena el array (0 - Descendente | 1 - Ascendente)
 */

int sortEmployees(Employee* employeeList,int len,int order){
	int retorno = TRUE;
	int flagSwap;
	int auxID;
	char auxName[LEN_NAME];
	char auxLastName[LEN_NAME];
	float auxSalary;
	int auxSector;
	switch(order){
		case 0:
			do{
				flagSwap=FALSE;
				for(int i = 0;i<len-1;i++){
					if(employeeList[i].isEmpty == FALSE && employeeList[i+1].isEmpty == FALSE){
						if(strcmp(employeeList[i].lastName,employeeList[i+1].lastName) < 0){
							flagSwap = TRUE;
							auxID = employeeList[i].id;
							strcpy(auxName,employeeList[i].name);
							strcpy(auxLastName,employeeList[i].lastName);
							auxSalary = employeeList[i].salary;
							auxSector = employeeList[i].sector;

							employeeList[i].id = employeeList[i+1].id;
							strcpy(employeeList[i].name,employeeList[i+1].name);
							strcpy(employeeList[i].lastName,employeeList[i+1].lastName);
							employeeList[i].salary = employeeList[i+1].salary;
							employeeList[i].sector = employeeList[i+1].sector;

							employeeList[i+1].id = auxID;
							strcpy(employeeList[i+1].name,auxName);
							strcpy(employeeList[i+1].lastName,auxLastName);
							employeeList[i+1].salary = auxSalary;
							employeeList[i+1].sector = auxSector;
						}
						if(strcmp(employeeList[i].lastName,employeeList[i+1].lastName) == 0){
							if(employeeList[i].sector < employeeList[i+1].sector){
								flagSwap = TRUE;
								auxID = employeeList[i].id;
								strcpy(auxName,employeeList[i].name);
								strcpy(auxLastName,employeeList[i].lastName);
								auxSalary = employeeList[i].salary;
								auxSector = employeeList[i].sector;

								employeeList[i].id = employeeList[i+1].id;
								strcpy(employeeList[i].name,employeeList[i+1].name);
								strcpy(employeeList[i].lastName,employeeList[i+1].lastName);
								employeeList[i].salary = employeeList[i+1].salary;
								employeeList[i].sector = employeeList[i+1].sector;

								employeeList[i+1].id = auxID;
								strcpy(employeeList[i+1].name,auxName);
								strcpy(employeeList[i+1].lastName,auxLastName);
								employeeList[i+1].salary = auxSalary;
								employeeList[i+1].sector = auxSector;
							}
						}
					}
				}
			}while(flagSwap==TRUE);
			break;
		case 1:
			do{
				flagSwap=FALSE;
				for(int x = 0;x<len-1;x++){
					if(employeeList[x].isEmpty == FALSE && employeeList[x+1].isEmpty == FALSE){
						if(strcmp(employeeList[x].lastName,employeeList[x+1].lastName) > 0){
							flagSwap = TRUE;
							auxID = employeeList[x].id;
							strcpy(auxName,employeeList[x].name);
							strcpy(auxLastName,employeeList[x].lastName);
							auxSalary = employeeList[x].salary;
							auxSector = employeeList[x].sector;

							employeeList[x].id = employeeList[x+1].id;
							strcpy(employeeList[x].name,employeeList[x+1].name);
							strcpy(employeeList[x].lastName,employeeList[x+1].lastName);
							employeeList[x].salary = employeeList[x+1].salary;
							employeeList[x].sector = employeeList[x+1].sector;

							employeeList[x+1].id = auxID;
							strcpy(employeeList[x+1].name,auxName);
							strcpy(employeeList[x+1].lastName,auxLastName);
							employeeList[x+1].salary = auxSalary;
							employeeList[x+1].sector = auxSector;
						}
						if(strcmp(employeeList[x].lastName,employeeList[x+1].lastName) == 0){
							if(employeeList[x].sector > employeeList[x+1].sector){
								flagSwap = TRUE;
								auxID = employeeList[x].id;
								strcpy(auxName,employeeList[x].name);
								strcpy(auxLastName,employeeList[x].lastName);
								auxSalary = employeeList[x].salary;
								auxSector = employeeList[x].sector;

								employeeList[x].id = employeeList[x+1].id;
								strcpy(employeeList[x].name,employeeList[x+1].name);
								strcpy(employeeList[x].lastName,employeeList[x+1].lastName);
								employeeList[x].salary = employeeList[x+1].salary;
								employeeList[x].sector = employeeList[x+1].sector;

								employeeList[x+1].id = auxID;
								strcpy(employeeList[x+1].name,auxName);
								strcpy(employeeList[x+1].lastName,auxLastName);
								employeeList[x+1].salary = auxSalary;
								employeeList[x+1].sector = auxSector;
							}
						}
					}
				}
		}while(flagSwap==TRUE);
		break;
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar un index disponible donde cargar los datos del empleado
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param pIndex: variable puntero que pretende retornar un index libre en el array.
 */

int findFreeEmployeeIndex(Employee* employeeList,int len,int* pIndex){
	int retorno = FALSE;
	if(employeeList != NULL && len > 0){
		for(int i = 0;i<= len;i++){
			if(employeeList[i].isEmpty == TRUE){
				*pIndex = i;
				retorno = TRUE;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de inicializar todas las variables "isEmpty" del array en TRUE, permitiendo así saber si hay datos cargados o no
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 */

int initEmployees(Employee* employeeList,int len){
	int retorno = FALSE;
	if(employeeList != NULL && len > 0){
		for(int i = 0;i<= len;i++){
			employeeList[i].isEmpty = TRUE;
			retorno = TRUE;
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de cargar los datos pasados por paramétro dentro del array.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param ID: numero ID del empleado.
 * Param name: nombre del empleado.
 * Param lastName: apellido del empleado
 * Param salary: salario del empleado
 * Param sector: sector del empleado
 */

int addEmployees(Employee* employeeList, int len, int id, char name[],char lastName[],float salary, int sector){
	int indexFree;
	int retorno = FALSE;
	if(findFreeEmployeeIndex(employeeList, len,&indexFree) == TRUE){
		if(employeeList != NULL && len > 0 && id >= 0 && name != NULL && lastName != NULL && salary > 0){
			employeeList[indexFree].id = id;
			strcpy(employeeList[indexFree].name,name);
			strcpy(employeeList[indexFree].lastName,lastName);
			employeeList[indexFree].salary = salary;
			employeeList[indexFree].sector = sector;
			employeeList[indexFree].isEmpty = FALSE;
			retorno = TRUE;
		}
	}else{
		printf("Se ha alcanzado la capacidad máxima de empleados.\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de buscar el index de un empleado mediante su ID, comparando con todas las del array hasta que encuentre a que index le pertenece.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param ID: numero ID del empleado a encontrar.
 */

int findEmployeeById(Employee* employeeList,int len, int ID){
	int retorno = -1;
	if(employeeList != NULL && len > 0 && ID > -1){
		for(int i = 0;i<= len;i++){
			if(employeeList[i].id == ID){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de hacer la baja lógica de un empleado mediante la ID ingresada por el usuario
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 * Param ID: numero ID del empleado a dar de baja.
 */

int removeEmployee(Employee* employeeList,int len, int ID){
	int index;
	int retorno = FALSE;
	index = findEmployeeById(employeeList, len, ID);
	if(index != -1){
		employeeList[index].isEmpty = TRUE;
		retorno = TRUE;
	}
	return retorno;
}

/* Brief: la función imprime el array de empleados con sus respectivos datos ingresados siempre y cuando haya algún valor cargado.
 * Param employeeList: lista de empleados
 * Param len: tamaño del array
 */
void printEmployees(Employee* employeeList,int len){
	for(int i=0;i<=len;i++){
		if(employeeList[i].isEmpty == FALSE){
			printf("-------------------------------------------------------------------------------------\n");
			printf("ID empleado: %d\n" ,employeeList[i].id);
			printf("Nombre del empleado: %s\n" ,employeeList[i].name);
			printf("Apellido del empleado: %s\n" ,employeeList[i].lastName);
			printf("Salario del empleado: %f\n" ,employeeList[i].salary);
			printf("Sector del empleado: %d\n" ,employeeList[i].sector);
			printf("-------------------------------------------------------------------------------------\n");
		}
	}
}




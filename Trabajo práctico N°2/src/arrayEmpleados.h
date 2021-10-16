/*
 * funciones.h
 *
 *  Created on: 28 sep. 2021
 *      Author: Julián Zubini
 */

#ifndef ARRAYEMPLEADOS_H_
#define ARRAYEMPLEADOS_H_
#include <stdio.h>
#include <stdlib.h>
#define LEN_EMPLOYEES 1000
#define LEN_NAME 51

typedef struct{
	int id;
	char name[LEN_NAME];
	char lastName[LEN_NAME];
	float salary;
	int sector;
	int isEmpty;
}Employee;


int initEmployees(Employee* employeeList,int len);
int addEmployees(Employee* employeeList, int len, int id, char name[],char lastName[],float salary, int sector);
int findEmployeeById(Employee* employeeList,int len, int ID);
int removeEmployee(Employee* employeeList,int len, int ID);
void printEmployees(Employee* employeeList,int len);
int sortEmployees(Employee* employeeList,int len,int order);
#endif /* ARRAYEMPLEADOS_H_ */

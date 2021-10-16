/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "arrayEmpleados.h"
#include "menu.h"
#define LEN_EMPLOYEES 1000

int main(void) {
	setbuf(stdout,NULL);
	Employee employeeList[LEN_EMPLOYEES];
	initEmployees(employeeList,LEN_EMPLOYEES);
	menu();
	return EXIT_SUCCESS;
}

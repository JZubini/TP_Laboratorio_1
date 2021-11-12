

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "LinkedList.h"
#include "UTN_Ingreso.h"

#define TRUE 1
#define FALSE 0

Employee* employee_new(){
	Employee* pEmployee = malloc(sizeof(Employee));
	return pEmployee;
}

void employee_delete(Employee* this){
	if(this != NULL){
		free(this);
	}
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr){
	int auxID;
	int auxHorasTrabajadas;
	float auxSueldo;
	Employee* retornoAuxEmployee;
	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL){
		if(UTN_validarNumeroEnteroIngresado(idStr) == TRUE && UTN_validarNumeroEnteroIngresado(horasTrabajadasStr) == TRUE && UTN_validarNumeroEnteroIngresado(sueldoStr) == TRUE && UTN_validarCadenaAlfabeticaIngresada(nombreStr) == TRUE){
			auxID = atoi(idStr);
			auxHorasTrabajadas = atoi(horasTrabajadasStr);
			auxSueldo = atof(sueldoStr);
			retornoAuxEmployee = employee_new();
			if(retornoAuxEmployee != NULL){
				employee_setId(retornoAuxEmployee, auxID);
				employee_setNombre(retornoAuxEmployee, nombreStr);
				employee_setHorasTrabajadas(retornoAuxEmployee,auxHorasTrabajadas);
				employee_setSueldo(retornoAuxEmployee,auxSueldo);
			}
		}else{
			retornoAuxEmployee = NULL;
		}
	}
	return retornoAuxEmployee;
}

int employee_setId(Employee* this,int id){
	int retorno = FALSE;
	if(this != NULL && id >= 0){
		this->id = id;
		retorno = TRUE;
	}
	return retorno;
}

int employee_getId(Employee* this,int* id){
	int retorno = FALSE;
	if(this != NULL && id != NULL){
		*id = this->id;
		retorno = TRUE;
	}
	return retorno;
}

int employee_setNombre(Employee* this,char* nombre){
	int retorno = FALSE;
	if(this != NULL && nombre != NULL){
		strcpy(this->nombre,nombre);
		retorno = TRUE;
	}
	return retorno;
}

int employee_getNombre(Employee* this,char* nombre){
	int retorno = FALSE;
	if(this != NULL && nombre != NULL){
		strcpy(nombre,this->nombre);
		retorno = TRUE;
	}
	return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas){
	int retorno = FALSE;
	if(this != NULL && horasTrabajadas >= 0){
		this->horasTrabajadas = horasTrabajadas;
		retorno = TRUE;
	}
	return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas){
	int retorno = FALSE;
	if(this != NULL && horasTrabajadas >= 0){
		*horasTrabajadas = this->horasTrabajadas;
		retorno = TRUE;
	}
	return retorno;
}

int employee_setSueldo(Employee* this,int sueldo){
	int retorno = FALSE;
	if(this != NULL && sueldo >= 0){
		this->sueldo = sueldo;
		retorno = TRUE;
	}
	return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo){
	int retorno = FALSE;
	if(this != NULL && sueldo >= 0){
		*sueldo = this->sueldo;
		retorno = TRUE;
	}
	return retorno;
}

int employee_findById(LinkedList *pArrayListEmployee,int id){
	int retorno = -1;
	int tamanoLista;
	if(id>=0 && pArrayListEmployee!=NULL){
		tamanoLista = ll_len(pArrayListEmployee);
		for(int i=0;i<tamanoLista;i++){
			Employee* pAuxiliarEmpleado=ll_get(pArrayListEmployee, i);
			if(id == pAuxiliarEmpleado->id){
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}


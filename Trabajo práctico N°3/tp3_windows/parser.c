#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#define TRUE 1
#define FALSE 0

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee){
	Employee* pEempleadoAuxiliar;
	int retorno = FALSE;
	if(pFile != NULL && pArrayListEmployee != NULL){
		char id[256];
		char nombre[256];
		char horas[256];
		char sueldo[256];
		if(pFile!=NULL){
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horas,sueldo); // salteo la 1era
			do{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horas,sueldo)==4){
					pEempleadoAuxiliar = employee_newParametros(id,nombre,horas,sueldo);
					if(pEempleadoAuxiliar != NULL){
						ll_add(pArrayListEmployee,pEempleadoAuxiliar);
						retorno = TRUE;
					}else{
						employee_delete(pEempleadoAuxiliar);
						break;
					}
				}
			}while(feof(pFile) == 0);
		}
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee){
    Employee* pEmpleadoAuxiliar;
    int retorno = FALSE;
    if(pFile != NULL && pArrayListEmployee != NULL){
        do{
        	pEmpleadoAuxiliar = employee_new();
            if(fread(pEmpleadoAuxiliar,sizeof(Employee),1,pFile) == 1){
                ll_add(pArrayListEmployee,pEmpleadoAuxiliar);
                retorno = TRUE;
            }else{
                employee_delete(pEmpleadoAuxiliar);
                break;
            }
        }while(feof(pFile) == 0);
    }
    return retorno;
}

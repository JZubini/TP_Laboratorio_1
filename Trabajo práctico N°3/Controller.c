#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "UTN_Ingreso.h"
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAM 128
#define REINTENTOS 5
#define MIN_MOD_MENU 1
#define MAX_MOD_MENU 4
#define MIN_EMPLEADOS 1
#define MIN_MENU 1
#define MAX_MENU 10

/** \brief La función se encarga de comparar los datos recibidos por parámetro.
 *
 * \param pFirstEmployee puntero a los datos de un empleado
 * \param pSecondEmployee puntero a los datos de un empleado
 * \return int Devuelve TRUE si se debe hacer un swap o FALSE si sucede lo contrario.
 *
 */

int compareEmployees(Employee* pFirstEmployee,Employee* pSecondEmployee,int orden){
	int retornoSwap = FALSE;
	char auxNombreUno[TAM];
	char auxNombreDos[TAM];
	if(pFirstEmployee != NULL && pSecondEmployee != NULL && orden > 0){
		employee_getNombre(pFirstEmployee, auxNombreUno);
		employee_getNombre(pSecondEmployee, auxNombreDos);
		switch(orden){
			case 1:
				if(strcmp(auxNombreUno,auxNombreDos) > 0){
					retornoSwap = TRUE;
				}
				break;
			case 2:
				if(strcmp(auxNombreUno,auxNombreDos) < 0){
					retornoSwap = TRUE;
				}
				break;
		}
	}
	return retornoSwap;
}

/** \brief La función se encarga de contar la cantidad de datos en los archivos para llevar un control de cual es la última ID registrada.
 *
 * \param pArrayListEmployee lista de punteros
 * \return int Devuelve el contador de datos registrados en el archivo.
 *
 */

int controller_dataCount(LinkedList* pArrayListEmployee){
	static int contador;
	FILE* file = fopen("data.csv","r");
	char id[256];
	char nombre[256];
	char horas[256];
	char sueldo[256];
	if(pArrayListEmployee != NULL){
	fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horas,sueldo); // salteo la 1era
	do{
		if(fscanf(file,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horas,sueldo)==4){
			contador++;
		}
	}while(feof(file) == 0);
	}
	return contador;
}

/** \brief La función se encarga de desplegar y utilizar un menú de modificaciones para los datos del empleado.
 *
 * \param respuestaUsuario contiene la respuesta ingresada por el usuario para usarla en el switch.
 * \param employeeMod puntero con la dirección de memoria a los datos que queremos modificar.
 * \return int Retorna true si los parámetros son correctos o false en caso contrario.
 *
 */

int controller_modMenu(int respuestaUsuario,Employee* employeeMod){
	char auxiliarNombre[TAM];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	int estadoIngresoNombre;
	int estadoIngresoHorasTrabajadas;
	int estadoIngresoSueldo;
	int retorno = FALSE;
	if(respuestaUsuario > 0 && employeeMod != NULL){
		retorno = TRUE;
		switch(respuestaUsuario){
			case 1:
				estadoIngresoNombre = UTN_ingresoTextoReintentos(auxiliarNombre, TAM, "Ingrese el nuevo nombre del empleado: ", "El valor ingresado es incorrecto, reingrese: ", REINTENTOS);
				if(estadoIngresoNombre == TRUE){

					employee_setNombre(employeeMod, auxiliarNombre);
					puts("¡Exito en la operación!\n");
				}else{
					puts("Hubo un error inesperado en la modificación, vuelva al menu e intentelo nuevamente.\n");
				}
				break;
			case 2:
				estadoIngresoHorasTrabajadas = UTN_ingresoIntReintentos(&auxiliarHorasTrabajadas, "Ingrese la nueva cantidad de horas trabajadas: ", "El valor ingresado es incorrecto, reingrese: ",REINTENTOS);
				if(estadoIngresoHorasTrabajadas == TRUE){
					employee_setHorasTrabajadas(employeeMod, auxiliarHorasTrabajadas);
					puts("¡Exito en la operación!\n");
				}else{
					puts("Hubo un error inesperado en la modificación, vuelva al menu e intentelo nuevamente.\n");
				}
				break;
			case 3:
				estadoIngresoSueldo = UTN_ingresoIntReintentos(&auxiliarSueldo, "Ingrese el nuevo sueldo: ", "El valor ingresado es incorrecto, reingrese: ",REINTENTOS);
				if(estadoIngresoSueldo == TRUE){
					employee_setSueldo(employeeMod, auxiliarSueldo);
					puts("¡Exito en la operación!\n");
				}else{
					puts("Hubo un error inesperado en la modificación, vuelva al menu e intentelo nuevamente.\n");
				}
				break;
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	if(path != NULL && pArrayListEmployee != NULL){
		FILE* file = fopen(path,"r");
		if(file != NULL){
			parser_EmployeeFromText(file, pArrayListEmployee);
			fclose(file);
			retorno = TRUE;
		}else{
			printf("ERROR, no se ha podido abrir el archivo: %s",path);
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	if(path != NULL && pArrayListEmployee != NULL){
		FILE* file = fopen(path,"rb");
		if(file != NULL){
			parser_EmployeeFromBinary(file, pArrayListEmployee);
			fclose(file);
			retorno = TRUE;
		}else{
			printf("ERROR, no se ha podido abrir el archivo: %s",path);
		}
	}
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	static int variable = 1;
	int auxiliarID;
	char nuevaID[TAM];
	char auxiliarNombre[TAM];
	char auxiliarHorasTrabajadas[TAM];
	char auxiliarSueldo[TAM];
	int estadoIngresoNombre;
	int estadoIngresoHorasTrabajadas;
	int estadoIngresoSueldo;
	Employee* pEmpleadoAuxiliar;
	if(pArrayListEmployee != NULL){
		auxiliarID = controller_dataCount(pArrayListEmployee) + variable;
		variable++;
		sprintf(nuevaID,"%d",auxiliarID);
		printf("------------------------ ID: %d ------------------------\n" ,auxiliarID);
		estadoIngresoNombre = UTN_ingresoTextoReintentos(auxiliarNombre, TAM, "Ingrese el nombre del empleado a continuacion: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		estadoIngresoHorasTrabajadas = UTN_ingresoTextoReintentos(auxiliarHorasTrabajadas,TAM, "Ingrese la cantidad de horas trabajadas del empleado: ","ERROR, el valor ingresado es incorrecto, reingrese: ",REINTENTOS);
		estadoIngresoSueldo = UTN_ingresoTextoReintentos(auxiliarSueldo,TAM, "Ingrese el sueldo del empleado: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		if(estadoIngresoNombre == TRUE && estadoIngresoHorasTrabajadas == TRUE && estadoIngresoSueldo == TRUE){
			pEmpleadoAuxiliar = employee_newParametros(nuevaID, auxiliarNombre, auxiliarHorasTrabajadas, auxiliarSueldo);
			if(pEmpleadoAuxiliar != NULL){
				ll_add(pArrayListEmployee,pEmpleadoAuxiliar);
				retorno = TRUE;
				puts("¡Exito en la operacion!\n");
			}else{
				puts("Ha ocurrido un error inesperado en la carga de datos, vuelva al menú e intentelo nuevamente.\n");
			}
		}else{
			puts("Ha ocurrido un error inesperado en el ingreso de datos, vuelva al menú y cargue los datos nuevamente.");
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	int modID;
	int maximoEmpleadosCargados;
	int respuestaUsuario;
	int indiceMod;
	Employee* employeeMod;
	if(pArrayListEmployee != NULL){
		maximoEmpleadosCargados = controller_dataCount(pArrayListEmployee);
		puts("--------------------- MENU DE MODIFICACIONES ---------------------\n");
		puts("Bienvenido al menu de modificaciones.\n");
		if(UTN_ingresoIntReintentosMinMax(&modID, "Ingrese la ID del empleado del que desea modificar sus datos:", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_EMPLEADOS, maximoEmpleadosCargados, REINTENTOS) == TRUE){
			indiceMod = employee_findById(pArrayListEmployee, modID);
			if(indiceMod != -1){
				employeeMod = ll_get(pArrayListEmployee,indiceMod);
				if(employeeMod != NULL){
					do{
						printf("--------------------- ID seleccionada: %d ---------------------\n" ,modID);
						puts("Seleccione una de las siguientes opciones:\n");
						puts("\t1 - Modificar el nombre");
						puts("\t2 - Modificar la cantidad de horas trabajadas");
						puts("\t3 - Modificar el sueldo");
						puts("\t4 - Salir del menú.");
						if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario, "Ingrese su respuesta: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_MOD_MENU, MAX_MOD_MENU, REINTENTOS) == TRUE){
							controller_modMenu(respuestaUsuario,employeeMod);
							retorno = TRUE;
						}else{
							puts("Demasiados intentos en el ingreso de opción, vuelva al menú e intentelo nuevamente\n");
						}
					}while(respuestaUsuario != 4);
				}
			}else{
				puts("No se ha podido encontrar la ID solicitada, vuelva al menú e intentelo nuevamente\n");
			}
		}else{
			puts("Ha ocurrido un error en el ingreso de ID, vuelva al menú e intentelo nuevamente\n");
		}
	}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	int bajaID;
	int maximoEmpleadosCargados;
	int indiceBaja;
	maximoEmpleadosCargados = controller_dataCount(pArrayListEmployee);
	Employee* employeeDown;
	if(pArrayListEmployee != NULL){
		if(UTN_ingresoIntReintentosMinMax(&bajaID, "Ingrese la ID del empleado del que desea dar de baja:", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_EMPLEADOS, maximoEmpleadosCargados, REINTENTOS) == TRUE){
			indiceBaja = employee_findById(pArrayListEmployee, bajaID);
			if(indiceBaja != -1){
				employeeDown = ll_get(pArrayListEmployee,indiceBaja);
				if(employeeDown != NULL){
					free(employeeDown);
					ll_remove(pArrayListEmployee,indiceBaja);
					puts("¡Exito en la operacion!\n");
					retorno = TRUE;
				}else{
					puts("Ha ocurrido un error inesperado en la busqueda del empleado, vuelva al menú e intentelo nuevamente.\n");
				}
			}else{
				puts("No se ha podido encontrar al empleado con la ID solicitada, vuelva al menú e intentelo nuevamente.\n");
			}
		}else{
			puts("Demasiados intentos fallidos, vuelva al menú e intentelo nuevamente");
		}
	}
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = FALSE;
	int tamanoLista;
	if(pArrayListEmployee != NULL){
		tamanoLista = ll_len(pArrayListEmployee);
		for(int i = 0;i<tamanoLista;i++){
			Employee* pAuxiliarEmpleado = ll_get(pArrayListEmployee,i);
			printf("-----------------------------------\n");
			printf("ID empleado: %d\n",pAuxiliarEmpleado->id);
			printf("Nombre: %s\n",pAuxiliarEmpleado->nombre);
			printf("Horas trabajadas: %d\n",pAuxiliarEmpleado->horasTrabajadas);
			printf("Sueldo: %d\n",pAuxiliarEmpleado->sueldo);
			puts("-----------------------------------\n");
			retorno = TRUE;
		}
	}
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleadoAuxiliar;
	Employee* pEmpleadoAuxiliarDos;
	Employee* pEmpleadoAuxiliarTres;
	int flagSwap;
	int tamanoLista;
	int retorno = FALSE;
	int respuestaUsuario;
	int estadoRespuestaUsuario;
	tamanoLista = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL){
		puts("¿En que orden desea ordenar a los empleados? 1 - Ascendente | 2 - Descendente");
		estadoRespuestaUsuario = UTN_ingresoIntReintentosMinMax(&respuestaUsuario, "Ingrese su respuesta: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", 1, 2, REINTENTOS);
		if(estadoRespuestaUsuario == TRUE){
			do{
				flagSwap = FALSE;
				for(int i=0; i<tamanoLista-1; i++)
				{
					pEmpleadoAuxiliar = ll_get(pArrayListEmployee,i);
					pEmpleadoAuxiliarDos = ll_get(pArrayListEmployee,i+1);
					if(compareEmployees(pEmpleadoAuxiliar, pEmpleadoAuxiliarDos,respuestaUsuario) == TRUE){
						flagSwap = TRUE;
						pEmpleadoAuxiliarTres = pEmpleadoAuxiliar;
						ll_set(pArrayListEmployee, i, pEmpleadoAuxiliarDos);
						ll_set(pArrayListEmployee, i+1, pEmpleadoAuxiliarTres);
						retorno = TRUE;
					}
				}
			}while(flagSwap == TRUE);
		}else{
			puts("Demasiados intentos fallidos, vuelva al menu e intentelo de nuevo.");
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	  FILE* file = fopen(path,"w");
	  Employee* pEmpleadoAuxiliar;
	  int tamanoLista;
	  int retorno = FALSE;
	  if(path != NULL && pArrayListEmployee != NULL){
		  if(file != NULL)
		  {
			  fprintf(file,"id,nombre,horasTrabajadas,sueldo\n");
			  tamanoLista = ll_len(pArrayListEmployee);
			  for(int i=0; i<tamanoLista; i++)
			  {
				  pEmpleadoAuxiliar = ll_get(pArrayListEmployee,i);
				  if(fprintf(file,"%d,%s,%d,%d\n",pEmpleadoAuxiliar->id,pEmpleadoAuxiliar->nombre,pEmpleadoAuxiliar->horasTrabajadas,pEmpleadoAuxiliar->sueldo) > 0){
					  retorno = TRUE;
				  }

			  }
			  fclose(file);
		  }
	  }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* file = fopen(path,"wb");
	int tamanoLista;
	int retorno = FALSE;
	int i;
	if(file != NULL){
		tamanoLista = ll_len(pArrayListEmployee);
		for(i = 0;i<tamanoLista+1;i++){
			fwrite(ll_get(pArrayListEmployee,i),sizeof(Employee),1,file);
			retorno = TRUE;
		}
	}
	fclose(file);
    return retorno;
}


void mainMenu(void){
	LinkedList* listaEmpleados = ll_newLinkedList();
	int respuestaUsuario;
	int banderaCargaDatosTexto = FALSE;
	int banderaCargaDatosBinario = FALSE;
	do{
		puts("----------------------------------------------------------------------------------\n");
		printf("Bienvenido al menú, seleccione una de las siguientes opciones:\n");
		puts("\t1 - Cargar los datos de los empleados desde el archivo data.csv (modo texto).");
		puts("\t2 - Cargar los datos de los empleados desde el archivo data.txt (modo binario).");
		puts("\t3 - Alta de empleados");
		puts("\t4 - Modificar empleado");
		puts("\t5 - Baja empleado");
		puts("\t6 - Listar empleados");
		puts("\t7 - Ordenar empleados");
		puts("\t8 - Guardar los datos de los empleados en el archivo data.csv (modo texto)");
		puts("\t9 - Guardar los datos de los empleados en el archivo data.txt (modo binario)");
		puts("\t10 - Salir del programa");
			UTN_ingresoIntReintentosMinMax(&respuestaUsuario,"Ingrese una opción del menu: ","ERROR, el valor ingresado es incorrecto, reingrese: ",MIN_MENU,MAX_MENU,REINTENTOS);
			switch(respuestaUsuario) {
				case 1:
					if(controller_loadFromText("data.csv", listaEmpleados) == TRUE){
						puts("¡Exito en la operacion!");
						banderaCargaDatosTexto = TRUE;
					}
					break;
				case 2:
					if(controller_loadFromBinary("data.txt", listaEmpleados) == TRUE){
						banderaCargaDatosBinario = TRUE;
					}
					break;
				case 3:
					if(banderaCargaDatosTexto == TRUE || banderaCargaDatosBinario == TRUE){
						controller_addEmployee(listaEmpleados);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 4:
					if(banderaCargaDatosTexto == TRUE || banderaCargaDatosBinario == TRUE){
						controller_editEmployee(listaEmpleados);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 5:
					if(banderaCargaDatosTexto == TRUE || banderaCargaDatosBinario == TRUE){
						controller_removeEmployee(listaEmpleados);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 6:
					if(banderaCargaDatosTexto == TRUE || banderaCargaDatosBinario == TRUE){
						controller_ListEmployee(listaEmpleados);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 7:
					// ORDENAR EMPLEADOS
					controller_sortEmployee(listaEmpleados);
					break;
				case 8:
					// GUARDAR DATOS EN MODO TEXTO
					if(banderaCargaDatosTexto == TRUE){
						if(controller_saveAsText("data.csv", listaEmpleados) == TRUE){
							puts("¡Exito en la operacion!");
						}
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 9:
					// GUARDAR DATOS EN MODO BINARIO
					if(banderaCargaDatosTexto == TRUE || banderaCargaDatosBinario == TRUE){
						if(controller_saveAsBinary("data.txt", listaEmpleados) == TRUE){
							puts("¡Exito en la operacion!");
						}
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 10:
					puts("Fin del programa.");
					break;
			}
	} while (respuestaUsuario != 10);
}





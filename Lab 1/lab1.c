#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Se define la lista de terminales de la gramatica como una constantes global de  arreglo de cadena de caracteres
const char TERMINALES[][32] = {
        "obras", "de", "prefiero", 
        "lee", "compra", "busca", 
        "investiga", "Neruda", "Kafka", 
        "Cervantes", "Shakespeare", "Tolkien", 
        "Orwell", "Lovecraft", "cuentos", 
        "novelas", "dramas", "romance", 
        "terror", "fantasía", "misterio", 
        "comedia", "literatura", "antigua", 
        "medieval", "renacentista", "barroca", 
        "neoclásica", "romana", "griega", 
        "naturalista", "populares"
    };

//Objetivo: Funcion que comprueba si existe un archivo con el mismo nombre del archivo de salida indicado
//Entrada: Cadena de texto con el nombre del archivo de salida
//Salida: Entero con valor 1 cuando el archivo existe o 0 cuando no existe
int existeSalida(char const* nombreSalida){
    //Se comprueba si ya existe el archivo de salida abriendolo en modo lectura
    FILE* salida;
    salida = fopen(nombreSalida, "r");
    //Si existe el archivo
    if(salida != NULL){
        fclose(salida);
		return 1;
	}
    //Si no existe el archivo
    return 0;
}

//Objetivo: Funcion que comprueba si una cadena de texto es un terminal o contiene un terminal y retorna el indice del terminal
//Entrada: Cadena de texto que representa una palabra leida del archivo de entrada
//Salida: Entero con valor mayor o igual a 0 con el indice del terminal o -1 en caso de que no
int esTerminal(char const* palabraVerificar){
    for (int i = 0; i < 32; i++){
        //Se comprueba si la palabra leida es un terminal o contiene un terminal
        if(strcmp(palabraVerificar, TERMINALES[i]) == 0 || strstr(palabraVerificar, TERMINALES[i])){
            return i;
        }
    }
    return -1;
}

int verificacion(char const* nombreEntrada, char const* nombreSalida){
    FILE *entrada;
	entrada = fopen(nombreEntrada, "r");

    //Se comprueba si existe el archivo de entrada
	if(entrada == NULL){
		return 4;
	}

	//Se abre el archivo de salida en modo escritura
    FILE* salida;
	salida = fopen (nombreSalida, "w");

    char palabraLeida[100];

    while(feof(entrada) == 0){
        //Se lee una palabra del archivo de entrada y se almacena
		fscanf(entrada, "%s", palabraLeida);
        //Se comprueba si la palabra leida es o contiene un terminal
        int resultado = esTerminal(palabraLeida);
        
        if(resultado >= 0){
            int i = 0;
            unsigned char caracter;
            int tilde = 0;
            
            //Ciclo para escribir cada letra del terminal encontrado en mayuscula dentro del archivo de salida
            while (TERMINALES[resultado][i]) {
                
                caracter = TERMINALES[resultado][i];
                if(caracter == 195){
                    tilde = 1;
                }
                //Caso general
                else{
                    if(tilde == 1 && caracter == 173){
                        fprintf(salida, "%c", 205);
                        tilde = 0;
                    }

                    else if(tilde == 1 && caracter == 161){
                        fprintf(salida, "%c", 193);
                        tilde = 0;
                    }

                    else{
                        fprintf(salida, "%c", toupper(caracter));
                    }
                }
                //Se actualiza el contador
                i++;
            }
            //Se escribe un salto de linea despues de la palabras
            fprintf(salida, "%s", "\n");
        }
	}
    //Se cierra el archivo de entrada y salida
    fclose(entrada);
    fclose(salida);

    return 0;
}

int main(int argc, char const *argv[]){
    
    //Comprobacion inicial de los paremetros de entrada
    //Error 1
    if (argc == 1){
        printf("Error: Faltan par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }
    //Error 2
    else if (argc == 2){
        printf("Error: Falta par%cmetro.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }
    //Error 3
    else if (argc > 3){
        printf("Error: Demasiados par%cmetros.\n", 160);
        printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
        return 1;
    }

    //Error 5
    if (existeSalida(argv[2])){
        printf("Error: El archivo de salida ya existe.\n");
        return 1;
    }

    //Se realiza el proceso de verificar terminales dentro del archivo de entrada si es que existe
    int resultado = verificacion(argv[1], argv[2]);

    //Comprobacion de errores con los archivos de entrada
    //Error 4
    if (resultado == 4){
        printf("Error: El archivo de entrada no existe.\n");
        return 1;
    }

    return 0;
}
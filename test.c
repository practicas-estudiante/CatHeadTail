#include <stdio.h>
#include "libreria.c"
#include <stdlib.h>

int main (int argc, char* argv[]) {

	int comando;
	int numeroDeLineas;
	char *error;
	if (argc < 2) {
		fprintf(stderr, "Error,faltan argumentos\n");
		return 3;
	} else if (argc > 3) {
		fprintf(stderr, "Error, sobran argumentos\n");
		return 4;
	} else {
		comando = strtol(argv[1], &error, 10);/*Se convierte a int el valor de argv*/

		if (argc == 2 ){
			numeroDeLineas=10;
		}else{
			numeroDeLineas = strtol(argv[2], &error, 10);
		}
		if (numeroDeLineas < 0) {
			fprintf(stderr, "El valor %i del parámetro lineasMostrar no es válido\n", numeroDeLineas);
			return 1;
		}
		switch (comando) {
			case 1:
				head(numeroDeLineas);
				return 0;
			case 2:
				tail(numeroDeLineas);
				return 0;
			case 3:
				longlines(numeroDeLineas);
				return 0;
		}
		fprintf(stderr, "El valor no es válido\n");
		return 5;
	}
}

/*int main2() {
  char *ruta = "..\\Prueba.txt";
  char *rutainvalida = "..\\Pruebainvalida.txt";
  int errorA, errorB, errorC;
  printf("ahora se muetran los números de 4 a 1\n");
  head_file(4, ruta);
  printf("ahora también");
  head_file(8, ruta);
  printf("otra vez\n");
  tail_file(5, ruta);
  printf("ahora se muetran los números de 4 a 3\n");
  head_file(2, ruta);
  printf("ahora se muetran los números de 2 a 1\n");
  tail_file(2, ruta);
  printf("ahora se muetran las lineas más largas\n");
  longlines_file(4, ruta);
/*Se comprueba la función HEAD*/
/*printf("ahora no se muestra nada\n");
  errorA = head_file(0, ruta);
  errorB = tail_file(0, ruta);
  errorC = longlines_file(0, ruta);

  printf("Ahora se mostrarán 3 códigos iguales a 0\n");
  printf("%i\n%i\n%i\n", errorA, errorB, errorC);
  printf("ahora se mostrarán 3 mensajes de error\n");
  errorA = head_file(3, rutainvalida);
  errorB = tail_file(3, rutainvalida);
  errorC = longlines_file(3, rutainvalida);
  printf("Ahora se mostrarán 3 códigos iguales a 2\n");
  printf("%i\n%i\n%i\n", errorA, errorB, errorC);
  printf("ahora se mostrarán otros 3 mensajes de error\n");

  errorA = head_file(-1, ruta);
  errorB = tail_file(-3, ruta);
  errorC = longlines_file(-2, ruta);

  printf("Ahora se mostrarán 3 códigos iguales a 1\n");
  printf("%i\n%i\n%i\n", errorA, errorB, errorC);


  ruta = "..\\PruebaLonglines.txt";
  printf("Ahora se mostrará una linea de a's\n");
  longlines_file(1, ruta);
  printf("Ahora se mostrará una linea de a's y los números hasta el 5\n");
  longlines_file(6, ruta);
  printf("Ahora se mostrará una linea de a's, los números de 9 a 1 y una linea vacía\n");
  longlines_file(11, ruta);
  printf("lo mismo que antes\n");
  longlines_file(21, ruta);
  printf("fin");
  return 0;


  }
  */

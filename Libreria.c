#include <stdio.h>
#include <stdlib.h>

/*---------------------Caracter--------------------*/
struct caracter {
    struct caracter *sig;
    char valor;
};

typedef struct caracter Caracter;

/*Metodos Caracter*/

Caracter *getSigCaracter(Caracter *pCaracter) {
    return pCaracter->sig;
}

Caracter *CrearCaracter(char caracter) {
    Caracter *newCaracter = (Caracter *) malloc(sizeof(Caracter));
    newCaracter->sig = NULL;
    newCaracter->valor = caracter;
    return newCaracter;
}


void MostrarCaracter(Caracter *pCaracter) {
    printf("%c", pCaracter->valor);
}

void setSigCaracter(Caracter *pCaracter, Caracter *sig) {
    pCaracter->sig = sig;
}

void DestruirCaracter(Caracter *pCaracter) {
    free(pCaracter);
}

/*---------------------String--------------------*/
struct string {
    struct caracter *inicio;
    int longitud;
    struct caracter *final;
};

typedef struct string String;


/*Metodos String*/
/*Getter String*/

int getLenghtString(String *pString) {
    return pString->longitud;
}

String *InicializarString() {
    String *newString = (String *) malloc(sizeof(String));
    newString->longitud = 0;
    newString->inicio = NULL;
    newString->final = NULL;
    return newString;
}

void AnnadirCaracter(String *pString, char caracter) {
    Caracter *newCaracter = CrearCaracter(caracter);
    pString->longitud += 1;
    if (pString->final == NULL) {
        pString->inicio = newCaracter;
        pString->final = newCaracter;
    } else {
        setSigCaracter(pString->final, newCaracter);
        pString->final = newCaracter;
    }
}

void destruirString(String *pString) {
    Caracter *BorrarCaracter;
    Caracter *caracter;
    if (pString == NULL) {
        free(pString);
    } else {
        caracter = pString->inicio;
        while (caracter != NULL) {
            BorrarCaracter = caracter;
            caracter = getSigCaracter(caracter);
            DestruirCaracter(BorrarCaracter);
        }
        free(pString);
    }
}

String *CrearString(FILE *file, char *pchar) {
    String *str = InicializarString();
    if (*pchar == EOF) {
        NULL;
    } else {
        while ((*pchar != '\n') && (*pchar != EOF)) {
            AnnadirCaracter(str, *pchar);
            *pchar = (char) fgetc(file);
            str->longitud += 1;
        }
        *pchar = (char) fgetc(file); /* Esto es necesario ya que sino se quedaría en un bucle de newline*/
    }
    return str;
}


void MostrarString(String *pString) {
    Caracter *sig = pString->inicio;
    while (sig != NULL) {
        MostrarCaracter(sig);
        sig = getSigCaracter(sig);
    }
    printf("\n");
}

/*---------------------Nodo--------------------*/
struct nodo {
    struct nodo *sig;
    struct string *contenido;
    int valor;
    struct nodo *ant;
};

typedef struct nodo Nodo;

/*Metodos nodo*/

/*Getters nodo*/
Nodo *getSigNodo(Nodo *pNodo) {
    return pNodo->sig;
}

int getValorNodo(Nodo *pNodo) {
    return pNodo->valor;
}

Nodo *getAntNodo(Nodo *pNodo) {
    return pNodo->ant;
}


/*Setters nodo*/
void setSigNodo(Nodo *pNodo, Nodo *sig) {
    pNodo->sig = sig;
}


void setAntNodo(Nodo *pNodo, Nodo *ant) {
    pNodo->ant = ant;
}


Nodo *CrearNodo(String *valor) {
    Nodo *newNodo = (Nodo *) malloc(sizeof(Nodo));
    newNodo->sig = NULL;
    newNodo->contenido = valor;
    newNodo->valor = getLenghtString(newNodo->contenido);
    newNodo->ant = NULL;
    return newNodo;
}

void MostrarLinea(Nodo *pNodo) {
    String *linea = pNodo->contenido;
    MostrarString(linea);
}

void destruirNodo(Nodo *pNodo) {
    if (pNodo == NULL) {
        free(pNodo);
    } else {
        destruirString(pNodo->contenido);
        free(pNodo);
    }
}


int CalcularDesplazamiento(int posIni, int posObj) {
    /*Esta función solo sirve para calcular cuantos nodos hay que moverse en la busqueda binaria*/
    return posObj - posIni;
}

Nodo *DesplazarNnodos(Nodo *nodoActual, int desplazamiento) {
    /*Esta función devuelve un puntero al Nodo destino dado un desplazamiento, positivo hacia la cola, negativo hacia la cabeza*/
    Nodo *current = nodoActual;
    while (desplazamiento != 0) {
        if (desplazamiento > 0) {
            current = current->sig;
            desplazamiento--;
        } else {
            current = current->ant;
            desplazamiento++;
        }
    }
    return current;
}

/*---------------------Lista--------------------*/
struct lista {
    struct nodo *head;
    int longitud; /*Se añade este elemento para que getLength sea O(1)*/
    struct nodo *tail;
};

typedef struct lista Lista;

/*Metodos Lista*/

Lista *InicializarLista() {
    Lista *newList = (Lista *) malloc(sizeof(Lista));
    newList->head = NULL;
    newList->longitud = 0;
    newList->tail = NULL;
    return newList;
}


Lista *AnnadirNodoALaCola(Lista *pLista, String *valor) {
    Nodo *current = pLista->tail;
    Nodo *newNodo = CrearNodo(valor);
    setAntNodo(newNodo, current);
    if (pLista->head == NULL) {/*Si la cabeza de la Lista está vacía se apunta al nuevo Nodo*/
        pLista->head = newNodo;
    } else {/*Si ya hay una head, significa que hay un Nodo, como no es null, se puede acceder a su sig  */
        setSigNodo(current, newNodo);
    }
    pLista->tail = newNodo;
    pLista->longitud++;
    return pLista;
}


Nodo *BusquedaBinariaRecursiva(Nodo *current, int valorBuscado, int posInicio, int posActual, int posFinal) {
    int mitad = (posInicio + posFinal) / 2;
    int desplazamiento = CalcularDesplazamiento(posActual, mitad);
    Nodo *nodoMitad = DesplazarNnodos(current, desplazamiento);

    if (getValorNodo(nodoMitad) <= valorBuscado && valorBuscado <= getValorNodo(getSigNodo(nodoMitad))) {
        return nodoMitad;
    } else if (getValorNodo(nodoMitad) < valorBuscado) {
        return BusquedaBinariaRecursiva(nodoMitad, valorBuscado, mitad + 1, mitad, posFinal);
    } else if (valorBuscado < getValorNodo(nodoMitad)) {
        return BusquedaBinariaRecursiva(nodoMitad, valorBuscado, posInicio, mitad, mitad - 1);
    } else {
        return NULL;
    }
}

Nodo *BusquedaBinaria(Lista *pLista, int valorBuscado) {
    /*Para la busqueda binaria se considerará el menor elemento el de HEAD*/
    /*Una comprobación de que la Lista sea vacía no hace falta ya que eso se comprueba en el método de añadir el Nodo ordenado*/
    if (valorBuscado <= getValorNodo(pLista->head)) {
        return NULL;
        /*Este es un caso especial, ya que el metodo de de añadir Nodo ordenado, toma el Nodo que devuelve esta
        * función,y pone el nuevo Nodo en el siguiente a él, por lo que añadir antes del primero es un caso especial que indicamos
        * usando NULL*/
    } else if (getValorNodo(pLista->tail) <= valorBuscado) {
        return pLista->tail;
    } else {
        return BusquedaBinariaRecursiva(pLista->head, valorBuscado, 0, 0, pLista->longitud);
    }
}

void recortarLista(Lista *pLista, int max) {
    Nodo *nodoBorrar = NULL;
    if (pLista->longitud > max) {
        nodoBorrar = pLista->head;
        pLista->head = getSigNodo(pLista->head);
        setAntNodo(pLista->head, NULL);
        destruirNodo(nodoBorrar);
        pLista->longitud -= 1;
    }
}

Lista *InsertarlistaOrdenada(Lista *pLista, String *elem, int max) {
    int valor = getLenghtString(elem);/*La longitud del contenido es el valor que usaremos para ordenar los nodos*/
    Nodo *nodoActual;
    Nodo *newNodo = CrearNodo(elem);
    if (pLista->longitud == 0) {
        /*Si la Lista está vacía entonces simplemente se crea un Nodo y se añade*/
        pLista->head = newNodo;
        pLista->tail = newNodo;
        pLista->longitud++;
    } else {
        /*Sino, se busca el Nodo que va  a ser el anterior del que vamos a añadir, se marca el caso especial de NULL,
         * y en otro caso, se inserta el Nodo después del que encontramos con la busqueda binaria*/
        nodoActual = BusquedaBinaria(pLista, valor);
        pLista->longitud++;
        if (nodoActual == NULL) {
            setSigNodo(newNodo, pLista->head);
            setAntNodo(newNodo, NULL);
            setAntNodo(getSigNodo(newNodo), newNodo);
            pLista->head = newNodo;
        } else {
            setAntNodo(newNodo, nodoActual);
            setSigNodo(newNodo, getSigNodo(nodoActual));

            if (getSigNodo(nodoActual) != NULL) {
                setAntNodo(getSigNodo(nodoActual), newNodo);
            } else {
                pLista->tail = newNodo;
            }
            setSigNodo(nodoActual, newNodo);
        }
        recortarLista(pLista, max);
    }
    return pLista;
}

void MostrarLista(Lista *pLista, int number, int recta) {
    /*Se mostrará la Lista en base al parámetro recta
     * 1= ordenada por posición contando n lineas desde la cabeza(head)
     * 0= ordenada por posición contando n lineas desde la cola(tail)
     * 2= Ordenada al revés, empezando por la cola contando n lineas(longlines)*/
    Nodo *cursor;
    if (number != 0 && pLista != NULL) {/*Si el valor de number es 0 simplemente no hace nada*/
        if (recta == 1) {
            cursor = pLista->head;
            while (number > 0 && cursor != NULL) {
                MostrarLinea(cursor);
                cursor = getSigNodo(cursor);
                number--;
            }
        } else if (recta == 0) {
            if (number >= pLista->longitud) {
                /*En el caso de que el número de lineas  a mostrar con tail sea mayor que la longitud total de la Lista
                 * se da que head=tail, por lo que para ahorrarnos volver desde la cola hasta la cabeza,y volver a la cola
                 * simplemente llamamos a head*/
                MostrarLista(pLista, number, 1);
            } else {
                cursor = pLista->tail;
                while (number > 1 && cursor != NULL) {
                    /*Primero se vuelve en la Lista n nodos*/
                    cursor = getAntNodo(cursor);
                    number--;
                }
                /*Una comprobación de que se ha retrocedido hasta null no es necesaria ya que con el primer if se asegura
                 * de que no ocurra*/
                while (cursor != NULL) {
                    /*Una vez se han retrocedido los n nodos, se muestran todos sus valores desde el actual hasta la cola*/
                    MostrarLinea(cursor);
                    cursor = getSigNodo(cursor);
                }
            }
        } else if (recta == 2) {
            /*La Lista está ordenada con el head en el menor elemento, por lo que hay que recorrerla de manera inversa*/
            cursor = pLista->tail;
            while (number > 0 && cursor != NULL) {
                MostrarLinea(cursor);
                cursor = getAntNodo(cursor);
                number--;
            }
        }
    }
}

void destruirLista(Lista *pLista) {
    if (pLista == NULL) {
        free(pLista);
    } else {
        Nodo *nodoBorrar;
        Nodo *nodo = pLista->head;
        while (nodo != NULL) {
            nodoBorrar = nodo;
            nodo = getSigNodo(nodo);
            destruirNodo(nodoBorrar);
        }
        free(pLista);
    }
}


Lista *LeerFichero(char *nombreFichero, int lineasMostrar, int ordenado) {
    /*Este método lee el fichero, hasta la linea lineasMostrar, esto se utiliza en el caso de HEAD, en tail y longlines se usa -2
     * para denotar que se tiene que leer todo el fichero. la variable ordenado indica si la Lista debe ser ordenada o no*/
    FILE *file;
    Lista *pLista = InicializarLista();
    String *str;
    file = fopen(nombreFichero, "r");
    char caracLeido = (char) fgetc(file);

    if (file == NULL) {
        printf("Hubo un error abriendo el fichero, posiblemente fallo en la ruta\n");
        return NULL;
    } else if (caracLeido == EOF) {
        return pLista;
    } else {
        while ((caracLeido != EOF) && (lineasMostrar > 1 || lineasMostrar <= -2)) {
            str = CrearString(file, &caracLeido);
            if (getLenghtString(str) < 0) {
                printf("aqui");
            }
            if (ordenado == 1) {
                InsertarlistaOrdenada(pLista, str, lineasMostrar);
            } else if (ordenado == 0) {
                AnnadirNodoALaCola(pLista, str);
                lineasMostrar--;
            }
        }
        return pLista;
    }
}

String *LeerString(char pchar) {
    String *str = InicializarString();
    if (pchar == EOF) {
        NULL;
    } else {
        while (pchar != '\n') {
            AnnadirCaracter(str, pchar);
            pchar = (char) getchar();
            str->longitud += 1;
        }
    }
    return str;
}

Lista *LeerEntrada(int comando, int lineasMostrar, int ordenado) {
    char caracLeido;
    Lista *pLista = InicializarLista();
    caracLeido = (char) getchar();
    while ((caracLeido != '\n') && (lineasMostrar > 0 || lineasMostrar==-2)) {
        String *str = LeerString(caracLeido);

        caracLeido = (char) getchar();
        if (ordenado == 1) {
            InsertarlistaOrdenada(pLista, str, lineasMostrar);
        } else if (ordenado == 0) {
            AnnadirNodoALaCola(pLista, str);
            if (comando == 1) {
                lineasMostrar--;
            }
        }
    }
    return pLista;
}

/*Estos ya son los métodos finales*/

int head_file(int lineasMostrar, char *archivo) {
    if (lineasMostrar < 0) {
        fprintf(stderr,"El valor %i del parámetro lineasMostrar no es válido\n", lineasMostrar);
        return 1;
    } else {
        Lista *pLista = LeerFichero(archivo, lineasMostrar, 0);
        if (pLista == NULL) {
            destruirLista(pLista);
            return 2;
        } else {
            MostrarLista(pLista, lineasMostrar, 1);
            destruirLista(pLista);
            return 0;
        }
    }
}

int tail_file(int lineasMostrar, char *archivo) {
    if (lineasMostrar < 0) {
        fprintf(stderr, "El valor %i del parámetro lineasMostrar no es válido\n", lineasMostrar);
        return 1;
    } else {
        Lista *pLista = LeerFichero(archivo, -2, 0);
        if (pLista == NULL) {
            destruirLista(pLista);
            return 2;
        } else {
            MostrarLista(pLista, lineasMostrar, 0);
            destruirLista(pLista);
            return 0;
        }
    }
}

int longlines_file(int lineasMostrar, char *archivo) {
    if (lineasMostrar < 0) {
        fprintf(stderr,"El valor %i del parámetro lineasMostrar no es válido\n", lineasMostrar);
        return 1;
    } else {
        Lista *pLista = LeerFichero(archivo, lineasMostrar, 1);
        if (pLista == NULL) {
            destruirLista(pLista);
            return 2;
        } else {
            MostrarLista(pLista, lineasMostrar, 2);
            destruirLista(pLista);
            return 0;
        }
    }
}

int head(int lineasMostrar) {
    Lista *pLista = LeerEntrada(1,lineasMostrar, 0);
    if (pLista == NULL) {
        destruirLista(pLista);
        return 2;
    } else {
        MostrarLista(pLista, lineasMostrar, 1);
        destruirLista(pLista);
        return 0;
    }
}

int tail(int lineasMostrar) {
    Lista *pLista = LeerEntrada(2,lineasMostrar, 0);
    if (pLista == NULL) {
        destruirLista(pLista);
        return 2;
    } else {
        MostrarLista(pLista, lineasMostrar, 0);
        destruirLista(pLista);
        return 0;
    }
}


int longlines(int lineasMostrar) {
    Lista *pLista = LeerEntrada(3,lineasMostrar, 1);
    if (pLista == NULL) {
        destruirLista(pLista);
        return 2;
    } else {
        MostrarLista(pLista, lineasMostrar, 2);
        destruirLista(pLista);
        return 0;
    }
}

#ifndef ED_IMP_H_
#define ED_IMP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

/***************************/
/* EXPRESIONES ARITMÉTICAS */
/***************************/

/*
  Una estructura de tipo `aexp_t' representa una expresión aritmética.
 */
struct aexp_t;
typedef struct aexp_t aexp_t;

/*
  A -> N | (A + A) | (A - A) | (A * A)
  
  Una expresión aritmética A puede ser un natural, una suma, una resta
  o una multiplicación.

  Los siguientes predicados determinan qué tipo de expresión es A.
  Toda expresión aritmética satisface únicamente uno de estos
  predicados.
 */
bool aexp_is_num(aexp_t *a);
bool aexp_is_add(aexp_t *a);
bool aexp_is_sub(aexp_t *a);
bool aexp_is_mul(aexp_t *a);

/*
  El valor de un natural se puede obtener con el selector `aexp_num',
  mientras que los operandos izquierdo y derecho de una suma, resta o
  multiplicación se pueden obtener con los selectores `aexp_left' y
  `aexp_right' respectivamente. En caso de crear memoria, se accede al
  indice con `aexp_indice',
 */
uint64_t aexp_num(aexp_t *a);
aexp_t *aexp_left(aexp_t *a);
aexp_t *aexp_right(aexp_t *a);
aexp_t *aexp_indice(aexp_t *a);

/*
  Los siguientes constructores permiten crear un natural a partir de
  un valor de tipo `uint64_t', o bien, una expresión aritmética
  compuesta por otras expresiones aritméticas más simples, o una que
  contenga el inicio de la dirección de memoria.
 */
aexp_t *aexp_make_num(uint64_t num);
aexp_t *aexp_make_add(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mem(aexp_t *indice, mexp_t *x);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  aritmética se utiliza el siguiente destructor.
 */
void aexp_free(aexp_t *a);

/*
  Evaluador de expresiones aritméticas.
 */
uint64_t aexp_eval(aexp_t *a);

/*************************/
/* EXPRESIONES BOOLEANAS */
/*************************/

/*
  Una estructura de tipo `bexp_t' representa una expresión booleana.
 */
struct bexp_t;
typedef struct bexp_t bexp_t;

/*
  B -> true | false | (A = A) | (A < A) | (B and B) | (B or B) | not B

  Una expresión Booleana B puede ser verdadero, falso, la comparación
  de igualdad y menor qué entre dos expresiones ariméticas, la
  conjunción, disyunción y negación de expresiones Booleanas.

  Los siguientes predicados determinan qué tipo de expresión es B.
  Toda expresión booleana satisface únicamente uno de estos
  predicados.
 */
bool bexp_is_true(bexp_t *b);
bool bexp_is_false(bexp_t *b);
bool bexp_is_equal(bexp_t *b);
bool bexp_is_less(bexp_t *b);
bool bexp_is_and(bexp_t *b);
bool bexp_is_or(bexp_t *b);
bool bexp_is_neg(bexp_t *b);

/*
  Las expresiones booleanas pueden tener como hijos, a expresiones
  aritméticas u otras expresiones booleanas (incluyendo la negación de
  una expresión booleana). Las siguientes definiciones, retornan los
  distintos hijos con los que se pueden representar estas expresiones
 */
aexp_t *bexp_aleft(bexp_t *b);
aexp_t *bexp_aright(bexp_t *b);
bexp_t *bexp_bleft(bexp_t *b);
bexp_t *bexp_bright(bexp_t *b);
bexp_t *bexp_nchild(bexp_t *b);

/*
  Los siguientes constructores permiten crear los valores "true" o "false",
  o bien, expresiones booleanas que comparan igualdad, menor qué, conjunción,
  disyunción o negación; que recibien como parámetro expresiones aritméticas
  o booleanas, según sea el caso
 */
bexp_t *bexp_make_true();
bexp_t *bexp_make_false();
bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_less(aexp_t *left, aexp_t *right);
bexp_t *bexp_make_and(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right);
bexp_t *bexp_make_neg(bexp_t *child);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  booleana se utiliza el siguiente destructor.
 */
void bexp_free(bexp_t *b);

/*
  Evaluador de expresiones booleanas.
 */
bool bexp_eval(bexp_t *b);


/*************/
/*  MEMORIA  */
/*************/

struct mexp_t;
typedef struct mexp_t mexp_t;

struct nodo;
typedef struct nodo nodo;

//Constuctores de nodos. El que sólo recibe indice, inicializa el valor en 0.
nodo *mem_make_nodo(uint64_t indice);
nodo *mem_make_nodo(uint64_t indice, uint64_t val);

nodo *mexp_lista(mexp_t *x);
nodo *mexp_add(nodo *n, mexp_t *x);
nodo *mexp_add(nodo *n, nodo *l);
  
nodo *mexp_busca(aexp_t *indice, mexp_t *x);
nodo *mexp_busca(uint64_t i, nodo *n);
uint64_t mexp_obten_val(aexp_t i, mexp_t *x);

uint64_t nodo_indice(nodo *n);
uint64_t nodo_val(nodo *n);
nodo *nodo_left(mexp_t *x);
nodo *nodo_left(nodo *n);
nodo *nodo_right(mexp_t *x);
nodo *nodo_right(nodo *n);
  
/*************/
/* PROGRAMAS */
/*************/

/*
  Una estructura de tipo `programa' representa un programa.
 */
struct pexp_t;
typedef struct pexp_t pexp_t;

/*
 P -> skip | X := A | (P ; P) | (while B do P) | (if B then P else P)
 
 Un programa puede no hacer algo, modificar espacio en memoria, ser una
 secuencia de programas, repetir una misma tarea en tanto una expresión
 booleana sea verdadera; ejecutar un programa u otro, si una expresión
 booleana es verdadera o falsa, respectivamente.

 Los siguentes predicados determinan qué tipo de programa es P
 Todo programa satisface únicamente a uno de estos predicados.
 */
bool pexp_is_skip(pexp_t *P);
bool pexp_is_mem(pexp_t *P);
bool pexp_is_sec(pexp_t *P);
bool pexp_is_while(pexp_t *P);
bool pexp_is_if(pexp_t *P);

/*
 Los siguientes constructores permiten crear programas que "no hagan algo",
 modifiquen valores en memoria, que sean secuenciales, que funcionen como un
 ciclo while o un condicional "if-else"; respectivamente.
 */
pexp_t *pexp_make_skip();
pexp_t *pexp_make_mem(pexp_t *P);
pexp_t *pexp_make_sec(pexp_t *P1, pexp_t *P2);
pexp_t *pexp_make_while(bexp_t *b, pexp_t *P);
pexp_t *pexp_make_if(bexp_t *b, pexp_t *P_then, pexp_t *P_else);

/*
  Para liberar el espacio en memoria que ocupa un programa se utiliza
  el siguiente destructor.
 */
void pexp_free(pexp_t *P);

/*
 Evaluador de programas.
 */
uint64_t pexp_eval(pexp_t *P);



/*********************************
* VERSION EXTENDIDA DE PROGRAMAS *
*********************************/


/*** LISTA DE PROGRAMAS ***/

//"Estructura/identificador" para lista simple de programas.
struct list_pexp_t;
typedef struct list_pexp_t list_pexp_t;

/*
Una lista de programas puede ser vacía, o contener 'n' elementos.
Las siguientes expresiones nos devuelven:
    true/false si la lista está vacía.
    La cantidad de elementos en la lista, puede ser >= 0.
    El último elemento de una lista.
    El elemento que se acaba de agregar a la lista.
    El elemento que se acaba de eliminar de la lista (siempre es el último elemento de la lista).
*/
bool list_pexp_vacia(list_pexp_t *l);

uint64_t list_pexp_elem(list_pexp_t *l);
uint64_t list_pexp_elem(list_pexp_t *l, uint64_t count);

list_pexp_t *list_pexp_ultimo(list_pexp_t *l);
list_pexp_t *list_pexp_ul(list_pexp_t *l);
list_pexp_t *list_pexp_add(pexp_t *P, list_pexp_t *l);
list_pexp_t *list_pexp_sub(list_pexp_t *l);

//Libera la memoria solicitada por toda la lista, junto a los programas de cada elemento.
void list_pexp_free(list_pexp_t *l);


/*** EXTENSIONES DE PROGRAMA ***/

struct pexp_ex_t;
typedef struct pexp_ex_t pexp_ex_t;

/*
 P -> (if B then P) | (for (P; B ; P) do P) | (P P')
 P': ;P | ;P P'
 
 Una extensión de programa puede ser un condicional simple, un ciclo
 for, o una ejecución secuencial de 'n' programas, respectivamente;
 usando únicamente la sintaxis de un programa tipo "pexp_t".

 Los siguentes predicados determinan qué tipo de extensión programa es P
 Toda extensión de programa satisface únicamente a uno de estos predicados.
 */
bool pexp_ex_is_if(pexp_ex_t *P);
bool pexp_ex_is_for(pexp_ex_t *P);
bool pexp_ex_is_PP(pexp_ex_t *P);


/*
 Los siguientes constructores permiten crear un programa condicional simple "if-then",
 uno que funcione como un ciclo for, y otro que sea una secuencia de 'n' programas
 tal que n >= 1; usando la sintaxis de un programa "pexp_t".
 */
pexp_ex_t *pexp_ex_make_if(bexp_t *b, pexp_t *lista);
pexp_ex_t *pexp_ex_make_for(bexp_t *b, pexp_t *lista);
pexp_ex_t *pexp_ex_make_PP(pexp_t *lista);

//Función que crea una secuencia de programas, a partir de una lista de programas.
pexp_t *pexp_ex_transforma(list_pexp_t *l);

//Evaluador de extensión de programa.
pexp_t *pexp_ex_eval(pexp_ex_t *P, mexp_t *x);

//Liberador de memoria solicitada por una extensión de programa.
void pexp_ex_free(pexp_ex_t *P);



/*** EXTENSIONES DE EXPRESIONES BOOLEANAS ***/

struct pexp_ex_t;
typedef struct pexp_ex_t pexp_ex_t;

bool bexp_ex_is_not_equal(bexp_ex_t *b);
bool bexp_ex_is_less_equal(bexp_ex_t *b);
bool bexp_ex_is_great(bexp_ex_t *b);
bool bexp_ex_is_great_equal(bexp_ex_t *b);


bexp_ex_t *bexp_make_not_equal(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_less_equal(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_great(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_great_equal(aexp_t *left, aexp_t *right);

bexp_t *bexp_ex_eval(bexp_ex_t *b);

void bexp_ex_free(bexp_ex_t *b);

#endif  /* ED_IMP_H_ */

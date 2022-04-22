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
  `aexp_right' respectivamente.
 */
uint64_t aexp_num(aexp_t *a);
aexp_t *aexp_left(aexp_t *a);
aexp_t *aexp_right(aexp_t *a);

/*
  Los siguientes constructores permiten crear un natural a partir de
  un valor de tipo `uint64_t', o bien, una expresión aritmética
  compuesta por otras expresiones aritméticas más simples.
 */
aexp_t *aexp_make_num(uint64_t num);
aexp_t *aexp_make_add(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right);
aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right);

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
/* PROGRAMAS */
/*************/

/*
  Una estructura de tipo `programa' representa un programa.
 */
struct programa;
typedef struct programa programa;

/*
 P -> skip | X := A | (P ; P) | (while B do P) | (if B then P else P)
 
 Un programa puede no hacer algo, modificar espacio en memoria, ser una
 secuencia de programas, repetir una misma tarea en tanto una expresión
 booleana sea verdadera; ejecutar un programa u otro, si una expresión
 booleana es verdadera o falsa, respectivamente.

 Los siguentes predicados determinan qué tipo de programa es P
 Todo programa satisface únicamente a uno de estos predicados.
 */
bool programa_is_skip(programa *P);
bool programa_is_mem(programa *P);
bool programa_is_sec(programa *P);
bool programa_is_while(programa *P);
bool programa_is_if(programa *P);

/*
 Los siguientes constructores permiten crear programas que "no hagan algo",
 modifiquen valores en memoria, que sean secuenciales, que funcionen como un
 ciclo while o un condicional "if-else"; respectivamente.
 */
programa *programa_make_skip();
programa *programa_make_mem(programa *P);
programa *programa_make_sec(programa *P1, programa *P2);
programa *programa_make_while(bexp_t *b, programa *P);
programa *programa_make_if(bexp_t *b, programa *P_then, programa *P_else);

/*
  Para liberar el espacio en memoria que ocupa un programa se utiliza
  el siguiente destructor.
 */
void programa_free(programa *P);

/*
 Evaluador de programas.
 */
void programa_eval(programa *P);

#endif  /* ED_IMP_H_ */

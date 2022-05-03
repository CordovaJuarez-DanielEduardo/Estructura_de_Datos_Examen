#ifndef ED_BEXP_H_
#define ED_BEXP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <aexp.h>
#include <mexp.h>

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


bool bexp_is_mem(bexp_t *b);

/*
  Las expresiones booleanas pueden tener como hijos, a expresiones
  aritméticas, otras expresiones booleanas (incluyendo la negación de
  una expresión booleana) o nodos de una memoria. Las siguientes definiciones,
  retornan los distintos hijos con los que se pueden representar estas expresiones
 */
aexp_t *bexp_aleft(bexp_t *b);
aexp_t *bexp_aright(bexp_t *b);
bexp_t *bexp_bleft(bexp_t *b);
bexp_t *bexp_bright(bexp_t *b);
bexp_t *bexp_nchild(bexp_t *b);


uint64_t *bexp_nleft(bexp_t *b);
uint64_t *bexp_nright(bexp_t *b)

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


bexp_t *bexp_make_equal(nodo *left, nodo *right);
bexp_t *bexp_make_less(nodo *left, nodo *right);

/*
  Para liberar el espacio en memoria que ocupa una expresión
  booleana se utiliza el siguiente destructor.
 */
void bexp_free(bexp_t *b);

/*
  Evaluador de expresiones booleanas.
 */
bool bexp_eval(bexp_t *b);

#endif ED_BEXP_H_

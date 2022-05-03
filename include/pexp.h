#ifndef ED_PEXP_H_
#define ED_PEXP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <aexp.h>
#include <bexp.h>
#include <mexp.h> 

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

#endif ED_PEXP_H_

#ifndef ED_MEXP_H_
#define ED_MEXP_H_


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

#endif  ED_MEXP_H_

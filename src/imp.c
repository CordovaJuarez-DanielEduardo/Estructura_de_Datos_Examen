#include <imp.h>

/***************************/
/* EXPRESIONES ARITMÃ‰TICAS */
/***************************/

typedef enum {
    AEXP_NUM,
    AEXP_ADD,
    AEXP_SUB,
    AEXP_MUL,
    AEXP_MEM,
} AEXP_TYPE;

typedef struct aexp_t {
    AEXP_TYPE type;
    union {
        uint64_t num;
        struct {
            struct aexp_t *left;
            struct aexp_t *right;
        };
        struct {
            struct aexp_t *indice;
            struct memoria *m;
        };
    };
} aexp_t;


bool aexp_is_num(aexp_t *a) {
    return a->type == AEXP_NUM;
}

bool aexp_is_add(aexp_t *a) {
    return a->type == AEXP_ADD;
}

bool aexp_is_sub(aexp_t *a) {
    return a->type == AEXP_SUB;
}

bool aexp_is_mul(aexp_t *a) {
    return a->type == AEXP_MUL;
}

bool aexp_is_mem(aexp_t *a) {
    return a->type == AEXP_MEM;
}

uint64_t aexp_num(aexp_t *a) {
    return a->num;
}

aexp_t *aexp_left(aexp_t *a) {
    return a->left;
}

aexp_t *aexp_right(aexp_t *a) {
    return a->right;
}

aexp_t *aexp_indice(aexp_t *a) {
    return a->indice;
}

aexp_t *aexp_make_num(uint64_t num) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_NUM;
    a->num = num;
    return a;
}

aexp_t *aexp_make_add(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_ADD;
    a->left = left;
    a->right = right;
    return a;
}

aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_SUB;
    a->left = left;
    a->right = right;
    return a;
}

aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_MUL;
    a->left = left;
    a->right = right;
    return a;
}

aexp_t *aexp_make_mem(aexp_t *indice, mexp_t *x) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_MEM;
    a->indice = indice;
    a->m = x;
    return a;
}

void aexp_free(aexp_t *a) {
    if (a == NULL) return;

    if (!aexp_is_num(a)) {
        if(!aexp_is_mem(a)){
            aexp_free(aexp_left(a));
            aexp_free(aexp_right(a));
        } else  aexp_free(aexp_indice(a));
    }
    free(a);
}

uint64_t aexp_eval(aexp_t *a) {
    if (aexp_is_num(a)) return aexp_num(a);

    //REVISAR EL RETURN//
    if (aexp_is_mem(a)){
        nodo *n = mexp_add(nodo_make(aexp_eval(aexp_indice(a)),a->x);
        if(n == NULL) return;
        return nodo_indice(n);
    }

    uint64_t nleft = aexp_eval(aexp_left(a));
    uint64_t nright = aexp_eval(aexp_right(a));

    if (aexp_is_add(a)) return nleft + nright;
    if (aexp_is_mul(a)) return nleft * nright;


    if (nright > nleft) return 0;
    return nleft - nright;
}

/*************************/
/* EXPRESIONES BOOLEANAS */
/*************************/

typedef enum {
    BEXP_BASURA,
    BEXP_EQUAL,
    BEXP_LESS,
    BEXP_AND,
    BEXP_OR,
    BEXP_NEG,
    BEXP_MEM
} BEXP_TYPE;

typedef struct bexp_t {
    BEXP_TYPE type;
    union {
        struct {
            struct aexp_t *aleft;
            struct aexp_t *aright;
        };
        struct {
            struct bexp_t *bleft;
            struct bexp_t *bright;
        };
        struct {
            struct nodo *nleft;  
            struct nodo *nright;
        };
        struct bexp_t *child;
    };
} bexp_t;

bexp_t bexp_true;
bexp_t bexp_false;

bool bexp_is_true(bexp_t *b) {
    return b == &bexp_true;
}

bool bexp_is_false(bexp_t *b) {
    return b == &bexp_false;
}

bool bexp_is_equal(bexp_t *b) {
    return b->type == BEXP_EQUAL;
}

bool bexp_is_less(bexp_t *b) {
    return b->type == BEXP_LESS;
}

bool bexp_is_and(bexp_t *b) {
    return b->type == BEXP_AND;
}

bool bexp_is_or(bexp_t *b) {
    return b->type == BEXP_OR;
}

bool bexp_is_neg(bexp_t *b) {
    return b->type == BEXP_NEG;
}
                           
bool bexp_is_mem(bexp_t *b) {
    return b->type == BEXP_MEM;
}

aexp_t *bexp_aleft(bexp_t *b) {
    return b->aleft;
}

aexp_t *bexp_aright(bexp_t *b) {
    return b->aright;
}

bexp_t *bexp_bleft(bexp_t *b) {
    return b->bleft;
}

bexp_t *bexp_bright(bexp_t *b) {
    return b->bright;
}

bexp_t *bexp_nchild(bexp_t *b) {
    return b->child;
}

uint64_t *bexp_nleft(bexp_t *b) {
    return nodo_val(b->nleft);
}

uint64_t *bexp_nright(bexp_t *b) {
    return nodo_val(b->nright);
}
                           
bexp_t *bexp_make_true() {
    return &bexp_true;
}

bexp_t *bexp_make_false() {
    return &bexp_false;
}

bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_EQUAL;
    root->aleft = left;
    root->aright = right;
    root->nleft = NULL;
    root->nright = NULL;
    return root;
}

bexp_t *bexp_make_equal(nodo *left, nodo *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_EQUAL;
    root->aleft = NULL;
    root->aright = NULL;
    root->nleft = left;
    root->nright = right;
    return root;
}

bexp_t *bexp_make_less(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_LESS;
    root->aleft = left;
    root->aright = right;
    root->nleft = NULL;
    root->nright = NULL;
    return root;
}
                   
bexp_t *bexp_make_less(nodo *left, nodo *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_LESS;
    root->aleft = NULL;
    root->aright = NULL;
    root->nleft = left;
    root->nright = right;
    return root;
}

bexp_t *bexp_make_and(bexp_t *left, bexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_AND;
    root->bleft = left;
    root->bright = right;
    return root;
}
                           
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_OR;
    root->bleft = left;
    root->bright = right;
    return root;
}
                           
bexp_t *bexp_make_neg(bexp_t *child) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_NEG;
    root->child = child;
    return root;
}
                           
void bexp_free(bexp_t *b) {
    if (b == NULL) return;

    if (bexp_is_true(b) || bexp_is_false(b))  return;

    if (bexp_is_equal(b) || bexp_is_less(b)) {
        aexp_free(bexp_aleft(b));
        aexp_free(bexp_aright(b));
        free(b);
        return;
    }

    if (bexp_is_and(b) || bexp_is_or(b)) {
        bexp_free(bexp_bleft(b));
        bexp_free(bexp_bright(b));
        free(b);
        return;
    }

    bexp_free(bexp_nchild(b));
    free(b);
}

bool bexp_eval(bexp_t *b) {
    if (bexp_is_true(b)) return true;
    if (bexp_is_false(b)) return false;

    if (bexp_is_neg(b)) return !bexp_eval(bexp_nchild(b));
        
    if (bexp_is_equal(b))
        if(bexp_aleft(b) == NULL && bexp_nleft(b) != NULL) {
            return bexp_nleft(b) == bexp_nright(b);
        }
        return aexp_eval(bexp_aleft(b)) == aexp_eval(bexp_aright(b));

    if (bexp_is_less(b))
        if(bexp_aleft(b) == NULL && bexp_nleft(b) != NULL) {
            return bexp_nleft(b) < bexp_nright(b);
        }
        return aexp_eval(bexp_aleft(b)) < aexp_eval(bexp_aright(b));

    if (bexp_is_and(b))
        return bexp_eval(bexp_bleft(b)) && bexp_eval(bexp_bright(b));

    return bexp_eval(bexp_bleft(b)) || bexp_eval(bexp_bright(b));
}

/*************/
/*  MEMORIA  */
/*************/

typedef struct mexp_t {
    struct nodo *lista;
} mexp_t;

typedef struct nodo {
    uint64_t indice;
    uint64_t val;
    nodo *left;
    nodo *right;
} nodo;

nodo *mexp_lista(mexp_t *x) {
    return x->lista;
}

uint64_t nodo_indice(nodo *n) {
    return n->indice;
}

uint64_t nodo_val(nodo *n) {
    return n->val;
}

nodo *nodo_left(mexp_t *x) {
    return nodo_left(mexp_lista(x));
}

nodo *nodo_left(nodo *n) {
    if(n == NULL) return NULL;
    return n->left;
}

nodo *nodo_right(mexp_t *x) {
    return nodo_right(mexp_lista(x));
}

nodo *nodo_right(nodo *n) {
    if(n == NULL) return NULL;
    return n->right;
}


nodo *mem_make_nodo(uint64_t indice) {
    return mem_make_nodo(indice, 0);
}

nodo *mem_make_nodo(uint64_t indice, uint64_t val){
    nodo *root = (nodo *)malloc(sizeof(nodo));
    if (root == NULL) return NULL;
    root->indice = indice;
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    return root;
}

nodo *mexp_add(nodo *n, mexp_t *x){
    if(mexp_list(x) != NULL) return mexp_add(n, mexp_list(x));
    return x->lista = n;
}

nodo *mexp_add(nodo *n, nodo *l){
    if(nodo_indice(n) == nodo_indice(l)) return;
    if(nodo_indice(n)  > nodo_indice(l)){
        if(nodo_right(l) != NULL) return mexp_add(n, nodo_right(l));
        return l->right = n;
    }
    if(nodo_left(l) != NULL) return mexp_add(n, nodo_left(l));
    return l->left = n;
}

nodo *mexp_busca(aexp_t *indice, mexp_t *x){
    if(mexp_list(x) != NULL) return mexp_busca(aexp_eval(aexp_indice(indice)), mexp_list(x));
    return NULL;
}

nodo *mexp_busca(uint64_t i, nodo *l){
    if(nodo_indice(l)  < i && nodo_right(l) != NULL) return mexp_busca(i, nodo_rigth(l));
    if(nodo_indice(l)  > i && nodo_left(l)  != NULL) return mexp_busca(i, nodo_left(l));
    if(nodo_indice(l) == i) return l;
    return NULL;
}

uint64_t mexp_obten_val(aexp_t i, mexp_t *x){
    nodo *n = mexp_busca(i, x);
    if(n == NULL) return 0;
    return nodo_val(n);
}


/*************/
/* PROGRAMAS */
/*************/

typedef enum {
    PEXP_SKIP,
    PEXP_ASS,
    PEXP_SEC,
    PEXP_WHILE,
    PEXP_IF
} PEXP_TYPE;

typedef struct pexp_t{
    PEXP_TYPE type;
    union{
        //Programa que comparten todas las expresiones de programa
        struct pexp_t *P;
        //Condicional tanto para "while" como para "if"
        struct { 
            struct bexp_t *b;
        }
        //Estructura de "asignacion de memoria"
        struct {
            struct aexp_t *indice;
            struct aexp_t *val;
        };
        //Estructura de "secuencia de programas"
        struct {
            struct pexp_t *P2;
        };
        //Estructura de programa "if"
        struct {
            struct pexp_t *P_else;
        };
    };
} pexp_t;

pexp_t pexp_skip;

bool pexp_is_skip(pexp_t *P) {
    return P == &pexp_skip;
}

bool pexp_is_ass(pexp_t *P) {
    return P->type == PROG_ASS;
}

bool pexp_is_sec(pexp_t *P) {
    return P->type == PROG_SEC;
}

bool pexp_is_while(pexp_t *P) {
    return P->type == PROG_WHILE;
}

bool pexp_is_if(pexp_t *P) {
    return P->type == PROG_IF;
}


pexp_t *pexp_main(pexp_t *P) {
    return P->P;
}

pexp_t *pexp_sec(pexp_t *P) {
    return P->P2;
}

bexp_t *pexp_bool(pexp_t *P) {
    return P->b;
}

aexp_t *pexp_indice(pexp_t *P) {
    return P->indice;
}

aexp_t *pexp_val(pexp_t *P) {
    return P->val;
}

pexp_t *pexp_else(pexp_t *P) {
    return P->P_else;
}


/*** CONSTRUCTORES DE PROGRAMA ***/

pexp_t *pexp_make_skip(){
    return &pexp_skip;
}

pexp_t *pexp_make_ass(aexp_t *indice, aexp_t *val){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PEXP_ASS;
    root->P = NULL;
    root->indice = indice;
    root->val = val;
    return root;
}

pexp_t *pexp_make_sec(pexp_t *P1, pexp_t *P2){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PEXP_SEC;
    root->P = P1;
    root->P2 = P2;
    return root;
}

pexp_t *pexp_make_while(bexp_t *b, pexp_t *P){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PEXP_WHILE;
    root->b = b;
    root->P = P;
    return root;

}

pexp_t *pexp_make_if(bexp_t *b, pexp_t *P_then, pexp_t *P_else){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PEXP_IF;
    root->b = b;
    root->P = P_then;
    root->P2 = P_else;
    return root;
}

void pexp_free(pexp_t *P){
    if(P == NULL) return;
    if(pexp_is_skip(P)) return;
    
    if(pexp_is_ass(P)){
        aexp_free(pexp_indice(P));
        aexp_free(pexp_val(P));
    }
    
    if(pexp_is_sec(P)) pexp_free(pexp_sec(P));
    if(pexp_is_while(P) || pexp_is_if(P)) bexp_free(pexp_bool(b));
    if(pexp_is_if(P)) pexp_free(pexp_else(P));
    
    pexp_free(pexp_main(P));
    free(P);
}

uint64_t pexp_eval(pexp_t *P, mexp_t *x){
    if(P == NULL) return;
    if(pexp_is_skip(P)) return;

    if(pexp_is_ass(P)){
        nodo *n = busca(pexp_indice(P), x);
        if(n == NULL){
            aexp_t *a = aexp_make_mem(pexp_indice(P), x);
            if(a == NULL) return;
            aexp_eval(a);
            n = busca(pexp_indice(P), x);
        }
        n->val = aexp_eval(pexp_val(P));
        return nodo_val(n);
    }
    
    if(pexp_is_while(P) && bexp_eval(pexp_bool(P))){
        pexp_eval(pexp_main(P), x);
        pexp_eval(P, x);
    }
    
    if(pexp_is_if(P) && !bexp_eval(pexp_bool(P))){
        pexp_eval(pexp_else(P), x);
        return;
    }
    
    if(!pexp_is_while(P))   pexp_eval(pexp_main(P), x);
    if(pexp_is_sec(P))      pexp_eval(pexp_sec(P), x);
    
}

/*******************************************
* PROBLEMA ADICIONAL, VERSIONES EXTENDIDAS *
*   DE PROGRAMAS Y EXPRESIONES BOOLEANAS   *
********************************************/

typedef struct list_pexp_t{
    struct pexp_ex_t *P;
    struct list_pexp_t *next;
    struct list_pexp_t *prev;
} list_pexp_t;

bool list_pexp_vacia(list_pexp_t *l) {
    return l == NULL;
}

pexp_t *list_pexp(list_pexp_t *l) {
    return l->P;
}

list_pexp_t *list_next(list_pexp_t *l) {
    return l->next;
}

list_pexp_t *list_prev(list_pexp_t *l) {
    return l->prev;
}

uint64_t list_pexp_elem(list_pexp_t *l) {
    if(list_pexp_vacia(l)) return 0;
    return list_pexp_elem(l, 1);
}

uint64_t list_pexp_elem(list_pexp_t *l, unit64_t count) {
    if(l->next == NULL) return count;
    return list_pexp_elem(l, count+1);
}

list_pexp_t *list_pexp_ultimo(list_pexp_t *l) {
    if(list_pexp_vacia(l)) return l;
    if(list_next(l) == l) return l;
    return list_pexp_ul(l);
}
list_pexp_t *list_pexp_ul(list_pexp_t *l) {
    if(list_next(l) == NULL) return l;
    return list_pexp_ul(list_next(l));
}

list_pexp_t *list_pexp_add(pexp_t *P, list_pexp_t *l) {
    list_pexp_t *root = (list_pexp_t *)malloc(sizeof(list_pexp_t));
    if(root == NULL) return NULL;
    root->P = P;
    root->next = NULL;
    
    list_pexp_t *ultimo = list_pexp_ultimo(l);
    ultimo->next = root;
    root->prev = ultimo;
    return = root;
}

list_pexp_t *list_pexp_sub(list_pexp_t *l) {
    if(list_pexp_vacia(l)) return NULL;
    if(list_next(l) == NULL){
        list_pexp_t *ultimo = l;
        l = NULL;
        return ultimo;
    }
    return list_pexp_sub(list_next(l));
}

void list_pexp_free(list_pexp_t *l) {
    if(list_pexp_vacia(l)) return;
    list_pexp_t *aux = list_next(l);
    pexp_free(list_pexp(l));
    free(l);
    list_pexp_free(aux);
}

/**  VERSION EXTENDIDA DE PROGRAMAS  **/

typedef enum{
    PEXP_EX_IF,
    PEXP_EX_FOR,
    PEXP_EX_PP
}PEXP_EX_TYPE;
typedef struct pexp_ex_t {
    PEXP_EX_TYPE type;
    struct list_pexp_t *list;
    union{
        struct{
            struct bexp_t *b;
        }
    }
}pexp_ex_t;


/**   PREDICADOS   **/
bool pexp_ex_is_if(pexp_ex_t *P) {
    return P->type == PEXP_EX_IF;
}

bool pexp_is_for(pexp_ex_t *P) {
    return P->type == PEXP_EX_FOR;
}

bool pexp_ex_is_PP(pexp_ex_t *P) {
    return P->type == PEXP_EX_PP;
}

list_pexp_t *pexp_ex_list(pexp_ex_t *P) {
    return P->list;
}

bexp_t *pexp_ex_bool(pexp_ex_t *P) {
    return P->b;
}

/**  CONSTRUCTORES  **/
pexp_ex_t *pexp_ex_make_for(bexp_t *b, pexp_t *lista) {
    pexp_ex_t *root = (pexp_ex_t *)malloc(sizeof(pexp_ex_t));
    if(root == NULL) return NULL;
    root->type = PEXP_EX_FOR;
    root->b = b;
    root->lista = lista;
    return root;
}

pexp_ex_t *pexp_ex_make_if(bexp_t *b, pexp_t *lista) {
    pexp_ex_t *root = (pexp_ex_t *)malloc(sizeof(pexp_ex_t));
    if(root == NULL) return NULL;
    root->type = PEXP_EX_IF;
    root->b = b;
    root->lista = lista;
    return root;
}

pexp_ex_t *pexp_ex_make_PP(pexp_t *lista) {
    pexp_ex_t *root = (pexp_ex_t *)malloc(sizeof(pexp_ex_t));
    if(root == NULL) return NULL;
    root->type = PEXP_EX_PP;
    root->lista = lista;
    return root;
}


/**  EVALUADORES  **/

//Devuelve un programa 'skip' o una secuencia de programas, usando aquellos dentro de la lista de programas
pexp_t *pexp_ex_transforma(list_pexp_t *l) {
    if(l == NULL) return pexp_make_skip();
    return pexp_make_sec(list_pexp(l), pexp_ex_transforma(list_next(l)));
}

pexp_t *pexp_ex_normaliza(pexp_ex_t *P) {
    return;
}

pexp_t *pexp_ex_eval(pexp_ex_t *P, mexp_t *x) {
    if(P == NULL) return NULL;
    pexp_t *t = pexp_ex_transforma(pexp_ex_list(P));
    
    if(pexp_ex_is_for(P) && (list_pexp_elem(pexp_ex_lista(P)) > 2)) {
        pexp_t *p = pexp_sec(t);
        pexp_t *sec = pexp_make_sec(pexp_sec(p), pexp_main(p));
        pexp_t *w = pexp_make_while(pexp_ex_bool(P), sec);
        sec = pexp_make_sec(pexp_main(t), w);
        return sec;
    }
    if(pexp_ex_is_if(P)) return pexp_make_if(pexp_ex_bool(P), pexp_main(t), pexp_make_skip);
    
    if(!pexp_is_sec(t)) return NULL;
    return t;
}

void pexp_ex_free(pexp_ex_t *P) {
    free(P);
}


/** VERSION EXTENDIDA DE EXPRESIONES BOOLEANAS **/
typedef enum{
    BEXP_EX_NOT_EQUAL;
    BEXP_EX_LESS_EQUAL,
    BEXP_EX_GREAT,
    BEXP_EX_GREAT_EQUAL
}BEXP_EX_TYPE;

typedef struct bexp_ex_t{
    BEXP_EX_TYPE type;
    struct aexp_t *left;
    struct aexp_t *right;
} bexp_ex_t;

/* PREDICADOS */
bool bexp_ex_is_not_equal(bexp_ex_t *b) {
    return b->type == BEXP_EX_NOT_EQUAL;
}

bool bexp_ex_is_less_equal(bexp_ex_t *b) {
    return b->type == BEXP_EX_LESS_EQUAL;
}

bool bexp_ex_is_great(bexp_ex_t *b) {
    return b->type == BEXP_EX_GREAT;
}

bool bexp_ex_is_great_equal(bexp_ex_t *b) {
    return b->type == BEXP_EX_GREAT_EQUAL;
}

aexp_t *bexp_ex_left(bexp_ex_t *b) {
    return b->left;
}

aexp_t *bexp_ex_right(bexp_ex_t *b) {
    return b->right;
}

/* CONSTRUCTORES */

bexp_ex_t *bexp_make_not_equal(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_NOT_EQUAL;
    
    root->left = left;
    root->right = right;
    return root;
}

bexp_ex_t *bexp_make_less_equal(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_LESS_EQUAL;
    
    root->left = left;
    root->right = right;
    return root;
}

bexp_ex_t *bexp_make_great(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_GREAT;
    
    root->left = left;
    root->right = right;
    return root;
}

bexp_ex_t *bexp_make_great_equal(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_GREAT_EQUAL;
    
    root->left = left;
    root->right = right;
    return root;
}

bexp_ex_t *bexp_ex_eval(bexp_ex_t *b) {
    bexp_t *RETURN = NULL;
    if(bexp_ex_is_not_equal(b)){
        bexp_t *equal = bexp_make_equal(b->left, b->right);
        RETURN = bexp_make_neg(equal);
        if(RETURN == NULL) bexp_free(equal);
    }
    if(bexp_ex_is_less_equal(b)){
        bexp_t *less, *equal;
        equal = bexp_make_equal(b->left, b->right);
        less = bexp_make_less(b->left, b->right);
        RETURN = bexp_make_or(less, equal);
        
        if(RETURN == NULL){
            bexp_free(equal);
            bexo_free(less);
        }
    }
    if(bexp_ex_is_great(b)){
        bexp_ex_t *less_equal = bexp_ex_make_less_equal(b->left, b->right);
        if(less_equal == NULL) return NULL;
        
        RETURN = bexp_make_neg(bexp_ex_eval(less_equal));
        if(RETURN == NULL) bexp_ex_free(less_equal);
    }
    if(bexp_ex_is_great_equal(b)){
        bexp_t *less = bexp_make_less(b->left, b->right);
        RETURN = bexp_make_neg(less);
        if(RETURN == NULL) bexp_free(less);
    }
    return RETURN;
}

void bexp_ex_free(bexp_ex_t *b) {
    aexp_free(bexp_ex_left(b));
    aexp_free(bexp_ex_right(b));
    free(b);
}

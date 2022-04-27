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
        aexp_free(aexp_left(a));
        aexp_free(aexp_right(a));
    }
    free(a);
}

uint64_t aexp_eval(aexp_t *a) {
    if (aexp_is_num(a)) return aexp_num(a);

    //REVISAR EL RETURN//
    if (aexp_is_mem(a)) return (mem_add(mem_make_nodo(aexp_eval(a->indice)),a->m))->indice;

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
    BEXP_NEG
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
    return root;
}

bexp_t *bexp_make_less(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_LESS;
    root->aleft = left;
    root->aright = right;
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
        return aexp_eval(bexp_aleft(b)) == aexp_eval(bexp_aright(b));

    if (bexp_is_less(b))
        return aexp_eval(bexp_aleft(b)) < aexp_eval(bexp_aright(b));

    if (bexp_is_and(b))
        return bexp_eval(bexp_bleft(b)) && bexp_eval(bexp_bright(b));

    return bexp_eval(bexp_bleft(b)) || bexp_eval(bexp_bright(b));
}

/*************/
/*  MEMORIA  */
/*************/

typedef struct mexp_t{
    struct nodo *lista;
} mexp_t;

typedef struct nodo{
    uint64_t indice;
    uint64_t val;
    nodo *left;
    nodo *right;
} nodo;

nodo *mem_make_nodo(uint64_t indice)}{
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

void mexp_add(nodo *n, mexp_t *x){
    if(x->lista != NULL) agrega(n, x->lista);
    x->lista = n;
}

void mexp_add(nodo *n, nodo *m){
    if(n->indice == m->indice) return;
    if(n->indice > m->indice){
        if(m->right != NULL) mexp_add(n, m->right);
        m->right = n;
    }
    if(m->left != NULL) mexp_add(n, m->left);
    m->left = n;
}

nodo* mexp_busca(aexp_t *indice, mexp_t *m){
    if(m->lista != NULL) return mexp_busca(aexp_eval(indice->indice), m->lista);
    return NULL;
}

nodo* mexp_busca(uint64_t i, nodo *n){
    if(n->indice  < i && n->right != NULL) mexp_busca(i, n->rigth);
    if(n->indice  > i && n->left  != NULL) mexp_busca(i, n->left);
    if(n->indice == i) return n;
    return NULL;
}

uint64_t mexp_obten(aexp_t i, mexp_t *m){
    return mexp_obten(aexp_eval(i), mexp_t *m);
}

uint64_t mexp_obten(uint64_t i, mexp_t *m){
    nodo *n = mexp_busca(i, m);
    if(n == NULL) return 0;
    return n->val
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
        //Estructura "while" (el Booleano se comparte con "if", adem¨¢s 'P' sirve como el primero de los que tienen 2)
        struct pexp_t *P;
        struct bexp_t *b;
        //Estructura de "asignacion de memoria"
        struct{
            aexp_t *indice;
            aexp_t *val;
        };
        //Estructura de "secuencia de programas"
        struct{
            struct pexp_t *P2;
        };
        //Estructura de programa "if"
        struct{
            struct pexp_t *P_else;
        };
    };
} pexp_t;

pexp_t progama_skip;

bool pexp_is_skip(pexp_t *P){
    return P == &programa_skip;
}

bool pexp_is_ass(pexp_t *P){
    return P->type == PROG_ASS;
}

bool pexp_is_sec(pexp_t *P){
    return P->type == PROG_SEC;
}

bool pexp_is_while(pexp_t *P){
    return P->type == PROG_WHILE;
}

bool pexp_is_if(pexp_t *P){
    return P->type == PROG_IF;
}

/*** CONSTRUCTORES DE PROGRAMA ***/

pexp_t *pexp_make_skip(){
    return &programa_skip;
}

pexp_t *pexp_make_ass(aexp_t *indice, aexp_t *val){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PROG_ASS;
    root->pos = indice;
    root->val = val;
    return root;
}

pexp_t *pexp_make_sec(pexp_t *P1, pexp_t *P2){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PROG_SEC;
    root->P = P1;
    root->P2 = P2;
    return root;
}

pexp_t *pexp_make_while(bexp_t *b, pexp_t *P){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PROG_WHILE;
    root->b = b;
    root->P = P;
    return root;

}

pexp_t *pexp_make_if(bexp_t *b, pexp_t *P_then, pexp_t *P_else){
    pexp_t *root = (pexp_t *)malloc(sizeof(pexp_t));
    if(root == NULL) return NULL;
    root->type = PROG_IF;
    root->b = b;
    root->P = P_then;
    root->P2 = P_else;
    return root;
}

void pexp_free(pexp_t *P){
    if(P == NULL) return;
    if(pexp_is_skip(P)) return;
    
    if(pexp_is_ass(P)){
        aexp_free(P->pos);
        aexp_free(P->val);
    }
    
    if(pexp_is_sec(P)) pexp_free(P->P2);
    if(pexp_is_while(P) || pexp_is_if(P)) bexp_free(P->b);
    if(pexp_is_if(P)) pexp_free(P->P_else);
    
    pexp_free(P->P);
    free(P);
}

uint64_t pexp_eval(pexp_t *P, mexp_t *x){
    if(P == NULL) return;
    if(pexp_is_skip(P)) return;

    if(pexp_is_ass(P)){
        nodo *n = busca(P->indice, x);
        if(n == NULL){
            aexp_t *a = aexp_make_mem(P->indice, x);
            aexp_eval(a);
            n = busca(P->indice, x);
        }
        n->val = aexp_eval(P->val);
        return n->val;
    }
    
    if(pexp_is_while(P) && bexp_eval(P->b)){
        pexp_eval(P->P, x);
        pexp_eval(P, x);
    }
    
    if(pexp_is_if(P) && !bexp_eval(P->b)){
        pexp_eval(P->P_else, x);
        return;
    }
    
    pexp_eval(P->P, x);
    if(pexp_is_sec(P))  pexp_eval(P->P2, x);
    
}

/*******************************************
* PROBLEMA ADICIONAL, VERSIONES EXTENDIDAS *
*   DE PROGRAMAS Y EXPRESIONES BOOLEANAS   *
********************************************/

typedef struct list_pexp_t{
    pexp_t *P;
    list_pexp_t *next;
} list_pexp_t;

/**  VERSION EXTENDIDA DE PROGRAMAS  **/

typedef enum{
    PEXP_EX_IF,
    PEXP_EX_FOR,
    PEXP_EX_PP
}PEXP_EX_TYPE;
typedef struct pexp_ex_t{
    PEXP_EX_TYPE type;
    list_pexp_t *list;
    union{
        struct{
            bexp_t *b;
        }
    }
}pexp_ex_t;


/**   PREDICADOS   **/
bool pexp_ex_is_if(pexp_ex_t *P){
    return;
}

bool pexp_is_for(pexp_ex_t *P){
    return P->type == PEXP_EX_FOR;
}

bool pexp_ex_is_PP(pexp_ex_t *P){
    return;
}

/**  CONSTRUCTORES  **/
pexp_ex_t *pexp_ex_make_for(bexp_t *b, pexp_t *lista){
    pexp_ex_t *root = (pexp_ex_t *)malloc(sizeof(pexp_ex_t));
    if(root == NULL) return NULL;
    root->type = PEXP_EX_FOR;
    root->b = b;
    root->lista = lista;
    return root;
}

pexp_ex_t *pexp_ex_make_if(bexp_t *b, pexp_t *lista){
    return;
}

pexp_ex_t *pexp_ex_make_PP(pexp_t *lista){
    return;
}


/**  EVALUADORES  **/

//Devuelve un programa 'skip' o una secuencia de programas, usando aquellos dentro de la lista de programas
pexp_t *pexp_ex_transforma(list_pexp_t *l){
    if(l == NULL) return pexp_make_skip();
    return pexp_make_sec(l->P, pexp_ex_transforma(l->next));
}

pexp_t *pexp_ex_normaliza(pexp_ex_t *P){
    return;
}

pexp_t *pexp_ex_eval(pexp_ex_t *P, mexp_t *x){
    if(P == NULL) return NULL;
    pexp_t *t = pexp_ex_transforma(P->list);
    
    if(pexp_ex_is_for(P)){
        pexp_t *p =;
    }
    if(pexp_ex_is_if(P)){
        pexp_t *p =;
    }
    //En el caso de PP (PP'), regresamos una secuencia de programas, que es lo que devuelve la función "transforma"
    return t;
}

/*/programa if para la versión extendida
pexp_t *pexp_ex_make_if(bexp_t *b, pexp_t *P_then){
    return programa_make_if(b, P_then, programa_make_skip());
}
*/


/** VERSION EXTENDIDA DE EXPRESIONES BOOLEANAS **/
typedef enum{
    BEXP_EX_NOT_EQUAL;
    BEXP_EX_LESS_EQUAL,
    BEXP_EX_GREAT,
    BEXP_EX_GREAT_EQUAL
}BEXP_EX_TYPE;

typedef struct bexp_ex_t{
    BEXP_EX_TYPE type;
    /*
    AGREGAR CÓDIGO
    */
} bexp_ex_t;

/* PREDICADOS */
bool bexp_ex_is_not_equal(bexp_t *b) {
    return b->type == BEXP_EX_NOT_EQUAL;
}

bool bexp_ex_is_less_equal(bexp_t *b) {
    return b->type == BEXP_EX_LESS_EQUAL;
}

bool bexp_ex_is_great(bexp_t *b) {
    return b->type == BEXP_EX_GREAT;
}

bool bexp_ex_is_great_equal(bexp_t *b) {
    return b->type == BEXP_EX_GREAT_EQUAL;
}

/* CONSTRUCTORES */

/* EVALUADORES */


//  ¡¡¡SEPARAR LA PARTE MAKE, DEL EVALUADOR!!!

bexp_t *bexp_make_not_equal(aexp_t *left, aexp_t *right){
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_NOT_EQUAL;
    
    bexp_t *equal = bexp_make_equal(left, right);
    root->child = bexp_make_neg(equal);
    
    //No se revisan todos los casos en donde debe liberarse la memoria, hace falta checarlo.
    if(root->child == NULL)   free(root);
    return root;
}

bexp_t *bexp_make_less_equal(aexp_t *left, aexp_t *right){
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_LESS_EQUAL;
    bexp_t *or, *less, *equal;
    equal = bexp_make_equal(left, right);
    less = bexp_make_less(left, right);
    or = bexp_make_or(less, equal);
    root->child = or;
    
    //No se revisan todos los casos en donde debe liberarse la memoria, hace falta checarlo.
    if(equal == NULL || (less == NULL || or == NULL)) free(root);
    return root;
}

bexp_t *bexp_make_great(aexp_t *left, aexp_t *right){
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_GREAT;
    root->child = bexp_make_neg(bexp_make_less_equal(left, right));

    //No se revisan todos los casos en donde debe liberarse la memoria, hace falta checarlo.
    if(root->child == NULL) free(root);
    return root;
}

bexp_t *bexp_make_great_equal(aexp_t *left, aexp_t *right){
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if(root == NULL) return NULL;
    root->type = BEXP_GREAT_EQUAL;

    bexp_t *less = bexp_make_less(left, right);
    root->child = bexp_make_neg(less);
    
    //No se revisan todos los casos en donde debe liberarse la memoria, hace falta checarlo.
    if(root->child == NULL) free(root);
    return root;
}

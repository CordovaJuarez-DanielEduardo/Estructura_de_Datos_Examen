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

aexp_t *aexp_make_mem(aexp_t *indice, memoria *x) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_MEM;
    a->indice = indice;
    a->m = x;
    return a;
}

void agrega(nodo *n, memoria *x){
    if(x->lista != NULL) agrega(n, m->lista);
    m->lista = n;
}

void agrega(nodo *n, nodo *m){
    if(n->indice == m->indice) return;
    if(n->indice > m->indice){
        if(m->right != NULL) agrega(n, m->right);
        m->right = n;
    }
    if(m->left != NULL) agrega(n, m->left);
    m->left = n;
}

aexp_t* busca(aexp_t *mem, aexp_t *indice){
    return busca(mem, aexp_eval(indice->indice));
}

aexp_t* busca(aexp_t *p, uint64_t i){
    uint64_t padre = aexp_eval(p->indice);
    if(padre < hijo && p->right != NULL) busca(p->right, i);
    if(padre > hijo && p->left  != NULL) busca(p->left, i);
    if(padre == hijo) return p;
    return NULL;
}
uint64_t obten(aexp_t m){
    if(m == NULL) return 0;
    if(aexp_is_mem(m)) return m->num;
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

    if (aexp_is_mem(a)) agrega(aexp_eval(a->indice),a->m);

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

    if (bexp_is_true(b) || bexp_is_false(b))
        return;

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

struct memoria{
    struct nodo *lista;
};

struct nodo{
    uint64_t indice;
    uint64_t val;
    nodo *left;
    nodo *right;
};

nodo *make_nodo(uint64_t indice)}{
    return make_nodo(indice, 0);
}

nodo *make_nodo(uint64_t indice, uint64_t val){
    nodo *root = (nodo *)malloc(sizeof(nodo));
    if (root == NULL) return NULL;
    root->indice = indice;
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    return root;
}

/*************/
/* PROGRAMAS */
/*************/

typedef enum {
    PROG_SKIP,
    PROG_ASS,
    PROG_SEC,
    PROG_WHILE,
    PROG_IF
} PROG_TYPE;

/*

 */

typedef struct programa{
    PROG_TYPE type;
    union{
        //Estructura "while" (el Booleano se comparte con "if", adem¨¢s 'P' sirve como el primero de los que tienen 2)
        struct programa *P;
        struct bexp_t *b;
        //Estructura de "asignacion de memoria"
        struct{
            aexp_t *pos;
            uint64_t val;
        };
        //Estructura de "secuencia de programas"
        struct{
          struct programa *P2;
        };
        //Estructura de programa "if"
        struct{
            struct programa *P_else;
        };
    };
} programa;

programa progama_skip;

bool programa_is_skip(programa *P){
    return P == &programa_skip;
}

bool programa_is_ass(programa *P){
    return P->type == PROG_ASS;
}

bool programa_is_sec(programa *P){
    return P->type == PROG_SEC;
}

bool programa_is_while(programa *P){
    return P->type == PROG_WHILE;
}

bool programa_is_if(programa *P){
    return P->type == PROG_IF;
}

/*** CONSTRUCTORES DE PROGRAMA ***/

programa *programa_make_skip(){
    return &programa_skip;
}

programa *programa_make_ass(aexp_t *indice, aexp_t *val){
    programa *root = (programa *)malloc(sizeof(programa));
    if(root == NULL) return NULL;
    root->type = PROG_ASS;
    root->pos = aexp_eval(indice);
    root->val = aexp_eval(val);
    return root;
}

programa *programa_make_sec(programa *P1, programa *P2){
    programa *root = (programa *)malloc(sizeof(programa));
    if(root == NULL) return NULL;
    root->type = PROG_SEC;
    root->P = P1;
    root->P2 = P2;
    return root;
}

programa *programa_make_while(bexp_t *b, programa *P){
    programa *root = (programa *)malloc(sizeof(programa));
    if(root == NULL) return NULL;
    root->type = PROG_WHILE;
    root->b = b;
    root->P = P;
    return root;

}

programa *programa_make_if(bexp_t *b, programa *P_then, programa *P_else){
    programa *root = (programa *)malloc(sizeof(programa));
    if(root == NULL) return NULL;
    root->type = PROG_IF;
    root->b = b;
    root->P = P_then;
    root->P2 = P_else;
    return root;
}


void programa_free(programa *P){
    if(P == NULL) return;
    if(programa_is_skip(P)) return;
    //REVISAR
    if(programa_is_ass(P)) aexp_free(P->pos);

    if(programa_is_sec(P)){
        programa_free(P->P);
        programa_free(P->P2);
    }

    if(programa_is_while(P)){
        bexp_free(P->b);
        programa_free(P->P);
    }
    if(programa_is_if(P)){
        bexp_free(P->b);
        programa_free(P->P);
        programa_free(P->P_else);
    }

    free(P);
}

uint64_t programa_eval(programa *P, memoria *x){
    if(P == NULL) return;
    if(programa_is_skip(P)) return;

    if(programa_is_ass(P)){
        nodo *n = busca(x, P->pos);
        if(n == NULL){
            //a = aexp_make_mem(P->pos, P->val);
            n = make_nodo(P->pos, P->val);
            agrega(x, n);
        }
        n->val =
        return a->num;
    }

    if(programa_is_sec(P)){
        programa_eval(P->P);
        programa_eval(P->P2);
    }
    if(programa_is_while(P) && bexp_eval(P->b)){
        programa_eval(P->P);
        programa_eval(P);
    }
    if(bexp_eval(P->b)) programa_eval(P->P);
    else                programa_eval(P->P_else);
}

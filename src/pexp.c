#include <pexp.h>
#include <mexp.h>
#include <aexp.h>
#include <bexp.h>

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

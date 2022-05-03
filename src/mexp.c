#include <mexp.h>

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

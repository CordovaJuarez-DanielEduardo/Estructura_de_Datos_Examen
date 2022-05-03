#include <aexp.h>


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
            struct mexp_t *x;
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
    a->x = x;
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

    if (aexp_is_mem(a)){
        nodo *n = mexp_add(nodo_make(aexp_eval(aexp_indice(a)), a->x);
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

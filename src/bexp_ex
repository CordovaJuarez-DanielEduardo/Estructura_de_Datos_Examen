#include <bexp_ex.h>
#include <bexp.h>

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
        RETURN = bexp_make_less(b->right, b->left);
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

#include <bexp_ex.h>


//EVALUADOR DE EXPRESIONES BOOLEANAS EXTENDIDAS
bexp_t *bexp_ex_eval(bexp_ex_t *b) {
    bexp_t *RETURN = NULL;
    if(bexp_ex_is_not_equal(b)){
        bexp_t *equal = bexp_make_equal(bexp_ex_left(b), bexp_ex_right(b));
        RETURN = bexp_make_neg(equal);
        if(RETURN == NULL) bexp_free(equal);
    }
    if(bexp_ex_is_less_equal(b)){
        bexp_t *less, *equal;
        equal = bexp_make_equal(bexp_ex_left(b), bexp_ex_right(b));
        less = bexp_make_less(bexp_ex_left(b), bexp_ex_right(b));
        RETURN = bexp_make_or(less, equal);

        if(RETURN == NULL){
            bexp_free(equal);
            bexp_free(less);
        }
    }
    if(bexp_ex_is_great(b)){
        RETURN = bexp_make_less(bexp_ex_left(b), bexp_ex_right(b));
    }
    if(bexp_ex_is_great_equal(b)){
        bexp_t *less = bexp_make_less(bexp_ex_left(b), bexp_ex_right(b));
        RETURN = bexp_make_neg(less);
        if(RETURN == NULL) bexp_free(less);
    }
    return RETURN;
}

void bexp_ex_free(bexp_ex_t *b) {
    if(b == NULL) return;
    aexp_free(bexp_ex_left(b));
    aexp_free(bexp_ex_right(b));
    free(b);
}

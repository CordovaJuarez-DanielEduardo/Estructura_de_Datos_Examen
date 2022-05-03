#ifndef ED_BEXP_EX_H_
#define ED_BEXP_EX_H_


#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <bexp.h>
#include <aexp.h>
#include <mexp.h>

/*** EXTENSIONES DE EXPRESIONES BOOLEANAS ***/

struct bexp_ex_t;
typedef struct bexp_ex_t bexp_ex_t;

bool bexp_ex_is_not_equal(bexp_ex_t *b);
bool bexp_ex_is_less_equal(bexp_ex_t *b);
bool bexp_ex_is_great(bexp_ex_t *b);
bool bexp_ex_is_great_equal(bexp_ex_t *b);


bexp_ex_t *bexp_make_not_equal(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_less_equal(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_great(aexp_t *left, aexp_t *right);
bexp_ex_t *bexp_make_great_equal(aexp_t *left, aexp_t *right);

bexp_t *bexp_ex_eval(bexp_ex_t *b);

void bexp_ex_free(bexp_ex_t *b);

#endif  ED_BEXP_EX_H_

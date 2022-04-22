#include <tests.h>
#include <imp.h>

bool a_make_num() {
    aexp_t *a = aexp_make_num(666);
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_num(a), "Esperaba expresión numérica");
    check(aexp_num(a) == 666, "Valor numérico no esperado");
    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_add() {
    aexp_t *a = aexp_make_add(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_add(a), "Experaba que expresión fuera suma");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_sub() {
    aexp_t *a = aexp_make_sub(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_sub(a), "Experaba que expresión fuera resta");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_make_mul() {
    aexp_t *a = aexp_make_mul(aexp_make_num(42),
                              aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_is_mul(a), "Experaba que expresión fuera multiplicación");
    check(aexp_left(a) != NULL, "Esperaba hijo izquierdo");
    check(aexp_right(a) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(aexp_left(a)), "Esperaba hijo izquierdo numérico");
    check(aexp_is_num(aexp_right(a)), "Esperaba hijo derecho numérico");
    check(aexp_num(aexp_left(a)) == 42, "Esperaba hijo izquierdo = 42");
    check(aexp_num(aexp_right(a)) == 666, "Esperaba hijo derecho = 666");

    aexp_free(a);
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_num() {
    aexp_t *a;

    a = aexp_make_num(0);
    check(aexp_eval(a) == 0, "Esperaba que 0 = 0");
    aexp_free(a);

    a = aexp_make_num(666);
    check(aexp_eval(a) == 666, "Esperaba que 666 = 666");
    aexp_free(a);

    a = aexp_make_num(42);
    check(aexp_eval(a) == 42, "Esperaba que 42 = 42");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_add() {
    aexp_t *a;

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 + 0 = 0");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 666, "Esperaba que 0 + 666 = 666");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 708, "Esperaba que 42 + 666 = 708");
    aexp_free(a);

    a = aexp_make_add(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 708, "Esperaba que 666 + 42 = 708");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_sub() {
    aexp_t *a;

    a = aexp_make_sub(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 - 0 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 42 - 666 = 0");
    aexp_free(a);

    a = aexp_make_sub(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 624, "Esperaba que 666 - 42 = 624");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool a_eval_mul() {
    aexp_t *a;

    a = aexp_make_mul(aexp_make_num(0),
                      aexp_make_num(0));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 * 0 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(0),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 0, "Esperaba que 0 * 666 = 0");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(1),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 666, "Esperaba que 1 * 666 = 666");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(42),
                      aexp_make_num(666));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 27972, "Esperaba que 42 * 666 = 27972");
    aexp_free(a);

    a = aexp_make_mul(aexp_make_num(666),
                      aexp_make_num(42));
    check(a != NULL, "Esperaba suficiente memoria");
    check(aexp_eval(a) == 27972, "Esperaba que 666 * 42 = 27972");
    aexp_free(a);
    
    return true;

 fail:
    aexp_free(a);
    return false;
}

bool misdudas() {
    bexp_t *bt = bexp_make_true();
    bexp_t *bf = bexp_make_false();
    check(bt != bf, "Esperaba que true fuera distinto a false");
    
    return true;

 fail:
    return false;
}

bool b_make_truefalse() {
    bexp_t *bt = bexp_make_true();
    bexp_t *bf = bexp_make_false();
    check(bt != NULL, "Esperaba suficiente memoria");
    check(bf != NULL, "Esperaba suficiente memoria");
    check(bt != bf, "Esperaba que true != false");

    bexp_free(bt);
    bexp_free(bf);
    return true;

 fail:
    bexp_free(bt);
    bexp_free(bf);
    return false;
}

bool b_make_equal() {
    bexp_t *b = bexp_make_equal(aexp_make_num(2),
                                aexp_make_num(3));
    check(b != NULL, "Esperaba suficiente memoria :C");
    check(bexp_is_equal(b), "Esperaba que la expresion fuera una igualdad");
    check(bexp_aleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_aright(b) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(bexp_aleft(b)), "Esperaba un numero en el hijo izquierdo");
    check(aexp_is_num(bexp_aright(b)), "Esperaba un numero en el hijo derecho");
    check(aexp_num(bexp_aleft(b)) == 2, "Esperaba que el hijo izquierdo fuera 2");
    check(aexp_num(bexp_aright(b)) == 3, "Esperaba que el hijo derecho fuera 3");

    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_make_less() {
    bexp_t *b = bexp_make_less(aexp_make_num(2),
                               aexp_make_num(3));
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_less(b), "Esperaba que la expresion fuera un menor que");
    check(bexp_aleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_aright(b) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(bexp_aleft(b)), "Esperaba un numero en el hijo izquierdo");
    check(aexp_is_num(bexp_aright(b)), "Esperaba un numero en el hijo derecho");
    check(aexp_num(bexp_aleft(b)) == 2, "Esperaba que el hijo izquierdo fuera 2");
    check(aexp_num(bexp_aright(b)) == 3, "Esperaba que el hijo derecho fuera 3");

    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_make_and() {
    bexp_t *b = bexp_make_and(bexp_make_true(),
                              bexp_make_true());
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_and(b), "Esperaba que la expresion fuera una conjuncion");
    check(bexp_bleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_bright(b) != NULL, "Esperaba hijo derecho");
    check(bexp_eval(bexp_bleft(b)),"Esperaba expresion booleana en hijo izquierdo");
    check(bexp_eval(bexp_bright(b)),"Esperaba expresion booleana en hijo derecho");    
    
    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_make_or() {
    bexp_t *b = bexp_make_or(bexp_make_true(),
                              bexp_make_false());
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_or(b), "Esperaba que la expresion fuera una disyuncion");
    check(bexp_bleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_bright(b) != NULL, "Esperaba hijo derecho");
    check(bexp_eval(bexp_bleft(b)),"Esperaba expresion booleana en hijo izquierdo");
    check(bexp_eval(bexp_bright(b)),"Esperaba expresion booleana en hijo derecho");
    
    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_make_neg() {
    bexp_t *b = bexp_make_neg(bexp_make_false());
    
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_neg(b), "Esperaba que la expresion fuera una negacion");
    check(bexp_nchild(b) != NULL, "Esperaba un hijo");
    check(bexp_eval(bexp_nchild(b)),"Espera expresion booleana en hijo");
    
    bexp_free(b);
    return true;
 fail:
    bexp_free(b);
    return false;
}

bool b_eval_truefalse() {
     bexp_t *b = bexp_make_or(bexp_make_true(),
                              bexp_make_false());
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_bleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_bright(b) != NULL, "Esperaba hijo derecho");
    check(bexp_is_true(bexp_bleft(b)),"Espera \"true\" en hijo izquierdo");
    check(bexp_is_false(bexp_bright(b)),"Espera \"false\" en hijo derecho");
    check(bexp_eval(bexp_bleft(b)),"Esperaba que hijo izquierdo fuera \"true\"");
    check(bexp_eval(!bexp_bright(b)),"Esperaba que hijo derecho fuera \"false\"");
    
    bexp_free(b);
    return true;
 fail:
    bexp_free(b);
    return false;
}

bool b_eval_equal() {
    bexp_t *b = bexp_make_equal(aexp_make_num(2),
                               aexp_make_num(3));
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_equal(b), "Esperaba que la expresion fuera una igualdad");
    check(bexp_aleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_aright(b) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(bexp_aleft(b)), "Esperaba un numero en el hijo izquierdo");
    check(aexp_is_num(bexp_aright(b)), "Esperaba un numero en el hijo derecho");
    check(aexp_num(bexp_aleft(b)) == 2, "Esperaba que el hijo izquierdo fuera 2");
    check(aexp_num(bexp_aright(b)) == 3, "Esperaba que el hijo derecho fuera 3");
    check(!bexp_eval(b), "Esperaba que la evaluacion devolviera un \"false\"");

    bexp_free(b);
    return true;

fail:
    bexp_free(b);
    return false;
}

bool b_eval_less() {
    bexp_t *b = bexp_make_equal(aexp_make_num(2),
                               aexp_make_num(3));
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_less(b), "Esperaba que la expresion fuera un menor que");
    check(bexp_aleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_aright(b) != NULL, "Esperaba hijo derecho");
    check(aexp_is_num(bexp_aleft(b)), "Esperaba un numero en el hijo izquierdo");
    check(aexp_is_num(bexp_aright(b)), "Esperaba un numero en el hijo derecho");
    check(aexp_num(bexp_aleft(b)) == 2, "Esperaba que el hijo izquierdo fuera 2");
    check(aexp_num(bexp_aright(b)) == 3, "Esperaba que el hijo derecho fuera 3");
    check(bexp_eval(b), "Esperaba que hijo izquierdo fuera menor que hijo derecho");

    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_eval_and() {
    bexp_t *b = bexp_make_and(bexp_make_true(),
                              bexp_make_true());
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_and(b), "Esperaba que la expresion fuera una conjuncion");
    check(bexp_bleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_bright(b) != NULL, "Esperaba hijo derecho");
    check(bexp_eval(bexp_bleft(b)),"Esperaba expresion booleana en hijo izquierdo");
    check(bexp_eval(bexp_bright(b)),"Esperaba expresion booleana en hijo derecho");
    check(bexp_eval(b),"Esperaba que ambos hijos fueran \"true\"");
    
    
    bexp_free(b);
    return true;

 fail:
    bexp_free(b);
    return false;
}

bool b_eval_or() {
    bexp_t *b = bexp_make_or(bexp_make_true(),
                              bexp_make_false());
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_or(b), "Esperaba que la expresion fuera una disyuncion");
    check(bexp_bleft(b) != NULL, "Esperaba hijo izquierdo");
    check(bexp_bright(b) != NULL, "Esperaba hijo derecho");
    check(bexp_eval(bexp_bleft(b)),"Esperaba expresion booleana en hijo izquierdo");
    check(bexp_eval(bexp_bright(b)),"Esperaba expresion booleana en hijo derecho");
    check(bexp_eval(b),"Esperaba que por lo menos uno de los hijos fuera \"true\"");
    
    bexp_free(b);
    return true;

fail:
    bexp_free(b);
    return false;
}

bool b_eval_neg() {
    bexp_t *b = bexp_make_neg(bexp_make_false());
    
    check(b != NULL, "Esperaba suficiente memoria");
    check(bexp_is_neg(b), "Esperaba que la expresion fuera una negacion");
    check(bexp_nchild(b) != NULL, "Esperaba un hijo");
    check(bexp_eval(bexp_nchild(b)),"Espera expresion booleana en hijo");
    check(bexp_eval(b),"Esperaba que la negacion del hijo fuera \"true\"");
    
    bexp_free(b);
    return true;
fail:
    bexp_free(b);
    return false;
}

int main() {
    fprintf(stderr, "- Probando expresiones aritméticas\n");
    run_test(a_make_num);
    run_test(a_make_add);
    run_test(a_make_sub);
    run_test(a_make_mul);
    run_test(a_eval_num);
    run_test(a_eval_add);
    run_test(a_eval_sub);
    run_test(a_eval_mul);
    fprintf(stderr, "- Probando expresiones booleanas\n");
    run_test(b_make_truefalse);
    run_test(b_make_equal);
    run_test(b_make_less);
    run_test(b_make_and);
    run_test(b_make_or);
    run_test(b_make_neg);
    run_test(b_eval_truefalse);
    run_test(b_eval_equal);
    run_test(b_eval_less);
    run_test(b_eval_and);
    run_test(b_eval_or);
    run_test(b_eval_neg);
    /* run_test(misdudas); */
}

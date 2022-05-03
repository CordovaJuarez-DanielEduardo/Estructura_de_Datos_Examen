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

/*****************************
* EVALUADORES PARA EL EXAMEN *
*****************************/

//EVALUADOR DE NODOS
bool n_make_nodo(){
    nodo *n = nodo_make(0);
    
    check(n != NULL, "Esperaba suficiente memoria");
    check(nodo_indice(n) == 0, "Esperaba valor 0 en el indice");
    check(nodo_val(n) == 0, "Esperaba valor 0 en el valor de nodo");
    check(nodo_left(n) == NULL, "No se esperaba un hijo izquierdo");
    check(nodo_right(n) == NULL, "No se esperaba un hijo derecho");
    
    nodo_free(n);
    return true;
fail:
    nodo_free(n);
    return false;
}

//EVALUADOR DE MEMORIA
bool m_eval_init(){
    mexp_t *x = mexp_init();
    
    check(x != NULL, "Esperaba suficiente memoria");
    check(mexp_lista(x) == NULL, "Esperaba una \"lista\" vacia");
    
    mexp_free(x);
    return true;
fail:
    mexp_free(x);
    return false;
}

bool m_eval_add(){
    mexp_t *x = mexp_init();
    check(x != NULL, "Esperaba suficiente memoria para \"mexp_t\"");
    check(mexp_lista(x) == NULL, "Esperaba una \"lista\" vacia");
    
    nodo *root = mexp_add(mexp_make_nodo(1), x);
    check(root != NULL, "Esperaba suficiente memoria para crear una raiz");
    check(nodo_indice(root) == 1, "Esperaba que el indice de root fuera 1");
    check(nodo_val(root) == 0, "Esperaba que el valor de root fuera 0");
    check(nodo_left(root) == NULL, "No esperaba hijo izquierdo en root");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho en root");
    
    nodo *left = mexp_add(mexp_make_nodo(0, 23), x);
    check(left != NULL, "Esperaba suficiente memoria para crear un hijo izquierdo");
    check(nodo_indice(left) == 0, "Esperaba que el indice de left fuera 0");
    check(nodo_val(left) == 23, "Esperaba que el valor de left fuera 23");
    check(nodo_left(left) == NULL, "No esperaba hijo izquierdo en left");
    check(nodo_right(left) == NULL, "No esperaba hijo derecho en left");
    
    check(nodo_left(root) == *left, "Esperaba la indireccion de left como hijo izquierdo");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho");
    
    nodo *right = mexp_add(mexp_make_nodo(8, 23), x);
    check(right != NULL, "Esperaba suficiente memoria para crear un hijo derecho");
    check(nodo_indice(right) == 8, "Esperaba que el indice de right fuera 8");
    check(nodo_val(right) == 23, "Esperaba que el valor de right fuera 23");
    check(nodo_left(right) == NULL, "No esperaba hijo izquierdo en right");
    check(nodo_right(right) == NULL, "No esperaba hijo derecho en right");
    
    check(nodo_left(root) == *left, "Esperaba la indireccion de left como hijo izquierdo en root");
    check(nodo_right(root) == *right, "Esperaba la indireccion de right como hijo derecho en root");
    
    mexp_free(x);
    return true;
fail:
    mexp_free(x);
    return false;
}

bool m_eval_busca(){
    mexp_t *x = mexp_init();
    
    check(x != NULL, "Esperaba suficiente memoria para \"mexp_t\"");
    check(mexp_busca(0, x) == NULL, "Esperaba una \"lista\" vacia");
    
    nodo *root = mexp_add(mexp_make_nodo(1), x);
    check(root != NULL, "Esperaba suficiente memoria para crear una raiz");
    check(nodo_indice(root) == 1, "Esperaba que el indice de root fuera 1");
    check(nodo_val(root) == 0, "Esperaba que el valor de root fuera 0");
    check(nodo_left(root) == NULL, "No esperaba hijo izquierdo en root");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho en root");
    
    nodo *left = mexp_add(mexp_make_nodo(0, 23), x);
    check(left != NULL, "Esperaba suficiente memoria para crear un hijo izquierdo");
    check(nodo_indice(left) == 0, "Esperaba que el indice de left fuera 0");
    check(nodo_val(left) == 23, "Esperaba que el valor de left fuera 23");
    check(nodo_left(left) == NULL, "No esperaba hijo izquierdo en left");
    check(nodo_right(left) == NULL, "No esperaba hijo derecho en left");
    
    check(nodo_left(root) == *left, "Esperaba la indireccion de left como hijo izquierdo");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho");
    
    nodo *right = mexp_add(mexp_make_nodo(8, 23), x);
    check(right != NULL, "Esperaba suficiente memoria para crear un hijo derecho");
    check(nodo_indice(right) == 8, "Esperaba que el indice de right fuera 8");
    check(nodo_val(right) == 23, "Esperaba que el valor de right fuera 23");
    check(nodo_left(right) == NULL, "No esperaba hijo izquierdo en right");
    check(nodo_right(right) == NULL, "No esperaba hijo derecho en right");
    
    check(mexp_busca(0, x) == *left, "Esperaba recibir la indireccion de left, luego de la llamada a funcion");
    check(mexp_busca(8, x) == *right, "Esperaba recibir la indireccion de right, luego de la llamada a funcion");
    check(mexp_busca(16, x) == NULL, "Esperaba recibir NULL, luego de la llamada a funcion");
    
    mexp_free(x);
    return true;
fail:
    mexp_free(x);
    return false;
}

bool m_eval_obten_val(){
    mexp_t *x = mexp_init();
    
    check(x != NULL, "Esperaba suficiente memoria para \"mexp_t\"");
    check(mexp_busca(0, x) == NULL, "Esperaba una \"lista\" vacia");
    
    nodo *root = mexp_add(mexp_make_nodo(1), x);
    check(root != NULL, "Esperaba suficiente memoria para crear una raiz");
    check(nodo_indice(root) == 1, "Esperaba que el indice de root fuera 1");
    check(nodo_val(root) == 0, "Esperaba que el valor de root fuera 0");
    check(nodo_left(root) == NULL, "No esperaba hijo izquierdo en root");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho en root");
    
    nodo *left = mexp_add(mexp_make_nodo(0, 23), x);
    check(left != NULL, "Esperaba suficiente memoria para crear un hijo izquierdo");
    check(nodo_indice(left) == 0, "Esperaba que el indice de left fuera 0");
    check(nodo_val(left) == 23, "Esperaba que el valor de left fuera 23");
    check(nodo_left(left) == NULL, "No esperaba hijo izquierdo en left");
    check(nodo_right(left) == NULL, "No esperaba hijo derecho en left");
    
    check(nodo_left(root) == *left, "Esperaba la indireccion de left como hijo izquierdo");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho");
    
    nodo *right = mexp_add(mexp_make_nodo(8, 23), x);
    check(right != NULL, "Esperaba suficiente memoria para crear un hijo derecho");
    check(nodo_indice(right) == 8, "Esperaba que el indice de right fuera 8");
    check(nodo_val(right) == 23, "Esperaba que el valor de right fuera 23");
    check(nodo_left(right) == NULL, "No esperaba hijo izquierdo en right");
    check(nodo_right(right) == NULL, "No esperaba hijo derecho en right");
    
    check(nodo_left(root) == *left, "Esperaba la indireccion de left como hijo izquierdo en root");
    check(nodo_right(root) == *right, "Esperaba la indireccion de right como hijo derecho en root");
    
    check(mexp_obten_val(0, x) == nodo_val(left), "Esperaba recibir el valor de left, luego de la llamada a funcion");
    check(mexp_obten_val(8, x) == nodo_val(right), "Esperaba recibir el valor de right, luego de la llamada a funcion");
    check(mexp_obten_val(16, x) == 0, "Esperaba recibir 0, luego de la llamada a funcion");
    
    mexp_free(x);
    return true;
fail:
    mexp_free(x);
    return false;
}
bool a_make_mem(){
    mexp_t *x = mexp_init();
    check(x != NULL, "Esperaba sufuciente memoria para crear \"mexp_t\"");
    
    aexp_t *a = aexp_make_mem(aexp_make_sub(2,1), x);
    check(a != NULL, "Esperaba suficiente memoria para crear a1");
    check(aexp_is_mem(a), "Esperaba que la expresion fuera \"creacion\" de memoria, para a1");
    check(aexp_indice(a) == 1, "Esperaba que el indice de a1 fuera 1");
    check(a->x == &x, "Esperaba que la expresion aritmetica guardara la direccion de x");
    
    mexp_free(x);
    aexp_free(a);
    return true;
fail:
    mexp_free(x);
    aexp_free(a);
    return false;
}

bool a_eval_mem(){
    mexp_t *x = mexp_init();
    check(x != NULL, "Esperaba sufuciente memoria para crear \"mexp_t\"");
    aexp_t *a1 = aexp_make_mem(aexp_make_num(1), x);
    
    check(a1 != NULL, "Esperaba suficiente memoria para crear a1");
    check(aexp_eval(a1) == 0, "Esperaba que se devolviera el indice de la memoria \"creada\"");
    
    nodo *root = mexp_lista(x);
    check(root != NULL, "Esperaba una raiz en memoria");
    check(nodo_indice(root) == 1, "Esperaba un 1 en el indice de root");
    check(nodo_val(root) == 0, "Esperaba un 0 en el valor de root");
    check(nodo_left(root) == NULL, "No esperaba hijo izquierdo en root");
    check(nodo_right(root) == NULL, "No esperaba hijo derecho en root");
    
    aexp_t *a2 = aexp_make_mem(aexp_make_sub(aexp_make_num(8),aexp_make_num(6)), x);
    check(a2 != NULL, "Esperaba suficiente memoria para crear a2");
    check(aexp_is_mem(a2), "Esperaba que la expresion fuera \"creacion\" de memoria, para a2");
    check(aexp_eval(a2) == 2, "Esperaba que el indice de a2 fuera 2");
    
    nodo *right = mexp_busca(aexp_eval(aexp_indice(a)), x);
    check(nodo_right(root) == *right, "Esperaba que el hijo derecho de root fuera el nodo creado con a2");
    check(nodo_left(root) == NULL, "No esperaba un hijo izquierdo en root");
    
    nodo *a_rep = mexp_add(2, x);
    nodo *n_rep = mexp_busca(2, x);
    check(a_rep == NULL, "Esperaba que el elemento agregado estuviese repetido");
    check(*n_rep == *right, "Esperaba que las indirecciones coincidieran");

    aexp_free(a1);
    aexp_free(a2);
    mexp_free(x);
    return true;
fail:
    aexp_free(a1);
    aexp_free(a2);
    mexp_free(x);
    return false;
}

bool p_make_skip(){
    pexp_t *p = pexp_make_skip();
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_is_skip(p), "Esperaba que el programa creado fuera skip");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_make_sec(){
    pexp_t *p = pexp_make_sec(pexp_make_skip(), pexp_make_skip());
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_is_sec(p), "Esperaba que se creara una secuencia de programas");
    check(pexp_is_skip(pexp_main(p)), "Esperaba que el primer programa fuera un skip");
    check(pexp_is_skip(pexp_sec(p)), "Esperaba que el segundo programa fuera un skip");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_make_ass(){
    pexp_t *p = pexp_make_ass(aexp_make_num(2), aexp_make_num(3));
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_is_ass(p), "Esperaba que el programa fuera una asignacion de memoria");
    check(aexp_is_num(pexp_indice(p)), "Esperaba una expresion aritmetica en el indice");
    check(aexp_is_num(pexp_val(p)), "Esperaba una expresion aritmetica en el valor");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_make_while(){
    pexp_t *p = pexp_make_while(bexp_make_true(), pexp_make_skip());
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_is_while(p), "Esperaba que el programa fuera un while");
    check(bexp_is_true(pexp_bool(p)), "Esperaba que la expresion booleana fuera true");
    check(pexp_is_skip(pexp_main(p)), "Esperaba que el programa principal fuera un skip");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_make_if(){
    pexp_t *p = pexp_make_if(bexp_make_true(), pexp_make_skip(), pexp_make_skip());
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_is_if(p), "Esperaba que el programa fuera un condicional");
    check(bexp_is_true(pexp_bool(p)), "Esperaba que la expresion booleana fuera true");
    check(pexp_is_skip(pexp_main(p)), "Esperaba que el programa principal fuera un skip");
    check(pexp_is_skip(pexp_else(p)), "Esperaba un programa skip, en \"else\"");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_eval_skip(){
    pexp_t *p = pexp_make_skip();
    
    check(p != NULL, "Esperaba suficiente memoria");
    check(pexp_eval(p) != NULL, "No esperaba una respuesta del evaluador");
    
    pexp_free(p);
    return true;
fail:
    pexp_free(p);
    return false;
}

bool p_eval_sec(){
    pexp_t *p = pexp_sec(pexp_make_ass(aexp_make_num(1), aexp_make_num(10)),
                         pexp_make_ass(aexp_make_num(3), aexp_make_num(666)));
    mexp_t *x = mexp_init();
    
    check(p != NULL, "Esperaba suficiente memoria para el programa");
    check(x != NULL, "Esperaba suficiente memoria para la memoria");
    
    pexp_eval(p);
    nodo *root = mexp_busca(1, x);
    nodo *right = mexp_busca(3, x);
    
    check(root != NULL, "Esperaba un nodo en root");
    check(right != NULL, "Esperaba un nodo en right");
    check(nodo_indice(root) == 1, "Esperaba root con indice 1");
    check(nodo_val(root) == 10, "Esperaba valor 10, en root");
    check(nodo_indice(right) == 3, "Esperaba right con indice 3");
    check(nodo_val(right) == 666, "Esperaba valor 666, en right");
    
    pexp_free(p);
    mexp_free(x);
    return true;
fail:
    pexp_free(p);
    mexp_free(x);
    return false;
}

bool p_eval_if(){
    pexp_t *p = pexp_if(bexp_make_true(),
                            pexp_make_ass(aexp_make_num(3), aexp_make_num(666)),
                            pexp_make_ass(aexp_make_num(3), aexp_make_num(0)));
    mexp_t *x = mexp_init();
    
    check(p != NULL, "Esperaba suficiente memoria para el programa");
    check(x != NULL, "Esperaba suficiente memoria para la memoria");
    
    pexp_eval(p);
    nodo *root = mexp_busca(3, x);
    //Caso de if true
    check(root != NULL, "Esperaba un nodo en root");
    check(nodo_indice(root) == 3, "Esperaba root con indice 3");
    check(nodo_val(root) == 666, "Esperaba valor 666, en root");
    
    //Caso de if false
    p->b = bexp_make_false();
    pexp_eval(p);
    check(nodo_indice(root) == 3, "Esperaba right con indice 3");
    check(nodo_val(root) == 0, "Esperaba valor 0, en root");
    
    pexp_free(p);
    mexp_free(x);
    return true;
fail:
    pexp_free(p);
    mexp_free(x);
    return false;
}

bool p_eval_ass(){
    pexp_t *p = pexp_make_ass(aexp_make_add(aexp_make_num(4),
                                            aexp_make_num(2)),
                              aexp_make_num(66));
    
    mexp_t *x = mexp_init();
    check(p != NULL, "Esperaba suficiente memoria para el programa");
    check(x != NULL, "Esperaba suficiente memoria para la memoria");
    check(pexp_eval(p) == 66, "Esperaba asignacion de memoria con valor 66");
    
    nodo *root = mexp_lista(x);
    check(nodo_indice(root) == 6, "Esperaba indice 6, en root");
    check(nodo_val(root) == 66, "Esperaba valor 66, en root");
    
    pexp_free(p);
    mexp_free(x);
    return true;
fail:
    pexp_free(p);
    mexp_free(x);
    return false;    
}

bool p_eval_while(){
    mexp_t *x = mexp_init(); 
    
    
   
    aexp_t *in_salida = aexp_make_num(0);
    aexp_t *salida = aexp_make_num(1);
    
    aexp_t *in_fac = aexp_make_num(1);
    aexp_t *fac = aexp_make_num(5);
    
    aexp_t *in_aux = aexp_make_num(2);
    aexp_t *aux = aexp_make_num(1);    
    aexp_t *incremento = aexp_make_num(1);
    
    
    aexp_t *mul = aexp_make_mul(salida, aux);
    aexp_t *add = aexp_make_add(aux, incremento);
    
    pexp_t *calcula = pexp_make_sec(pexp_make_ass(in_salida,
                                                  mul),
                                    pexp_make_ass(in_aux,
                                                  add));
    
    bexp_t *compara = bexp_make_or(bexp_make_less(mexp_busca(in_aux, x), mexp_busca(in_fac, x)),
                                    bexp_make_equal(mexp_busca(in_aux, x), mexp_busca(in_fac, x)));
    
    
    check(p != NULL, "Esperaba suficiente memoria para inicializar el factorial");
    
    pexp_t *factorial = pexp_make_while();
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
    fprintf(stderr, "- Probando expresiones de memoria\n");
    run_test(n_make_nodo)
    run_test(m_eval_init);
    run_test(m_eval_add);
    run_test(m_eval_busca);
    run_test(m_eval_obten_val);
    
    run_test(a_make_mem);
    run_test(a_eval_mem);
    
    fprintf(stderr, "- Probando expresiones de programas\n");
    run_test(p_make_skip);
    run_test(p_make_sec);
    run_test(p_make_ass);
    run_test(p_make_while);
    run_test(p_make_if);
    run_test(p_eval_skip);
    run_test(p_eval_sec);
    run_test(p_eval_ass);
    run_test(p_eval_if);
    run_test(p_eval_while);
}

#pragma once
#include "mpc.h"

typedef struct lval {
    int type;
    long num;
    char* err;
    char* sym;
    int count;
    struct lval** cell;
} lval;

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

lval* lval_err(char* m);
lval* lval_num(long x);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_read(mpc_ast_t* t);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_add(lval* v, lval* x);
void lval_expr_print(lval* v, char open, char close);
void lval_print(lval* v);
void lval_println(lval* v);
void lval_del(lval* v);

lval* lval_eval_sexpr(lval* v);
lval* lval_eval(lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
lval* builtin(lval* a, char* func);
lval* builtin_list(lval* a);
lval* builtin_head(lval* a);
lval* builtin_tail(lval* a);
lval* builtin_join(lval* a);
lval* builtin_eval(lval* a);
lval* builtin_cons(lval* a);
lval* builtin_len(lval* a);
lval* builtin_init(lval* a);
lval* builtin_op(lval* a, char* op);

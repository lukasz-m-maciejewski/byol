#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

#include "mpc.h"
#include "lval.h"

lval eval(mpc_ast_t* t);
lval eval_op(lval x, char* op, lval y);

int main() {
    puts("Lispy Version 0.0.6");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Integer = mpc_new("integer");
    mpc_parser_t* Double = mpc_new("double");
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Symbol = mpc_new("symbol");
    mpc_parser_t* Sexpr = mpc_new("sexpr");
    mpc_parser_t* Qexpr = mpc_new("qexpr");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
        "         \
          integer : /-?[0-9]+/ ;                              \
          double  : /-?[0-9]+\\.[0-9]+/ ;                     \
          number  : <integer> ;                               \
          symbol  : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;        \
          sexpr   : '(' <expr>* ')' ;                         \
          qexpr   : '{' <expr>* '}' ;                         \
          expr    : <number> | <symbol> | <sexpr> | <qexpr> ; \
          lispy   : /^/ <expr>* /$/ ;  ",
              Integer, Double, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);

    lenv* e = lenv_new();
    lenv_add_builtins(e);

    while (1) {
        char* input = readline("lispy> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            mpc_ast_print(r.output);
            //lval result = eval(r.output);
            printf("out> ");
            //lval_println(result);
            lval* x = lval_read(r.output);
            lval_println(x);
            printf("res> ");
            x = lval_eval(e, x);

            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    lenv_del(e);
    mpc_cleanup(8, Integer, Double, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);
    return 0;
}

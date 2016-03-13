#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

#include "mpc.h"

int main(int argc, char** argv) {
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Right_expr = mpc_new("right_expr");
    mpc_parser_t* Infixy = mpc_new("infixy");

    mpca_lang(MPCA_LANG_DEFAULT,
        "         \
          number : /-?[0-9]+(\\.[0-9]+)?/ ; \
          operator : '+' | '-' | '*' | '/' | \"div\" ; \
          expr : <number> | '(' <expr> <right_expr>+ ')' ; \
          right_expr : <operator> <expr> ; \
          infixy : /^/ <expr> <right_expr>+ /$/ ;  ",
              Number, Operator, Expr, Right_expr, Infixy);

    while (1) {
        char* input = readline("infixy> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Infixy, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(5, Number, Operator, Expr, Right_expr, Infixy);
    return 0;
}

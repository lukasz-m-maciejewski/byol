#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

#include "mpc.h"

int main(int argc, char** argv) {
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");

    mpc_parser_t* Adjective = mpc_new("adjective");
    mpc_parser_t* Noun = mpc_new("noun");
    mpc_parser_t* Phrase = mpc_new("phrase");
    mpc_parser_t* Doge = mpc_new("doge");

    mpca_lang(MPCA_LANG_DEFAULT,
        "         \
          adjective : \"wow\" | \"many\" | \"so\" | \"such\"; \
          noun      : \"lisp\" | \"language\" | \"book\" | \"build\" | \"c\" ; \
          phrase    : <adjective> <noun> ; \
          doge      : /^/ <phrase>+ /$/ ;  ",
              Adjective, Noun, Phrase, Doge);

    while (1) {
        char* input = readline("doge> ");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Doge, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(4, Adjective, Noun, Phrase, Doge);
    return 0;
}

#include "s21_cat.h"

void e_func(counters dta, param_list params, char c) {
    if (params.e) {
        if (c == '\n' && !dta.vl_co) {
            printf("$");
        }
    }
}

void n_func(counters *dta, param_list params) {
    if (params.n && !params.b && !dta->vl_co) {
        if (dta->l_co == 1 || dta->pc_co == '\n') {
            printf("%6d\t", dta->l_co++);
        }
    }
}

void b_func(counters *dta, param_list params, char c) {
    if (params.b) {
        if (dta->l_co == 1 && c != '\n') {
            printf("%6d\t", dta->l_co++);
        } else if (dta->pc_co == '\n' && c != '\n') {
            printf("%6d\t", dta->l_co++);
        }
    }
}

void non_func(counters dta, char c) {
    if (!dta.vl_co) {
        printf("%c", c);
    }
}

void s_func(param_list params, counters *dta, char *c) {
    if (params.s) {
        if (dta->pc_co == '\n' && *c == '\n' && !dta->vl_co) {
            n_func(dta, params);
            b_func(dta, params, *c);
            e_func(*dta, params, *c);
            v_func(params, c);
            non_func(*dta, *c);
            dta->vl_co = 1;
        } else if (dta->vl_co && *c != '\n') {
            dta->vl_co = 0;
        }
    }
}

void t_func(param_list params, char *c) {
    if (params.t) {
        if (*c =='\t') {
            printf("^");
            *c = 'I';
        }
    }
}

void v_func_ch(int *ch, char *c) {
    if (*c < 0) {
        *c &= 127;
        *ch = (int)*c;
        *ch += 128;
    }
}

void v_func(param_list params, char *c) {
    if (params.v) {
        int ch = (int)*c;
        v_func_ch(&ch, c);
        if (ch != 9 && ch != 10 && ch < 32) {
            printf("^");
            *c += 64;
        } else if (ch == 127) {
            printf("^");
            *c = '?';
        } else if (ch > 127 && ch < 160) {
            printf("M-^");
            *c = ch - 64;
        } else if (ch > 160 && ch <= 255) {
            *c -= 128;
        }
    }
}


void fullfill_dta(counters *dta, char c) {
    dta->l_co = 1;
    dta->pc_co = c;
    dta->vl_co = 0;
}

void file_true(FILE* file, param_list params) {
    char c = fgetc(file);
    counters dta = {0};
    fullfill_dta(&dta, c);
    while (!feof(file)) {
        s_func(params, &dta, &c);
        n_func(&dta, params);
        b_func(&dta, params, c);
        e_func(dta, params, c);
        v_func(params, &c);
        t_func(params, &c);
        non_func(dta, c);
        dta.pc_co = c;
        c = fgetc(file);
    }
    fclose(file);
}

void file_false(char *argv[], int pos) {
    printf("cat: %s: No such file or directory\n", argv[pos]);
}

void parse_false(char *argv[], int i, int j) {
    printf("cat: illegal option -- %c\nusage: cat [-benstuv] [file ""...]\n", argv[i][j]);
}

void file_output_(char *argv[], int argc, int pos, param_list params) {
    for (; pos < argc; pos++) {
        FILE* file = fopen(argv[pos], "rt");
        if (file == NULL) {
            file_false(argv, pos);
        } else {
            file_true((FILE*)file, params);
        }
    }
}

void var_pars(int GNU_f, char *argv[], int i, int j, param_list *params, int *result, int *err) {
    if (GNU_f) {
        if (argv[i][j] == 'b') {
            params->b = 1;
        } else if (argv[i][j] == 'e') {
            params->e = 1;
            params->v = 1;
        } else if (argv[i][j] == 'v') {
            params->v = 1;
        } else if (argv[i][j] == 'n') {
            params->n = 1;
        } else if (argv[i][j] == 's') {
            params->s = 1;
        } else if (argv[i][j] == 't') {
            params->t = 1;
            params->v = 1;
        } else {
            *result = -1;
            parse_false(argv, i, j);
            *err = 0;
        }
    }
}

void var_pars_GNU(int *GNU_f, char *argv[], int i, int j, param_list *params, int *result, int *err) {
    if (!strcmp(G_b, argv[i])) {
        params->b = 1;
        *GNU_f = 0;
    } else if (!strcmp(G_n, argv[i])) {
        params->n = 1;
        *GNU_f = 0;
    } else if (!strcmp(G_s, argv[i])) {
        params->s = 1;
        *GNU_f = 0;
    } else {
        *GNU_f = 0;
        *result = -1;
        parse_false(argv, i, j);
        *err = 0;
    }
}

void pars_var_(int *result, int i, char *argv[], param_list *params) {
    for (size_t j = 1; j < strlen(argv[i]) && *result == 0; ++j) {
        int GNU_f = 1;
        int err = 1;
        #if defined(__linux__)
        if (argv[i][1] == '-') {
            var_pars_GNU(&GNU_f, argv, i, j, params, result, &err);
            if (!err) {
                break;
            }
        } else if (argv[i][j] == 'T') {
            params->t = 1;
            GNU_f = 0;
        } else if (argv[i][j] == 'E') {
            params->e = 1;
            GNU_f = 0;
        }
        #endif
        var_pars(GNU_f, argv, i, j, params, result, &err);
        if (!err) {
            break;
        }
    }
}


void pars_(int *result, int i, char *argv[], param_list *params) {
    if (argv[i][0] == '-') {
        pars_var_(result, i, argv, params);
    } else {
        *result = i;
    }
}

int shift_argv_(int argc, char *argv[], param_list *params) {
    int result = 0;
    int i = 1;
    for (; i < argc && result == 0; i++) {
        pars_(&result, i, argv, params);
    }
    return result;
}

int main(int argc, char *argv[]) {
    param_list params = {0};
    int pos = shift_argv_(argc, argv, &params);
    if (!pos) {
        printf("std in");
    } else if (pos != -1) {
        file_output_(argv, argc, pos, params);
    }
    return 0;
}

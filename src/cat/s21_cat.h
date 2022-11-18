#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

#define G_b "--number-nonblank"
#define G_n "--number"
#define G_s "--squeeze-blank"

typedef struct flags {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
    int T;
} param_list;

typedef struct co {
    int l_co;
    int vl_co;
    char pc_co;
}counters;


int shift_argv_(int argc, char *argv[], param_list *params);

void pars_(int *result, int i, char *argv[], param_list *params);

void pars_var_(int *result, int i, char *argv[], param_list *params);

void file_output_(char *argv[], int argc, int pos, param_list params);

void e_func(counters dta, param_list params, char c);

void n_func(counters *dta, param_list params);

void b_func(counters *dta, param_list params, char c);

void non_func(counters dta, char c);

void s_func(param_list params, counters *dta, char *c);

void fullfill_dta(counters *dta, char c);

void t_func(param_list params, char *c);

void v_func(param_list params, char *c);

void v_func_ch(int *ch, char *c);

void file_false(char *argv[], int pos);

void file_true(FILE* file, param_list params);

void parse_false(char *argv[], int i, int j);

void var_pars(int GNU_f, char *argv[], int i, int j, param_list *params, int *result, int *err);

#endif  // SRC_CAT_S21_CAT_H_

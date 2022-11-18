#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static const char *er1 = "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n"
                         "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
                         "\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n"
                         "\t[--null] [pattern] [file ...]\n";

static const char *er2 = "No files found\n";

static const char *er3 = "No such file or directory\n";

static const char *er4 = "Regex comp. fail\n";

static const char *er5 = "grep: invalid option -- ";

static const char *er6 = "grep: option requires an argument -- ";

typedef struct pos_match {
    int so;
    int eo;
}pm;

typedef struct fparams {
    int count_line;
    int line_true;
    int count_line_match;
    int no_match_line;
    int void_out;
    int first_match;
}fp;

typedef struct f_or_t {
    int ft;
    char *name;
}fot;

typedef struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int f_c;
    int t_rue;
    fot *ft;
} fl;

int N_a(int f_n);

int s21_grep(int argc, char *argv[]);

int sh_argc(int argc, char *argv[], fl *f);

int pr_argv(int argc, char *argv[], fl *f, int *i);

int sh_argv_f(int argc, char *argv[], fl *f, int *i);

int init_flag(int j, char c, int *i, char *argv[], fl *f, int argc);

int fe_init(char *argv[], int *i, int j, fl *f, int argc);

int sh_argv_ft(char* st, fl *f, int i);

int output_file(int argc, fl f);

void open_file(fl f, int i, int argc);

void t_tf(fl *f, int argc);

size_t str_ln(const char *string);

int is_f_null(int i, fl f);

void file_null(fl f, int i);

void nl_fo_el(char * line);

long int is_void_file(FILE *f_file);

void c_func(fl f, int i, int argc, FILE * file);

void recurs_o(char *str, pm *pos_match, fl f, int j, int *pos);

void o_func(fl f, int i, int argc, FILE *file);

int recourse_other(char *str, fl f, fp *fl, int j);

void other_func(fl f, int i, int argc, FILE *file);

#endif  // SRC_GREP_S21_GREP_H_

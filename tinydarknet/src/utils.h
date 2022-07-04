#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <time.h>
#include "darknet.h"
#include "list.h"

#define TIME(a) \
    do { \
    double start = what_time_is_it_now(); \
    a; \
    printf("%s took: %f seconds\n", #a, what_time_is_it_now() - start); \
    } while (0)

#define TWO_PI 6.2831853071795864769252866f


double what_time_is_it_now();
void del_arg(int argc, char **argv, int index);
int find_arg(int argc, char* argv[], char *arg);
int find_int_arg(int argc, char **argv, char *arg, int def);
float find_float_arg(int argc, char **argv, char *arg, float def);
char *find_char_arg(int argc, char **argv, char *arg, char *def);
char *basecfg(char *cfgfile);
float sec(clock_t clocks);
void top_k(float *a, int n, int k, int *index);
void error(const char *s);
void file_error(char *s);
void strip(char *s);
void free_ptrs(void **ptrs, int n);
char *fgetl(FILE *fp);
char *copy_string(char *s);
float sum_array(float *a, int n);
int constrain_int(int a, int min, int max);
int rand_int(int min, int max);
float rand_normal();
float rand_uniform(float min, float max);
float rand_scale(float s);


#endif


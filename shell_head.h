#ifndef SHELLL_HEAD_H
#define SHELLL_HEAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define PATH_MAX 1024
extern char **environ;

int main(int arg1, char *arg2[]);

/* join.c file*/
char *_strjoin(char *st1, char *st2);
int _strcomp(char *s1, char *s2);
char *_strcopy(char *dest, char *str);
char *_strdupli(char *str);
int _strlen(const char *str);

/*environment_sn.c*/
int shell_environment(void);
int _sete(char *name, char *value);
char *build(char *name, char *value);
int _unsete(char *name);

/*cd.c file*/
char *_getcwd(void);
int home(void);
int prev(void);
int _cd(char **arg);

/*exit_term.c*/
void print(void);
char *ignore(char *str);
void ctrl_c(int num);
void sexit(char **args, char *line);

/*exe.c file*/
unsigned int _occur(char *s);
char **_strtok(char *str);
int file_status(char *filename);
int _exe(char **tok, char *line, char *args);

/*line_reader.c*/
char *read_line1(void);
char *read_line2(void);
void free_a(char **args);

/*memory.c*/
void *_reallocate(void *ptr, unsigned int old_si, unsigned int new_si);

/*program_man.c*/
int parser(char **tok);

/*prt.c file*/
int get_path(char **args);
char *get_enviro(char *path);
char *cmdbuild(char *token, char *dir);

/*print.c file*/
int _putchar(char ch);
void _print(char *str);

/*hist.c*/
int get_hist(char *input);
int display_history(void);

#endif

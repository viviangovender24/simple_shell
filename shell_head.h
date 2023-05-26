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

/*_interact.c*/
int interact(info_t *form);
int _delim(char b, char *delim);
int _alpha(int f);
int c_atoi(char *d);

/*biuld.c*/
int _egress(info_t *read);
int _currentcd(info_t *read);
int _change(info_t *read);

/*build2.c*/
int _past(info_t *read);
int unset_(info_t *read, char *str);
int set_anonym(info_t *read, char *str);
int print_anonym(list_ *node);
int _mycopy(info_t *read);

/*environ_sn.c*/
int env_now(info_t *read);
char *env_open(info_t *read, const char *call);
int set_env(info_t *read);
int fill_list(info_t *read);

/*erratum.c*/
void _input(char *str);
int _char(char f);
int _writefd(char f, int fd);
int _writesfd(char *str, int fd);

/*erratum_2.c*/
int error_atoi(char *s);
void format_error(info_t *read, char *st);
int format_d(int puts, int fd);
char *change_number(long int no, int base, int flg);
void delete_comments(char *buff);

/*leave.c*/
char *_strncpy(char *dn, char *sc, int m);
char *_strncat(char *dn, char *sc, int m);
char *_strchr(char *s, char f);

/*g_line.c*/
ssize_t fill_buff(info_t *read, char **buf, size_t *len);
ssize_t _myinput(info_t *read);
ssize_t check_buf(info_t *read, char *buf, size_t *b);
int _getline(info_t *read, char **ptr, size_t *length);
void sig_Handler(__attribute__((unused))int sig_num);

/* g_env */
char **g_env(info_t *read);
int unset_env(info_t *read, char *var);
int set_env(info_t *read, char *var, char *val);

/* g_info.c */
void edit_info(info_t *read);
void get_info(info_t *read, char **avt);
void push_info(info_t *read, int all);

/* past.c */
char *get_pastfile(info_t *read);
int write_past(info_t *read);
int read_past(info_t *read);
int build_pastlist(info_t *read, char *buf, int linecount);
int renum_past(info_t *read);

/* files.c */
list_ *plus_node(list_ **head, const char *str, int num);
list_ *node_end(list_ **head, const char *str, int num);
size_t short_list(const list_ *h);
int remove_node(list_t **head, unsigned int idx);
void empty_list(list_ **head_ptr);

/*
#endif

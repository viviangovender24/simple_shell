#ifndef SHELLL_HEAD_H
#define SHELLL_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*_interact.c*/
int interact(info_t *read);
int _delim(char b, char *delim);
int _alpha(int f);
int c_atoi(char *d);

/*biuld.c*/
int _egress(info_t *);
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

/* files_2.c */
size_t _lengthlist(const list_ *p);
char **_stringslist(list_ *head);
size_t _prtlist(const list_ *p);
list_ *node_start(list_ *node, char *prefix, char f);
ssize_t node_idx(list_ *head, list_t *node);

/* main_file.c */
int main_file(int arc, char **arv);

/* recall.c */
int _free(void **ptr);

/* p_ars.c */
int cm_d(info_t *read, char *path);
char *same_chars(char *pathstr, int start, int stop);
char *get_path(info_t *read, char *pathstr, char *cmd);

/* _alloc.c */
char *_memset(char *d, char b, unsigned int m);
void free_str(char **qq);
void *alloc(void *ptr, unsigned int prev_size, unsigned int new_size);

/* _loop.c */
int hsh(info_t *read, char **arv);
int get_builtin(info_t *read);
void get_cmd(info_t *read);
void fork_cmd(info_t *read);


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_;

/**
* struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_ *env;
	list_ *past;
	list_ *same;
	char **environ;
	int env_changed;
	int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#endif

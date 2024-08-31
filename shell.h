#ifndef _SHELL_H_
#define _SHELL_H_

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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
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
} list_t;

/**
 *struct passinfo - Contains pseudo-arguements to pass into a
 *function allowing uniform prototype for function pointer struct.
 *@arg: A string generated from getline containing arguements.
 *@argv: An array of strings generated from arg.
 *@path: A string path for the current command.
 *@argc: The argument count.
 *@line_count: The error count.
 *@err_num: The error code for exit()s.
 *@linecount_flag: If on count this line of input.
 *@fname: The program filename.
 *@env: Linked list local copy of environ.
 *@environ: Custom modified copy of environ from LL env.
 *@history: The history node.
 *@alias: The alias node.
 *@env_changed: On if environ was changed.
 *@status: The return status of the last executed command.
 *@cmd_buf: Address of pointer to cmd_buf, on if chaining.
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: The fd from which to read line input.
 *@histcount: The history line number count.
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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hshell(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int f_command(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path_cmd(info_t *, char *, char *);
void _errputs(char *);
int _errputchar(char);
int _putfd(char c, int fd);
int _putsfdes(char *str, int fd);
int _strlen(char *);
int _strcomp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_str_c(char *, char *);
char *_str_dup(const char *);
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *, int);
char *_strcat(char *, char *, int);
char *_strchar(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memoryset(char *, char, unsigned int);
void sfree(char **);
void *_resize_memory(void *, unsigned int, unsigned int);
int memfree(void **);
int is_interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _strtoi(char *);
int __errstr(char *);
void print_error(info_t *, char *);
int print_decim(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _fhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void reset_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _winenv(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int p_env_list(info_t *);
char **get_env(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *start_node(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:59:18 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/13 16:44:33 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_based/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RST "\033[0m"    // reset to default color
# define RED "\033[1;31m" // bold red
# define G "\033[1;32m"   // bold green
# define Y "\033[1;33m"   // bold Yellow
# define B "\033[1;34m"   // bold blue
# define M "\033[1;35m"   // bold magenta
# define C "\033[1;36m"   // bold cyan
# define W "\033[1;37m"   // bold white

# define DEBUG_MODE 1
# define MAX_ENV_SIZE 1024
# define HEREDOC_TMP ".$%%$XxXxX_heredoc_tmp_XxXxX$%%$"
# define STDIN "$%%$XXXXII<IIXXXX&%%$"
# define STDOUT "$%%$XXXXII>IIXXXX&%%$"
# define APPEND "$%%$XXXXII>>IIXXXX&%%$"
# define HEREDOC "$%%$XXXXII<<IIXXXX&%%$"
# define PROMT "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"
# define COMMAND_NOT_FOUND 127
# define SUCCESS 0
# define FAILURE 1
# define ECHO_CMD "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"
# define CAT "cat"

typedef enum e_token_var // enum for token types
{
	TOKEN_STDIN, // 0 <
	TOKEN_STDOUT, // 1 >
	TOKEN_APPEND, // 2 >>
	TOKEN_HEREDOC, // 3 <<
	TOKEN_PIPE, // 4 |
	TOKEN_STR, // 5
	TOKEN_CMDAND, // 6 &&
	TOKEN_CMDOR, // 7 ||
}							t_token_var;

typedef struct s_token
{
	t_token_var				type;
	char					*value;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_bin_cmd
{
	char					*name;
	char					*path;
}							t_bin_cmd;

typedef struct s_redirections
{
	char					*type;
	char					*destination;
	struct s_redirections	*next;
}							t_redirections;

typedef enum e_atribute
{
	PARENT,
	CHILD,
	CMDOR,
	CMDAND,
}							t_atribute;

typedef struct s_command
{
	char					**arguemnts;
	t_atribute				atribute;
	struct s_redirections	*redirections;
	struct s_command		*next;
	struct s_command		*prev;
}							t_command;

typedef struct s_descriptors
{
	int						original_fds[2];
	int						pipefd[2];
	int						prev_fd;
}							t_descriptor;

// main

// globals

int							manage_exit_status(int set_flag);
bool 						matching_mode(int set_flag);


// parsing

t_command					*parse_tokens(t_token *tokens);
void						add_command(t_command **commands,
								t_command *new_command);
t_command					*create_command(char **args, t_atribute atribute);
void						free_commands(t_command *commands);

// redirections

char						**reparse_args(char **args, int num_of_args);
void						add_redirection(t_redirections **redirections,
								t_redirections *new_redirection);
t_redirections				*create_redirection(char *type, char *destination);
t_redirections				*find_redirections(char **args);
void						free_redirections(t_redirections *redirections);

int							apply_redirections(t_redirections *redirections,
								char **env);
int							output_redirection(char *destination);
int							input_redirection(char *destination);
int							append_redirection(char *destination);
int							heredoc_redirection(char *delimiter, char **env);

// input

char						*display_prompt(void);
int							is_valid_input(t_token *tokens);

// env

char						**store_environment(char **env);
int							ft_setenv(char *name, char *value, char **env);
char						*ft_getenv(const char *name, char **env);

// execution_protocol

int							execution_protocol(t_command *commands, char **env);
int							current_command(t_command *command, char **env);
int							execute_command(char **args, char **env, t_descriptor *descriptor, t_command *commands);


t_descriptor				*get_descriptors(void);
void						free_descriptor(t_descriptor *descriptor);


// bin

int							execute_bin_command(char **args, char **env, t_descriptor *descriptor, t_command *commands);

// pipes

int							pipe_commands(t_command *commands, char **env);

// commands

int							ft_cd(char **args, char **env);
int							ft_echo(char **args);
int							ft_pwd(char **args);
int							ft_export(char **args, char **env);
int							ft_unset(char **args, char **env);
int							ft_env(char **args, char **env);
int							ft_exit(char **args, char **env, t_descriptor *descriptor, t_command *commands);

// tokenization

t_token						*ft_tokenize(char *input, char **env);
void						free_tokens(t_token *tokens);
t_token						*create_token(t_token_var type, char *value);
void						add_token(t_token **tokens, t_token *new_token);
t_token						*create_token(t_token_var type, char *value);
int							count_tokens(t_token *tokens);

char						*gather_word(char **input, char **env);

char						*handle_wildcard_expansion(char *input);

// bools

bool						is_special_token(int token);
bool						is_redirection_token(int token);
bool						is_bin_command(char *command);
bool						is_output_redirection(t_redirections *redirections);
bool						is_input_redirection(t_redirections *redirections);
bool						is_first_and_last_char(const char *str, char ch);

// debug

void						print_args(char **args);
void						print_tokens(t_token *tokens);
void						print_commands(t_command *commands);

// signals

void						handle_signals(void);
void						handle_sigquit(int sig);
void						handle_sigint(int sig);
void						handle_sigint_child(int sig);

// quotes

char						*handle_single_quotes(char **input);
char						*handle_unmatched_single_quotes(char *start);
char						*handle_double_quotes(char **input, char **env);
char						*handle_double_quotes_var(char **input, char **env,
								char *res);
char						*handle_unmatched_double_quotes(char *start,
								char **env);

// var_utils

char						*handle_var(char **input, char **env);
char						*handle_var_heredoc(char **buffer, char **env);

#endif
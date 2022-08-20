/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:05:10 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/09 12:55:06 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../Librarys/libft/libft.h"

int	g_exit_status;

typedef enum bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum token
{
	UNKNOWN,
	COMMAND,
	ARGUMENT,
	PIPE,
	GREATER,
	LESSER,
	DGREATER,
	DLESSER,
	FILENAME
}	t_token;

typedef struct descriptor
{
	int		in;
	int		out;
	int		err;
}			t_desc;

typedef struct command
{
	char	*cmd;
	char	**args;
	t_desc	descriptor;
}			t_command;

typedef struct gen
{
	int			token_count;
	int			cmd_count;
	int			*arg_counts;
	t_token		*tokens;
	t_command	*command;
	char		**envp;
	void		(*sigint_handler)(int);
	void		(*sigquit_handler)(int);
	t_bool		*redir_mark;
	int			redir_len;
	int			pipe_holder;
	char		*home_path;
	char		**cmd_line;
}				t_gen;

int		print_error(char *str, t_gen *gen, int exit_status, int free_level);
int		free_on_error(t_gen *gen, int level);
int		get_string_arr_len(char **arr);
int		lexer(t_gen *gen, char *line);
int		parser(t_gen *gen);
int		executor(t_gen *gen);
int		ft_strcont(char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		get_key_index(char *env, t_gen *gen);
int		free_and_ret(char *str);
int		ft_strncmpf(const char *s1, const char *s2, size_t n);
int		greater(t_gen *gen, int *i, int *cmd_i);
int		dgreater(t_gen *gen, int *i, int *cmd_i);
int		lesser(t_gen *gen, int *i, int *cmd_i);
int		dlesser(t_gen *gen, int	*i, int *cmd_i);

char	**copy_str_array(char **arr);
char	*ft_strjoinf(char *s1, char *s2);
char	*get_env(char *env, t_gen *gen);
char	**split_line(char *str, t_gen *gen);
char	*set_env_var_digit(char *str, int *ind);
char	*set_env_var(char *str, int *ind, t_gen *gen);
char	*set_exit_status(char *str, int *ind);
char	**add_to_array(char **arr, const char *str, int st, int fn);
char	*fill_path(char *path_line, int rot);

void	set_signals(t_gen *gen);
void	clear(int fdout);
void	free_on_exit(t_gen *gen);
void	init_int_array(int *arr, int len, int val);
void	sigint_dlesser(int signal);
void	free_all_exit(t_gen *gen);
void	sigint(int signal);
void	pwd(int fdout);
void	cd(char **args, t_gen *gen, int fdout);
void	echo(char **args, int fdout);
void	env(char **args, char **envp, int fdout);
void	exitbin(char **args, int fdout, t_gen *gen);
void	unset(char **args, t_gen *gen);
void	export(char **args, char **envp, int fdout, t_gen *gen);
void	restore_sigint(t_gen *gen);
void	sigint2(int signal);
void	sort_2d_str_array(char **arr);
void	add_to_env(char *line, t_gen *gen);
void	free_str_array(char **arr);
void	free_after_cmd(t_gen *gen);
void	dlesser_child(t_gen *gen, int i, int fd[2]);
void	executor_helper2(void);
void	executor_helper(t_gen *gen, int i);
void	create_the_array(char *str, t_bool quote[2], char ***array);

#endif
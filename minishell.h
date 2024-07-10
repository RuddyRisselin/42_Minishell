/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:47 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 15:04:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft/libft.h"
# include "pipe/pipex.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>

# define YES	1
# define NO		0
# define SPACES	" \t\n"
# define CHEVRON	"><"
# define PIPE	"|"
# define SPECIAL	"><|"
# define DQUOTE	'\"'
# define SQUOTE	'\''
# define QUOTES	"\'\""
# define BUFFER_SIZE 1024

extern int	g_return_value;

typedef struct s_expend
{
	int		index;
	int		jindex;
}	t_expend;

typedef struct s_pipex
{
	char	**cmd;
	char	*out;
	int		cmd_count;
	int		pipe_count;
}	t_pipex;

typedef struct t_token
{
	char			*word;
	int				type;
	struct t_token	*prev;
	struct t_token	*next;
}	t_token;

typedef struct s_data
{
	char	**env_maj;
	char	**params_cmd;
	char	*dest;
	char	*path_part;
	int		continue_while;
	pid_t	pid;
	int		fd_out;
	int		fd_in;
	int		saved_stdin;
	int		saved_stdout;
	int		is_heredoc;
	int		redirin;
	int		redirout;
	t_token	*token;
}	t_data;

void	ft_print_tab(char **tab);

int		exec_cmd(t_data *data, char **env);
void	check_to_send(t_data *data, char **env);
int		check_cmd_path(char *cmd);
char	*get_path(char *cmd, char **env, t_data *data);
void	free_if_no_tmp(t_data *data, int i);
void	free_if_no_dup(t_data *data, int i);
int		if_pipex(t_data *data, t_token *token, t_pipex *pipex);
int		join_pipex_token(t_pipex *pipex, t_token *token);
void	ft_free_pipe(t_pipex *pipex);
int		if_argcmd(t_token *token);

void	print_welcome(void);
int		ft_tablen(char **tab);
int		token_size(t_token *lst);
void	ft_free_tab(char **tab);

int		check_builtins(t_data *data);
void	print_export(t_data *data);
void	builtins_env(t_data *data);
void	builtins_pwd(t_data *data);
void	builtins_cd(int ac, t_data *data);
int		builtins_echo(t_token *token, t_data *data);
void	builtins_exit(t_data *data);

void	check_redirection_in(t_data *data);
void	check_redirection_out(t_data *data);
int		check_if_in5(t_data *data);
void	reset_redir(t_data *data);
int		change_out(t_data *data, t_token *token);

void	variables_env(t_data *data);
void	ft_free_env(t_data *data);
char	**if_var_exist(char **env, char *word, int *x);
void	unset_variables(t_data *data);
void	env_maj_pwd(t_data *data);
void	env_cpy(t_data *data, char **env);
int		search_pwd(t_data *data, int n);
char	*ft_strcpy_oldpwd(char *src);
char	*ft_strcpy_pwd(char *src, char *dest);

int		syntax(char *line);
int		parsing(char *line, char **env, t_data *data);
int		ft_count_word(char *line);
int		type_define(char *s);
char	*check_dollar(char *str, const char **env);
char	**ft_separator(char *s);
void	positif_string(char *line);
void	negatif_string(char *line);
void	find_command(char *line, t_data *data);
void	free_token_list(t_token *head);
void	free_tab(char **tab);
t_token	*create_token_list(char **words);
char	*expend(char *str, char **env, t_data *data);
int		in_single_quote2(char *str, t_expend *exp);
void	expend_return_value(t_data *data, char *dest, t_expend *exp);
int		positv_str(char c);
void	print_msg_error_syntax(int i);

int		in_single_quote(char *str, int j);
int		ft_strlen1(const char *str);
int		ft_strncmp1(const char *s1, const char *s2, int n);
int		ft_isalnum1(int c);
char	*ft_strncpy1(char *dest, const char *src, int n);
char	*ft_strcat1(char *dest, char *src);
char	*ft_strncat1(char *dest, const char *src, unsigned int nb);
void	*ft_memset1(void *p, int v, int c);

void	sig_management(int signo);
void	handler_int_try(int sign);
void	handler_quit(int sign);

#endif
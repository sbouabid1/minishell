/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:46:56 by touahman          #+#    #+#             */
/*   Updated: 2024/03/09 15:07:52 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	COMMAND,
	ARG,
	STRING,
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HERDOC,
	DELIMITER,
	INFILE,
	OUTFILE,
}	t_token_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct indexes
{
	int		i;
	int		j;
	int		len;
	int		end;
	int		fd_w;
	int		fd_r;
	int		size;
	int		inquotes;
	int		inside_d_quotes;
	int		inside_s_quotes;
	char	*result;
	char	*expand;
	char	*temp;
	char	*temp2;
	char	*l_temp;
	char	*delimiter;
	char	*temp_file;
	char	*buffer;
	char	**env;
	t_env	**env_head;
}	t_index;

typedef struct state
{
	int	inside_d_quotes;
	int	inside_s_quotes;
	int	i;
	int	j;
}	t_state;

typedef struct lex
{
	char	*fixed_line;
	char	*p_line;
	char	*e_line;
	char	**str;
}	t_lexer;

typedef struct s_node
{
	t_token_type	type;
	char			*str;
	int				fd_in;
	int				fd_out;
	struct s_node	*prev;
	struct s_node	*next;
}	t_pnode;

typedef struct q_node
{
	t_pnode	*head;
	t_pnode	*tail;
}	t_plist;

typedef struct node
{
	char		*command;
	char		*path;
	char		**arg;
	int			fd_in;
	int			fd_out;
	struct node	*prev;
	struct node	*next;
}				t_node;

typedef struct d_node
{
	t_node	*head;
	t_node	*tail;
}	t_dblst;

void	ft_free(char **lst);
void	add_list(char **str, t_dblst *list, char **env);
void	free_list(t_dblst *list);
t_pnode	*create_snode(char *data);
void	add_to_slist(t_plist *list, char *data);
void	add_slist(char *str, t_plist *list);
char	**token_split(char const *s, char c);
void	free_slist(t_plist *list);
void	remove_quotes(t_plist *p_list);
void	redirections(t_plist *list, t_env **env_head);
void	expand_redir(char **str, t_env **env_head);
int		fix_input(char *line);
int		check_quotes(char *input);
int		check_syntax(t_plist *list);
void	quotes(t_pnode *p_list, char *env, t_env **env_head);
void	handle_signals(void);

void	add_spaces_back(t_dblst *list);
void	remove_spaces(char *str);

int		heredoc(t_pnode *list, t_env **env_head);
void	expand(t_plist *p_list, t_env **env_head, int *status);
char	*find_env(t_env **env, char *arg);
int		lexer(char *line, t_dblst *list, t_index *index, int *status);
void	epur_str(char *str);
int		str_len(char *str);
int		get_len(char *str);
int		count_len(char *input);
void	fix_it_again(char *str);
char	*fix_quotes(char *input);
t_plist	tokenize_list(char *str);

char	*exec_line(t_plist *list);
void	fix_e_line(char *f_line, char *e_line);
void	remove_line_quotes(char *str);
// TOKENIZER
void	mark_arguments(t_pnode *head);
void	mark_heredoc(t_pnode *head);
void	mark_redirection_output(t_pnode *head);
void	mark_redirection_input(t_pnode *head);
void	mark_pipes(t_pnode *head);
// EXECUTION

typedef struct s_var
{
	int		i;
	int		j;
	int		result;
	int		temp;
	int		fd[2];
	int		pid;
	int		waitstatus;
	t_env	**env_head;
	char	**envs;
	char	**paths;
	char	*env;
	char	*join1;
	char	*join2;
}	t_var;

t_env	*new_env(char	*arg);
void	add_env(t_env **env_head, t_env *new);
void	makestatus(int waitstatus, int *status);
char	*get_command_path(char *command, char **env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ex_count_len(char	*str);
void	free_arr(char **arr);
void	first_condition(t_node *curr, t_var *var);
void	second_condition(t_node *curr, t_var *var);
void	last_condition(t_node *curr, t_var *var);
void	free_curr(t_env *curr);
/*builtins*/
int		echo(t_node *node);
int		cd(t_node *node);
int		pwd(t_node *node);
int		ft_env(t_env **envs, t_node *node);
int		export(t_node *node, t_env **env, char **envs);
int		ft_unset(t_env **head, t_node *curr, char **env);
void	ft_exit(t_node *curr, t_env **env_head);
void	ft_run(t_node *curr, char **env);
/*pipes*/
int		builtins(int index, t_node *curr, t_env **env_head, char **env);
int		check_if_builtins(t_node *curr);
void	put_error(char *mesg, char *command);
void	execute_cmds(t_node **node, char **env, t_env **env_head, int *status);

/*export*/
void	swap(t_env *a, t_env *b);
void	sort_list(t_env *head);
void	copy_list(t_env *source, t_env **destination);
void	exfree_list(t_env **head);
void	print_sorted_env(t_env **env, t_node *node);

#endif

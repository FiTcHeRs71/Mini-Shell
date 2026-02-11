/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgranger <lgranger@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2010/02/20 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/11 14:45:51 by lgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef enum e_error
{
	MALLOC,
	CD,
	CD_ENTRY,
}						t_error;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
}						t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}						t_quote_type;

typedef enum e_pattern_type
{
	EVERYTHING,
	START_WITH,
	END_WITH,
	ANYTHING_CONTAINING,
	ANYTHING_IN_BETWEEN,
	WRONG_PATTERN,
}						t_pattern_type;

typedef struct s_wildcards
{
	t_pattern_type		pattern;
	char				*start;
	char				*end;
}						t_wildcards;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*prev;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	t_token_type		type;
	t_quote_type		quote;
	t_wildcards			wildcards;
	char				*value;
	bool				wc;
	struct s_token		*next;
}						t_token;

typedef struct s_heredoc_data
{
	int					interrupted;
	char				*limiter;
	struct sigaction	old_int;
	struct sigaction	old_quit;
}						t_heredoc_data;

typedef struct s_segments
{
	bool				expand;
	bool				exist;
	bool				is_word;
	bool				spec_char;
	char				*buffer;
	struct s_segments	*next;
}						t_segments;

typedef struct s_state_data
{
	t_quote_type		state;
	t_segments			*phrase;
	t_segments			*word;
	int					word_i;
	int					quote;
	bool				done;
}						t_state_data;

typedef struct s_pipe
{
	int					pipefd[2];
	int					pid_l;
	int					pid_r;
	int					status_l;
	int					status_r;
	int					code;
}						t_pipe;

typedef struct s_expansion
{
	char	*new_value;
	char	*joined;
	char	*result;
	char	*varname;
	bool	last_status;
	bool	spec_char;
	int		index;
}			t_expansion;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_CMD,
	NODE_REDIR,
	NODE_OR,
	NODE_AND,
	NODE_SUBSHELL,
}						t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	t_token_type		redir_type;
	char				**args;
	char				*cmd_path;
	char				*file;
	int					heredoc_fd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_shell
{
	t_env				*env;
	t_token				*token_list;
	t_ast_node			*tree_ast;
	bool				syntax_flag;
	bool				heredoc;
	bool				hd_expansion;
	int					is_child;
	int					is_subshell;
	int					fd_in;
	int					fd_out;
	int					stdin_back_up;
	int					stdout_back_up;
	int					last_exit_status;
	int					pipe_depth;
	char				*syntax;
}						t_shell;

#endif
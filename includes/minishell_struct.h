#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef enum e_error
{
	MALLOC,
	CD,
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
	char				*value;
	bool				expand;
	struct s_token		*next;
}						t_token;

typedef struct s_pipe
{
	int					pipefd[2];
	int					pid_l;
	int					pid_r;
	int					status_l;
	int					status_r;
	int					code;
}						t_pipe;

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
	char				**args;
	char				*cmd_path;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				*file;
	t_token_type		redir_type;
}						t_ast_node;

typedef struct s_shell
{
	t_env				*env;
	t_token				*token_list;
	t_ast_node			*tree_ast;
	bool				syntax_flag;
	bool				is_child;
	bool				heredoc;
	int					pipehd[2];
	int					pipefd[2];
	int					fd_in;
	int					fd_out;
	int					stdin_back_up;
	int					stdout_back_up;
	int					last_exit_status;
}						t_shell;

#endif
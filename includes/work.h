
#include"minishell.h"

typedef enum e_token_type {
    TOKEN_WORD,      // Commande ou argument
    TOKEN_PIPE,      // |
    TOKEN_REDIR_IN,  // 
    TOKEN_REDIR_OUT, // >
    TOKEN_APPEND,    // >>
    TOKEN_HEREDOC,   // 
} t_token_type;

typedef struct s_token {
    t_token_type     type;
    char             *value;
    struct s_token   *next;
} t_token;

typedef enum	e_node_type
{
	NODE_PIPE,
	NODE_CMD,
	NODE_REDIR,
	NODE_OR,
	NODE_AND,
}				t_node_type;

typedef struct	s_ast_node
{
	t_node_type	type;
	//CMD
	char				**args;
	//PIPE | REDIR
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	//REDIR
	char				*file;
	t_token_type		*types;
}				t_ast_node;

t_ast_node	*create_node(t_node_type type);
t_ast_node	*parse_command(t_token **current);
t_ast_node	*parser_token(t_token *token);
t_ast_node	*parser_pipe(t_token **current);
t_ast_node	*parser_redir(t_token **current);
void	advance_token(t_token **current);

#include"minishell.h"

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
	
}				t_ast_node;
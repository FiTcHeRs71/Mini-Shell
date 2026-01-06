
#include "../../includes/minishell.h"

// Helper pour obtenir le symbole de redirection
static const char	*get_redir_symbol(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("?");
}

// Helper pour obtenir le nom du type de nœud
/*static const char *get_node_type_name(t_node_type type)
{
	int	i;

	if (type == NODE_CMD)
		return ("COMMAND");
	if (type == NODE_PIPE)
		return ("PIPE");
	if (type == NODE_REDIR)
		return ("REDIR");
	if (type == NODE_AND)
		return ("AND");
	if (type == NODE_OR)
		return ("OR");
	if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}*/
// Afficher l'indentation
static void	print_indent(int depth)
{
	int	i;
	
	i = 0;
	while (i < depth)
	{
		ft_printf("│   "); // Ligne verticale + espaces
		i++;
	}
}

// Fonction principale d'affichage
void	print_ast(t_ast_node *node, int depth)
{
	int i;

	if (!node)
	{
		print_indent(depth);
		ft_printf("(null)\n");
		return ;
	}

	// Indentation
	print_indent(depth);

	// Afficher selon le type
	if (node->type == NODE_CMD)
	{
		ft_printf("├─ COMMAND: ");
		if (node->args && node->args[0])
		{
			i = 0;
			while (node->args[i])
			{
				ft_printf("%s", node->args[i]);
				if (node->args[i + 1])
					ft_printf(" ");
				i++;
			}
		}
		else
		{
			ft_printf("(empty)");
		}
		ft_printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		ft_printf("├─ PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == NODE_REDIR)
	{
		ft_printf("├─ REDIR %s → %s\n", get_redir_symbol(node->redir_type),
			node->file ? node->file : "(null)");
		print_ast(node->left, depth + 1);
	}
	else if (node->type == NODE_AND)
	{
		ft_printf("├─ AND (&&)\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == NODE_OR)
	{
		ft_printf("├─ OR (||)\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == NODE_SUBSHELL)
	{
		ft_printf("├─ SUBSHELL ( )\n");
		print_ast(node->left, depth + 1);
	}
	else
	{
		ft_printf("├─ UNKNOWN TYPE (%d)\n", node->type);
	}
}
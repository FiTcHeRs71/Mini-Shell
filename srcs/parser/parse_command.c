
#include "../../includes/minishell.h"

static int	count_arg(t_token *current)
{
	int	size;

	size = 0;
	while (current != NULL && current->type == TOKEN_WORD)
	{
		size++;
		advance_token(&current);
	}
	return (size);
}

t_ast_node	*parser_command(t_shell *shell, t_token **current)
{
	t_ast_node	*cmd;
	int			arg_count;
	int			i;

	if (!current || !(*current) || (*current)->type != TOKEN_WORD)
		return (NULL);
	i = 0;
	cmd = create_node(shell, NODE_CMD);
	arg_count = count_arg(*current);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
		ft_error(shell, MALLOC);
	while ((*current) != NULL && (*current)->type == TOKEN_WORD)
	{
		cmd->args[i] = ft_strdup((*current)->value);
		if (!cmd->args[i])
			ft_error(shell, MALLOC);
		advance_token(current);
		i++;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

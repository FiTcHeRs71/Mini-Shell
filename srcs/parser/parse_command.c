
#include "../../includes/minishell.h"

int	count_arg(t_token *current)
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

t_ast_node	*parser_command(t_token **current)
{
	t_ast_node	*cmd;
	t_token		**temp;
	int			arg_count;
	int			i;

	temp = current;
	if (!current || !(*current) || (*current)->type != TOKEN_WORD)
		return (NULL);
	i = 0;
	cmd = create_node(NODE_CMD);
	if (!cmd)
		exit(EXIT_FAILURE);// TODO : exit clean
	arg_count = count_arg(*temp);
	cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
		exit(EXIT_FAILURE);// TODO : exit clean
	while ((*temp) != NULL && (*temp)->type == TOKEN_WORD)
	{
		cmd->args[i] = ft_strdup((*temp)->value);
		if (!cmd->args[i])
			exit(EXIT_FAILURE);// TODO : exit clean
		advance_token(temp);
		i++;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

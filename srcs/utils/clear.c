
#include "../../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	if (!env)
	{
		return ;
	}
	while (env)
	{
		temp = env->next;
		if (env && env->key)
		{
			free(env->key);
		}
		if (env && env->value)
		{
			free(env->value);
		}
		if (env)
		{
			free(env);
		}
		env = temp;
	}
}

void	free_token(t_token *token)
{
	t_token	*temp;

	if (!token)
	{
		return ;
	}
	while (token)
	{
		temp = token->next;
		if (token && token->value)
		{
			free(token->value);
		}
		if (token)
		{
			free(token);
		}
		token = temp;
	}
}

void	free_ast(t_ast_node *tree)
{
	int	i;

	i = 0;
	if (!tree)
	{
		return ;
	}
	if (tree && tree->args)
	{
		while (tree->args[i])
		{
			free(tree->args[i]);
			i++;
		}
		free(tree->args);
	}
	if (tree && tree->file)
	{
		free(tree->file);
	}
	free_ast(tree->right);
	free_ast(tree->left);
	free(tree);
}

void	clean_up_fds(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	if (shell->stdin_back_up > 0)
	{
		close(shell->stdin_back_up);
	}
	if (shell->stdout_back_up > 0)
	{
		close(shell->stdout_back_up);
	}
}

void	clean_up_loop(t_shell *shell)
{
	free_ast(shell->tree_ast);
	free_token(shell->token_list);
	dup2(shell->stdout_back_up, STDOUT_FILENO);
	dup2(shell->stdin_back_up, STDIN_FILENO);
}

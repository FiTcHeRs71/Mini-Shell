
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
		temp = token;
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

	if (!tree)
	{
		return ;
	}
	if (tree && tree->args)
	{
		i = 0;
		while(tree->args[i])
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
		close (shell->stdin_back_up);
	}
	if (shell->stdout_back_up > 0)
	{
		close (shell->stdout_back_up);
	}
}

void	clean_before_exit(t_shell *shell)
{
	clean_up_fds(shell);
	free_env_list(*(shell->env));
	free(shell->env);
}
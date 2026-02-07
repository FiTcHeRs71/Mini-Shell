
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
			free(token->value);
		if (token && token->wildcards.start)
			free(token->wildcards.start);
		if (token && token->wildcards.end)
			free(token->wildcards.end);
		if (token)
			free(token);
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
	free_ast(tree->right);
	free_ast(tree->left);
	if (tree && tree->args)
	{
		while (tree->args[i])
		{
			free(tree->args[i]);
			i++;
		}
		free(tree->args);
	}
	if (tree && tree->cmd_path)
		free(tree->cmd_path);
	if (tree && tree->file)
		free(tree->file);
	free(tree);
}

void	clean_up_fds(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	if (shell->stdin_back_up > 2)
	{
		close(shell->stdin_back_up);
	}
	if (shell->stdout_back_up > 2)
	{
		close(shell->stdout_back_up);
	}
	if (shell->fd_in > 2)
	{
		close(shell->fd_in);
	}
	if (shell->fd_out > 2)
	{
		close(shell->fd_out);
	}
	shell->stdin_back_up = -1;
	shell->stdout_back_up = -1;
	shell->fd_in = -1;
	shell->fd_out = -1;
}

void	clean_up_loop(t_shell *shell)
{
	free_ast(shell->tree_ast);
	shell->tree_ast = NULL;
	free_token(shell->token_list);
	shell->token_list = NULL;
	dup2(shell->stdout_back_up, STDOUT_FILENO);
	dup2(shell->stdin_back_up, STDIN_FILENO);
}

void	clean_all(t_shell *shell)
{
	if (!shell)
	{
		return ;
	}
	free_ast(shell->tree_ast);
	shell->tree_ast = NULL;
	free_token(shell->token_list);
	shell->token_list = NULL;
	free_env_list(shell->env);
	shell->env = NULL;
	clean_up_fds(shell);
	//rl_clear_history();
}

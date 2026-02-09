#include "../includes/minishell.h"

char	**convert_env(t_shell *shell, t_env *env)
{
	char	**new_env;
	char	*tmp;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	new_env = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
	if (!new_env)
	{
		ft_error(shell, MALLOC);
	}
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			ft_error(shell, MALLOC);
		new_env[i] = ft_strjoin(tmp, env->value);
		if (!new_env[i])
			ft_error(shell, MALLOC);
		free(tmp);
		env = env->next;
		i++;
	}
	return (new_env);
}

static void	execute_ext_cmd(t_shell *shell, t_ast_node *node)
{
	char	**new_env;

	new_env = convert_env(shell, shell->env);
	if (execve(node->cmd_path, node->args, new_env) < 0)
	{
		ft_free_2d_array(new_env);
		clean_without_exit(shell);
		check_error(shell, node, node->args[0], errno);
		exit(1);
	}
}

static int	check_cmd(t_shell *shell, t_ast_node *node)
{
	if (access(node->args[0], X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->args[0]);
		if (!node->cmd_path)
			ft_error(shell, MALLOC);
		if (!node->cmd_path)
			return (1);
		return (0);
	}
	else
		return (update_cmd(shell, node, node->args[0]));
}

static int	execute_is_builtin(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = -1;
	if (!ft_strncmp(node->args[0], "echo", 5))
		signal = exec_echo(node->args, 1);
	else if(!ft_strncmp(node->args[0], "cd", 3))
		signal = exec_cd(shell, node->args);
	else if (!ft_strncmp(node->args[0], "env", 4))
		signal = exec_env(shell);
	else if (!ft_strncmp(node->args[0], "exit", 5))
		signal = exec_exit(shell, node->args);
	else if (!ft_strncmp(node->args[0], "export", 7))
		signal = exec_export(shell, &shell->env, node->args);
	else if (!ft_strncmp(node->args[0], "pwd", 4))
		signal = exec_pwd();
	else if (!ft_strncmp(node->args[0], "unset", 5))
		signal = exec_unset(shell, node->args[1]);
	return (signal);
}

int	exec_cmd(t_shell *shell, t_ast_node *node)
{
	int	check;
	int	exit_code;
	int	pid;
	
	exit_code = execute_is_builtin(shell, node);
	if (exit_code != -1)
	{
		if (shell->is_child)
		{
			clean_all(shell);
			exit(exit_code);
		}
		return(exit_code);
	}
	check = check_cmd(shell, node);
	if (check != 0)
		return (check);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		shell->is_child = true;
		execute_ext_cmd(shell, node);
	}
	return (wait_on_process(pid));
}

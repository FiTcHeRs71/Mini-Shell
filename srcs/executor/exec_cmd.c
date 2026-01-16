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
		new_env[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	return (new_env);
}

void	execute_ext_cmd(t_shell *shell, t_ast_node *node)
{
	char	**new_env;

	new_env = convert_env(shell, shell->env);
	execve(node->cmd_path, node->args, new_env);
	ft_free_2d_array(new_env);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		exit(126);
	exit(1);
}

int	check_cmd(t_shell *shell, t_ast_node *node)
{
	if (access(node->args[0], X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->args[0]);
		if (!node->cmd_path)
			return (1);
		return (0);
	}
	else
		return (update_cmd(shell, node, node->args[0]));
}

int	is_builtin(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = -1;
	if (!ft_strncmp(node->args[0], "echo", 5))
		signal = exec_echo(node->args);
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
	int	signal;
	int	pid;
	int	status;
	
	signal = is_builtin(shell, node);
	if (signal != -1)
	{
		if (shell->is_child)
			exit(signal);
		return(signal);
	}
	if (check_cmd(shell, node) != 0)
		return (127);
	if (shell->is_child)
		execute_ext_cmd(shell, node);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execute_ext_cmd(shell, node);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

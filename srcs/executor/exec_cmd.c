#include "../includes/minishell.h"

static char	**convert_env(t_env *env)
{
	char	**new_env;
	char	*tmp;
	int		i;

	i = 0;
	new_env = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
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

static void	execute_ext_cmd(t_shell *shell, t_ast_node *node)
{
	t_env	*tmp_env;
	char	**new_env;

	tmp_env = shell->env;
	new_env = convert_env(tmp_env);
	execve(node->cmd_path, node->args, new_env); // TODO : define error and return
	if (errno == ENOENT)
		_exit(127);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		_exit(126);
	exit(1);
}

static int	check_cmd(t_shell *shell, t_ast_node *node)
{
	if (access(node->args[0], X_OK) == 0)
		return (get_cmd(node, node->args[0]), 0);
	else
		return (update_cmd(shell, node, node->args[0]));
}

static int	is_builtin(t_shell *shell, t_ast_node *node)
{
	int	signal;

	signal = 0;
	//if(!ft_strncmp(node->file, "cd", 3))
		//signal = exec_cd();
	// else if (!ft_strncmp(node->file, "echo", 5)
	// 	signal = exec_echo(node->args);
	// else if (!ft_strncmp(node->file, "env", 4))
	// 	signal = exec_env(shell);
	// else if (!ft_strncmp(node->file, "exit", 5))
	// 	signal = exec_exit(shell, node->args);
	// else if (!ft_strncmp(node->file, "export", 7))
	// 	signal = exec_export();
	// else if (!ft_strncmp(node->file, "pwd", 4))
	// 	signal = exec_pwd(shell);
	if (!ft_strncmp(node->file, "unset", 5))
		signal = exec_unset(shell, node->args[0]);
	return (signal);
}

int	exec_cmd(t_shell *shell, t_ast_node *node)
{
	int	signal;
	int	pid;
	int	status;

	signal = check_cmd(shell, node);
	if (signal == 0)
	{
		signal = is_builtin(shell, node);
		if (signal == 0)
			return (0);
		if (signal > 0)
			return (signal);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			execute_ext_cmd(shell, node);
			exit(1);
		}
		if (waitpid(pid, &status, 0) < 0)
			return (1);
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	else
		return (signal);
}

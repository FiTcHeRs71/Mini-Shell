
#include "../../includes/minishell.h"

t_env	*get_env_node(t_shell *shell, char *key)
{
	t_env	*env;
	size_t	key_len;

	env = shell->env;
	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strlen(env->key) == key_len && ft_strncmp(env->key, key, key_len) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
static void	update_env(t_shell *shell, t_env *finder, char *new_value)
{
	if (finder->value)
	{
		free(finder->value);
	}
	finder->value = ft_strdup(new_value);
	if (!finder->value)
	{
		ft_error(shell, MALLOC);
	}
}

static void	helpers_update_env(t_shell *shell, char *old_pwd)
{
	char	*current_pwd;
	t_env	*finder;

	current_pwd = getcwd(NULL, 0);
	finder = get_env_node(shell, "PWD");
	if (finder)
	{
		update_env(shell, finder, current_pwd);
	}
	else
	{
		add_env_variable(shell, &shell->env, ft_strjoin("PWD=", current_pwd));
	}
	finder = get_env_node(shell, "OLDPWD");
	if (finder)
	{
		update_env(shell, finder, old_pwd);
	}
	else
	{
		add_env_variable(shell, &shell->env, ft_strjoin("OLDPWD=", old_pwd));
	}
	free(current_pwd);
}

static void	go_to_home(t_shell *shell, char *old_pwd)
{
	t_env	*finder;

	finder = get_env_node(shell, "HOME");
	if (!finder)
	{
		ft_putstr_fd("Home not set\n", 2);
	}
	else
	{
		if (chdir(finder->value) == 0)
		{
			helpers_update_env(shell, old_pwd);
		}
		else
			ft_putstr_fd("Unable to acces at the directory\n", 2);
	}
}

static void	go_back_directory(t_shell *shell, char *old_pwd)
{
	if (chdir(".."))
	{
		ft_putstr_fd("Unable to acces at the directory\n", 2);
	}
	else
	{
		helpers_update_env(shell, old_pwd);
	}
}
static void	go_to_directory(t_shell *shell, char *old_pwd, char *path)
{
	int	flag;

	flag = chdir(path);
	if (flag == 0)
	{
		helpers_update_env(shell, old_pwd);
	}
	else
		ft_putstr_fd("Unable to acces at the directory\n", 2);
}

int	exec_cd(t_shell *shell, char **args)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		ft_error(shell, MALLOC);
	if (!args[1] || ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
	{
		go_to_home(shell, old_pwd);
	}
	else if (ft_strncmp(args[1], ".", ft_strlen(args[1])) == 0)
	{
		free(old_pwd);
		return (0);
	}
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
	{
		go_back_directory(shell, old_pwd);
	}
	else
	{
		go_to_directory(shell, old_pwd, args[1]);
	}
	return (0);
}

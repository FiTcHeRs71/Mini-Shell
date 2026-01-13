
#include "../../includes/minishell.h"

static t_env	*get_env_node(t_shell *shell, char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
static void	update_env(t_shell *shell, t_env *finder, char *old_pwd, int flag)
{
	if (flag == 0)
	{
		if (finder->value)
			free(finder->value);
		finder->value = getcwd(NULL, 0);
		if (!finder->value)
		{
			ft_error(shell, MALLOC);
		}
	}
	else if (flag == 1)
	{
		if (finder->value)
			free(finder->value);
		finder->value = old_pwd;
	}
}

static void	helpers_update_env(t_shell *shell, t_env *finder, char *old_pwd)
{
	finder = get_env_node(shell, "PWD");
	if (finder)
	{
		update_env(shell, finder, old_pwd, 0);
	}
	else if (!finder)
	{
		add_env_variable(shell, &shell->env, ft_strjoin("PWD=",getcwd(NULL, 0))); // a check
	}
	finder = get_env_node(shell, "OLDPWD");
	if (finder)
	{
		update_env(shell, finder, old_pwd, 1);
	}
	else if (!finder)
	{
		add_env_variable(shell, &shell->env, ft_strjoin("OLDPWD=",old_pwd)); // a check
	}
}


static void	go_to_home(t_shell *shell, t_env *finder, char *old_pwd)
{
	int		flag;

	flag = 0;
	finder = get_env_node(shell, "HOME");
	if (!finder)
	{
		ft_putstr_fd("Home not set\n", 2);
	}
	else
	{
		flag = chdir(finder->value);
		if (flag == 0)
		{
			helpers_update_env(shell, finder, old_pwd);
		}
		else
			ft_putstr_fd("Unable to acces at the directory\n", 2);
	}
}

static void	go_back_directory(t_shell *shell, t_env *finder, char *old_pwd)
{
	char	*way;

	way = ft_substr(old_pwd, 0, ft_strrchr(old_pwd, '/') - old_pwd);
	if (!way)
		ft_error(shell, MALLOC);
	if (!chdir(way))
	{
		ft_putstr_fd("Unable to acces at the directory\n", 2);
		return;
	}
	helpers_update_env(shell, finder, old_pwd);
	if (way)
		free(way);
}
static void	go_to_directory(t_shell *shell, t_env *finder, char *old_pwd, char *path)
{
	int	flag;

	flag = chdir(path);
	if (flag == 0)
	{
		helpers_update_env(shell, finder, old_pwd);
	}
	else
		ft_putstr_fd("Unable to acces at the directory\n", 2);
}


int	exec_cd(t_shell *shell, char **args) //TODO :compter le nb dargs pour valide chemin ?  tester chdir(..)
{
	t_env	*finder;
	char	*old_pwd;

	finder = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		ft_error(shell, MALLOC);
	if (!args[1] || ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
	{
		go_to_home(shell, finder, old_pwd);
	}
	else if (ft_strncmp(args[1], ".", ft_strlen(args[1])) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(args[1], "..", ft_strlen(args[1])) == 0)
	{
		go_back_directory(shell, finder, old_pwd);
	}
	else
	{
		go_to_directory(shell, finder, old_pwd, args[1]);
	}
	return (0);
}

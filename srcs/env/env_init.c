
#include "../../includes/minishell.h"

static t_env	*env_last(t_env *env)
{
	if (!env)
	{
		return (NULL);
	}
	while (env->next != NULL)
	{
		env = env->next;
	}
	return (env);
}

static void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new)
	{
		return ;
	}
	if (!*env)
	{
		*env = new;
		return ;
	}
	last = env_last(*env);
	last->next = new;
}

static void	add_env_variable(t_env **env, char *envp)
{
	char	*finder;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		exit(EXIT_FAILURE); // TODO :  error manage + free
	}
	finder = ft_strchr(envp, '=');
	if (!finder)
	{
		free(new);
		return ;
	}
	new->key = ft_substr(envp, 0, finder - envp);
	new->value = ft_strdup(finder + 1);
	env_add_back(env, new);
}

void	init_shell(t_shell *shell, char **envp)
{
	size_t	i;
	t_env	*envp_list;

	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		add_env_variable(&envp_list, envp[i]);
		i++;
	}
	shell->env = ft_calloc(1, sizeof(t_env *));
	*(shell->env) = envp_list;
}

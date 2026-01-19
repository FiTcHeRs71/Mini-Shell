#include "../includes/minishell.h"

static char	*get_env_varname(t_shell *shell, char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);	
}

static char	*expanded_value(t_shell *shell, t_token *token, char *varname)
{
	char	*var_value;
	char	*buffer;
	char	*value;
	char	*res;

	value = token->value;
	buffer = ft_calloc(increment_len(token->value, '$', 0) + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (*value != '$' && *value)
		*buffer++ = *value++;
	*buffer = '\0';
	var_value = get_env_varname(shell, varname);
	if (!var_value)
		var_value = "";
	res = ft_strjoin(buffer, var_value);
	free(buffer);
	return (res);
}
static void expand_last_status(t_shell *shell, t_token *token)
{
	free(token->value);
	token->value = ft_itoa(shell->last_exit_status);
}

static void	process_expansion(t_shell *shell, t_token *token, char *value)
{
	char	*varname;
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '$' && value[i])
		i++;
	if (value[i] == '$' && value[i + 1] == '?')
	{
		expand_last_status(shell, token);
		return ;
	}
	varname = ft_calloc(increment_len(value, ' ', i), sizeof(char));
	if (!varname)
		ft_error(shell, MALLOC);
	find_varname(varname, value, i, j);
	new_value = expanded_value(shell, token, varname);
	free(varname);
	if (!new_value)
		ft_error(shell, MALLOC);
	free(token->value);
	token->value = new_value;
}

void	expansion(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->expand == true)
		{
			if (ft_strchr(tmp->value, '$') && ft_strncmp(tmp->value, "$", 2))
				process_expansion(shell, tmp, tmp->value);
		}
		tmp = tmp->next;
	}
}

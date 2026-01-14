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
		free(token->value);
		token->value = ft_itoa(shell->last_exit_status);
		return ;
	}
	varname = ft_calloc(increment_len(value, ' ', i), sizeof(char));
	if (!varname)
		return ;
	while (value[i])
	{
		if (value[i] == '$')
			i++;
		if (!value[i])
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
	new_value = expanded_value(shell, token, varname);
	free(varname);
	if (!new_value)
		return ;
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

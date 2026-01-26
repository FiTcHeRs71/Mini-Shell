#include "../includes/minishell.h"

char	*get_env_varname(t_shell *shell, char *key)
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
	int		i;

	var_value = get_env_varname(shell, varname);
	if (!var_value)
		var_value = "";
	i = ft_strlen(var_value) + increment_len(token->value, ' ', 0);
	buffer = ft_calloc(i + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	value = token->value;
	i = 0;
	while (*value)
	{
		if (*value == '$' && *var_value)
		{
			while (*var_value != '$' && *var_value)
			{
				buffer[i++] = *var_value++;
			}
			value += ft_strlen(varname) + 1;
		}
		buffer[i++] = *value++;
	}
	buffer[i] = '\0';
	return (buffer);
}

static void expand_last_status(t_shell *shell, t_token *token, char *value)
{
	char	*expand;
	char	*res;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(value) + shell->last_exit_status;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		ft_error(shell, MALLOC);
	while (*value != '$' && *value)
		res[i++] = *value++;
	expand = ft_itoa(shell->last_exit_status);
	while (expand[j])
		res[i++] = expand[j++];
	value += 2;
	while (*value)
		res[i++] = *value++;
	free(token->value);
	token->value = ft_strdup(res);
	free(expand);
	free(res);
}

static void	process_expansion(t_shell *shell, t_token *token, char *value)
{
	char	*varname;
	char	*new_value;
	int		i;

	i = 0;
	while (value[i] != '$' && value[i])
	{
		i++;
	}
	if (value[i] == '$' && value[i + 1] == '?')
	{
		expand_last_status(shell, token, token->value);
		return (process_expansion(shell, token, token->value));
	}
	else if (value[i] == '$')
	{
		varname = find_varname(shell, value, i + 1);
		if (!varname)
			return ;
		new_value = expanded_value(shell, token, varname);
		free(varname);
		if (!new_value)
			ft_error(shell, MALLOC);
		free(token->value);
		token->value = new_value;
		return (process_expansion(shell, token, token->value));
	}
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


/*
char *buffer;

while (value[i])
{
	buffer = ft_calloc(increment_len(token->value, '$', i), sizeof(char));
	while()
	if (value[i] == '$' && value[i + 1] == '?')
	{
		expand_last_status(shell, token, token->value);
		return (process_expansion(shell, token, token->value));
	}
}
*/

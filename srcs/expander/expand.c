#include "../includes/minishell.h"

static char	*expand_last_status(t_shell *shell, char *value)
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
	free(expand);
	return (res);
}

static char	*fill_buffer(char *buffer, char *value, char *var_value, char *varname)
{
	bool	filled;
	int		i;

	i = 0;
	filled = false;
	while (*value)
	{
		if (*value == '$' && !*var_value && filled == false)
			value += ft_strlen(varname) + 1;
		else if (*value == '$' && *var_value)
		{
			while (*var_value != '$' && *var_value)
				buffer[i++] = *var_value++;
			value += ft_strlen(varname) + 1;
			filled = true;
		}
		else
			buffer[i++] = *value++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*expanded_value(t_shell *shell, char *value, char *varname)
{
	char	*var_value;
	char	*buffer;
	int		i;

	var_value = get_env_varname(shell, varname);
	if (!var_value)
	{
		buffer = ft_substr(value, 0, increment_len(value, '$', 0));
		return (buffer);
	}
	i = ft_strlen(var_value) + increment_len(value, ' ', 0);
	buffer = ft_calloc(i + 1, sizeof(char));
	if (!buffer)
		ft_error(shell, MALLOC);
	return (fill_buffer(buffer, value, var_value, varname));
}

char	*find_varname(t_shell *shell, char *value, int i)
{
	char	*varname;
	int		j;

	j = 0;
	varname = ft_calloc(increment_len(value, '$', i) + 1, sizeof(char));
	if (!varname)
		ft_error(shell, MALLOC);
	while (value[i])
	{
		if (!value[i] || value[i] == '$' || value[i] == ' ' || value[i] == '-' || value[i] == '\'')
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
	return (varname);
}

char	*process_expansion(t_shell *shell, char *value)
{
	char	*new_value;
	int		i;

	i = 0;
	while (value[i] != '$' && value[i])
		i++;
	if (value[i] == '$' && value[i + 1] == '?')
	{
		new_value = expand_last_status(shell, value);
		free(value);
		value = new_value;
		return (process_expansion(shell, value));
	}
	else if (value[i] == '$' && value[i + 1])
	{
		value = common_expansion(shell, value, i);
		return (process_expansion(shell, value));
	}
	return (value);
}

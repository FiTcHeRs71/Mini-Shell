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

// static char	*fill_buffer(char *buffer, char *value, char *var_value, char *varname)
// {
// 	bool	filled;
// 	int		i;

// 	i = 0;
// 	filled = false;
// 	while (*value)
// 	{
// 		if (*value == '$' && !*var_value && filled == false)
// 			value += ft_strlen(varname) + 1;
// 		else if (*value == '$' && *var_value)
// 		{
// 			while (*var_value != '$' && *var_value)
// 				buffer[i++] = *var_value++;
// 			value += ft_strlen(varname) + 1;
// 			filled = true;
// 		}
// 		else
// 			buffer[i++] = *value++;
// 	}
// 	buffer[i] = '\0';
// 	return (buffer);
// }

char	*expanded_value(t_shell *shell, char *value, char *varname, int index)
{
	char	*var_value;
	char	*buffer;

	var_value = get_env_varname(shell, varname);
	if (!var_value)
	{
		if (ft_isalnum(value[1]))
			buffer = ft_strdup("");
		else
			buffer = ft_substr(value, index, increment_len(value, '$', index));
		return (buffer);
	}
	buffer = ft_strdup(var_value);
	if (!buffer)
		ft_error(shell, MALLOC);
	return (buffer);
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
		if (!value[i] || value[i] == '$' || value[i] == ' ' || value[i] == '-' || value[i] == '\'' || value[i] == '"')
			break ;
		varname[j++] = value[i++];
	}
	varname[j] = '\0';
	return (varname);
}

char	*process_expansion(t_shell *shell, char *value)
{
	char	*new_value;
	char	*joined;
	char	*res;
	int		i;
	
	i = 0;
	res = ft_strdup("");
	while (value[i])
	{
		while (value[i] != '$' && value[i])
			i++;
		if (!value[i])
			break ;
		if (value[i] == '$' && value[i + 1] == '?')
		{
			new_value = expand_last_status(shell, value);
			joined = ft_strjoin(res, new_value);
			free(res);
			free(new_value);
			res = joined;
			i += 2;
		}
		else if (value[i] == '$' && value[i + 1])
		{
			new_value = common_expansion(shell, value, i);
			joined = ft_strjoin(res, new_value);
			free(res);
			free(new_value);
			res = joined;
			i += increment_len(value, '$', i + 1) + 1;
		}
		else
		{
			free(res);
			res = ft_strdup(value);
			free(value);
			return (res);
		}
	}
	free(value);
	return (res);
}

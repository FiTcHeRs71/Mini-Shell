#include "../includes/minishell.h"

static char	*expanded_value(t_token *token, char *varname)
{
	char	*var_value;
	char	*buffer;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = token->value;
	if (value[i] == '$')
		buffer = NULL;
	else
		buffer = ft_calloc(increment_len(token->value, '$', 0), sizeof(char));
	while (value[i] != '$')
	{
		buffer[j++] = value[i];
		i++;
	}
	var_value = getenv(varname);
	return (ft_strjoin(buffer, var_value));
}

static void	redirect_expansion(t_shell *shell, t_token *token, char *varname)
{
	if (!ft_strncmp(varname, "$?", 3))
		token->value = ft_itoa(shell->last_exit_status);
	else
		token->value = expanded_value(token, varname);
}

static void	process_expansion(t_shell *shell, t_token *token, char *value)
{
	char	*varname;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '$')
		i++;
	varname = ft_calloc(increment_len(value, ' ', i), sizeof(char));
	while (value[i])
	{
		if (value[i] == '$')
			i++;
		varname[j++] = value[i];
		i++;
	}
	redirect_expansion(shell, token, varname);
	free(varname);
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

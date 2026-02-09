#include "../includes/minishell.h"

static void	pattern_start_without_asterisk(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = find_asterisk(token->value, 0);
	token->wildcards.start = ft_substr(token->value, 0, i);
	if (!token->wildcards.start)
		ft_error(shell, MALLOC);
	if (token->value[i + 1])
	{
		j = find_asterisk(token->value, i + 1);
		token->wildcards.end = ft_substr(token->value, i + 1, j);
		token->wildcards.pattern = ANYTHING_IN_BETWEEN;
		if (token->value[j])
			token->wildcards.pattern = WRONG_PATTERN;
	}
	else
		token->wildcards.pattern = START_WITH;
}

static void	find_wildcard_pattern(t_shell *shell, t_token *token)
{
	int	i;

	i = 0;
	if (!ft_strncmp(token->value, "*", 2))
		token->wildcards.pattern = EVERYTHING;
	else if (token->value[0] != '*')
	{
		pattern_start_without_asterisk(shell, token);
	}
	else if (token->value[0] == '*')
	{
		i = find_asterisk(token->value, 1);
		token->wildcards.end = ft_substr(token->value, 1, i - 1);
		if (token->value[i] == '*')
			token->wildcards.pattern = ANYTHING_CONTAINING;
		else if (token->value[i])
			token->wildcards.pattern = WRONG_PATTERN;
		else
			token->wildcards.pattern = END_WITH;
	}
}

static t_token	*process_wildcards(t_shell *shell, t_token *token)
{
	DIR		*dir;
	t_token	*new_list;

	dir = opendir(".");
	if (!dir)
		ft_error(shell, MALLOC);
	if (token->wildcards.pattern == EVERYTHING)
		new_list = everything_pattern(shell, dir);
	else if (token->wildcards.pattern == START_WITH)
		new_list = start_with_pattern(shell, token, dir);
	else if (token->wildcards.pattern == END_WITH)
		new_list = end_with_pattern(shell, token, dir);
	else if (token->wildcards.pattern == ANYTHING_CONTAINING)
		new_list = anything_containing_pattern(shell, token, dir);
	else if (token->wildcards.pattern == ANYTHING_IN_BETWEEN)
		new_list = in_between_pattern(shell, token, dir);
	closedir(dir);
	return (new_list);
}

static void	sort_token(t_token **list)
{
	t_token	**head;
	int		len;

	head = list;
	while (*list && (*list)->next)
	{
		len = ft_strlen((*list)->value);
		if (strncmp_with_maj((*list)->value, (*list)->next->value, len) > 0)
		{
			swap_token(list);
			return (sort_token(head));
		}
		else
			list = &(*list)->next;
	}
}

void	wildcards(t_shell *shell)
{
	t_token	*last;
	t_token	*new_list;
	t_token	*tmp;

	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->wc == true && ft_strrchr(tmp->value, '*'))
		{
			find_wildcard_pattern(shell, tmp);
			new_list = process_wildcards(shell, tmp);
			if (!new_list)
			{
				free(new_list);
				tmp = tmp->next;
				continue ;
			}
			sort_token(&new_list);
			last = last_token(new_list);
			add_token(shell, tmp, new_list);
			tmp = last;
		}
		tmp = tmp->next;
	}
}

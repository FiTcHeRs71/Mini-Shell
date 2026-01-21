#include "../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>

void	find_wildcard_pattern(t_shell *shell, t_token *token)
{
	int	i;

	i = 0;
	if (!ft_strncmp(token->value, "*", 2))
		token->wildcards.pattern = EVERYTHING;
	else if (token->value[0] != '*')
	{
		pattern_start_with_asterisk(shell, token);
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

void	wildcards(t_shell *shell)
{
	t_token	*last;
	t_token	*new_list;
	t_token	*tmp;

	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->wc == true)
		{
			find_wildcard_pattern(shell, tmp);
			if (tmp->wildcards.pattern != WRONG_PATTERN)
			{
				new_list = process_wildcards(shell, tmp);
				if (!new_list->value)
				{
					tmp = tmp->next;
					continue ;
				}
				// trier liste alphabet
				last = last_token(new_list);
				add_token(shell, tmp, new_list);
				tmp = last;
			}
		}
		tmp = tmp->next;
	}
}

t_token	*process_wildcards(t_shell *shell, t_token *token)
{
	DIR	*dir;
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

// 1. add flag wildcard if NO_QUOTES && strrchr * dans tokenisation
// 2. quand expansion, si flag == true opendir, readdir et strcmp avec le .xyz ou whatever
// 3. collect les matchs dans une liste
// 4. quick sort les args par ordre alphabetiques (sauf le premier)
// 5. remplace la token_list avec une nouvelle contenant les wildcards
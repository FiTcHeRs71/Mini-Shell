#include "../includes/minishell.h"
#include <sys/types.h>
#include <dirent.h>

int	find_asterisk(char *str, int i)
{
	while (str[i] != '*' && str[i])
	{
		i++;
	}
	return (i);
}

void	pattern_start_with_asterisk(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = find_asterisk(token->value, 0);
	token->wildcards->start = ft_substr(token->value, 0, i - 1);
	if (token->value[i + 1])
	{
		j = find_asterisk(token->value, i + 1);
		token->wildcards->end = ft_substr(token->value, i + 1, j);
		token->wildcards->pattern = ANYTHING_IN_BETWEEN;
		if (token->value[j + 1])
			token->wildcards->pattern = WRONG_PATTERN;
	}
	else
		token->wildcards->pattern = START_WITH;
}

void	find_wildcard_pattern(t_shell *shell, t_token *token)
{
	int	i;

	if (ft_strncmp(token->value, "*", 2))
		token->wildcards->pattern = EVERYTHING;
	else if (token->value[0] != '*')
	{
		pattern_start_with_asterisk(shell, token);
	}
	else if (token->value[0] == '*')
	{
		i = find_asterisk(token->value, 1);
		token->wildcards->end = ft_substr(token->value, 1, i);
		if (token->value[i] == '*')
			token->wildcards->pattern = ANYTHING_CONTAINING;
		else if (token->value[i + 1])
			token->wildcards->pattern = WRONG_PATTERN;
		else
			token->wildcards->pattern = END_WITH;
	}
}

void	wildcards(t_shell *shell)
{
	t_token	*tmp;
	t_token	*new_node;

	tmp = shell->token_list;
	while (tmp)
	{
		if (tmp->wc == true)
		{
			if (ft_strrchr(tmp->value, '*'))
			{
				find_wildcard_pattern(shell, tmp);
				if (tmp->wildcards->pattern != WRONG_PATTERN)
					process_wildcards(shell, tmp);
			}
		}
		tmp = tmp->next;
	}
}

void	process_wildcards(t_shell *shell, t_token *token)
{
	DIR	*dir;
	struct dirent	*entry;
	t_token	*new;

	dir = opendir(".");
	if (!dir)
		return ;
	if (token->wildcards == EVERYTHING)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			new = new_token(shell);
			new->value = entry->d_name;
			new->type = TOKEN_WORD;
			add_token(token, new); // si premier token (celui contenant *), remplacer celui-ci par le nouveau
		}
	}
}

// 1. add flag wildcard if NO_QUOTES && strrchr * dans tokenisation
// 2. quand expansion, si flag == true opendir, readdir et strcmp avec le .xyz ou whatever
// 3. collect les matchs dans une liste
// 4. quick sort les args par ordre alphabetiques (sauf le premier)
// 5. remplace la token_list avec une nouvelle contenant les wildcards
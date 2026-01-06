
#include "../../includes/minishell.h"

void	syntaxe_error()
{
	ft_putstr_fd("Minishell : syntax error near unexpected token \n", 2);
}
void	ft_error(t_shell *shell, int error)
{
	if (error == MALLOC)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		clean_before_exit(shell);
		exit(EXIT_FAILURE);
	}
}
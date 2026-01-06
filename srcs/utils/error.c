
#include "../../includes/minishell.h"

void	syntaxe_error(char	*token)
{
	ft_putstr_fd("Minishell : syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

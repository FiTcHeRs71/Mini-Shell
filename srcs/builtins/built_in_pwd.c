
#include "../../includes/minishell.h"

int	exec_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("error retrieving current directory", 2);
		return (2);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

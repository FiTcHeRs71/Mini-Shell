
#include "../../includes/minishell.h"

int	exec_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_error(shell, MALLOC);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

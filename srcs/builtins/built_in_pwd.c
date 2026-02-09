
#include "../../includes/minishell.h"

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	if (printf("%s\n", pwd) < 0)
	{
		perror("pwd: write error");
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}

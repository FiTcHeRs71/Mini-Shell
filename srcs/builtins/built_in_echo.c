
#include "../../includes/minishell.h"

static bool check_n_flag(char *arg, int *i)
{
	if (ft_strncmp(arg, "-n", ft_strlen(arg)) == 0)
	{
		(*i) = 2;
		return (true);
	}
	return (false);
}

int	exec_echo(char **args)
{
	int	i;
	int	n_flag;

	if (!(*args) || !args || !args[1])
	{
		if (ft_putstr_fd_checked("\n", 1) == -1)
			return (perror("echo : write error"), 1);
		return(0);
	}
	i = 1;
	n_flag = check_n_flag(args[1], &i);
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", ft_strlen(args[i])) != 0)
		{
			i++;
			continue ;
		}
		if (ft_putstr_fd_checked(args[i], 1) == -1)
			return (perror("echo : write error"), 1);
		if (args[i + 1] && ft_putstr_fd_checked(" ", 1) == -1)
			return (perror("echo : write error"), 1);
		i++;
	}
	if (!n_flag)
	{
		if(ft_putstr_fd_checked("\n", 1) == -1)
			return (perror("echo : write error"), 1);
	}
	return (0);
}

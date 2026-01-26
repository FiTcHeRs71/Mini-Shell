
#include "../../includes/minishell.h"

static bool	check_multi_n_flag(char *line)
{
	int i;

	i = 0;
	if(line[i] == '-')
	{
		i++;
	}
	else
	{
		return (false);
	}
	while(line[i])
	{
		if (line[i] != 'n')
		{
			return (false);
		}
		else
		{
			i++;
		}
	}
	return (true);
}

static bool	check_n_flag(char **array, int *i)
{
	int flag;

	flag = false;
	while (array[(*i)])
	{
		if (ft_strncmp(array[(*i)], "-n", ft_strlen(array[(*i)])) == 0)
			flag = true;
		if (check_multi_n_flag(array[(*i)]))
			(*i)++;
		else 
		{
			break;
		}
	}
	return (flag);
}

int	exec_echo(char **args , int i)
{
	int	n_flag;
	int	saver_i;

	if (!(*args) || !args || !args[1])
	{
		if (ft_putstr_fd_checked("\n", 1) == -1)
			return (perror("echo : write error"), 1);
		return(0);
	}
	n_flag = check_n_flag(args, &i);
	saver_i = i;
	while (args[i])
	{
		if (ft_putstr_fd_checked(args[i], 1) == -1)
			return (perror("echo : write error"), 1);
		if (args[i + 1] && ft_putstr_fd_checked(" ", 1) == -1)
			return (perror("echo : write error"), 1);
		i++;
	}
	if (!n_flag && i > saver_i)
	{
		if(ft_putstr_fd_checked("\n", 1) == -1)
			return (perror("echo : write error"), 1);
	}
	return (0);
}

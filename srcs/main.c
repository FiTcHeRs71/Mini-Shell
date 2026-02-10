/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:16:54 by fducrot           #+#    #+#             */
/*   Updated: 2026/02/10 18:17:07 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal;

static void	handle_ctrl_c(t_shell *shell)
{
	shell->last_exit_status = g_signal;
	g_signal = 0;
	clean_all(shell);
}

static void	reset_var(t_shell *shell, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	shell->tree_ast = NULL;
	shell->token_list = NULL;
	shell->last_exit_status = 0;
	errno = 0;
}

static void	tokenise_parse_exec(t_shell *shell, char *line)
{
	tokenisation(shell, line);
	if (!g_signal)
	{
		parse(shell->token_list, shell);
		if (!g_signal)
		{
			init_signal_exec();
			g_signal = exec_ast(shell, shell->tree_ast);
			init_signal();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	g_signal = 0;
	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	while (true)
	{
		reset_var(&shell, argc, argv);
		if (g_signal != 0)
			update_signal(&shell);
		line = readline("Minishell > ");
		if (g_signal != 0)
		{
			handle_ctrl_c(&shell);
		}
		if (!line)
			break ;
		add_history(line);
		if (line)
			tokenise_parse_exec(&shell, line);
		clean_up_loop(&shell);
	}
	clean_before_exit(&shell);
	rl_clear_history();
}

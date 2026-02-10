/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 10/02/2026 17:14:58 by fducrot           #+#    #+#             */
/*   Updated: 10/02/2026 18:16:22 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_signals(t_heredoc_data *data)
{
	rl_catch_signals = 1;
	rl_catch_sigwinch = 1;
	sigaction(SIGINT, &data->old_int, NULL);
	sigaction(SIGQUIT, &data->old_quit, NULL);
	rl_done = 0;
	rl_event_hook = NULL;
	rl_outstream = stdout;
}

static void	here_doc_sigint(int sig)
{
	(void)sig;
	g_signal = 1;
}

static int	heredoc_event_hook(void)
{
	if (g_signal)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	set_hd_signal(t_heredoc_data *data)
{
	struct sigaction	new_int;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	new_int.sa_handler = here_doc_sigint;
	sigemptyset(&new_int.sa_mask);
	new_int.sa_flags = 0;
	sigaction(SIGINT, &new_int, &data->old_int);
	sigaction(SIGQUIT, NULL, &data->old_quit);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = heredoc_event_hook;
	rl_outstream = stderr;
}

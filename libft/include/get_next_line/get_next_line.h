/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:33:57 by fducrot           #+#    #+#             */
/*   Updated: 2025/12/12 10:33:57 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1000
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

/* get_next_line_bonus.c */
char	*get_next_line(int fd);
char	*ft_update_static(char *all_files);
char	*ft_define_line(char *all_files);
char	*ft_read_doc(int fd, char *buffer, char *all_files);

#endif
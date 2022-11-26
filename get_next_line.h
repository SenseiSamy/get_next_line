/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:35:10 by snaji             #+#    #+#             */
/*   Updated: 2022/11/26 01:05:31 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_line
{
	char			buf[BUFFER_SIZE + 1];
	struct s_line	*next;
}					t_line;

typedef struct s_fd
{
	int			fd;
	char		buf[BUFFER_SIZE + 1];
	struct s_fd	*next;
}	t_fd;

char	*get_next_line(int fd);
t_line	*get_line(t_fd *fd, int *buf_count);
t_line	*get_one(t_fd *fd, ssize_t *ret, int *buf_count);
t_fd	*get_fd(int fd, t_fd **list_fd);
char	*build_line(t_line **line, int buf_count);
void	remove_line_from_buf(t_fd *fd);
void	remove_fd(int fd, t_fd **liste_fd);
void	free_line(t_line **line);
size_t	eol_pos(char *s);
#endif
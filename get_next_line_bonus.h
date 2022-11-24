/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:35:22 by snaji             #+#    #+#             */
/*   Updated: 2022/11/24 16:26:33 by snaji            ###   ########.fr       */
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
t_line	*get_line(int fd, char *buf, int *buf_count);
t_line	*get_one(int fd, char *buf, ssize_t *ret, int *buf_count);
char	*get_fd_buf(int fd, t_fd **list_fd);
char	*build_line(t_line **line, int buf_count);
void	remove_line_from_buf(char *buffer);
void	remove_fd(int fd, t_fd **liste_fd);
void	free_line(t_line **line);
int		is_end_line(char *s);
#endif
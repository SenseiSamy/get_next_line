/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:54:03 by snaji             #+#    #+#             */
/*   Updated: 2022/11/26 01:13:51 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd	*list_fd;
	t_line		*line;
	t_fd		*current_fd;
	int			buf_count;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	current_fd = get_fd(fd, &list_fd);
	if (!current_fd)
		return (NULL);
	line = get_line(current_fd, &buf_count);
	if (!line)
		return (free_line(&line), remove_fd(fd, &list_fd), NULL);
	return (build_line(&line, buf_count));
}

char	*build_line(t_line **line, int buf_count)
{
	char	*result;
	t_line	*curr;
	size_t	i;
	size_t	j;

	result = malloc((buf_count * BUFFER_SIZE + 1) * sizeof (*result));
	if (!result)
		return (free_line(line), NULL);
	curr = *line;
	j = 0;
	while (curr)
	{
		i = 0;
		while (curr->buf[i] && curr->buf[i] != '\n')
			result[j++] = curr->buf[i++];
		if (curr->buf[i] == '\n')
			result[j++] = '\n';
		curr = curr->next;
	}
	result[j] = '\0';
	free_line(line);
	return (result);
}

t_line	*get_line(t_fd *fd, int *buf_count)
{
	t_line	*line;
	t_line	*curr;
	ssize_t	ret;
	size_t	i;

	*buf_count = 0;
	ret = -1;
	line = get_one(fd, &ret, buf_count);
	curr = line;
	if (!curr)
		return (NULL);
	while (ret && !eol_pos(curr->buf))
	{
		curr->next = get_one(fd, &ret, buf_count);
		if (!curr->next)
			return (free_line(&line), NULL);
		curr = curr->next;
	}
	i = 0;
	while (curr->buf[++i - 1])
		fd->buf[i - 1] = curr->buf[i - 1];
	remove_line_from_buf(fd);
	if (line->buf[0])
		return (line);
	return (free_line(&line), NULL);
}

t_line	*get_one(t_fd *fd, ssize_t *ret, int *buf_count)
{
	t_line	*line_el;

	*ret = 0;
	line_el = malloc(sizeof (*line_el));
	if (!line_el)
		return (NULL);
	line_el->next = NULL;
	if (*fd->buf)
	{
		while (fd->buf[*ret])
		{
			line_el->buf[*ret] = fd->buf[*ret];
			++*ret;
		}
		remove_line_from_buf(fd);
	}
	else
		*ret = read(fd->fd, line_el->buf, BUFFER_SIZE);
	if (*ret == -1)
		return (free(line_el), NULL);
	line_el->buf[*ret] = '\0';
	++*buf_count;
	return (line_el);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:54:03 by snaji             #+#    #+#             */
/*   Updated: 2022/11/23 21:31:13 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd	*list_fd;
	t_line		*line;
	char		*current_buf;
	int			buf_count;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	current_buf = get_fd_buf(fd, &list_fd);
	if (!current_buf)
		return (NULL);
	line = get_line(fd, current_buf, &buf_count);
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

t_line	*get_line(int fd, char *buf, int *buf_count)
{
	t_line	*line;
	t_line	*curr;
	ssize_t	ret;
	size_t	i;

	*buf_count = 0;
	ret = -1;
	line = get_one(fd, buf, &ret, buf_count);
	curr = line;
	if (!curr)
		return (NULL);
	while (ret && !is_end_line(curr->buf))
	{
		curr->next = get_one(fd, buf, &ret, buf_count);
		if (!curr->next)
			return (free_line(&line), NULL);
		curr = curr->next;
	}
	i = 0;
	while (++i - 1 < BUFFER_SIZE + 1)
		buf[i - 1] = curr->buf[i - 1];
	remove_line_from_buf(buf);
	if (line->buf[0])
		return (line);
	return (free_line(&line), NULL);
}

t_line	*get_one(int fd, char *buf, ssize_t *ret, int *buf_count)
{
	t_line	*line_el;
	size_t	i;

	*ret = -1;
	line_el = malloc(sizeof (*line_el));
	if (!line_el)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		line_el->buf[i++] = '\0';
	line_el->next = NULL;
	if (buf && *buf)
	{
		while (buf[++*ret])
			line_el->buf[*ret] = buf[*ret];
	}
	else
		*ret = read(fd, line_el->buf, BUFFER_SIZE);
	if (*ret == -1)
		return (free(line_el), NULL);
	++*buf_count;
	remove_line_from_buf(buf);
	return (line_el);
}

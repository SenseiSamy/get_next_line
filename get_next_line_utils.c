/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:26:16 by snaji             #+#    #+#             */
/*   Updated: 2022/11/26 01:04:06 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Returns the buffer corresponding to the fd in list_fd */
/* or creates one and add it to the list */
t_fd	*get_fd(int fd, t_fd **list_fd)
{
	t_fd	*tmp;

	tmp = *list_fd;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = malloc(sizeof (*tmp));
	if (!tmp)
		return (NULL);
	tmp->buf[0] = '\0';
	tmp->fd = fd;
	tmp->next = *list_fd;
	*list_fd = tmp;
	return (tmp);
}

/* Removes the corresponding fd from the list of fd */
void	remove_fd(int fd, t_fd **liste_fd)
{
	t_fd	*tmp;
	t_fd	*current;

	if ((*liste_fd)->fd == fd)
	{
		tmp = (*liste_fd)->next;
		free(*liste_fd);
		*liste_fd = tmp;
	}
	else
	{
		current = *liste_fd;
		while (current->next != NULL)
		{
			if (current->next->fd == fd)
			{
				tmp = current->next;
				current->next = current->next->next;
				free(tmp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

/* Remove one line from the buffer */
void	remove_line_from_buf(t_fd *fd)
{
	size_t	i;
	size_t	j;
	size_t	shift;	

	if (!*fd->buf)
		return ;
	shift = eol_pos(fd->buf);
	i = 0;
	if (!shift)
		while (fd->buf[i])
			fd->buf[i++] = '\0';
	else
	{
		i = shift;
		while (i--)
		{
			j = 0;
			while (fd->buf[++j])
				fd->buf[j - 1] = fd->buf[j];
			fd->buf[j - 1] = fd->buf[j];
		}
	}
}

/* Frees the linked list line and set its pointer to NULL */
void	free_line(t_line **line)
{
	t_line	*curr;
	t_line	*tmp;

	if (!line)
		return ;
	curr = *line;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*line = NULL;
}

/* Returns the index + 1 of the first occurence of the eol character in s. */
/* Returns 0 if s doesnt contain eol */
size_t	eol_pos(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		++i;
	}
	return (0);
}

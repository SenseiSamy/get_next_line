/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:26:16 by snaji             #+#    #+#             */
/*   Updated: 2022/11/23 21:30:28 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Returns the buffer corresponding to the fd in list_fd */
/* or creates one and add it to the list */
char	*get_fd_buf(int fd, t_fd **list_fd)
{
	t_fd	*tmp;
	int		i;

	tmp = *list_fd;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp->buf);
		tmp = tmp->next;
	}
	tmp = malloc(sizeof (*tmp));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		tmp->buf[i++] = '\0';
	tmp->fd = fd;
	tmp->next = *list_fd;
	*list_fd = tmp;
	return (tmp->buf);
}

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
void	remove_line_from_buf(char *buffer)
{
	size_t		i;
	size_t		j;
	char		*tmp;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof (*tmp));
	if (tmp)
	{
		i = 0;
		j = 0;
		while (i < BUFFER_SIZE && buffer[i] != '\n')
			++i;
		++i;
		while (i < BUFFER_SIZE)
			tmp[j++] = buffer[i++];
		while (j < BUFFER_SIZE)
			tmp[j++] = '\0';
		i = 0;
		while (i < BUFFER_SIZE)
		{
			buffer[i] = tmp[i];
			++i;
		}
		free(tmp);
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

/* Returns 1 if the buffer contains eol, returns 0 otherwise*/
int	is_end_line(char *s)
{
	while (s && *s)
		if (*s++ == '\n')
			return (1);
	return (0);
}

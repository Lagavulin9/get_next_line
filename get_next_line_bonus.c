/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:41:28 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/10 11:40:37 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>

t_list	*list_add_new(t_list **head, int fd)
{
	t_list	*elem;
	t_list	*new;
	t_info	info;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	info.index = BUFFER_SIZE;
	info.rbyte = BUFFER_SIZE;
	new->fd = fd;
	new->info = info;
	new->next = 0;
	if (!*head)
		*head = new;
	else
	{
		elem = *head;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	return (new);
}

void	list_del(t_list **head, int fd)
{
	t_list	*elem;
	t_list	*tmp;

	if (!head || !*head)
		return ;
	elem = *head;
	while (elem->next)
	{
		if (elem->next->fd == fd)
		{
			tmp = elem->next->next;
			free(elem->next);
			elem->next = tmp;
			return ;
		}
		elem = elem->next;
	}
	elem = *head;
	if (elem->fd == fd)
	{
		*head = elem->next;
		free(elem);
	}
}

t_info	*get_info_from_list(t_list **head, int fd)
{
	t_list	*elem;

	elem = *head;
	while (elem)
	{
		if (elem->fd == fd)
			return (&elem->info);
		if (!elem->next)
			break ;
		elem = elem->next;
	}
	elem = list_add_new(head, fd);
	return (&elem->info);
}

char	*get_next_line(int fd)
{
	static t_list	*head = 0;
	t_info			*info;
	char			*line;

	info = get_info_from_list(&head, fd);
	if (!init(fd, &line, info, &head))
		return (0);
	while (1)
	{
		if ((size_t)info->rbyte == info->index)
		{
			line = join(line, info);
			info->rbyte = read(fd, info->buffer, BUFFER_SIZE);
			if (buf_end(&line, info))
			{
				list_del(&head, fd);
				return (line);
			}
			info->index = 0;
		}
		info->len++;
		if (info->buffer[info->index++] == '\n')
			return (join(line, info));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:00:45 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/10 11:41:20 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	init(int fd, char **line, t_info *info)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	else
	{
		*line = 0;
		info->total = 0;
		info->len = 0;
		return (1);
	}
}

void	*ft_memcpy(char	*dst, char *src, size_t n)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	buf_end(char **line, t_info *info)
{
	if (info->rbyte == -1 || (!info->rbyte && !info->total))
	{
		free(*line);
		*line = 0;
		info->index = BUFFER_SIZE;
		info->rbyte = BUFFER_SIZE;
		return (1);
	}
	if (!info->rbyte && info->total)
	{
		info->index = BUFFER_SIZE;
		info->rbyte = BUFFER_SIZE;
		return (1);
	}
	return (0);
}

char	*join(char *line, t_info *info)
{
	char	*buffer;
	char	*new_line;

	buffer = info->buffer + info->index - info->len;
	new_line = malloc(info->total + info->len + 1);
	if (!new_line)
		return (0);
	if (line)
	{
		ft_memcpy(new_line, line, info->total);
		free(line);
	}
	ft_memcpy(new_line + info->total, (char *)buffer, info->len);
	info->total += info->len;
	info->len = 0;
	new_line[info->total] = 0;
	return (new_line);
}

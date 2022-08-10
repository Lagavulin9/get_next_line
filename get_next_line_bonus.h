/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:34:44 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/10 11:41:05 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_info
{
	char	buffer[BUFFER_SIZE];
	size_t	index;
	size_t	len;
	size_t	total;
	ssize_t	rbyte;
}				t_info;

typedef struct s_list
{
	int				fd;
	t_info			info;
	struct s_list	*next;
}				t_list;

int		init(int fd, char **line, t_info *info, t_list **head);
void	*ft_memcpy(char	*dst, char *src, size_t n);
int		buf_end(char **line, t_info *info);
char	*join(char *line, t_info *info);
char	*get_next_line(int fd);
void	list_del(t_list **head, int fd);
t_list	*list_add_new(t_list **head, int fd);
t_info	*get_info_from_list(t_list **head, int fd);

#endif
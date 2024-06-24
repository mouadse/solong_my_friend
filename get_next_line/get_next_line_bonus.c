/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:13:41 by msennane          #+#    #+#             */
/*   Updated: 2024/03/07 22:58:51 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_queue(t_list *node)
{
	struct s_list_node	*temp;

	while (node->head)
	{
		temp = node->head;
		node->head = node->head->next;
		free(temp);
	}
	node->tail = NULL;
}

static char	*extract_line(t_list *node)
{
	char				*line;
	int					i;
	struct s_list_node	*temp;

	i = 0;
	temp = node->head;
	while (temp && temp->data != '\n')
	{
		temp = temp->next;
		i++;
	}
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (node->head && node->head->data != '\n')
		line[i++] = pop_node(node);
	line[i++] = pop_node(node);
	line[i] = '\0';
	return (line);
}

static char	*extract_rest(t_list *node)
{
	char				*rest;
	int					i;
	struct s_list_node	*temp;

	i = 0;
	temp = node->head;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	rest = malloc(sizeof(char) * (i + 1));
	if (!rest)
		return (NULL);
	i = 0;
	while (node->head)
		rest[i++] = pop_node(node);
	rest[i] = '\0';
	return (rest);
}

static char	*handle_cases(ssize_t bytes, t_list *node, char *rest, int *fd)
{
	ssize_t	i;

	if (bytes == -1)
	{
		free(rest);
		free_queue(node);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(rest);
		if (is_it_empty(node))
			return (NULL);
		else
			return (extract_rest(node));
	}
	else
	{
		i = 0;
		while (i < bytes)
			push_node(node, rest[i++]);
		free(rest);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	ssize_t				bytes;
	char				*rest;
	t_open_file			*file;
	static t_open_file	files[OPEN_MAX] = {};

	if (fd < 0 || fd > MAX_OPEN_FILES || BUFFER_SIZE <= 0)
		return (NULL);
	file = &files[fd];
	if (file->is_open == 0)
	{
		initialize_queue(&file->node);
		file->is_open = 1;
	}
	if (file->node.head && has_new_line(&file->node))
		return (extract_line(&file->node));
	rest = malloc(sizeof(char) * (BUFFER_SIZE));
	if (!rest)
		return (NULL);
	bytes = read(fd, rest, BUFFER_SIZE);
	return (handle_cases(bytes, &file->node, rest, &fd));
}

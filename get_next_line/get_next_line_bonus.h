/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:21:10 by msennane          #+#    #+#             */
/*   Updated: 2024/03/07 20:27:38 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define MAX_OPEN_FILES 1024

struct					s_list_node
{
	char				data;
	struct s_list_node	*next;
};

typedef struct s_list
{
	struct s_list_node	*head;
	struct s_list_node	*tail;
}						t_list;

typedef struct File
{
	t_list				node;
	int					is_open;
}						t_open_file;

void					initialize_queue(t_list *node);
void					push_node(t_list *node, char c);
char					pop_node(t_list *node);
int						has_new_line(t_list *node);
int						is_it_empty(t_list *node);
char					*get_next_line(int fd);

#endif

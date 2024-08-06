/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:44:33 by msennane          #+#    #+#             */
/*   Updated: 2024/01/21 20:45:03 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	prt_hexa(unsigned int n, int is_upper);
int	prt_int(int n);
int	prt_pointer(void *address);
int	prt_str(char const *str);
int	prt_unsigned(unsigned int nbr);

#endif

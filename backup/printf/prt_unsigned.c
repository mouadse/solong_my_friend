/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:36:50 by msennane          #+#    #+#             */
/*   Updated: 2024/01/20 14:46:24 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	number_of_digits(unsigned int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	print_unsigned(unsigned int nbr)
{
	static char	*dgts;

	dgts = "0123456789";
	if (nbr > 9)
		print_unsigned(nbr / 10);
	write(1, &dgts[nbr % 10], 1);
}

int	prt_unsigned(unsigned int nbr)
{
	print_unsigned(nbr);
	return (number_of_digits(nbr));
}

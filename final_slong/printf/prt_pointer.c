/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:59 by msennane          #+#    #+#             */
/*   Updated: 2024/01/19 21:50:43 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	number_of_dgts(unsigned long long n)
{
	size_t	dgts;

	dgts = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		dgts += 1;
		n /= 16;
	}
	return (dgts);
}

static void	ft_put_hex(unsigned long long n)
{
	static char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_put_hex(n / 16);
	write(1, &base[n % 16], 1);
}

int	prt_pointer(void *address)
{
	if (address == NULL)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	ft_put_hex((unsigned long long)address);
	return (number_of_dgts((unsigned long long)address) + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:07:55 by msennane          #+#    #+#             */
/*   Updated: 2024/08/05 23:21:42 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *str)
{
	char	*word;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	word = malloc(ft_strlen(str) + 1);
	if (!word)
		return (NULL);
	while (str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}


static int	calculate_len(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	gen_char_array(char *int_str, long number, int len, int sign)
{
	while (number && len--)
	{
		int_str[len + sign] = (number % 10) + 48;
		number /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*int_str;
	long	number;

	number = (long)n;
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		number = -number;
	}
	len = calculate_len(number);
	int_str = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!int_str)
		return (NULL);
	if (sign)
		int_str[0] = '-';
	int_str[len + sign] = '\0';
	gen_char_array(int_str, number, len, sign);
	return (int_str);
}

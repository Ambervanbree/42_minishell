/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:16:10 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/16 16:16:12 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	nr_char(long long n)
{
	long long	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long long	i;
	char		*str;
	long long	nb;

	nb = n;
	i = nr_char(nb);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	if (nb < 0)
		nb = nb * -1;
	while (i >= 0)
	{
		str[i] = (nb % 10 + '0');
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

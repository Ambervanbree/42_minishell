/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:24:07 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 16:45:08 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *restrict s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *)s;
	dest = (unsigned char *)d;
	i = 0;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
		{
			dest[i] = src[i];
			return (&dest[i + 1]);
		}
		else
			dest[i] = src[i];
		i++;
	}
	return (NULL);
}

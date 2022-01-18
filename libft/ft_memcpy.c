/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 10:33:52 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 16:42:26 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict d, const void *restrict s, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *)s;
	dest = (unsigned char *)d;
	i = 0;
	if (src == 0 && dest == 0)
		return (dest);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

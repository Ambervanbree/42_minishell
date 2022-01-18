/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:48:18 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 16:45:56 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t len)
{
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *)s;
	dest = (unsigned char *)d;
	if (src == 0 && dest == 0)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	while (len-- > 0)
	{
		dest[len] = src[len];
	}
	return (dest);
}

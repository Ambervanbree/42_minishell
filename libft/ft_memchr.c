/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:08:22 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 16:47:16 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*hs;
	unsigned int	i;

	hs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (hs[i] == (unsigned char)c)
			return (&hs[i]);
		i++;
	}
	return (0);
}

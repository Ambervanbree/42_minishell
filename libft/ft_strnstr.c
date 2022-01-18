/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:37:13 by avan-bre          #+#    #+#             */
/*   Updated: 2021/12/07 17:23:32 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t n)
{
	size_t	i;
	size_t	j;
	char	*hs;
	char	*nd;

	i = 0;
	hs = (char *)big;
	nd = (char *)small;
	if (*nd == 0)
		return (hs);
	while (hs[i] && i < n)
	{
		j = 0;
		while (hs[i + j] == nd[j] & (i + j) < n)
		{
			j++;
			if (nd[j] == '\0')
				return (&hs[i]);
		}
		i++;
	}
	return (0);
}

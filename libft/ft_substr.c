/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 08:27:12 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 17:21:59 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || len > ft_strlen(s))
		sub = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			sub[i] = (char)s[start];
			i++;
			start++;
		}
		sub[i] = 0;
	}
	else
		sub[i] = 0;
	return (sub);
}

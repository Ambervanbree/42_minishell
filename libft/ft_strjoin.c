/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:13:29 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 17:22:55 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2));
	mem = malloc(size + 1);
	if (!mem)
		return (NULL);
	ft_strlcpy((char *)mem, (char *)s1, (ft_strlen(s1) + 1));
	ft_strlcat((char *)mem, (char *)s2, (size + 1));
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:33:02 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 17:53:05 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ischar(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*mem;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ischar(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > 0 && ischar(s1[j - 1], set))
		j--;
	if (j == 0 || ft_strlen(s1) == 0)
	{
		mem = malloc(sizeof(char) * 1);
		mem[0] = 0;
		return (mem);
	}
	mem = malloc(sizeof(char) * (j - i + 1));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s1 + i, j - i + 1);
	return (mem);
}

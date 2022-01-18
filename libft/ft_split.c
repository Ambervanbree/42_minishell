/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:57:15 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/04 16:33:26 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nr_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (ft_strlen(s) - 1))
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != 0)
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}

size_t	get_word(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	**make_ret(char const *s, char **ret, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] && k < nr_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = get_word((char *)(s + i), c);
		ret[k] = ft_substr(s, i, j);
		k++;
		i = j + i;
	}
	ret[k] = 0;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		ret = (char **)malloc(sizeof(char *));
		ret[0] = (NULL);
		return (ret);
	}
	ret = (char **)malloc((nr_words(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	return (make_ret(s, ret, c));
}

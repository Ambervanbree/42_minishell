/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 16:13:51 by avan-bre          #+#    #+#             */
/*   Updated: 2021/06/03 17:27:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*mem;

	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s1, (ft_strlen(s1) + 1));
	return (mem);
}

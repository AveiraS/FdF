/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:35:01 by pthuy             #+#    #+#             */
/*   Updated: 2019/10/09 12:55:25 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*find)
		return ((char *)str);
	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		while (i + j < len && str[i + j] == find[j] && find[j])
			j++;
		if (!find[j])
			return ((char *)str + i);
		i++;
	}
	return (0);
}

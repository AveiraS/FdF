/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:10:38 by pthuy             #+#    #+#             */
/*   Updated: 2019/10/09 12:55:25 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_recclear(char **t, int i)
{
	while (t[--i])
		free(t[i]);
	free(t);
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**t;

	if (!s || !(t = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1))))
		return (0);
	i = 0;
	k = 0;
	while (i < ft_wordcount(s, c))
	{
		if (!(t[i] = (char *)malloc(sizeof(char) * (ft_wordlen(s + k, c) + 1))))
		{
			ft_recclear(t, i);
			return (0);
		}
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			t[i][j++] = s[k++];
		t[i++][j] = '\0';
	}
	t[i] = 0;
	return (t);
}

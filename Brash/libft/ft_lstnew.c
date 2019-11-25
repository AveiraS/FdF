/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:37:03 by pthuy             #+#    #+#             */
/*   Updated: 2019/09/23 23:59:33 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == NULL)
		return (NULL);
	if (content == NULL)
	{
		newlst->content = NULL;
		newlst->content_size = 0;
	}
	else
	{
		newlst->content = malloc(content_size);
		if (newlst->content == NULL)
			return (NULL);
		ft_memmove(newlst->content, content, content_size);
		newlst->content_size = content_size;
	}
	newlst->next = NULL;
	return (newlst);
}

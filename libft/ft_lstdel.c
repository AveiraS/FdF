/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:38:49 by pthuy             #+#    #+#             */
/*   Updated: 2019/09/23 23:59:33 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;
	t_list	*next;

	ptr = *alst;
	if (del != NULL && *alst != NULL && alst != NULL)
	{
		while (ptr != NULL)
		{
			next = ptr->next;
			del(ptr->content, ptr->content_size);
			free(ptr);
			ptr = next;
		}
		*alst = NULL;
	}
}

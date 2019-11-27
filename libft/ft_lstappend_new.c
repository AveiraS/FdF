/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:21:15 by pthuy             #+#    #+#             */
/*   Updated: 2019/10/18 17:36:06 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstappend_new(t_list **alst, t_list *new)
{
	t_list		*alstcp;

	alstcp = *alst;
	if (*alst == NULL)
	{
		*alst = ft_lstnew(new->content, new->content_size);
		return ;
	}
	while (alstcp->next)
		alstcp = alstcp->next;
	alstcp->next = new;
}

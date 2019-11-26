/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthuy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:48:45 by pthuy             #+#    #+#             */
/*   Updated: 2019/09/24 19:48:47 by pthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list *alst)
{
	t_list	*tmp;

	if (alst == NULL)
		return ;
	while (alst)
	{
		tmp = alst->next;
		free(alst->content);
		free(alst);
		alst = tmp;
	}
	free(alst);
	alst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:54:36 by ygolshan          #+#    #+#             */
/*   Updated: 2022/11/06 16:01:56 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*n;

	if (lst && del)
	{
		temp = *lst;
		if (temp)
		{
			del (temp->content);
			while (temp->next)
			{
				n = temp->next;
				free(temp);
				temp = n;
				del (temp->content);
			}
			free(temp);
		}
		*lst = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:32:59 by ygolshan          #+#    #+#             */
/*   Updated: 2022/11/08 10:50:33 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	if (!dest && len == 0)
		return (0);
	while (dest[j] && j < len)
		j++;
	while ((src[k]) && ((j + k + 1) < len))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != len)
		dest[j + k] = '\0';
	return (j + ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:53:33 by ygolshan          #+#    #+#             */
/*   Updated: 2022/11/08 10:26:42 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!(str))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_together;
	int		i;

	if (s1 && s2)
	{
		str_together = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (str_together)
		{
			i = 0;
			while (*s1)
			{
				str_together[i++] = *s1;
				s1++;
			}
			while (*s2)
			{
				str_together[i++] = *s2;
				s2++;
			}
			str_together[i] = '\0';
			return (str_together);
		}
	}
	return (NULL);
}

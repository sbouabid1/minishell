/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:18:31 by touahman          #+#    #+#             */
/*   Updated: 2023/11/04 18:18:32 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dst;
	if (!s1 && !s2)
		return (dst);
	if (s1 == s2)
		return ((char *)src);
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:18:38 by touahman          #+#    #+#             */
/*   Updated: 2023/11/04 18:18:39 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s || len == 0)
		return (dst);
	i = 0;
	if (d > s)
	{
		while (i < len)
		{
			i++;
			d[len - i] = s[len - i];
		}
	}
	else
		ft_memcpy(d, s, len);
	return (d);
}

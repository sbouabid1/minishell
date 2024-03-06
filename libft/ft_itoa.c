/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:18:04 by touahman          #+#    #+#             */
/*   Updated: 2023/11/04 18:18:06 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_str_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = get_str_len(nb);
	str = (char *)malloc((len + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		len--;
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

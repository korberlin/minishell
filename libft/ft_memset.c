/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:14:55 by gkoksal           #+#    #+#             */
/*   Updated: 2024/06/19 13:20:16 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	ch;

	src = (unsigned char *)s;
	i = 0;
	ch = (unsigned char)c;
	while (i < n)
	{
		*src = ch;
		src++;
		i++;
	}
	return (s);
}

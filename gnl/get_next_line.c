/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:20:01 by gkoksal           #+#    #+#             */
/*   Updated: 2024/03/27 12:20:49 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer;
	char	line[70000];
	int		b;
	int		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	b = read(fd, &buffer, 1);
	while (b > 0)
	{
		line[i++] = buffer;
		if (buffer == '\n')
			break ;
		b = read(fd, &buffer, 1);
	}
	line[i] = '\0';
	if (b <= 0 && i == 0)
		return (NULL);
	return (ft_strdupp(line));
}
// #include <fcntl.h>
// #include <stdio.h>
// int main(void)
// {
// 	int fd = open("maps.ber2", O_RDONLY);
// 	char *str;
// 	int i  = 0;
// 	while (i++ < 20)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s",str);
// 		free(str);
// 		str = NULL;
// 	}
// 	free(str);
// 	close(fd);
// }

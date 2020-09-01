/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 12:40:45 by ncolomer          #+#    #+#             */
/*   Updated: 2019/12/12 23:24:10 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				ft_atoi(char *str)
{
	int		nb;

	if (*str == '\0')
		return (-1);
	nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		nb = 10 * nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (nb);
}


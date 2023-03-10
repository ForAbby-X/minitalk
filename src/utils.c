/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:44:27 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/08 18:06:21 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(char *str)
{
	size_t	size;

	if (str == NULL)
		return (0lu);
	size = 0;
	while (str[size])
		size++;
	return (size);
}

ssize_t	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

static size_t	_ft_putnbr(int nbr, char buff[11], size_t index)
{
	size_t	ret;

	if (nbr >= 10)
		ret = _ft_putnbr(nbr / 10, buff, index - 1);
	else
		ret = index;
	buff[index] = '0' + (nbr % 10);
	return (ret);
}

ssize_t	ft_putnbr(int nbr)
{
	char	buff[12];
	size_t	index;
	int		neg;

	if (nbr == -2147483648)
		return (ft_putstr("-21474836478"));
	if (nbr < 0)
	{
		neg = 1;
		nbr = -nbr;
	}
	else
		neg = 0;
	index = -1;
	while (++index < 12)
		buff[index] = 0;
	index = _ft_putnbr(nbr, buff, 10);
	if (neg)
		buff[index - 1] = '-';
	return (ft_putstr(buff + index - neg));
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:43:51 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/10 20:02:22 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client_dat	g_dat;

static void	_signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_dat.ping = 1;
}

static void	_send_byte(uint8_t byte)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (byte & (1 << i))
			kill(g_dat.sender_pid, SIGUSR1);
		else
			kill(g_dat.sender_pid, SIGUSR2);
		while (g_dat.ping == 0)
			;
		g_dat.ping = 0;
		i--;
	}
}

static void	_send_phrase(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	_send_byte((size >> 56) & 0xFF);
	_send_byte((size >> 48) & 0xFF);
	_send_byte((size >> 40) & 0xFF);
	_send_byte((size >> 32) & 0xFF);
	_send_byte((size >> 24) & 0xFF);
	_send_byte((size >> 16) & 0xFF);
	_send_byte((size >> 8) & 0xFF);
	_send_byte(size & 0xFF);
	while (1)
	{
		_send_byte(*str);
		if (*str == '\0')
			return ;
		str++;
	}
}

static void	_init_dat(int sender_pid)
{
	g_dat.my_pid = getpid();
	g_dat.sender_pid = sender_pid;
	g_dat.ping = 0;
	g_dat.flag = 0;
	ft_putstr("my pid:");
	ft_putnbr(g_dat.my_pid);
	write(1, (char [1]){'\n'}, 1);
}

int	main(int argc, char **argv)
{
	t_sigact	act;
	int			pid;

	if (argc != 3)
		return (ft_putstr("ERROR:Invalid number of args (must be three)\n"), 0);
	if (!ft_isallnum(argv[1]))
		return (ft_putstr("ERROR:Invalid PID (must be numbers only)\n"), 0);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		return (ft_putstr("ERROR:Invalid PID (PID is negative)\n"), 0);
	_init_dat(pid);
	setup_signal(&act, _signal_handler);
	if (kill(g_dat.sender_pid, SIGUSR1) != 0)
		return (ft_putstr("ERROR:Invalid PID (PID isn't in use)\n"), 0);
	while (g_dat.ping == 0)
		;
	g_dat.ping = 0;
	_send_phrase(argv[2]);
	return (1);
}

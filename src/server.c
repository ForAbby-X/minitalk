/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:43:48 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/10 20:02:19 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_dat	g_dat;

static void	_get_pid(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig != SIGUSR1)
		return ;
	g_dat.sender_pid = info->si_pid;
	ft_putstr("client pid is:");
	ft_putnbr(g_dat.sender_pid);
	write(1, (char [1]){'\n'}, 1);
}

static void	_packet_handler(void)
{
	g_dat.packet_nbr++;
	if (g_dat.packet_nbr <= 8)
		g_dat.str_size = (g_dat.str_size << 8) | g_dat.packet.data;
	if (g_dat.packet_nbr == 8)
	{
		g_dat.tmp_str = malloc(g_dat.str_size + 1);
		if (g_dat.tmp_str == NULL)
		{
			g_dat.flag = 1;
			return ;
		}
	}
	if (g_dat.packet_nbr > 8)
	{
		g_dat.tmp_str[g_dat.index] = g_dat.packet.data;
		g_dat.index++;
		if (g_dat.index >= g_dat.str_size + 1)
			g_dat.string = g_dat.tmp_str;
	}
}

static void	_signal_handler(int sig)
{
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	g_dat.packet.data = (g_dat.packet.data << 1) | (sig == SIGUSR1);
	g_dat.packet.size++;
	if (g_dat.packet.size == 8)
	{
		_packet_handler();
		g_dat.packet.size = 0;
	}
	kill(g_dat.sender_pid, SIGUSR1);
}

static void	_init_dat(void)
{
	g_dat.my_pid = getpid();
	g_dat.sender_pid = -1;
	g_dat.packet.size = 0;
	g_dat.string = NULL;
	g_dat.tmp_str = NULL;
	g_dat.ping = 0;
	g_dat.index = 0;
	g_dat.packet_nbr = 0;
	g_dat.str_size = 0;
	g_dat.flag = 0;
	ft_putstr("my pid:");
	ft_putnbr(g_dat.my_pid);
	write(1, (char [1]){'\n'}, 1);
}

int	main(void)
{
	t_sigact	act;

	while (1)
	{
		_init_dat();
		setup_signal_info(&act, _get_pid);
		while (g_dat.sender_pid == -1)
			;
		setup_signal(&act, _signal_handler);
		kill(g_dat.sender_pid, SIGUSR1);
		while (g_dat.string == NULL)
		{
			if (g_dat.flag)
			{
				ft_putstr("ERROR:Memory error (malloc fail)\n");
				return (0);
			}
		}
		ft_putstr("Client message:\n");
		if (g_dat.str_size)
			write(1, g_dat.string, g_dat.str_size);
		write(1, (char [1]){'\n'}, 1);
		free(g_dat.string);
	}
	return (1);
}

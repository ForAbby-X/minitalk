/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:43:53 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/09 19:28:20 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct sigaction		t_sigact;
typedef struct s_server_data	t_server_dat;
typedef struct s_client_data	t_client_dat;
typedef struct s_packet			t_packet;

size_t	ft_strlen(char *str);
ssize_t	ft_putstr(char *str);
ssize_t	ft_putnbr(int nbr);
int		ft_atoi(char *str);

int		setup_signal_info(t_sigact *act, void (*f)(int, siginfo_t *, void *));
int		setup_signal(t_sigact *act, void (*f)(int));

int		ft_isallnum(char *str);

struct	s_packet
{
	uint8_t	data;
	uint8_t	size;
};

struct	s_server_data
{
	t_packet	packet;
	int			my_pid;
	int			sender_pid;
	char		*string;
	char		*tmp_str;
	size_t		str_size;
	size_t		index;
	size_t		packet_nbr;
	int			ping;
	int			flag;
};

struct	s_client_data
{
	int			my_pid;
	int			sender_pid;
	int			ping;
	int			flag;
};

#endif

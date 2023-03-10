/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:10:10 by alde-fre          #+#    #+#             */
/*   Updated: 2023/03/09 15:27:02 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	setup_signal_info(t_sigact *act, void (*f)(int, siginfo_t *, void *))
{
	act->sa_sigaction = f;
	sigemptyset (&act->sa_mask);
	act->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, act, NULL))
		return (0);
	if (sigaction(SIGUSR2, act, NULL))
		return (0);
	return (1);
}

int	setup_signal(t_sigact *act, void (*f)(int))
{
	act->sa_handler = f;
	sigemptyset (&act->sa_mask);
	act->sa_flags = 0;
	if (sigaction(SIGUSR1, act, NULL))
		return (0);
	if (sigaction(SIGUSR2, act, NULL))
		return (0);
	return (1);
}

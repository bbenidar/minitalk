/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:46:10 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/12 14:54:51 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_caract(int *received_bits,
					char *received_message, pid_t client_pid)
{
	if (*received_bits % 8 == 0)
	{
		ft_putchar_fd(*received_message, 1);
		*received_message = 0;
		*received_bits = 0;
		kill(client_pid, SIGUSR1);
	}
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static pid_t	client_pid;
	static pid_t	now_pid;
	static int		received_bits;
	static char		received_message;

	context = 0;
	if (!client_pid)
		client_pid = info->si_pid;
	now_pid = info->si_pid;
	if (now_pid != client_pid)
	{
		client_pid = 0;
		received_bits = 0;
	}
	if (signal == SIGUSR1)
	{
		received_message |= (1 << (received_bits % 8));
		received_bits++;
	}
	else if (signal == SIGUSR2)
		received_bits++;
	print_caract(&received_bits, &received_message, client_pid);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	if (ac == 1)
	{
		ft_strlen(av[0]);
		ft_putstr("Server PID: ");
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
		act.sa_sigaction = &handle_signal;
		act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &act, NULL) < 0
			||sigaction(SIGUSR2, &act, NULL) < 0)
		{
			ft_putstr("Error: Failed to set signal handler\n");
			return (1);
		}
		while (1)
			pause();
	}
	return (0);
}

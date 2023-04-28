/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:45:48 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/12 14:37:12 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int		g_len;

void	reseved_msg(int signal)
{
	static int	i;

	(void)signal;
	i++;
	if (i == g_len)
		ft_putstr("\033[0;32m message was sent successfully\n");
	return ;
}

void	send_bit(int pid, char *buffer)
{
	int	i;
	int	j;

	j = 0;
	while (buffer[j])
	{
		i = 0;
		while (i < 8)
		{
			if (buffer[j] & (1 << i))
			{
				kill(pid, SIGUSR1);
			}
			else
			{
				kill(pid, SIGUSR2);
			}
			usleep(1100);
			i++;
		}
		j++;
	}
}

void	send_message(int pid, char *message)
{
	int		i;
	char	*buffer;

	buffer = (char *)malloc(ft_strlen(message) + 1);
	if (buffer == NULL)
	{
		ft_putstr("\033[0;31m Error: failed to allocate memory\n");
		free(buffer);
		return ;
	}
	ft_strcpy(buffer, message);
	signal(SIGUSR1, reseved_msg);
	send_bit(pid, buffer);
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(1100);
		i++;
	}
	free(buffer);
}

void	check_par(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		ft_putstr("\033[0;31m ERROR input should have *PID* & *MESSAGE*\n");
		exit(1);
	}
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_putstr("\033[0;31m ERROR ||-INVELIBLE PID-||\n");
			exit(1);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	check_par(ac, av);
	pid = ft_atoi(av[1]);
	g_len = ft_strlen(av[2]);
	send_message(pid, av[2]);
	return (0);
}

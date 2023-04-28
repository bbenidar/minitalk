/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:58:02 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/11 23:43:58 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			usleep(800);
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
	send_bit(pid, buffer);
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(900);
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
	send_message(pid, av[2]);
	return (0);
}

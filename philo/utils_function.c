/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 04:20:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/26 02:19:22 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_and_free(t_philo *philo,
			pthread_mutex_t *fork, char **argv)
{
	int	i;

	i = -1;
	if (fork)
	{
		while (++i < a_to_i(argv[1]))
			pthread_mutex_destroy(&fork[i]);
		free(fork);
	}
	if (philo)
	{
		pthread_mutex_destroy(&philo->info->dead);
		pthread_mutex_destroy(&philo->info->meals);
		free(philo->info);
		free(philo);
	}
}

int	a_to_i(const char *str)
{
	int					i;
	unsigned long int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			return (0);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
		if (result > 2147483647)
			return (0);
	}
	return (result);
}

static int	help_func(int len_str, char **str)
{
	int	i;
	int	s;
	int	l;

	s = 1;
	while (s < len_str)
	{
		l = 1;
		i = 0;
		while (str[s][i] != 0)
		{
			if (str[s][i] >= 48 && str[s][i] <= 57)
				l = 0;
			if (str[s][i] != 43)
				if (str[s][i] < 48 || str[s][i] > 57)
					return (-1);
			i++;
		}
		if (l == 1)
			return (-1);
		s++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	s;

	i = 1;
	if (help_func(argc, argv) == -1)
		return (-1);
	while (i < argc)
	{
		s = 0;
		while (argv[i][s] != 0)
		{
			if (argv[i][s] == 43 && s - 1 >= 0)
				return (-1);
			if (argv[i][s] == 43)
				if (argv[i][++s] == 43 || argv[i][s] == 0)
					return (-1);
			s++;
		}
		i++;
	}
	if (i == argc)
		return (0);
	return (-1);
}
